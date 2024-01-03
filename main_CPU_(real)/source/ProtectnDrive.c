//###########################################################################
//
// FILE: ProtecnDrive.c
//
// TITLE: Protection drive support functions.
//
// NOTES:
//
//###########################################################################


////////////////////// HEADER FILE CONNECTION //////////////////////
//! include the PeripheralHeaderIncludes.h header file
#include "PeripheralHeaderIncludes.h"
//! include the ProtectnDrive.h
#include "ProtectnDrive.h"


/////////////////////////// FUNCTION DECLARATION //////////////////////////////
//! protection function declaration MaxMotorIPrtctn
retval_t MaxMotorIPrtctn(float32 iu_l_a, float32 iv_l_a, float32 iw_l_a, float32 valmax_prtctn_l_a);
//! protection function pointer declaration pMaxMotorIPrtctn
retval_t (*pMaxMotorIPrtctn)(float32 iu_l_a, float32 iv_l_a, float32 iw_l_a, float32 valmax_prtctn_l_a) = &MaxMotorIPrtctn;
//! protection function declaration TimeIMotorPrtctn
retval_t TimeIMotorPrtctn(float32 istator_l, float32 ki_integral_l, float32 i_nom_l, float32 *i_intgrl_l, float32 activ_intgr_prtctn_l);
//! protection function pointer declaration pTimeIMotorPrtctn
retval_t (*pTimeIMotorPrtctn)(float32 istator_l, float32 ki_integral_l, float32 i_nom_l, float32 *i_intgrl_l, float32 activ_intgr_prtctn_l) = &TimeIMotorPrtctn;
//! protection function declaration BreakPhasePrtctn
retval_t BreakPhasePrtctn(float32 urefu_l, float32 urefv_l, float32 urefw_l, float32 iu_l, float32 iv_l, float32 iw_l, float32 valmax_prtctn_l, float32 ku_multiply_l);
//! protection function pointer declaration pBreakPhasePrtctn
retval_t (*pBreakPhasePrtctn)(float32 urefu_l, float32 urefv_l, float32 urefw_l, float32 iu_l, float32 iv_l, float32 iw_l, float32 valmax_prtctn_l, float32 ku_multiply_l) = &BreakPhasePrtctn;
//! protection function declaration pMaxUDCMotorPrtctn
retval_t MaxUDCMotorPrtctn(float32 udc_l, float32 udc_nom_max_l);
//! protection function pointer declaration pMaxUDCMotorPrtctn
retval_t (*pMaxUDCMotorPrtctn)(float32 udc_l, float32 udc_nom_max_l) = &MaxUDCMotorPrtctn;
//! protection function declaration MinUDCMotorPrtctn
retval_t MinUDCMotorPrtctn(float32 udc_l, float32 udc_nom_min_l);
//! protection function pointer declaration pMinUDCMotorPrtctn
retval_t(*pMinUDCMotorPrtctn)(float32 udc_l, float32 udc_nom_min_l) = &MinUDCMotorPrtctn;
//! function declaration  PressFaultMotorPrtctn
retval_t PressFaultMotorPrtctn(Uint16 press_fault_l);
//! function pointer declaration pPressFaultMotorPrtctn
retval_t (*pPressFaultMotorPrtctn)(Uint16 press_fault_l) = &PressFaultMotorPrtctn;


////////////////////////// MOTOR PROTECTION FUNCTIONS /////////////////////////
/*!
    \brief Checking the event "overcurrent on one of the three phases"
 */
retval_t MaxMotorIPrtctn(float32 iu_la, float32 iv_la, float32 iw_la, float32 valmax_prtctn_la)
{
	//! declaration of the initial state of the overcurrent protection
	retval_t StatMotorErr = SUCCESS;

	//! quadraticization of the overcurrent set point
	valmax_prtctn_la *= valmax_prtctn_la;
	//! fulfillment of the condition of tripping of the overcurrent protection
	if (((iu_la * iu_la) > valmax_prtctn_la) || ((iv_la * iv_la) > valmax_prtctn_la) ||
	((iw_la * iw_la) > valmax_prtctn_la)) {
		// detection of fault detection of overcurrent protection
		StatMotorErr = ERROR;
	}

	//! return the function state
	return StatMotorErr;
}

