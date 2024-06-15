//###########################################################################
//
// FILE:    FuncDrive.c
//
// TITLE:   Drive support functions
//
// NOTES:
//
//###########################################################################

#include "PeripheralHeaderIncludes.h"
#include "FuncDrive.h"
#include "BaseDrive.h"

// Function declaration Stop
void Stop(Model_Data_PMSM_S *md_la, Settng_Data_PMSM_S *sd_la,
          Flg_Cntrl_Drive_S *mf_la);
// Function declaration Calc2To3Cos
void Calc2To3Cos(float32 first_var_lb, float32 sec_var_lb,
                 float32 *first_res_lb, float32 *sec_res_lb,
                 float32 *third_res_lb);
// Function declaration Calc3To2
void Calc3To2(float32 first_var_lb, float32 sec_var_lb, float32 third_var_lb,
              float32 *first_res_lb, float32 *sec_res_lb);
// Function declaration ApprdFltr
float32 ApprdFltr(float32 first_var_lb, float32 Ti_apprd_lb, float32 *integr_lb);
// Function declaration SpeedRef
void SpeedRef(float32 k_f_mul_ref_lb, float32 k_f_mul_plus_lb,
              float32 k_f_mul_minus_lb, float32 *k_f_mul_lb);
// Function declaration CalcLengthVect2In
float32 CalcLengthVect2In(float32 first_lb, float32 secnd_lb);
// Function declaration PI_Regltr
float32 PiRegltr(float32 cur_var_lb, float32 k_prprnl_lb, float32 k_integral_lb,
                 float32 *integral_lb);
// Function declaration PID_Regltr
float32 PID_Regltr(PID_Rgltr_S *v_pid_r_lb);
// Function declaration CalculateConditionPMSForward
void CalculateConditionPMSForward(Model_Data_PMSM_S *md_l, int32 calc_theta);
// Function declaration CalculateConditionPMSBackward
void CalculateConditionPMSBackward(Model_Data_PMSM_S *md_l, int32 calc_theta);
// Function declaration CalculateScalarCurrentFrom6Phase
float32 CalculateScalarCurrentFrom6Phase(Model_Data_PMSM_S *md_l);

void Stop(Model_Data_PMSM_S *md_la, Settng_Data_PMSM_S *sd_la,
          Flg_Cntrl_Drive_S *mf_la)
{

}

/*!
 \brief calculating the speed setter
 */
void SpeedRef(float32 k_f_mul_ref_lb, float32 k_f_mul_plus_lb,
              float32 k_f_mul_minus_lb, float32 *k_f_mul_lb)
{
    //! if the current speed setting is greater than the set speed setting
    if (*k_f_mul_lb > k_f_mul_ref_lb)
    {
        //! calculation of the current task at decreasing acceleration
        *k_f_mul_lb -= k_f_mul_minus_lb;
    }

    //! if the current speed setting is less than the set speed setting
    if (*k_f_mul_lb < k_f_mul_ref_lb)
    {
        //! calculation of the current job at higher acceleration
        *k_f_mul_lb += k_f_mul_plus_lb;
    }
}

/*!
 \brief aperiodic filter
 */
float32 ApprdFltr(float32 first_var_lb, float32 Ti_apprd_lb, float32 *integr_lb)
{
    *integr_lb += (Ti_apprd_lb * (first_var_lb - *integr_lb));
    return (*integr_lb);
}

/*!
 *  \brief Calculation of variable value after PI regulator
 */
float32 PiRegltr(float32 cur_var_lb, float32 k_prprnl_lb, float32 k_integral_lb,
                 float32 *integral_lb)
{
    //! calculation of the integral component of the pi controller
    *integral_lb += cur_var_lb;
    //! calculation of the return value of the pi regulator function
    return ((cur_var_lb * k_prprnl_lb) + (k_integral_lb * *integral_lb));
}

/*!
 *  \brief PID controller calculation function
 *  Detailed description
 *  e(t) = SP(t) - PV(t)
 *  CO(t) = CObias + Kp * (e(t) + (1/Ti)*Integrl_t_0((e(theta)dtheta) - Td*((dPV(t))/dt)) )
 */
float32 PID_Regltr(PID_Rgltr_S *v_pid_r_lb)
{
    static float32 prop_lb = 0, integr_lb = 0, different_lb = 0;

    prop_lb = v_pid_r_lb->error.fl;
    integr_lb += (1 / v_pid_r_lb->t_intgrl.fl) * v_pid_r_lb->error.fl
            * v_pid_r_lb->dt.fl;
    different_lb = -v_pid_r_lb->t_dfrntl.fl
            * (v_pid_r_lb->cur_var.fl - v_pid_r_lb->prvs_var.fl)
            / v_pid_r_lb->dt.fl;
    v_pid_r_lb->cur_var.fl = v_pid_r_lb->cur_var.fl - v_pid_r_lb->prvs_var.fl;
    return (prop_lb + integr_lb + different_lb);
}

/*!
 \brief conversion from two-phase to three-phase system
 */
