//###########################################################################
//
// FILE:	MainModbus.c
//
// TITLE:	Функции modbus устройства
//
//###########################################################################


////////////////////// ПОДКЛЮЧЕНИЕ ЗАГОЛОВОЧНЫХ ФАЙЛОВ //////////////////////
// подключение заголовочного файла "PeripheralHeaderIncludes.h"
#include "PeripheralHeaderIncludes.h"
// подключение заголовочного файла "MainModbus.h"
#include "MainModbus.h"


/////////////////////////// ОБЪЯВЛЕНИЕ ПРЕМЕННЫХ //////////////////////////////
// 16 битная контрольная сумма
Uint16 	usCRC16;


/////////////////////////// ОБЪЯВЛЕНИЕ ТАБЛИЦ //////////////////////////////
// таблица контрольной суммы 16 битного слова старшего разряда (циклически избыточного кода)
static const Uchar aucCRCHi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1,
    0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80,
    0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00,
    0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81,
    0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1,
    0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81,
    0x40
};


// таблица контрольной суммы 16 битного слова младшего разряда (циклически избыточного кода)
static const Uchar aucCRCLo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
    0x05, 0xC5, 0xC4,
    0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB,
    0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE,
    0xDF, 0x1F, 0xDD,
    0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2,
    0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
    0x36, 0xF6, 0xF7,
    0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E,
    0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B,
    0x2A, 0xEA, 0xEE,
    0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27,
    0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
    0x63, 0xA3, 0xA2,
    0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD,
    0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8,
    0xB9, 0x79, 0xBB,
    0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4,
    0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
    0x50, 0x90, 0x91,
    0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94,
    0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59,
    0x58, 0x98, 0x88,
    0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D,
    0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
    0x41, 0x81, 0x80,
    0x40
};


/////////////////////////// ОБЪЯВЛЕНИЕ ФУНКЦИЙ //////////////////////////////
// функция вычисления контрольной суммы 16 битного регистра
Ushort usMBCRC16	(Uchar * pucFrame, Ushort usLen);
// выбор функции и определение дальнейшего действия
void MBReadFuncSlave (MB_Servc *mb_servc_l, Uint16 *pMBmemory_l);
// объявление функции MBReadHoldingReg
eMBErrorCode MBReadHoldingReg(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la);
// объявление функции MBReadInptReg
eMBErrorCode MBReadInptReg(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la);
// объявление функции MBPresetMultReg
eMBErrorCode MBPresetMultRegs(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la);
// объявление функции MBForceMultCoils
eMBErrorCode MBForceMultCoils(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la);
// объявление функции MBPresetSinglReg
eMBErrorCode MBPresetSinglReg(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la);
// объявление функции MBWriteSinglCoil
eMBErrorCode MBWriteSinglCoil(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la);
// объявление функции MBReadCoils
eMBErrorCode MBReadCoils(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la);
// объявление функции MBReadDiscrInpts
eMBErrorCode MBReadDiscrInpts(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la);



//----------------------------------------------------------------------------------------------------------------
// Функция:  			usMBCRC16
// Описание: 			Вычисление контрольной суммы протокола modbus (циклически избыточного кода)
// Вход:  	  			Тип переменнойи:	Предназначение переменной:	Имя переменной:
//						Uchar				посылка данных				*pucFrame
//						Ushort				длина данных				usLen
// Выход: 	  			( - )
// Возвр.знач.ф-ции.:	Тип функции			Предназначение функции		Имя функции
//						Ushort				значение контрольной суммы	usMBCRC16
// Пример вызова: 		usMBCRC16(Uchar *посылка данных, Ushort длина данных)
//----------------------------------------------------------------------------------------------------------------
Ushort usMBCRC16(Uchar* pucFrame, Ushort usLen)
{
	// начальное значение контрольной суммы старшего разряда (циклически избыточного кода)
    Uchar ucCRCHi = 0xFF;
    // начальное значение контрольной суммы младшего разряда (циклически избыточного кода)
    Uchar ucCRCLo = 0xFF;
    int iIndex;

    // повторять до конца длины посылки
    while ( usLen-- )
    {
    	// вычисление индекса контрольной суммы
        iIndex = ucCRCLo ^ *( pucFrame++ );
        // вычисление старшего разряда контрольной суммы
        ucCRCLo = ucCRCHi ^ aucCRCHi[ iIndex ];
        // вычисление младшего разряда контрольной суммы
        ucCRCHi = aucCRCLo[ iIndex ];
    }
    return ucCRCHi << 8 | ucCRCLo;
}


