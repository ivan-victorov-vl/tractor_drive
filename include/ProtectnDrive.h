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


////////////////////// ПОДКЛЮЧЕНИЕ ЗАГОЛОВОЧНЫХ ФАЙЛОВ //////////////////////
// подключение заголовочного файла "BaseDrive.h"
#include "BaseDrive.h"


/////////////////////// ОБЪЯВЛЕНИЕ ТИПОВ ДАННЫХ //////////////////////////
// тип данных ошибок
typedef enum
{
	// ошибок нет
	SUCCESS,
	// обнаружена ошибка
	ERROR
} retval_t;
// Примечение: В случае если данный тип данных имеется, требуется его удалить.


////////////////////// ОБЪЯВЛЕНИЕ ИМЕНОВАННЫХ КОНСТАНТ //////////////////////
// формат: DIV_делимое_делитель; именованная константа равна 1/2
#define DIV_1_2					0.5
// уставка по перегрузке по напряжению на звене постоянного тока
#define KMAX_UDC_FROM_NOM		1.2
// уставка по чересчур низкому напряжению на звене постоянного тока
#define KMIN_UDC_FROM_NOM		0.65
// уставка по перегрузке по напряжению на звене постоянного тока
#define KOVRLD_UDC_FROM_NOM		1.1
// уставка по перегрузке по напряжению на звене постоянного тока
#define KMINWRNG_UDC_FROM_NOM 	0.85


//////////////// ОБЪЯВЛЕНИЕ ВНЕШНЕГО ДОСТУПА К ФУНКЦИЯМ /////////////////////
// объявление внешнего доступа к функции pMaxMotorIPrtctn
extern retval_t (*pMaxMotorIPrtctn)(float32 iu_l_a, float32 iv_l_a, float32 iw_l_a, float32 valmax_prtctn_l_a);
// объявление внешнего доступа к функции pTimeIMotorPrtctn
extern retval_t (*pTimeIMotorPrtctn)(float32 istator_l, float32 ki_integral_l, float32 i_nom_l, float32 *i_intgrl_l, float32 activ_intgr_prtctn_l);
// объявление внешнего доступа к функции pBreakPhasePrtctn
extern retval_t (*pBreakPhasePrtctn)(float32 urefu_l, float32 urefv_l, float32 urefw_l, float32 iu_l, float32 iv_l, float32 iw_l, float32 valmax_prtctn_l, float32 ku_multiply_l);
// объявление внешнего доступа к функции pMaxUDCMotorPrtctn
extern retval_t (*pMaxUDCMotorPrtctn)(float32 udc_l, float32 udc_nom_max_l);
// объявление внешнего доступа к функции pMinUDCMotorPrtctn
extern retval_t(*pMinUDCMotorPrtctn)(float32 udc_l, float32 udc_nom_min_l);
// объявление внешнего доступа к функции pPressFaultMotorPrtctn
extern retval_t (*pPressFaultMotorPrtctn)(Uint16 press_fault_l);


#endif
