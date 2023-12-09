//###########################################################################
//
// File:    	MainCpuAdc.c
//
// Description: ADC initialization
//
//###########################################################################


////////////////////// HEADER FILE CONNECTION //////////////////////
//! include of the header file "PeripheralHeaderIncludes.h"
#include "PeripheralHeaderIncludes.h"


//! FUNCTION DECLARATION
//! AdcInitDrive function declaration
void AdcInitDrive (void);
//! function declaration HandlrADC
void HandlrADC(Model_Data_PMSM_S *md_motor_l, Settng_Data_PMSM_S *sd_motor_l);


//! ADC SETTING FUNCTIONS
/*!
 *  \brief: Setting and initialization of the ADC of the frequency converter
 */
void AdcInitDrive(void)
{
	//! zeroing of ADCTRL1 register data
	AdcRegs.ADCTRL1.all = 0;
	//! SOC pulse width control equal to 7 = 8 x ADCCLK
	AdcRegs.ADCTRL1.bit.ACQ_PS = 4;
	//! processing in cascade mode with one 16-level sequencer
	AdcRegs.ADCTRL1.bit.SEQ_CASC =1;
	//! core frequency predilator by 1
	AdcRegs.ADCTRL1.bit.CPS = 0;
	//! START-STOP mode selection.
	//! after conversion enter standby mode, and after the standby is completed
	//!	retransformation start
	AdcRegs.ADCTRL1.bit.CONT_RUN = 0;
	//! zeroing of ADCTRL3 register data
	AdcRegs.ADCTRL3.all = 0x00E0;
	//! frequency division by 2
	AdcRegs.ADCTRL3.bit.ADCCLKPS = 1;
	//! selecting the ADC serial polling mode
	AdcRegs.ADCTRL3.bit.SMODE_SEL = 0;
	//! selecting the maximum number of conversions equal to 7
	AdcRegs.ADCMAXCONV.all =7;
	//! setting CONV00 polling on ADCINA0
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;
	//! setting CONV01 polling on ADCINA1
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;
	//! setting CONV02 polling on ADCINA2
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2;
	//! setting CONV03 polling on ADCINA3
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3;
	//! setting CONV04 polling on ADCINA4
	AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x4;
	//! setting CONV05 polling on ADCINA5
	AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x5;
	//! setting CONV06 polling on ADCINA6
	AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x6;
	//! setting CONV07 polling on ADCINA7
	AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x7;
	//! setting CONV08 polling on ADCINA0
	AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0x0;
	//! setting CONV09 polling on ADCINA1
	AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x1;
	//! setting CONV10 polling on ADCINA2
	AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 0x2;
	//! setting CONV11 polling on ADCINA3
	AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 0x3;
	//! setting CONV12 polling on ADCINA4
	AdcRegs.ADCCHSELSEQ4.bit.CONV12 = 0x4;
	//! setting CONV13 polling on ADCINA5
	AdcRegs.ADCCHSELSEQ4.bit.CONV13 = 0x5;
	//! setting CONV14 polling on ADCINA6
	AdcRegs.ADCCHSELSEQ4.bit.CONV14 = 0x6;
	//! setting CONV15 polling on ADCINA7
	AdcRegs.ADCCHSELSEQ4.bit.CONV15 = 0x7;
	//! SEQ1 interrupt enable
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;
}

/*!
 *  \brief ADC value processing
 */
void HandlrADC(Model_Data_PMSM_S *md_motor_l, Settng_Data_PMSM_S *sd_motor_l) {
	Uint16 i_abs_u_l, i_abs_v_l, ramp_speed_ext_l;

	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;
	i_abs_u_l = AdcRegs.ADCRESULT7 >> 4;
	i_abs_v_l = AdcRegs.ADCRESULT6 >> 4;
	ramp_speed_ext_l= AdcRegs.ADCRESULT5 >> 4;

	md_motor_l->iu.fl = ((float32)i_abs_u_l - SHIFT_IU) * DIV_1_1700 * 2;
	md_motor_l->iv.fl = ((float32)i_abs_v_l - SHIFT_IV) * DIV_1_1700 * 2;
	md_motor_l->iw.fl = -md_motor_l->iu.fl - md_motor_l->iv.fl;
	sd_motor_l->k_mul_ext_ref = ramp_speed_ext_l * DIV_1_4096;
}