//----------------------------------------------------------------------------------------------------------------
// Функция:  			MBReadFuncSlave
// Описание: 			Выбор функции и определение дальнейшего действия
// Вход:  	 	 		Структура данных сервисных параметров modbus'а:
//						"
//						Тип переменной:		Предназначение переменной:	Имя переменной:
//						Uint16				массив принимаемой памяти	mb_servc_l->rx
//						Uint16				массив передаваемой памяти	mb_servc_l->tx
//						"
//						Тип переменной:		Предназначение переменной:	Имя переменной:
//						Uint16				указатель modbus посылки	pMBmemory_l
// Выход: 	  			Структура данных сервисных параметров modbus'а:
//						"
//						Тип переменной:		Предназначение переменной:	Имя переменной:
//						Uint16				указатель на приём посылки	mb_servc_l->prx
//						Uint16				указатель на передачу 		mb_servc_l->ptx
//											посылки
//						eMBErrorCode		состояние функции			mb_servc_l->mb_status
//						"
// Возвр.знач.ф-ции.:	( - )
// Пример вызова: 		MBReadFuncSlave(MB_Servc *структура данных сервисных параметров modbus'а, Uint16 *указатель modbus посылки)
//----------------------------------------------------------------------------------------------------------------
void MBReadFuncSlave(MB_Servc *mb_servc_l, Uint16 *pMBmemory_l)
{
	// объявление состояние линии modbus
	mb_servc_l->mb_status = MB_ENOERR;

	// установление указателя на 0-ой адрес массива приёма
	mb_servc_l->prx = &mb_servc_l->rx[0];
	// установление указателя на 0-ой адрес массива передачи
	mb_servc_l->ptx = &mb_servc_l->tx[0];

	// выбор выполняемой функции
	switch (mb_servc_l->rx[1])
	{
		// если выбрана функция: modbus read coil status
		case MBREADCOILSTATUSF:
		// если выбрана функция (1), то выполнение чтение логических ячеек
		mb_servc_l->mb_status = MBReadCoils(&(*mb_servc_l), pMBmemory_l);
		// выход из переключателя switch
		break;

		// если выбрана функция: modbus read input status
		case MBREADINPUTSTATUSF:
		// если выбрана функция (2), то выполнение функции чтение дискретных входов
		mb_servc_l->mb_status = MBReadDiscrInpts(&(*mb_servc_l), pMBmemory_l);
		// выход из переключателя switch
		break;

		// если выбрана функция: modbus read holding register
		case MBREADHOLDINGREGSF:
		// если выбрана функция (3), то выполнение чтение регистров
		mb_servc_l->mb_status = MBReadHoldingReg(&(*mb_servc_l), pMBmemory_l);
		// выход из переключателя switch
		break;

		// если выбрана функция: modbus read input register
		case MBREADINPUTREGSF:
		// если выбрана функция (4), то выполнение чтение регистров
		mb_servc_l->mb_status = MBReadInptReg(&(*mb_servc_l), pMBmemory_l);
		// выход из переключателя switch
		break;

		// если выбрана функция: modbus force single coil
		case MBFORCESINGLECOILF:
		// если выбрана функция (5), то установка единичного выхода ON/OFF
		mb_servc_l->mb_status = MBWriteSinglCoil(&(*mb_servc_l), pMBmemory_l);
		// выход из переключателя switch
		break;

		// если выбрана функция: modbus preset single register
		case MBPRESETSINGLEREGF:
		// если выбрана функция (6), то выполнение запись одного регистра
		mb_servc_l->mb_status = MBPresetSinglReg(&(*mb_servc_l), pMBmemory_l);
		// выход из переключателя switch
		break;

		// если выбрана функция: modbus force multiple coils
		case MBFORCEMULTCOILSF:
		// если выбрана функция (15), то выполнение запись нескольких регистров
		mb_servc_l->mb_status = MBForceMultCoils(&(*mb_servc_l), pMBmemory_l);
		// выход из переключателя switch
		break;

		// если выбрана функция: modbus preset multiple register
		case MBPRESETMULTREGSF:
		// если выбрана функция (16), то выполнение запись нескольких регистров
		mb_servc_l->mb_status = MBPresetMultRegs(&(*mb_servc_l), pMBmemory_l);
		// выход из переключателя switch
		break;

		// если выбрана функция не используемая функция
		default:
		// идентификация состояния modbus как ошибка по недоступности выбранной функции
		mb_servc_l->mb_status = MB_FUNCERR;
		// выход из переключателя switch
		break;
	}
}


