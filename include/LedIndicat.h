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
#define VD_HL1_ON			 GpioDataRegs.GPBCLEAR.bit.GPIO40 = 1		// �������� ��������� HL1		 	
#define VD_HL1_OFF			 GpioDataRegs.GPBSET.bit.GPIO40 = 	1		// ��������� ��������� HL1		
#define VD_HL2_ON			 GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1		// �������� ��������� HL2 	
#define VD_HL2_OFF			 GpioDataRegs.GPBSET.bit.GPIO41 = 	1		// ��������� ��������� HL2
#define VD_HL3_ON			 GpioDataRegs.GPBCLEAR.bit.GPIO42 = 1 		// �������� ��������� HL3
#define VD_HL3_OFF			 GpioDataRegs.GPBSET.bit.GPIO42 = 	1		// ��������� ��������� HL3
#define VD_HL4_ON			 GpioDataRegs.GPBCLEAR.bit.GPIO43 = 1		// �������� ��������� HL4 	
#define VD_HL4_OFF			 GpioDataRegs.GPBSET.bit.GPIO43 = 	1		// ��������� ��������� HL4
#define VD_HL5_ON			 GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1		// �������� ��������� HL5 	
#define VD_HL5_OFF			 GpioDataRegs.GPBSET.bit.GPIO44 = 	1		// ��������� ��������� HL5


//	----------------------------------------------------------------------------------------------
//
// -  �������� ������������� ��������������� ���������� - 					
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

#define HL_A_ON			 	GpioDataRegs.GPASET.bit.GPIO30 = 	1		// �������� ������� HLA ���������� 
#define HL_A_OFF		 	GpioDataRegs.GPACLEAR.bit.GPIO30 = 	1 		// ��������� ������� HLA ���������� 
#define HL_B_ON			 	GpioDataRegs.GPASET.bit.GPIO31 = 	1		// �������� ������� HLB ���������� 
#define HL_B_OFF		 	GpioDataRegs.GPACLEAR.bit.GPIO31 = 	1 		// ��������� ������� HLB ����������  
#define HL_C_ON			 	GpioDataRegs.GPBSET.bit.GPIO32 = 	1		// �������� ������� HLC ���������� 
#define HL_C_OFF		 	GpioDataRegs.GPBCLEAR.bit.GPIO32 = 	1 		// ��������� ������� HLC ����������  
#define HL_D_ON			 	GpioDataRegs.GPBSET.bit.GPIO33 = 	1		// �������� ������� HLD ���������� 
#define HL_D_OFF		 	GpioDataRegs.GPBCLEAR.bit.GPIO33 = 	1 		// ��������� ������� HLD ����������  
#define HL_E_ON			 	GpioDataRegs.GPBSET.bit.GPIO34 = 	1		// �������� ������� HLE ���������� 
#define HL_E_OFF		 	GpioDataRegs.GPBCLEAR.bit.GPIO34 = 	1 		// ��������� ������� HLE ����������  
#define HL_F_ON			 	GpioDataRegs.GPBSET.bit.GPIO35 = 	1		// �������� ������� HLF ���������� 
#define HL_F_OFF		 	GpioDataRegs.GPBCLEAR.bit.GPIO35 = 	1 		// ��������� ������� HLF ����������  
#define HL_G_ON			 	GpioDataRegs.GPBSET.bit.GPIO36 = 	1		// �������� ������� HLG ���������� 
#define HL_G_OFF		 	GpioDataRegs.GPBCLEAR.bit.GPIO36 = 	1 		// ��������� ������� HLG ����������  
#define HL_DP_ON			GpioDataRegs.GPBSET.bit.GPIO37 = 	1		// �������� ������� HLDP ���������� 
#define HL_DP_OFF		 	GpioDataRegs.GPBCLEAR.bit.GPIO37 = 	1 		// ��������� ������� HLDP ����������   

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of AD7732_H definition

//===========================================================================
// End of file.
//===========================================================================


