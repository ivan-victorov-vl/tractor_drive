// TI File $Revision: /main/8 $
// Checking $Date: April 15, 2009   09:54:05 $
//###########################################################################
//
// FILE:   DSP2833x_SysCtrl.c
//
// TITLE:  DSP2833x Device System Control Initialization & Support Functions.
//
// DESCRIPTION:
//
//         Example initialization of system resources.
//
//###########################################################################
// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
// $Release Date: August 4, 2009 $
//###########################################################################

#include "PeripheralHeaderIncludes.h" // Include all Peripheral Headers.

// Functions that will be run from RAM need to be assigned to
// a different section.  This section will then be mapped to a load and
// run address using the linker cmd file.

void DisableDog(void);
void InitPll(Uint16, Uint16);
void InitPeripheralClocks(void);
void GpioConf(void);
void ADC_cal(void);

//---------------------------------------------------------------------------
// InitSysCtrl:
//---------------------------------------------------------------------------
// This function initializes the System Control registers to a known state.
// - Disables the watchdog
// - Set the PLLCR for proper SYSCLKOUT frequency
// - Set the pre-scaler for the high and low frequency peripheral clocks
// - Enable the clocks to the peripherals

void InitSysCtrl(void)
{

    // Disable the watchdog
    DisableDog();

    // Initialize the PLL control: PLLCR and DIVSEL
    // DSP28_PLLCR and DSP28_DIVSEL are defined in DSP2833x_Examples.h
    InitPll(0x6, 2);

    // Initialize the peripheral clocks
    InitPeripheralClocks();
    GpioConf();
}

//---------------------------------------------------------------------------
// Example: InitFlash:
//---------------------------------------------------------------------------
// This function initializes the Flash Control registers

//                   CAUTION
// This function MUST be executed out of RAM. Executing it
// out of OTP/Flash will yield unpredictable results

void InitFlash(void)
{
    EALLOW;
    //Enable Flash Pipeline mode to improve performance
    //of code executed from Flash.
    FlashRegs.FOPT.bit.ENPIPE = 1;

    //Set the Paged Waitstate for the Flash
    FlashRegs.FBANKWAIT.bit.PAGEWAIT = 5;

    //Set the Random Waitstate for the Flash
    FlashRegs.FBANKWAIT.bit.RANDWAIT = 5;

    //Set the Waitstate for the OTP
    FlashRegs.FOTPWAIT.bit.OTPWAIT = 8;

    //                CAUTION
    //ONLY THE DEFAULT VALUE FOR THESE 2 REGISTERS SHOULD BE USED
    FlashRegs.FSTDBYWAIT.bit.STDBYWAIT = 0x01FF;
    FlashRegs.FACTIVEWAIT.bit.ACTIVEWAIT = 0x01FF;
    EDIS;

    //Force a pipeline flush to ensure that the write to
    //the last register configured occurs before returning.

    asm(" RPT #7 || NOP");
}

//---------------------------------------------------------------------------
// Example: DisableDog:
//---------------------------------------------------------------------------
// This function disables the watchdog timer.

void DisableDog(void)
{
    EALLOW;
    SysCtrlRegs.WDCR = 0x0068;
    EDIS;
}

//---------------------------------------------------------------------------
// Example: InitPll:
//---------------------------------------------------------------------------
// This function initializes the PLLCR register.

