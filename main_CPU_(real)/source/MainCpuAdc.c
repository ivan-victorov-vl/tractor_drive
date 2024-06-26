//###########################################################################
//
// File:        MainCpuAdc.c
//
// Description: ADC initialization
//
//###########################################################################

////////////////////// HEADER FILE CONNECTION //////////////////////
//! Include of the header file "PeripheralHeaderIncludes.h"
#include "PeripheralHeaderIncludes.h"
//! Include of the header file "Debug.h"
#include "Debug.h"

//! FUNCTION DECLARATION
//! AdcInitDrive function declaration
void AdcInitDrive (void);
//! Function declaration HandlrAdc
void HandlrdAdc(Model_Data_PMSM_S *md_motor_l, Settng_Data_PMSM_S *sd_motor_l);
//! Function declaration HandlrVoltageAdc
void HandlrVoltageAdc(Model_Data_PMSM_S *md_motor_l);
//! Function declaration HandlrCurrentAdc
void HandlrCurrentAdc(Model_Data_PMSM_S *md_motor_l);
//! Function declaration HandlrFastAdc
void HandlrFastAdc(Model_Data_PMSM_S *md_motor_l);

/*!
 *  \brief: Setting and initialization of the ADC of the frequency converter
 */
void AdcInitDrive(void) {
    //! Acquisition window size
    AdcRegs.ADCTRL1.bit.ACQ_PS = 0xf;
    //! Adc core clock divider
    AdcRegs.ADCTRL3.bit.ADCCLKPS = 0x1;
    //! 0 Non-Cascaded Mode
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 0;
    //! Seq 1 interrupt enable
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0x1;
    //! Seq 2 interrupt enable
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ2 = 0x1;
    //! Restart sequencer 1
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 0x1;
    //! Restart sequencer 1
    AdcRegs.ADCTRL2.bit.RST_SEQ2 = 0x1;
    //! Conversion selection 00
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;
    //! Conversion selection 01
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;
    //! Conversion selection 02
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2;
    //! Conversion selection 03
    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3;
    //! Conversion selection 04
    AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x4;
    //! Conversion selection 05
    AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x5;
    //! Conversion selection 06
    AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x6;
    //! Conversion selection 07
    AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x7;
    //! Conversion selection 08
    AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0x8;
    //! Conversion selection 09
    AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x9;
    //! Conversion selection 10
    AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 0xA;
    //! Conversion selection 11
    AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 0xB;
    //! Conversion selection 12
    AdcRegs.ADCCHSELSEQ4.bit.CONV12 = 0xC;
    //! Conversion selection 13
    AdcRegs.ADCCHSELSEQ4.bit.CONV13 = 0xD;
    //! Conversion selection 14
    AdcRegs.ADCCHSELSEQ4.bit.CONV14 = 0xE;
    //! Conversion selection 15
    AdcRegs.ADCCHSELSEQ4.bit.CONV15 = 0xF;
    //! Set up ADC to perform 4 conversions for every SOC for max conversation 1
    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 3;
    //! Set up ADC to perform 4 conversions for every SOC for max conversation 2
    AdcRegs.ADCMAXCONV.bit.MAX_CONV2 = 3;
    //! Start of conversion trigger for SEQ1
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 0x1;
    //! Start of conversion trigger for SEQ2
    AdcRegs.ADCTRL2.bit.SOC_SEQ2 = 0x1;
}

/*!
 *  \brief ADC value processing
 */
void HandlrAdc(Model_Data_PMSM_S *md_motor_l, Settng_Data_PMSM_S *sd_motor_l) {
    //! Read ADCINA6 value
    md_motor_l->udc.fl = ((float32)(AdcRegs.ADCRESULT6 >> 4) * DIV_1_4096);
    //! Read ADCINA7 value
    md_motor_l->temp.fl = (float32)(AdcRegs.ADCRESULT7 >> 4);
    //! Read ADCINB0 value
    md_motor_l->izad_20_ma.fl = (float32)(AdcRegs.ADCRESULT8 >> 4);
    //! Read ADCINB1 value
    md_motor_l->fzad_20_ma.fl = (float32)(AdcRegs.ADCRESULT9 >> 4);

    //! bringing the voltage set point to unity
    sd_motor_l->k_mul_ext_ref = DIV_1_4096 * md_motor_l->fzad_20_ma.fl;
    //! Start conversation ADC
    AdcRegs.ADCTRL2.all = 0x2020;
}

/*!
 *  \brief Handler fast ADC value
 */
