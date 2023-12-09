//###########################################################################
//
// FILE:    SysSrvc.h
//
// TITLE:   System service defenitions.
//
// NOTES:
//
//###########################################################################

#ifndef SYSSRVC_H_
#define SYSSRVC_H_


////////////////////// ОБЪЯВЛЕНИЕ ИМЕНОВАННЫХ КОНСТАНТ //////////////////////
// частота процессора в ГЦ
#define FRQ_HZ_PRCSR	150000000
// включение светодиода 	LED 1
#define	LED1_inv_clear 	GpioDataRegs.GPBCLEAR.bit.GPIO48 = 1;
// выключение светодиода 	LED 1
#define	LED1_inv_set   	GpioDataRegs.GPBSET.bit.GPIO48   = 1;
// включение светодиода 	LED 2
#define	LED2_inv_clear	GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1;
// выключение светодиода 	LED 2
#define	LED2_inv_set   	GpioDataRegs.GPBSET.bit.GPIO49   = 1;
// состояние светодиода 	LED 1
#define	LED1_inv_status	GpioDataRegs.GPBDAT.bit.GPIO48
// состояние светодиода 	LED 2
#define	LED2_inv_status	GpioDataRegs.GPBDAT.bit.GPIO49
// включение светодиода 	LED 1
#define OK_S_ON 		GpioDataRegs.GPCCLEAR.bit.GPIO66 = 1;
// выключение светодиода 	LED 1
#define	OK_S_OFF   		GpioDataRegs.GPCSET.bit.GPIO66   = 1;
// включение светодиода 	LED 2
#define	ERR_S_ON		GpioDataRegs.GPCCLEAR.bit.GPIO67 = 1;
// выключение светодиода 	LED 2
#define	ERR_S_OFF   	GpioDataRegs.GPCSET.bit.GPIO67   = 1;
// состояние нажатия кнопки "вверх" пульта
#define	UP_STATUS	 	GpioDataRegs.GPBDAT.bit.GPIO63
// состояние нажатия кнопки "вниз" пульта
#define	DOWN_STATUS	 	GpioDataRegs.GPBDAT.bit.GPIO62
// состояние нажатия кнопки "влево" пульта
#define	LEFT_STATUS	 	GpioDataRegs.GPBDAT.bit.GPIO61
// состояние нажатия кнопки "вправо" пульта
#define	RIGHT_STATUS 	GpioDataRegs.GPBDAT.bit.GPIO60
// состояние нажатия кнопки "выбор" пульта
#define	SEL_STATUS	 	GpioDataRegs.GPBDAT.bit.GPIO59
// состояние нажатия внешней кнопки "пуск"
#define	EXT_START		GpioDataRegs.GPBDAT.bit.GPIO53
// состояние нажатия внешней кнопки "стоп"
#define	EXT_STOP		GpioDataRegs.GPBDAT.bit.GPIO52
// масксимальное количество входов в фильтр кнопки
#define	N_CNT_FLTR_MAX	32000
// минимальное количество входов в фильтр кнопки
#define	N_CNT_FLTR_MIN	1000
// формат: DIV_делимое_делитель; именованная константа равна 1/6
#define DIV_1_6		0.1666666666666667


//////////////// ОБЪЯВЛЕНИЕ ВНЕШНЕГО ДОСТУПА К ФУНКЦИЯМ /////////////////////
// объявление внешнего доступа к функции TimeDelay
extern void TimeDelaySys(float32 time_in_sec_l);
// объявление внешнего доступа к функции Init_GPIO_0_5_in_PWM
extern void Init_GPIO_0_5_in_PWM(void);
// объявление внешнего доступа к функции HandlrBttn
extern Uint16 HandlrBttn(Uint16 push_l);
// объявление внешнего доступа к функции LimitVar
extern void LimitVar(float32 min_var, float32 max_var, float32 *var_lim);
// объявление внешнего доступа к функции FltrMas6Var
float32 FltrMas6Var(float32 cur_var, Uint16 *cur_mas, float32 *pmas_var);


/////////////////////// ОБЪЯВЛЕНИЕ СТРУКТУР ДАННЫХ //////////////////////////
// структура данных 32-битного числа
typedef union
{
 float32 fl;
 Uint32  uint;
} B32_Numb_S;


#endif
