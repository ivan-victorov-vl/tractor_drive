//###########################################################################
//
// Файл:    	MainCpuSci.c
//
// Описание:   	Инициализация Sci
//
//###########################################################################


////////////////////// ПОДКЛЮЧЕНИЕ ЗАГОЛОВОЧНЫХ ФАЙЛОВ //////////////////////
// подключение заголовочного файла "PeripheralHeaderIncludes.h"
#include "PeripheralHeaderIncludes.h"
// подключение заголовочного файла "MainModbus.h"
#include "MainModbus.h"

void InitSCIA(void);
void InitSCIB(void);
void CheckErrSciABRxTx(void);
void MBSciABRxTx(MB_Servc *mb_servc_l);
void MBSciABCyclRxTx(MB_Servc *mb_servc_l, Uint16 *pMBmemory_l);


void InitSCIA(void)
{
	SciaRegs.SCICTL1.bit.SWRESET = 0;
	SciaRegs.SCICTL1.bit.SWRESET = 1;

	SciaRegs.SCICCR.bit.SCICHAR	=	0x7;
	SciaRegs.SCICCR.bit.PARITY	=	1;
	SciaRegs.SCICCR.bit.PARITYENA =	0;

	SciaRegs.SCIHBAUD	=	0x01;
	SciaRegs.SCILBAUD	=	0xEA;
	SciaRegs.SCICTL1.bit.TXENA	=	0;
	SciaRegs.SCICTL1.bit.RXENA	=	1;

	SciaRegs.SCICTL2.bit.RXBKINTENA = 1;
	SciaRegs.SCICTL1.bit.RXERRINTENA = 1;

	SciaRegs.SCIFFTX.bit.SCIRST	= 1	;
	SciaRegs.SCIFFTX.bit.SCIFFENA = 1;
	SciaRegs.SCIFFTX.bit.TXFIFOXRESET = 0;
	SciaRegs.SCIFFTX.bit.TXFIFOXRESET = 1;

	SciaRegs.SCIFFRX.bit.RXFFIL = 0x1;
	SciaRegs.SCIFFRX.bit.RXFFIENA = 1;

	SciaRegs.SCIFFRX.bit.RXFIFORESET = 0;
	SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;
}

void InitSCIB(void)
{
	ScibRegs.SCICTL1.bit.SWRESET = 0;
	ScibRegs.SCICTL1.bit.SWRESET = 1;

	ScibRegs.SCICCR.bit.SCICHAR	= 0x7;
	ScibRegs.SCICCR.bit.PARITY = 1;
	ScibRegs.SCICCR.bit.PARITYENA =	0;

	ScibRegs.SCIHBAUD =	0x01;
	ScibRegs.SCILBAUD =	0xEA;

	ScibRegs.SCICTL1.bit.TXENA = 0;
	ScibRegs.SCICTL1.bit.RXENA = 1;

	ScibRegs.SCICTL2.bit.RXBKINTENA = 1;
	ScibRegs.SCICTL1.bit.RXERRINTENA = 1;

	ScibRegs.SCIFFTX.bit.SCIRST	= 1	;
	ScibRegs.SCIFFTX.bit.SCIFFENA = 1;
	ScibRegs.SCIFFTX.bit.TXFIFOXRESET = 0;
	ScibRegs.SCIFFTX.bit.TXFIFOXRESET = 1;

	ScibRegs.SCIFFRX.bit.RXFFIL = 0x1;
	ScibRegs.SCIFFRX.bit.RXFFIENA = 1;

	ScibRegs.SCIFFRX.bit.RXFIFORESET = 0;
	ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;
}

