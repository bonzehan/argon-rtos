/*
 * Copyright (c) 2013, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL FREESCALE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 */
/*
 * WARNING! DO NOT EDIT THIS FILE DIRECTLY!
 *
 * This file was generated automatically and any changes may be lost.
 */
#ifndef __HW_SMC_REGISTERS_H__
#define __HW_SMC_REGISTERS_H__

#include "regs.h"

/*
 * MK64F12 SMC
 *
 * System Mode Controller
 *
 * Registers defined in this header file:
 * - HW_SMC_PMPROT - Power Mode Protection register
 * - HW_SMC_PMCTRL - Power Mode Control register
 * - HW_SMC_VLLSCTRL - VLLS Control register
 * - HW_SMC_PMSTAT - Power Mode Status register
 *
 * - hw_smc_t - Struct containing all module registers.
 */

//! @name Module base addresses
//@{
#ifndef REGS_SMC_BASE
#define HW_SMC_INSTANCE_COUNT (1U) //!< Number of instances of the SMC module.
#define REGS_SMC_BASE (0x4007E000U) //!< Base address for SMC.
#endif
//@}

//-------------------------------------------------------------------------------------------
// HW_SMC_PMPROT - Power Mode Protection register
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_SMC_PMPROT - Power Mode Protection register (RW)
 *
 * Reset value: 0x00U
 *
 * This register provides protection for entry into any low-power run or stop
 * mode. The enabling of the low-power run or stop mode occurs by configuring the
 * Power Mode Control register (PMCTRL). The PMPROT register can be written only
 * once after any system reset. If the MCU is configured for a disallowed or
 * reserved power mode, the MCU remains in its current power mode. For example, if the
 * MCU is in normal RUN mode and AVLP is 0, an attempt to enter VLPR mode using
 * PMCTRL[RUNM] is blocked and the RUNM bits remain 00b, indicating the MCU is
 * still in Normal Run mode. This register is reset on Chip Reset not VLLS and by
 * reset types that trigger Chip Reset not VLLS. It is unaffected by reset types
 * that do not trigger Chip Reset not VLLS. See the Reset section details for more
 * information.
 */
typedef union _hw_smc_pmprot
{
    uint8_t U;
    struct _hw_smc_pmprot_bitfields
    {
        uint8_t RESERVED0 : 1;         //!< [0]
        uint8_t AVLLS : 1;             //!< [1] Allow Very-Low-Leakage Stop Mode
        uint8_t RESERVED1 : 1;         //!< [2]
        uint8_t ALLS : 1;              //!< [3] Allow Low-Leakage Stop Mode
        uint8_t RESERVED2 : 1;         //!< [4]
        uint8_t AVLP : 1;              //!< [5] Allow Very-Low-Power Modes
        uint8_t RESERVED3 : 2;         //!< [7:6]
    } B;
} hw_smc_pmprot_t;
#endif

/*!
 * @name Constants and macros for entire SMC_PMPROT register
 */
//@{
#define HW_SMC_PMPROT_ADDR       (REGS_SMC_BASE + 0x0U)

#ifndef __LANGUAGE_ASM__
#define HW_SMC_PMPROT            (*(__IO hw_smc_pmprot_t *) HW_SMC_PMPROT_ADDR)
#define HW_SMC_PMPROT_RD         (HW_SMC_PMPROT.U)
#define HW_SMC_PMPROT_WR(v)      (HW_SMC_PMPROT.U = (v))
#define HW_SMC_PMPROT_SET(v)     (HW_SMC_PMPROT_WR(HW_SMC_PMPROT_RD |  (v)))
#define HW_SMC_PMPROT_CLR(v)     (HW_SMC_PMPROT_WR(HW_SMC_PMPROT_RD & ~(v)))
#define HW_SMC_PMPROT_TOG(v)     (HW_SMC_PMPROT_WR(HW_SMC_PMPROT_RD ^  (v)))
#endif
//@}

/*
 * Constants & macros for individual SMC_PMPROT bitfields
 */