//----------------------------------------------------------------------------------------------------------------
// Функция:  			MBReadCoils
// Описание: 			Реализация функции 1, протокола modbus "чтение логических ячеек"
// Вход:  	  			Структура данных сервисных параметров modbus'а:
//						"
//						Тип переменной:		Предназначение переменной:	Имя переменной:
//						Uint16				массив принимаемой памяти	mb_servc_l->rx
//						Uint16				массив передаваемой памяти	mb_servc_l->tx
//						"
//						Тип переменной:		Предназначение переменной:	Имя переменной:
//						Uint16				указатель modbus посылки	pMBmemory_l
// Выход: 	  			Структура данных сервисных параметров modbus'а:
//						"
//						Тип функции:		Предназначение функции:		Имя функции:
// 						Uint16				длина передаваемой посылки	mb_servc_la->length_tx
//						Uint16				указатель на приём посылки	mb_servc_la->prx
//						Uint16				указатель на передачу 		mb_servc_la->ptx
//											посылки
//						Uint16				флаг направления передачи 	mb_servc_la->flgs.tx_rx
//											tx_rx == 1 (посылка) иначе
//											(приём)
//						"
// Возвр.знач.ф-ции.:	Тип функции			Предназначение функции		Имя функции
//						eMBErrorCode		состояние modbus посылки	MBReadCoils
// Пример вызова: 		MBReadCoils(MB_Servc *структура данных сервисных параметров modbus'а, Uint16 *указатель modbus посылки)
//----------------------------------------------------------------------------------------------------------------
eMBErrorCode MBReadCoils(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la)
{
	// объявления локальной переменной состояния modbus
	eMBErrorCode    LMBStatus = MB_ENOERR;
	// объявление локальных переменных
	Uint16 startadresscoils, startadress, qnttofcoils, bytecount = 1, cntmbreg = 0, numbcntmas = 0, cntmasreg = 0, sumshiftregcoils;

	mb_servc_la->length_tx = 0;
	// извлечение значения начального адреса
	startadresscoils =    (*(mb_servc_la->prx + 3) & 0xFF) + ((*(mb_servc_la->prx + 2) & 0xFF) << 8);
	// вычисление значения количества данных
	qnttofcoils =   (*(mb_servc_la->prx + 5) & 0xFF) + ((*(mb_servc_la->prx + 4) & 0xFF) << 8);

	// присвоения значения посылки (адрес)
	*(mb_servc_la->ptx++) =*(mb_servc_la->prx++);
	// цикл вычисления количества байт
    for (bytecount = 1; qnttofcoils > 8; bytecount++ )
    {
    	// вычесть для вычисления байт
    	qnttofcoils -= 8;
    }

    // присвоение значения посылки (адрес)
	*(mb_servc_la->ptx++) =*(mb_servc_la->prx++);

	// присвоение значения передачи количества байт
	*(mb_servc_la->ptx) = bytecount;

	// цикл вычисления смещения относительно начального адреса
    for (startadress = 0; startadresscoils >= 16; startadress++)
    {
    	// уменьшение на 8 ячеек для вычисления адреса сдвига
    	startadresscoils -= 16;
    }

    // ыход в цикл передачи данных из массива памяти
    for (cntmbreg = 1; cntmbreg <= *(mb_servc_la->ptx); cntmbreg++)
    {
    	// если счётчик массива равен 2
    	if (numbcntmas == 2)
    	{
    		// сброс счётчика массива
    		numbcntmas = 0;
    		// инкремент перехода к следующему регистру
    		cntmasreg++;
    	}

    	// если  начальный адрес больше 8 ячеек
    	if (startadresscoils > 8)
    	{
    		// вычисление суммарного смещения
    	    sumshiftregcoils = qnttofcoils + startadresscoils - 8;
    	    //  если суммарное смещение больше или равно 8
    	    if (sumshiftregcoils > 8)
    	    {
    	    	// уменьшение значение сдвига регистра на 8
    	    	sumshiftregcoils -= 8;
    	    	// увелиение количества посылок счётчика байт
    	    	bytecount++;
    	    	// присвоение значения передачи количества байт
    	    	*(mb_servc_la->ptx) = bytecount;
    	    }

    	    // если байт последний
    		if (!(bytecount - cntmbreg))
    		{
    			if (!numbcntmas)
    			{
    				// присвоение значения данных для передачи последней посылки
    				*(mb_servc_la->ptx + cntmbreg) = (((*(pMBmemory_la + startadress + cntmasreg) >> startadresscoils) & 0xFF)
    				|  ((*(pMBmemory_la + startadress + cntmasreg + 1) ) << (16 - startadresscoils))) & ( 0xFF >> (8 - sumshiftregcoils));
    			}
    			else
    			{
    				//  присвоение значения данных для передачи последней посылки
    				*(mb_servc_la->ptx + cntmbreg) = ((*(pMBmemory_la + startadress + cntmasreg) >> startadresscoils) & 0xFF) & ( 0xFF >> (8 - sumshiftregcoils));
    			}
    		}
    		else
    		{
    			// если четная посылка
    			if (!numbcntmas)
    			{
    				// присвоение значения данных для передачи посылки
    				*(mb_servc_la->ptx + cntmbreg) = (((*(pMBmemory_la + startadress + cntmasreg) >> startadresscoils) & 0xFF)
    				  | ((*(pMBmemory_la + startadress + cntmasreg + 1) ) << (16 - startadresscoils))) & 0xFF;
    			}
    			// иначе
    			else
    			{
    				// присвоение значения данных для передачи посылки
    				*(mb_servc_la->ptx + cntmbreg) = ((*(pMBmemory_la + startadress + cntmasreg) >> startadresscoils) & 0xFF);
    			}
    		}
    	}
    	// иначе
    	else
    	{
    		// вычисление суммарного смещение
       	    sumshiftregcoils = qnttofcoils + startadresscoils;
        	if (sumshiftregcoils > 8)
        	{
        		// уменьшение значение сдвига регистра на 8
        		sumshiftregcoils -= 8;
        		// увеличение количества посылок счётчика байт
        		bytecount++;
        		// присвоение значения передачи количества байт
        	    *(mb_servc_la->ptx) = bytecount;
        	}
        	// если байт последний
        	if (!(bytecount - cntmbreg))
        	{
        		//  если четная посылка
        		if (!numbcntmas)
        	    {
        			// присвоение значения данных для передачи последней посылки
        	    	*(mb_servc_la->ptx + cntmbreg) = ((*(pMBmemory_la + startadress + cntmasreg) >> startadresscoils) & 0xFF) & ( 0xFF >> (8 - sumshiftregcoils));
        	    }
        		// иначе
        	    else
        	    {
        	    	// присвоение значения данных для передачи последней посылки
        			*(mb_servc_la->ptx + cntmbreg) = (((*(pMBmemory_la + startadress + cntmasreg) >> startadresscoils) & 0xFF)
        										| ((*(pMBmemory_la + startadress + cntmasreg + 1) ) << (16 - startadresscoils))) & ( 0xFF >> (8 - sumshiftregcoils));
        	    }
        	}
        	// иначе
        	else
        	{
        		// если четная посылка
        		if (!numbcntmas)
        	    {
        			// присвоение значения данных для передачи посылки
        	    	*(mb_servc_la->ptx + cntmbreg) = ((*(pMBmemory_la + startadress + cntmasreg) >> startadresscoils) & 0xFF);
        	    }
        		// иначе
        	   	else
        	   	{
        	   		// присвоение значения данных для передачи посылки
        	   		*(mb_servc_la->ptx + cntmbreg) = (((*(pMBmemory_la + startadress + cntmasreg) >> startadresscoils) & 0xFF)
        	   									   | ((*(pMBmemory_la + startadress + cntmasreg + 1) ) << (16 - startadresscoils))) & 0xFF;
        	    }
        	}
    	}
    	numbcntmas++;
    }
    // запуск функции вычисления контрольной суммы
    usCRC16 = usMBCRC16((Uchar*) & *(mb_servc_la->ptx - 2), (*(mb_servc_la->ptx) + 3));
    // запуск посылки передачи старшей части
    *(mb_servc_la->ptx + 1 + *(mb_servc_la->ptx)) = (Uchar)(usCRC16 & 0xFF);
    // запуск посылки передачи младшей части
    *(mb_servc_la->ptx + 2 + *(mb_servc_la->ptx)) = (Uchar)(usCRC16 >> 8);
    // вычисление длины передающих данных
    mb_servc_la->length_tx = 7 + *(mb_servc_la->ptx);
    // установка флага передачи
    mb_servc_la->flgs.tx_rx = 1;
    // возврат состояния ошибки
    return LMBStatus;
}


