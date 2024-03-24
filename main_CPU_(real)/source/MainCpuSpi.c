//###########################################################################
//
// File:  MainCpuSpi.c
//
// Title: SPI initialization and functions working with the SPI peripheral block
//
//###########################################################################


#include "PeripheralHeaderIncludes.h"
#include "MainCpuSpi.h"


Uint16 RXRotorPostnSPI(void);
void InitSPIA(void);



void InitSPIA(void)
{
	EALLOW;
	GpioCtrlRegs.GPAPUD.bit.GPIO16 = 1;
	GpioCtrlRegs.GPAPUD.bit.GPIO17 = 1;
	GpioCtrlRegs.GPAPUD.bit.GPIO18 = 1;
	EDIS;

	SpiaRegs.SPICCR.bit.SPISWRESET = 0;
	SpiaRegs.SPICCR.bit.SPICHAR = 0xB;
	SpiaRegs.SPICCR.bit.CLKPOLARITY = 1;
	SpiaRegs.SPICCR.bit.SPILBK = 0;

	SpiaRegs.SPICTL.bit.SPIINTENA = 0;
	SpiaRegs.SPICTL.bit.TALK = 1;
	SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1;
	SpiaRegs.SPICTL.bit.CLK_PHASE = 0;
	SpiaRegs.SPICTL.bit.OVERRUNINTENA = 0;
	SpiaRegs.SPIBRR = 74;
	SpiaRegs.SPICCR.bit.SPISWRESET = 1;
    SpiaRegs.SPIPRI.bit.FREE = 1;
}


Uint16 RXRotorPostnSPI(void) {
	Uint16 meas_positn_l, i;
	if(SpiaRegs.SPISTS.bit.INT_FLAG) {
		CS_AD2S90_OFF;

		for(i = 0; i < 5; i++) {
			asm ("NOP");
		};

		meas_positn_l = (SpiaRegs.SPIRXBUF);
		CS_AD2S90_ON;
		SpiaRegs.SPITXBUF = 0;
	}
	return meas_positn_l;
}
