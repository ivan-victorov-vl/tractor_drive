//###########################################################################
//
// File: MainSetting.h
//
// Description: MainSetting.c header file
//
//###########################################################################

#ifndef MAINSETTING_H_
#define MAINSETTING_H_

////////////////////// DECLARATION OF NAMED CONSTANTS //////////////////////
// constant value conversion coefficient from 12 bit value
#define K_REAL_CUR_PSTN 0.087890625
// processor time cycle
#define TIME_CYCLE_CPU 0.00011

//////////////// DECLARATION OF EXTERNAL ACCESS TO FUNCTIONS /////////////////////
// declaration of external access to function CalcVarblsSttng
extern void CalcVarblsSttng(Data_PMSM_S *md_motor_l);
// declaration of the CalcFastVarblsSttng function
extern void CalcFastVarblsSttng(Data_PMSM_S *md_motor_l);

#endif