void Calc3To2(float32 first_var_lb, float32 sec_var_lb, float32 third_var_lb,
              float32 *first_res_lb, float32 *sec_res_lb)
{
    *first_res_lb = first_var_lb;
    *sec_res_lb = DIV_1_SQRT3 * (sec_var_lb - third_var_lb);
}

/*!
 \brief conversion from three-phase to two-phase system
 */
void Calc2To3Cos(float32 first_var_lb, float32 sec_var_lb,
                 float32 *first_res_lb, float32 *sec_res_lb,
                 float32 *third_res_lb)
{
    *first_res_lb = first_var_lb;
    *sec_res_lb = (DIV_SQRT3_2 * sec_var_lb) - (DIV_1_2 * first_var_lb);
    *third_res_lb = (-DIV_1_2 * first_var_lb) - (DIV_SQRT3_2 * sec_var_lb);
}

/*!
 *  \brief calculating the modulus of a vector by two input values
 */
float32 CalcLengthVect2In(float32 first_lb, float32 secnd_lb)
{
    //! declaration of the variable len_vect_diskrf_lb
    float32 len_vect_diskrf_lb;
    //! declaration of the variable len_vect_diskri_lb
    Uint16 len_vect_diskri_lb;
    //! declaration of vector length calculation variable
    float32 add_len_vect_lb;
    //! declaration of the variable of vector length table calculation
    const float32 *len_vect_tablf_lb;

    //! conversion to an array variable
    len_vect_diskrf_lb = ((first_lb * first_lb) + (secnd_lb * secnd_lb)) * 100;
    //! conversion from floating point to integer type
    len_vect_diskri_lb = (Uint16) len_vect_diskrf_lb;
    //! calculation of the additive variable for vector length calculation
    add_len_vect_lb = len_vect_diskrf_lb - (float32) len_vect_diskri_lb;
    //! specify array address
    len_vect_tablf_lb = &SQRT350[len_vect_diskri_lb];

    //! calculate the return value of the function
    return (*len_vect_tablf_lb
            + (add_len_vect_lb * (*(len_vect_tablf_lb + 1) - *len_vect_tablf_lb)));
}

/*!
 \brief calculate scalar current from six phase
 */
float32 CalculateScalarCurrentFrom6Phase(Model_Data_PMSM_S *md_l)
{
    //! Get value for calculate in square table
    float32 len_diskr_float_lb;
    //! Declaration of the variable len_vect_diskri_lb
    Uint32 len_diskr_int_lb;
    //! Declaration of vector length calculation variable
    float32 add_len_vect_lb;
    //! Declaration of the variable of vector length table calculation
    const float32 *len_vect_tabl_float_lb;

    //! Get value current for calculation in square
    len_diskr_float_lb = ((md_l->iu.fl * md_l->iu.fl)
            + (md_l->iv.fl * md_l->iv.fl) + (md_l->iw.fl * md_l->iw.fl)
            + (md_l->iu1.fl * md_l->iu1.fl) + (md_l->iv1.fl * md_l->iv1.fl)
            + (md_l->iw1.fl * md_l->iw1.fl)) * 100;
    //! Conversion from floating point to integer type
    len_diskr_int_lb = (Uint32) len_diskr_float_lb;
    //! Calculation of the additive variable for vector length calculation
    add_len_vect_lb = len_diskr_float_lb - (float32) len_diskr_int_lb;
    //! Specify array address
    len_vect_tabl_float_lb = &SQRT350[len_diskr_int_lb];
    //! Calculate the return value of the function
    return DIV_SQRT3_3
            * (*len_vect_tabl_float_lb
                    + (add_len_vect_lb
                            * (*(len_vect_tabl_float_lb + 1)
                                    - *len_vect_tabl_float_lb)));
}

/*!
 \brief Calculate condition of PMSM for forward
 */
void CalculateConditionPMSForward(Model_Data_PMSM_S *md_l, int32 calc_theta)
{
    //! Set forward direction for drive
    md_l->uu.fl = TABL_UU[calc_theta];
    md_l->uv.fl = TABL_UW[calc_theta];
    md_l->uw.fl = TABL_UV[calc_theta];
    md_l->uu1.fl = TABL_UU1[calc_theta];
    md_l->uv1.fl = TABL_UW1[calc_theta];
    md_l->uw1.fl = TABL_UV1[calc_theta];
}

/*!
 \brief Calculate condition of PMSM for backward
 */
void CalculateConditionPMSBackward(Model_Data_PMSM_S *md_l, int32 calc_theta)
{
    //! Decrement angle
    //! Set backward direction for drive
    md_l->uu.fl = TABL_UU[calc_theta];
    md_l->uv.fl = TABL_UV[calc_theta];
    md_l->uw.fl = TABL_UW[calc_theta];
    md_l->uu1.fl = TABL_UU1[calc_theta];
    md_l->uv1.fl = TABL_UV1[calc_theta];
    md_l->uw1.fl = TABL_UW1[calc_theta];
}
