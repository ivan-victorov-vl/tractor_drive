//###########################################################################
//
// ����:    	MainCpuEpwm.h
//
// ��������:   	Header ����� MainCpuEpwm.�
//
//###########################################################################


#ifndef MAINCPUEPWM_H
#define MAINCPUEPWM_H


////////////////////// ����������� ������������ ������ //////////////////////
// // ����������� ������������� ����� "BaseDriveUsr.h"
#include "BaseDriveUsr.h"


//////////////// ���������� �������� ������� � �������� /////////////////////
// ���������� �������� ������� � ������� InitEPwm_1_2_3_4_6_Timers
extern void InitEPwm_1_2_3_4_6_Timers(Uint16 prd_epwm_1_2_3, Uint16 prd_epwm_4, Uint16 prd_epwm_6);
// ���������� �������� ������� � ������� Handlr_ePwm
extern void  Handlr_ePwm(float32 *pbrws_var_l, Uint16 prd_div_2_epwm_dac_l, Uint16 prd_div_2_epwm_u_v_w_l, Model_Data_PMSM_S *md_motor_l);


#endif
