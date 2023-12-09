//###########################################################################
//
// FILE:    FuncDrive.h
//
// TITLE:   Functions drive definitions
//
// NOTES:
//
//###########################################################################

#ifndef FUNCDRIVE_H_
#define FUNCDRIVE_H_


////////////////////// ����������� ������������ ������ //////////////////////
// ����������� ������������� ����� "BaseDriveUsr.h"
#include "BaseDrive.h"
// ����������� ������������� ����� "Flg_Cntrl_Drive_S.h"
#include "FlagParamDrive.h"


////////////////////// ���������� ����������� �������� //////////////////////
// ���������� ������� �� ������ ������
#define	FULL_DSKRT			359.999
// ��������� ���������� ������� ��� ���������� ������� (1 / (����� ����� * 2 ))
#define CONST_ACCEL 		18181.81818181818
// ������: DIV_�������_��������; ����������� ��������� ����� 1/SQRT(3)
#define DIV_1_SQRT3			0.5773502691896259
// ������: DIV_�������_��������; ����������� ��������� ����� SQRT(3)/2
#define DIV_SQRT3_2			0.8660254037844386
// ������: DIV_�������_��������; ����������� ��������� ����� 2/SQRT(3)
#define DIV_2_SQRT3			1.154700538379252
// ������: DIV_�������_��������; ����������� ��������� ����� 1/2
#define DIV_1_2				0.5
// ������: DIV_�������_��������; ����������� ��������� ����� 1/90
#define DIV_1_90			1 / 90
// ������� ���������� �� ����
#define KOVRLD_I_FROM_NOM	1.1
// ������: MUL_���������.1_���������.2; ����������� ��������� ����� 1*10
#define MUL_1_10 			10
// ����������� ������������ im �������� �� ����� 30 ��
#define KIM_EQLZTN			1 / (30 * 10 * 1.804402742692169)
// ������� ������������� �������� ����������� ����
#define MAX_IR				0.23
// ����� ������� � n(min) �� n(nom)
#define ACCEL_UP			5
// ����� ���������� � n(nom) �� n(min)
#define ACCEL_DOWN			5
// ����������� �������� � ��/���
#define NOM_SPEED			1000
// ����������� �������� ���� �������
#define NOM_I_STATOR		25
// ����� ��� �������
#define NUMB_PAIR_POLES		3
// ������: DIV_�������_��������; ����������� ��������� ����� 1/360
#define K_1_DIV_360		 	0.0027777777777778
// ������: DIV_�������_��������; ����������� ��������� ����� 1/4
#define K_1_DIV_4			0.25




//////////////// ���������� �������� ������� � �������� /////////////////////
// ���������� ������� Stop
extern void Stop(Model_Data_PMSM_S *md_la, Settng_Data_PMSM_S *sd_la, Flg_Cntrl_Drive_S *mf_la );
// ���������� �������� ������� � ������� CalcSinCos
extern void (**pCalcSinCos)(float32 theta_lb, float32 *sin_lb, float32 *cos_lb);
// ���������� �������� ������� � ������� CalcIm
extern float32 CalcIm(float32 kf_multiply_lb, float32 kim_eqlztn_lb, float32 *eqlztn_im_lb);
// ���������� �������� ������� � ������� ApprdFltr
extern float32 ApprdFltr(float32 first_var_lb, float32 Ti_apprd_lb, float32 *integr_lb);
// ���������� �������� ������� � ������� Calc2To3Cos
extern void Calc2To3Cos(float32 first_var_lb, float32 sec_var_lb, float32 *first_res_lb, float32 *sec_res_lb, float32 *third_res_lb);
// ���������� �������� ������� � ������� Calc3To2
extern void Calc3To2(float32 first_var_lb, float32 sec_var_lb, float32 third_var_lb, float32 *first_res_lb, float32 *sec_res_lb);
// ���������� �������� ������� � ������� SpeedRef
extern void SpeedRef(float32 k_f_mul_ref_lb, float32 k_f_mul_plus_lb, float32 k_f_mul_minus_lb, float32 *k_f_mul_lb);
// ���������� �������� ������� � ������� CalcLengthVect2In
extern float32 CalcLengthVect2In(float32 first_lb, float32 secnd_lb);
// ���������� �������� ������� � ������� PID_Regltr
extern float32 PID_Regltr(PID_Rgltr_S *v_pid_r_lb);
// ���������� �������� ������� � ������� CalcSpeedRtr
extern float32 CalcSpeedRtr(float32 theta_rtr_lb, float32 *ptheta_rtr_lb,  float32 *pcalc_speed_rez_lb);


#endif
