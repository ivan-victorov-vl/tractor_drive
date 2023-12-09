//###########################################################################
//
// FILE: ProtecnDrive.c
//
// TITLE: Protection drive support functions.
//
// NOTES:
//
//###########################################################################


////////////////////// ПОДКЛЮЧЕНИЕ ЗАГОЛОВОЧНЫХ ФАЙЛОВ //////////////////////
// подключение заголовочного файла PeripheralHeaderIncludes.h
#include "PeripheralHeaderIncludes.h"
// подключенных заголовочного файла ProtectnDrive.h
#include "ProtectnDrive.h"


/////////////////////////// ОБЪЯВЛЕНИЕ ФУНКЦИЙ //////////////////////////////
// объявление функции защиты MaxMotorIPrtctn
retval_t MaxMotorIPrtctn(float32 iu_l_a, float32 iv_l_a, float32 iw_l_a, float32 valmax_prtctn_l_a);
// объявление указателя функции защиты pMaxMotorIPrtctn
retval_t (*pMaxMotorIPrtctn)(float32 iu_l_a, float32 iv_l_a, float32 iw_l_a, float32 valmax_prtctn_l_a) = &MaxMotorIPrtctn;

// объявление функции защиты TimeIMotorPrtctn
retval_t TimeIMotorPrtctn(float32 istator_l, float32 ki_integral_l, float32 i_nom_l, float32 *i_intgrl_l, float32 activ_intgr_prtctn_l);
// объявление указателя функции защиты pTimeIMotorPrtctn
retval_t (*pTimeIMotorPrtctn)(float32 istator_l, float32 ki_integral_l, float32 i_nom_l, float32 *i_intgrl_l, float32 activ_intgr_prtctn_l) = &TimeIMotorPrtctn;

// объявление функции защиты BreakPhasePrtctn
retval_t BreakPhasePrtctn(float32 urefu_l, float32 urefv_l, float32 urefw_l, float32 iu_l, float32 iv_l, float32 iw_l, float32 valmax_prtctn_l, float32 ku_multiply_l);
// объявление указателя функции защиты pBreakPhasePrtctn
retval_t (*pBreakPhasePrtctn)(float32 urefu_l, float32 urefv_l, float32 urefw_l, float32 iu_l, float32 iv_l, float32 iw_l, float32 valmax_prtctn_l, float32 ku_multiply_l) = &BreakPhasePrtctn;

// объявление функции защиты pMaxUDCMotorPrtctn
retval_t MaxUDCMotorPrtctn(float32 udc_l, float32 udc_nom_max_l);
// объявление указателя функции защиты pMaxUDCMotorPrtctn
retval_t (*pMaxUDCMotorPrtctn)(float32 udc_l, float32 udc_nom_max_l) = &MaxUDCMotorPrtctn;

// объявление функции защиты MinUDCMotorPrtctn
retval_t MinUDCMotorPrtctn(float32 udc_l, float32 udc_nom_min_l);
// объявление указателя функции защиты pMinUDCMotorPrtctn
retval_t(*pMinUDCMotorPrtctn)(float32 udc_l, float32 udc_nom_min_l) = &MinUDCMotorPrtctn;

// объявление функции PressFaultMotorPrtctn
retval_t PressFaultMotorPrtctn(Uint16 press_fault_l);
// объявление указателя функции pPressFaultMotorPrtctn
retval_t (*pPressFaultMotorPrtctn)(Uint16 press_fault_l) = &PressFaultMotorPrtctn;




