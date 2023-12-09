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
float32 CalcIm (float32 kf_multiply_lb, float32 kim_eqlztn_lb, float32 *eqlztn_im_lb);
void (*CalcSinCos[4])(float32 theta_lb, float32 *sin_lb, float32 *cos_lb) = {&CalcSinCos_0_90, &CalcSinCos_90_180, &CalcSinCos_180_270, &CalcSinCos_270_360};
void (**pCalcSinCos)(float32 theta_lb, float32 *sin_lb, float32 *cos_lb) = &CalcSinCos[0];
void SpeedRef(float32 k_f_mul_ref_lb, float32 k_f_mul_plus_lb, float32 k_f_mul_minus_lb, float32 *k_f_mul_lb);
float32 CalcLengthVect2In(float32 first_lb, float32 secnd_lb);
float32 PID_Regltr(PID_Rgltr_S *v_pid_r_lb);
float32 CalcSpeedRtr(float32 theta_rtr_lb, float32 *ptheta_rtr_lb,  float32 *pcalc_speed_rez_lb);

void Stop(Model_Data_PMSM_S *md_la, Settng_Data_PMSM_S *sd_la, Flg_Cntrl_Drive_S *mf_la )
{

}


void CalcSinCos_0_90(float32 theta_lb, float32 *sin_lb, float32 *cos_lb)
{
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


void CalcSinCos_90_180(float32 theta_lb, float32 *sin_lb, float32 *cos_lb)
{
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


void CalcSinCos_180_270(float32 theta_lb, float32 *sin_lb, float32 *cos_lb)
{
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


void CalcSinCos_270_360(float32 theta_lb, float32 *sin_lb, float32 *cos_lb)
{
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


void SpeedRef(float32 k_f_mul_ref_lb, float32 k_f_mul_plus_lb, float32 k_f_mul_minus_lb, float32 *k_f_mul_lb)
{


}


float32 ApprdFltr(float32 first_var_lb, float32  Ti_apprd_lb, float32 *integr_lb)
{
	*integr_lb += (Ti_apprd_lb * (first_var_lb - *integr_lb));
	return (*integr_lb);
}


float32 PID_Regltr(PID_Rgltr_S *v_pid_r_lb)
{

}


float32 CalcIm(float32 kf_multiply_lb, float32 kim_eqlztn_lb, float32 *eqlztn_im_lb)
{

}


void Calc3To2(float32 first_var_lb, float32 sec_var_lb, float32 third_var_lb, float32 *first_res_lb, float32 *sec_res_lb)
{
	*first_res_lb = first_var_lb;
	*sec_res_lb = DIV_1_SQRT3 * (sec_var_lb - third_var_lb);
}


void Calc2To3Cos(float32 first_var_lb, float32 sec_var_lb, float32 *first_res_lb, float32 *sec_res_lb, float32 *third_res_lb)
{
	*first_res_lb = first_var_lb;
	*sec_res_lb = (DIV_SQRT3_2 * sec_var_lb) - (DIV_1_2 * first_var_lb);
	*third_res_lb = (-DIV_1_2 * first_var_lb) - (DIV_SQRT3_2 * sec_var_lb);
}


float32 CalcLengthVect2In(float32 first_lb, float32 secnd_lb)
{
	float32 len_vect_diskrf_lb;
	Uint16 len_vect_diskri_lb;
	float32 add_len_vect_lb;
	const float32 *len_vect_tablf_lb;

	len_vect_diskrf_lb = ((first_lb * first_lb) + (secnd_lb * secnd_lb)) * 100;
	len_vect_diskri_lb = (Uint16)len_vect_diskrf_lb;
	add_len_vect_lb = len_vect_diskrf_lb - (float32)len_vect_diskri_lb;
	len_vect_tablf_lb = &SQRT175[len_vect_diskri_lb];

	return (*len_vect_tablf_lb + (add_len_vect_lb * (*(len_vect_tablf_lb + 1) - *len_vect_tablf_lb)));
}


float32 CalcSpeedRtr(float32 theta_rtr_lb, float32 *ptheta_rtr_lb,  float32 *pcalc_speed_rez_lb)
{
	static Uint16 cnt_speed_lb = 0, cnt_speed_fltr_lb = 0;
	static float32 calc_speed_sum_lb = 0, calc_speed_rez_lb = 0;

	cnt_speed_lb++;
	*(ptheta_rtr_lb + 1) = theta_rtr_lb;
 	if (((*(ptheta_rtr_lb + 1) - *ptheta_rtr_lb) < - 2) || ((*(ptheta_rtr_lb + 1) - *ptheta_rtr_lb) > 2))
 	{
 		if ((*(ptheta_rtr_lb + 1) - *ptheta_rtr_lb) < - (FULL_DSKRT - 2))
 		calc_speed_sum_lb += (*(ptheta_rtr_lb + 1) + (FULL_DSKRT - *ptheta_rtr_lb));
 		if ((*(ptheta_rtr_lb + 1) - *ptheta_rtr_lb) > (FULL_DSKRT - 2))
 		calc_speed_sum_lb += (*(ptheta_rtr_lb + 1) - (FULL_DSKRT - *ptheta_rtr_lb));
 		*ptheta_rtr_lb = *(ptheta_rtr_lb + 1);
	}
 	else
 	{
 		calc_speed_sum_lb += (*(ptheta_rtr_lb + 1) - *ptheta_rtr_lb);
 		*ptheta_rtr_lb = *(ptheta_rtr_lb + 1);
 	}
	if (cnt_speed_lb > FULL_DSKRT)
	{
		cnt_speed_lb = 0;
		*ptheta_rtr_lb = *(ptheta_rtr_lb + 1) = theta_rtr_lb;
		calc_speed_rez_lb = calc_speed_sum_lb * K_1_DIV_360 *  NUMB_PAIR_POLES;
		calc_speed_sum_lb = 0;
		cnt_speed_fltr_lb++;
		if (cnt_speed_fltr_lb > 3) cnt_speed_fltr_lb = 0;
	}
	if ((calc_speed_rez_lb > 1.1) || (calc_speed_rez_lb < -1.1))
		calc_speed_rez_lb = *(pcalc_speed_rez_lb + cnt_speed_fltr_lb);
	*(pcalc_speed_rez_lb + cnt_speed_fltr_lb) = calc_speed_rez_lb;

	return	 ((*pcalc_speed_rez_lb + *(pcalc_speed_rez_lb + 1) + *(pcalc_speed_rez_lb + 2) + *(pcalc_speed_rez_lb + 3)) * K_1_DIV_4);
}

