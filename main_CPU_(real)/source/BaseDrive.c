//###########################################################################
//
// File: BaseDrive.c
//
// Title: Frequency converter control
//
//###########################################################################

////////////////////// HEADER FILE INCLUDE //////////////////////
//! Include header "PeripheralHeaderIncludes.h"
#include "PeripheralHeaderIncludes.h"
//! Header file include "BaseDrive.h"
#include "BaseDrive.h"
//! Header file include"SysSrvc.h"
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
 * \brief Initialization PMSM motor control
 */
void PMSMotorFuncInit(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l) {
    //! Initialization setting the frequency inverter data
    md_l->k_f_mul_ref.fl = 0;
    md_l->k_f_mul.fl = 0;
    md_l->k_f_mul_plus.fl = 0;
    md_l->k_f_mul_minus.fl = 0;
    md_l->uu.fl = 0;
    md_l->uv.fl = 0;
    md_l->uw.fl = 0;
    md_l->uu1.fl = 0;
    md_l->uv1.fl = 0;
    md_l->uw1.fl = 0;
    md_l->is.fl = 0;
    md_l->cur_pstn_rtr.fl = 0;
    md_l->udc.fl = 0;
    md_l->isnom.fl = 0;
    mf_l->bits_reg2.bits.wrk_drv=FALSE_VAL;
    mf_l->bits_reg2.bits.strt_drv=FALSE_VAL;
    mf_l->bits_reg2.bits.stp_drv=FALSE_VAL;
}

/*!
 * \brief Reset PMSM motor control
 */
void PMSMotorFuncReset(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l) {
    //! Resetting the frequency inverter data
    md_l->k_f_mul_ref.fl = 0;
    md_l->k_f_mul.fl = 0;
    md_l->k_f_mul_plus.fl = ADD_PART_INTESNE_SETTER;
    md_l->k_f_mul_minus.fl = ADD_PART_INTESNE_SETTER;
    md_l->uu.fl = 0;
    md_l->uv.fl = 0;
    md_l->uw.fl = 0;
    md_l->uu1.fl = 0;
    md_l->uv1.fl = 0;
    md_l->uw1.fl = 0;
    LED_START_OFF;
    LED_STOP_OFF;
    mf_l->bits_reg2.bits.wrk_drv=FALSE_VAL;
    mf_l->bits_reg2.bits.strt_drv=FALSE_VAL;
    mf_l->bits_reg2.bits.stp_drv=FALSE_VAL;
}

void PMSMotorFuncScal(Model_Data_PMSM_S *md_la, Flg_Cntrl_Drive_S *mf_la, Brws_Param_Drive *bpd_la) {
}

/*!
 * \brief PMSM motor control function from technical specification
 */
void PMSMotorFuncTechSpec(Model_Data_PMSM_S *md_la, Flg_Cntrl_Drive_S *mf_la, Brws_Param_Drive *bpd_la) {
    static float32 i_alpha_la, i_beta_la;

    //! Conversion of currents from three-phase to two-phase reference frame
    Calc3To2(md_la->iu.fl, md_la->iv.fl, md_la->iw.fl, &i_alpha_la, &i_beta_la);
    //! Calculation of the measured current in scalar coordinate system
    md_la->is.fl = CalcLengthVect2In(i_alpha_la, i_beta_la);
    //! Calculation degree
    md_la->theta.fl += md_la->k_f_mul.fl;
    //! When it reaches less than 0 degrees
    if (md_la->theta.fl <= 0) {
        //! Update the angle
        md_la->theta.fl += FULL_DSKRT;
    }
    //! If it more than 360 degrees
    if (md_la->theta.fl >= FULL_DSKRT) {
        //! Reset the angle to zero
        md_la->theta.fl -= FULL_DSKRT;
    }

    //! Calculate current phase
    CalculateConditionPMS(md_la);
}

/*!
 * \brief PMSM motor control function from technical specification without intensity controller
 */
void PMSMotorFuncTechSpecWithoutIntenstCntrllr(Model_Data_PMSM_S *md_la, Flg_Cntrl_Drive_S *mf_la, Brws_Param_Drive *bpd_la) {
    static float32 i_alpha_la, i_beta_la;

    //! Conversion of currents from three-phase to two-phase reference frame
    Calc3To2(md_la->iu.fl, md_la->iv.fl, md_la->iw.fl, &i_alpha_la, &i_beta_la);
    //! Calculation of the measured current in scalar coordinate system
    md_la->is.fl = CalcLengthVect2In(i_alpha_la, i_beta_la);

    //! Compilation when forward of rotation
    #if FORWARD==TRUE_VAL
       //! Increment angle
       md_la->theta.fl += MIN_CROSS_ANGLE;
    //! Compilation when backward of rotation
    #else
       //! Decrement angle
       md_la->theta.fl -= MIN_CROSS_ANGLE;
    #endif

    //! When it reaches less than 0 degrees
    if (md_la->theta.fl <= 0) {
        //! Update the angle
        md_la->theta.fl += FULL_DSKRT;
    }
    //! If it more than 360 degrees
    if (md_la->theta.fl >= FULL_DSKRT) {
        //! Reset the angle to zero
        md_la->theta.fl -= FULL_DSKRT;
    }
    //! Calculate current phase
    CalculateConditionPMS(md_la);
}

