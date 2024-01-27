//###########################################################################
//
// FILE:   MainCPU-Main.h
//
// TITLE: Declaration of global variables
//
//###########################################################################

#ifndef MAINCPU_MAIN_H
#define MAINCPU_MAIN_H


////////////////////// INCLUDE OF HEADER FILES//////////////////////
//! include header file "PeripheralHeaderIncludes.h"
#include "PeripheralHeaderIncludes.h"


/////////////////////////// VARIABLE DECLARATION ///////////////////////////
//! frequency converter parameter memory (shared memory)
Rpd_Ctrl_Regs_S rpd_ctrl_regs;
// frequency converter parameter memory (model memory)
Data_PMSM_S data_pmsm;
// common flag memory of the frequency converter
Flg_Cntrl_Drive_S flags_drive;
// modbus service parameters data structure
MB_Servc mb_servc;
// modbus memory pointer
Uint16 	*pMBmemory;
// counter for displaying the seven-segment indicator
Uint16 cnt_vdhl;
// declaration of the parameter view structure
Brws_Param_Drive brwsr;


#endif  // end of MAINCPU_MAIN_H definition

//===========================================================================
// End of file.
//===========================================================================
