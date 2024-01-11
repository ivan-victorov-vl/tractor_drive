//###########################################################################
//
// FILE:    	BaseDrUsr.h
//
// TITLE:   	BaseDrUsr.c header file
//
//###########################################################################

#ifndef BASEDRIVE_H_
#define BASEDRIVE_H_


////////////////////// ����������� ������������ ������ //////////////////////
// ����������� ������������� ����� "SysSrvc.h"
#include "SysSrvc.h"
// ����������� ������������� ����� "Flg_Cntrl_Drive_S.h"
#include "FlagParamDrive.h"
//  ����������� ������������� ����� "RegParamDrive.h"
#include "RegParamDrive.h"


////////////////////// ���������� ����������� �������� //////////////////////
// ������: DIV_�������_��������; ����������� ��������� ����� 4096/360
#define DIV_4096_360	11.37777777777778
// ������: DIV_�������_��������; ����������� ��������� ����� 1/360
#define DIV_1_360	0.0027777777777778
// ������: DIV_�������_��������; ����������� ��������� ����� 3/360
#define DIV_3_360	0.0083333333333333
// ���������������� ����������� ��� ���������� ��������� ������
#define K_PRPRTNL_PSTN	0.0077
// ���������� ������� ��� ���������� ��������� ������ ��� ������������ ����� �������������
#define T_INTGRL_PSTN	7
// ���������� ������� ����������������� ������������ ��� ���������� ��������� ������
#define T_DFRNTNL_PSTN	99999999999


///////////////////////////  ���������������� ///////////////////////////////
// ����������� ���������� ��������� �������� ����
// 1-�� �����		f - float
//					s -��������� ���������
// 2-�� �����		p - ��������� �� ���������
//					f - float
// 3-� �����		s - ���������
//					p - ��������� �� ���������
// 4-� �����		l - ��������� ���������
//					f - ����
// 					s - ���������
// 5-� �����		a - ������� ������, ��� (������� - 0-�� �������), a - 1-�� �������
//					l - ��������� ���������
//
// ��������� �����	a - 1-�� ������� ������
// 					b - 2-�� ������� ������
//
// ���������������� ��������� md_l -> a.fl
#define fpsl(a)	 			(md_l->a.fl)
// ���������������� ��������� sd_l -> a.fl
#define sfpsl(a)			(sd_l->a.fl)
// ���������������� ��������� md_la -> a.fl
#define fpsla(a)	 		(md_la->a.fl)
// ���������������� ��������� sd_l -> a.fl
#define sfpsla(a)			(sd_la->a.fl)
// ���������������� ��������� md_lb -> a.fl
#define fpslb(a)	 		(md_lb->a.fl)
// ���������������� ��������� sd_l -> a.fl
#define sfpslb(a)			(sd_lb->a.fl)
// ���������������� ��������� mf_l -> a.fl
#define fpsfl(a)  			(mf_l->a.fl)
// ���������������� ��������� mf_la -> a.fl
#define fpsfla(a) 			(mf_la->a.fl)
// ���������������� ��������� mf_lb -> a.fl
#define fpsflb(a)  			(mf_l->a.fl)



//----------------------------------------------------------------------------------------------------------------
// ������ ���������: 					(������ �� )
// �������� ����������������� ������: 	��������� ��� ����������
// ������ � �������� 					������ / ������
//----------------------------------------------------------------------------------------------------------------
typedef struct
{
	// ������� ����������
	B32_Numb_S cur_var;
	// ���������� ����������
	B32_Numb_S prvs_var;
	// ���������������� ����������� ��� ����������
	B32_Numb_S k_prprtnl;
	// ������������ ����������� ��� ����������
	B32_Numb_S k_intgrl;
	// �������� ���������������� ����� ��� ����������
	B32_Numb_S p_intgrl;
	// �������� ������������ ����� ��� ����������
	B32_Numb_S i_intgrl;
	// ���������������� ����������� ��� ����������
	B32_Numb_S k_dfrntl;
} PID_Rgltr_S;


/*
 * \brief Inverter model parameter group
 */