//----------------------------------------------------------------------------------------------------------------
// Функция:  			MBReadDiscrInpts
// Описание: 			Реализация функции 2, протокола modbus "чтение ON/OFF состояний дискретных входов"
// Вход:  	  			Структура данных сервисных параметров modbus'а:
//						"
//						Тип переменной:		Предназначение переменной:	Имя переменной:
//						Uint16				массив принимаемой памяти	mb_servc_l->rx
//						Uint16				массив передаваемой памяти	mb_servc_l->tx
//						"
//						Тип переменной:		Предназначение переменной:	Имя переменной:
//						Uint16				указатель modbus посылки	pMBmemory_l
// Выход: 	  			Структура данных сервисных параметров modbus'а:
//						"
//						Тип функции:		Предназначение функции:		Имя функции:
// 						Uint16				длина передаваемой посылки	mb_servc_la->length_tx
//						Uint16				указатель на приём посылки	mb_servc_la->prx
//						Uint16				указатель на передачу 		mb_servc_la->ptx
//											посылки
//						Uint16				флаг направления передачи 	mb_servc_la->flgs.tx_rx
//											tx_rx == 1 (посылка) иначе
//											(приём)
//						"
// Возвр.знач.ф-ции.:	Тип функции			Предназначение функции		Имя функции
//						eMBErrorCode		состояние modbus посылки	MBReadDiscrInpts
// Пример вызова: 		MBReadDiscrInpts(MB_Servc *структура данных сервисных параметров modbus'а, Uint16 *указатель modbus посылки)
//----------------------------------------------------------------------------------------------------------------
eMBErrorCode MBReadDiscrInpts(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la)
{
	// объявления локальной переменной состояния modbus
	eMBErrorCode    LMBStatus = MB_ENOERR;
	// объявление локальных переменных
	Uint16 startadressdiskr, startadress, qnttofdiskr, bytecount = 1, cntmbreg = 0, numbcntmas = 0, cntmasreg = 0, sumshiftregdiskr;
	mb_servc.length_tx = 0;
	// извлечение значения начального адреса
	startadressdiskr =    (*(mb_servc_la->prx + 3) & 0xFF) + ((*(mb_servc_la->prx + 2) & 0xFF) << 8);
	// вычисление значения количества данных
	qnttofdiskr =   (*(mb_servc_la->prx + 5) & 0xFF) + ((*(mb_servc_la->prx + 4) & 0xFF) << 8);

	// присвоение значения посылки (адрес)
	*(mb_servc_la->ptx++) =*(mb_servc_la->prx++);
	// цикл вычисления количества байт
    for (bytecount = 1; qnttofdiskr > 8; bytecount++ )
    {
    	// вычитание для вычисления байт
    	qnttofdiskr -= 8;
    }

    // присвоение значения посылки (адрес)
	*(mb_servc_la->ptx++) =*(mb_servc_la->prx++);

	// присвоение значения передачи количества байт
	*(mb_servc_la->ptx) = bytecount;

	// цикл вычисления смещения относительно начального адреса
    for (startadress = 0; startadressdiskr >= 16; startadress++)
    {
    	// уменьшение на 8 ячеек для вычисления адреса сдвига
    	startadressdiskr -= 16;
    }

    // вход в цикл передачи данных из массива памяти
    for (cntmbreg = 1; cntmbreg <= *(mb_servc_la->ptx); cntmbreg++)
    {

    	// если счётчик массива равен 2
    	if (numbcntmas == 2)
    	{
    		// сброс счётчика массива
    		numbcntmas = 0;
    		// инкремент перехода к следующему регистру
    		cntmasreg++;
    	}

    	// если начальный адрес больше 8 дискрет
    	if (startadressdiskr > 8)
    	{
    		// вычисление суммарного смещения
    	    sumshiftregdiskr = qnttofdiskr + startadressdiskr - 8;
    	    //  если суммарное смещение больше или равно 8
    	    if (sumshiftregdiskr > 8)
    	    {
    	    	// уменьшение значения сдвига регистра на 8
    	    	sumshiftregdiskr -= 8;
    	    	// увеличения количества посылок счётчика байт
    	    	bytecount++;
    	    	// присвоение значения передачи количества байт
    	    	*(mb_servc_la->ptx) = bytecount;
    	    }

    	    // если байт последний
    		if (!(bytecount - cntmbreg))
    		{
    			if (!numbcntmas)
    			{
    				// присвоение значения данных для передачи последней посылки
    				*(mb_servc_la->ptx + cntmbreg) = (((*(pMBmemory_la + startadress + cntmasreg) >> startadressdiskr) & 0xFF)
    											   | ((*(pMBmemory_la + startadress + cntmasreg + 1) ) << (16 - startadressdiskr))) & ( 0xFF >> (8 - sumshiftregdiskr));
    			}
    			else
    			{
    				//  присвоение значения данных для передачи последней посылки
    				*(mb_servc_la->ptx + cntmbreg) = ((*(pMBmemory_la + startadress + cntmasreg) >> startadressdiskr) & 0xFF) & ( 0xFF >> (8 - sumshiftregdiskr));
    			}
    		}
    		else
    		{
    			// если четная посылка
    			if (!numbcntmas)
    			{
    				// присвоение значения данных для передачи посылки
    				*(mb_servc_la->ptx + cntmbreg) = (((*(pMBmemory_la + startadress + cntmasreg) >> startadressdiskr) & 0xFF)
    											   | ((*(pMBmemory_la + startadress + cntmasreg + 1) ) << (16 - startadressdiskr))) & 0xFF;
    			}
    			// иначе
    			else
    			{
    				// присвоение значения данных для передачи посылки
    				*(mb_servc_la->ptx + cntmbreg) = ((*(pMBmemory_la + startadress + cntmasreg) >> startadressdiskr) & 0xFF);
    			}
    		}
    	}
    	// иначе
    	else
    	{
    		// вычисление суммарного смещение
       	    sumshiftregdiskr = qnttofdiskr + startadressdiskr;

       	    // если количество бит больше 8
        	if (sumshiftregdiskr > 8)
        	{
        		// уменьшение значения сдвига регистра на 8
        		sumshiftregdiskr -= 8;
        		// увеличение количества посылок счётчика байт
        		bytecount++;
        		// присвоение значения передачи количества байт
        	    *(mb_servc_la->ptx) = bytecount;
        	}

        	// если байт последний
        	if (!(bytecount - cntmbreg))
        	{
        		//  если четная посылка
        		if (!numbcntmas)
        	    {
        			// присвоение значения данных для передачи последней посылки
        	    	*(mb_servc_la->ptx + cntmbreg) = ((*(pMBmemory_la + startadress + cntmasreg) >> startadressdiskr) & 0xFF) & ( 0xFF >> (8 - sumshiftregdiskr));
        	    }
        		// иначе
        	    else
        	    {
        	    	// присвоение значения данных для передачи последней посылки
        			*(mb_servc_la->ptx + cntmbreg) = (((*(pMBmemory_la + startadress + cntmasreg) >> startadressdiskr) & 0xFF)
        										   | ((*(pMBmemory_la + startadress + cntmasreg + 1) ) << (16 - startadressdiskr))) & ( 0xFF >> (8 - sumshiftregdiskr));
        	    }
        	}
        	// иначе
        	else
        	{
        		//   если четная посылка
        		if (!numbcntmas)
        	    {
        			// присвоение значения данных для передачи посылки
        	    	*(mb_servc_la->ptx + cntmbreg) = ((*(pMBmemory_la + startadress + cntmasreg) >> startadressdiskr) & 0xFF);
        	    }
        	   	else
        	   	{
        	   		// присвоение значения данных для передачи посылки
        	   		*(mb_servc_la->ptx + cntmbreg) = (((*(pMBmemory_la + startadress + cntmasreg) >> startadressdiskr) & 0xFF)
        	   		        	    			   | ((*(pMBmemory_la + startadress + cntmasreg + 1) ) << (16 - startadressdiskr))) & 0xFF;
        	    }
        	}
    	}

    	// переход к следующему массиву
    	numbcntmas++;
    }

    // запуск функции вычисления контрольной суммы
    usCRC16 = usMBCRC16((Uchar*) & *(mb_servc_la->ptx - 2), (*(mb_servc_la->ptx) + 3));
    // запуск посылки передачи старшей части
    *(mb_servc_la->ptx + 1 + *(mb_servc_la->ptx)) = (Uchar)(usCRC16 & 0xFF);
    // запуск посылки передачи младшей части
    *(mb_servc_la->ptx + 2 + *(mb_servc_la->ptx)) = (Uchar)(usCRC16 >> 8);
    // вычисление длины передающих данных
    mb_servc_la->length_tx = 7 + *(mb_servc_la->ptx);
    // установка флага передачи
    mb_servc_la->flgs.tx_rx = 1;
    // возврат состояния ошибки
    return LMBStatus;
}


