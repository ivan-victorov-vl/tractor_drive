//###########################################################################
//
// File:    	MainCpuEpwm.c
//
// Title:   	PWM setting parameters function
//
//###########################################################################


#include "PeripheralHeaderIncludes.h"


/////////////////////////// FUNCTION DECLARATION //////////////////////////////
// function declaration InitEPwm_1_2_3_4_6_Timers
void InitEPwm_1_2_3_4_6_Timers(Uint16 prd_epwm_1_2_3, Uint16 prd_epwm_4, Uint16 prd_epwm_6);
// Handlr_ePwm function declaration
void  Handlr_ePwm(float32 *pbrws_var_l, Uint16 prd_div_2_epwm_dac_l, Uint16 prd_div_2_epwm_u_v_w_l, Model_Data_PMSM_S *md_motor_l);


void InitEPwm_1_2_3_4_6_Timers(Uint16 prd_epwm_1_2_3, Uint16 prd_epwm_4, Uint16 prd_epwm_6)
{
	//! allow changes to forbidden registers
	EALLOW;
	//! reset the EWPM clocking of the TBCLK module
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	//! not modify forbidden registers
	EDIS;

	//! supplying the clock frequency to the PWM modules:
	//! allow changes to forbidden registers
	EALLOW;
	//! EPWM1 clocking resolution
	SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;
	//! EPWM2 clocking resolution
	SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;
	//! EPWM3 clocking resolution
	SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 1;
	//! EPWM4 clocking resolution
	SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = 1;
	//! EPWM5 clocking resolution
	SysCtrlRegs.PCLKCR1.bit.EPWM5ENCLK = 1;
	//! EPWM6 clocking resolution
	SysCtrlRegs.PCLKCR1.bit.EPWM6ENCLK = 1;
	//!  not modify forbidden registers
	EDIS;


	//! configuring the epwm1 module:
	//! PWM period selection
	EPwm1Regs.TBPRD = prd_epwm_1_2_3;
	//! PWM register phase shift selection
	EPwm1Regs.TBPHS.half.TBPHS = 0;
	//! select symmetrical mode
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	//! phase out
	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	//! loading the active register from the shadow register
	EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	//! base counter when 0 is reached
	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
	//! shadow channel mode a
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	//! shadow mode of channel b
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	//! set CTR mode = 0 channel a
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	//! set CTR mode = 0 channel b
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	//! set incrementing (signal reset) to a low voltage state
	EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	//! set incrementing (signal reset) to high voltage state
	EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
	//! output both complementary signals
	EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	//! the active level is the lower state
	EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_LOC;
	//! select delay on edge transition to low signal level
	EPwm1Regs.DBFED = 50;
	//! select delay on edge transition to high signal level
	EPwm1Regs.DBRED = 50;
	//! set the effective value to low signal level
	EPwm1Regs.CMPA.half.CMPA = 0;

	//! PWM period selection
	EPwm2Regs.TBPRD = prd_epwm_1_2_3;
	//! PWM register phase shift selection
	EPwm2Regs.TBPHS.half.TBPHS = 0;
	//! select symmetrical mode
	EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	//! phase loading
	EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;
	//! loading the active register from the shad
	EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	//! epwm synchronization
	EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	//! shadow mode of channel a
	EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	//! shadow mode of channel b
	EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	//! set CTR mode = 0 channel a
	EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	//! set CTR mode = 0 channel b
	EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	//! set incrementing (signal reset) to a low voltage state
	EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	//! set incrementing (signal reset) to high voltage stat
	EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;
	//! output both complementary signals
	EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	//! the active level is the lower state
	EPwm2Regs.DBCTL.bit.POLSEL =  DB_ACTV_LOC;
	//! select the delay on the transition to the lower edge
	EPwm2Regs.DBFED = 50;
	//! select delay on edge transition to high signal level
	EPwm2Regs.DBRED = 50;
	//! set the effective value to low signal level
	EPwm2Regs.CMPA.half.CMPA = 0;


	//! PWM period selection
	EPwm3Regs.TBPRD = prd_epwm_1_2_3;
	//! PWM register phase shift selection
	EPwm3Regs.TBPHS.half.TBPHS = 0;
	//! select symmetrical mode
	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	//! phase loading
	EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;
	//! loading the active register from the shadow register
	EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	//! epwm synchronization
	EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	//! shadow mode of channel a
	EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	//! shadow mode of channel b
	EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	//! set CTR mode = 0 channel a
	EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	//! set CTR mode = 0 channel b
	EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	//! set incrementing (signal reset) to a low voltage state
	EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	//! set incrementing (signal reset) to high voltage state
	EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;
	//! output both complementary signals
	EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	//! the active level is the lower state
	EPwm3Regs.DBCTL.bit.POLSEL =  DB_ACTV_LOC;
	//! select delay on edge transition to high signal level
	EPwm3Regs.DBFED = 50;
	//! set the effective value to low signal level
	EPwm3Regs.DBRED = 50;
	//! set the effective value to low signal level
	EPwm3Regs.CMPA.half.CMPA = 0;

	//! from inlet to outlet
	EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	//! sync output off
	EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;

	//! turn on phase tracking. register epwm 4
	EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE;
	//! turn on phase tracking. register epwm 5
	EPwm5Regs.TBCTL.bit.PHSEN = TB_ENABLE;
	//! turn on phase tracking. register epwm 6
	EPwm6Regs.TBCTL.bit.PHSEN = TB_ENABLE;

	//! phase loading in EPWM6;
	//! EPwm4Regs.TBPHS.half.TBPHS = 0;
	//! synchronization epwm 5 by 0
	EPwm5Regs.TBPHS.half.TBPHS = 0;
	//! synchronization epwm 6 by 0
	EPwm6Regs.TBPHS.half.TBPHS = 0;

	//! PWM period selection
	EPwm4Regs.TBPRD = prd_epwm_4;
	//! set the mode when there is no frequency division
	EPwm4Regs.TBCTL.bit.HSPCLKDIV = 0x0;

	EPwm4Regs.DBCTL.bit.OUT_MODE =DBB_ENABLE;
	//! invert the output
	EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_LOC;
	//! counting mode: up - down
	EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	//! loading from shadow register (shadow register)
	EPwm4Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	//! shdow
	EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	//! PRD and Zero comparison update
	EPwm4Regs.CMPCTL.bit.LOADAMODE = 2;
	//! set incrementing (signal reset) to high voltage state
	EPwm4Regs.AQCTLA.bit.CAU = AQ_SET;
	//! set incrementing (signal reset) to a low voltage state
	EPwm4Regs.AQCTLA.bit.CAD = AQ_CLEAR;
	//! clear the flag
	EPwm6Regs.ETCLR.bit.INT = 1;
	//! load period
	EPwm6Regs.TBPRD = prd_epwm_6;
	//! select saw mode
	EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
	//! enable interrupt on transition to 0
	EPwm6Regs.ETSEL.bit.INTSEL 	= ET_CTR_ZERO;
	//! interrupt
	EPwm6Regs.ETSEL.bit.INTEN 	= 1;
	//! generate an interrupt on the first event
	EPwm6Regs.ETPS.bit.INTPRD	= 1;

	//! allow changes to forbidden register
	EALLOW;
	// establish the onset of synchronization
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	//! prohibit changing prohibited registers
	EDIS;
}