////////////////////////// ФУНКЦИИ ЗАЩИТЫ ДВИГАТЕЛЯ /////////////////////////
//----------------------------------------------------------------------------------------------------------------
// Функция:  			MaxMotorIPrtctn
// Описание: 			Проверка события "превышение тока по одной из трёх фаз"
// Вход:  	  			(ток фазы u, ток фазы v, ток фазы w, уставка по превышению тока)
// Выход: 	  			(состояние проверки ошибки максимально-токовой защиты)
// Возвр.знач.ф-ции.:	(нет ошибки, ошибка по максимально-токовой защите)(SUCCESS|ERROR))
// Пример вызова: 		MaxMotorIPrtctn(float32 ток фазы u, float32 ток фазы v, float32 ток фазы w, float32 уставка по превышению тока)
//----------------------------------------------------------------------------------------------------------------
retval_t MaxMotorIPrtctn(float32 iu_la, float32 iv_la, float32 iw_la, float32 valmax_prtctn_la)
{
	// объявление начального состояния максимально - токовой защиты
	retval_t StatMotorErr = SUCCESS;


	// приведение уставки по превышению тока к квадратичному виду
	valmax_prtctn_la *= valmax_prtctn_la;
	// выполнение условия срабатыванивания максимально токовой защиты
	if (((iu_la * iu_la) > valmax_prtctn_la) || ((iv_la * iv_la) > valmax_prtctn_la) ||
	((iw_la * iw_la) > valmax_prtctn_la))
	{
		// детектирование обнаружения ошибки максимально-токовой защиты
		StatMotorErr = ERROR;
	}

	// возвратить состояние функции
	return StatMotorErr;
}



//----------------------------------------------------------------------------------------------------------------
// Функция:  			TimeIMotorPrtctn
// Описание: 			Проверка события "время-токовая защита"
// Вход:  	  			(ток статора, коэффициент суммы, номинальный ток, &суммарное накопление время-токовой защиты, уставка срабатывания защиты)
// Выход: 	  			(состояние проверки ошибки максимально-токовой защиты)
// Возвр.знач.ф-ции.:	(нет ошибки, ошибка по максимально-токовой защите)(SUCCESS|ERROR)
// Пример вызова: 		TimeIMotorPrtctn(float32 ток статора, float32 коэффициент суммы, float32 номинальный ток, float32 &суммарное накопление время-токовой защиты, уставка срабатывания защиты)
//----------------------------------------------------------------------------------------------------------------
retval_t TimeIMotorPrtctn(float32 istator_la, float32 ki_sum_ti_la, float32 i_nom_la,  float32 *i_sum_ti_la, float32 activ_intgr_prtctn_la)
{
	// объявление начального состояния
	retval_t StatMotorErr = SUCCESS;


	// вычисление интеграла
	*i_sum_ti_la += ki_sum_ti_la * (i_nom_la - istator_la);

	// если значение интеграла меньше 0
	if (*i_sum_ti_la <= 0)
		// обнулить интеграл
		*i_sum_ti_la = 0;

	// если интеграл больше установленного значения
	if (*i_sum_ti_la > activ_intgr_prtctn_la)
		StatMotorErr = ERROR;

	// возвратить состояние функции
	return StatMotorErr;
}



//----------------------------------------------------------------------------------------------------------------
// Функция:  			BreakPhasePrtctn
// Описание: 			Проверка события "защита от обрыва фазы"
// Вход:  	  			(заданное напряжение фазы U, заданное напряжение фазы V, заданное напряжение фазы W, измеренный ток фазы U, измеренный ток фазы V, уставка превышения обрыва фазы, коэффициент напряжения)
// Выход: 	  			(состояние проверки ошибки защиты от обрыва фазы U,V,W)
// Возвр.знач.ф-ции.:	(нет ошибки, обрыв фазы U, обрыв фазы V, обрыв фазы W)(SUCCESS|ERROR)
// Пример вызова: 		BreakPhasePrtctn(float32 заданное напряжение фазы U, float32 заданное напряжение фазы V, float32 заданное напряжение фазы W, float32 измеренный ток фазы U, float32 измеренный ток фазы V, float32 уставка превышения обрыва фазы, float32 коэффициент напряжения)
//----------------------------------------------------------------------------------------------------------------
retval_t BreakPhasePrtctn(float32 urefu_la, float32 urefv_la, float32 urefw_la, float32 iu_la, float32 iv_la, float32 iw_la, float32 valmax_prtctn_la, float32 ku_multiply_la)
{
	// объявление начального состояния
	retval_t StatMotorErr = SUCCESS;


	// установка значения обрыва фазы
	valmax_prtctn_la *= (ku_multiply_la * ku_multiply_la) * DIV_1_2;

	// проверка на обрыв фазы U
	if ( ( (urefu_la * urefu_la) - (iu_la * iu_la) ) > valmax_prtctn_la)
		// установка состояния: обрыв фазы U
		StatMotorErr = ERROR;

	// проверка на обрыв фазы V
	if ( ( (urefv_la * urefv_la) - (iv_la * iv_la) ) > valmax_prtctn_la)
		// установка состояния: обрыв фазы V
		StatMotorErr = ERROR;

	// проверка на обрыв фазы W
	if ( ( (urefw_la * urefw_la) - (iw_la * iw_la) ) > valmax_prtctn_la)
		// установка состояния: обрыв фазы W
		StatMotorErr = ERROR;

	// возвратить состояние функции
	return StatMotorErr;
}