/*!
 * @name Register SMC_PMPROT, field AVLLS[1] (RW)
 *
 * Provided the appropriate control bits are set up in PMCTRL, this write once
 * bit allows the MCU to enter any very-low-leakage stop mode (VLLSx).
 *
 * Values:
 * - 0 - Any VLLSx mode is not allowed
 * - 1 - Any VLLSx mode is allowed
 */
//@{
#define BP_SMC_PMPROT_AVLLS  (1U)          //!< Bit position for SMC_PMPROT_AVLLS.
#define BM_SMC_PMPROT_AVLLS  (0x02U)       //!< Bit mask for SMC_PMPROT_AVLLS.
#define BS_SMC_PMPROT_AVLLS  (1U)          //!< Bit field size in bits for SMC_PMPROT_AVLLS.

#ifndef __LANGUAGE_ASM__
//! @brief Read current value of the SMC_PMPROT_AVLLS field.
#define BR_SMC_PMPROT_AVLLS  (BITBAND_ACCESS8(HW_SMC_PMPROT_ADDR, BP_SMC_PMPROT_AVLLS))
#endif

//! @brief Format value for bitfield SMC_PMPROT_AVLLS.
#define BF_SMC_PMPROT_AVLLS(v) (__REG_VALUE_TYPE((__REG_VALUE_TYPE((v), uint8_t) << BP_SMC_PMPROT_AVLLS), uint8_t) & BM_SMC_PMPROT_AVLLS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the AVLLS field to a new value.
#define BW_SMC_PMPROT_AVLLS(v) (BITBAND_ACCESS8(HW_SMC_PMPROT_ADDR, BP_SMC_PMPROT_AVLLS) = (v))
#endif
//@}

/*!
 * @name Register SMC_PMPROT, field ALLS[3] (RW)
 *
 * Provided the appropriate control bits are set up in PMCTRL, this write-once
 * bit allows the MCU to enter any low-leakage stop mode (LLS).
 *
 * Values:
 * - 0 - LLS is not allowed
 * - 1 - LLS is allowed
 */
//@{
#define BP_SMC_PMPROT_ALLS   (3U)          //!< Bit position for SMC_PMPROT_ALLS.
#define BM_SMC_PMPROT_ALLS   (0x08U)       //!< Bit mask for SMC_PMPROT_ALLS.
#define BS_SMC_PMPROT_ALLS   (1U)          //!< Bit field size in bits for SMC_PMPROT_ALLS.

#ifndef __LANGUAGE_ASM__
//! @brief Read current value of the SMC_PMPROT_ALLS field.
#define BR_SMC_PMPROT_ALLS   (BITBAND_ACCESS8(HW_SMC_PMPROT_ADDR, BP_SMC_PMPROT_ALLS))
#endif

//! @brief Format value for bitfield SMC_PMPROT_ALLS.
#define BF_SMC_PMPROT_ALLS(v) (__REG_VALUE_TYPE((__REG_VALUE_TYPE((v), uint8_t) << BP_SMC_PMPROT_ALLS), uint8_t) & BM_SMC_PMPROT_ALLS)

#ifndef __LANGUAGE_ASM__
//! @brief Set the ALLS field to a new value.
#define BW_SMC_PMPROT_ALLS(v) (BITBAND_ACCESS8(HW_SMC_PMPROT_ADDR, BP_SMC_PMPROT_ALLS) = (v))
#endif
//@}

/*!
 * @name Register SMC_PMPROT, field AVLP[5] (RW)
 *
 * Provided the appropriate control bits are set up in PMCTRL, this write-once
 * bit allows the MCU to enter any very-low-power mode (VLPR, VLPW, and VLPS).
 *
 * Values:
 * - 0 - VLPR, VLPW and VLPS are not allowed
 * - 1 - VLPR, VLPW and VLPS are allowed
 */
//@{
#define BP_SMC_PMPROT_AVLP   (5U)          //!< Bit position for SMC_PMPROT_AVLP.
#define BM_SMC_PMPROT_AVLP   (0x20U)       //!< Bit mask for SMC_PMPROT_AVLP.
#define BS_SMC_PMPROT_AVLP   (1U)          //!< Bit field size in bits for SMC_PMPROT_AVLP.

