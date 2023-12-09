//###########################################################################
//
// FILE:	MainLedIndctn.c
//
// TITLE:	Functions of the seven-segment indicator of the device
//
//###########################################################################


#include "PeripheralHeaderIncludes.h"
#include "MainLedIndctn.h"


void VDHl1(void);
void VDHl2(void);
void VDHl3(void);
void VDHl4(void);
void VDHl5(void);
void (*VDHL[5])(void) = {&VDHl5, &VDHl4, &VDHl3, &VDHl2, &VDHl1};

void VDHlOff(void);

void HlNumb0(void);
void HlNumb1(void);
void HlNumb2(void);
void HlNumb3(void);
void HlNumb4(void);
void HlNumb5(void);
void HlNumb6(void);
void HlNumb7(void);
void HlNumb8(void);
void HlNumb9(void);
void (*HLNumb[10])(void) = {&HlNumb0, &HlNumb1, &HlNumb2, &HlNumb3, &HlNumb4, &HlNumb5, &HlNumb6, &HlNumb7, &HlNumb8, &HlNumb9};

void VDHLIndctn(Uint16 hl_numb, Uint16 vdhl);

Uint16 ExtrctPstnIndctn_0_Fl_3_2(float32 var_indctn_la);
Uint16 ExtrctPstnIndctn_1_Fl_3_2(float32 var_indctn_la);
Uint16 ExtrctPstnIndctn_2_Fl_3_2(float32 var_indctn_la);
Uint16 ExtrctPstnIndctn_3_Fl_3_2(float32 var_indctn_la);
Uint16 ExtrctPstnIndctn_4_Fl_3_2(float32 var_indctn_la);
Uint16 (*ExtrctPstnIndctn_Fl_3_2[5])(float32 var_indctn_la) = {&ExtrctPstnIndctn_0_Fl_3_2, &ExtrctPstnIndctn_1_Fl_3_2, &ExtrctPstnIndctn_2_Fl_3_2, &ExtrctPstnIndctn_3_Fl_3_2, &ExtrctPstnIndctn_4_Fl_3_2 };

void VDHLIndctnVar(float32 *var_indctn_l, Uint16 *cnt_vdhl_l);


void HlNumb0(void)
{
	HL_A_ON;
	HL_B_ON;
	HL_C_ON;
	HL_D_ON;
	HL_E_ON;
	HL_F_ON;
	HL_G_OFF;
	HL_DP_OFF;
}


void HlNumb1(void)
{
	HL_A_OFF;
	HL_B_ON;
	HL_C_ON;
	HL_D_OFF;
	HL_E_OFF;
	HL_F_OFF;
	HL_G_OFF;
	HL_DP_OFF;
}


void HlNumb2(void)
{
	HL_A_ON;
	HL_B_ON;
	HL_C_OFF;
	HL_D_ON;
	HL_E_ON;
	HL_F_OFF;
	HL_G_ON;
	HL_DP_OFF;
}

void HlNumb3(void)
{
	HL_A_ON;
	HL_B_ON;
	HL_C_ON;
	HL_D_ON;
	HL_E_OFF;
	HL_F_OFF;
	HL_G_ON;
	HL_DP_OFF;
}


void HlNumb4(void)
{
	HL_A_OFF;
	HL_B_ON;
	HL_C_ON;
	HL_D_OFF;
	HL_E_OFF;
	HL_F_ON;
	HL_G_ON;
	HL_DP_OFF;
}

void HlNumb5(void)
{
	HL_A_ON;
	HL_B_OFF;
	HL_C_ON;
	HL_D_ON;
	HL_E_OFF;
	HL_F_ON;
	HL_G_ON;
	HL_DP_OFF;
}

void HlNumb6(void)
{
	HL_A_ON;
	HL_B_OFF;
	HL_C_ON;
	HL_D_ON;
	HL_E_ON;
	HL_F_ON;
	HL_G_ON;
	HL_DP_OFF;
}

