//###########################################################################
//
// FILE:    Debug.h
//
// TITLE:   Debug board
//
//###########################################################################

#ifndef DEBUG_H_
#define DEBUG_H_


//! ����������� �������� (����������� �������� ��������� TRUE_VAL - �����, ����� FALSE_VAL)
#define FORWARD TRUE_VAL

//! ������� ����� ���� ���� U
#define ZERO_VALUE_I_PHASE_U 2048-109
//! ������� ����� ���� ���� V
#define ZERO_VALUE_I_PHASE_V 2048-97
//! ������� ����� ���� ���� W
#define ZERO_VALUE_I_PHASE_W 2048-103
//! ������� ����� ���� ���� U1
#define ZERO_VALUE_I_PHASE_U1 2048-101
//! ������� ����� ���� ���� V1
#define ZERO_VALUE_I_PHASE_V1 2048-104
//! ������� ����� ���� ���� W1
#define ZERO_VALUE_I_PHASE_W1 2048-98

//! ������� ����� ���������� ���� U
#define ZERO_VALUE_U_PHASE_U 2048
//! ������� ����� ���������� ���� V
#define ZERO_VALUE_U_PHASE_V 2048
//! ������� ����� ���������� ���� W
#define ZERO_VALUE_U_PHASE_W 2048
//! ������� ����� ���������� ���� U1
#define ZERO_VALUE_U_PHASE_U1 2048
//! ������� ����� ���������� ���� V1
#define ZERO_VALUE_U_PHASE_V1 2048
//! ������� ����� ���������� ���� W1
#define ZERO_VALUE_U_PHASE_W1 2048

//! ����������� ���������� UDC,����� (���������� ��� ������� ���������� DO1)
#define ENABLE_UDC_VOLTAGE 50

//! ����������� ��� ���������������� ������������ �������� �������
#define K_PROP 0.1
//! ����������� ��� ������������ ������������ �������� �������
#define K_INTEGR 0.000001

//! ������ � ���������� ������������� (���� ��������� ������ � ���������� �������������, �� ����� ������ �����������)
//#define MODEL_INTENSITY_SET TRUE_VAL

#endif /* DEBUG_H_ */