#ifndef __LANGUAGE_ASM__
//! @brief Read current value of the SMC_PMPROT_AVLP field.
#define BR_SMC_PMPROT_AVLP   (BITBAND_ACCESS8(HW_SMC_PMPROT_ADDR, BP_SMC_PMPROT_AVLP))
#endif

//! @brief Format value for bitfield SMC_PMPROT_AVLP.
#define BF_SMC_PMPROT_AVLP(v) (__REG_VALUE_TYPE((__REG_VALUE_TYPE((v), uint8_t) << BP_SMC_PMPROT_AVLP), uint8_t) & BM_SMC_PMPROT_AVLP)

#ifndef __LANGUAGE_ASM__
//! @brief Set the AVLP field to a new value.
#define BW_SMC_PMPROT_AVLP(v) (BITBAND_ACCESS8(HW_SMC_PMPROT_ADDR, BP_SMC_PMPROT_AVLP) = (v))
#endif
//@}

//-------------------------------------------------------------------------------------------
// HW_SMC_PMCTRL - Power Mode Control register
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_SMC_PMCTRL - Power Mode Control register (RW)
 *
 * Reset value: 0x00U
 *
 * The PMCTRL register controls entry into low-power run and stop modes,
 * provided that the selected power mode is allowed via an appropriate setting of the
 * protection (PMPROT) register. This register is reset on Chip POR not VLLS and by
 * reset types that trigger Chip POR not VLLS. It is unaffected by reset types
 * that do not trigger Chip POR not VLLS. See the Reset section details for more
 * information.
 */
typedef union _hw_smc_pmctrl
{
    uint8_t U;
    struct _hw_smc_pmctrl_bitfields
    {
        uint8_t STOPM : 3;             //!< [2:0] Stop Mode Control
        uint8_t STOPA : 1;             //!< [3] Stop Aborted
        uint8_t RESERVED0 : 1;         //!< [4]
        uint8_t RUNM : 2;              //!< [6:5] Run Mode Control
        uint8_t LPWUI : 1;             //!< [7] Low-Power Wake Up On Interrupt
    } B;
} hw_smc_pmctrl_t;
#endif

/*!
 * @name Constants and macros for entire SMC_PMCTRL register
 */
//@{
#define HW_SMC_PMCTRL_ADDR       (REGS_SMC_BASE + 0x1U)

#ifndef __LANGUAGE_ASM__
#define HW_SMC_PMCTRL            (*(__IO hw_smc_pmctrl_t *) HW_SMC_PMCTRL_ADDR)
#define HW_SMC_PMCTRL_RD         (HW_SMC_PMCTRL.U)
#define HW_SMC_PMCTRL_WR(v)      (HW_SMC_PMCTRL.U = (v))
#define HW_SMC_PMCTRL_SET(v)     (HW_SMC_PMCTRL_WR(HW_SMC_PMCTRL_RD |  (v)))
#define HW_SMC_PMCTRL_CLR(v)     (HW_SMC_PMCTRL_WR(HW_SMC_PMCTRL_RD & ~(v)))
#define HW_SMC_PMCTRL_TOG(v)     (HW_SMC_PMCTRL_WR(HW_SMC_PMCTRL_RD ^  (v)))
#endif
//@}

/*
 * Constants & macros for individual SMC_PMCTRL bitfields
 */

/*!
 * @name Register SMC_PMCTRL, field STOPM[2:0] (RW)
 *
 * When written, controls entry into the selected stop mode when Sleep-Now or
 * Sleep-On-Exit mode is entered with SLEEPDEEP=1 . Writes to this field are
 * blocked if the protection level has not been enabled using the PMPROT register.
 * After any system reset, this field is cleared by hardware on any successful write
 * to the PMPROT register. When set to VLLSx, the VLLSM bits in the VLLSCTRL
 * register is used to further select the particular VLLS submode which will be
 * entered.
 *
 * Values:
 * - 000 - Normal Stop (STOP)
 * - 001 - Reserved
 * - 010 - Very-Low-Power Stop (VLPS)
 * - 011 - Low-Leakage Stop (LLS)
 * - 100 - Very-Low-Leakage Stop (VLLSx)
 * - 101 - Reserved
 * - 110 - Reseved
 * - 111 - Reserved
 */
