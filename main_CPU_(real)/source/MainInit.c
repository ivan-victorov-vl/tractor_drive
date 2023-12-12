//###########################################################################
//
// File:    	MainInit.c
//
// Title:   	Basic initialization before entering the execution loop
//
//###########################################################################


#include "PeripheralHeaderIncludes.h"
#include "MainCpuAdc.h"
#include "MainInit.h"


/////////////////////////// FUNCTION DECLARATION //////////////////////////////
//! MainInit function declaration
void MainInit(void);


//////////////// Œ¡⁄ﬂ¬À≈Õ»≈ ¬Õ≈ÿÕ≈√Œ ƒŒ—“”œ¿   ‘”Õ ÷»ﬂÃ /////////////////////
//! function declaration InitSysCtrl
extern void InitSysCtrl(void);
//! function declaration InitPieVectTable
extern void InitPieVectTable(void);
//! function declaration InitFlash
extern void InitFlash();
//! function declaration InitPieCtrl
extern void InitPieCtrl(void);


/*!
 *  \brief Initializing the program before entering the execution loop
 */
void MainInit(void)
{
	//! controller initialization
	InitSysCtrl();

	//! interrupt disable
	DINT;
	//! initialization of PIE control registers
	InitPieCtrl();

	//! interrupt protection
	IER = 0x0000;
	//! flagging
	IFR = 0x0000;
	//! initializing the interrupt table
	InitPieVectTable();

	//! flash initialization
	InitFlash();

	//! configuring interrupt handling functions:
	//! allow changes to forbidden registers
	EALLOW;
	//! setting the pwm6 interrupt
	PieVectTable.EPWM6_INT = &epwm6_timer_isr;
	//! unmodify forbidden registers
	EDIS;

	//! SPIA initialization
	InitSPIA();

	//! processor delay for a specified time
	TimeDelaySys(TIME_DELAY_IN_SEC);

	//! to start communication with the chip, set 0 value for transmission
	SpiaRegs.SPITXBUF = 0;

	//! setting of modules ePWM 1 to ePWM 3 for output PWM to motor,
	//! ePWM 4 custom PWM,
	//! ePWM to set the basic cycle
	InitEPwm_1_2_3_4_6_Timers(PWM_OUT_PHASE, PWM_USR, PERD_BASE_CYCLE);

	//! ADC initialization
	AdcInitDrive();

	//! CPU interrupt resolution
	//! interrupt CPU int3 to connect to ePWM
	IER |= M_INT3;
	//! PWM interrupt enable 6
	PieCtrlRegs.PIEIER3.bit.INTx6 = 1;

	//! global interrupt resolution and real-time debugging of high-priority interrupts:
	//! resolution of global INTM interrupts
	EINT;
	//! resolution of global interrupts in real time DBGM
	ERTM;

	//! initialization to view current parameters
	brwsr.pbrws =  &brwsr.pstn_rtr_md;

	//! initialization of permanent magnet synchronous motor model
	PMSMotorFuncScalInit(&data_pmsm.md, &data_pmsm.sd, &flags_drive);

	//! set pins 0...5 to PWM mode
	Init_GPIO_0_5_in_PWM();

	//! ADC data update
	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;
}