void InitPll(Uint16 val, Uint16 divsel)
{

    // Make sure the PLL is not running in limp mode
    if (SysCtrlRegs.PLLSTS.bit.MCLKSTS != 0)
    {
        // Missing external clock has been detected
        // Replace this line with a call to an appropriate
        // SystemShutdown(); function.
        asm("        ESTOP0");
    }

    // DIVSEL MUST be 0 before PLLCR can be changed from
    // 0x0000. It is set to 0 by an external reset XRSn
    // This puts us in 1/4
    if (SysCtrlRegs.PLLSTS.bit.DIVSEL != 0)
    {
        EALLOW;
        SysCtrlRegs.PLLSTS.bit.DIVSEL = 0;
        EDIS;
    }

    // Change the PLLCR
    if (SysCtrlRegs.PLLCR.bit.DIV != val)
    {

        EALLOW;
        // Before setting PLLCR turn off missing clock detect logic
        SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1;
        SysCtrlRegs.PLLCR.bit.DIV = val;
        EDIS;

        // Optional: Wait for PLL to lock.
        // During this time the CPU will switch to OSCCLK/2 until
        // the PLL is stable.  Once the PLL is stable the CPU will
        // switch to the new PLL value.
        //
        // This time-to-lock is monitored by a PLL lock counter.
        //
        // Code is not required to sit and wait for the PLL to lock.
        // However, if the code does anything that is timing critical,
        // and requires the correct clock be locked, then it is best to
        // wait until this switching has completed.

        // Wait for the PLL lock bit to be set.

        // The watchdog should be disabled before this loop, or fed within
        // the loop via ServiceDog().

        // Uncomment to disable the watchdog
        DisableDog();

        while (SysCtrlRegs.PLLSTS.bit.PLLLOCKS != 1)
        {
            // Uncomment to service the watchdog
            // ServiceDog();
        }

        EALLOW;
        SysCtrlRegs.PLLSTS.bit.MCLKOFF = 0;
        EDIS;
    }

    // If switching to 1/2
    if ((divsel == 1) || (divsel == 2))
    {
        EALLOW;
        SysCtrlRegs.PLLSTS.bit.DIVSEL = divsel;
        EDIS;
    }
}

//--------------------------------------------------------------------------
// Example: InitPeripheralClocks:
//---------------------------------------------------------------------------
// This function initializes the clocks to the peripheral modules.
// First the high and low clock prescalers are set
// Second the clocks are enabled to each peripheral.
// To reduce power, leave clocks to unused peripherals disabled
//
// Note: If a peripherals clock is not enabled then you cannot
// read or write to the registers for that peripheral