//@{
#define BP_SMC_PMCTRL_STOPM  (0U)          //!< Bit position for SMC_PMCTRL_STOPM.
#define BM_SMC_PMCTRL_STOPM  (0x07U)       //!< Bit mask for SMC_PMCTRL_STOPM.
#define BS_SMC_PMCTRL_STOPM  (3U)          //!< Bit field size in bits for SMC_PMCTRL_STOPM.

#ifndef __LANGUAGE_ASM__
//! @brief Read current value of the SMC_PMCTRL_STOPM field.
#define BR_SMC_PMCTRL_STOPM  (HW_SMC_PMCTRL.B.STOPM)
#endif

//! @brief Format value for bitfield SMC_PMCTRL_STOPM.
#define BF_SMC_PMCTRL_STOPM(v) (__REG_VALUE_TYPE((__REG_VALUE_TYPE((v), uint8_t) << BP_SMC_PMCTRL_STOPM), uint8_t) & BM_SMC_PMCTRL_STOPM)

#ifndef __LANGUAGE_ASM__
//! @brief Set the STOPM field to a new value.
#define BW_SMC_PMCTRL_STOPM(v) (HW_SMC_PMCTRL_WR((HW_SMC_PMCTRL_RD & ~BM_SMC_PMCTRL_STOPM) | BF_SMC_PMCTRL_STOPM(v)))
#endif
//@}

/*!
 * @name Register SMC_PMCTRL, field STOPA[3] (RO)
 *
 * When set, this read-only status bit indicates an interrupt or reset occured
 * during the previous stop mode entry sequence, preventing the system from
 * entering that mode. This bit is cleared by hardware at the beginning of any stop
 * mode entry sequence and is set if the sequence was aborted.
 *
 * Values:
 * - 0 - The previous stop mode entry was successsful.
 * - 1 - The previous stop mode entry was aborted.
 */
//@{
#define BP_SMC_PMCTRL_STOPA  (3U)          //!< Bit position for SMC_PMCTRL_STOPA.
#define BM_SMC_PMCTRL_STOPA  (0x08U)       //!< Bit mask for SMC_PMCTRL_STOPA.
#define BS_SMC_PMCTRL_STOPA  (1U)          //!< Bit field size in bits for SMC_PMCTRL_STOPA.

#ifndef __LANGUAGE_ASM__
//! @brief Read current value of the SMC_PMCTRL_STOPA field.
#define BR_SMC_PMCTRL_STOPA  (BITBAND_ACCESS8(HW_SMC_PMCTRL_ADDR, BP_SMC_PMCTRL_STOPA))
#endif
//@}

/*!
 * @name Register SMC_PMCTRL, field RUNM[6:5] (RW)
 *
 * When written, causes entry into the selected run mode. Writes to this field
 * are blocked if the protection level has not been enabled using the PMPROT
 * register. This field is cleared by hardware on any exit to normal RUN mode. RUNM
 * may be set to VLPR only when PMSTAT=RUN. After being written to VLPR, RUNM
 * should not be written back to RUN until PMSTAT=VLPR.
 *
 * Values:
 * - 00 - Normal Run mode (RUN)
 * - 01 - Reserved
 * - 10 - Very-Low-Power Run mode (VLPR)
 * - 11 - Reserved
 */
//@{
#define BP_SMC_PMCTRL_RUNM   (5U)          //!< Bit position for SMC_PMCTRL_RUNM.
#define BM_SMC_PMCTRL_RUNM   (0x60U)       //!< Bit mask for SMC_PMCTRL_RUNM.
#define BS_SMC_PMCTRL_RUNM   (2U)          //!< Bit field size in bits for SMC_PMCTRL_RUNM.

#ifndef __LANGUAGE_ASM__
//! @brief Read current value of the SMC_PMCTRL_RUNM field.
#define BR_SMC_PMCTRL_RUNM   (HW_SMC_PMCTRL.B.RUNM)
#endif

