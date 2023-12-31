//###########################################################################
//
// ����:    	FlagParamDrive.h
//
// ��������:   	���� ����������� ��������� ������ ������
//
//###########################################################################


#ifndef FLAGPARAMDRIVE_H_
#define FLAGPARAMDRIVE_H_



/////////////////////// ���������� �������� ������ //////////////////////////
//----------------------------------------------------------------------------------------------------------------
// ������ ���������: 					�����
// �������� ����������������� ������: 	����� ���������� ���������������� �������
// ����� ��������:  					1
// ������ � �������� 					������ / ������
//-----------------------------------------------------------------------------------------------------------------
typedef struct
{
	// 0  ���� ��������������� ������� 0 - ���������, 1 - ��������
	Uint16 net_drv :1;
	// 1  ���� ��������������� �������:  0 - ����, 1 - ����
	Uint16 strt_drv : 1;
	// 2  ������� ��������������� �������: 0 - ����, 1 - �������
	Uint16 stp_drv : 1;
	// 3  ������� ������� ��������: 0 - ������, 1 - ����������
	Uint16 ext_spd : 1;
	// 15 : 4 ���������������
	Uint16 rsvd : 12;
} Flg_Adr01_Bits_S;


//----------------------------------------------------------------------------------------------------------------
// ������ ���������: 					�����
// �������� ����������������� ������: 	����� ������ 1-���  ��������
// ������ � �������� 					������ / ������
//----------------------------------------------------------------------------------------------------------------
typedef union
{
	Uint16               all;
	Flg_Adr01_Bits_S 	 bits;
} Flg_Adr01_Reg_S;


//----------------------------------------------------------------------------------------------------------------
// ������ ���������: 					�����
// �������� ����������������� ������: 	����� ���������� ���������������� �������
// ����� ��������:  					2
// ������ � �������� 					������
//-----------------------------------------------------------------------------------------------------------------
typedef struct
{
	// 0  ���� ��������������� ������� 0 - ���������, 1 - ��������
	Uint16 net_drv :1;
	// 1  ���������� ������ ��������������� �������: 0 - ���������, 1 - ��������
	Uint16 read_drv : 1;
	// 2 ������ ��������������� �������: 0 - ���������, 1 - ��������
	Uint16 wrk_drv : 1;
	// 3 ���� ��������������� �������:  0 - ����, 1 - ����
	Uint16 strt_drv : 1;
	// 4 ������� ��������������� �������: 0 - ����, 1 - �������
	Uint16 stp_drv : 1;
	// 5 ������ ��������������� �������: 0 - ������ �����������, 1 - ��������� ������
	Uint16 err_drv : 1;
	// 6 ������ ��������������� ������� �� �����������-������� ������: 0 - ������ �����������, 1 - ��������� ������
	Uint16 err_mi_drv : 1;
	// 7 ������ ��������������� ������� �� ������ ��������: 0 - ������ �����������, 1 - ��������� ������
	Uint16 err_trnstr_drv : 1;
	// 15:7 ���������������
	Uint16 rsvd : 9;
} Flg_Adr02_Bits_S;


//----------------------------------------------------------------------------------------------------------------
// ������ ���������: 					�����
// �������� ����������������� ������: 	����� ������ 2-���  ��������
// ������ � �������� 					������ / ������
//----------------------------------------------------------------------------------------------------------------
typedef union
{
	Uint16               all;
	Flg_Adr02_Bits_S 	 bits;
} Flg_Adr02_Reg_S;


//----------------------------------------------------------------------------------------------------------------
// ������ ���������: 					�����
// �������� ����������������� ������: 	����� ���������� ���������������� �������
// ����� ��������:  					3
// ������ � �������� 					������ / ������
//-----------------------------------------------------------------------------------------------------------------
typedef struct
{
	// 0 ���� ������������ ������ SEL: 0 - ������ �� ���������, 1 - ������ ���������
	Uint16 sel:1;
	// 1 ���� ������������ ������ �����: 0 - ������ �� ���������, 1 - ������ ���������
	Uint16  up:1;
	// 2 ���� ������������ ������ ����: 0 - ������ �� ���������, 1 - ������ ���������
	Uint16  down:1;
	// ����������������� �����
    Uint16  rsvd : 13;
} Flg_Adr03_Bits_S;


//----------------------------------------------------------------------------------------------------------------
// ������ ���������: 					�����
// �������� ����������������� ������: 	����� ������ 3-���  ��������
// ������ � �������� 					������ / ������
//----------------------------------------------------------------------------------------------------------------
typedef union
{
	Uint16               all;
	Flg_Adr03_Bits_S 	 bits;
} Flg_Adr03_Reg_S;


//----------------------------------------------------------------------------------------------------------------
// ������ ���������: 					�����
// �������� ����������������� ������: 	����� ������ ������ ��������������� �������
// ������ � �������� 					������ / ������
//----------------------------------------------------------------------------------------------------------------
typedef struct
{
	Flg_Adr01_Reg_S bits_reg1;
	Flg_Adr02_Reg_S bits_reg2;
	Flg_Adr03_Reg_S bits_reg3;
} Flg_Cntrl_Drive_S;


#endif /* FLAGPARAMDRIVE_H_ */
