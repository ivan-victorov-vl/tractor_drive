//###########################################################################
//
// File:        MainCpuAdc.c
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
void AdcInitDrive(void) {

    // zeroing of ADCTRL1 register data
    AdcRegs.ADCTRL1.all = 0;


    // control SOC pulse width equal to 7 = 8 x ADCCLK
    AdcRegs.ADCTRL1.bit.ACQ_PS = 0x1;
    // core frequency predilator by 1
    AdcRegs.ADCTRL1.bit.CPS = 0;
    // START-STOP mode selection.
    // after conversion enter standby mode, and after standby is completed
    // start the conversion again
    // zeroing of ADCTRL3 register data
    AdcRegs.ADCTRL3.all = 0x00E0;
    // frequency division by 1
    AdcRegs.ADCTRL3.bit.ADCCLKPS = 0;
    AdcRegs.ADCTRL3.bit.SMODE_SEL = 0x1;
    //! processing in cascade mode with one 16-level sequencer
    AdcRegs.ADCTRL1.bit.SEQ_CASC=0;
    //! SEQ1 interrupt enable
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0x1;
    //! SEQ2 interrupt enable
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ2 = 0x1;

    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 0x1;
    AdcRegs.ADCTRL2.bit.RST_SEQ2 = 0x1;

    //! select the maximum number of conversions equal to 16
    AdcRegs.ADCMAXCONV.bit.MAX_CONV1= 0x7;
    AdcRegs.ADCMAXCONV.bit.MAX_CONV2= 0x7;

    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2;
    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3;
    AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x4;
    AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x5;
    AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x6;
    AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x7;

    AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0x8;
    AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x9;
    AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 0xA;
    AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 0xB;
    AdcRegs.ADCCHSELSEQ4.bit.CONV12 = 0xC;
    AdcRegs.ADCCHSELSEQ4.bit.CONV13 = 0xD;
    AdcRegs.ADCCHSELSEQ4.bit.CONV14 = 0xE;
    AdcRegs.ADCCHSELSEQ4.bit.CONV15 = 0xF;

    // TODO For Debug
    /*
    //! 4  double  conv's  each  sequencer  (8  total)
    AdcRegs.ADCMAXCONV.all  =  0x0033;
    //! Setup  conv  from  ADCINA0  &amp;  ADCINB0
    AdcRegs.ADCCHSELSEQ1.bit.CONV00  =  0x0;
    //! Setup  conv  from  ADCINA1  &amp;  ADCINB1
    AdcRegs.ADCCHSELSEQ1.bit.CONV01  =  0x1;
    //! Setup  conv  from  ADCINA2  &amp;  ADCINB2
    AdcRegs.ADCCHSELSEQ1.bit.CONV02  =  0x2;
    //! Setup  conv  from  ADCINA3  &amp;  ADCINB3
    AdcRegs.ADCCHSELSEQ1.bit.CONV03  =  0x3;
    //!  Setup  conv  from  ADCINA4  &amp;  ADCINB4
    AdcRegs.ADCCHSELSEQ3.bit.CONV08  =  0x4;
    //! Setup  conv  from  ADCINA5  &amp;  ADCINB5
    AdcRegs.ADCCHSELSEQ3.bit.CONV09  =  0x5;
    //! Setup  conv  from  ADCINA6  &amp;  ADCINB6
    AdcRegs.ADCCHSELSEQ3.bit.CONV10  =  0x6;
    //! Setup  conv  from  ADCINA7  &amp;  ADCINB7
    AdcRegs.ADCCHSELSEQ3.bit.CONV11  =  0x7;
    */



    AdcRegs.ADCTRL2.all = 0x2020;

}

/*!
 *  \brief ADC value processing
 */
void HandlrADC(Model_Data_PMSM_S *md_motor_l, Settng_Data_PMSM_S *sd_motor_l) {
    //! ADCINA0
    md_motor_l->uac_os_1_1.fl = (float32)(AdcRegs.ADCRESULT0 >> 4);
    //! ADCINB0
    md_motor_l->izad_20_ma.fl = (float32)(AdcRegs.ADCRESULT1 >> 4);
    //! ADCINA1
    md_motor_l->uac_os_2_1.fl = (float32)(AdcRegs.ADCRESULT2 >> 4);
    //! ADCINB1
    md_motor_l->fzad_20_ma.fl = (float32)(AdcRegs.ADCRESULT3 >> 4);
    //! ADCINA2
    md_motor_l->uac_os_3_1.fl = (float32)(AdcRegs.ADCRESULT4 >> 4);
    //! ADCINB2
    md_motor_l->i_os_1_0.fl = (float32)(AdcRegs.ADCRESULT5 >> 4);
    //! ADCINA3
    md_motor_l->uac_os_1_0.fl = (float32)(AdcRegs.ADCRESULT6 >> 4);
    //! ADCINB3
    md_motor_l->i_os_2_0.fl = (float32)(AdcRegs.ADCRESULT7 >> 4);
    //! ADCINA4
    md_motor_l->uac_os_2_0.fl = (float32)(AdcRegs.ADCRESULT8 >> 4);
    //! ADCINB4
    md_motor_l->i_os_3_0.fl = (float32)(AdcRegs.ADCRESULT9 >> 4);
    //! ADCINA5
    md_motor_l->uac_os_3_0.fl = (float32)(AdcRegs.ADCRESULT10 >> 4);
    //! ADCINB5
    md_motor_l->i_os_1_1.fl = (float32)(AdcRegs.ADCRESULT11 >> 4);
    //! ADCINA6
    md_motor_l->udc.fl = (float32)(AdcRegs.ADCRESULT12 >> 4);
    //! ADCINB6
    md_motor_l->i_os_2_1.fl = (float32)(AdcRegs.ADCRESULT13 >> 4);
    //! ADCINA7
    md_motor_l->temp.fl = (float32)(AdcRegs.ADCRESULT14 >> 4);
    //! ADCINB7
    md_motor_l->i_os_3_1.fl = (float32)(AdcRegs.ADCRESULT15 >> 4);

    //! TODO please change shift current for debug (IT IS NOT SET UP NOW!!!)
    md_motor_l->iu.fl = md_motor_l->i_os_1_0.fl - 2048;
    md_motor_l->iv.fl = md_motor_l->i_os_2_0.fl - 2048;
    md_motor_l->iw.fl = md_motor_l->i_os_3_0.fl - 2048;
    md_motor_l->iu1.fl = md_motor_l->i_os_1_1.fl - 2048;
    md_motor_l->iv1.fl = md_motor_l->i_os_2_1.fl - 2048;
    md_motor_l->iw1.fl = md_motor_l->i_os_3_1.fl - 2048;
    sd_motor_l->k_mul_ext_ref = 0;
    AdcRegs.ADCTRL2.all = 0x2020;
}
