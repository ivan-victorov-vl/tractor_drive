//###########################################################################
//
// FILE: MainCPU-Main.h
//
// TITLE: Header file: MainCPU-Main.c
//
//###########################################################################

#ifndef MAINCPU_MAIN_DEFS_H
#define MAINCPU_MAIN_DEFS_H

////////////////////// HEADER FILE CONNECTION //////////////////////
// include header file "BaseDriveUsr.h"
#include "BaseDrive.h"
//! include header file "RegParamDrive.h"
#include "FlagParamDrive.h"

////////////////////// DECLARATION OF NAMED CONSTANTS //////////////////////
//! power-on delay time in seconds
#define TIME_DELAY_IN_SEC 0.00001
//! disable AD2S90 chip
#define CS_AD2S90_OFF GpioDataRegs.GPASET.bit.GPIO19 = 1
//! connect AD2S90 chip
#define CS_AD2S90_ON GpioDataRegs.GPACLEAR.bit.GPIO19 = 1
//! switch RS485A chip to transmit state
#define DE_RS485A_ON GpioDataRegs.GPASET.bit.GPIO27 = 1;
//! switch RS485A chip to receive state
#define DE_RS485A_OFF GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;
//! switch RS485B chip to transmit state
#define DE_RS485B_ON GpioDataRegs.GPASET.bit.GPIO21 = 1;
//! switch RS485B chip to the receive state
#define DE_RS485B_OFF GpioDataRegs.GPACLEAR.bit.GPIO21 = 1;
//! timer PWM interrupt base cycle period
#define PERD_BASE_CYCLE (5515 * 1.5)
//! period of the user PWM for the variable viewer
#define PWM_USR 250
//! user PWM period for the variable viewer divided by 2
#define PWM_USR_DIV_2 PWM_USR / 2
//! phase PWM period
#define PWM_OUT_PHASE 7500
//! phase PWM period divided by 2
#define PWM_OUT_PHASE_DIV_2 PWM_OUT_PHASE / 2
//! modbus parcel delay, for transmission between parcels
#define TIMECNT_DELAY_MB 70000
//! format: DIV_divider; named constant equal to 1/4096
#define K_1_DIV_4096 0.000244140625

//////////////// DECLARATION OF EXTERNAL ACCESS TO VARIABLES //////////////////
//! frequency converter flags memory
extern Flg_Cntrl_Drive_S flags_drive;
//! frequency inverter parameter memory (model memory)
extern Data_PMSM_S data_pmsm;
//! pointer to modbus memory
extern Uint16 *pMBmemory;
//! parameter lookup declaration
extern Brws_Param_Drive brwsr;

//////////////// DECLARATION OF EXTERNAL ACCESS TO FUNCTIONS ////////////////////
//! timer interrupt by PWM interrupt epwm6_timer_isr
extern interrupt void epwm6_timer_isr(void);

#endif