//----------------------------------------------------------------------------------------------------------------
// Функция:  			MBReadHoldingReg
// Описание: 			Реализация функции 3, протокола modbus "чтение регистров"
// Вход:  	  			Структура данных сервисных параметров modbus'а:
//						"
//						Тип переменной:		Предназначение переменной:	Имя переменной:
//						Uint16				массив принимаемой памяти	mb_servc_l->rx
//						Uint16				массив передаваемой памяти	mb_servc_l->tx
//						"
//						Тип переменной:		Предназначение переменной:	Имя переменной:
//						Uint16				указатель modbus посылки	pMBmemory_l
// Выход: 	  			Структура данных сервисных параметров modbus'а:
//						"
//						Тип функции:		Предназначение функции:		Имя функции:
// 						Uint16				длина передаваемой посылки	mb_servc_la->length_tx
//						Uint16				указатель на приём посылки	mb_servc_la->prx
//						Uint16				указатель на передачу 		mb_servc_la->ptx
//											посылки
//						Uint16				флаг направления передачи 	mb_servc_la->flgs.tx_rx
//											tx_rx == 1 (посылка) иначе
//											(приём)
//						"
// Возвр.знач.ф-ции.:	Тип функции			Предназначение функции		Имя функции
//						eMBErrorCode		состояние modbus посылки	MBReadHoldingReg
// Пример вызова: 		MBReadHoldingReg(MB_Servc *структура данных сервисных параметров modbus'а, Uint16 *указатель modbus посылки)
//----------------------------------------------------------------------------------------------------------------
eMBErrorCode MBReadHoldingReg(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la)
{
	// объявления локальной переменной состояния modbus
	eMBErrorCode    LMBStatus = MB_ENOERR;
	// объявление переменных (начальный адресс, количество данных, счётчик номеров регистров
	Uint16 startadress , numbofpoints, cntmbreg;
	// обновить длину передачи
	mb_servc_la->length_tx = 0;
	// извлечение значения начального адреса
	startadress =  (*(mb_servc_la->prx + 3) & 0xFF) + ((*(mb_servc_la->prx + 2) & 0xFF) << 8);
	// вычисление значения количества данных
	numbofpoints = (*(mb_servc_la->prx + 5) & 0xFF) + ((*(mb_servc_la->prx + 4) & 0xFF) << 8);

	// присвоение значения посылки (адрес)
	*(mb_servc_la->ptx++) = *(mb_servc_la->prx++);
	// присвоение значения посылки (номер функции)
	*(mb_servc_la->ptx++) = *(mb_servc_la->prx);
	// присвоение значения передачи количества байт
	*(mb_servc_la->ptx++) = (numbofpoints * 2);

	// вход в цикл передачи данных из массива памяти
    for (cntmbreg = 0; cntmbreg <= numbofpoints; cntmbreg++)
    {
    	// присвоение значения данных для передачи
    	*(mb_servc_la->ptx + (cntmbreg * 2)) = (*(pMBmemory_la + startadress + cntmbreg) & 0xFF00) >> 8;
    	*(mb_servc_la->ptx + (cntmbreg * 2) + 1) = (*(pMBmemory_la + startadress + cntmbreg) & 0xFF);
    }
    // запуск функции вычисления контрольной суммы
    usCRC16 = usMBCRC16((Uchar*) & *(mb_servc_la->ptx - 3), (*(mb_servc_la->ptx - 1) + 3));
    // запуск посылки передачи старшей части
    *(mb_servc_la->ptx + *(mb_servc_la->ptx - 1)) = (Uchar)( usCRC16 & 0xFF );
    // запуск посылки передачи младшей части
    *(mb_servc_la->ptx + *(mb_servc_la->ptx - 1) + 1) = (Uchar)( usCRC16 >> 8 );
    // вычисление длины передающих данных
    mb_servc_la->length_tx = 7 + *(mb_servc_la->ptx - 1);
    // установка флага передачи
    mb_servc_la->flgs.tx_rx = 1;
    // возврат состояния ошибки
    return LMBStatus;
}