typedef struct
{
	//! set freauency
	B32_Numb_S k_f_mul_ref;
	//! current motor speed
	B32_Numb_S k_f_mul;
	//! nominal motor current
	B32_Numb_S isnom;
	//! current stator
	B32_Numb_S is;
	//! current phase u
	B32_Numb_S iu;
	//! current phase v
	B32_Numb_S iv;
	//! current phase w
	B32_Numb_S iw;
	//! set rotation angle
	B32_Numb_S theta;
	//! incremental part for acceleration from n(min) to n(nom)
	B32_Numb_S k_f_mul_plus;
	//! incremental part for deceleration from n(nom) to n(min)
	B32_Numb_S k_f_mul_minus;
	//! current value of rotor position
	B32_Numb_S cur_pstn_rtr;
	//! phase voltage U
	B32_Numb_S uu;
	//! phase voltage V
	B32_Numb_S uv;
	//! phase voltage W
	B32_Numb_S uw;
	//! position rotor of structure PID regulator
	PID_Rgltr_S pstn_rtr;
    //! voltage  phase A first invertor
	B32_Numb_S uac_is_1_0;
	//! voltage  phase B first invertor
	B32_Numb_S uac_is_2_0;
	//! voltage  phase C first invertor
	B32_Numb_S uac_is_3_0;
	//! voltage  phase A second invertor
	B32_Numb_S uac_is_1_1;
    //! voltage  phase B second invertor
	B32_Numb_S uac_is_2_1;
    //! voltage  phase B second invertor
	B32_Numb_S uac_is_3_1;
    //! level voltage DC
	B32_Numb_S udc;
    //! level temperature
	B32_Numb_S temp;
    //! level current assignment
	B32_Numb_S izad_20_ma;
    //! level frequency assignment
	B32_Numb_S fzad_20_ma;
    //! current phase A first invertor
	B32_Numb_S i_os_1_0;
    //! current phase B first invertor
	B32_Numb_S i_os_2_0;
    //! current phase C first invertor
	B32_Numb_S i_os_3_0;
	//! current phase A second invertor
	B32_Numb_S i_os_1_1;
    //! current phase B second invertor
	B32_Numb_S i_os_2_1;
    //! current phase B third invertor
	B32_Numb_S i_os_3_1;
} Model_Data_PMSM_S;


//----------------------------------------------------------------------------------------------------------------
// ������ ���������: 					( ������ �� )
// �������� ����������������� ������: 	������ ��������� ��������������� �������
// ������ � �������� 					������ / ������
//----------------------------------------------------------------------------------------------------------------
typedef struct
{
	// ����� ������� ������� �� 0 �� ������������ �������� � ���.
	B32_Numb_S accel_sec_up;
	// ����� ���������� ������� �� ������������ �������� �� 0 � ���.
	B32_Numb_S accel_sec_down;
	// �������� �������� �������� �������
	B32_Numb_S real_ref;
	// ����������� �������� �� ��������� �������� �������� � �������������
	float32 k_real_to_mul_ref;
	// ����������� �������� �� �������������� �������� �������� � ��������
	B32_Numb_S k_mul_to_real_ref;
	// �������� �������� �������� �������
	B32_Numb_S real_frq;
	// �������� �������� ���� ������� ���������
	B32_Numb_S real_cur_i_sttr;
	// ����������� �������� �� �������������� �������� ���� � ��������
	B32_Numb_S k_mul_to_real_i_sttr;
	// ����������� �������� �� �������������� ��������� ������ � ��������
	float32 k_diskr_to_real_i_pstn_rtr;
	// �������� �������� ����� ����������� ����
	B32_Numb_S real_udc;
	// ����������� �������� �� �������������� �������� ���������� � ��������
	float32 k_mul_to_real_udc;
	// �������� ������� � �������� ���������
	float32 k_mul_ext_ref;
	// ���������� �������� �������� ��������� ������
	float32 diskr_cur_pstn_rtr;
	// ���������� �������������� ��� ���������� ��������� ������
	B32_Numb_S const_integr_pid_reg_pstn_rtr;
	// ���������� ����������������� ��� ���������� ��������� ������
	B32_Numb_S const_differntl_pid_reg_pstn_rtr;
} Settng_Data_PMSM_S;


//----------------------------------------------------------------------------------------------------------------
// ������ ���������: 					( ������ �� )
// �������� ����������������� ������: 	������ ���������� � ��������� ��������������� �������
// ������ � �������� 					������ / ������
//----------------------------------------------------------------------------------------------------------------
typedef struct
{
	// ������ ������ ���������� ���������������� �������
	Model_Data_PMSM_S md;
	// ����������� ������ ������ ���������� ���������������� �������
	Settng_Data_PMSM_S sd;
} Data_PMSM_S;


//----------------------------------------------------------------------------------------------------------------
// ������ ���������: 					(�������� ��������� ������������ ���������� �� )
// �������� ����������������� ������: 	������ ��� ��������� ������������ ���������� ��������������� �������
// ������ � �������� 					������ / ������
//----------------------------------------------------------------------------------------------------------------
typedef struct
{
	// ������ �� ������������� ��������������� �������
	B32_Numb_S sub_theta_md;
	// ��������� ������ ��������������� �������
	float32 pstn_rtr_md;
	// ��������� �������� ����������
	float32 *pbrws;
} Brws_Param_Drive;


//////////////// DECLARATION OF EXTERNAL ACCESS TO FUNCTIONS /////////////////////
//! declaration of external access to a function PMSMotorFuncScalInit
extern void PMSMotorFuncScalInit(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l);
//! declaration of external access to a function PMSMotorFuncReset
extern void PMSMotorFuncReset(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l);
//! declaration of external access to a function PMSMotorFuncScal
extern void PMSMotorFuncScal(Model_Data_PMSM_S *md_la, Flg_Cntrl_Drive_S *mf_la, Brws_Param_Drive *bpd_la);
//! declaration of external access to a function CntrlDrive
extern void CntrlDrive(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l, Brws_Param_Drive *bpd_l);

#endif
