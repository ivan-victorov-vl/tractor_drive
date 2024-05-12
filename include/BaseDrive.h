//###########################################################################
//
// FILE:    	BaseDrUsr.h
//
// TITLE:   	BaseDrUsr.c header file
//
//###########################################################################

#ifndef BASEDRIVE_H_
#define BASEDRIVE_H_


////////////////////// HEADER FILE CONNECTION //////////////////////
//! include header file "SysSrvc.h"
#include "SysSrvc.h"
//! include header file "Flg_Cntrl_Drive_S.h"
#include "FlagParamDrive.h"
//! include header file "RegParamDrive.h"
#include "RegParamDrive.h"


////////////////////// DECLARATION OF NAMED CONSTANTS //////////////////////
//! format: DIV_separate_divider; named constant equal to 4096/360
#define DIV_4096_360	11.37777777777778
//! format: DIV_division_divider; named constant equal to 1/360
#define DIV_1_360	0.0027777777777778
//! format: DIV_divider_separator; named constant equal to 3/360
#define DIV_3_360	0.0083333333333333
//! proportional coefficient of the rotor position controller pid
#define K_PRPRTNL_PSTN	0.0077
//! time constant of rotor position regulator pid at initialization is equal to infinity
#define T_INTGRL_PSTN	7
//! time constant of the diffrential coefficient of the rotor position controller pid
#define T_DFRNTNL_PSTN	99999999999
//! Minimum transition angle
#define MIN_CROSS_ANGLE 30


///////////////////////////  MACROSUBSTITUTION ///////////////////////////////
//! Substitution denotes the following letter values
//! 1st letter f - float
//! s - configuration parameters
//! 2nd letter p - pointer to structure
//! f - float
//! 3rd letter s - structure
//! p - pointer to structure
//! 4th letter l - local structure
//! f - flag
//! s - structure
//! 5th letter a - tree level, where (empty - level 0), a - level 1
//! l - local structure
//!
//! the last letter a is the 1st level of the tree
//! b - 2nd level of the tree
//!
//! macro substitution of structure md_l -> a.fl
#define fpsl(a) (md_l->a.fl)
//! macro substitution of structure sd_l -> a.fl
#define sfpsl(a) (sd_l->a.fl)
//! macro substitution of the structure md_la -> a.fl
#define fpsla(a) (md_la->a.fl)
//! macro substitution of the structure sd_l -> a.fl
#define sfpsla(a) (sd_la->a.fl)
//! macro substitution of the structure md_lb -> a.fl
#define fpslb(a) (md_lb->a.fl)
//! macro substitution of the structure sd_l -> a.fl
#define sfpslb(a) (sd_lb->a.fl)
//! macro substitution of the structure mf_l -> a.fl
#define fpsfl(a) (mf_l->a.fl)
//! macro substitution of the structure mf_la -> a.fl
#define fpsfla(a) (mf_la->a.fl)
//! macro substitution of structure mf_lb -> a.fl
#define fpsflb(a) (mf_l->a.fl)

/*!
 * \brief PID controller structure
 */
typedef struct {
    //! current variable
    B32_Numb_S cur_var;
    //! previous variable
    B32_Numb_S prvs_var;
    //! proportional coefficient of the pid controller
    B32_Numb_S k_prprprtnl;
    //! Ti of the pid regulator
    B32_Numb_S t_intgrl;
    //! integral of the proportional part of the pid controller
    B32_Numb_S p_intgrl;
    //! integral of the integral part of the pid regulator
    B32_Numb_S i_intgrl;
    //! differential t of the pid regulator
    B32_Numb_S t_dfrntl;
    //! error value
    B32_Numb_S error;
    //! dt value
    B32_Numb_S dt;
} PID_Rgltr_S;

/*
 * \brief Inverter model parameter group
 */
typedef struct {
	//! set frequency
	B32_Numb_S k_f_mul_ref;
	//! current motor speed
	B32_Numb_S k_f_mul;
	//! koefficient regulator amplitude
	B32_Numb_S k_reg_mul;
	//! nominal motor current
	B32_Numb_S isnom;
	//! current stator
	B32_Numb_S is;
	//! current phase u
	B32_Numb_S iu;
	//! current phase v
	B32_Numb_S iv;
	//! current phase w
	B32_Numb_S iw;
    //! current phase u1
    B32_Numb_S iu1;
    //! current phase v1
    B32_Numb_S iv1;
    //! current phase w1
    B32_Numb_S iw1;
	//! set rotation angle
	B32_Numb_S theta;
	//! sinus
    B32_Numb_S sin;
    //! cosinus
    B32_Numb_S cos;
	//! incremental part for acceleration from n(min) to n(nom)
	B32_Numb_S k_f_mul_plus;
	//! incremental part for deceleration from n(nom) to n(min)
	B32_Numb_S k_f_mul_minus;
	//! current value of rotor position
	B32_Numb_S cur_pstn_rtr;
	//! phase voltage U
	B32_Numb_S uu;
	//! phase voltage U1
	B32_Numb_S uu1;
	//! phase voltage V
	B32_Numb_S uv;
    //! phase voltage V1
    B32_Numb_S uv1;
	//! phase voltage W
	B32_Numb_S uw;
	//! phase voltage W1
	B32_Numb_S uw1;
	//! position rotor of structure PID regulator
	PID_Rgltr_S pstn_rtr;
    //! voltage  phase A first invertor
	B32_Numb_S uac_os_1_0;
	//! voltage  phase B first invertor
	B32_Numb_S uac_os_2_0;
	//! voltage  phase C first invertor
	B32_Numb_S uac_os_3_0;
	//! voltage  phase A second invertor
	B32_Numb_S uac_os_1_1;
    //! voltage  phase B second invertor
	B32_Numb_S uac_os_2_1;
    //! voltage  phase B second invertor
	B32_Numb_S uac_os_3_1;
    //! voltage  phase u first invertor
    B32_Numb_S uu_os;
    //! voltage  phase v first invertor
    B32_Numb_S uv_os;
    //! voltage  phase w first invertor
    B32_Numb_S uw_os;
    //! voltage  phase u1 second invertor
    B32_Numb_S uu1_os;
    //! voltage  phase v1 second invertor
    B32_Numb_S uv1_os;
    //! voltage  phase w1 second invertor
    B32_Numb_S uw1_os;
    //! level voltage DC
	B32_Numb_S udc;
    //! level temperature
	B32_Numb_S temp;
    //! level current assignment
	B32_Numb_S izad_20_ma;
    //! level frequency assignment
	B32_Numb_S fzad_20_ma;
    //! current phase A first invertor
	B32_Numb_S i_os_1_0;
    //! current phase B first invertor
	B32_Numb_S i_os_2_0;
    //! current phase C first invertor
	B32_Numb_S i_os_3_0;
	//! current phase A second invertor
	B32_Numb_S i_os_1_1;
    //! current phase B second invertor
	B32_Numb_S i_os_2_1;
    //! current phase B third invertor
	B32_Numb_S i_os_3_1;
} Model_Data_PMSM_S;

