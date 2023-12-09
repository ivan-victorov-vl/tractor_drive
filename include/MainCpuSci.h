//###########################################################################
//
// Файл:    	MainCpuSci.h
//
// Описание:   	Заголовочный файл: MainCpuSci.c
//
//###########################################################################

#ifndef MAINCPUSCI_H
#define MAINCPUSCI_H


////////////////////// ПОДКЛЮЧЕНИЕ ЗАГОЛОВОЧНЫХ ФАЙЛОВ //////////////////////
// подключение заголовочного файла "MainModbus.h"
#include "MainModbus.h"


//////////////// ОБЪЯВЛЕНИЕ ВНЕШНЕГО ДОСТУПА К ФУНКЦИЯМ /////////////////////
// объявление внешнего доступа к функции InitSCIA
extern void InitSCIA(void);
// объявление внешнего доступа к функции InitSCIB
extern void InitSCIB(void);
// объявление внешнего доступа к CheckErrSciRxTx
extern void CheckErrSciABRxTx(void);
// объявление функции CMBSciABRxTx
extern void MBSciABRxTx(MB_Servc *mb_servc_l);
// объявление функции MBSciABCyclRxTx
extern void MBSciABCyclRxTx(MB_Servc *mb_servc_l, Uint16 *pMBmemory_l);


#endif
