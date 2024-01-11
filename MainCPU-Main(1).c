//###########################################################################
//
// File:    	    MainCpu-Main(1).c
//
// Description:   	Main program execution file
//
//###########################################################################

//! HEADER FILE CONNECTION
//! include header file "PeripheralHeaderIncludes.h"
#include "PeripheralHeaderIncludes.h"
//! include header file "MainCPU-Main.h"
#include "MainCPU-Main.h"
//! include header file "ProtectnDrive.h"
#include "ProtectnDrive.h"
//! include header file "BaseDrive.h"
#include "BaseDrive.h"
//!	include header file "SysSrvc.h"
#include "SysSrvc.h"


//! FUNCTION DECLARATION
//! function declaration interrupt epwm6_timer_isr
interrupt void epwm6_timer_isr(void);
//! Base_Cycle
void Base_Cycle(void);

/*!
    \brief: Main
 */
void main(void)
{
    //! program initialization before entering the execution loop
	MainInit();
	//! entering the main program cycle
	for(;;)
	{
		//! entering the cycle of operations execution in the external background
		Base_Cycle();
	}
}

/*!
    \brief: Main program cycle
 */
void Base_Cycle(void)
{
    //! configuration variable calculation
	CalcVarblsSttng(&data_pmsm);
}

/*!
    \brief: Interrupt from the ePWM6 timer (enters the cycle when an interrupt is triggered)
 */
interrupt void epwm6_timer_isr(void)
{
	//! First step
    //! extraction of ADC currents and external speed reference values
	HandlrADC(&data_pmsm.md, &data_pmsm.sd);

	//! Second step
	//! computing fast variables
	CalcFastVarblsSttng(&data_pmsm);

	//! frequency converter control
	CntrlDrive(&data_pmsm.md, &data_pmsm.sd, &flags_drive, &brwsr);

	//! conversion of phase ePwm from relative view to processor PWM view
	Handlr_ePwm(brwsr.pbrws, PWM_USR_DIV_2, PWM_OUT_PHASE_DIV_2, &data_pmsm.md);

	CalculateConditionPMS(&data_pmsm.md);
	//! clear ePWM 6 interrupt flag
	EPwm6Regs.ETCLR.bit.INT = 1;
	//! group 3 interrupt reset
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}
