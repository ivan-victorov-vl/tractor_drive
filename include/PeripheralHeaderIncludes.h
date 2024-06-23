//============================================================================
//============================================================================
//
// FILE:   			PeripheralHeaderIncludes.h (2833x version)
// 
// DESCRIPTION:		Contains F283xx device specific definitions and includes
//
// VERSION:			04 Apr 2008 - (BRL)
//============================================================================
//============================================================================

#ifndef PERIPHERALHEADERINCLUDES_H
#define PERIPHERALHEADERINCLUDES_H

#ifdef __cplusplus
extern "C"
{
#endif

//---------------------------------------------------------------------------
// CPU Timer Definitions:
// Timer definitions are based on 150MHz System Clock.
// If not using a 150MHz clock define a different set of constants elsewhere.
#define		mSec0_5		75000		// 0.5 mS.
#define		mSec1		150000		// 1.0 mS.
#define		mSec2		300000		// 2.0 mS.
#define		mSec5		750000		// 5.0 mS.
#define		mSec7_5		1125000		// 7.5 mS.
#define		mSec10		1500000		// 10 mS.
#define		mSec20		3000000		// 20 mS.
#define		mSec50		7500000		// 50 mS.
#define		mSec100		15000000	// 100 mS.
#define		mSec500		75000000	// 500 mS.
#define		mSec1000	150000000	// 1000 mS.
#define		mSec5000	750000000	// 5000 mS.

//---------------------------------------------------------------------------
// Common CPU Definitions:
//---------------------------------------------------------------------------
extern cregister volatile unsigned int IFR;
extern cregister volatile unsigned int IER;

#define  EINT   asm(" clrc INTM")
#define  DINT   asm(" setc INTM")
#define  ERTM   asm(" clrc DBGM")
#define  DRTM   asm(" setc DBGM")
#define  EALLOW asm(" EALLOW")
#define  EDIS   asm(" EDIS")
#define  ESTOP0 asm(" ESTOP0")

#define M_INT1  0x0001
#define M_INT2  0x0002
#define M_INT3  0x0004
#define M_INT4  0x0008
#define M_INT5  0x0010
#define M_INT6  0x0020
#define M_INT7  0x0040
#define M_INT8  0x0080
#define M_INT9  0x0100
#define M_INT10 0x0200
#define M_INT11 0x0400
#define M_INT12 0x0800
#define M_INT13 0x1000
#define M_INT14 0x2000
#define M_DLOG  0x4000
#define M_RTOS  0x8000

#define BIT0	0x1
#define BIT1    0x2
#define BIT2    0x4
#define BIT3    0x8
#define BIT4    0x10
#define BIT5    0x20
#define BIT6    0x40
#define BIT7    0x80
#define BIT8    0x100
#define BIT9    0x200
#define BIT10   0x400
#define BIT11   0x800
#define BIT12   0x1000
#define BIT13   0x2000
#define BIT14   0x4000
#define BIT15   0x8000
#define BIT16	0x10000
#define BIT17	0x20000
#define BIT18	0x40000
#define BIT19	0x80000
#define BIT20   0x100000
#define BIT21   0x200000
#define BIT22   0x400000
#define BIT23   0x800000
#define BIT24   0x1000000
#define BIT25   0x2000000
#define BIT26   0x4000000
#define BIT27   0x8000000
#define BIT28   0x10000000
#define BIT29   0x20000000
#define BIT30   0x40000000
#define BIT31   0x80000000

//-----------------------------------
#ifndef DSP28_DATA_TYPES
#define DSP28_DATA_TYPES
typedef int int16;
typedef long int32;
typedef unsigned int Uint16;
typedef unsigned long Uint32;
typedef float float32;
typedef long double float64;

typedef unsigned char Uchar;
typedef unsigned short Ushort;

#endif

//---------------------------------------------------------------------------
// Include All Peripheral Header Files:
//---------------------------------------------------------------------------
//! include header file "DSP2833x_Adc.h"
#include "DSP2833x_Adc.h"
//! include header file "DSP2833x_DevEmu.h"
#include "DSP2833x_DevEmu.h"
//! include header file "DSP2833x_CpuTimers.h"
#include "DSP2833x_CpuTimers.h"
//! include header file "DSP2833x_ECan.h"
#include "DSP2833x_ECan.h"
//! include header file "DSP2833x_ECap.h"
#include "DSP2833x_ECap.h"
//! include header file "DSP2833x_DMA.h"
#include "DSP2833x_DMA.h"
//! include header file "DSP2833x_EPwm.h"
#include "DSP2833x_EPwm.h"
//! include header file "DSP2833x_EQep.h"
#include "DSP2833x_EQep.h"
//! include header file "DSP2833x_Gpio.h"
#include "DSP2833x_Gpio.h"
//! include header file "DSP2833x_I2c.h"
#include "DSP2833x_I2c.h"
//! include header file "DSP2833x_McBSP.h"
#include "DSP2833x_McBSP.h"
//! include header file "DSP2833x_PieCtrl.h"
#include "DSP2833x_PieCtrl.h"
//! include header file "DSP2833x_PieVect.h"
#include "DSP2833x_PieVect.h"
//! include header file "DSP2833x_Spi.h"
#include "DSP2833x_Spi.h"
//! include header file "DSP2833x_Sci.h"
#include "DSP2833x_Sci.h"
//! include header file "DSP2833x_SysCtrl.h"
#include "DSP2833x_SysCtrl.h"
//! include header file "DSP2833x_XIntrupt.h"
#include "DSP2833x_XIntrupt.h"
//! include header file "DSP2833x_Xintf.h"
#include "DSP2833x_Xintf.h"
//! include header file "ProtectnDrive_defs.h"
#include "ProtectnDrive_defs.h"
//! include header file "DSP2833x_DefaultIsr.h"
#include "DSP2833x_DefaultIsr.h"
//! include header file "DSP2833x_EPwm_defines.h"
#include "DSP2833x_EPwm_defines.h"
//! include header file "MainCPU-GPIO_defines.h"
#include "MainCPU-GPIO_defines.h"
//! include header file "MainCpuAdc.h"
#include "MainCpuAdc.h"
//! include header file "MainCpuSpi.h"
#include "MainCpuSpi.h"
//! include header file "MainCpuEpwm.h"
#include "MainCpuEpwm.h"
//! include header file "MainCPU-Main_defs.h"
#include "MainCPU-Main_defs.h"
//! include header file "BaseDrive.h"
#include "BaseDrive.h"
//! include header file "FuncDrive.h"
#include "FuncDrive.h"
//! include header file "RegParamDrive.h"
#include "RegParamDrive.h"
//! include header file "SysSrvc.h"
#include "SysSrvc.h"
//! include header file "MenuModbus.h"
#include "MenuModbus.h"
//! include header file "FlagParamDrive.h"
#include "FlagParamDrive.h"
//! include header file "MainInit.h"
#include "MainInit.h"
//! include header file "MainSetting.h"
#include "MainSetting.h"
//! include header file "MeasExtrnlDevice.h"
#include "MeasExtrnlDevice.h"
//! include header file "Smpl_table.h"
#include "Smpl_table.h"

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