//! @brief Format value for bitfield SMC_PMCTRL_RUNM.
#define BF_SMC_PMCTRL_RUNM(v) (__REG_VALUE_TYPE((__REG_VALUE_TYPE((v), uint8_t) << BP_SMC_PMCTRL_RUNM), uint8_t) & BM_SMC_PMCTRL_RUNM)

#ifndef __LANGUAGE_ASM__
//! @brief Set the RUNM field to a new value.
#define BW_SMC_PMCTRL_RUNM(v) (HW_SMC_PMCTRL_WR((HW_SMC_PMCTRL_RD & ~BM_SMC_PMCTRL_RUNM) | BF_SMC_PMCTRL_RUNM(v)))
#endif
//@}

/*!
 * @name Register SMC_PMCTRL, field LPWUI[7] (RW)
 *
 * Causes the SMC to exit to normal RUN mode when any active MCU interrupt
 * occurs while in a VLP mode (VLPR, VLPW or VLPS). If VLPS mode was entered directly
 * from RUN mode, the SMC will always exit back to normal RUN mode regardless of
 * the LPWUI setting. LPWUI must be modified only while the system is in RUN
 * mode, that is, when PMSTAT=RUN.
 *
 * Values:
 * - 0 - The system remains in a VLP mode on an interrupt
 * - 1 - The system exits to Normal RUN mode on an interrupt
 */
//@{
#define BP_SMC_PMCTRL_LPWUI  (7U)          //!< Bit position for SMC_PMCTRL_LPWUI.
#define BM_SMC_PMCTRL_LPWUI  (0x80U)       //!< Bit mask for SMC_PMCTRL_LPWUI.
#define BS_SMC_PMCTRL_LPWUI  (1U)          //!< Bit field size in bits for SMC_PMCTRL_LPWUI.

#ifndef __LANGUAGE_ASM__
//! @brief Read current value of the SMC_PMCTRL_LPWUI field.
#define BR_SMC_PMCTRL_LPWUI  (BITBAND_ACCESS8(HW_SMC_PMCTRL_ADDR, BP_SMC_PMCTRL_LPWUI))
#endif

//! @brief Format value for bitfield SMC_PMCTRL_LPWUI.
#define BF_SMC_PMCTRL_LPWUI(v) (__REG_VALUE_TYPE((__REG_VALUE_TYPE((v), uint8_t) << BP_SMC_PMCTRL_LPWUI), uint8_t) & BM_SMC_PMCTRL_LPWUI)

#ifndef __LANGUAGE_ASM__
//! @brief Set the LPWUI field to a new value.
#define BW_SMC_PMCTRL_LPWUI(v) (BITBAND_ACCESS8(HW_SMC_PMCTRL_ADDR, BP_SMC_PMCTRL_LPWUI) = (v))
#endif
//@}

//-------------------------------------------------------------------------------------------
// HW_SMC_VLLSCTRL - VLLS Control register
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_SMC_VLLSCTRL - VLLS Control register (RW)
 *
 * Reset value: 0x03U
 *
 * The VLLSCTRL register controls features related to VLLS modes. This register
 * is reset on Chip POR not VLLS and by reset types that trigger Chip POR not
 * VLLS. It is unaffected by reset types that do not trigger Chip POR not VLLS. See
 * the Reset section details for more information.
 */
typedef union _hw_smc_vllsctrl
{
    uint8_t U;
    struct _hw_smc_vllsctrl_bitfields
    {
        uint8_t VLLSM : 3;             //!< [2:0] VLLS Mode Control
        uint8_t RESERVED0 : 2;         //!< [4:3]
        uint8_t PORPO : 1;             //!< [5] POR Power Option
        uint8_t RESERVED1 : 2;         //!< [7:6]
    } B;
} hw_smc_vllsctrl_t;
#endif

/*!
 * @name Constants and macros for entire SMC_VLLSCTRL register
 */
//@{
#define HW_SMC_VLLSCTRL_ADDR     (REGS_SMC_BASE + 0x2U)

