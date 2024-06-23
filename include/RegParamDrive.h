//###########################################################################
//
// FILE:    RegisterParametrs.h
//
// TITLE:   Register parametrs defenitions.
//
// NOTES:
//
//###########################################################################

#ifndef REGPARAMDRIVE_H_
#define REGPARAMDRIVE_H_

//----------------------------------------------------------------------------------------------------------------
// ������ ���������: 					1 (��������� ���������)
// �������� ����������������� ������: 	������� ����������
// ����� ��������:  					1
// ������ � �������� 					������ / ������
//----------------------------------------------------------------------------------------------------------------
typedef struct
{
    // 0  ���� ��������������� ������� 0 - ���������, 1 - ��������
    Uint16 net_drv :1;
    // 1  ���� ��������������� �������:  0 - ����, 1 - ����
    Uint16 strt_drv :1;
    // 2  ������� ��������������� �������: 0 - ����, 1 - �������
    Uint16 stp_drv :1;
    // 3  ������� ������� ��������: 0 - ������, 1 - ����������
    Uint16 ext_spd :1;
    // 15 : 4 ���������������
    Uint16 rsvd :12;
} Rpd_Adr01_Bits;

//----------------------------------------------------------------------------------------------------------------
// ������ ���������: 					1 (��������� ���������)
// �������� ����������������� ������: 	������� ����������
// ����� ��������:  					1
// ������ � �������� 					������ / ������ (������� ������ � �������� �� ������)
//----------------------------------------------------------------------------------------------------------------
typedef union
{
    Uint16 all;
    Rpd_Adr01_Bits bits1;
} Rpd_Adr01_Reg;

//----------------------------------------------------------------------------------------------------------------
// ������ ���������: 					1 (��������� ���������)
// �������� ����������������� ������: 	������ �������� ����������
// ����� ��������:  					2
// ������ � �������� 					������
//----------------------------------------------------------------------------------------------------------------
typedef struct
{
    // 0  ���� ��������������� ������� 0 - ���������, 1 - ��������
    Uint16 net_drv :1;
    // 1  ���������� ������ ��������������� �������: 0 - ���������, 1 - ��������
    Uint16 read_drv :1;
    // 2 ������ ��������������� �������: 0 - ���������, 1 - ��������
    Uint16 wrk_drv :1;
    // 3 ���� ��������������� �������:  0 - ����, 1 - ����
    Uint16 strt_drv :1;
    // 4 ������� ��������������� �������: 0 - ����, 1 - �������
    Uint16 stp_drv :1;
    // 5 ������ ��������������� �������: 0 - ������ �����������, 1 - ��������� ������
    Uint16 err_drv :1;
    // 6 ������ ��������������� ������� �� �����������-������� ������: 0 - ������ �����������, 1 - ��������� ������
    Uint16 err_mi_drv :1;
    // 7 ������ ��������������� ������� �� ������ ��������: 0 - ������ �����������, 1 - ��������� ������
    Uint16 err_trnstr_drv :1;
    // 15:7 ���������������
    Uint16 rsvd :8;
} Rpd_Adr02_Bits;

//----------------------------------------------------------------------------------------------------------------
// ������ ���������: 					1 (��������� ���������)
// �������� ����������������� ������: 	������� ����������
// ����� ��������:  					2
// ������ � �������� 					������ / ������ (������� ������ � �������� �� ������)
//----------------------------------------------------------------------------------------------------------------
typedef union
{
    Uint16 all;
    Rpd_Adr02_Bits bits2;
} Rpd_Adr02_Reg;

