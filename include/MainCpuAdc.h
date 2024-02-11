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


////////////////////// DECLARATION OF NAMED CONSTANTS //////////////////////
// format: DIV_divider; named constant equals 1/1700
#define DIV_1_1700 0.0005882352941176471
// format: DIV_divider; named constant equals 1/4095
#define DIV_1_4096 0.000244140625
// current shift iu to extract zero value
#define SHIFT_IU 1722
// current shift iv to extract zero value
#define SHIFT_IV 1725


//////////////// FUNCTION EXTERNAL ACCESS DECLARATION /////////////////////
// declaration of external access to the AdcInitDrive function
extern void AdcInitDrive(void);
// declaration of external access to the HandlrADC function
extern void HandlrADC(Model_Data_PMSM_S *md_motor_l, Settng_Data_PMSM_S *sd_motor_l);


#endif
