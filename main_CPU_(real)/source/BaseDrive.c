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
void PMSMotorFuncScalReset(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l);
void PMSMotorFuncScal(Model_Data_PMSM_S *md_la, Flg_Cntrl_Drive_S *mf_la, Brws_Param_Drive *bpd_la);
void CntrlDrive(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l, Brws_Param_Drive *bpd_l);


void PMSMotorFuncScalInit(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l) {

}

void PMSMotorFuncScalReset(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l) {
}

void PMSMotorFuncScal(Model_Data_PMSM_S *md_la, Flg_Cntrl_Drive_S *mf_la, Brws_Param_Drive *bpd_la) {
}


/*!
 * \brief PMSM motor control function
 */
void CntrlDrive(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l, Brws_Param_Drive *bpd_l) {
    //! processing intensity generator values
    SpeedRef(md_l->k_f_mul_ref.fl, md_l->k_f_mul_plus.fl, md_l->k_f_mul_minus.fl, &md_l->k_f_mul.fl);

}
