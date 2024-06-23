//###########################################################################
//
// File:  MainCpuSpi.c
//
// Title: SPI initialization and functions working with the SPI peripheral block
//
//###########################################################################

#include "PeripheralHeaderIncludes.h"
#include "MainCpuSpi.h"

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