void PMSMotorFuncSensorless(Model_Data_PMSM_S *md_la, Flg_Cntrl_Drive_S *mf_la, Brws_Param_Drive *bpd_la) {
}

/*!
 * \brief PMSM motor control function
 */
void CntrlDrive(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l, Brws_Param_Drive *bpd_l) {
    //! set external reference
    md_l->k_f_mul_ref.fl = sd_l->k_mul_ext_ref;
    //! if UDC more value cutoffs
    if (md_l->udc.fl > DO1_ACTIVATION) {
        //! switch on DO1
        DISCRETE_OUT_1_ON;
    } else {
        //! switch off DO1
        DISCRETE_OUT_1_OFF;
    }

    //! work frequency control
    if (mf_l->bits_reg2.bits.wrk_drv) {
        //! if a stop command has been received
        if (mf_l->bits_reg2.bits.stp_drv) {
            //! light the stop LED
            LED_STOP_ON;
            //! TODO added for current regulator reduction (now for debug)
            SpeedRef(0, md_l->k_f_mul_plus.fl, md_l->k_f_mul_minus.fl, &md_l->k_f_mul.fl);
            //! if the speed is stopped
            if (md_l->k_f_mul.fl < md_l->k_f_mul_minus.fl) {
               //! reset the wrk_drv reset flag
                mf_l->bits_reg2.bits.wrk_drv = FALSE_VAL;
               //! set zero value flag stop
                mf_l->bits_reg2.bits.stp_drv = FALSE_VAL;
            }
        } else {
            //! getting "stop" data button
            mf_l->bits_reg2.bits.stp_drv = GET_DIN_3_STOP_BUTTON;
            //! set value speed motor with reference control
            SpeedRef(md_l->k_f_mul_ref.fl, md_l->k_f_mul_plus.fl, md_l->k_f_mul_minus.fl, &md_l->k_f_mul.fl);
        }
    #if defined(MODEL_INTENSITY_SET) && MODEL_INTENSITY_SET == TRUE_VAL
        //! processing intensity generator values
        SpeedRef(md_l->k_f_mul_ref.fl, md_l->k_f_mul_plus.fl, md_l->k_f_mul_minus.fl, &md_l->k_f_mul.fl);
        // Calculate U,V,W for PMSM control
        PMSMotorFuncTechSpec(md_l, mf_l, bpd_l);
    #else
        //! Running the model without intensity setter
        if (mf_l->bits_reg1.bits.ext_angle) {
            PMSMotorFuncTechSpecWithoutIntenstCntrllr(md_l, mf_l, bpd_l);
            mf_l->bits_reg1.bits.ext_angle = FALSE_VAL;
        }
    #endif
    } else {
        //! reset variable PMSM-Motor
        PMSMotorFuncReset(md_l, sd_l, mf_l);
        //! step with non-working condition of the frequency converter
        //! start drive converter
        mf_l->bits_reg2.bits.strt_drv = GET_DIN_2_START_BUTTON;
        if (mf_l->bits_reg2.bits.strt_drv) {
            //! set "work" bit
            mf_l->bits_reg2.bits.wrk_drv = TRUE_VAL;
            //! set "start" bit
            LED_START_ON;
            //! set PWM complimentary state
            Set_Pwm_Complimentary_State();
        }
    }
}

/*!
 * \brief processing of external buttons
 */
void HandlerExternalButtons(Flg_Cntrl_Drive_S *mf_l) {
    //! getting "reset" data button
    mf_l->bits_reg2.bits.reset_drv = GET_DIN_4_RESET_BUTTON;
}

/*!
 * \brief handler for freeze protection
 */
void HandlerFreezeProtection() {
    static Uint16 freezeCondition = 0;

    //! switch pin GPIO58 for freeze
    (freezeCondition) ? (FREEZE_PROTECTION_ON) : (FREEZE_PROTECTION_OFF);
    //! set value freeCondition
    freezeCondition = freezeCondition ? FALSE_VAL : TRUE_VAL;
}

/*!
 * \brief handler for switch processing
 */
Uint16 HandlerSwitchProcessing(Uint16 current_count, Uint16 maxCount) {
    //! get value current count
    if (current_count < (maxCount>>1)) {
        //! set true value
        return TRUE_VAL;
    } else {
        //! set false value
        return FALSE_VAL;
    }
}
