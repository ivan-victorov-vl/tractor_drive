//###########################################################################
//
// File:    	MainCpuEpwm.c
//
// Title:   	PWM setting parameters function
//
//###########################################################################

#include "PeripheralHeaderIncludes.h"

/////////////////////////// FUNCTION DECLARATION //////////////////////////////
// Function declaration InitEPwm_1_2_3_4_6_Timers
void InitEPwm_1_2_3_4_5_6_Timers(Uint16 prd_epwm_1_2_3_4_5_6);
// Function declaration Handlr_ePwm
void Handlr_ePwm(Flg_Cntrl_Drive_S *mf_l, Uint16 prd_div_2_epwm_u_v_w_l, Model_Data_PMSM_S *md_motor_l);
// Function declaration Set_Pwm_Complimentary_State
void Set_Pwm_Complimentary_State();
// Function declaration Set_Pwm_Low_State
void Set_Pwm_Low_State();

/*!
     \brief Initialization timer for 1,2,3,4,5,6 ePWM value
 */
void InitEPwm_1_2_3_4_5_6_Timers(Uint16 prd_epwm_1_2_3_4_5_6) {
	//! Allow changes to forbidden registers
	EALLOW;
	//! Reset the EWPM clocking of the TBCLK module
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	//! Not modify forbidden registers
	EDIS;

	//! Supplying the clock frequency to the PWM modules:
	//! Allow changes to forbidden registers
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

	//! Configuring the epwm1 module:
	//! PWM period selection
	EPwm1Regs.TBPRD = prd_epwm_1_2_3_4_5_6;
	//! PWM register phase shift selection
	EPwm1Regs.TBPHS.half.TBPHS = 0;
	//! Select symmetrical mode
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	//! Phase out
	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	//! Loading the active register from the shadow register
	EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	//! Base counter when 0 is reached
	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
	//! Shadow channel mode a
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	//! Shadow mode of channel b
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	//! Set CTR mode = 0 channel a
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	//! Set CTR mode = 0 channel b
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	//! Set incrementing (signal reset) to a high voltage state
	EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;
	//! Set incrementing (signal reset) to low voltage state
	EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;
	//! Output both complementary signals
	EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	//! The active level is the higher complimentary state
	EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
	//! Select delay on edge transition to low signal level
	EPwm1Regs.DBFED = DEAD_BAND;
	//! Select delay on edge transition to high signal level
	EPwm1Regs.DBRED = DEAD_BAND;
	//! Set the effective value to low signal level
	EPwm1Regs.CMPA.half.CMPA = 0;

	//! PWM period selection
	EPwm2Regs.TBPRD = prd_epwm_1_2_3_4_5_6;
	//! PWM register phase shift selection
	EPwm2Regs.TBPHS.half.TBPHS = 0;
	//! Select symmetrical mode
	EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	//! Phase loading
	EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;
	//! Loading the active register from the shad
	EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	//! EPWM synchronization
	EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	//! Shadow mode of channel a
	EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	//! Shadow mode of channel b
	EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	//! Set CTR mode = 0 channel a
	EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	//! Set CTR mode = 0 channel b
	EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	//! Set incrementing (signal reset) to a high voltage state
	EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;
	//! Set incrementing (signal reset) to low voltage state
	EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;
	//! Output both complementary signals
	EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	//! The active level is the higher complimentary state
	EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
	//! Select the delay on the transition to the lower edge
	EPwm2Regs.DBFED = DEAD_BAND;
	//! Select delay on edge transition to high signal level
	EPwm2Regs.DBRED = DEAD_BAND;
	//! set the effective value to low signal level
	EPwm2Regs.CMPA.half.CMPA = 0;

    //! PWM period selection
    EPwm3Regs.TBPRD = prd_epwm_1_2_3_4_5_6;
    //! PWM register phase shift selection
    EPwm3Regs.TBPHS.half.TBPHS = 0;
    //! Select symmetrical mode
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    //! Phase loading
    EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    //! Loading the active register from the shadow register
    EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    //! EPWM synchronization
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    //! Shadow mode of channel a
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    //! Shadow mode of channel b
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    //! Set CTR mode = 0 channel a
    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    //! Set CTR mode = 0 channel b
    EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    //! Set incrementing (signal reset) to a high voltage state
    EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;
    //! Set incrementing (signal reset) to low voltage state
    EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    //! Output both complementary signals
    EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    //! The active level is the higher complimentary state
    EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    //! Select delay on edge transition to high signal level
    EPwm3Regs.DBFED = DEAD_BAND;
    //! Set the effective value to low signal level
    EPwm3Regs.DBRED = DEAD_BAND;
    //! Set the effective value to low signal level
    EPwm3Regs.CMPA.half.CMPA = 0;

    //! PWM period selection
    EPwm4Regs.TBPRD = prd_epwm_1_2_3_4_5_6;
    //! PWM register phase shift selection
    EPwm4Regs.TBPHS.half.TBPHS = 0;
    //! Select symmetrical mode
    EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    //! Phase loading
    EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    //! Loading the active register from the shadow register
    EPwm4Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    //! EPWM synchronization
    EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    //! Shadow mode of channel a
    EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    //! Shadow mode of channel b
    EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    //! Set CTR mode = 0 channel a
    EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    //! Set CTR mode = 0 channel b
    EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    //! Set incrementing (signal reset) to a high voltage state
    EPwm4Regs.AQCTLA.bit.CAU = AQ_SET;
    //! Set incrementing (signal reset) to low voltage state
    EPwm4Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    //! Output both complementary signals
    EPwm4Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    //! The active level is the higher complimentary state
    EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    //! Select delay on edge transition to high signal level
    EPwm4Regs.DBFED = DEAD_BAND;
    //! Set the effective value to low signal level
    EPwm4Regs.DBRED = DEAD_BAND;
    //! Set the effective value to low signal level
    EPwm4Regs.CMPA.half.CMPA = 0;

    //! PWM period selection
    EPwm5Regs.TBPRD = prd_epwm_1_2_3_4_5_6;
    //! PWM register phase shift selection
    EPwm5Regs.TBPHS.half.TBPHS = 0;
    //! Select symmetrical mode
    EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    //! Phase loading
    EPwm5Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    //! Loading the active register from the shadow register
    EPwm5Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    //! EPWM synchronization
    EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    //! Shadow mode of channel a
    EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    //! Shadow mode of channel b
    EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    //! Set CTR mode = 0 channel a
    EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    //! Set CTR mode = 0 channel b
    EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    //! Set incrementing (signal reset) to a high voltage state
    EPwm5Regs.AQCTLA.bit.CAU = AQ_SET;
    //! Set incrementing (signal reset) to low voltage state
    EPwm5Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    //! Output both complementary signals
    EPwm5Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    //! The active level is the higher complimentary state
    EPwm5Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    //! Select delay on edge transition to high signal level
    EPwm5Regs.DBFED = DEAD_BAND;
    //! Set the effective value to low signal level
    EPwm5Regs.DBRED = DEAD_BAND;
    //! Set the effective value to low signal level
    EPwm5Regs.CMPA.half.CMPA = 0;

    //! PWM period selection
    EPwm6Regs.TBPRD = prd_epwm_1_2_3_4_5_6;
    //! PWM register phase shift selection
    EPwm6Regs.TBPHS.half.TBPHS = 0;
    //! Select symmetrical mode
    EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    //! Phase loading
    EPwm6Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    //! Loading the active register from the shadow register
    EPwm6Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    //! EPWM synchronization
    EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    //! Shadow mode of channel a
    EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    //! Shadow mode of channel b
    EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    //! Set CTR mode = 0 channel a
    EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    //! Set CTR mode = 0 channel b
    EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    //! Set incrementing (signal reset) to a high voltage state
    EPwm6Regs.AQCTLA.bit.CAU = AQ_SET;
    //! Set incrementing (signal reset) to low voltage state
    EPwm6Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    //! Output both complementary signals
    EPwm6Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    //! The active level is the higher complimentary state
    EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    //! Select delay on edge transition to high signal level
    EPwm6Regs.DBFED = DEAD_BAND;
    //! Set the effective value to low signal level
    EPwm6Regs.DBRED = DEAD_BAND;
    //! Set the effective value to low signal level
    EPwm6Regs.CMPA.half.CMPA = 0;

	//! Allow changes to forbidden register
	EALLOW;
	// establish the onset of synchronization
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	//! Prohibit changing prohibited registers
	EDIS;
}

