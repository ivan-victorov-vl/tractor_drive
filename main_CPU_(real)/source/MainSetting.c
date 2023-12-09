//###########################################################################
//
// FILE:   MainSetting.c
//
// TITLE: The main settings file of the frequency inverter.
//
//###########################################################################

#include "PeripheralHeaderIncludes.h"
#include "MainSetting.h"

void CalcVarblsSttng(Data_PMSM_S *md_motor_l);
void CalcFastVarblsSttng(Data_PMSM_S *md_motor_l);



void CalcVarblsSttng(Data_PMSM_S *md_motor_l) {
}


void CalcFastVarblsSttng(Data_PMSM_S *md_motor_l) {
	md_motor_l->md.cur_pstn_rtr.fl = md_motor_l->sd.diskr_cur_pstn_rtr * K_REAL_CUR_PSTN;
}
