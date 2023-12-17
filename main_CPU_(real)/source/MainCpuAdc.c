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
	//! core frequency pre-divider by 1
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
	//! selecting the maximum number of conversions equal to 8
	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 =7;
    AdcRegs.ADCMAXCONV.bit.MAX_CONV2 =8;

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
	//! setting CONV08 polling on ADCINB0
	AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0x0;
	//! setting CONV09 polling on ADCINB1
	AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x1;
	//! setting CONV10 polling on ADCINB2
	AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 0x2;
	//! setting CONV11 polling on ADCINB3
	AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 0x3;
	//! setting CONV12 polling on ADCINB4
	AdcRegs.ADCCHSELSEQ4.bit.CONV12 = 0x4;
	//! setting CONV13 polling on ADCINB5
	AdcRegs.ADCCHSELSEQ4.bit.CONV13 = 0x5;
	//! setting CONV14 polling on ADCINB6
	AdcRegs.ADCCHSELSEQ4.bit.CONV14 = 0x6;
	//! setting CONV15 polling on ADCINB7
	AdcRegs.ADCCHSELSEQ4.bit.CONV15 = 0x7;
	//! SEQ1 interrupt enable
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;
}

/*!
 *  \brief ADC value processing
 */
void HandlrADC(Model_Data_PMSM_S *md_motor_l, Settng_Data_PMSM_S *sd_motor_l) {
	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;
    AdcRegs.ADCTRL2.bit.SOC_SEQ2 = 1;

	md_motor_l->uac_is_1_0.fl = AdcRegs.ADCRESULT3 >> 4;
	md_motor_l->uac_is_2_0.fl = AdcRegs.ADCRESULT4 >> 4;
	md_motor_l->uac_is_3_0.fl = AdcRegs.ADCRESULT5 >> 4;
	md_motor_l->uac_is_1_1.fl = AdcRegs.ADCRESULT0 >> 4;
	md_motor_l->uac_is_2_1.fl = AdcRegs.ADCRESULT1 >> 4;
	md_motor_l->uac_is_3_1.fl = AdcRegs.ADCRESULT2 >> 4;
	md_motor_l->udc.fl = AdcRegs.ADCRESULT6 >> 4;
	md_motor_l->temp.fl = AdcRegs.ADCRESULT7 >> 4;
	md_motor_l->izad_20_ma.fl = AdcRegs.ADCRESULT8 >> 4;
	md_motor_l->fzad_20_ma.fl = AdcRegs.ADCRESULT9 >> 4;
	md_motor_l->i_os_1_0.fl = AdcRegs.ADCRESULT10 >> 4;
	md_motor_l->i_os_2_0.fl = AdcRegs.ADCRESULT11 >> 4;
	md_motor_l->i_os_3_0.fl = AdcRegs.ADCRESULT12 >> 4;
	md_motor_l->i_os_1_1.fl = AdcRegs.ADCRESULT13 >> 4;
	md_motor_l->i_os_2_1.fl = AdcRegs.ADCRESULT14 >> 4;
	md_motor_l->i_os_3_1.fl = AdcRegs.ADCRESULT15 >> 4;

	md_motor_l->iu.fl = 0;
	md_motor_l->iv.fl = 0;
	md_motor_l->iw.fl = 0;
	sd_motor_l->k_mul_ext_ref = 0;
}
