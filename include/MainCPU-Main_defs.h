//###########################################################################
//
// FILE:   MainCPU-Main.h
//
// TITLE: Заголовочный файл: MainCPU-Main.c
//
//###########################################################################

#ifndef MAINCPU_MAIN_DEFS_H
#define MAINCPU_MAIN_DEFS_H


////////////////////// ПОДКЛЮЧЕНИЕ ЗАГОЛОВОЧНЫХ ФАЙЛОВ //////////////////////
// подключение заголовочного файла "BaseDriveUsr.h"
#include "BaseDrive.h"
// подключение заголовочного файла "RegParamDrive.h"
#include "RegParamDrive.h"
// подключение заголовочного файла "RegParamDrive.h"
#include "FlagParamDrive.h"


////////////////////// ОБЪЯВЛЕНИЕ ИМЕНОВАННЫХ КОНСТАНТ //////////////////////
// время задержки включения в секундах
#define TIME_DELAY_IN_SEC	0.00001
// отключить микросхему AD2S90
#define CS_AD2S90_OFF 		GpioDataRegs.GPASET.bit.GPIO19 = 1
// подключить микросхему AD2S90
#define CS_AD2S90_ON  		GpioDataRegs.GPACLEAR.bit.GPIO19 = 1
// перевод микросхемы RS485A в состояние передачи
#define DE_RS485A_ON 		GpioDataRegs.GPASET.bit.GPIO27 = 1;
// перевод микросхемы RS485A в состояние приёма
#define DE_RS485A_OFF 		GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;
// перевод микросхемы RS485B в состояние передачи
#define DE_RS485B_ON 		GpioDataRegs.GPASET.bit.GPIO21 = 1;
// перевод микросхемы RS485B в состояние приёма
#define DE_RS485B_OFF 		GpioDataRegs.GPACLEAR.bit.GPIO21 = 1;
// период базового цикла таймерного шим прерывания
#define	PERD_BASE_CYCLE 	(5515 * 1.5)
// период пользовательского шим'а для просматора переменных
#define	PWM_USR 			250
// период пользовательского шим'а для просматора переменных делённый на 2
#define	PWM_USR_DIV_2 		PWM_USR / 2
// период фазного шим'а
#define PWM_OUT_PHASE		7500
// период фазного шим'а делённый на 2
#define PWM_OUT_PHASE_DIV_2	PWM_OUT_PHASE / 2
// задержка modbus посылки, для передачи между посылками
#define TIMECNT_DELAY_MB 	70000
// формат: DIV_делимое_делитель; именованная константа равна 1/4096
#define K_1_DIV_4096	 	0.000244140625


//////////////// ОБЪЯВЛЕНИЕ ВНЕШНЕГО ДОСТУПА К ПЕРЕМЕННЫМ //////////////////
// память флагов преобразователя частоты
extern Flg_Cntrl_Drive_S flags_drive;
// память параметров преобразователя частоты (общая память)
extern Rpd_Ctrl_Regs_S rpd_ctrl_regs;
// память параметров преобразователя частоты  (память модели)
extern Data_PMSM_S data_pmsm;
// память сервисных параметров modbus
extern MB_Servc mb_servc;
// указатель на память modbus
extern Uint16 	*pMBmemory;
// объявление просматривания параметров
extern Brws_Param_Drive brwsr;


//////////////// ОБЪЯВЛЕНИЕ ВНЕШНЕГО ДОСТУПА К ФУНКЦИЯМ ////////////////////
// таймерное прерывание по ШИМ'у прерывания epwm6_timer_isr
extern interrupt void epwm6_timer_isr(void);


#endif