//----------------------------------------------------------------------------------------------------------------
// Функция:  			MBReadInptReg
// Описание: 			Реализация функции 4, протокола modbus "чтение входных регистров"
// Вход:  	  			Структура данных сервисных параметров modbus'а:
//						"
//						Тип переменной:		Предназначение переменной:	Имя переменной:
//						Uint16				массив принимаемой памяти	mb_servc_l->rx
//						Uint16				массив передаваемой памяти	mb_servc_l->tx
//						"
//						Тип переменной:		Предназначение переменной:	Имя переменной:
//						Uint16				указатель modbus посылки	pMBmemory_l
// Выход: 	  			Структура данных сервисных параметров modbus'а:
//						"
//						Тип функции:		Предназначение функции:		Имя функции:
// 						Uint16				длина передаваемой посылки	mb_servc_la->length_tx
//						Uint16				указатель на приём посылки	mb_servc_la->prx
//						Uint16				указатель на передачу 		mb_servc_la->ptx
//											посылки
//						Uint16				флаг направления передачи 	mb_servc_la->flgs.tx_rx
//											tx_rx == 1 (посылка) иначе
//											(приём)
//						"
// Возвр.знач.ф-ции.:	Тип функции			Предназначение функции		Имя функции
//						eMBErrorCode		состояние modbus посылки	MBReadInptReg
// Пример вызова: 		MBReadInptReg(MB_Servc *структура данных сервисных параметров modbus'а, Uint16 *указатель modbus посылки)
//----------------------------------------------------------------------------------------------------------------
eMBErrorCode MBReadInptReg(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la)
{
	// объявления локальной переменной состояния modbus
	eMBErrorCode    LMBStatus = MB_ENOERR;
	// объявление переменных (начальный адрес, количество данных, счётчик номеров регистров
	Uint16 startadress, numbofpoints, cntmbreg;
	// обновление длины передачи
	mb_servc_la->length_tx = 0;
	// извлечение значения начального адреса
	startadress =  (*(mb_servc_la->prx + 3) & 0xFF) + ((*(mb_servc_la->prx + 2) & 0xFF) << 8);
	// вычисление значения количества данных
	numbofpoints = (*(mb_servc_la->prx + 5) & 0xFF) + ((*(mb_servc_la->prx + 4) & 0xFF) << 8);

	// присвоение значения посылки (адрес)
	*(mb_servc_la->ptx++) = *(mb_servc_la->prx++);
	// присвоение значения посылки (номер функции)
	*(mb_servc_la->ptx++) = *(mb_servc_la->prx);
	// присвоение значения передачи количества байт
	*(mb_servc_la->ptx++) = (numbofpoints * 2);
	// вход в цикл передачи данных из массива память
    for (cntmbreg = 0; cntmbreg <= numbofpoints; cntmbreg++)
    {
    	// присвоение значения данных для передачи
    	*(mb_servc_la->ptx + (cntmbreg * 2))= (*(pMBmemory_la + startadress + cntmbreg) & 0xFF00) >> 8;
    	*(mb_servc_la->ptx + (cntmbreg * 2) + 1)= (*(pMBmemory_la + startadress + cntmbreg) & 0xFF);
    }
    // запуск функции вычисления контрольной суммы
    usCRC16 = usMBCRC16((Uchar*) & *(mb_servc_la->ptx - 3), (*(mb_servc_la->ptx - 1) + 3));
    // запуск посылки передачи старшей части
    *(mb_servc_la->ptx + *(mb_servc_la->ptx - 1)) = (Uchar)( usCRC16 & 0xFF );
    // запуск посылки передачи младшей части
    *(mb_servc_la->ptx + *(mb_servc_la->ptx - 1) + 1) = (Uchar)( usCRC16 >> 8 );
    // вычисление длины передающих данных
    mb_servc_la->length_tx = 7 + *(mb_servc_la->ptx - 1);
    // установка флага передачи
    mb_servc_la->flgs.tx_rx = 1;
    // возврат состояния ошибки
    return LMBStatus;
}