void HandlrFastAdc(Model_Data_PMSM_S *md_motor_l) {
    //! Get voltage ADC value
    HandlrVoltageAdc(md_motor_l);
    //! Get current ADC value
    HandlrCurrentAdc(md_motor_l);
    //! Start conversation ADC
    AdcRegs.ADCTRL2.all = 0x2020;
}

/*!
 *  \brief ADC value voltage processing
 */
void HandlrVoltageAdc(Model_Data_PMSM_S *md_motor_l) {
    //! Read ADCINA0 value
    md_motor_l->uac_os_1_1.fl = (float32)(AdcRegs.ADCRESULT0 >> 4);
    //! Read ADCINA1 value
    md_motor_l->uac_os_2_1.fl = (float32)(AdcRegs.ADCRESULT1 >> 4);
    //! Read ADCINA2 value
    md_motor_l->uac_os_3_1.fl = (float32)(AdcRegs.ADCRESULT2 >> 4);
    //! Read ADCINA3 value
    md_motor_l->uac_os_1_0.fl = (float32)(AdcRegs.ADCRESULT3 >> 4);
    //! Read ADCINA4 value
    md_motor_l->uac_os_2_0.fl = (float32)(AdcRegs.ADCRESULT4 >> 4);
    //! Read ADCINA5 value
    md_motor_l->uac_os_3_0.fl = (float32)(AdcRegs.ADCRESULT5 >> 4);

    //! Shift for sensor voltage phase u
    md_motor_l->uu_os.fl = md_motor_l->uac_os_1_0.fl - (float32)ZERO_VALUE_U_PHASE_U;
    //! Shift for sensor voltage phase v
    md_motor_l->uv_os.fl = md_motor_l->uac_os_2_0.fl - (float32)ZERO_VALUE_U_PHASE_V;
    //! Shift for sensor voltage phase w
    md_motor_l->uw_os.fl = md_motor_l->uac_os_3_0.fl - (float32)ZERO_VALUE_U_PHASE_W;
    //! Shift for sensor voltage phase u1
    md_motor_l->uu1_os.fl = md_motor_l->uac_os_1_1.fl - (float32)ZERO_VALUE_U_PHASE_U1;
    //! Shift for sensor voltage phase v1
    md_motor_l->uv1_os.fl = md_motor_l->uac_os_2_1.fl - (float32)ZERO_VALUE_U_PHASE_V1;
    //! Shift for sensor voltage phase w1
    md_motor_l->uw1_os.fl = md_motor_l->uac_os_3_1.fl - (float32)ZERO_VALUE_U_PHASE_W1;
}

/*!
 *  \brief ADC value current processing
 */
void HandlrCurrentAdc(Model_Data_PMSM_S *md_motor_l) {
    //! Read ADCINB2 value
    md_motor_l->i_os_1_0.fl = (float32)(AdcRegs.ADCRESULT10 >> 4);
    //! Read ADCINB3 value
    md_motor_l->i_os_2_0.fl = (float32)(AdcRegs.ADCRESULT11 >> 4);
    //! Read ADCINB4 value
    md_motor_l->i_os_3_0.fl = (float32)(AdcRegs.ADCRESULT12 >> 4);
    //! Read ADCINB5 value
    md_motor_l->i_os_1_1.fl = (float32)(AdcRegs.ADCRESULT13 >> 4);
    //! Read ADCINB6 value
    md_motor_l->i_os_2_1.fl = (float32)(AdcRegs.ADCRESULT14 >> 4);
    //! Read ADCINB7 value
    md_motor_l->i_os_3_1.fl = (float32)(AdcRegs.ADCRESULT15 >> 4);

    //! Shift for current phase u
    md_motor_l->iu.fl = md_motor_l->i_os_1_0.fl - ZERO_VALUE_I_PHASE_U;
    //! Shift for current phase v
    md_motor_l->iv.fl = md_motor_l->i_os_2_0.fl - ZERO_VALUE_I_PHASE_V;
    //! Shift for current phase w
    md_motor_l->iw.fl = md_motor_l->i_os_3_0.fl - ZERO_VALUE_I_PHASE_W;
    //! Shift for current phase u1
    md_motor_l->iu1.fl = md_motor_l->i_os_1_1.fl - ZERO_VALUE_I_PHASE_U1;
    //! Shift for current phase v1
    md_motor_l->iv1.fl = md_motor_l->i_os_2_1.fl - ZERO_VALUE_I_PHASE_V1;
    //! Shift for current phase w1
    md_motor_l->iw1.fl = md_motor_l->i_os_3_1.fl - ZERO_VALUE_I_PHASE_W1;
}
