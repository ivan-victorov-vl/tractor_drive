//###########################################################################
//
// FILE:    Menu.c
//
// TITLE:   Base Drive support functions.
//
// NOTES:
//
//###########################################################################

#ifndef MENUMODBUS_H_
#define MENUMODBUS_H_


////////////////////// ����������� ������������ ������ //////////////////////
// // ����������� ������������� ����� "FlagParamDrive.h"
#include "FlagParamDrive.h"



//////////////// ���������� �������� ������� � �������� /////////////////////
// ���������� �������� ������� � ������� pExtrctModbusVal
extern void ExtrctModbusVal(Rpd_Ctrl_Regs_S *rpd_ctrl_regs_l, Flg_Cntrl_Drive_S *flag_ctrl_regs_l, Data_PMSM_S *md_motor_l, Brws_Param_Drive *bpd_l);
// ���������� �������� ������� � ������� pPushIndctnCntrl
extern void PushIndctnCntrlMB(Rpd_Ctrl_Regs_S *rpd_ctrl_regs_l, Flg_Cntrl_Drive_S *flag_ctrl_regs_l);
// ���������� �������� ������� � ������� ExtrctModbusValInit
extern void ExtrctModbusValInit(Rpd_Ctrl_Regs_S *rpd_ctrl_regs_l, Flg_Cntrl_Drive_S *flag_ctrl_regs_l, Data_PMSM_S *md_motor_l);


#endif