/*!
 *  \brief PWM value processing
 */
void Handlr_ePwm(float32 *pbrws_var_l, Uint16 prd_div_2_epwm_dac_l, Uint16 prd_div_2_epwm_u_v_w_l, Model_Data_PMSM_S *md_motor_l)
{
	//! set the pwm value for the phase u
	EPwm1Regs.CMPA.half.CMPA = (Uint16)(( (md_motor_l->uu.fl) * (prd_div_2_epwm_u_v_w_l) ) + prd_div_2_epwm_u_v_w_l);
	//! set the pwm'a value for phase v
	EPwm2Regs.CMPA.half.CMPA = (Uint16)(( (md_motor_l->uv.fl) * (prd_div_2_epwm_u_v_w_l) ) + prd_div_2_epwm_u_v_w_l);
	//! set the pwm value for phase w
	EPwm3Regs.CMPA.half.CMPA = (Uint16)(( (md_motor_l->uw.fl) * (prd_div_2_epwm_u_v_w_l) ) + prd_div_2_epwm_u_v_w_l);
	//! set the pwm value on the dac
	EPwm4Regs.CMPA.half.CMPA = (Uint16)((*pbrws_var_l * (prd_div_2_epwm_dac_l) ) + prd_div_2_epwm_dac_l);
}
