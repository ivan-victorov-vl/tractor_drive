//###########################################################################
//
// FILE: ProtecnDrive.c
//
// TITLE: Protection drive support functions.
//
// NOTES:
//
//###########################################################################


////////////////////// ����������� ������������ ������ //////////////////////
// ����������� ������������� ����� PeripheralHeaderIncludes.h
#include "PeripheralHeaderIncludes.h"
// ������������ ������������� ����� ProtectnDrive.h
#include "ProtectnDrive.h"


/////////////////////////// ���������� ������� //////////////////////////////
// ���������� ������� ������ MaxMotorIPrtctn
retval_t MaxMotorIPrtctn(float32 iu_l_a, float32 iv_l_a, float32 iw_l_a, float32 valmax_prtctn_l_a);
// ���������� ��������� ������� ������ pMaxMotorIPrtctn
retval_t (*pMaxMotorIPrtctn)(float32 iu_l_a, float32 iv_l_a, float32 iw_l_a, float32 valmax_prtctn_l_a) = &MaxMotorIPrtctn;

// ���������� ������� ������ TimeIMotorPrtctn
retval_t TimeIMotorPrtctn(float32 istator_l, float32 ki_integral_l, float32 i_nom_l, float32 *i_intgrl_l, float32 activ_intgr_prtctn_l);
// ���������� ��������� ������� ������ pTimeIMotorPrtctn
retval_t (*pTimeIMotorPrtctn)(float32 istator_l, float32 ki_integral_l, float32 i_nom_l, float32 *i_intgrl_l, float32 activ_intgr_prtctn_l) = &TimeIMotorPrtctn;

// ���������� ������� ������ BreakPhasePrtctn
retval_t BreakPhasePrtctn(float32 urefu_l, float32 urefv_l, float32 urefw_l, float32 iu_l, float32 iv_l, float32 iw_l, float32 valmax_prtctn_l, float32 ku_multiply_l);
// ���������� ��������� ������� ������ pBreakPhasePrtctn
retval_t (*pBreakPhasePrtctn)(float32 urefu_l, float32 urefv_l, float32 urefw_l, float32 iu_l, float32 iv_l, float32 iw_l, float32 valmax_prtctn_l, float32 ku_multiply_l) = &BreakPhasePrtctn;

// ���������� ������� ������ pMaxUDCMotorPrtctn
retval_t MaxUDCMotorPrtctn(float32 udc_l, float32 udc_nom_max_l);
// ���������� ��������� ������� ������ pMaxUDCMotorPrtctn
retval_t (*pMaxUDCMotorPrtctn)(float32 udc_l, float32 udc_nom_max_l) = &MaxUDCMotorPrtctn;

// ���������� ������� ������ MinUDCMotorPrtctn
retval_t MinUDCMotorPrtctn(float32 udc_l, float32 udc_nom_min_l);
// ���������� ��������� ������� ������ pMinUDCMotorPrtctn
retval_t(*pMinUDCMotorPrtctn)(float32 udc_l, float32 udc_nom_min_l) = &MinUDCMotorPrtctn;

// ���������� ������� PressFaultMotorPrtctn
retval_t PressFaultMotorPrtctn(Uint16 press_fault_l);
// ���������� ��������� ������� pPressFaultMotorPrtctn
retval_t (*pPressFaultMotorPrtctn)(Uint16 press_fault_l) = &PressFaultMotorPrtctn;