void InitPeripheralClocks(void)
{
    EALLOW;

// HISPCP/LOSPCP prescale register settings, normally it will be set to default values
    SysCtrlRegs.HISPCP.all = 0x0001;
    SysCtrlRegs.LOSPCP.all = 0x0001;

// XCLKOUT to SYSCLKOUT ratio.  By default XCLKOUT = 1/4 SYSCLKOUT
    // XTIMCLK = SYSCLKOUT/2
    XintfRegs.XINTCNF2.bit.XTIMCLK = 1;
    // XCLKOUT = XTIMCLK/2
    XintfRegs.XINTCNF2.bit.CLKMODE = 1;
    // Enable XCLKOUT
    XintfRegs.XINTCNF2.bit.CLKOFF = 0;

// Peripheral clock enables set for the selected peripherals.
// If you are not using a peripheral leave the clock off
// to save on power.
//
// Note: not all peripherals are available on all 2833x derivates.
// Refer to the datasheet for your particular device.
//
// This function is not written to be an example of efficient code.

    SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;    // ADC

    // *IMPORTANT*
    // The ADC_cal function, which  copies the ADC calibration values from TI reserved
    // OTP into the ADCREFSEL and ADCOFFTRIM registers, occurs automatically in the
    // Boot ROM. If the boot ROM code is bypassed during the debug process, the
    // following function MUST be called for the ADC to function according
    // to specification. The clocks to the ADC MUST be enabled before calling this
    // function.
    // See the device data manual and/or the ADC Reference
    // Manual for more information.

    ADC_cal();

//   SysCtrlRegs.PCLKCR0.bit.I2CAENCLK = 1;   // I2C
    SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 1;   // SCI-A
    SysCtrlRegs.PCLKCR0.bit.SCIBENCLK = 1;   // SCI-B
    SysCtrlRegs.PCLKCR0.bit.SCICENCLK = 1;   // SCI-C
    SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 1;   // SPI-A
    SysCtrlRegs.PCLKCR0.bit.MCBSPAENCLK = 1; // McBSP-A
    SysCtrlRegs.PCLKCR0.bit.MCBSPBENCLK = 1; // McBSP-B
    SysCtrlRegs.PCLKCR0.bit.ECANAENCLK = 1;    // eCAN-A
    SysCtrlRegs.PCLKCR0.bit.ECANBENCLK = 1;    // eCAN-B

//	SysCtrlRegs.PCLKCR1.bit.ECAP3ENCLK = 1;  // eCAP3
//	SysCtrlRegs.PCLKCR1.bit.ECAP4ENCLK = 1;  // eCAP4
//	SysCtrlRegs.PCLKCR1.bit.ECAP5ENCLK = 1;  // eCAP5
//	SysCtrlRegs.PCLKCR1.bit.ECAP6ENCLK = 1;  // eCAP6
//	SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 1;  // eCAP1
//	SysCtrlRegs.PCLKCR1.bit.ECAP2ENCLK = 1;  // eCAP2
//	SysCtrlRegs.PCLKCR1.bit.EQEP1ENCLK = 1;  // eQEP1
//	SysCtrlRegs.PCLKCR1.bit.EQEP2ENCLK = 1;  // eQEP2

    SysCtrlRegs.PCLKCR3.bit.CPUTIMER0ENCLK = 1; // CPU Timer 0
    SysCtrlRegs.PCLKCR3.bit.CPUTIMER1ENCLK = 1; // CPU Timer 1
    SysCtrlRegs.PCLKCR3.bit.CPUTIMER2ENCLK = 1; // CPU Timer 2

    SysCtrlRegs.PCLKCR3.bit.DMAENCLK = 1;       // DMA Clock
    SysCtrlRegs.PCLKCR3.bit.XINTFENCLK = 1;     // XTIMCLK
    SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;    // GPIO input clock

    EDIS;
}
//=========================================================
void GpioConf(void)
{
// GPIO (GENERAL PURPOSE I/O) CONFIG
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// QUICK NOTES on GPIO CONFIG USAGE:
//----------------------------------
// If GpioCtrlRegs.GP?MUX?bit.GPIO?= 1, 2 or 3 (i.e. Non GPIO func), then leave
//	rest of lines commented
// If GpioCtrlRegs.GP?MUX?bit.GPIO?= 0 (i.e. GPIO func), then:
//	  1) uncomment GpioCtrlRegs.GP?DIR.bit.GPIO? = ? and choose pin to be IN or OUT direc.
//	  2) If IN, can leave next two lines commented
//	  3) If OUT, uncomment line with ..GPACLEAR.. to force pin LOW or
//			     uncomment line with ..GPASET.. to force pin HIGH
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
    EALLOW;
//!  GPIO-00 - PIN FUNCTION (EPWM1A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1; // 0=GPIO,  1=EPWM1A,  2=Resv,  3=Resv
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 1; 				// 1=OUTput,  0=INput

//!  GPIO-01 - PIN FUNCTION (EPWM1B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1; // 0=GPIO,  1=EPWM1B,  2=ECAP6,  3=MFSR-B
    GpioCtrlRegs.GPADIR.bit.GPIO1 = 1; 				// 1=OUTput,  0=INput

//!  GPIO-02 - PIN FUNCTION (EPWM2A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1; // 0=GPIO,  1=EPWM2A,  2=Resv,  3=Resv
    GpioCtrlRegs.GPADIR.bit.GPIO2 = 1; 				// 1=OUTput,  0=INput

//!  GPIO-03 - PIN FUNCTION (EPWM2B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1; // 0=GPIO,  1=EPWM2B,  2=ECAP5,  3=MCLKR-B
    GpioCtrlRegs.GPADIR.bit.GPIO3 = 1; 				// 1=OUTput,  0=INput

//!  GPIO-04 - PIN FUNCTION (EPWM3A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1; // 0=GPIO,  1=EPWM3A,  2=Resv,  3=Resv
    GpioCtrlRegs.GPADIR.bit.GPIO4 = 1; 				// 1=OUTput,  0=INput

//!  GPIO-05 - PIN FUNCTION (EPWM3B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1; // 0=GPIO,  1=EPWM3B,  2=MFSR-A,  3=ECAP1
    GpioCtrlRegs.GPADIR.bit.GPIO5 = 1; 				// 1=OUTput,  0=INput

//!  GPIO-06 - PIN FUNCTION (EPWM4A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1; // 0=GPIO,  1=EPWM4A,  2=SYNCI,  3=SYNCO
    GpioCtrlRegs.GPADIR.bit.GPIO6 = 1; 				// 1=OUTput,  0=INput

//!  GPIO-07 - PIN FUNCTION (EPWM4B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1; // 0=GPIO,  1=EPWM4B,  2=MCLKR-A,  3=ECAP2
    GpioCtrlRegs.GPADIR.bit.GPIO7 = 1; 				// 1=OUTput,  0=INput

//!  GPIO-08 - PIN FUNCTION (EPWM5A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1; // 0=GPIO,  1=EPWM5A,  2=CANTX-B,  3=ADCSOC-A
    GpioCtrlRegs.GPADIR.bit.GPIO8 = 1; 				// 1=OUTput,  0=INput

//!  GPIO-09 - PIN FUNCTION (EPWM5B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1; // 0=GPIO,  1=EPWM5B,  2=SCITX-B,  3=ECAP3
    GpioCtrlRegs.GPADIR.bit.GPIO9 = 1; 				// 1=OUTput,  0=INput

//!  GPIO-10 - PIN FUNCTION (EPWM6A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1; // 0=GPIO,  1=EPWM6A,  2=CANRX-B,  3=ADCSOC-B
    GpioCtrlRegs.GPADIR.bit.GPIO10 = 1; 				// 1=OUTput,  0=INput

//!  GPIO-11 - PIN FUNCTION (EPWM6B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1; // 0=GPIO,  1=EPWM6B,  2=SCIRX-B,  3=ECAP4
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1; 				// 1=OUTput,  0=INput

//!  GPIO-12 - PIN FUNCTION (Err IGBT1.1)
    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0; // 0=GPIO,  1=TZ1,  2=CANTX-B,  3=MDX-B
    GpioCtrlRegs.GPADIR.bit.GPIO12 = 0; 				// 1=OUTput,  0=INput

//!	GPIO-13 - PIN FUNCTION (Err IGBT1.2)
    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0; // 0=GPIO,  1=TZ2,  2=CANRX-B,  3=MDR-B
    GpioCtrlRegs.GPADIR.bit.GPIO13 = 0; 				// 1=OUTput,  0=INput

//!  GPIO-14 - PIN FUNCTION (Err IGBT1.3)
    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0; // 0=GPIO,  1=TZ3,  2=SCITX-B,  3=MCLKX-B
    GpioCtrlRegs.GPADIR.bit.GPIO14 = 0; 				// 1=OUTput,  0=INput

//!  GPIO-15 - PIN FUNCTION (Err IGBT2.1)
    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0; // 0=GPIO,  1=TZ4,  2=SCIRX-B,  3=MFSX-B
    GpioCtrlRegs.GPADIR.bit.GPIO15 = 0; 				// 1=OUTput,  0=INput

//!  GPIO-16 - PIN FUNCTION (Err IGBT2.2)
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0; // 0=GPIO,  1=SPISIMO-A,  2=CANTX-B,  3=TZ5
    GpioCtrlRegs.GPADIR.bit.GPIO16 = 0; 				// 1=OUTput,  0=INput

//!  GPIO-17 - PIN FUNCTION (Err IGBT2.3)
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;// 0=GPIO,  1=SPISOMI-A,  2=CANRX-B,  3=TZ6
    GpioCtrlRegs.GPADIR.bit.GPIO17 = 0; 				// 1=OUTput,  0=INput

//!  GPIO-18 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 0; // 0=GPIO,  1=SPICLK-A,  2=SCITX-B,  3=CANRX-A
    GpioCtrlRegs.GPADIR.bit.GPIO18 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;  // uncomment if --> Set Low initially

//!  GPIO-19 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0; // 0=GPIO,  1=SPISTE-A,  2=SCIRX-B,  3=CANTX-A
    GpioCtrlRegs.GPADIR.bit.GPIO19 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;  // uncomment if --> Set Low initially

//!  GPIO-20 - PIN FUNCTION (CANTXB)
    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 3; // 0=GPIO,  1=EQEPA-1,  2=MDX-A,  3=CANTX-B
    GpioCtrlRegs.GPADIR.bit.GPIO20 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPACLEAR.bit.GPIO20 = 1; // uncomment if --> Set Low initially

//!  GPIO-21 - PIN FUNCTION (CANRXB)
    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 3; // 0=GPIO,  1=EQEPB-1,  2=MDR-A,  3=CANRX-B
    GpioCtrlRegs.GPADIR.bit.GPIO21 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPACLEAR.bit.GPIO21 = 1; // uncomment if --> Set Low initially

//!  GPIO-22 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0; // 0=GPIO,  1=EQEPS-1,  2=MCLKX-A,  3=SCITX-B
    GpioCtrlRegs.GPADIR.bit.GPIO22 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPACLEAR.bit.GPIO22 = 1;  // uncomment if --> Set Low initially

//!  GPIO-23 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0; // 0=GPIO,  1=EQEPI-1,  2=MFSX-A,  3=SCIRX-B
    GpioCtrlRegs.GPADIR.bit.GPIO23 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPACLEAR.bit.GPIO23 = 1;  // uncomment if --> Set Low initially

//!  GPIO-24 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0; // 0=GPIO,  1=ECAP1,  2=EQEPA-2,  3=MDX-B
    GpioCtrlRegs.GPADIR.bit.GPIO24 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPACLEAR.bit.GPIO24 = 1;  // uncomment if --> Set Low initially

//!  GPIO-25 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0; // 0=GPIO,  1=ECAP2,  2=EQEPB-2,  3=MDR-B
    GpioCtrlRegs.GPADIR.bit.GPIO25 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPACLEAR.bit.GPIO25 = 1;  // uncomment if --> Set Low initially

//!  GPIO-26 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0; // 0=GPIO,  1=ECAP3,  2=EQEPI-2,  3=MCLKX-B
    GpioCtrlRegs.GPADIR.bit.GPIO26 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPACLEAR.bit.GPIO26 = 1;  // uncomment if --> Set Low initially

//!  GPIO-27 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0; // 0=GPIO,  1=ECAP4,  2=EQEPS-2,  3=MFSX-B
    GpioCtrlRegs.GPADIR.bit.GPIO27 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;  // uncomment if --> Set Low initially

//!  GPIO-28 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 0; // 0=GPIO,  1=SCIRX-A,  2=Resv,  3=Resv
    GpioCtrlRegs.GPADIR.bit.GPIO28 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;  // uncomment if --> Set Low initially

//!  GPIO-29 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 0; // 0=GPIO,  1=SCITXD-A,  2=XA19,  3=Resv
    GpioCtrlRegs.GPADIR.bit.GPIO29 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPACLEAR.bit.GPIO29 = 1;  // uncomment if --> Set Low initially

//!  GPIO-30 - PIN FUNCTION (CANRXA)
    GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1; // 0=GPIO,  1=CANRX-A,  2=XA18,  3=Resv
    GpioCtrlRegs.GPADIR.bit.GPIO30 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPACLEAR.bit.GPIO30 = 1; // uncomment if --> Set Low initially

//!  GPIO-31 - PIN FUNCTION (CANTXA)
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1; // 0=GPIO,  1=CANTX-A,  2=XA17,  3=Resv
    GpioCtrlRegs.GPADIR.bit.GPIO31 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPACLEAR.bit.GPIO31 = 1; // uncomment if --> Set Low initially

//!  GPIO-32 - PIN FUNCTION (SDAA)
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1; // 0=GPIO,  1=I2C-SDA,  2=SYNCI,  3=ADCSOCA
    GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1; // uncomment if --> Set Low initially

//!  GPIO-33 - PIN FUNCTION (SCLA)
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1; // 0=GPIO,  1=I2C-SCL,  2=SYNCO,  3=ADCSOCB
    GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1; // uncomment if --> Set Low initially

//!  GPIO-34 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0; // 0=GPIO,  1=ECAP1,  2=Resv,  3=Resv
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;  // uncomment if --> Set Low initially

//!  GPIO-35 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPBMUX1.bit.GPIO35 = 0; // 0=GPIO,  1=SCIA-TX,  2=Resv,  3=Resv
    GpioCtrlRegs.GPBDIR.bit.GPIO35 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO35 = 1; // uncomment if --> Set Low initially

//!  GPIO-36 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 0; // 0=GPIO,  1=SCIA-RX,  2=Resv,  3=Resv
    GpioCtrlRegs.GPBDIR.bit.GPIO36 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO36 = 1; // uncomment if --> Set Low initially

//!  GPIO-37 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPBMUX1.bit.GPIO37 = 0; 	// 0=GPIO37 1=ECAP2 2=XZCS7 3=XZCS7
    GpioCtrlRegs.GPBDIR.bit.GPIO37 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO37 = 1; // uncomment if --> Set Low initially

//!  GPIO-38 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPBMUX1.bit.GPIO38 = 0; 	// 0=GPIO,  1=Resv,  2=Resv,  3=Resv
    GpioCtrlRegs.GPBDIR.bit.GPIO38 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO38 = 1; // uncomment if --> Set Low initially

//!  GPIO-39 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0; 	// 0=GPIO,  1=Resv,  2=XA16,  3=Resv
    GpioCtrlRegs.GPBDIR.bit.GPIO39 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1; // uncomment if --> Set Low initially

//!  GPIO-40 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 0; 	// 0=GPIO,  1=Resv,  2=XA0,  3=XA0
    GpioCtrlRegs.GPBDIR.bit.GPIO40 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBSET.bit.GPIO40 = 1; // uncomment if --> Set Low initially

//!  GPIO-41 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 0; 	// 0=GPIO,  1=Resv,  2=XA1,  3=XA1
    GpioCtrlRegs.GPBDIR.bit.GPIO41 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBSET.bit.GPIO41 = 1; // uncomment if --> Set Low initially

//!  GPIO-42 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 0; 	// 0=GPIO,  1=Resv,  2=XA2,  3=XA2
    GpioCtrlRegs.GPBDIR.bit.GPIO42 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBSET.bit.GPIO42 = 1; // uncomment if --> Set Low initially

//!  GPIO-43 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 0; 	// 0=GPIO,  1=Resv,  2=XA3,  3=XA3
    GpioCtrlRegs.GPBDIR.bit.GPIO43 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBSET.bit.GPIO43 = 1; // uncomment if --> Set Low initially

//!  GPIO-44 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0; 	// 0=GPIO,  1=Resv,  2=XA4,  3=XA4
    GpioCtrlRegs.GPBDIR.bit.GPIO44 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBSET.bit.GPIO44 = 1; // uncomment if --> Set Low initially

//!  GPIO-45 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPBMUX1.bit.GPIO45 = 0; 	// 0=GPIO,  1=Resv,  2=XA5,  3=XA5
    GpioCtrlRegs.GPBDIR.bit.GPIO45 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO45 = 1; // uncomment if --> Set Low initially

//!  GPIO-46 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPBMUX1.bit.GPIO46 = 0; 	// 0=GPIO,  1=Resv,  2=XA6,  3=XA6
    GpioCtrlRegs.GPBDIR.bit.GPIO46 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO46 = 1; // uncomment if --> Set Low initially

//!  GPIO-47 - PIN FUNCTION (LED_VD1 - "net")
    GpioCtrlRegs.GPBMUX1.bit.GPIO47 = 0; 	// 0=GPIO,  1=Resv,  2=XA7,  3=XA7
    GpioCtrlRegs.GPBDIR.bit.GPIO47 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBSET.bit.GPIO47 = 1;   // uncomment if --> Set High initially

//!  GPIO-48 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPBMUX2.bit.GPIO48 = 0; // 0=GPIO,  1=ECAP5,  2=XD31,  3=Resv
    GpioCtrlRegs.GPBDIR.bit.GPIO48 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO48 = 1; // uncomment if --> Set Low initially

//!  GPIO-49 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPBMUX2.bit.GPIO49 = 0; // 0=GPIO,  1=ECAP6,  2=XD30,  3=Resv
    GpioCtrlRegs.GPBDIR.bit.GPIO49 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1; // uncomment if --> Set Low initially

//!  GPIO-50 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 0; 				// 0=GPIO,  1=EQEP1A,
    GpioCtrlRegs.GPBDIR.bit.GPIO50 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO50 = 1; // uncomment if --> Set Low initially

//!  GPIO-51 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 0; 				// 0=GPIO,  1=EQEP1B,
    GpioCtrlRegs.GPBDIR.bit.GPIO51 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO51 = 1; // uncomment if --> Set Low initially

//!  GPIO-52 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 0; 				// 0=GPIO,  1=EQEP1S
    GpioCtrlRegs.GPBDIR.bit.GPIO52 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO52 = 1;  // uncomment if --> Set Low initially

//!  GPIO-53 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 0; 				// 0=GPIO,  1=EQEP1I
    GpioCtrlRegs.GPBDIR.bit.GPIO53 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO53 = 1;  // uncomment if --> Set Low initially

//!  GPIO-54 - PIN FUNCTION (SPI MOSI)
    GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 1; 				// 0=GPIO,
    GpioCtrlRegs.GPBDIR.bit.GPIO54 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO54 = 1; // uncomment if --> Set Low initially

//!  GPIO-55 - PIN FUNCTION (SPI MISO)
    GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 1; 				// 0=GPIO,
    GpioCtrlRegs.GPBDIR.bit.GPIO55 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO55 = 1; // uncomment if --> Set Low initially

//!  GPIO-56 - PIN FUNCTION (SPI SCK)
    GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 1; 				// 0=GPIO,
    GpioCtrlRegs.GPBDIR.bit.GPIO56 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO56 = 1; // uncomment if --> Set Low initially

//!  GPIO-57 - PIN FUNCTION (SPI INV_CS)
    GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 1; 				// 0=GPIO,
    GpioCtrlRegs.GPBDIR.bit.GPIO57 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO57 = 1; // uncomment if --> Set Low initially

//!  GPIO-58 - PIN FUNCTION (FREEZE PROTECTION)
    GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 0; // 0=GPIO,  1=MCLKR-A,  2=XD21,  3=Resv
    GpioCtrlRegs.GPBDIR.bit.GPIO58 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPBCLEAR.bit.GPIO58 = 1; // uncomment if --> Set Low initially

//!  GPIO-59 - PIN FUNCTION (Hall pulse 2.1)
    GpioCtrlRegs.GPBMUX2.bit.GPIO59 = 0; // 0=GPIO,  1=MFSR-A,  2=XD20,  3=Resv
    GpioCtrlRegs.GPBDIR.bit.GPIO59 = 0; 				// 1=OUTput,  0=INput

//!  GPIO-60 - PIN FUNCTION (Hall pulse 2.0)
    GpioCtrlRegs.GPBMUX2.bit.GPIO60 = 0; // 0=GPIO,  1=MCLKR-B,  2=XD19,  3=Resv
    GpioCtrlRegs.GPBDIR.bit.GPIO60 = 0; 				// 1=OUTput,  0=INput

//!  GPIO-61 - PIN FUNCTION (Hall pulse 1.1)
    GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 0; // 0=GPIO,  1=MFSR-B,  2=XD18,  3=Resv
    GpioCtrlRegs.GPBDIR.bit.GPIO61 = 0; 				// 1=OUTput,  0=INput

//!  GPIO-62 - PIN FUNCTION (Hall pulse 1.0)
    GpioCtrlRegs.GPBMUX2.bit.GPIO62 = 0; // 0=GPIO,  1=SCIRX-C,  2=XD17,  3=Resv
    GpioCtrlRegs.GPBDIR.bit.GPIO62 = 0; 				// 1=OUTput,  0=INput
    GpioCtrlRegs.GPBQSEL2.bit.GPIO62 = 0;       // Xint1 Synch to SYSCLKOUT only

//!  GPIO-63 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPBMUX2.bit.GPIO63 = 0; // 0=GPIO,  1=SCITX-C,  2=XD16,  3=Resv
    GpioCtrlRegs.GPBDIR.bit.GPIO63 = 1; 				// 1=OUTput,  0=INput
    GpioCtrlRegs.GPBPUD.bit.GPIO63 = 1; 				// 1=OUTput,  0=INput

//!  GPIO-64 - PIN FUNCTION (D out 4)
    GpioCtrlRegs.GPCMUX1.bit.GPIO64 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO64 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPCCLEAR.bit.GPIO64 = 1; // uncomment if --> Set Low initially

//!  GPIO-65 - PIN FUNCTION (D out 3)
    GpioCtrlRegs.GPCMUX1.bit.GPIO65 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO65 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPCCLEAR.bit.GPIO65 = 1; // uncomment if --> Set Low initially

//!  GPIO-66 - PIN FUNCTION (D out 2)
    GpioCtrlRegs.GPCMUX1.bit.GPIO66 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO66 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPCCLEAR.bit.GPIO66 = 1; // uncomment if --> Set Low initially

//!  GPIO-67 - PIN FUNCTION (D out 1)
    GpioCtrlRegs.GPCMUX1.bit.GPIO67 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO67 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPCCLEAR.bit.GPIO67 = 1; // uncomment if --> Set Low initially

//!  GPIO-68 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPCMUX1.bit.GPIO68 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO68 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPCCLEAR.bit.GPIO68 = 1; // uncomment if --> Set Low initially

//!  GPIO-69 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPCMUX1.bit.GPIO69 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO69 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPCCLEAR.bit.GPIO69 = 1; // uncomment if --> Set Low initially

//!  GPIO-70 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPCMUX1.bit.GPIO70 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO70 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPCCLEAR.bit.GPIO70 = 1; // uncomment if --> Set Low initially

//!  GPIO-71 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPCMUX1.bit.GPIO71 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO71 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPCCLEAR.bit.GPIO71 = 1; // uncomment if --> Set Low initially

//!  GPIO-72 - PIN FUNCTION (D in 4 / Reset)
    GpioCtrlRegs.GPCMUX1.bit.GPIO72 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO72 = 0; 				// 1=OUTput,  0=INput

//!  GPIO-73 - PIN FUNCTION (D in 3 / Stop)
    GpioCtrlRegs.GPCMUX1.bit.GPIO73 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO73 = 0; 				// 1=OUTput,  0=INput

//!  GPIO-74 - PIN FUNCTION (D in 2 / Start)
    GpioCtrlRegs.GPCMUX1.bit.GPIO74 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO74 = 0; 				// 1=OUTput,  0=INput

//!  GPIO-75 - PIN FUNCTION (D in 1 / Change direction)
    GpioCtrlRegs.GPCMUX1.bit.GPIO75 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO75 = 0; 				// 1=OUTput,  0=INput

//!  GPIO-76 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPCMUX1.bit.GPIO76 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO76 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPCCLEAR.bit.GPIO76 = 1; // uncomment if --> Set Low initially

//!  GPIO-77 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPCMUX1.bit.GPIO77 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO77 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPCCLEAR.bit.GPIO77 = 1; // uncomment if --> Set Low initially

//!  GPIO-78 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPCMUX1.bit.GPIO78 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO78 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPCCLEAR.bit.GPIO78 = 1; // uncomment if --> Set Low initially

//!  GPIO-79 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPCMUX1.bit.GPIO79 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO79 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPCCLEAR.bit.GPIO79 = 1; // uncomment if --> Set Low initially

//!  GPIO-80 - PIN FUNCTION (LED_VD2 - "start")
    GpioCtrlRegs.GPCMUX2.bit.GPIO80 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO80 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPCSET.bit.GPIO80 = 1; // uncomment if --> Set High initially

//!  GPIO-81 - PIN FUNCTION (LED_VD3 - "stop")
    GpioCtrlRegs.GPCMUX2.bit.GPIO81 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO81 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPCSET.bit.GPIO81 = 1; // uncomment if --> Set High  initially

//!  GPIO-82 - PIN FUNCTION (LED_VD4 - "error")
    GpioCtrlRegs.GPCMUX2.bit.GPIO82 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO82 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPCSET.bit.GPIO82 = 1; // uncomment if --> Set High initially

//!  GPIO-83 - PIN FUNCTION (NONE)
    GpioCtrlRegs.GPCMUX2.bit.GPIO83 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO83 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPCCLEAR.bit.GPIO83 = 1; // uncomment if --> Set Low initially

//!  GPIO-84 - PIN FUNCTION (GPIO84)
    GpioCtrlRegs.GPCMUX2.bit.GPIO84 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO84 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPCCLEAR.bit.GPIO84 = 1; // uncomment if --> Set Low initially

//!  GPIO-85 - PIN FUNCTION (GPIO85)
    GpioCtrlRegs.GPCMUX2.bit.GPIO85 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO85 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPCCLEAR.bit.GPIO85 = 1; // uncomment if --> Set Low initially

//!  GPIO-86 - PIN FUNCTION (GPIO86)
    GpioCtrlRegs.GPCMUX2.bit.GPIO86 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO86 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPCCLEAR.bit.GPIO86 = 1; // uncomment if --> Set Low initially

//!  GPIO-87 - PIN FUNCTION (GPIO87)
    GpioCtrlRegs.GPCMUX2.bit.GPIO87 = 0; 				// 0=GPIO,
    GpioCtrlRegs.GPCDIR.bit.GPIO87 = 1; 				// 1=OUTput,  0=INput
    GpioDataRegs.GPCCLEAR.bit.GPIO87 = 1; // uncomment if --> Set Low initially

    EDIS;
}

//===========================================================================
// End of file.
//===========================================================================
