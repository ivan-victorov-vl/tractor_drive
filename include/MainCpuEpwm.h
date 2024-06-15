//###########################################################################
//
// FILE:    	MainCpuEpwm.h
//
// DESCRIPTION: Header file MainCpuEpwm.ñ
//
//###########################################################################

#ifndef MAINCPUEPWM_H
#define MAINCPUEPWM_H

//////////////// DECLARATION OF EXTERNAL ACCESS TO FUNCTIONS /////////////////////
//! declaration of external access to a function InitEPwm_1_2_3_4_5_6_Timers
extern void InitEPwm_1_2_3_4_5_6_Timers(Uint16 prd_epwm_1_2_3_4_5_6);
//! declaration of external access to a function Handlr_ePwm
extern void Handlr_ePwm(Flg_Cntrl_Drive_S *mf_l, Uint16 prd_div_2_epwm_u_v_w_l,
                        Model_Data_PMSM_S *md_motor_l);
//! declaration of external access to a function  Set_Pwm_Complimentary_State
extern void Set_Pwm_Complimentary_State();
//! declaration of external access to a function  Set_Pwm_Low_State
extern void Set_Pwm_Low_State();

#endif
