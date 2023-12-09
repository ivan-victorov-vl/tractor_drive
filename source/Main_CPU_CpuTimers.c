// TI File $Revision: /main/3 $
// Checkin $Date: July 9, 2009   10:51:55 $
//###########################################################################
//
// FILE:    Main_CPU_CpuTimers.c
//
// TITLE:   CPU 32-bit Timers Initialization & Support Functions.
//
// NOTES:   CpuTimer2 is reserved for use with DSP BIOS and
//          other realtime operating systems.
//
//          Do not use these this timer in your application if you ever plan
//          on integrating DSP-BIOS or another realtime OS.
//
//###########################################################################

#include "PeripheralHeaderIncludes.h"

//---------------------------------------------------------------------------
// InitCpuTimers:
//---------------------------------------------------------------------------
// This function initializes all three CPU timers to a known state.
//
void InitCpuTimers(void)
{
    // CPU Timer 0

    // Initialize timer period to maximum:
    CpuTimer0Regs.PRD.all  = 0xFFFFFFFF;
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT):
    CpuTimer0Regs.TPR.all  = 0;
    CpuTimer0Regs.TPRH.all = 0;
    // Make sure timer is stopped:
    CpuTimer0Regs.TCR.bit.TSS = 1;
    // Reload all counter register with period value:
    CpuTimer0Regs.TCR.bit.TRB = 1;
    // Reset interrupt counters:

// CpuTimer2 is reserved for DSP BIOS & other RTOS
// Do not use this timer if you ever plan on integrating
// DSP-BIOS or another realtime OS.

    // Initialize timer period to maximum:
    CpuTimer1Regs.PRD.all  = 0xFFFFFFFF;
    CpuTimer2Regs.PRD.all  = 0xFFFFFFFF;
    // Make sure timers are stopped:
    CpuTimer1Regs.TCR.bit.TSS = 1;
    CpuTimer2Regs.TCR.bit.TSS = 1;
    // Reload all counter register with period value:
    CpuTimer1Regs.TCR.bit.TRB = 1;
    CpuTimer2Regs.TCR.bit.TRB = 1;

}

//---------------------------------------------------------------------------
// ConfigCpuTimer:
//---------------------------------------------------------------------------
// This function initializes the selected timer to the period specified
// by the "Freq" and "Period" parameters. The "Freq" is entered as "MHz"
// and the period in "uSeconds". The timer is held in the stopped state
// after configuration.
//
void ConfigCpuTimer(volatile struct CPUTIMER_REGS *TimerRegs, Uint32 Period, Uint16 inten)
{
	// Initialize timer period:
    TimerRegs->PRD.all = Period;

    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    TimerRegs->TPR.all  = 0;
    TimerRegs->TPRH.all  = 0;

    // Initialize timer control register:
    TimerRegs->TCR.bit.TSS = 1;      // 1 = Stop timer, 0 = Start/Restart Timer
    TimerRegs->TCR.bit.TRB = 1;      // 1 = reload timer
    TimerRegs->TCR.bit.SOFT = 1;
    TimerRegs->TCR.bit.FREE = 1;     // Timer Free Run
    TimerRegs->TCR.bit.TIE = inten;      // 0 = Disable/ 1 = Enable Timer Interrupt

}

//===========================================================================
// End of file.
//===========================================================================
