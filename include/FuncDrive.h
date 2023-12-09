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


////////////////////// ПОДКЛЮЧЕНИЕ ЗАГОЛОВОЧНЫХ ФАЙЛОВ //////////////////////
// подключение заголовочного файла "BaseDriveUsr.h"
#include "BaseDrive.h"
// подключение заголовочного файла "Flg_Cntrl_Drive_S.h"
#include "FlagParamDrive.h"


////////////////////// ОБЪЯВЛЕНИЕ ИМЕНОВАННЫХ КОНСТАНТ //////////////////////
// количество дискрет на полный оборот
#define	FULL_DSKRT			359.999
// константа постоянной времени для вычисление секунды (1 / (время цикла * 2 ))
#define CONST_ACCEL 		18181.81818181818
// формат: DIV_делимое_делитель; именованная константа равна 1/SQRT(3)
#define DIV_1_SQRT3			0.5773502691896259
// формат: DIV_делимое_делитель; именованная константа равна SQRT(3)/2
#define DIV_SQRT3_2			0.8660254037844386
// формат: DIV_делимое_делитель; именованная константа равна 2/SQRT(3)
#define DIV_2_SQRT3			1.154700538379252
// формат: DIV_делимое_делитель; именованная константа равна 1/2
#define DIV_1_2				0.5
// формат: DIV_делимое_делитель; именованная константа равна 1/90
#define DIV_1_90			1 / 90
// уставка перегрузки по току
#define KOVRLD_I_FROM_NOM	1.1
// формат: MUL_множитель.1_множитель.2; именованная константа равна 1*10
#define MUL_1_10 			10
// коэффициент стабилизации im настроен на время 30 мс
#define KIM_EQLZTN			1 / (30 * 10 * 1.804402742692169)
// уставка максимального значения реактивного тока
#define MAX_IR				0.23
// время разгона с n(min) до n(nom)
#define ACCEL_UP			5
// время замедления с n(nom) до n(min)
#define ACCEL_DOWN			5
// номинальная скорость в об/мин
#define NOM_SPEED			1000
// номинальное значение тока статора
#define NOM_I_STATOR		25
// число пар полюсов
#define NUMB_PAIR_POLES		3
// формат: DIV_делимое_делитель; именованная константа равна 1/360
#define K_1_DIV_360		 	0.0027777777777778
// формат: DIV_делимое_делитель; именованная константа равна 1/4
#define K_1_DIV_4			0.25




//////////////// ОБЪЯВЛЕНИЕ ВНЕШНЕГО ДОСТУПА К ФУНКЦИЯМ /////////////////////
// объявление функции Stop
extern void Stop(Model_Data_PMSM_S *md_la, Settng_Data_PMSM_S *sd_la, Flg_Cntrl_Drive_S *mf_la );
// объявление внешнего доступа к функции CalcSinCos
extern void (**pCalcSinCos)(float32 theta_lb, float32 *sin_lb, float32 *cos_lb);
// объявление внешнего доступа к функции CalcIm
extern float32 CalcIm(float32 kf_multiply_lb, float32 kim_eqlztn_lb, float32 *eqlztn_im_lb);
// объявление внешнего доступа к функции ApprdFltr
extern float32 ApprdFltr(float32 first_var_lb, float32 Ti_apprd_lb, float32 *integr_lb);
// объявление внешнего доступа к функции Calc2To3Cos
extern void Calc2To3Cos(float32 first_var_lb, float32 sec_var_lb, float32 *first_res_lb, float32 *sec_res_lb, float32 *third_res_lb);
// объявление внешнего доступа к функции Calc3To2
extern void Calc3To2(float32 first_var_lb, float32 sec_var_lb, float32 third_var_lb, float32 *first_res_lb, float32 *sec_res_lb);
// объявление внешнего доступа к функции SpeedRef
extern void SpeedRef(float32 k_f_mul_ref_lb, float32 k_f_mul_plus_lb, float32 k_f_mul_minus_lb, float32 *k_f_mul_lb);
// объявление внешнего доступа к функции CalcLengthVect2In
extern float32 CalcLengthVect2In(float32 first_lb, float32 secnd_lb);
// объявление внешнего доступа к функции PID_Regltr
extern float32 PID_Regltr(PID_Rgltr_S *v_pid_r_lb);
// объявление внешнего доступа к функции CalcSpeedRtr
extern float32 CalcSpeedRtr(float32 theta_rtr_lb, float32 *ptheta_rtr_lb,  float32 *pcalc_speed_rez_lb);


#endif
