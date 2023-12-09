//###########################################################################
//
// ����:    	MainCpuSci.h
//
// ��������:   	������������ ����: MainCpuSci.c
//
//###########################################################################

#ifndef MAINCPUSCI_H
#define MAINCPUSCI_H


////////////////////// ����������� ������������ ������ //////////////////////
// ����������� ������������� ����� "MainModbus.h"
#include "MainModbus.h"


//////////////// ���������� �������� ������� � �������� /////////////////////
// ���������� �������� ������� � ������� InitSCIA
extern void InitSCIA(void);
// ���������� �������� ������� � ������� InitSCIB
extern void InitSCIB(void);
// ���������� �������� ������� � CheckErrSciRxTx
extern void CheckErrSciABRxTx(void);
// ���������� ������� CMBSciABRxTx
extern void MBSciABRxTx(MB_Servc *mb_servc_l);
// ���������� ������� MBSciABCyclRxTx
extern void MBSciABCyclRxTx(MB_Servc *mb_servc_l, Uint16 *pMBmemory_l);


#endif
