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
	//! setting the cpu_timer_0 interrupt
	PieVectTable.TINT0 = &cpu_timer0_isr;
	//! unmodify forbidden registers
	EDIS;

	//! SPIA initialization
	InitSPIA();

	//! processor delay for a specified time
	TimeDelaySys(TIME_DELAY_IN_SEC);

	//! to start communication with the chip, set 0 value for transmission
	SpiaRegs.SPITXBUF = 0;
	//! Set configuration for cpu_timer_0
	ConfigCpuTimer(&CpuTimer0, 150, 10000);
	//! setting of modules ePWM 1 to ePWM 3 for output PWM to motor,
	//! ePWM to set the basic cycle
	InitEPwm_1_2_3_4_5_6_Timers(PWM_OUT_PHASE);

	//! ADC initialization
	AdcInitDrive();

	//! CPU interrupt resolution
	 CpuTimer0Regs.TCR.all = 0x4000;
	//! set interrupt M_INT1
	IER |= M_INT1;
	//! CPU_TIMER_0
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

	//! global interrupt resolution and real-time debugging of high-priority interrupts:
	//! resolution of global INTM interrupts
	EINT;
	//! resolution of global interrupts in real time DBGM
	ERTM;

	//! initialization to view current parameters
	brwsr.pbrws =  &brwsr.pstn_rtr_md;

	//! initialization of permanent magnet synchronous motor model
	PMSMotorFuncInit(&data_pmsm.md, &data_pmsm.sd, &flags_drive);

	//! set pins 0...5 to PWM mode
	Init_GPIO_0_5_in_PWM();

	//! ADC data update
	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;
    AdcRegs.ADCTRL2.bit.SOC_SEQ2 = 1;
}
