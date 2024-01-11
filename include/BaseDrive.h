//###########################################################################
//
// FILE:    	BaseDrUsr.h
//
// TITLE:   	BaseDrUsr.c header file
//
//###########################################################################

#ifndef BASEDRIVE_H_
#define BASEDRIVE_H_


////////////////////// ПОДКЛЮЧЕНИЕ ЗАГОЛОВОЧНЫХ ФАЙЛОВ //////////////////////
// подключение заголовочного файла "SysSrvc.h"
#include "SysSrvc.h"
// подключение заголовочного файла "Flg_Cntrl_Drive_S.h"
#include "FlagParamDrive.h"
//  подключение заголовочного файла "RegParamDrive.h"
#include "RegParamDrive.h"


////////////////////// ОБЪЯВЛЕНИЕ ИМЕНОВАННЫХ КОНСТАНТ //////////////////////
// формат: DIV_делимое_делитель; именованная константа равна 4096/360
#define DIV_4096_360	11.37777777777778
// формат: DIV_делимое_делитель; именованная константа равна 1/360
#define DIV_1_360	0.0027777777777778
// формат: DIV_делимое_делитель; именованная константа равна 3/360
#define DIV_3_360	0.0083333333333333
// пропорциональный коэффициент пид регулятора положения ротора
#define K_PRPRTNL_PSTN	0.0077
// постоянная времени пид регулятора положения ротора при инциализации равна бесконечности
#define T_INTGRL_PSTN	7
// постоянная времени дифферинциального коэффициента пид регулятора положения ротора
#define T_DFRNTNL_PSTN	99999999999


///////////////////////////  МАКРОПОДСТАНОВКА ///////////////////////////////
// Подстановка обозначает следующие значения букв
// 1-ая буква		f - float
//					s -параметры настройки
// 2-ая буква		p - указатель на структуру
//					f - float
// 3-я буква		s - структура
//					p - указатель на структуру
// 4-я буква		l - локальная структура
//					f - флаг
// 					s - структура
// 5-я буква		a - уровень дерева, где (пустота - 0-ой уровень), a - 1-ый уровень
//					l - локальная структура
//
// Последняя буква	a - 1-ый уровень дерева
// 					b - 2-ый уровень дерева
//
// макроподстановка структуры md_l -> a.fl
#define fpsl(a)	 			(md_l->a.fl)
// макроподстановка структуры sd_l -> a.fl
#define sfpsl(a)			(sd_l->a.fl)
// макроподстановка структуры md_la -> a.fl
#define fpsla(a)	 		(md_la->a.fl)
// макроподстановка структуры sd_l -> a.fl
#define sfpsla(a)			(sd_la->a.fl)
// макроподстановка структуры md_lb -> a.fl
#define fpslb(a)	 		(md_lb->a.fl)
// макроподстановка структуры sd_l -> a.fl
#define sfpslb(a)			(sd_lb->a.fl)
// макроподстановка структуры mf_l -> a.fl
#define fpsfl(a)  			(mf_l->a.fl)
// макроподстановка структуры mf_la -> a.fl
#define fpsfla(a) 			(mf_la->a.fl)
// макроподстановка структуры mf_lb -> a.fl
#define fpsflb(a)  			(mf_l->a.fl)



//----------------------------------------------------------------------------------------------------------------
// Группа параметра: 					(Данные ПЧ )
// Название идентификационных данных: 	Структура ПИД регулятора
// Доступ к регистру 					Чтение / Запись
//----------------------------------------------------------------------------------------------------------------
typedef struct
{
	// текущая переменная
	B32_Numb_S cur_var;
	// предыдущая переменная
	B32_Numb_S prvs_var;
	// пропорциональный коэффициент пид регулятора
	B32_Numb_S k_prprtnl;
	// интегральный коэффициент пид регулятора
	B32_Numb_S k_intgrl;
	// интеграл пропорциональной части пид регулятора
	B32_Numb_S p_intgrl;
	// интеграл интегральной части пид регулятора
	B32_Numb_S i_intgrl;
	// дифферинциальный коэффициент пид регулятора
	B32_Numb_S k_dfrntl;
} PID_Rgltr_S;


/*
 * \brief Inverter model parameter group
 */
