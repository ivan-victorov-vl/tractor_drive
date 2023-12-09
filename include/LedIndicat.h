//###########################################################################
//
// FILE:   AD7732.h
//
// TITLE:  AD7732 device description.
//
//###########################################################################


#ifndef LEDINDICAT_H
#define LEDINDICAT_H

#ifdef __cplusplus
extern "C" {
#endif
#define VD_HL1_ON			 GpioDataRegs.GPBCLEAR.bit.GPIO40 = 1		// включить индикатор HL1		 	
#define VD_HL1_OFF			 GpioDataRegs.GPBSET.bit.GPIO40 = 	1		// отключить индикатор HL1		
#define VD_HL2_ON			 GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1		// включить индикатор HL2 	
#define VD_HL2_OFF			 GpioDataRegs.GPBSET.bit.GPIO41 = 	1		// отключить индикатор HL2
#define VD_HL3_ON			 GpioDataRegs.GPBCLEAR.bit.GPIO42 = 1 		// включить индикатор HL3
#define VD_HL3_OFF			 GpioDataRegs.GPBSET.bit.GPIO42 = 	1		// отключить индикатор HL3
#define VD_HL4_ON			 GpioDataRegs.GPBCLEAR.bit.GPIO43 = 1		// включить индикатор HL4 	
#define VD_HL4_OFF			 GpioDataRegs.GPBSET.bit.GPIO43 = 	1		// отключить индикатор HL4
#define VD_HL5_ON			 GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1		// включить индикатор HL5 	
#define VD_HL5_OFF			 GpioDataRegs.GPBSET.bit.GPIO44 = 	1		// отключить индикатор HL5


//	----------------------------------------------------------------------------------------------
//
// -  Описание используемого семисегментного индикатора - 					
//
// -----------------------------------------------------------------------------------------------
/*
					    A
					  - - -
					F|     |B
					 |  G  |
					 |_ _ _|
					E|     |C
					 |  D  |
					 |	   |  
					  - - -   DP 
					   		  O			  
*/

#define HL_A_ON			 	GpioDataRegs.GPASET.bit.GPIO30 = 	1		// включить сегмент HLA индикатора 
#define HL_A_OFF		 	GpioDataRegs.GPACLEAR.bit.GPIO30 = 	1 		// отключить сегмент HLA индикатора 
#define HL_B_ON			 	GpioDataRegs.GPASET.bit.GPIO31 = 	1		// включить сегмент HLB индикатора 
#define HL_B_OFF		 	GpioDataRegs.GPACLEAR.bit.GPIO31 = 	1 		// отключить сегмент HLB индикатора  
#define HL_C_ON			 	GpioDataRegs.GPBSET.bit.GPIO32 = 	1		// включить сегмент HLC индикатора 
#define HL_C_OFF		 	GpioDataRegs.GPBCLEAR.bit.GPIO32 = 	1 		// отключить сегмент HLC индикатора  
#define HL_D_ON			 	GpioDataRegs.GPBSET.bit.GPIO33 = 	1		// включить сегмент HLD индикатора 
#define HL_D_OFF		 	GpioDataRegs.GPBCLEAR.bit.GPIO33 = 	1 		// отключить сегмент HLD индикатора  
#define HL_E_ON			 	GpioDataRegs.GPBSET.bit.GPIO34 = 	1		// включить сегмент HLE индикатора 
#define HL_E_OFF		 	GpioDataRegs.GPBCLEAR.bit.GPIO34 = 	1 		// отключить сегмент HLE индикатора  
#define HL_F_ON			 	GpioDataRegs.GPBSET.bit.GPIO35 = 	1		// включить сегмент HLF индикатора 
#define HL_F_OFF		 	GpioDataRegs.GPBCLEAR.bit.GPIO35 = 	1 		// отключить сегмент HLF индикатора  
#define HL_G_ON			 	GpioDataRegs.GPBSET.bit.GPIO36 = 	1		// включить сегмент HLG индикатора 
#define HL_G_OFF		 	GpioDataRegs.GPBCLEAR.bit.GPIO36 = 	1 		// отключить сегмент HLG индикатора  
#define HL_DP_ON			GpioDataRegs.GPBSET.bit.GPIO37 = 	1		// включить сегмент HLDP индикатора 
#define HL_DP_OFF		 	GpioDataRegs.GPBCLEAR.bit.GPIO37 = 	1 		// отключить сегмент HLDP индикатора   

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of AD7732_H definition

//===========================================================================
// End of file.
//===========================================================================


