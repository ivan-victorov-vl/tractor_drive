//###########################################################################
//
// File: BaseDriveUsr.c
//
// Title: Frequency converter control
//
//###########################################################################

////////////////////// HEADER FILE INCLUDE //////////////////////
//! include header "PeripheralHeaderIncludes.h"
#include "PeripheralHeaderIncludes.h"
//! header file include "BaseDrive.h"
#include "BaseDrive.h"
//! header file include"SysSrvc.h"
#include "FuncDrive.h"

void PMSMotorFuncInit(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l);
void PMSMotorFuncReset(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l);
void PMSMotorFuncScal(Model_Data_PMSM_S *md_la, Flg_Cntrl_Drive_S *mf_la, Brws_Param_Drive *bpd_la);
void PMSMotorFuncTechSpec(Model_Data_PMSM_S *md_la, Flg_Cntrl_Drive_S *mf_la, Brws_Param_Drive *bpd_la);
void PMSMotorFuncTechSpecWithoutIntenstCntrllr(Model_Data_PMSM_S *md_la, Flg_Cntrl_Drive_S *mf_la, Brws_Param_Drive *bpd_la);
void PMSMotorFuncSensorless(Model_Data_PMSM_S *md_la, Flg_Cntrl_Drive_S *mf_la, Brws_Param_Drive *bpd_la);
void CntrlDrive(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l, Brws_Param_Drive *bpd_l);
void HandlerExternalButtons(Flg_Cntrl_Drive_S *mf_l);


/*!
 * \brief initialization PMSM motor control
 */
void PMSMotorFuncInit(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l) {
    //! initialization setting the frequency inverter data
    md_l->k_f_mul_ref.fl = 0;
    md_l->k_f_mul.fl = 0;
    md_l->k_f_mul_plus.fl = 0;
    md_l->k_f_mul_minus.fl = 0;
    md_l->uu.fl = 0;
    md_l->uv.fl = 0;
    md_l->uw.fl = 0;
    md_l->is.fl = 0;
    md_l->cur_pstn_rtr.fl = 0;
    md_l->udc.fl = 0;
    md_l->isnom.fl = 0;
}

/*!
 * \brief reset PMSM motor control
 */
void PMSMotorFuncReset(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l) {
    //! resetting the frequency inverter data
    md_l->k_f_mul_ref.fl = 0;
    md_l->k_f_mul.fl = 0;
    md_l->k_f_mul_plus.fl = 0;
    md_l->k_f_mul_minus.fl = 0;
    md_l->uu.fl = 0;
    md_l->uv.fl = 0;
    md_l->uw.fl = 0;
}

void PMSMotorFuncScal(Model_Data_PMSM_S *md_la, Flg_Cntrl_Drive_S *mf_la, Brws_Param_Drive *bpd_la) {
}

/*!
 * \brief PMSM motor control function from technical specification
 */
void PMSMotorFuncTechSpec(Model_Data_PMSM_S *md_la, Flg_Cntrl_Drive_S *mf_la, Brws_Param_Drive *bpd_la) {
    static float32 i_alpha_la, i_beta_la;

    //! conversion of currents from three-phase to two-phase reference frame
    Calc3To2(md_la->iu.fl, md_la->iv.fl, md_la->iw.fl, &i_alpha_la, &i_beta_la);
    //! calculation of the measured current in scalar coordinate system
    md_la->is.fl = CalcLengthVect2In(i_alpha_la, i_beta_la);
    //! calculation degree
    md_la->theta.fl += md_la->k_f_mul.fl;
    //! when it reaches less than 0 degrees
    if (md_la->theta.fl <= 0) {
        //! update the angle
        md_la->theta.fl += FULL_DSKRT;
    }
    //! if it more than 360 degrees
    if (md_la->theta.fl >= FULL_DSKRT) {
        //! reset the angle to zero
        md_la->theta.fl -= FULL_DSKRT;
    }

    //! calculate current phase
    CalculateConditionPMS(md_la);

    // TODO Now kk_f_mul amplitude is not regulator. Please to do regulator to voltage or current
    md_la->k_reg_mul.fl = md_la->k_f_mul.fl;
    //! calculate phase with amplitude
    md_la->uu.fl =  md_la->uu.fl * md_la->k_reg_mul.fl;
    md_la->uv.fl =  md_la->uv.fl * md_la->k_reg_mul.fl;
    md_la->uw.fl =  md_la->uw.fl * md_la->k_reg_mul.fl;
    md_la->uu1.fl =  md_la->uu1.fl * md_la->k_reg_mul.fl;
    md_la->uv1.fl =  md_la->uv1.fl * md_la->k_reg_mul.fl;
    md_la->uv1.fl =  md_la->uw1.fl * md_la->k_reg_mul.fl;
}


