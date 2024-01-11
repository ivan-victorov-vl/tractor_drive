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

void PMSMotorFuncScalInit(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l);
void PMSMotorFuncReset(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l);
void PMSMotorFuncScal(Model_Data_PMSM_S *md_la, Flg_Cntrl_Drive_S *mf_la, Brws_Param_Drive *bpd_la);
void CntrlDrive(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l, Brws_Param_Drive *bpd_l);


/*!
 * \brief Init PMSM motor control
 */
void PMSMotorFuncScalInit(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l) {
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
 * \brief Reset PMSM motor control
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
 * \brief PMSM motor control function
 */
void CntrlDrive(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l, Brws_Param_Drive *bpd_l) {

    //! work frequency control
    if (mf_l->bits_reg2.bits.wrk_drv) {
        //! processing intensity generator values
        SpeedRef(md_l->k_f_mul_ref.fl, md_l->k_f_mul_plus.fl, md_l->k_f_mul_minus.fl, &md_l->k_f_mul.fl);

    } else {
        //! step with non-working condition of the frequency converter
        //! start drive converter
        mf_l->bits_reg2.bits.strt_drv = GpioDataRegs.GPCDAT.bit.GPIO72;
        if (mf_l->bits_reg2.bits.strt_drv) {
            mf_l->bits_reg2.bits.wrk_drv = 1;
        }
    }
}
