//###########################################################################
//
// FILE:   MainCPU-Main.h
//
// TITLE: ������������ ����: MainCPU-Main.c
//
//###########################################################################

#ifndef MAINCPU_MAIN_DEFS_H
#define MAINCPU_MAIN_DEFS_H


////////////////////// ����������� ������������ ������ //////////////////////
// ����������� ������������� ����� "BaseDriveUsr.h"
#include "BaseDrive.h"
// ����������� ������������� ����� "RegParamDrive.h"
#include "RegParamDrive.h"
// ����������� ������������� ����� "RegParamDrive.h"
#include "FlagParamDrive.h"


////////////////////// ���������� ����������� �������� //////////////////////
// ����� �������� ��������� � ��������
#define TIME_DELAY_IN_SEC	0.00001
// ��������� ���������� AD2S90
#define CS_AD2S90_OFF 		GpioDataRegs.GPASET.bit.GPIO19 = 1
// ���������� ���������� AD2S90
#define CS_AD2S90_ON  		GpioDataRegs.GPACLEAR.bit.GPIO19 = 1
// ������� ���������� RS485A � ��������� ��������
#define DE_RS485A_ON 		GpioDataRegs.GPASET.bit.GPIO27 = 1;
// ������� ���������� RS485A � ��������� �����
#define DE_RS485A_OFF 		GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;
// ������� ���������� RS485B � ��������� ��������
#define DE_RS485B_ON 		GpioDataRegs.GPASET.bit.GPIO21 = 1;
// ������� ���������� RS485B � ��������� �����
#define DE_RS485B_OFF 		GpioDataRegs.GPACLEAR.bit.GPIO21 = 1;
// ������ �������� ����� ���������� ��� ����������
#define	PERD_BASE_CYCLE 	(5515 * 1.5)
// ������ ����������������� ���'� ��� ���������� ����������
#define	PWM_USR 			250
// ������ ����������������� ���'� ��� ���������� ���������� ������� �� 2
#define	PWM_USR_DIV_2 		PWM_USR / 2
// ������ ������� ���'�
#define PWM_OUT_PHASE		7500
// ������ ������� ���'� ������� �� 2
#define PWM_OUT_PHASE_DIV_2	PWM_OUT_PHASE / 2
// �������� modbus �������, ��� �������� ����� ���������
#define TIMECNT_DELAY_MB 	70000
// ������: DIV_�������_��������; ����������� ��������� ����� 1/4096
#define K_1_DIV_4096	 	0.000244140625


//////////////// ���������� �������� ������� � ���������� //////////////////
// ������ ������ ��������������� �������
extern Flg_Cntrl_Drive_S flags_drive;
// ������ ���������� ��������������� ������� (����� ������)
extern Rpd_Ctrl_Regs_S rpd_ctrl_regs;
// ������ ���������� ��������������� �������  (������ ������)
extern Data_PMSM_S data_pmsm;
// ������ ��������� ���������� modbus
extern MB_Servc mb_servc;
// ��������� �� ������ modbus
extern Uint16 	*pMBmemory;
// ���������� �������������� ����������
extern Brws_Param_Drive brwsr;


//////////////// ���������� �������� ������� � �������� ////////////////////
// ��������� ���������� �� ���'� ���������� epwm6_timer_isr
extern interrupt void epwm6_timer_isr(void);


#endif