typedef struct
{
	//! set freauency
	B32_Numb_S k_f_mul_ref;
	//! current motor speed
	B32_Numb_S k_f_mul;
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
	//! set rotation angle
	B32_Numb_S theta;
	//! incremental part for acceleration from n(min) to n(nom)
	B32_Numb_S k_f_mul_plus;
	//! incremental part for deceleration from n(nom) to n(min)
	B32_Numb_S k_f_mul_minus;
	//! current value of rotor position
	B32_Numb_S cur_pstn_rtr;
	//! phase voltage U
	B32_Numb_S uu;
	//! phase voltage V
	B32_Numb_S uv;
	//! phase voltage W
	B32_Numb_S uw;
	//! position rotor of structure PID regulator
	PID_Rgltr_S pstn_rtr;
    //! voltage  phase A first invertor
	B32_Numb_S uac_is_1_0;
	//! voltage  phase B first invertor
	B32_Numb_S uac_is_2_0;
	//! voltage  phase C first invertor
	B32_Numb_S uac_is_3_0;
	//! voltage  phase A second invertor
	B32_Numb_S uac_is_1_1;
    //! voltage  phase B second invertor
	B32_Numb_S uac_is_2_1;
    //! voltage  phase B second invertor
	B32_Numb_S uac_is_3_1;
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


//----------------------------------------------------------------------------------------------------------------
// Группа параметра: 					( Данные ПЧ )
// Название идентификационных данных: 	Данные настройки преобразователя частоты
// Доступ к регистру 					Чтение / Запись
//----------------------------------------------------------------------------------------------------------------
typedef struct
{
	// время разгона частоты от 0 до номинального значения в сек.
	B32_Numb_S accel_sec_up;
	// время замедления частоты от номинального значения до 0 в сек.
	B32_Numb_S accel_sec_down;
	// реальное значение заданной частоты
	B32_Numb_S real_ref;
	// коэффициент перевода из реального значения скорости в относительное
	float32 k_real_to_mul_ref;
	// коэффициент перевода из относительного значения скорости в реальное
	B32_Numb_S k_mul_to_real_ref;
	// реальное значение заданной частоты
	B32_Numb_S real_frq;
	// реальное значение тока статора двигателя
	B32_Numb_S real_cur_i_sttr;
	// коэффициент перевода из относительного значения тока в реальное
	B32_Numb_S k_mul_to_real_i_sttr;
	// коэффициент перевода из относительного положения ротора в реальное
	float32 k_diskr_to_real_i_pstn_rtr;
	// реальное значение звена постоянного тока
	B32_Numb_S real_udc;
	// коэффициент перевода из относительного значения напряжения в реальное
	float32 k_mul_to_real_udc;
	// заданная частота с внешнего задатчика
	float32 k_mul_ext_ref;
	// дискретное значение текущего положения ротора
	float32 diskr_cur_pstn_rtr;
	// постоянная интегрирования пид регулятора положения ротора
	B32_Numb_S const_integr_pid_reg_pstn_rtr;
	// постоянная дифферинцирования пид регулятора положения ротора
	B32_Numb_S const_differntl_pid_reg_pstn_rtr;
} Settng_Data_PMSM_S;


//----------------------------------------------------------------------------------------------------------------
// Группа параметра: 					( Данные ПЧ )
// Название идентификационных данных: 	Данные управления и настройки преобразователя частоты
// Доступ к регистру 					Чтение / Запись
//----------------------------------------------------------------------------------------------------------------
typedef struct
{
	// данные модели управления преобразователем частоты
	Model_Data_PMSM_S md;
	// настроечные данные модели управления преобразователем частоты
	Settng_Data_PMSM_S sd;
} Data_PMSM_S;


//----------------------------------------------------------------------------------------------------------------
// Группа параметра: 					(Просмотр параметра динамических параметров ПЧ )
// Название идентификационных данных: 	Данные для просмотра динамических параметров преобразователя частоты
// Доступ к регистру 					Чтение / Запись
//----------------------------------------------------------------------------------------------------------------
typedef struct
{
	// ошибка по регулированию преобразователя частоты
	B32_Numb_S sub_theta_md;
	// положение ротора преобразователя частоты
	float32 pstn_rtr_md;
	// указатель просмотр параметров
	float32 *pbrws;
} Brws_Param_Drive;


//////////////// DECLARATION OF EXTERNAL ACCESS TO FUNCTIONS /////////////////////
//! declaration of external access to a function PMSMotorFuncScalInit
extern void PMSMotorFuncScalInit(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l);
//! declaration of external access to a function PMSMotorFuncReset
extern void PMSMotorFuncReset(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l);
//! declaration of external access to a function PMSMotorFuncScal
extern void PMSMotorFuncScal(Model_Data_PMSM_S *md_la, Flg_Cntrl_Drive_S *mf_la, Brws_Param_Drive *bpd_la);
//! declaration of external access to a function CntrlDrive
extern void CntrlDrive(Model_Data_PMSM_S *md_l, Settng_Data_PMSM_S *sd_l, Flg_Cntrl_Drive_S *mf_l, Brws_Param_Drive *bpd_l);

#endif