//----------------------------------------------------------------------------------------------------------------
// ��������� ��������: 					���������� ������ modbus ��������
//----------------------------------------------------------------------------------------------------------------
typedef struct
{
    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					1 (��������� ���������)
    // �������� ����������������� ������: 	������� ����������
    // ����� ��������:  						1
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Rpd_Adr01_Reg bits_reg1;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					1 (��������� ���������)
    // �������� ����������������� ������: 	������ �������� ����������
    // ����� ��������:  						2
    // ������ � �������� 					������
    //----------------------------------------------------------------------------------------------------------------
    Rpd_Adr02_Reg bits_reg2;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					1 (��������� ���������)
    // �������� ����������������� ������: 	������� �������� ��������������� �������
    // ����� ��������:  						3
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 ref_spd1;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					1 (��������� ���������)
    // �������� ����������������� ������: 	������� �������� ��������������� �������
    // ����� ��������:  						4
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 ref_spd2;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					1 (��������� ���������)
    // �������� ����������������� ������: 	������� �������� ��������������� �������
    // ����� ��������:  						5
    // ������ � �������� 					������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 cur_spd1;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					1 (��������� ���������)
    // �������� ����������������� ������: 	������� �������� ��������������� �������
    // ����� ��������:  						6
    // ������ � �������� 					������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 cur_spd2;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					1 (��������� ���������)
    // �������� ����������������� ������: 	������� ��� ������� ��������������� �������
    // ����� ��������:  						7
    // ������ � �������� 					������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 cur_i_sttr1;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					1 (��������� ���������)
    // �������� ����������������� ������: 	������� ��� ������� ��������������� �������
    // ����� ��������:  						8
    // ������ � �������� 					������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 cur_i_sttr2;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					1 (��������� ���������)
    // �������� ����������������� ������: 	������� �������� ���������� ���������� �� ����� ����������� ����
    // ����� ��������:  						9
    // ������ � �������� 					������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 cur_udc1;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					1 (��������� ���������)
    // �������� ����������������� ������: 	������� �������� ���������� ���������� �� ����� ����������� ����
    // ����� ��������:  						10
    // ������ � �������� 					������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 cur_udc2;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					1 (��������� ���������)
    // �������� ����������������� ������: 	������� �������� ��������� ������
    // ����� ��������:  						11
    // ������ � �������� 					������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 cur_pstn_rtr1;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					1 (��������� ���������)
    // �������� ����������������� ������: 	������� �������� ��������� ������
    // ����� ��������:  						12
    // ������ � �������� 					������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 cur_pstn_rtr2;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����� ������� � n(min) �� n(nom)
    // ����� ��������:  						13
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 accel_sec_up1;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����� ������� � n(min) �� n(nom)
    // ����� ��������:  						14
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 accel_sec_up2;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����� ���������� � n(min) �� n(nom)
    // ����� ��������:  						15
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 accel_sec_down1;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����� ���������� � n(min) �� n(nom)
    // ����� ��������:  						16
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 accel_sec_down2;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������� �������� ��������� (��/���)
    // ����� ��������:  						17
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 nom_speed_mtr1;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������� �������� ��������� (��/���)
    // ����� ��������:  						18
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 nom_speed_mtr2;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	���������������� ����������� ��� ���������� ��������� ������
    // ����� ��������:  						19
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 k_prptnl_pid_regltr_pstn1;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	���������������� ����������� ��� ���������� ��������� ������
    // ����� ��������:  						20
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 k_prptnl_pid_regltr_pstn2;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	������������ ����������� ��� ���������� ��������� ������
    // ����� ��������:  						21
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 k_intgrl_pid_regltr_pstn1;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	������������ ����������� ��� ���������� ��������� ������
    // ����� ��������:  						22
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 k_intgrl_pid_regltr_pstn2;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	���������������� ����������� ��� ���������� ��������� ������
    // ����� ��������:  						23
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 k_drntl_pid_regltr_pstn1;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	���������������� ����������� ��� ���������� ��������� ������
    // ����� ��������:  						24
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 k_drntl_pid_regltr_pstn2;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						25
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved1;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						26
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved2;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						27
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved3;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						28
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved4;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						29
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved5;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						30
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved6;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						31
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved7;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						32
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved8;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						33
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved9;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						34
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved10;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						35
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved11;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						36
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved12;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						37
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved13;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						38
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved14;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						39
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved15;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						40
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved16;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						41
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved17;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						42
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved18;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						43
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved19;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						44
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved20;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						45
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved21;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (��������� ���������)
    // �������� ����������������� ������: 	����������������� ������� ��������� ��������������� �������
    // ����� ��������:  						46
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 setting_reserved23;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (�������� ����������)
    // �������� ����������������� ������: 	������ ��������������� ������� � ���������
    // ����� ��������:  						47
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 error_position_dskr1;

    //----------------------------------------------------------------------------------------------------------------
    // ������ ���������: 					2 (�������� ����������)
    // �������� ����������������� ������: 	������ ��������������� ������� � ���������
    // ����� ��������:  						48
    // ������ � �������� 					������ / ������
    //----------------------------------------------------------------------------------------------------------------
    Uint16 error_position_dskr2;
} Rpd_Ctrl_Regs_S;

#endif /* REGPARAMDRIVE_H_ */