////////////////////////// ������� ������ ��������� /////////////////////////
//----------------------------------------------------------------------------------------------------------------
// �������:  			MaxMotorIPrtctn
// ��������: 			�������� ������� "���������� ���� �� ����� �� ��� ���"
// ����:  	  			(��� ���� u, ��� ���� v, ��� ���� w, ������� �� ���������� ����)
// �����: 	  			(��������� �������� ������ �����������-������� ������)
// �����.����.�-���.:	(��� ������, ������ �� �����������-������� ������)(SUCCESS|ERROR))
// ������ ������: 		MaxMotorIPrtctn(float32 ��� ���� u, float32 ��� ���� v, float32 ��� ���� w, float32 ������� �� ���������� ����)
//----------------------------------------------------------------------------------------------------------------
retval_t MaxMotorIPrtctn(float32 iu_la, float32 iv_la, float32 iw_la, float32 valmax_prtctn_la)
{
	// ���������� ���������� ��������� ����������� - ������� ������
	retval_t StatMotorErr = SUCCESS;


	// ���������� ������� �� ���������� ���� � ������������� ����
	valmax_prtctn_la *= valmax_prtctn_la;
	// ���������� ������� ���������������� ����������� ������� ������
	if (((iu_la * iu_la) > valmax_prtctn_la) || ((iv_la * iv_la) > valmax_prtctn_la) ||
	((iw_la * iw_la) > valmax_prtctn_la))
	{
		// �������������� ����������� ������ �����������-������� ������
		StatMotorErr = ERROR;
	}

	// ���������� ��������� �������
	return StatMotorErr;
}



//----------------------------------------------------------------------------------------------------------------
// �������:  			TimeIMotorPrtctn
// ��������: 			�������� ������� "�����-������� ������"
// ����:  	  			(��� �������, ����������� �����, ����������� ���, &��������� ���������� �����-������� ������, ������� ������������ ������)
// �����: 	  			(��������� �������� ������ �����������-������� ������)
// �����.����.�-���.:	(��� ������, ������ �� �����������-������� ������)(SUCCESS|ERROR)
// ������ ������: 		TimeIMotorPrtctn(float32 ��� �������, float32 ����������� �����, float32 ����������� ���, float32 &��������� ���������� �����-������� ������, ������� ������������ ������)
//----------------------------------------------------------------------------------------------------------------
retval_t TimeIMotorPrtctn(float32 istator_la, float32 ki_sum_ti_la, float32 i_nom_la,  float32 *i_sum_ti_la, float32 activ_intgr_prtctn_la)
{
	// ���������� ���������� ���������
	retval_t StatMotorErr = SUCCESS;


	// ���������� ���������
	*i_sum_ti_la += ki_sum_ti_la * (i_nom_la - istator_la);

	// ���� �������� ��������� ������ 0
	if (*i_sum_ti_la <= 0)
		// �������� ��������
		*i_sum_ti_la = 0;

	// ���� �������� ������ �������������� ��������
	if (*i_sum_ti_la > activ_intgr_prtctn_la)
		StatMotorErr = ERROR;

	// ���������� ��������� �������
	return StatMotorErr;
}



//----------------------------------------------------------------------------------------------------------------
// �������:  			BreakPhasePrtctn
// ��������: 			�������� ������� "������ �� ������ ����"
// ����:  	  			(�������� ���������� ���� U, �������� ���������� ���� V, �������� ���������� ���� W, ���������� ��� ���� U, ���������� ��� ���� V, ������� ���������� ������ ����, ����������� ����������)
// �����: 	  			(��������� �������� ������ ������ �� ������ ���� U,V,W)
// �����.����.�-���.:	(��� ������, ����� ���� U, ����� ���� V, ����� ���� W)(SUCCESS|ERROR)
// ������ ������: 		BreakPhasePrtctn(float32 �������� ���������� ���� U, float32 �������� ���������� ���� V, float32 �������� ���������� ���� W, float32 ���������� ��� ���� U, float32 ���������� ��� ���� V, float32 ������� ���������� ������ ����, float32 ����������� ����������)
//----------------------------------------------------------------------------------------------------------------
retval_t BreakPhasePrtctn(float32 urefu_la, float32 urefv_la, float32 urefw_la, float32 iu_la, float32 iv_la, float32 iw_la, float32 valmax_prtctn_la, float32 ku_multiply_la)
{
	// ���������� ���������� ���������
	retval_t StatMotorErr = SUCCESS;


	// ��������� �������� ������ ����
	valmax_prtctn_la *= (ku_multiply_la * ku_multiply_la) * DIV_1_2;

	// �������� �� ����� ���� U
	if ( ( (urefu_la * urefu_la) - (iu_la * iu_la) ) > valmax_prtctn_la)
		// ��������� ���������: ����� ���� U
		StatMotorErr = ERROR;

	// �������� �� ����� ���� V
	if ( ( (urefv_la * urefv_la) - (iv_la * iv_la) ) > valmax_prtctn_la)
		// ��������� ���������: ����� ���� V
		StatMotorErr = ERROR;

	// �������� �� ����� ���� W
	if ( ( (urefw_la * urefw_la) - (iw_la * iw_la) ) > valmax_prtctn_la)
		// ��������� ���������: ����� ���� W
		StatMotorErr = ERROR;

	// ���������� ��������� �������
	return StatMotorErr;
}