/*
 * \brief Setting data of the frequency inverter
 */
typedef struct {
    //! time of frequency acceleration from 0 to nominal value in sec.
    B32_Numb_S accel_sec_up;
    //! time of frequency deceleration from nominal value to 0 in sec.
    B32_Numb_S accel_sec_down;
    //! real value of the set frequency
    B32_Numb_S real_ref;
    //! conversion coefficient from the real value of speed to the relative one
    float32 k_real_to_mul_ref;
    //! conversion factor from relative speed value to real speed value
    B32_Numb_S k_mul_to_real_ref;
    //! real value of the set frequency
    B32_Numb_S real_frq;
    //! real value of motor stator current
    B32_Numb_S real_cur_i_sttr;
    //! conversion factor from relative current value to real current value
    B32_Numb_S k_mul_to_real_i_sttr;
    //! conversion factor from relative rotor position to real rotor position
    float32 k_diskr_to_real_i_pstn_rtr;
    //! real DC link value
    B32_Numb_S real_udc;
    //! conversion factor from relative voltage value to real voltage value
    float32 k_mul_to_real_udc;
    //! set frequency from external setpoint adjuster
    float32 k_mul_ext_ref;
    //! discrete value of the current rotor position
    float32 diskr_cur_pstn_rtr;
    //! integration constant of the rotor position controller pid
    B32_Numb_S const_integr_pid_pid_reg_pstn_rtr;
    //! integration constant of the rotor position controller pid
    B32_Numb_S const_differntl_pid_reg_reg_pstn_rtr;
} Settng_Data_PMSM_S;

/*!
 * \brief Control and setting data of the frequency inverter
 */
typedef struct {
    //! frequency converter control model data
	Model_Data_PMSM_S md;
	//! setting data of the frequency converter control model
	Settng_Data_PMSM_S sd;
} Data_PMSM_S;

/*!
 * \brief Data for viewing the dynamic parameters of the frequency inverter
 */
typedef struct {
    //! frequency converter control error
    B32_Numb_S sub_theta_md;
    //! frequency converter rotor position
    float32 pstn_rtr_md;
    //! parameter view pointer
    float32 *pbrws;
} Brws_Param_Drive;


//////////////// DECLARATION OF EXTERNAL ACCESS TO FUNCTIONS /////////////////////
//! declaration of external access to a function PMSMotorFuncScalInit
extern void PMSMotorFuncInit(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l);
//! declaration of external access to a function PMSMotorFuncReset
extern void PMSMotorFuncReset(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l);
//! declaration of external access to a function PMSMotorFuncScal
extern void PMSMotorFuncScal(Model_Data_PMSM_S *md_la, Flg_Cntrl_Drive_S *mf_la, Brws_Param_Drive *bpd_la);
//! declaration of external access to a function PMSMotorFuncTechSpec
extern void PMSMotorFuncTechSpec(Model_Data_PMSM_S *md_la, Flg_Cntrl_Drive_S *mf_la, Brws_Param_Drive *bpd_la);
//! declaration of external access to a function PMSMotorFuncTechSpecWithoutIntenstCntrllr
extern void PMSMotorFuncTechSpecWithoutIntenstCntrllr(Model_Data_PMSM_S *md_la, Flg_Cntrl_Drive_S *mf_la, Brws_Param_Drive *bpd_la);
//! declaration of external access to a function PMSMotorFuncSensorless
extern void PMSMotorFuncSensorless(Model_Data_PMSM_S *md_la, Flg_Cntrl_Drive_S *mf_la, Brws_Param_Drive *bpd_la);
//! declaration of external access to a function CntrlDrive
extern void CntrlDrive(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l, Brws_Param_Drive *bpd_l);
//! declaration of external access to a function CntrlDrive
extern void HandlerExternalButtons(Flg_Cntrl_Drive_S *mf_l);
//! declaration of external access to a function HandlerFreezeProtection
extern void HandlerFreezeProtection();
//! declaration of external access to a function HandlerSwitchProcessing
extern Uint16 HandlerSwitchProcessing(Uint16 current_count, Uint16 maxCount);
#endif
