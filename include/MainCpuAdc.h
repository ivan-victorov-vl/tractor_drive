//###########################################################################
//
// File: MainCpuAdc.h
//
// Description: MainCpuAdc.c header file
//
//###########################################################################

#ifndef MAINCPU_ADC_H_
#define MAINCPU_ADC_H_

////////////////////// HEADER FILE INCLUDE //////////////////////
// include header file "BaseDriveUsr.h"
#include "BaseDrive.h"

//////////////// FUNCTION EXTERNAL ACCESS DECLARATION /////////////////////
// declaration of external access to the AdcInitDrive function
extern void AdcInitDrive(void);
// declaration of external access to the HandlrADC function
extern void HandlrADC(Model_Data_PMSM_S *md_motor_l, Settng_Data_PMSM_S *sd_motor_l);
//! declaration of external access to the HandlrVoltageAdc
extern void HandlrVoltageAdc(Model_Data_PMSM_S *md_motor_l, Settng_Data_PMSM_S *sd_motor_l);
//! declaration of external access to the HandlrCurrentAdc
extern void HandlrCurrentAdc(Model_Data_PMSM_S *md_motor_l, Settng_Data_PMSM_S *sd_motor_l);

#endif
