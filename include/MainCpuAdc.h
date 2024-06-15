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
// Include header file "BaseDriveUsr.h"
#include "BaseDrive.h"

//////////////// FUNCTION EXTERNAL ACCESS DECLARATION /////////////////////
// declaration of external access to the AdcInitDrive function
extern void AdcInitDrive(void);
// declaration of external access to the HandlrADC function
extern void HandlrAdc(Model_Data_PMSM_S *md_motor_l,
                      Settng_Data_PMSM_S *sd_motor_l);
//! declaration of external access to the HandlrFastAdc
void HandlrFastAdc(Model_Data_PMSM_S *md_motor_l);

#endif