void HlNumb7(void)
{
	HL_A_ON;
	HL_B_ON;
	HL_C_ON;
	HL_D_OFF;
	HL_E_OFF;
	HL_F_OFF;
	HL_G_OFF;
	HL_DP_OFF;
}

void HlNumb8(void)
{
	HL_A_ON;
	HL_B_ON;
	HL_C_ON;
	HL_D_ON;
	HL_E_ON;
	HL_F_ON;
	HL_G_ON;
	HL_DP_OFF;
}

void HlNumb9(void)
{
	HL_A_ON;
	HL_B_ON;
	HL_C_ON;
	HL_D_ON;
	HL_E_OFF;
	HL_F_ON;
	HL_G_ON;
	HL_DP_OFF;
}

void VDHl1(void)
{
	VD_HL1_ON;
	VD_HL2_OFF;
	VD_HL3_OFF;
	VD_HL4_OFF;
	VD_HL5_OFF;
}

void VDHl2(void)
{
	VD_HL1_OFF;
	VD_HL2_ON;
	VD_HL3_OFF;
	VD_HL4_OFF;
	VD_HL5_OFF;
}

void VDHl3(void)
{
	VD_HL1_OFF;
	VD_HL2_OFF;
	VD_HL3_ON;
	VD_HL4_OFF;
	VD_HL5_OFF;
}

void VDHl4(void)
{
	VD_HL1_OFF;
	VD_HL2_OFF;
	VD_HL3_OFF;
	VD_HL4_ON;
	VD_HL5_OFF;
}

void VDHl5(void)
{
	VD_HL1_OFF;
	VD_HL2_OFF;
	VD_HL3_OFF;
	VD_HL4_OFF;
	VD_HL5_ON;
}

void VDHlOff(void)
{
	VD_HL1_OFF;
	VD_HL2_OFF;
	VD_HL3_OFF;
	VD_HL4_OFF;
	VD_HL5_OFF;
}

void VDHLIndctn(Uint16 hl_numb, Uint16 vdhl)
{
	(*HLNumb[hl_numb])();
	(*VDHL[vdhl])();
}

Uint16 ExtrctPstnIndctn_0_Fl_3_2(float32 var_indctn_la)
{
	Uint16 temp_var_la;

	temp_var_la =  (Uint16)(var_indctn_la * 10);
	return (Uint16)((Uint32)(var_indctn_la * 100) - (Uint32)(temp_var_la * 10));
}

Uint16 ExtrctPstnIndctn_1_Fl_3_2(float32 var_indctn_la)
{
	Uint16 temp_var_la;

	temp_var_la =  (Uint16)(var_indctn_la);
	return ((Uint16)(var_indctn_la * 10) - (temp_var_la * 10));
}

Uint16 ExtrctPstnIndctn_2_Fl_3_2(float32 var_indctn_la)
{
	Uint16 temp_var_la;

	temp_var_la =  (Uint16)(var_indctn_la * 0.1);
	return ((Uint16)(var_indctn_la) - (temp_var_la * 10));
}

Uint16 ExtrctPstnIndctn_3_Fl_3_2(float32 var_indctn_la)
{
	Uint16 temp_var_la;

	temp_var_la =  (Uint16)(var_indctn_la * 0.01);
	return ((Uint16)(var_indctn_la * 0.1) - (temp_var_la * 10));
}

Uint16 ExtrctPstnIndctn_4_Fl_3_2(float32 var_indctn_la)
{
	return (Uint16)(var_indctn_la * 0.01);
}

void VDHLIndctnVar(float32 *var_indctn_l, Uint16 *cnt_vdhl_l)
{
	if (*cnt_vdhl_l > 4) *cnt_vdhl_l = 0;
	LimitVar(MIN_VAR_INCTN_Fl_3_2, MAX_VAR_INCTN_Fl_3_2, &(*var_indctn_l));
	VDHLIndctn((*ExtrctPstnIndctn_Fl_3_2[*cnt_vdhl_l])(*var_indctn_l), *cnt_vdhl_l);
	if (*cnt_vdhl_l == 2) HL_DP_ON;
}
