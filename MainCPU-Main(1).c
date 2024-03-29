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
	//! reset error drive
	if (flags_drive.bits_reg2.bits.err_drv) {
	    LED_ERROR_ON;
	    LED_NET_OFF;
	    PMSMotorFuncReset(&data_pmsm.md, &data_pmsm.sd, &flags_drive);
	    if (flags_drive.bits_reg2.bits.reset_drv) {
	        flags_drive.bits_reg2.bits.err_drv = FALSE_VAL;
	        LED_ERROR_OFF;
	        LED_NET_ON;
	    }
	} else {
	    flags_drive.bits_reg2.bits.err_drv = !(GpioDataRegs.GPADAT.bit.GPIO12 && GpioDataRegs.GPADAT.bit.GPIO13 &&
	                                         GpioDataRegs.GPADAT.bit.GPIO14 && GpioDataRegs.GPADAT.bit.GPIO15 &&
	                                         GpioDataRegs.GPADAT.bit.GPIO16 && GpioDataRegs.GPADAT.bit.GPIO17);
	}
}

/*!
    \brief: Interrupt from the CPU0 timer (enters the cycle when an interrupt is triggered)
 */
interrupt void TINT0_ISR(void) {
    static Uint16 current_count = 0;
	//! First step
    //! extraction of ADC currents and external speed reference values
	HandlrADC(&data_pmsm.md, &data_pmsm.sd);

	//! Second step
	//! computing fast variables
	CalcFastVarblsSttng(&data_pmsm);
	//! if there is an error, the operation stops.
	if (!flags_drive.bits_reg2.bits.err_drv) {
	    //! increment for current count
	    current_count++;
	    //! get condition for switch
	    if (HandlerSwitchProcessing(current_count, VAL_MAX_LED_NET))  {
	        //! on led net
	        LED_NET_ON;
	    } else {
	        //! off led net
	        LED_NET_OFF;
	        //! if bigger max value then reset current_count
	        if (current_count > VAL_MAX_LED_NET) {
	            //! reset current_count
	            current_count = 0;
	        }
	    }
	    //! frequency converter control
	    CntrlDrive(&data_pmsm.md, &data_pmsm.sd, &flags_drive, &brwsr);
	}
	//! conversion of phase ePwm from relative view to processor PWM view
	Handlr_ePwm(&flags_drive, PWM_OUT_PHASE_DIV_2, &data_pmsm.md);

	//! handler freeze protection
	HandlerFreezeProtection();

    PieCtrlRegs.PIEACK.bit.ACK7 = PIEACK_GROUP7;
}

/*!
    \brief: Interrupt from the GPIO62
 */
interrupt void XINT3_ISR(void) {
    //! set next value angle rotor
    flags_drive.bits_reg1.bits.ext_angle=TRUE_VAL;
    //! acknowledge this interrupt to get more from group 1
    PieCtrlRegs.PIEACK.bit.ACK12 = PIEACK_GROUP12;
}