#ifndef __LANGUAGE_ASM__
#define HW_SMC_VLLSCTRL          (*(__IO hw_smc_vllsctrl_t *) HW_SMC_VLLSCTRL_ADDR)
#define HW_SMC_VLLSCTRL_RD       (HW_SMC_VLLSCTRL.U)
#define HW_SMC_VLLSCTRL_WR(v)    (HW_SMC_VLLSCTRL.U = (v))
#define HW_SMC_VLLSCTRL_SET(v)   (HW_SMC_VLLSCTRL_WR(HW_SMC_VLLSCTRL_RD |  (v)))
#define HW_SMC_VLLSCTRL_CLR(v)   (HW_SMC_VLLSCTRL_WR(HW_SMC_VLLSCTRL_RD & ~(v)))
#define HW_SMC_VLLSCTRL_TOG(v)   (HW_SMC_VLLSCTRL_WR(HW_SMC_VLLSCTRL_RD ^  (v)))
#endif
//@}

/*
 * Constants & macros for individual SMC_VLLSCTRL bitfields
 */

/*!
 * @name Register SMC_VLLSCTRL, field VLLSM[2:0] (RW)
 *
 * Controls which VLLS sub-mode to enter if STOPM=VLLS.
 *
 * Values:
 * - 000 - VLLS0
 * - 001 - VLLS1
 * - 010 - VLLS2
 * - 011 - VLLS3
 * - 100 - Reserved
 * - 101 - Reserved
 * - 110 - Reserved
 * - 111 - Reserved
 */
//@{
#define BP_SMC_VLLSCTRL_VLLSM (0U)         //!< Bit position for SMC_VLLSCTRL_VLLSM.
#define BM_SMC_VLLSCTRL_VLLSM (0x07U)      //!< Bit mask for SMC_VLLSCTRL_VLLSM.
#define BS_SMC_VLLSCTRL_VLLSM (3U)         //!< Bit field size in bits for SMC_VLLSCTRL_VLLSM.

#ifndef __LANGUAGE_ASM__
//! @brief Read current value of the SMC_VLLSCTRL_VLLSM field.
#define BR_SMC_VLLSCTRL_VLLSM (HW_SMC_VLLSCTRL.B.VLLSM)
#endif

//! @brief Format value for bitfield SMC_VLLSCTRL_VLLSM.
#define BF_SMC_VLLSCTRL_VLLSM(v) (__REG_VALUE_TYPE((__REG_VALUE_TYPE((v), uint8_t) << BP_SMC_VLLSCTRL_VLLSM), uint8_t) & BM_SMC_VLLSCTRL_VLLSM)

#ifndef __LANGUAGE_ASM__
//! @brief Set the VLLSM field to a new value.
#define BW_SMC_VLLSCTRL_VLLSM(v) (HW_SMC_VLLSCTRL_WR((HW_SMC_VLLSCTRL_RD & ~BM_SMC_VLLSCTRL_VLLSM) | BF_SMC_VLLSCTRL_VLLSM(v)))
#endif
//@}

/*!
 * @name Register SMC_VLLSCTRL, field PORPO[5] (RW)
 *
 * Controls whether the POR detect circuit (for brown-out detection) is enabled
 * in VLLS0 mode.
 *
 * Values:
 * - 0 - POR detect circuit is enabled in VLLS0
 * - 1 - POR detect circuit is disabled in VLLS0
 */
//@{
#define BP_SMC_VLLSCTRL_PORPO (5U)         //!< Bit position for SMC_VLLSCTRL_PORPO.
#define BM_SMC_VLLSCTRL_PORPO (0x20U)      //!< Bit mask for SMC_VLLSCTRL_PORPO.
#define BS_SMC_VLLSCTRL_PORPO (1U)         //!< Bit field size in bits for SMC_VLLSCTRL_PORPO.

#ifndef __LANGUAGE_ASM__
//! @brief Read current value of the SMC_VLLSCTRL_PORPO field.
#define BR_SMC_VLLSCTRL_PORPO (BITBAND_ACCESS8(HW_SMC_VLLSCTRL_ADDR, BP_SMC_VLLSCTRL_PORPO))
#endif