/*!
 * \brief PMSM motor control function from technical specification without intensity controller
 */
void PMSMotorFuncTechSpecWithoutIntenstCntrllr(Model_Data_PMSM_S *md_la, Flg_Cntrl_Drive_S *mf_la, Brws_Param_Drive *bpd_la) {
    static float32 i_alpha_la, i_beta_la;

    //! conversion of currents from three-phase to two-phase reference frame
    Calc3To2(md_la->iu.fl, md_la->iv.fl, md_la->iw.fl, &i_alpha_la, &i_beta_la);
    //! calculation of the measured current in scalar coordinate system
    md_la->is.fl = CalcLengthVect2In(i_alpha_la, i_beta_la);
    //!
    md_la->theta.fl += MIN_CROSS_ANGLE;
    //! when it reaches less than 0 degrees
    if (md_la->theta.fl <= 0) {
        //! update the angle
        md_la->theta.fl += FULL_DSKRT;
    }
    //! if it more than 360 degrees
    if (md_la->theta.fl >= FULL_DSKRT) {
        //! reset the angle to zero
        md_la->theta.fl -= FULL_DSKRT;
    }

    //! calculate current phase
    CalculateConditionPMS(md_la);

    //! calculate phase with amplitude
    md_la->uu.fl =  md_la->uu.fl * md_la->k_reg_mul.fl;
    md_la->uv.fl =  md_la->uv.fl * md_la->k_reg_mul.fl;
    md_la->uw.fl =  md_la->uw.fl * md_la->k_reg_mul.fl;
    md_la->uu1.fl =  md_la->uu1.fl * md_la->k_reg_mul.fl;
    md_la->uv1.fl =  md_la->uv1.fl * md_la->k_reg_mul.fl;
    md_la->uv1.fl =  md_la->uw1.fl * md_la->k_reg_mul.fl;
}

void PMSMotorFuncSensorless(Model_Data_PMSM_S *md_la, Flg_Cntrl_Drive_S *mf_la, Brws_Param_Drive *bpd_la) {
}

/*!
 * \brief PMSM motor control function
 */
void CntrlDrive(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l, Brws_Param_Drive *bpd_l) {
    //! work frequency control
    if (mf_l->bits_reg2.bits.wrk_drv) {

    #if defined(MODEL_INTENSITY_SET) && MODEL_INTENSITY_SET==TRUE_VAL
        //! processing intensity generator values
        SpeedRef(md_l->k_f_mul_ref.fl, md_l->k_f_mul_plus.fl, md_l->k_f_mul_minus.fl, &md_l->k_f_mul.fl);
        // Calculate U,V,W for PMSM control
        PMSMotorFuncTechSpec(md_l, mf_l, bpd_l);
    #else
        static Uint16 conditionSensor;
        //! Running the model without intensity setter
        if (mf_l->bits_reg1.bits.ext_angle && conditionSensor) {
            PMSMotorFuncTechSpecWithoutIntenstCntrllr(md_l, mf_l, bpd_l);
            conditionSensor = 0;
        }
        //! Get condition sensor angle
        if (!mf_l->bits_reg1.bits.ext_angle) {
            conditionSensor = 1;
        }
    #endif
    } else {
        //! step with non-working condition of the frequency converter
        //! start drive converter
        mf_l->bits_reg2.bits.strt_drv = GpioDataRegs.GPCDAT.bit.GPIO72;
        if (mf_l->bits_reg2.bits.strt_drv) {
            mf_l->bits_reg2.bits.wrk_drv = 1;
        }
    }
}

/*!
 * \brief processing of external buttons
 */
void HandlerExternalButtons(Flg_Cntrl_Drive_S *mf_l) {
    //! getting start data button
    mf_l->bits_reg2.bits.strt_drv = GpioDataRegs.GPCDAT.bit.GPIO72;
    //! getting stop data button
    mf_l->bits_reg2.bits.stp_drv = GpioDataRegs.GPCDAT.bit.GPIO74;
    //! getting reset data button
    mf_l->bits_reg2.bits.reset_drv = GpioDataRegs.GPCDAT.bit.GPIO73;
}
