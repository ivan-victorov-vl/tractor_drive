//###########################################################################
//
// ����:    	MainLedIndctn.h
//
// ��������:   	������������ ����: MainLedIndctn.c
//
//###########################################################################

#ifndef MAINLEDINDCTN_H_
#define MAINLEDINDCTN_H_


////////////////////// ���������� ����������� �������� //////////////////////
// ����������� �������� ���������� ����������� ��������������� ����������,
// ���	3 - ����� �����, 2 - ������� �����
#define	MIN_VAR_INCTN_Fl_3_2			0
// ������������ �������� ���������� ����������� ��������������� ����������,
// ���	3 - ����� �����, 2 - ������� �����
#define	MAX_VAR_INCTN_Fl_3_2			999.99


//////////////// ���������� �������� ������� � �������� /////////////////////
// ���������� �������� ������� � ������� VDHLIndctnVar
extern void VDHLIndctnVar(float32 *var_indctn_l, Uint16 *cnt_vdhl_l);
// ���������� �������� ������� � ������� VDHlOff
extern  void VDHlOff(void);


#endif