//----------------------------------------------------------------------------------------------------------------
// Функция:  			MaxUDCMotorPrtctn
// Описание: 			Проверка события "превышение напряжение"
// Вход:  	  			(постоянное напряжения, уставка по превышению постоянного напряжения)
// Выход: 	  			(состояние проверки по превышению напряжения)
// Возвр.знач.ф-ции.:	(нет ошибки, ошибка по превышению напряжения)(SUCCESS|ERROR)
// Пример вызова: 		MaxUDCMotorPrtctn(float32 постоянное напряжения, float32 уставка по превышению постоянного напряжения)
//----------------------------------------------------------------------------------------------------------------
retval_t MaxUDCMotorPrtctn(float32 udc_la, float32 udc_nom_max_la)
{
	// объявление начального состояния
	retval_t StatMotorErr = SUCCESS;


	// проверка на превышение по постоянному напряжению
	if (udc_la > (udc_nom_max_la * KMAX_UDC_FROM_NOM))
		// установка состояния : превышение по максимальному напряжению
		StatMotorErr = ERROR;

	// возвратить состояние функции
	return StatMotorErr;
}



//----------------------------------------------------------------------------------------------------------------
// Функция:  			MinUDCMotorPrtctn
// Описание: 			Проверка события "чересчур низкое напряжение"
// Вход:  	  			(постоянное напряжения, уставка на слишком низкое)
// Выход: 	  			(состояние проверки на чересчур низкое напряжение)
// Возвр.знач.ф-ции.:	(нет ошибки, ошибка на чересчур низкое напряжение)(SUCCESS|ERROR)
// Пример вызова: 		MinUDCMotorPrtctn(float32 постоянное напряжения, float32 уставка на слишком низкое напряжения)
//----------------------------------------------------------------------------------------------------------------
retval_t MinUDCMotorPrtctn(float32 udc_la, float32 udc_nom_min_la)
{
	// объявление начального состояния
	retval_t StatMotorErr = SUCCESS;


	// проверка на превышение по постоянному напряжению
	if (udc_la < (udc_nom_min_la * KMIN_UDC_FROM_NOM))
		// установка состояние проверки : слишком низкое напряжение
		StatMotorErr = ERROR;

	// возвратить состояние функции
	return StatMotorErr;
}



//----------------------------------------------------------------------------------------------------------------
// Функция:  			PressFaultMotorPrtctn
// Описание: 			Проверка события "нажата АВАРИЯ"
// Вход:  	  			(состояние кнопки АВАРИЯ)
// Выход: 	  			(состояние проверки на нажатие кнопки АВАРИЯ)
// Возвр.знач.ф-ции.:	(нет ошибки, нажата кнопка АВАРИЯ)(SUCCESS|ERROR)
// Пример вызова: 		PressFaultM6otorPrtctn(float32 состояние кнопки АВАРИЯ)
//----------------------------------------------------------------------------------------------------------------
retval_t PressFaultMotorPrtctn(Uint16 press_fault_la)
{
	// объявление начального состояния
	retval_t StatMotorErr = SUCCESS;


	// если нажата кнопка АВАРИЯ
	if (press_fault_la)
		// установка состояния что нажата кнопка АВАРИЯ
		StatMotorErr = ERROR;

	// возвратить состояние функции
	return StatMotorErr;
}
