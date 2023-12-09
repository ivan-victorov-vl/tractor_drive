//###########################################################################
//
// ����:    	MainModbus.h
//
// ��������:   	������������ ����: MainModbus.c
//
//###########################################################################

#ifndef MAIN_MODBUS_H
#define MAIN_MODBUS_H

#ifdef __cplusplus
extern "C" {
#endif


////////////////////// ���������� ����������� �������� //////////////////////
// ��������� ������������ 1-�� ������� ��������� modbus "READ COIL STATUS"
#define	MBREADCOILSTATUSF	1
// ��������� ������������ 2-�� ������� ��������� modbus "READ INPUT STATUS"
#define	MBREADINPUTSTATUSF	2
// ��������� ������������ 3-�� ������� ��������� modbus "READ HOLDING REGISTERS"
#define	MBREADHOLDINGREGSF	3
// ��������� ������������ 4-�� ������� ��������� modbus "READ INPUT REGISTERS"
#define	MBREADINPUTREGSF	4
// ��������� ������������ 5-�� ������� ��������� modbus "FORCE SINGLE COIL"
#define	MBFORCESINGLECOILF	5
// ��������� ������������ 6-�� ������� ��������� modbus "FORCE SINGLE REGISTER"
#define	MBPRESETSINGLEREGF	6
// ��������� ������������ 15-�� ������� ��������� modbus "FORCE MULTIPLE COILS"
#define	MBFORCEMULTCOILSF	15
// ��������� ������������ 16-�� ������� ��������� modbus "FORCE MULTIPLE REGISTERS"
#define	MBPRESETMULTREGSF	16


/////////////////////// ���������� ����� ������������ ������ //////////////////////////
// ������������ ������ ������ modbus
typedef enum
{
	// ��� ������
    MB_ENOERR,
    // ����������� ����� ��������
    MB_ENOREG,
    // ����������� ��������
    MB_EINVAL,
    // ������ ������ �����
    MB_EPORTERR,
    // ������������ ��������
    MB_ENORES,
    // ������ �����/������
    MB_EIO,
    // �������� ����� ��������� � ����������� ���������
    MB_EILLSTATE,
    // ������������������ ������ time-out'�
    MB_ETIMEDOUT,
    // ������ �� ������������� �������
    MB_FUNCERR
} eMBErrorCode;


/////////////////////// ���������� �������� ������ //////////////////////////
// ��������� ������ ��������� ������
typedef struct
{
	// ���� �������� ��������
	Uint16 	rx_tx_idle : 1;
	// ���� ����������� �������� tx_rx == 1 (�������) ����� (����)
	Uint16  tx_rx:1;
	// ���� ���������� �������� ������� modbus �������
	Uint16	tx_en_modbus:1;
	// ���� ���������� ����� ������� modbus �������
	Uint16	rx_en_modbus:1;
	// ���� ������ �������� �� ������� SCIA - 0; SCIB - 0;
	Uint16	sci_ab_tx:1;
} MB_Flgs_Srvc;


// ��������� ������ ��������� ����������  modbus'�
typedef struct
{
	// ������ ����������� ������
	Uint16	rx[130];
	// ������ ������������ ������
	Uint16	tx[130];
	// ������� ������ ������������ ���������
	Uint16 numb_mes_rx;
	// ������� ������ ������������� ���������
	Uint16 numb_mes_tx;
	// ������� ������� ��� �������� �� ��������� modbus
	Uint16 cnt_modbus_time;
	// ������� ���������� ������������� ������
	Uint32 cnt_vdhl_modbus;
	// modbus ��������� �����
	MB_Flgs_Srvc flgs;
	// ����� ������������ �������
	Uint16 length_tx;
	// ��������� �� ���� �������
	Uint16 *prx;
	// ��������� �� �������� �������
	Uint16 *ptx;
	// ��������� �������
	eMBErrorCode mb_status;
} MB_Servc;


//////////////// ���������� �������� ������� � �������� /////////////////////
// ���������� �������� ������� � ������� InitSCIA
extern void MBReadFuncSlave (MB_Servc *mb_servc_l, Uint16 *pMBmemory_l);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
