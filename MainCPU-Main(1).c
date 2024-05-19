//###########################################################################
//
// File:    	    MainCpu-Main.c
//
// Description:   	Main program execution file
//
//###########################################################################

//! HEADER FILE CONNECTION
//! Include header file "PeripheralHeaderIncludes.h"
#include "PeripheralHeaderIncludes.h"
//! Include header file "MainCPU-Main.h"
#include "MainCPU-Main.h"
//! Include header file "ProtectnDrive.h"
#include "ProtectnDrive.h"
//! Include header file "BaseDrive.h"
#include "BaseDrive.h"
//!	Include header file "SysSrvc.h"
#include "SysSrvc.h"

//! Base_Cycle
void Base_Cycle(void);

/*!
    \brief: Main
 */
void main(void) {
    //! Program initialization before entering the execution loop
    MainInit();
    //! Light up the LED with the value "net"
    LED_NET_ON;
	//! Entering the main program cycle
	for(;;) {
		//! Entering the cycle of operations execution in the external background
		Base_Cycle();
	}
}

/*!
    \brief: Main program cycle
 */
void Base_Cycle(void) {
    //! Configuration variable calculation
	CalcVarblsSttng(&data_pmsm);
    //! Receiving data from external control signals
	HandlerExternalButtons(&flags_drive);
	//! Reset error drive
	if (flags_drive.bits_reg2.bits.err_drv) {
	    //! Turn on led
	    LED_ERROR_ON;
	    //! Reset value of drive
	    PMSMotorFuncReset(&data_pmsm.md, &data_pmsm.sd, &flags_drive);
	    //! If reset
	    if (flags_drive.bits_reg2.bits.reset_drv) {
	        //! Reset err_drv
	        flags_drive.bits_reg2.bits.err_drv = FALSE_VAL;
	        //! Turn off led
	        LED_ERROR_OFF;
	    }
	} else {
#if defined(DEBUG)
	    flags_drive.bits_reg2.bits.err_drv = !(GpioDataRegs.GPADAT.bit.GPIO12 && GpioDataRegs.GPADAT.bit.GPIO13 &&
	                                         GpioDataRegs.GPADAT.bit.GPIO14 && GpioDataRegs.GPADAT.bit.GPIO15 &&
	                                         GpioDataRegs.GPADAT.bit.GPIO16 && GpioDataRegs.GPADAT.bit.GPIO17);
#else
        flags_drive.bits_reg2.bits.err_drv = (GpioDataRegs.GPADAT.bit.GPIO12 || GpioDataRegs.GPADAT.bit.GPIO13 ||
                                              GpioDataRegs.GPADAT.bit.GPIO14 || GpioDataRegs.GPADAT.bit.GPIO15 ||
                                              GpioDataRegs.GPADAT.bit.GPIO16 || GpioDataRegs.GPADAT.bit.GPIO17);
#endif
	}
}

/*!
    \brief: Interrupt from the CPU0 timer (enters the cycle when an interrupt is triggered)
 */
interrupt void TINT0_ISR(void) {
    static Uint16 current_count = 0;

    //! Increment for current count
    current_count++;
    //! Get condition for switch
    if (HandlerSwitchProcessing(current_count, VAL_MAX_LED_NET))  {
        //! On led net
        LED_NET_ON;
    } else {
        //! Off led net
        LED_NET_OFF;
        //! If bigger max value then reset current_count
        if (current_count > VAL_MAX_LED_NET) {
            //! Reset current_count
            current_count = 0;
        }
    }

   //! Check direction motor
   if (flags_drive.bits_reg2.bits.dir_drv) {
       //! If inverse set led direction on
       LED_DIR_ON;
    } else {
        //! If not inverse set led direction off
        LED_DIR_OFF;
    }

    //! First step
    //! Extraction of ADC currents and external speed reference values
	HandlrAdc(&data_pmsm.md, &data_pmsm.sd);

	//! Second step
	//! Computing fast variables
	CalcFastVarblsSttng(&data_pmsm);
	//! If there is an error, the operation stops.
	if (!flags_drive.bits_reg2.bits.err_drv) {
	    //! Frequency converter control
	    CntrlDrive(&data_pmsm.md, &data_pmsm.sd, &flags_drive, &brwsr);
	}
	//! Conversion of phase ePwm from relative view to processor PWM view
	Handlr_ePwm(&flags_drive, PWM_OUT_PHASE_DIV_2, &data_pmsm.md);

	//! Handler freeze protection
	HandlerFreezeProtection();
    //! Acknowledge this interrupt to get more from group 7
    PieCtrlRegs.PIEACK.bit.ACK7 = PIEACK_GROUP7;
}

/*!
    \brief: Interrupt from the CPU2 timer (enters the cycle when an interrupt is triggered)
 */
interrupt void INT14_ISR(void) {
    //! configuring interrupt handling functions:
    //! allow changes to forbidden registers
    EALLOW;
    //! Get voltage and current value
    HandlrFastAdc(&data_pmsm.md);

    #if defined(CURRENT_REF)
    //! declaration local variable integral_ref_current
    static float32 integral_ref_current = 0;

    data_pmsm.md.k_f_mul = I_Regltr(data_pmsm.md.k_f_mul_ref.fl - CalculateScalarCurrentFrom6Phase(&data_pmsm.md),
              K_PROP,
              K_INTEGR,
              &integral_ref_current);
    #endif
    //! unchanging forbidden registers
    EDIS;
}

/*!
    \brief: Interrupt from the GPIO62
 */
interrupt void XINT3_ISR(void) {
    //! Set next value angle rotor
    flags_drive.bits_reg1.bits.ext_angle=TRUE_VAL;
    //! Acknowledge this interrupt to get more from group 12
    PieCtrlRegs.PIEACK.bit.ACK12 = PIEACK_GROUP12;
}