//----------------------------------------------------------------------------------------------------------------
// �������:  			MaxUDCMotorPrtctn
// ��������: 			�������� ������� "���������� ����������"
// ����:  	  			(���������� ����������, ������� �� ���������� ����������� ����������)
// �����: 	  			(��������� �������� �� ���������� ����������)
// �����.����.�-���.:	(��� ������, ������ �� ���������� ����������)(SUCCESS|ERROR)
// ������ ������: 		MaxUDCMotorPrtctn(float32 ���������� ����������, float32 ������� �� ���������� ����������� ����������)
//----------------------------------------------------------------------------------------------------------------
retval_t MaxUDCMotorPrtctn(float32 udc_la, float32 udc_nom_max_la)
{
	// ���������� ���������� ���������
	retval_t StatMotorErr = SUCCESS;


	// �������� �� ���������� �� ����������� ����������
	if (udc_la > (udc_nom_max_la * KMAX_UDC_FROM_NOM))
		// ��������� ��������� : ���������� �� ������������� ����������
		StatMotorErr = ERROR;

	// ���������� ��������� �������
	return StatMotorErr;
}



//----------------------------------------------------------------------------------------------------------------
// �������:  			MinUDCMotorPrtctn
// ��������: 			�������� ������� "�������� ������ ����������"
// ����:  	  			(���������� ����������, ������� �� ������� ������)
// �����: 	  			(��������� �������� �� �������� ������ ����������)
// �����.����.�-���.:	(��� ������, ������ �� �������� ������ ����������)(SUCCESS|ERROR)
// ������ ������: 		MinUDCMotorPrtctn(float32 ���������� ����������, float32 ������� �� ������� ������ ����������)
//----------------------------------------------------------------------------------------------------------------
retval_t MinUDCMotorPrtctn(float32 udc_la, float32 udc_nom_min_la)
{
	// ���������� ���������� ���������
	retval_t StatMotorErr = SUCCESS;


	// �������� �� ���������� �� ����������� ����������
	if (udc_la < (udc_nom_min_la * KMIN_UDC_FROM_NOM))
		// ��������� ��������� �������� : ������� ������ ����������
		StatMotorErr = ERROR;

	// ���������� ��������� �������
	return StatMotorErr;
}



//----------------------------------------------------------------------------------------------------------------
// �������:  			PressFaultMotorPrtctn
// ��������: 			�������� ������� "������ ������"
// ����:  	  			(��������� ������ ������)
// �����: 	  			(��������� �������� �� ������� ������ ������)
// �����.����.�-���.:	(��� ������, ������ ������ ������)(SUCCESS|ERROR)
// ������ ������: 		PressFaultM6otorPrtctn(float32 ��������� ������ ������)
//----------------------------------------------------------------------------------------------------------------
retval_t PressFaultMotorPrtctn(Uint16 press_fault_la)
{
	// ���������� ���������� ���������
	retval_t StatMotorErr = SUCCESS;


	// ���� ������ ������ ������
	if (press_fault_la)
		// ��������� ��������� ��� ������ ������ ������
		StatMotorErr = ERROR;

	// ���������� ��������� �������
	return StatMotorErr;
}