//----------------------------------------------------------------------------------------------------------------
// Функция:  			MBPresetSinglReg
// Описание: 			Реализация функции 5, протокола modbus "запись нового значения в регистр хранения"
// Вход:  	  			Структура данных сервисных параметров modbus'а:
//						"
//						Тип переменной:		Предназначение переменной:	Имя переменной:
//						Uint16				массив принимаемой памяти	mb_servc_l->rx
//						Uint16				массив передаваемой памяти	mb_servc_l->tx
//						"
//						Тип переменной:		Предназначение переменной:	Имя переменной:
//						Uint16				указатель modbus посылки	pMBmemory_l
// Выход: 	  			Структура данных сервисных параметров modbus'а:
//						"
//						Тип функции:		Предназначение функции:		Имя функции:
// 						Uint16				длина передаваемой посылки	mb_servc_la->length_tx
//						Uint16				указатель на приём посылки	mb_servc_la->prx
//						Uint16				указатель на передачу 		mb_servc_la->ptx
//											посылки
//						Uint16				флаг направления передачи 	mb_servc_la->flgs.tx_rx
//											tx_rx == 1 (посылка) иначе
//											(приём)
//						"
// Возвр.знач.ф-ции.:	Тип функции			Предназначение функции		Имя функции
//						eMBErrorCode		состояние modbus посылки	MBPresetSinglReg
// Пример вызова: 		MBPresetSinglReg(MB_Servc *структура данных сервисных параметров modbus'а, Uint16 *указатель modbus посылки)
//----------------------------------------------------------------------------------------------------------------
eMBErrorCode MBPresetSinglReg(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la)
{
	// объявления локальной переменной состояния modbus
	eMBErrorCode    LMBStatus = MB_ENOERR;
	// объявление переменной начального адреса
	Uint16 startadress, cntmsg;
	// вычисление начального адреса
	startadress = (*(mb_servc_la->prx + 3) & 0xFF) + ((*(mb_servc_la->prx + 2) & 0xFF) << 8);

	// вычисление данных для записи	в память
	*(pMBmemory_la + startadress) = (*(mb_servc_la->prx + 5) & 0xFF)|((*(mb_servc_la->prx + 4) & 0xFF) << 8);

	// вход в цикл передачи данных
	for (cntmsg = 0; cntmsg < 4; cntmsg++)
	{
		// значение передачи байтов
		*(mb_servc_la->ptx++) = *(mb_servc_la->prx++);
	}

	// значение передачи пятого байта (Preset Data Hi)
	*(mb_servc_la->ptx++) = (*(pMBmemory_la + startadress) & 0xFF00) >> 8;
	// значение передачи шестого байта (Preset Data Lo)
	*(mb_servc_la->ptx++) = *(pMBmemory_la + startadress)  & 0xFF;
	// вычисление контрольной суммы CRC16
	usCRC16 = usMBCRC16( (Uchar*)(mb_servc_la->ptx - 6), 6);
	// значение записи  контрольной суммы CRC16 Hi
	*(mb_servc_la->ptx++) =  (Uchar)( usCRC16 & 0xFF );
	// значение записи контрольной суммы CRC16 Lo
	*(mb_servc_la->ptx) =  (Uchar)( usCRC16 >> 8 );
	// задание вычисления длины
	mb_servc_la->length_tx = 10;
	// установка флага разрешения передачи
	mb_servc_la->flgs.tx_rx = 1;
    // возврат состояния ошибки
    return LMBStatus;
}


//----------------------------------------------------------------------------------------------------------------
// Функция:  			MBWriteSinglCoil
// Описание: 			Реализация функции 6, протокола modbus "установка единичного выхода ON/OFF"
// Вход:  	  			Структура данных сервисных параметров modbus'а:
//						"
//						Тип переменной:		Предназначение переменной:	Имя переменной:
//						Uint16				массив принимаемой памяти	mb_servc_l->rx
//						Uint16				массив передаваемой памяти	mb_servc_l->tx
//						"
//						Тип переменной:		Предназначение переменной:	Имя переменной:
//						Uint16				указатель modbus посылки	pMBmemory_l
// Выход: 	  			Структура данных сервисных параметров modbus'а:
//						"
//						Тип функции:		Предназначение функции:		Имя функции:
// 						Uint16				длина передаваемой посылки	mb_servc_la->length_tx
//						Uint16				указатель на приём посылки	mb_servc_la->prx
//						Uint16				указатель на передачу 		mb_servc_la->ptx
//											посылки
//						Uint16				флаг направления передачи 	mb_servc_la->flgs.tx_rx
//											tx_rx == 1 (посылка) иначе
//											(приём)
//						"
// Возвр.знач.ф-ции.:	Тип функции			Предназначение функции		Имя функции
//						eMBErrorCode		состояние modbus посылки	MBWriteSinglCoil
// Пример вызова: 		MBWriteSinglCoil(MB_Servc *структура данных сервисных параметров modbus'а, Uint16 *указатель modbus посылки)
//----------------------------------------------------------------------------------------------------------------
eMBErrorCode MBWriteSinglCoil(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la)
{
	// объявления локальной переменной состояния modbus
	eMBErrorCode    LMBStatus = MB_ENOERR;
	// объявление переменной начального адреса
	Uint16 startadress, startadresscoils, cntmsg;

	// вычисление начального адреса массива
	startadresscoils = (*(mb_servc_la->prx + 3) & 0xFF) + ((*(mb_servc_la->prx + 2) & 0xFF) << 8);

	// цикл вычисления смещения относительно начального адреса
	for (startadress = 0; startadresscoils > 16; startadress++)
	{
		// уменьшение на 8 ячеек для вычисления адреса сдвига
		startadresscoils -= 16;
	}

	// если приянто разрешение на установку значения бита "1"
	if (*(mb_servc_la->prx + 4) == 0xFF)
	// установление бита
	*(pMBmemory_la + startadress) |= (1 << startadresscoils);

	// если приянто разрешение на установку значения бита "0"
	if (*(mb_servc_la->prx + 4) == 0x00)
		// установление бита
	*(pMBmemory_la + startadress) &= ~(1 << startadresscoils);
	// запись посылки сообщения
	for (cntmsg = 0; cntmsg < 6; cntmsg++)
	{
		// значение передачи байтов
		*(mb_servc_la->ptx++) = *(mb_servc_la->prx++);
	}

	// вычисление контрольной суммы CRC16
	usCRC16 = usMBCRC16( (Uchar*) & *(mb_servc_la->ptx - 6), 6);
	// значение записи  контрольной суммы CRC16 Hi
	*(mb_servc_la->ptx++) =  (Uchar)(usCRC16 & 0xFF);
	// значение записи контрольной суммы CRC16 Lo
	*(mb_servc_la->ptx) =  (Uchar)(usCRC16 >> 8);
	// задание вычисления длины
	mb_servc_la->length_tx = 10;
	// установление флага разрешения передачи
	mb_servc_la->flgs.tx_rx = 1;
    // возврат состояния ошибки
    return LMBStatus;
}


