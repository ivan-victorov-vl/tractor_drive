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


////////////////////// ПОДКЛЮЧЕНИЕ ЗАГОЛОВОЧНЫХ ФАЙЛОВ //////////////////////
// // подключение заголовочного файла "FlagParamDrive.h"
#include "FlagParamDrive.h"



//////////////// ОБЪЯВЛЕНИЕ ВНЕШНЕГО ДОСТУПА К ФУНКЦИЯМ /////////////////////
// объявление внешнего доступа к функции pExtrctModbusVal
extern void ExtrctModbusVal(Rpd_Ctrl_Regs_S *rpd_ctrl_regs_l, Flg_Cntrl_Drive_S *flag_ctrl_regs_l, Data_PMSM_S *md_motor_l, Brws_Param_Drive *bpd_l);
// объявление внешнего доступа к функции pPushIndctnCntrl
extern void PushIndctnCntrlMB(Rpd_Ctrl_Regs_S *rpd_ctrl_regs_l, Flg_Cntrl_Drive_S *flag_ctrl_regs_l);
// объявление внешнего доступа к функции ExtrctModbusValInit
extern void ExtrctModbusValInit(Rpd_Ctrl_Regs_S *rpd_ctrl_regs_l, Flg_Cntrl_Drive_S *flag_ctrl_regs_l, Data_PMSM_S *md_motor_l);


#endif