/*!
    \brief Checking the "time-current protection" event
 */
retval_t TimeIMotorPrtctn(float32 istator_la, float32 ki_sum_ti_la, float32 i_nom_la,  float32 *i_sum_ti_la, float32 activ_intgr_prtctn_la)
{
	//! initial state declaration
	retval_t StatMotorErr = SUCCESS;


	//! integral calculation
	*i_sum_ti_la += ki_sum_ti_la * (i_nom_la - istator_la);

	//! if the value of the integral is less than 0
	if (*i_sum_ti_la <= 0)
		//! zero the integral
		*i_sum_ti_la = 0;

	//if the integral is greater than the set value если интеграл больше установленного значения
	if (*i_sum_ti_la > activ_intgr_prtctn_la)
		StatMotorErr = ERROR;

	//! return the function state
	return StatMotorErr;
}

/*!
    \brief Checking the "phase failure protection" event
 */
retval_t BreakPhasePrtctn(float32 urefu_la, float32 urefv_la, float32 urefw_la, float32 iu_la, float32 iv_la, float32 iw_la, float32 valmax_prtctn_la, float32 ku_multiply_la)
{
	//! initial state declaration
	retval_t StatMotorErr = SUCCESS;


	//! setting the phase failure value
	valmax_prtctn_la *= (ku_multiply_la * ku_multiply_la) * DIV_1_2;

	//! U phase failure test
	if ( ( (urefu_la * urefu_la) - (iu_la * iu_la) ) > valmax_prtctn_la)
		//! status setting: phase failure U
		StatMotorErr = ERROR;

	//! V phase failure test
	if ( ( (urefv_la * urefv_la) - (iv_la * iv_la) ) > valmax_prtctn_la)
		//! status setting: V phase failure
		StatMotorErr = ERROR;

	//! phase failure test W
	if ( ( (urefw_la * urefw_la) - (iw_la * iw_la) ) > valmax_prtctn_la)
		//! status setting: phase failure W
		StatMotorErr = ERROR;

	//! return the function state
	return StatMotorErr;
}

/*!
    \brief Checking the event "over voltage"
 */
retval_t MaxUDCMotorPrtctn(float32 udc_la, float32 udc_nom_max_la)
{
	//! initial state declaration
	retval_t StatMotorErr = SUCCESS;


	//! DC overvoltage test
	if (udc_la > (udc_nom_max_la * KMAX_UDC_FROM_NOM))
		//! status setting : maximum voltage exceeded
		StatMotorErr = ERROR;

	//! return the function state
	return StatMotorErr;
}

/*!
    \brief Checking the "too low voltage" event
 */
retval_t MinUDCMotorPrtctn(float32 udc_la, float32 udc_nom_min_la)
{
	//! initial state declaration
	retval_t StatMotorErr = SUCCESS;


	//! DC overvoltage test
	if (udc_la < (udc_nom_min_la * KMIN_UDC_FROM_NOM))
		//! setting test status : voltage too low
		StatMotorErr = ERROR;

	//! return the function state
	return StatMotorErr;
}

/*!
    \brief Checking the event "FAULT MOTOR pressed"
 */
retval_t PressFaultMotorPrtctn(Uint16 press_fault_la)
{
	//! initial state declaration
	retval_t StatMotorErr = SUCCESS;


	//! if the FAULT MOTOR button is pressed
	if (press_fault_la)
		// setting the status that the FAULT MOTOR button is pressed
		StatMotorErr = ERROR;

	//! return the function state
	return StatMotorErr;
}
