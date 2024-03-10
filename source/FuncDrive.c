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
#include "Smpl_table.h"
#include "BaseDrive.h"

void Stop(Model_Data_PMSM_S *md_la, Settng_Data_PMSM_S *sd_la, Flg_Cntrl_Drive_S *mf_la );
void CalcSinCos_0_90(float32 theta_lb, float32 *sin_lb, float32 *cos_lb);
void CalcSinCos_90_180(float32 theta_lb, float32 *sin_lb, float32 *cos_lb);
void CalcSinCos_180_270(float32 theta_lb, float32 *sin_lb, float32 *cos_lb);
void CalcSinCos_270_360(float32 theta_lb, float32 *sin_lb, float32 *cos_lb);
void Calc2To3Cos(float32 first_var_lb, float32 sec_var_lb, float32 *first_res_lb, float32 *sec_res_lb, float32 *third_res_lb);
void Calc3To2(float32 first_var_lb, float32 sec_var_lb, float32 third_var_lb, float32 *first_res_lb, float32 *sec_res_lb);
float32 ApprdFltr(float32 first_var_lb, float32 Ti_apprd_lb, float32 *integr_lb);
void (*CalcSinCos[4])(float32 theta_lb, float32 *sin_lb, float32 *cos_lb) = {&CalcSinCos_0_90, &CalcSinCos_90_180, &CalcSinCos_180_270, &CalcSinCos_270_360};
void (**pCalcSinCos)(float32 theta_lb, float32 *sin_lb, float32 *cos_lb) = &CalcSinCos[0];
void SpeedRef(float32 k_f_mul_ref_lb, float32 k_f_mul_plus_lb, float32 k_f_mul_minus_lb, float32 *k_f_mul_lb);
float32 CalcLengthVect2In(float32 first_lb, float32 secnd_lb);
float32 PI_Regltr(float32 cur_var_lb, float32 k_prprnl_lb, float32 k_integral_lb, float32 *integral_lb);
float32 PID_Regltr(PID_Rgltr_S *v_pid_r_lb);
void CalculateConditionPMS(Model_Data_PMSM_S *md_l);


void Stop(Model_Data_PMSM_S *md_la, Settng_Data_PMSM_S *sd_la, Flg_Cntrl_Drive_S *mf_la ) {

}


/*!
     \brief calculate sin and cos from degree 0-90
*/
void CalcSinCos_0_90(float32 theta_lb, float32 *sin_lb, float32 *cos_lb) {
	int16	theta_dtabl_lb;
	float32 add_angl_lb;
	const float32  *psin_90_lb;

	theta_dtabl_lb = (int16)theta_lb;
	psin_90_lb = &Tabl_sin_90[theta_dtabl_lb];
	add_angl_lb = theta_lb - (float32)theta_dtabl_lb;
	*sin_lb = *psin_90_lb + (add_angl_lb * (*(psin_90_lb + 1) - *psin_90_lb));
	psin_90_lb = &Tabl_sin_90[89];
	*cos_lb = *(psin_90_lb - theta_dtabl_lb) + ((1 - add_angl_lb) * ( *(psin_90_lb - (theta_dtabl_lb - 1)) - *(psin_90_lb - theta_dtabl_lb)));
}

/*!
     \brief calculate sin and cos from degree 90-180
*/
void CalcSinCos_90_180(float32 theta_lb, float32 *sin_lb, float32 *cos_lb) {
	int16	theta_dtabl_lb;
	float32 add_angl_lb;
	const float32  *psin_90_lb;

	theta_dtabl_lb = (int16)theta_lb;
	add_angl_lb = theta_lb - (float32)theta_dtabl_lb;
	psin_90_lb = &Tabl_sin_90[89];
	*sin_lb = *(psin_90_lb - (theta_dtabl_lb - 90) ) + ((1 - add_angl_lb) * (*(psin_90_lb - (theta_dtabl_lb - 91)) - *(psin_90_lb - (theta_dtabl_lb - 90))));
	psin_90_lb = &Tabl_sin_90[theta_dtabl_lb - 90];
	*cos_lb = -*psin_90_lb -  (add_angl_lb * ( *(psin_90_lb + 1) - *psin_90_lb));
}

/*!
    \brief calculate sin and cos from degree 180-270
*/
void CalcSinCos_180_270(float32 theta_lb, float32 *sin_lb, float32 *cos_lb) {
	int16	theta_dtabl_lb;
	float32 add_angl_lb;
	const float32  *psin_90_lb;


	theta_dtabl_lb = (int16)theta_lb;
	add_angl_lb = theta_lb - (float32)theta_dtabl_lb;
	psin_90_lb = &Tabl_sin_90[theta_dtabl_lb - 180];
	*sin_lb = -(*psin_90_lb + (add_angl_lb * ( *(psin_90_lb + 1) - *psin_90_lb)));
	psin_90_lb = &Tabl_sin_90[89];
	*cos_lb = -*(psin_90_lb - (theta_dtabl_lb - 180) ) - ((1 - add_angl_lb) * (*(psin_90_lb - (theta_dtabl_lb - 181)) - *(psin_90_lb - (theta_dtabl_lb - 180))));
}

/*!
    \brief calculate sin and cos from degree 270-360
 */
