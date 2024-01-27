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
// turn on LED 1
#define LED1_inv_clear GpioDataRegs.GPBCLEAR.bit.GPIO48 = 1;
// LED 1 off
#define LED1_inv_set GpioDataRegs.GPBSET.bit.GPIO48 = 1;
// turn LED 2 on
#define LED2_inv_clear GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1;
// LED 2 off
#define LED2_inv_set GpioDataRegs.GPBSET.bit.GPIO49 = 1;
// LED 1 state
#define LED1_inv_status GpioDataRegs.GPBDAT.bit.GPIO48
// LED 2 status
#define LED2_inv_status GpioDataRegs.GPBDAT.bit.GPIO49
// turn on LED 1
#define OK_S_ON GpioDataRegs.GPCCLEAR.bit.GPIO66 = 1;
// LED 1 off
#define OK_S_OFF GpioDataRegs.GPCSET.bit.GPIO66 = 1;
// turning LED 2 on
#define ERR_S_ON GpioDataRegs.GPCCLEAR.bit.GPIO67 = 1;
// LED 2 off
#define ERR_S_OFF GpioDataRegs.GPCSET.bit.GPIO67 = 1;
// state of pressing the "up" button of the remote control
#define UP_STATUS GpioDataRegs.GPBDAT.bit.GPIO63
// state of pressing the "down" button of the remote control
#define DOWN_STATUS GpioDataRegs.GPBDAT.bit.GPIO62
// state of pressing the "left" button of the remote control
#define LEFT_STATUS GpioDataRegs.GPBDAT.bit.GPIO61
// state of pressing the "right" button of the remote control
#define RIGHT_STATUS GpioDataRegs.GPBDAT.bit.GPIO60
// state of pressing the "select" button of the remote control
#define SEL_STATUS GpioDataRegs.GPBDAT.bit.GPIO59
// state of pressing the external "start" button
#define EXT_START GpioDataRegs.GPBDAT.bit.GPIO53
// state of pressing the external "stop" button
#define EXT_STOP GpioDataRegs.GPBDAT.bit.GPIO52
// maximum number of inputs to the button filter
#define N_CNT_FLTR_MAX 32000
// minimum number of inputs to the button filter
#define N_CNT_FLTR_MIN 1000
// format: DIV_divider; named constant equal to 1/6
#define DIV_1_6 0.1666666666666667
// TRUE value for compilation
#define TRUE_VAL 1
// FALSE value for compilation
#define FALSE_VAL 0



//////////////// DECLARATION OF EXTERNAL ACCESS TO FUNCTIONS /////////////////////
// declaration of external access to the TimeDelay function
extern void TimeDelaySys(float32 time_in_sec_l);
// declaration of external access to the Init_GPIO_0_5_in_PWM function
extern void Init_GPIO_0_5_in_PWM(void);
// declaration of external access to the HandlrBttn function
extern Uint16 HandlrBttn(Uint16 push_l);
// declaration of external access to the LimitVar function
extern void LimitVar(float32 min_var, float32 max_var, float32 *var_lim);
// declaration of external access to the function FltrMas6Var
extern float32 FltrMas6Var(float32 cur_var, Uint16 *cur_mas, float32 *pmas_var);
// declaration of external access to the cpu_timer0_isr interrupt
extern interrupt void cpu_timer0_isr(void);

/////////////////////// DECLARATION OF DATA STRUCTURES //////////////////////////
// data structure of a 32-bit number
typedef union
{
 float32 fl;
 Uint32 uint;
} B32_Numb_S;
#endif
