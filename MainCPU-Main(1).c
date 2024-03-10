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

////! FUNCTION DECLARATION
////! function declaration interrupt CPU_TIMER0_ISR
//interrupt void CPU_TIMER0_ISR(void);
////! function declaration interrupt XINT1_ISR
//interrupt void XINT1_ISR(void);
//! Base_Cycle
void Base_Cycle(void);

/*!
    \brief: Main
 */
void main(void) {
    //! program initialization before entering the execution loop
    MainInit();
    //! light up the LED with the value "net"
    LED_NET_ON;
	//! entering the main program cycle
	for(;;) {
		//! entering the cycle of operations execution in the external background
		Base_Cycle();
	}
}

/*!
    \brief: Main program cycle
 */
void Base_Cycle(void) {
    //! configuration variable calculation
	CalcVarblsSttng(&data_pmsm);
    //! receiving data from external control signals
	HandlerExternalButtons(&flags_drive);
}

/*!
    \brief: Interrupt from the CPU0 timer (enters the cycle when an interrupt is triggered)
 */
interrupt void TINT0_ISR(void) {
	//! First step
    //! extraction of ADC currents and external speed reference values
	HandlrADC(&data_pmsm.md, &data_pmsm.sd);

	//! Second step
	//! computing fast variables
	CalcFastVarblsSttng(&data_pmsm);

	//! frequency converter control
	CntrlDrive(&data_pmsm.md, &data_pmsm.sd, &flags_drive, &brwsr);

	//! conversion of phase ePwm from relative view to processor PWM view
	Handlr_ePwm(brwsr.pbrws, PWM_OUT_PHASE_DIV_2, &data_pmsm.md);

	//! handler freeze protection
	HandlerFreezeProtection();

	//! TODO for Debug
	//CalculateConditionPMS(&data_pmsm.md);
    PieCtrlRegs.PIEACK.bit.ACK7 = PIEACK_GROUP7;
}

/*!
    \brief: Interrupt from the GPIO62
 */
interrupt void XINT3_ISR(void) {
    // acknowledge this interrupt to get more from group 1
    PieCtrlRegs.PIEACK.bit.ACK12 = PIEACK_GROUP12;
}