/*!
     \brief PWM value processing
 */
void Handlr_ePwm(Flg_Cntrl_Drive_S *mf_l, Uint16 prd_div_2_epwm_u_v_w_l, Model_Data_PMSM_S *md_motor_l) {
    //! Check work drive
    if (mf_l->bits_reg2.bits.wrk_drv) {
        //! Set the PWM value for the phase w
	    EPwm1Regs.CMPA.half.CMPA = (Uint16)(( (md_motor_l->uw.fl * md_motor_l->k_f_mul.fl) * (prd_div_2_epwm_u_v_w_l) ) + prd_div_2_epwm_u_v_w_l);
	    //! Set the PWM'a value for phase v
	    EPwm2Regs.CMPA.half.CMPA = (Uint16)(( (md_motor_l->uv.fl * md_motor_l->k_f_mul.fl) * (prd_div_2_epwm_u_v_w_l) ) + prd_div_2_epwm_u_v_w_l);
	    //! Set the PWM value for phase u
	    EPwm3Regs.CMPA.half.CMPA = (Uint16)(( (md_motor_l->uu.fl * md_motor_l->k_f_mul.fl) * (prd_div_2_epwm_u_v_w_l) ) + prd_div_2_epwm_u_v_w_l);
        //! Set the PWM value for the phase u1
        EPwm4Regs.CMPA.half.CMPA = (Uint16)(( (md_motor_l->uu1.fl * md_motor_l->k_f_mul.fl) * (prd_div_2_epwm_u_v_w_l) ) + prd_div_2_epwm_u_v_w_l);
        //! Set the PWM'a value for phase w1
        EPwm5Regs.CMPA.half.CMPA = (Uint16)(( (md_motor_l->uw1.fl * md_motor_l->k_f_mul.fl) * (prd_div_2_epwm_u_v_w_l) ) + prd_div_2_epwm_u_v_w_l);
        //! Set the PWM value for phase v1
        EPwm6Regs.CMPA.half.CMPA = (Uint16)(( (md_motor_l->uv1.fl * md_motor_l->k_f_mul.fl) * (prd_div_2_epwm_u_v_w_l) ) + prd_div_2_epwm_u_v_w_l);
    } else {
        //! Set PWM low state
        Set_Pwm_Low_State();
        //! Set 0 the PWM value for the phase u
        EPwm1Regs.CMPA.half.CMPA = (Uint16)(0);
        //! Set 0 the PWM'a value for phase v
        EPwm2Regs.CMPA.half.CMPA = (Uint16)(0);
        //! Set 0 the PWM value for phase w
        EPwm3Regs.CMPA.half.CMPA = (Uint16)(0);
        //! Set 0 the PWM value for the phase u1
        EPwm4Regs.CMPA.half.CMPA = (Uint16)(0);
        //! Set 0 the PWM'a value for phase v1
        EPwm5Regs.CMPA.half.CMPA = (Uint16)(0);
        //! Set 0 the PWM value for phase w1
        EPwm6Regs.CMPA.half.CMPA = (Uint16)(0);
    }
}

/*!
     \brief Set complimentary PWM state
 */
void Set_Pwm_Complimentary_State() {
    //! EPwm1 the active level is the higher complimentary state
    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    //! EPwm2 the active level is the higher complimentary state
    EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    //! EPwm3 the active level is the higher complimentary state
    EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    //! EPwm4 the active level is the higher complimentary state
    EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    //! EPwm5 the active level is the higher complimentary state
    EPwm5Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    //! EPwm6 the active level is the higher complimentary state
    EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
}

/*!
     \brief Set low PWM state
 */
void Set_Pwm_Low_State() {
    //! EPwm1 the active level is the low state
    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_LO;
    //! EPwm2 the active level is the low state
    EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_LO;
    //! EPwm3 the active level is the low state
    EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_LO;
    //! EPwm4 the active level is the low state
    EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_LO;
    //! EPwm5 the active level is the low state
    EPwm5Regs.DBCTL.bit.POLSEL = DB_ACTV_LO;
    //! EPwm6 the active level is the low state
    EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_LO;
}
