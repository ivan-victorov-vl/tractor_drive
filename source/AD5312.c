//###########################################################################
//
// FILE:	DSP2833x_McBSP.c
//
// TITLE:	DSP2833x Device McBSP Initialization & Support Functions.
//
//###########################################################################

#include "PeripheralHeaderIncludes.h"
extern struct	AD5312_RES_REG AD5312;
                                        
#define CPU_SPD              150E6
#define MCBSP_SRG_FREQ       CPU_SPD/4                    				 
#define CLKGDV_VAL           1
#define MCBSP_INIT_DELAY     2*(CPU_SPD/MCBSP_SRG_FREQ)                  
#define MCBSP_CLKG_DELAY     2*(CPU_SPD/(MCBSP_SRG_FREQ/(1+CLKGDV_VAL))) 
//---------------------------------------------------------------------------
// ������������� Mcbsp:
//---------------------------------------------------------------------------
//
//

void delay_loop(void);					// ������� �������� ��� ������������� SRG


void InitAD5312()						// ������� ������������� ���������� AD5312 �� ��������� SPI � Mcbsp  		
{
    // ��������� McBSP-A
    McbspaRegs.SPCR2.all=0x0000;		 // ����� FS ����������, ������� ������������� ���������� � �����������
	McbspaRegs.SPCR1.all=0x0000;		 // ����� ��������, ��������� justify word, �������� ��������� �������� dis.
    McbspaRegs.PCR.all=0x0F08;           //(CLKXM=CLKRM=FSXM=FSRM= 1, FSXP = 1)
    McbspaRegs.SPCR1.bit.DLB = 1;
    McbspaRegs.SPCR1.bit.CLKSTP = 3;     // ��� ������������: � ��������� �� �������� ������� 
	McbspaRegs.PCR.bit.CLKXP = 1;		 // CPOL = 0, CPHA = 1 �������� �� ��������� ������
    McbspaRegs.XCR2.bit.XDATDLY=01;      // FSX setup time 1 in master mode. 0 for slave mode (Transmit)
    McbspaRegs.XCR1.bit.XWDLEN1=2;       //  16-bit word
    McbspaRegs.SRGR2.all=0x2000; 	 	 // CLKSM=1, FPER = 1 CLKG periods
    McbspaRegs.SRGR1.all= 0x004A;	     // ��������� �� �������  1 ��� (150/SRGR1)
    McbspaRegs.SPCR2.bit.GRST=1;         // ��������� ������� ������������� ����������
	delay_loop();                        // ������� ��� ������� 2 SRG �����
	McbspaRegs.SPCR2.bit.XRST=1;         // �������� � ��������� ��������
	McbspaRegs.SPCR1.bit.RRST=0;         // ��������� ������� � ��������� ������
    McbspaRegs.SPCR2.bit.FRST=1;         // �������� Frame Sync Generator 
}



void AD5312_ChA(float32 data)			// ������� ������ ��� �� ����� �
{
   AD5312.dac_a = (Uint16)(1023 * data);						
   data = (AD5312_CH_A|AD5312_UNBUF|AD5312_NORM_OP|(AD5312.dac_a <<2)); // ������������ ������� (����� �, ��� �����������, ���������� ����� ������) 
	
    McbspaRegs.DXR1.all=(Uint16)data;
}


void AD5312_ChB(float32 data)			// ������� ������ ��� �� ����� �	
{
   AD5312.dac_b = (Uint16)(1023 * data);
   data = (AD5312_CH_B|AD5312_UNBUF|AD5312_NORM_OP|(AD5312.dac_b<<2)); // ������������ ������� (����� B, ��� �����������, ���������� ����� ������)
	
    McbspaRegs.DXR1.all=(Uint16)data;
}

void delay_loop(void)
{
    long      i;
    for (i = 0; i < MCBSP_INIT_DELAY; i++) {} //�������� ��� ������������� McBsp
}

//===========================================================================
//
//===========================================================================











