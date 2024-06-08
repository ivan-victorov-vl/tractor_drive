//###########################################################################
//
// FILE:    FuncDrive.h
//
// TITLE:   Functions drive definitions
//
// NOTES:
//
//###########################################################################

#ifndef FUNCDRIVE_H_
#define FUNCDRIVE_H_


////////////////////// HEADER FILE CONNECTION //////////////////////
// connection of the header file "BaseDriveUsr.h"
#include "BaseDrive.h"
// connection of the header file "Flg_Cntrl_Drive_S.h"
#include "FlagParamDrive.h"


////////////////////// DECLARATION OF NAMED CONSTANTS //////////////////////
//! number of samples per complete revolution
#define	FULL_DSKRT			360.00
//! time constant for calculating the second (1 / (cycle time * 2 )))
#define CONST_ACCEL 		18181.81818181818
//! format: DIV_separate_divider; named constant equal to 1/SQRT(3)
#define DIV_1_SQRT3			0.5773502691896259
//! format: DIV_divider_divisor; named constant equal to SQRT(3)/2
#define DIV_SQRT3_2			0.8660254037844386
//! format: DIV_separate_divider; named constant equal to 2/SQRT(3)
#define DIV_2_SQRT3			1.154700538379252
//! format: DIV_separate_divider; named constant equal to 1/2
#define DIV_1_2				0.5
//! format: DIV_divider_divider; named constant equal to 1/90
#define DIV_1_90			1 / 90
//! overcurrent setpoint
#define KOVRLD_I_FROM_NOM	1.1
//! format: MUL_multiplier.1_multiplier.2; named constant equals 1*10
#define MUL_1_10 			10
//! stabilization factor im set to 30 ms time
#define KIM_EQLZTN			1 / (30 * 10 * 1.804402742692169)
//! maximum reactive current setpoint
#define MAX_IR				0.23
//! acceleration time from n(min) to n(nom)
#define ACCEL_UP			5
//! deceleration time from n(nom) to n(min)
#define ACCEL_DOWN			5
//! nominal speed in rpm
#define NOM_SPEED			1000
//! stator current rating
#define NOM_I_STATOR		25
//! number of pole pairs
#define NUMB_PAIR_POLES		3
//! format: DIV_division_divider; named constant equal to 1/360
#define K_1_DIV_360		 	0.0027777777777778
//! format: DIV_separate_divider; named constant equal to 1/4
#define K_1_DIV_4			0.25

//////////////// DECLARATION OF EXTERNAL ACCESS TO FUNCTIONS /////////////////////
//! declaration of external access to a function Stop
extern void Stop(Model_Data_PMSM_S *md_la, Settng_Data_PMSM_S *sd_la, Flg_Cntrl_Drive_S *mf_la );
//! declaration of external access to a function ApprdFltr
extern float32 ApprdFltr(float32 first_var_lb, float32 Ti_apprd_lb, float32 *integr_lb);
//! declaration of external access to a function Calc2To3Cos
extern void Calc2To3Cos(float32 first_var_lb, float32 sec_var_lb, float32 *first_res_lb, float32 *sec_res_lb, float32 *third_res_lb);
//! declaration of external access to a function Calc3To2
extern void Calc3To2(float32 first_var_lb, float32 sec_var_lb, float32 third_var_lb, float32 *first_res_lb, float32 *sec_res_lb);
//! declaration of external access to a function SpeedRef
extern void SpeedRef(float32 k_f_mul_ref_lb, float32 k_f_mul_plus_lb, float32 k_f_mul_minus_lb, float32 *k_f_mul_lb);
//! declaration of external access to a function CalcLengthVect2In
extern float32 CalcLengthVect2In(float32 first_lb, float32 secnd_lb);
//! declaration of external access to a function PiRegltr
extern float32 PiRegltr(float32 cur_var_lb, float32 k_prprnl_lb, float32 k_integral_lb, float32 *integral_lb);
//! declaration of external access to a function PID_Regltr
extern float32 PID_Regltr(PID_Rgltr_S *v_pid_r_lb);
//! declaration of external access to a function CalculateConditionPMSForward
extern void CalculateConditionPMSForward(Model_Data_PMSM_S *md_l);
//! declaration of external access to a function CalculateConditionPMSBackward
extern void CalculateConditionPMSBackward(Model_Data_PMSM_S *md_l);
//! declaration of external access to a function CalculateScalarCurrentFrom6Phase
extern float32 CalculateScalarCurrentFrom6Phase(Model_Data_PMSM_S *md_l);
#endif
