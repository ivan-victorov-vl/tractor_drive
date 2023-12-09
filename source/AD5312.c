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
// Инициализация Mcbsp:
//---------------------------------------------------------------------------
//
//

void delay_loop(void);					// функция задержки для инициализации SRG


void InitAD5312()						// функция инициализации микросхемы AD5312 по протоколу SPI в Mcbsp  		
{
    // Настройки McBSP-A
    McbspaRegs.SPCR2.all=0x0000;		 // сброс FS генератора, частоты дискретизации генератора и передатчика
	McbspaRegs.SPCR1.all=0x0000;		 // сброс приёмника, разрешить justify word, цифровая кольцевая проверка dis.
    McbspaRegs.PCR.all=0x0F08;           //(CLKXM=CLKRM=FSXM=FSRM= 1, FSXP = 1)
    McbspaRegs.SPCR1.bit.DLB = 1;
    McbspaRegs.SPCR1.bit.CLKSTP = 3;     // вид тактирования: с задержкой на половину периода 
	McbspaRegs.PCR.bit.CLKXP = 1;		 // CPOL = 0, CPHA = 1 передача по переднему фронту
    McbspaRegs.XCR2.bit.XDATDLY=01;      // FSX setup time 1 in master mode. 0 for slave mode (Transmit)
    McbspaRegs.XCR1.bit.XWDLEN1=2;       //  16-bit word
    McbspaRegs.SRGR2.all=0x2000; 	 	 // CLKSM=1, FPER = 1 CLKG periods
    McbspaRegs.SRGR1.all= 0x004A;	     // настроить на частоту  1 мГц (150/SRGR1)
    McbspaRegs.SPCR2.bit.GRST=1;         // разрешить частоту дискретизации генератора
	delay_loop();                        // ожидать как минимум 2 SRG цикла
	McbspaRegs.SPCR2.bit.XRST=1;         // сбросить и разрешить передачу
	McbspaRegs.SPCR1.bit.RRST=0;         // перевести приёмник в состояние сброса
    McbspaRegs.SPCR2.bit.FRST=1;         // сбросить Frame Sync Generator 
}



void AD5312_ChA(float32 data)			// функция вывода ЦАП на канал А
{
   AD5312.dac_a = (Uint16)(1023 * data);						
   data = (AD5312_CH_A|AD5312_UNBUF|AD5312_NORM_OP|(AD5312.dac_a <<2)); // формирование посылки (канал А, без буферизации, нормальный режим вывода) 
	
    McbspaRegs.DXR1.all=(Uint16)data;
}


void AD5312_ChB(float32 data)			// функция вывода ЦАП на канал В	
{
   AD5312.dac_b = (Uint16)(1023 * data);
   data = (AD5312_CH_B|AD5312_UNBUF|AD5312_NORM_OP|(AD5312.dac_b<<2)); // формирование посылки (канал B, без буферизации, нормальный режим вывода)
	
    McbspaRegs.DXR1.all=(Uint16)data;
}

void delay_loop(void)
{
    long      i;
    for (i = 0; i < MCBSP_INIT_DELAY; i++) {} //задержка для инициализации McBsp
}

//===========================================================================
//
//===========================================================================











