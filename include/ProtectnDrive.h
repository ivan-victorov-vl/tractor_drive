//###########################################################################
//
// FILE:    ProtectnDrive.h
//
// TITLE:   Protectn Drive defenitions.
//
// NOTES:
//
//###########################################################################

#ifndef PROTECTNDRIVE_H_
#define PROTECTNDRIVE_H_


////////////////////// ����������� ������������ ������ //////////////////////
// ����������� ������������� ����� "BaseDrive.h"
#include "BaseDrive.h"


/////////////////////// ���������� ����� ������ //////////////////////////
// ��� ������ ������
typedef enum
{
	// ������ ���
	SUCCESS,
	// ���������� ������
	ERROR
} retval_t;
// ����������: � ������ ���� ������ ��� ������ �������, ��������� ��� �������.


////////////////////// ���������� ����������� �������� //////////////////////
// ������: DIV_�������_��������; ����������� ��������� ����� 1/2
#define DIV_1_2					0.5
// ������� �� ���������� �� ���������� �� ����� ����������� ����
#define KMAX_UDC_FROM_NOM		1.2
// ������� �� �������� ������� ���������� �� ����� ����������� ����
#define KMIN_UDC_FROM_NOM		0.65
// ������� �� ���������� �� ���������� �� ����� ����������� ����
#define KOVRLD_UDC_FROM_NOM		1.1
// ������� �� ���������� �� ���������� �� ����� ����������� ����
#define KMINWRNG_UDC_FROM_NOM 	0.85


//////////////// ���������� �������� ������� � �������� /////////////////////
// ���������� �������� ������� � ������� pMaxMotorIPrtctn
extern retval_t (*pMaxMotorIPrtctn)(float32 iu_l_a, float32 iv_l_a, float32 iw_l_a, float32 valmax_prtctn_l_a);
// ���������� �������� ������� � ������� pTimeIMotorPrtctn
extern retval_t (*pTimeIMotorPrtctn)(float32 istator_l, float32 ki_integral_l, float32 i_nom_l, float32 *i_intgrl_l, float32 activ_intgr_prtctn_l);
// ���������� �������� ������� � ������� pBreakPhasePrtctn
extern retval_t (*pBreakPhasePrtctn)(float32 urefu_l, float32 urefv_l, float32 urefw_l, float32 iu_l, float32 iv_l, float32 iw_l, float32 valmax_prtctn_l, float32 ku_multiply_l);
// ���������� �������� ������� � ������� pMaxUDCMotorPrtctn
extern retval_t (*pMaxUDCMotorPrtctn)(float32 udc_l, float32 udc_nom_max_l);
// ���������� �������� ������� � ������� pMinUDCMotorPrtctn
extern retval_t(*pMinUDCMotorPrtctn)(float32 udc_l, float32 udc_nom_min_l);
// ���������� �������� ������� � ������� pPressFaultMotorPrtctn
extern retval_t (*pPressFaultMotorPrtctn)(Uint16 press_fault_l);


#endif
