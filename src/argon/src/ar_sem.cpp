/*
 * Copyright (c) 2007-2014 Immo Software
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its contributors may
 *   be used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*!
 * @file
 * @brief Source for Ar microkernel semaphores.
 */

#include "ar_internal.h"
#include <string.h>
#include <assert.h>

using namespace Ar;

//------------------------------------------------------------------------------
// Code
//------------------------------------------------------------------------------

// See ar_kernel.h for documentation of this function.
ar_status_t ar_semaphore_create(ar_semaphore_t * sem, const char * name, unsigned count)
{
    if (!sem)
    {
        return kArInvalidParameterError;
    }

    memset(sem, 0, sizeof(ar_semaphore_t));
    sem->m_name = name ? name : AR_ANONYMOUS_OBJECT_NAME;
    sem->m_count = count;

#if AR_GLOBAL_OBJECT_LISTS
    sem->m_createdNode.m_obj = sem;
    g_ar.allObjects.semaphores.add(&sem->m_createdNode);
#endif // AR_GLOBAL_OBJECT_LISTS

    return kArSuccess;
}

// See ar_kernel.h for documentation of this function.
ar_status_t ar_semaphore_delete(ar_semaphore_t * sem)
{
    if (!sem)
    {
        return kArInvalidParameterError;
    }

    // Unblock all threads blocked on this semaphore.
    while (sem->m_blockedList.m_head)
    {
        sem->m_blockedList.m_head->getObject<ar_thread_t>()->unblockWithStatus(sem->m_blockedList, kArObjectDeletedError);
    }

#if AR_GLOBAL_OBJECT_LISTS
    g_ar.allObjects.semaphores.remove(&sem->m_createdNode);
#endif // AR_GLOBAL_OBJECT_LISTS

    return kArSuccess;
}

// See ar_kernel.h for documentation of this function.
ar_status_t ar_semaphore_get(ar_semaphore_t * sem, uint32_t timeout)
{
    if (!sem)
    {
        return kArInvalidParameterError;
    }

    // Ensure that only 0 timeouts are specified when called from an IRQ handler.
    if (ar_port_get_irq_state() && timeout != 0)
    {
        return kArNotFromInterruptError;
    }

    KernelLock guard;

    if (sem->m_count == 0)
    {
        // Count is 0, so we must block. Return immediately if the timeout is 0.
        if (timeout == kArNoTimeout)
        {
            return kArTimeoutError;
        }

        // Block this thread on the semaphore.
        ar_thread_t * thread = g_ar.currentThread;
        thread->block(sem->m_blockedList, timeout);

        guard.enable();

        // Yield to the scheduler. We'll return when a call to put()
        // wakes this thread. If another thread gains control, interrupts will be
        // set to that thread's last state.
        ar_kernel_enter_scheduler();

        guard.disable();

        // We're back from the scheduler. Interrupts are still disabled.
        // Check for errors and exit early if there was one.
        if (thread->m_unblockStatus != kArSuccess)
        {
            // Failed to gain the semaphore, probably due to a timeout.
            sem->m_blockedList.remove(&thread->m_blockedNode);
            return thread->m_unblockStatus;
        }
    }

    // Take ownership of the semaphore.
    --sem->m_count;

    return kArSuccess;
}

// See ar_kernel.h for documentation of this function.
ar_status_t ar_semaphore_put(ar_semaphore_t * sem)
{
    if (!sem)
    {
        return kArInvalidParameterError;
    }

    KernelLock guard;

    // Increment count.
    ++sem->m_count;

    // Are there any threads waiting on this semaphore?
    if (sem->m_blockedList.m_head)
    {
        // Unblock the head of the blocked list.
        ar_thread_t * thread = sem->m_blockedList.m_head->getObject<ar_thread_t>();
        thread->unblockWithStatus(sem->m_blockedList, kArSuccess);

        // Invoke the scheduler if the unblocked thread is higher priority than the current one.
        if (thread->m_priority > g_ar.currentThread->m_priority)
        {
            guard.enable();

            ar_kernel_enter_scheduler();
        }
    }

    return kArSuccess;
}

// See ar_kernel.h for documentation of this function.
uint32_t ar_semaphore_get_count(ar_semaphore_t * sem)
{
    return sem ? sem->m_count : 0;
}

const char * ar_semaphore_get_name(ar_semaphore_t * sem)
{
    return sem ? sem->m_name : NULL;
}

//------------------------------------------------------------------------------
// EOF
//------------------------------------------------------------------------------
