//###########################################################################
//
// FILE:    ProtectnDrive.h
//
// TITLE:   Protectn Drive defenitions.
//
// NOTES:
//
//###########################################################################

#ifndef PROTECTNDRIVE_H_
#define PROTECTNDRIVE_H_


////////////////////// HEADER FILE CONNECTION //////////////////////
//! include the "BaseDrive.h"
#include "BaseDrive.h"


/////////////////////// DATA TYPE DECLARATION //////////////////////////
//! error data type
typedef enum {
	// no errors
	SUCCESS,
	// error detected
	ERROR
} retval_t;
// Note: If this data type exists, you must delete it.


////////////////////// DECLARATION OF NAMED CONSTANTS //////////////////////
//! format: DIV_separate_divider; named constant equal to 1/2
#define DIV_1_2					0.5
//! overvoltage overload setpoint on the DC link
#define KMAX_UDC_FROM_NOM		1.2
//! Over-voltage setpoint on the DC link
#define KMIN_UDC_FROM_NOM		0.65
//! overvoltage overload setpoint on the DC link
#define KOVRLD_UDC_FROM_NOM		1.1
//! overvoltage overload setpoint on the DC link
#define KMINWRNG_UDC_FROM_NOM 	0.85


//////////////// DECLARATION OF EXTERNAL ACCESS TO FUNCTIONS /////////////////////
//! declaration of external access to the pMaxMotorIPrtctn function
extern retval_t (*pMaxMotorIPrtctn)(float32 iu_l_a, float32 iv_l_a, float32 iw_l_a, float32 valmax_prtctn_l_a);
//! declaration of external access to the function pTimeIMotorPrtctn
extern retval_t (*pTimeIMotorPrtctn)(float32 istator_l, float32 ki_integral_l, float32 i_nom_l, float32 *i_intgrl_l, float32 activ_intgr_prtctn_l);
//! declaration of external access to the pBreakPhasePrtctn function
extern retval_t (*pBreakPhasePrtctn)(float32 urefu_l, float32 urefv_l, float32 urefw_l, float32 iu_l, float32 iv_l, float32 iw_l, float32 valmax_prtctn_l, float32 ku_multiply_l);
//! declaration of external access to the function pMaxUDCMotorPrtctn
extern retval_t (*pMaxUDCMotorPrtctn)(float32 udc_l, float32 udc_nom_max_l);
//! declaration of external access to the function pMinUDCMotorPrtctn
extern retval_t(*pMinUDCMotorPrtctn)(float32 udc_l, float32 udc_nom_min_l);
//! declaration of external access to the function pPressFaultMotorPrtctn
extern retval_t (*pPressFaultMotorPrtctn)(Uint16 press_fault_l);

#endif
