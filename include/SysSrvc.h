//###########################################################################
//
// FILE:    SysSrvc.h
//
// TITLE:   System service defenitions.
//
// NOTES:
//
//###########################################################################

#ifndef SYSSRVC_H_
#define SYSSRVC_H_


////////////////////// ���������� ����������� �������� //////////////////////
// ������� ���������� � ��
#define FRQ_HZ_PRCSR	150000000
// ��������� ���������� 	LED 1
#define	LED1_inv_clear 	GpioDataRegs.GPBCLEAR.bit.GPIO48 = 1;
// ���������� ���������� 	LED 1
#define	LED1_inv_set   	GpioDataRegs.GPBSET.bit.GPIO48   = 1;
// ��������� ���������� 	LED 2
#define	LED2_inv_clear	GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1;
// ���������� ���������� 	LED 2
#define	LED2_inv_set   	GpioDataRegs.GPBSET.bit.GPIO49   = 1;
// ��������� ���������� 	LED 1
#define	LED1_inv_status	GpioDataRegs.GPBDAT.bit.GPIO48
// ��������� ���������� 	LED 2
#define	LED2_inv_status	GpioDataRegs.GPBDAT.bit.GPIO49
// ��������� ���������� 	LED 1
#define OK_S_ON 		GpioDataRegs.GPCCLEAR.bit.GPIO66 = 1;
// ���������� ���������� 	LED 1
#define	OK_S_OFF   		GpioDataRegs.GPCSET.bit.GPIO66   = 1;
// ��������� ���������� 	LED 2
#define	ERR_S_ON		GpioDataRegs.GPCCLEAR.bit.GPIO67 = 1;
// ���������� ���������� 	LED 2
#define	ERR_S_OFF   	GpioDataRegs.GPCSET.bit.GPIO67   = 1;
// ��������� ������� ������ "�����" ������
#define	UP_STATUS	 	GpioDataRegs.GPBDAT.bit.GPIO63
// ��������� ������� ������ "����" ������
#define	DOWN_STATUS	 	GpioDataRegs.GPBDAT.bit.GPIO62
// ��������� ������� ������ "�����" ������
#define	LEFT_STATUS	 	GpioDataRegs.GPBDAT.bit.GPIO61
// ��������� ������� ������ "������" ������
#define	RIGHT_STATUS 	GpioDataRegs.GPBDAT.bit.GPIO60
// ��������� ������� ������ "�����" ������
#define	SEL_STATUS	 	GpioDataRegs.GPBDAT.bit.GPIO59
// ��������� ������� ������� ������ "����"
#define	EXT_START		GpioDataRegs.GPBDAT.bit.GPIO53
// ��������� ������� ������� ������ "����"
#define	EXT_STOP		GpioDataRegs.GPBDAT.bit.GPIO52
// ������������� ���������� ������ � ������ ������
#define	N_CNT_FLTR_MAX	32000
// ����������� ���������� ������ � ������ ������
#define	N_CNT_FLTR_MIN	1000
// ������: DIV_�������_��������; ����������� ��������� ����� 1/6
#define DIV_1_6		0.1666666666666667


//////////////// ���������� �������� ������� � �������� /////////////////////
// ���������� �������� ������� � ������� TimeDelay
extern void TimeDelaySys(float32 time_in_sec_l);
// ���������� �������� ������� � ������� Init_GPIO_0_5_in_PWM
extern void Init_GPIO_0_5_in_PWM(void);
// ���������� �������� ������� � ������� HandlrBttn
extern Uint16 HandlrBttn(Uint16 push_l);
// ���������� �������� ������� � ������� LimitVar
extern void LimitVar(float32 min_var, float32 max_var, float32 *var_lim);
// ���������� �������� ������� � ������� FltrMas6Var
float32 FltrMas6Var(float32 cur_var, Uint16 *cur_mas, float32 *pmas_var);


/////////////////////// ���������� �������� ������ //////////////////////////
// ��������� ������ 32-������� �����
typedef union
{
 float32 fl;
 Uint32  uint;
} B32_Numb_S;


#endif
