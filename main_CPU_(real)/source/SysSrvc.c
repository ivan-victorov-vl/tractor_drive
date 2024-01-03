//###########################################################################
//
// FILE:    SysSrvc.c
//
// TITLE:   Handler system functions.
//
// NOTES:
//
//###########################################################################


#include "PeripheralHeaderIncludes.h"
#include "SysSrvc.h"

void TimeDelaySys(float32 time_in_sec_l);
void Init_GPIO_0_5_in_PWM(void);
Uint16 HandlrBttn(Uint16 push_l);
void LimitVar(float32 min_var, float32 max_var, float32 *var_lim);
float32 FltrMas6Var(float32 cur_var, Uint16 *cur_mas, float32 *pmas_var);

void TimeDelaySys(float32 time_in_sec_l) {
	Uint32 a, i;

	a = (Uint32)(time_in_sec_l * FRQ_HZ_PRCSR);
	for(i = 0; i < a; i++) {
		asm ("NOP");
	};
}



void Init_GPIO_0_5_in_PWM(void) {
	EALLOW;

	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO0  = 1;

	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO1  = 1;

	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO2  = 1;

	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO3  = 1;

	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO4  = 1;

	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO5  = 1;
	EDIS;
}

Uint16 HandlrBttn(Uint16 push_l) {
	static Uint16 n_cnt_fltr = 0;
	Uint16 FlgBttn = 0;

	if (!push_l) {
		n_cnt_fltr++;
		if (n_cnt_fltr++ > N_CNT_FLTR_MAX)
		n_cnt_fltr = N_CNT_FLTR_MIN;
	}
	else {
		if (n_cnt_fltr >= N_CNT_FLTR_MIN) {
			FlgBttn = 1;
		}
		n_cnt_fltr = 0;
	  }
	return FlgBttn;
}

/*!
    \brief Limiting variables and assigning new values
 */
void LimitVar(float32 min_var, float32 max_var, float32 *var_lim) {
 	*var_lim = (*var_lim < min_var) ? min_var : *var_lim;
	*var_lim = (*var_lim > max_var) ? max_var : *var_lim;
}


/*!
    \brief Filter six values
 */
float32 FltrMas6Var(float32 cur_var, Uint16 *cur_mas, float32 *pmas_var) {
	if (*cur_mas ==  6) *cur_mas = 0;

	*(pmas_var + *cur_mas) = cur_var;
	return (( *(pmas_var) + *(pmas_var + 1) + *(pmas_var + 2) + *(pmas_var + 3) + *(pmas_var + 4)  + *(pmas_var + 5)) * DIV_1_6);
}