void CheckErrSciABRxTx(void)
{
	if(SciaRegs.SCIRXST.bit.RXERROR)
	{
		SciaRegs.SCICTL1.bit.RXENA = 0;
		SciaRegs.SCICTL1.bit.SWRESET = 0;
		SciaRegs.SCICTL1.bit.SWRESET = 1;
		SciaRegs.SCIFFRX.bit.RXFIFORESET = 0;
		SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;
	  }

	if(ScibRegs.SCIRXST.bit.RXERROR)
	{
		ScibRegs.SCICTL1.bit.RXENA = 0;
		ScibRegs.SCICTL1.bit.SWRESET = 0;
		ScibRegs.SCICTL1.bit.SWRESET = 1;
		ScibRegs.SCIFFRX.bit.RXFIFORESET = 0;
		ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;
	}
}

void MBSciABRxTx(MB_Servc *mb_servc_l)
{
	for(;SciaRegs.SCIFFRX.bit.RXFFST;)
	{
		mb_servc_l->rx[mb_servc_l->numb_mes_rx++] = SciaRegs.SCIRXBUF.all & 0xFF;
		mb_servc_l->cnt_modbus_time = 0;
		mb_servc_l->flgs.sci_ab_tx = 0;
	}

	for(;ScibRegs.SCIFFRX.bit.RXFFST;)
	{
		mb_servc_l->rx[mb_servc_l->numb_mes_rx++] = ScibRegs.SCIRXBUF.all & 0xFF;
		mb_servc_l->cnt_modbus_time = 0;
		mb_servc_l->flgs.sci_ab_tx = 1;
	}

	if (mb_servc_l->flgs.tx_en_modbus)
	{
		mb_servc_l->numb_mes_tx = 0;
		for (;mb_servc_l->flgs.tx_rx;)
		{
			ExtrctModbusVal(&rpd_ctrl_regs, &flags_drive, &data_pmsm, &brwsr);
			PushIndctnCntrlMB(&rpd_ctrl_regs, &flags_drive);

			mb_servc_l->cnt_vdhl_modbus = 0;

			if (!mb_servc_l->flgs.sci_ab_tx)
			{
				DE_RS485A_ON;

				if (SciaRegs.SCIFFTX.bit.TXFFST == 0)
				{
					SciaRegs.SCITXBUF = mb_servc_l->tx[mb_servc_l->numb_mes_tx++];
					DE_RS485A_OFF;
				}
			}
			else
			{
				DE_RS485B_ON;

				if (ScibRegs.SCIFFTX.bit.TXFFST == 0)
				{
					ScibRegs.SCITXBUF = mb_servc_l->tx[mb_servc_l->numb_mes_tx++];
					DE_RS485B_OFF;
				}
			}
			if (mb_servc_l->numb_mes_tx >= mb_servc_l->length_tx)
			{
				mb_servc_l->flgs.tx_rx = 0;
				mb_servc_l->flgs.tx_en_modbus = 0;
			}
			mb_servc_l->cnt_vdhl_modbus = 0;
		}
	}
}


void MBSciABCyclRxTx(MB_Servc *mb_servc_l, Uint16 *pMBmemory_l)
{
	if (mb_servc_l->flgs.tx_rx)
	{
		ScibRegs.SCICTL1.bit.RXENA = 0;
		if (mb_servc_l->cnt_modbus_time >= 30)
		{
			mb_servc_l->cnt_modbus_time = 0;
			mb_servc_l->flgs.tx_en_modbus = 1;
			ScibRegs.SCICTL1.bit.TXENA = 1;
		}
	}
	else
	{
		if (mb_servc_l->cnt_modbus_time >= 31)
		{
			mb_servc_l->numb_mes_tx  = 0;
			mb_servc_l->numb_mes_rx = 0;
			mb_servc_l->cnt_modbus_time = 0;
			ScibRegs.SCICTL1.bit.RXENA = 1;
			ScibRegs.SCICTL1.bit.TXENA = 0;

			if (mb_servc_l->rx[0] == 1)
			{
				MBReadFuncSlave(&(*mb_servc_l),&(*pMBmemory_l));
				mb_servc_l->rx[0]= 130;
			}
			else
			{
				mb_servc_l->rx[0] = 130;
			}
		}
	}
}
