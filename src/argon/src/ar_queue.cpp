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
 * @brief Implementation of Ar microkernel queue.
 */

#include "ar_internal.h"
#include <string.h>

using namespace Ar;

//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------

//! Returns a uint8_t * to the first byte of element @a i of the queue.
//!
//! @param q The queue object.
//! @param i Index of the queue element, base 0.
#define QUEUE_ELEMENT(q, i) (&(q)->m_elements[(q)->m_elementSize * (i)])

//------------------------------------------------------------------------------
// Implementation
//------------------------------------------------------------------------------

// See ar_kernel.h for documentation of this function.
ar_status_t ar_queue_create(ar_queue_t * queue, const char * name, void * storage, unsigned elementSize, unsigned capacity)
{
    if (!queue || !storage || !elementSize || !capacity)
    {
        return kArInvalidParameterError;
    }

    memset(queue, 0, sizeof(ar_queue_t));

    queue->m_name = name ? name : AR_ANONYMOUS_OBJECT_NAME;
    queue->m_elements = reinterpret_cast<uint8_t *>(storage);
    queue->m_elementSize = elementSize;
    queue->m_capacity = capacity;

#if AR_GLOBAL_OBJECT_LISTS
    queue->m_createdNode.m_obj = queue;
    g_ar.allObjects.queues.add(&queue->m_createdNode);
#endif // AR_GLOBAL_OBJECT_LISTS

    return kArSuccess;
}

// See ar_kernel.h for documentation of this function.
ar_status_t ar_queue_delete(ar_queue_t * queue)
{
    if (!queue)
    {
        return kArInvalidParameterError;
    }

    // Unblock all threads blocked on this queue.
    ar_thread_t * thread;
    while (queue->m_sendBlockedList.m_head)
    {
        thread = queue->m_sendBlockedList.m_head->getObject<ar_thread_t>();
        thread->unblockWithStatus(queue->m_sendBlockedList, kArObjectDeletedError);
    }

    while (queue->m_receiveBlockedList.m_head)
    {
        thread = queue->m_receiveBlockedList.m_head->getObject<ar_thread_t>();
        thread->unblockWithStatus(queue->m_receiveBlockedList, kArObjectDeletedError);
    }

#if AR_GLOBAL_OBJECT_LISTS
    g_ar.allObjects.queues.remove(&queue->m_createdNode);
#endif // AR_GLOBAL_OBJECT_LISTS

    return kArSuccess;
}

// See ar_kernel.h for documentation of this function.
ar_status_t ar_queue_send(ar_queue_t * queue, const void * element, uint32_t timeout)
{
    if (!queue || !element)
    {
        return kArInvalidParameterError;
    }

    KernelLock guard;

    // Check for full queue
    if (queue->m_count >= queue->m_capacity)
    {
        // If the queue is full and a zero timeout was given, return immediately.
        if (timeout == kArNoTimeout)
        {
            return kArQueueFullError;
        }

        // Otherwise block until the queue has room.
        ar_thread_t * thread = g_ar.currentThread;
        thread->block(queue->m_sendBlockedList, timeout);

        // Reenable interrupts to allow switching contexts.
        guard.enable();

        // Yield to the scheduler. While other threads are executing, interrupts
        // will be restored to the state on those threads. When we come back to
        // this thread, interrupts will still be disabled.
        ar_kernel_enter_scheduler();

        guard.disable();

        // We're back from the scheduler. Interrupts are still disabled.
        // Check for errors and exit early if there was one.
        if (thread->m_unblockStatus != kArSuccess)
        {
            // Failed to gain the semaphore, probably due to a timeout.
            queue->m_sendBlockedList.remove(&thread->m_blockedNode);
            return thread->m_unblockStatus;
        }
    }

    // fill element
    uint8_t * elementSlot = QUEUE_ELEMENT(queue, queue->m_tail);
    memcpy(elementSlot, element, queue->m_elementSize);

    // Update queue pointers
    queue->m_tail = (queue->m_tail + 1) % queue->m_capacity;
    queue->m_count++;

    // Are there any threads waiting to receive?
    if (queue->m_receiveBlockedList.m_head)
    {
        // Unblock the head of the blocked list.
        ar_thread_t * thread = queue->m_receiveBlockedList.m_head->getObject<ar_thread_t>();
        thread->unblockWithStatus(queue->m_receiveBlockedList, kArSuccess);

        // Invoke the scheduler if the unblocked thread is higher priority than the current one.
        if (thread->m_priority > g_ar.currentThread->m_priority)
        {
            // Reenable interrupts to allow switching contexts.
            guard.enable();

            ar_kernel_enter_scheduler();
        }
    }

    return kArSuccess;
}

// See ar_kernel.h for documentation of this function.
ar_status_t ar_queue_receive(ar_queue_t * queue, void * element, uint32_t timeout)
{
    if (!queue || !element)
    {
        return kArInvalidParameterError;
    }

    KernelLock guard;

    // Check for empty queue
    if (queue->m_count == 0)
    {
        if (timeout == kArNoTimeout)
        {
            return kArQueueEmptyError;
        }

        // Otherwise block until the queue has room.
        ar_thread_t * thread = g_ar.currentThread;
        thread->block(queue->m_receiveBlockedList, timeout);

        // Reenable interrupts to allow switching contexts.
        guard.enable();

        // Yield to the scheduler. While other threads are executing, interrupts
        // will be restored to the state on those threads. When we come back to
        // this thread, interrupts will still be disabled.
        ar_kernel_enter_scheduler();

        guard.disable();

        // We're back from the scheduler. Interrupts are still disabled.
        // Check for errors and exit early if there was one.
        if (thread->m_unblockStatus != kArSuccess)
        {
            // Failed to gain the semaphore, probably due to a timeout.
            queue->m_receiveBlockedList.remove(&thread->m_blockedNode);
            return thread->m_unblockStatus;
        }
    }

    // read out data
    uint8_t * elementSlot = QUEUE_ELEMENT(queue, queue->m_head);
    memcpy(element, elementSlot, queue->m_elementSize);

    // update queue
    queue->m_head = (queue->m_head + 1) % queue->m_capacity;
    queue->m_count--;

    // Are there any threads waiting to send?
    if (queue->m_sendBlockedList.m_head)
    {
        // Unblock the head of the blocked list.
        ar_thread_t * thread = queue->m_sendBlockedList.m_head->getObject<ar_thread_t>();
        thread->unblockWithStatus(queue->m_sendBlockedList, kArSuccess);

        // Invoke the scheduler if the unblocked thread is higher priority than the current one.
        if (thread->m_priority > g_ar.currentThread->m_priority)
        {
            // Reenable interrupts to allow switching contexts.
            guard.enable();

            ar_kernel_enter_scheduler();
        }
    }

    return kArSuccess;
}

const char * ar_queue_get_name(ar_queue_t * queue)
{
    return queue ? queue->m_name : NULL;
}

//------------------------------------------------------------------------------
// EOF
//------------------------------------------------------------------------------