void CalcSinCos_270_360(float32 theta_lb, float32 *sin_lb, float32 *cos_lb) {
	int16	theta_dtabl_lb;
	float32 add_angl_lb;
	const float32  *psin_90_lb;


	theta_dtabl_lb = (int16)theta_lb;
	add_angl_lb = theta_lb - (float32)theta_dtabl_lb;
	psin_90_lb = &Tabl_sin_90[89];
	*sin_lb = -(*(psin_90_lb - (theta_dtabl_lb - 270) ) + ((1 - add_angl_lb) * (*(psin_90_lb - (theta_dtabl_lb - 271)) - *(psin_90_lb - (theta_dtabl_lb - 270)))));
	psin_90_lb = &Tabl_sin_90[theta_dtabl_lb - 270];
	*cos_lb = *psin_90_lb + (add_angl_lb * ( *(psin_90_lb + 1) - *psin_90_lb));
}

/*!
    \brief calculating the speed setter
 */
void SpeedRef(float32 k_f_mul_ref_lb, float32 k_f_mul_plus_lb, float32 k_f_mul_minus_lb, float32 *k_f_mul_lb) {
    //! if the current speed setting is greater than the set speed setting
    if (*k_f_mul_lb > k_f_mul_ref_lb) {
        //! calculation of the current task at decreasing acceleration
        *k_f_mul_lb -= k_f_mul_minus_lb;
    }

    //! if the current speed setting is less than the set speed setting
    if (*k_f_mul_lb  < k_f_mul_ref_lb) {
        //! calculation of the current job at higher acceleration
        *k_f_mul_lb +=  k_f_mul_plus_lb;
    }
}

/*!
    \brief aperiodic filter
*/
float32 ApprdFltr(float32 first_var_lb, float32  Ti_apprd_lb, float32 *integr_lb) {
	*integr_lb += (Ti_apprd_lb * (first_var_lb - *integr_lb));
	return (*integr_lb);
}

/*!
 *  \brief calculation of variable value after PI regulator
 */
float32 PI_Regltr(float32 cur_var_lb, float32 k_prprnl_lb, float32 k_integral_lb, float32 *integral_lb) {
    //! calculation of the integral component of the pi controller
    *integral_lb +=  cur_var_lb;
    //! calculation of the return value of the pi regulator function
    return ((cur_var_lb * k_prprnl_lb) + (k_integral_lb * *integral_lb));
}

/*!
 *  \brief PID controller calculation function
 *  Detailed description
 *  e(t) = SP(t) - PV(t)
 *  CO(t) = CObias + Kp * (e(t) + (1/Ti)*Integrl_t_0((e(theta)dtheta) - Td*((dPV(t))/dt)) )
 */
float32 PID_Regltr(PID_Rgltr_S *v_pid_r_lb) {
    static float32 prop_lb = 0, integr_lb = 0, different_lb = 0;

    prop_lb = v_pid_r_lb->error.fl;
    integr_lb += (1 / v_pid_r_lb->t_intgrl.fl) * v_pid_r_lb->error.fl * v_pid_r_lb->dt.fl;
    different_lb = -v_pid_r_lb->t_dfrntl.fl * (v_pid_r_lb->cur_var.fl - v_pid_r_lb->prvs_var.fl)/ v_pid_r_lb->dt.fl;
    v_pid_r_lb->cur_var.fl = v_pid_r_lb->cur_var.fl - v_pid_r_lb->prvs_var.fl;
    return (prop_lb + integr_lb + different_lb);
}


/*!
    \brief conversion from two-phase to three-phase system
*/
void Calc3To2(float32 first_var_lb, float32 sec_var_lb, float32 third_var_lb, float32 *first_res_lb, float32 *sec_res_lb) {
	*first_res_lb = first_var_lb;
	*sec_res_lb = DIV_1_SQRT3 * (sec_var_lb - third_var_lb);
}

/*!
    \brief conversion from three-phase to two-phase system
*/
void Calc2To3Cos(float32 first_var_lb, float32 sec_var_lb, float32 *first_res_lb, float32 *sec_res_lb, float32 *third_res_lb) {
	*first_res_lb = first_var_lb;
	*sec_res_lb = (DIV_SQRT3_2 * sec_var_lb) - (DIV_1_2 * first_var_lb);
	*third_res_lb = (-DIV_1_2 * first_var_lb) - (DIV_SQRT3_2 * sec_var_lb);
}

/*!
 *  \brief calculating the modulus of a vector by two input values
 */
float32 CalcLengthVect2In(float32 first_lb, float32 secnd_lb) {
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
    len_vect_diskri_lb = (Uint16)len_vect_diskrf_lb;
    //! calculation of the additive variable for vector length calculation
    add_len_vect_lb = len_vect_diskrf_lb - (float32)len_vect_diskri_lb;
    //! specify array address
    len_vect_tablf_lb = &SQRT175[len_vect_diskri_lb];

    //! calculate the return value of the function
    return (*len_vect_tablf_lb + (add_len_vect_lb * (*(len_vect_tablf_lb + 1) - *len_vect_tablf_lb)));
}

/*!
    \brief calculate condition of PMSM
 */
void CalculateConditionPMS(Model_Data_PMSM_S *md_l) {
    int32 calc_theta = ((int32)md_l->theta.fl%120)/10;
    md_l->uu.fl = TABL_UU[calc_theta];
    md_l->uv.fl = TABL_UV[calc_theta];
    md_l->uw.fl = TABL_UW[calc_theta];
    md_l->uu1.fl = TABL_UU1[calc_theta];
    md_l->uv1.fl = TABL_UV1[calc_theta];
    md_l->uw1.fl = TABL_UW1[calc_theta];
}