//----------------------------------------------------------------------------------------------------------------
// Функция:  			MBForceMultCoils
// Описание: 			Реализация функции 15, протокола modbus "запись нескольких битов"
// Вход:  	  			Структура данных сервисных параметров modbus'а:
//						"
//						Тип переменной:		Предназначение переменной:	Имя переменной:
//						Uint16				массив принимаемой памяти	mb_servc_l->rx
//						Uint16				массив передаваемой памяти	mb_servc_l->tx
//						"
//						Тип переменной:		Предназначение переменной:	Имя переменной:
//						Uint16				указатель modbus посылки	pMBmemory_l
// Выход: 	  			Структура данных сервисных параметров modbus'а:
//						"
//						Тип функции:		Предназначение функции:		Имя функции:
// 						Uint16				длина передаваемой посылки	mb_servc_la->length_tx
//						Uint16				указатель на приём посылки	mb_servc_la->prx
//						Uint16				указатель на передачу 		mb_servc_la->ptx
//											посылки
//						Uint16				флаг направления передачи 	mb_servc_la->flgs.tx_rx
//											tx_rx == 1 (посылка) иначе
//											(приём)
//						"
// Возвр.знач.ф-ции.:	Тип функции			Предназначение функции		Имя функции
//						eMBErrorCode		состояние modbus посылки	MBForceMultCoils
// Пример вызова: 		MBForceMultCoils(MB_Servc *структура данных сервисных параметров modbus'а, Uint16 *указатель modbus посылки)
//----------------------------------------------------------------------------------------------------------------
eMBErrorCode MBForceMultCoils(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la)
{

	// объявления локальной переменной состояния modbus
	eMBErrorCode    LMBStatus = MB_ENOERR;

	// в текущий момент функция является нерабочей и происходит его наладка

    return LMBStatus;
}


//----------------------------------------------------------------------------------------------------------------
// Функция:  			MBPresetMultRegs
// Описание: 			Реализация функции 16, протокола modbus "запись нескольких регистров"
// Вход:  	  			Структура данных сервисных параметров modbus'а:
//						"
//						Тип переменной:		Предназначение переменной:	Имя переменной:
//						Uint16				массив принимаемой памяти	mb_servc_l->rx
//						Uint16				массив передаваемой памяти	mb_servc_l->tx
//						"
//						Тип переменной:		Предназначение переменной:	Имя переменной:
//						Uint16				указатель modbus посылки	pMBmemory_l
// Выход: 	  			Структура данных сервисных параметров modbus'а:
//						"
//						Тип функции:		Предназначение функции:		Имя функции:
// 						Uint16				длина передаваемой посылки	mb_servc_la->length_tx
//						Uint16				указатель на приём посылки	mb_servc_la->prx
//						Uint16				указатель на передачу 		mb_servc_la->ptx
//											посылки
//						Uint16				флаг направления передачи 	mb_servc_la->flgs.tx_rx
//											tx_rx == 1 (посылка) иначе
//											(приём)
//						"
// Возвр.знач.ф-ции.:	Тип функции			Предназначение функции		Имя функции
//						eMBErrorCode		состояние modbus посылки	MBPresetMultRegs
// Пример вызова: 		MBPresetMultRegs(MB_Servc *структура данных сервисных параметров modbus'а, Uint16 *указатель modbus посылки)
//----------------------------------------------------------------------------------------------------------------
eMBErrorCode MBPresetMultRegs(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la)
{
	// объявления локальной переменной состояния modbus
	eMBErrorCode    LMBStatus = MB_ENOERR;
	// объявление локальных переменных
	Uint16 startadress, bytecount, cntmbreg, cntmsg;

	// вычисление начального адреса
	startadress = (*(mb_servc_la->prx + 3) & 0xFF) + ((*(mb_servc_la->prx + 2) & 0xFF) << 8);
	// вычисление количества байт
	bytecount = (*(mb_servc_la->prx + 6) & 0xFF) >> 1;

	// вход в цикл записи регистров
	for (cntmbreg = 0; cntmbreg < bytecount; cntmbreg++)
	{
		// запись регистра modbus
		*(pMBmemory_la + startadress + cntmbreg) = (*(mb_servc_la->prx + 8 + (cntmbreg * 2)) & 0xFF)|((*(mb_servc_la->prx + 7 + (cntmbreg * 2)) & 0xFF)<<8);
	}
	// запись передащих данных
	for (cntmsg = 0; cntmsg < 6; cntmsg++)
	{
		// значение передачи байтов
		*(mb_servc_la->ptx++) = *(mb_servc_la->prx++);
	}

	// вычисление контрольной суммы CRC16
	usCRC16 = usMBCRC16((Uchar*) & *(mb_servc_la->ptx - 6), 6);
	// значение записи  контрольной суммы CRC16 Hi
	*(mb_servc_la->ptx++) =  (Uchar)(usCRC16 & 0xFF);
	// значение записи контрольной суммы CRC16 Lo
	*(mb_servc_la->ptx) =  (Uchar)(usCRC16 >> 8);
	// задание вычисления длины
	mb_servc_la->length_tx = 10;
	// установление флага разрешения передачи
	mb_servc_la->flgs.tx_rx = 1;
    // возврат состояния ошибки
    return LMBStatus;
}
