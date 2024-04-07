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
//! include of the header file "Debug.h"
#include "Debug.h"


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
    //! acquisition window size
    AdcRegs.ADCTRL1.bit.ACQ_PS = 0xf;
    //! adc core clock divider
    AdcRegs.ADCTRL3.bit.ADCCLKPS = 0x1;
    //! 0 Non-Cascaded Mode
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 0;
    //! seq 1 interrupt enable
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0x1;
    //! seq 2 interrupt enable
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ2 = 0x1;
    //! restart sequencer 1
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 0x1;
    //! restart sequencer 1
    AdcRegs.ADCTRL2.bit.RST_SEQ2 = 0x1;
    //! conversion selection 00
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;
    //! conversion selection 01
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;
    //! conversion selection 02
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2;
    //! conversion selection 03
    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3;
    //! conversion selection 04
    AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x4;
    //! conversion selection 05
    AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x5;
    //! conversion selection 06
    AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x6;
    //! conversion selection 07
    AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x7;
    //! conversion selection 08
    AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0x8;
    //! conversion selection 09
    AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x9;
    //! conversion selection 10
    AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 0xA;
    //! conversion selection 11
    AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 0xB;
    //! conversion selection 12
    AdcRegs.ADCCHSELSEQ4.bit.CONV12 = 0xC;
    //! conversion selection 13
    AdcRegs.ADCCHSELSEQ4.bit.CONV13 = 0xD;
    //! conversion selection 14
    AdcRegs.ADCCHSELSEQ4.bit.CONV14 = 0xE;
    //! conversion selection 15
    AdcRegs.ADCCHSELSEQ4.bit.CONV15 = 0xF;
    //! set up ADC to perform 4 conversions for every SOC for max conversation 1
    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 3;
    //! set up ADC to perform 4 conversions for every SOC for max conversation 2
    AdcRegs.ADCMAXCONV.bit.MAX_CONV2 = 3;
    //! start of conversion trigger for SEQ1
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 0x1;
    //! start of conversion trigger for SEQ2
    AdcRegs.ADCTRL2.bit.SOC_SEQ2 = 0x1;
}

/*!
 *  \brief ADC value processing
 */
void HandlrADC(Model_Data_PMSM_S *md_motor_l, Settng_Data_PMSM_S *sd_motor_l) {
    //! ADCINA0
    md_motor_l->uac_os_1_1.fl = (float32)(AdcRegs.ADCRESULT0 >> 4);
    //! ADCINA1
    md_motor_l->uac_os_2_1.fl = (float32)(AdcRegs.ADCRESULT1 >> 4);
    //! ADCINA2
    md_motor_l->uac_os_3_1.fl = (float32)(AdcRegs.ADCRESULT2 >> 4);
    //! ADCINA3
    md_motor_l->uac_os_1_0.fl = (float32)(AdcRegs.ADCRESULT3 >> 4);
    //! ADCINA4
    md_motor_l->uac_os_2_0.fl = (float32)(AdcRegs.ADCRESULT4 >> 4);
    //! ADCINA5
    md_motor_l->uac_os_3_0.fl = (float32)(AdcRegs.ADCRESULT5 >> 4);
    //! ADCINA6
    md_motor_l->udc.fl = ((float32)(AdcRegs.ADCRESULT6 >> 4) * DIV_1_4096);
    //! ADCINA7
    md_motor_l->temp.fl = (float32)(AdcRegs.ADCRESULT7 >> 4);
    //! ADCINB0
    md_motor_l->izad_20_ma.fl = (float32)(AdcRegs.ADCRESULT8 >> 4);
    //! ADCINB1
    md_motor_l->fzad_20_ma.fl = (float32)(AdcRegs.ADCRESULT9 >> 4);
    //! ADCINB2
    md_motor_l->i_os_1_0.fl = (float32)(AdcRegs.ADCRESULT10 >> 4);
    //! ADCINB3
    md_motor_l->i_os_2_0.fl = (float32)(AdcRegs.ADCRESULT11 >> 4);
    //! ADCINB4
    md_motor_l->i_os_3_0.fl = (float32)(AdcRegs.ADCRESULT12 >> 4);
    //! ADCINB5
    md_motor_l->i_os_1_1.fl = (float32)(AdcRegs.ADCRESULT13 >> 4);
    //! ADCINB6
    md_motor_l->i_os_2_1.fl = (float32)(AdcRegs.ADCRESULT14 >> 4);
    //! ADCINB7
    md_motor_l->i_os_3_1.fl = (float32)(AdcRegs.ADCRESULT15 >> 4);

    //! TODO please change shift current for debug (IT IS NOT SET UP NOW!!!)
    //! shift for current phase u
    md_motor_l->iu.fl = md_motor_l->i_os_1_0.fl - ZERO_VALUE_I_PHASE_U;
    //! shift for current phase v
    md_motor_l->iv.fl = md_motor_l->i_os_2_0.fl - ZERO_VALUE_I_PHASE_V;
    //! shift for current phase w
    md_motor_l->iw.fl = md_motor_l->i_os_3_0.fl - ZERO_VALUE_I_PHASE_W;
    //! shift for current phase u1
    md_motor_l->iu1.fl = md_motor_l->i_os_1_1.fl - ZERO_VALUE_I_PHASE_U1;
    //! shift for current phase v1
    md_motor_l->iv1.fl = md_motor_l->i_os_2_1.fl - ZERO_VALUE_I_PHASE_V1;
    //! shift for current phase w1
    md_motor_l->iw1.fl = md_motor_l->i_os_3_1.fl - ZERO_VALUE_I_PHASE_W1;

    //! shift for sensor voltage phase u
    md_motor_l->uu_os.fl = md_motor_l->uac_os_1_0.fl - ZERO_VALUE_U_PHASE_U;
    //! shift for sensor voltage phase v
    md_motor_l->uv_os.fl = md_motor_l->uac_os_2_0.fl - ZERO_VALUE_U_PHASE_V;
    //! shift for sensor voltage phase w
    md_motor_l->uw_os.fl = md_motor_l->uac_os_3_0.fl - ZERO_VALUE_U_PHASE_W;
    //! shift for sensor voltage phase u1
    md_motor_l->uu1_os.fl = md_motor_l->uac_os_1_1.fl - ZERO_VALUE_U_PHASE_U1;
    //! shift for sensor voltage phase v1
    md_motor_l->uv1_os.fl = md_motor_l->uac_os_2_1.fl - ZERO_VALUE_U_PHASE_V1;
    //! shift for sensor voltage phase w1
    md_motor_l->uw1_os.fl = md_motor_l->uac_os_3_1.fl - ZERO_VALUE_U_PHASE_W1;

    //! bringing the voltage set point to unity
    sd_motor_l->k_mul_ext_ref = DIV_1_4096 * md_motor_l->fzad_20_ma.fl;

    AdcRegs.ADCTRL2.all = 0x2020;
}
