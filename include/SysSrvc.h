//###########################################################################
//
// FILE:    SysSrvc.h
//
// TITLE:   System service defenitions.
//
// NOTES:
//
//###########################################################################

#ifndef SYSSRVC_H_
#define SYSSRVC_H_


////////////////////// DECLARATION OF NAMED CONSTANTS //////////////////////
// processor frequency in Hz
#define FRQ_HZ_PRCSR	150000000
//! maximum number of inputs to the button filter
#define N_CNT_FLTR_MAX 32000
//! minimum number of inputs to the button filter
#define N_CNT_FLTR_MIN 1000
//! format: DIV_divider; named constant equal to 1/6
#define DIV_1_6 0.1666666666666667
//! format: DIV_divider; named constant equal to 1/4096
#define DIV_1_4096 0.000244140625
//! TRUE value for compilation
#define TRUE_VAL 1
//! FALSE value for compilation
#define FALSE_VAL 0
//! define led net on
#define LED_NET_ON GpioDataRegs.GPBCLEAR.bit.GPIO47 = 1
//! define led START on
#define LED_START_ON GpioDataRegs.GPCCLEAR.bit.GPIO80 = 1
//! define led START off
#define LED_START_OFF GpioDataRegs.GPCSET.bit.GPIO80 = 1
//! define led STOP on
#define LED_STOP_ON GpioDataRegs.GPCCLEAR.bit.GPIO81 = 1
//! define led STOP off
#define LED_STOP_OFF GpioDataRegs.GPCSET.bit.GPIO81 = 1
//! define led STOP on
#define LED_ERROR_ON GpioDataRegs.GPCCLEAR.bit.GPIO82 = 1
//! define led ERROR off
#define LED_ERROR_OFF GpioDataRegs.GPCSET.bit.GPIO82 = 1
//! define D_in_2 "START" button
#define GET_DIN_2_START_BUTTON GpioDataRegs.GPCDAT.bit.GPIO74
//! define D_in_3 "STOP" button
#define GET_DIN_3_STOP_BUTTON GpioDataRegs.GPCDAT.bit.GPIO73
//! define D_in_4 "RESET" button
#define GET_DIN_4_RESET_BUTTON GpioDataRegs.GPCDAT.bit.GPIO72


//////////////// DECLARATION OF EXTERNAL ACCESS TO FUNCTIONS /////////////////////
//! declaration of external access to the TimeDelay function
extern void TimeDelaySys(float32 time_in_sec_l);
//! declaration of external access to the Init_GPIO_0_5_in_PWM function
extern void Init_GPIO_0_5_in_PWM(void);
//! declaration of external access to the HandlrBttn function
extern Uint16 HandlrBttn(Uint16 push_l);
//! declaration of external access to the LimitVar function
extern void LimitVar(float32 min_var, float32 max_var, float32 *var_lim);
//! declaration of external access to the function FltrMas6Var
extern float32 FltrMas6Var(float32 cur_var, Uint16 *cur_mas, float32 *pmas_var);
//! declaration of external access to the cpu_timer0_isr interrupt
extern interrupt void cpu_timer0_isr(void);

/////////////////////// DECLARATION OF DATA STRUCTURES //////////////////////////
//! data structure of a 32-bit number
typedef union {
 float32 fl;
 Uint32 uint;
} B32_Numb_S;
#endif
