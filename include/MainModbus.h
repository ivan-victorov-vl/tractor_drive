//###########################################################################
//
// Файл:    	MainModbus.h
//
// Описание:   	Заголовочный файл: MainModbus.c
//
//###########################################################################

#ifndef MAIN_MODBUS_H
#define MAIN_MODBUS_H

#ifdef __cplusplus
extern "C" {
#endif


////////////////////// ОБЪЯВЛЕНИЕ ИМЕНОВАННЫХ КОНСТАНТ //////////////////////
// константа обозначающая 1-ую функцию протокола modbus "READ COIL STATUS"
#define	MBREADCOILSTATUSF	1
// константа обозначающая 2-ую функцию протокола modbus "READ INPUT STATUS"
#define	MBREADINPUTSTATUSF	2
// константа обозначающая 3-ию функцию протокола modbus "READ HOLDING REGISTERS"
#define	MBREADHOLDINGREGSF	3
// константа обозначающая 4-ую функцию протокола modbus "READ INPUT REGISTERS"
#define	MBREADINPUTREGSF	4
// константа обозначающая 5-ую функцию протокола modbus "FORCE SINGLE COIL"
#define	MBFORCESINGLECOILF	5
// константа обозначающая 6-ую функцию протокола modbus "FORCE SINGLE REGISTER"
#define	MBPRESETSINGLEREGF	6
// константа обозначающая 15-ую функцию протокола modbus "FORCE MULTIPLE COILS"
#define	MBFORCEMULTCOILSF	15
// константа обозначающая 16-ую функцию протокола modbus "FORCE MULTIPLE REGISTERS"
#define	MBPRESETMULTREGSF	16


/////////////////////// ОБЪЯВЛЕНИЕ ТИПОВ ПЕРЕЧИСЛЕНИЯ ДАННЫХ //////////////////////////
// перечисление данных ошибок modbus
typedef enum
{
	// нет ошибки
    MB_ENOERR,
    // запрещенный адрес регистра
    MB_ENOREG,
    // запрещённый аргумент
    MB_EINVAL,
    // ошибка уровня порта
    MB_EPORTERR,
    // недостаточно ресурсов
    MB_ENORES,
    // ошибка ввода/вывода
    MB_EIO,
    // протокол стека находится в запрещённом состоянии
    MB_EILLSTATE,
    // идентифицированная ошибка time-out'а
    MB_ETIMEDOUT,
    // ошибка по недоступности функции
    MB_FUNCERR
} eMBErrorCode;


/////////////////////// ОБЪЯВЛЕНИЕ СТРУКТУР ДАННЫХ //////////////////////////
// структура данных сервисных флагов
typedef struct
{
	// флаг ожидания передачи
	Uint16 	rx_tx_idle : 1;
	// флаг направления передачи tx_rx == 1 (посылка) иначе (приём)
	Uint16  tx_rx:1;
	// флаг разрешения передачи посылки modbus запроса
	Uint16	tx_en_modbus:1;
	// флаг разрешения приёма посылки modbus запроса
	Uint16	rx_en_modbus:1;
	// флаг выбора передачи по каналам SCIA - 0; SCIB - 0;
	Uint16	sci_ab_tx:1;
} MB_Flgs_Srvc;


// структура данных сервисных параметров  modbus'а
typedef struct
{
	// массив принимаемой памяти
	Uint16	rx[130];
	// массив передаваемой памяти
	Uint16	tx[130];
	// текущий массив принимаемого сообщения
	Uint16 numb_mes_rx;
	// текущий массив передаваемого сообщения
	Uint16 numb_mes_tx;
	// счетчик времени для передачи по протоколу modbus
	Uint16 cnt_modbus_time;
	// счётчик выключения индикационной панели
	Uint32 cnt_vdhl_modbus;
	// modbus сервисные флаги
	MB_Flgs_Srvc flgs;
	// длина передаваемой посылки
	Uint16 length_tx;
	// указатель на приём посылки
	Uint16 *prx;
	// указатель на передачу посылки
	Uint16 *ptx;
	// состояние функции
	eMBErrorCode mb_status;
} MB_Servc;


//////////////// ОБЪЯВЛЕНИЕ ВНЕШНЕГО ДОСТУПА К ФУНКЦИЯМ /////////////////////
// объявление внешнего доступа к функции InitSCIA
extern void MBReadFuncSlave (MB_Servc *mb_servc_l, Uint16 *pMBmemory_l);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