//! @brief Format value for bitfield SMC_VLLSCTRL_PORPO.
#define BF_SMC_VLLSCTRL_PORPO(v) (__REG_VALUE_TYPE((__REG_VALUE_TYPE((v), uint8_t) << BP_SMC_VLLSCTRL_PORPO), uint8_t) & BM_SMC_VLLSCTRL_PORPO)

#ifndef __LANGUAGE_ASM__
//! @brief Set the PORPO field to a new value.
#define BW_SMC_VLLSCTRL_PORPO(v) (BITBAND_ACCESS8(HW_SMC_VLLSCTRL_ADDR, BP_SMC_VLLSCTRL_PORPO) = (v))
#endif
//@}

//-------------------------------------------------------------------------------------------
// HW_SMC_PMSTAT - Power Mode Status register
//-------------------------------------------------------------------------------------------

#ifndef __LANGUAGE_ASM__
/*!
 * @brief HW_SMC_PMSTAT - Power Mode Status register (RO)
 *
 * Reset value: 0x01U
 *
 * PMSTAT is a read-only, one-hot register which indicates the current power
 * mode of the system. This register is reset on Chip POR not VLLS and by reset
 * types that trigger Chip POR not VLLS. It is unaffected by reset types that do not
 * trigger Chip POR not VLLS. See the Reset section details for more information.
 */
typedef union _hw_smc_pmstat
{
    uint8_t U;
    struct _hw_smc_pmstat_bitfields
    {
        uint8_t PMSTAT : 7;            //!< [6:0]
        uint8_t RESERVED0 : 1;         //!< [7]
    } B;
} hw_smc_pmstat_t;
#endif

/*!
 * @name Constants and macros for entire SMC_PMSTAT register
 */
//@{
#define HW_SMC_PMSTAT_ADDR       (REGS_SMC_BASE + 0x3U)

#ifndef __LANGUAGE_ASM__
#define HW_SMC_PMSTAT            (*(__I hw_smc_pmstat_t *) HW_SMC_PMSTAT_ADDR)
#define HW_SMC_PMSTAT_RD         (HW_SMC_PMSTAT.U)
#endif
//@}

/*
 * Constants & macros for individual SMC_PMSTAT bitfields
 */

/*!
 * @name Register SMC_PMSTAT, field PMSTAT[6:0] (RO)
 *
 * When debug is enabled, the PMSTAT will not update to STOP or VLPS
 */
//@{
#define BP_SMC_PMSTAT_PMSTAT (0U)          //!< Bit position for SMC_PMSTAT_PMSTAT.
#define BM_SMC_PMSTAT_PMSTAT (0x7FU)       //!< Bit mask for SMC_PMSTAT_PMSTAT.
#define BS_SMC_PMSTAT_PMSTAT (7U)          //!< Bit field size in bits for SMC_PMSTAT_PMSTAT.

#ifndef __LANGUAGE_ASM__
//! @brief Read current value of the SMC_PMSTAT_PMSTAT field.
#define BR_SMC_PMSTAT_PMSTAT (HW_SMC_PMSTAT.B.PMSTAT)
#endif
//@}

//-------------------------------------------------------------------------------------------
// hw_smc_t - module struct
//-------------------------------------------------------------------------------------------
/*!
 * @brief All SMC module registers.
 */
#ifndef __LANGUAGE_ASM__
#pragma pack(1)
typedef struct _hw_smc
{
    __IO hw_smc_pmprot_t PMPROT;           //!< [0x0] Power Mode Protection register
    __IO hw_smc_pmctrl_t PMCTRL;           //!< [0x1] Power Mode Control register
    __IO hw_smc_vllsctrl_t VLLSCTRL;       //!< [0x2] VLLS Control register
    __I hw_smc_pmstat_t PMSTAT;            //!< [0x3] Power Mode Status register
} hw_smc_t;
#pragma pack()

//! @brief Macro to access all SMC registers.
//! @return Reference (not a pointer) to the registers struct. To get a pointer to the struct,
//!     use the '&' operator, like <code>&HW_SMC</code>.
#define HW_SMC         (*(hw_smc_t *) REGS_SMC_BASE)
#endif

#endif // __HW_SMC_REGISTERS_H__
// v22/130726/0.9
// EOF
