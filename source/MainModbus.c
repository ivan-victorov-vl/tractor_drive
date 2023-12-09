//###########################################################################
//
// FILE:	MainModbus.c
//
// TITLE:	������� modbus ����������
//
//###########################################################################


////////////////////// ����������� ������������ ������ //////////////////////
// ����������� ������������� ����� "PeripheralHeaderIncludes.h"
#include "PeripheralHeaderIncludes.h"
// ����������� ������������� ����� "MainModbus.h"
#include "MainModbus.h"


/////////////////////////// ���������� ��������� //////////////////////////////
// 16 ������ ����������� �����
Uint16 	usCRC16;


/////////////////////////// ���������� ������ //////////////////////////////
// ������� ����������� ����� 16 ������� ����� �������� ������� (���������� ����������� ����)
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


// ������� ����������� ����� 16 ������� ����� �������� ������� (���������� ����������� ����)
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


/////////////////////////// ���������� ������� //////////////////////////////
// ������� ���������� ����������� ����� 16 ������� ��������
Ushort usMBCRC16	(Uchar * pucFrame, Ushort usLen);
// ����� ������� � ����������� ����������� ��������
void MBReadFuncSlave (MB_Servc *mb_servc_l, Uint16 *pMBmemory_l);
// ���������� ������� MBReadHoldingReg
eMBErrorCode MBReadHoldingReg(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la);
// ���������� ������� MBReadInptReg
eMBErrorCode MBReadInptReg(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la);
// ���������� ������� MBPresetMultReg
eMBErrorCode MBPresetMultRegs(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la);
// ���������� ������� MBForceMultCoils
eMBErrorCode MBForceMultCoils(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la);
// ���������� ������� MBPresetSinglReg
eMBErrorCode MBPresetSinglReg(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la);
// ���������� ������� MBWriteSinglCoil
eMBErrorCode MBWriteSinglCoil(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la);
// ���������� ������� MBReadCoils
eMBErrorCode MBReadCoils(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la);
// ���������� ������� MBReadDiscrInpts
eMBErrorCode MBReadDiscrInpts(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la);



//----------------------------------------------------------------------------------------------------------------
// �������:  			usMBCRC16
// ��������: 			���������� ����������� ����� ��������� modbus (���������� ����������� ����)
// ����:  	  			��� �����������:	�������������� ����������:	��� ����������:
//						Uchar				������� ������				*pucFrame
//						Ushort				����� ������				usLen
// �����: 	  			( - )
// �����.����.�-���.:	��� �������			�������������� �������		��� �������
//						Ushort				�������� ����������� �����	usMBCRC16
// ������ ������: 		usMBCRC16(Uchar *������� ������, Ushort ����� ������)
//----------------------------------------------------------------------------------------------------------------
Ushort usMBCRC16(Uchar* pucFrame, Ushort usLen)
{
	// ��������� �������� ����������� ����� �������� ������� (���������� ����������� ����)
    Uchar ucCRCHi = 0xFF;
    // ��������� �������� ����������� ����� �������� ������� (���������� ����������� ����)
    Uchar ucCRCLo = 0xFF;
    int iIndex;

    // ��������� �� ����� ����� �������
    while ( usLen-- )
    {
    	// ���������� ������� ����������� �����
        iIndex = ucCRCLo ^ *( pucFrame++ );
        // ���������� �������� ������� ����������� �����
        ucCRCLo = ucCRCHi ^ aucCRCHi[ iIndex ];
        // ���������� �������� ������� ����������� �����
        ucCRCHi = aucCRCLo[ iIndex ];
    }
    return ucCRCHi << 8 | ucCRCLo;
}


//----------------------------------------------------------------------------------------------------------------
// �������:  			MBReadFuncSlave
// ��������: 			����� ������� � ����������� ����������� ��������
// ����:  	 	 		��������� ������ ��������� ���������� modbus'�:
//						"
//						��� ����������:		�������������� ����������:	��� ����������:
//						Uint16				������ ����������� ������	mb_servc_l->rx
//						Uint16				������ ������������ ������	mb_servc_l->tx
//						"
//						��� ����������:		�������������� ����������:	��� ����������:
//						Uint16				��������� modbus �������	pMBmemory_l
// �����: 	  			��������� ������ ��������� ���������� modbus'�:
//						"
//						��� ����������:		�������������� ����������:	��� ����������:
//						Uint16				��������� �� ���� �������	mb_servc_l->prx
//						Uint16				��������� �� �������� 		mb_servc_l->ptx
//											�������
//						eMBErrorCode		��������� �������			mb_servc_l->mb_status
//						"
// �����.����.�-���.:	( - )
// ������ ������: 		MBReadFuncSlave(MB_Servc *��������� ������ ��������� ���������� modbus'�, Uint16 *��������� modbus �������)
//----------------------------------------------------------------------------------------------------------------
void MBReadFuncSlave(MB_Servc *mb_servc_l, Uint16 *pMBmemory_l)
{
	// ���������� ��������� ����� modbus
	mb_servc_l->mb_status = MB_ENOERR;

	// ������������ ��������� �� 0-�� ����� ������� �����
	mb_servc_l->prx = &mb_servc_l->rx[0];
	// ������������ ��������� �� 0-�� ����� ������� ��������
	mb_servc_l->ptx = &mb_servc_l->tx[0];

	// ����� ����������� �������
	switch (mb_servc_l->rx[1])
	{
		// ���� ������� �������: modbus read coil status
		case MBREADCOILSTATUSF:
		// ���� ������� ������� (1), �� ���������� ������ ���������� �����
		mb_servc_l->mb_status = MBReadCoils(&(*mb_servc_l), pMBmemory_l);
		// ����� �� ������������� switch
		break;

		// ���� ������� �������: modbus read input status
		case MBREADINPUTSTATUSF:
		// ���� ������� ������� (2), �� ���������� ������� ������ ���������� ������
		mb_servc_l->mb_status = MBReadDiscrInpts(&(*mb_servc_l), pMBmemory_l);
		// ����� �� ������������� switch
		break;

		// ���� ������� �������: modbus read holding register
		case MBREADHOLDINGREGSF:
		// ���� ������� ������� (3), �� ���������� ������ ���������
		mb_servc_l->mb_status = MBReadHoldingReg(&(*mb_servc_l), pMBmemory_l);
		// ����� �� ������������� switch
		break;

		// ���� ������� �������: modbus read input register
		case MBREADINPUTREGSF:
		// ���� ������� ������� (4), �� ���������� ������ ���������
		mb_servc_l->mb_status = MBReadInptReg(&(*mb_servc_l), pMBmemory_l);
		// ����� �� ������������� switch
		break;

		// ���� ������� �������: modbus force single coil
		case MBFORCESINGLECOILF:
		// ���� ������� ������� (5), �� ��������� ���������� ������ ON/OFF
		mb_servc_l->mb_status = MBWriteSinglCoil(&(*mb_servc_l), pMBmemory_l);
		// ����� �� ������������� switch
		break;

		// ���� ������� �������: modbus preset single register
		case MBPRESETSINGLEREGF:
		// ���� ������� ������� (6), �� ���������� ������ ������ ��������
		mb_servc_l->mb_status = MBPresetSinglReg(&(*mb_servc_l), pMBmemory_l);
		// ����� �� ������������� switch
		break;

		// ���� ������� �������: modbus force multiple coils
		case MBFORCEMULTCOILSF:
		// ���� ������� ������� (15), �� ���������� ������ ���������� ���������
		mb_servc_l->mb_status = MBForceMultCoils(&(*mb_servc_l), pMBmemory_l);
		// ����� �� ������������� switch
		break;

		// ���� ������� �������: modbus preset multiple register
		case MBPRESETMULTREGSF:
		// ���� ������� ������� (16), �� ���������� ������ ���������� ���������
		mb_servc_l->mb_status = MBPresetMultRegs(&(*mb_servc_l), pMBmemory_l);
		// ����� �� ������������� switch
		break;

		// ���� ������� ������� �� ������������ �������
		default:
		// ������������� ��������� modbus ��� ������ �� ������������� ��������� �������
		mb_servc_l->mb_status = MB_FUNCERR;
		// ����� �� ������������� switch
		break;
	}
}


//----------------------------------------------------------------------------------------------------------------
// �������:  			MBReadCoils
// ��������: 			���������� ������� 1, ��������� modbus "������ ���������� �����"
// ����:  	  			��������� ������ ��������� ���������� modbus'�:
//						"
//						��� ����������:		�������������� ����������:	��� ����������:
//						Uint16				������ ����������� ������	mb_servc_l->rx
//						Uint16				������ ������������ ������	mb_servc_l->tx
//						"
//						��� ����������:		�������������� ����������:	��� ����������:
//						Uint16				��������� modbus �������	pMBmemory_l
// �����: 	  			��������� ������ ��������� ���������� modbus'�:
//						"
//						��� �������:		�������������� �������:		��� �������:
// 						Uint16				����� ������������ �������	mb_servc_la->length_tx
//						Uint16				��������� �� ���� �������	mb_servc_la->prx
//						Uint16				��������� �� �������� 		mb_servc_la->ptx
//											�������
//						Uint16				���� ����������� �������� 	mb_servc_la->flgs.tx_rx
//											tx_rx == 1 (�������) �����
//											(����)
//						"
// �����.����.�-���.:	��� �������			�������������� �������		��� �������
//						eMBErrorCode		��������� modbus �������	MBReadCoils
// ������ ������: 		MBReadCoils(MB_Servc *��������� ������ ��������� ���������� modbus'�, Uint16 *��������� modbus �������)
//----------------------------------------------------------------------------------------------------------------
eMBErrorCode MBReadCoils(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la)
{
	// ���������� ��������� ���������� ��������� modbus
	eMBErrorCode    LMBStatus = MB_ENOERR;
	// ���������� ��������� ����������
	Uint16 startadresscoils, startadress, qnttofcoils, bytecount = 1, cntmbreg = 0, numbcntmas = 0, cntmasreg = 0, sumshiftregcoils;

	mb_servc_la->length_tx = 0;
	// ���������� �������� ���������� ������
	startadresscoils =    (*(mb_servc_la->prx + 3) & 0xFF) + ((*(mb_servc_la->prx + 2) & 0xFF) << 8);
	// ���������� �������� ���������� ������
	qnttofcoils =   (*(mb_servc_la->prx + 5) & 0xFF) + ((*(mb_servc_la->prx + 4) & 0xFF) << 8);

	// ���������� �������� ������� (�����)
	*(mb_servc_la->ptx++) =*(mb_servc_la->prx++);
	// ���� ���������� ���������� ����
    for (bytecount = 1; qnttofcoils > 8; bytecount++ )
    {
    	// ������� ��� ���������� ����
    	qnttofcoils -= 8;
    }

    // ���������� �������� ������� (�����)
	*(mb_servc_la->ptx++) =*(mb_servc_la->prx++);

	// ���������� �������� �������� ���������� ����
	*(mb_servc_la->ptx) = bytecount;

	// ���� ���������� �������� ������������ ���������� ������
    for (startadress = 0; startadresscoils >= 16; startadress++)
    {
    	// ���������� �� 8 ����� ��� ���������� ������ ������
    	startadresscoils -= 16;
    }

    // ���� � ���� �������� ������ �� ������� ������
    for (cntmbreg = 1; cntmbreg <= *(mb_servc_la->ptx); cntmbreg++)
    {
    	// ���� ������� ������� ����� 2
    	if (numbcntmas == 2)
    	{
    		// ����� �������� �������
    		numbcntmas = 0;
    		// ��������� �������� � ���������� ��������
    		cntmasreg++;
    	}

    	// ����  ��������� ����� ������ 8 �����
    	if (startadresscoils > 8)
    	{
    		// ���������� ���������� ��������
    	    sumshiftregcoils = qnttofcoils + startadresscoils - 8;
    	    //  ���� ��������� �������� ������ ��� ����� 8
    	    if (sumshiftregcoils > 8)
    	    {
    	    	// ���������� �������� ������ �������� �� 8
    	    	sumshiftregcoils -= 8;
    	    	// ��������� ���������� ������� �������� ����
    	    	bytecount++;
    	    	// ���������� �������� �������� ���������� ����
    	    	*(mb_servc_la->ptx) = bytecount;
    	    }

    	    // ���� ���� ���������
    		if (!(bytecount - cntmbreg))
    		{
    			if (!numbcntmas)
    			{
    				// ���������� �������� ������ ��� �������� ��������� �������
    				*(mb_servc_la->ptx + cntmbreg) = (((*(pMBmemory_la + startadress + cntmasreg) >> startadresscoils) & 0xFF)
    				|  ((*(pMBmemory_la + startadress + cntmasreg + 1) ) << (16 - startadresscoils))) & ( 0xFF >> (8 - sumshiftregcoils));
    			}
    			else
    			{
    				//  ���������� �������� ������ ��� �������� ��������� �������
    				*(mb_servc_la->ptx + cntmbreg) = ((*(pMBmemory_la + startadress + cntmasreg) >> startadresscoils) & 0xFF) & ( 0xFF >> (8 - sumshiftregcoils));
    			}
    		}
    		else
    		{
    			// ���� ������ �������
    			if (!numbcntmas)
    			{
    				// ���������� �������� ������ ��� �������� �������
    				*(mb_servc_la->ptx + cntmbreg) = (((*(pMBmemory_la + startadress + cntmasreg) >> startadresscoils) & 0xFF)
    				  | ((*(pMBmemory_la + startadress + cntmasreg + 1) ) << (16 - startadresscoils))) & 0xFF;
    			}
    			// �����
    			else
    			{
    				// ���������� �������� ������ ��� �������� �������
    				*(mb_servc_la->ptx + cntmbreg) = ((*(pMBmemory_la + startadress + cntmasreg) >> startadresscoils) & 0xFF);
    			}
    		}
    	}
    	// �����
    	else
    	{
    		// ���������� ���������� ��������
       	    sumshiftregcoils = qnttofcoils + startadresscoils;
        	if (sumshiftregcoils > 8)
        	{
        		// ���������� �������� ������ �������� �� 8
        		sumshiftregcoils -= 8;
        		// ���������� ���������� ������� �������� ����
        		bytecount++;
        		// ���������� �������� �������� ���������� ����
        	    *(mb_servc_la->ptx) = bytecount;
        	}
        	// ���� ���� ���������
        	if (!(bytecount - cntmbreg))
        	{
        		//  ���� ������ �������
        		if (!numbcntmas)
        	    {
        			// ���������� �������� ������ ��� �������� ��������� �������
        	    	*(mb_servc_la->ptx + cntmbreg) = ((*(pMBmemory_la + startadress + cntmasreg) >> startadresscoils) & 0xFF) & ( 0xFF >> (8 - sumshiftregcoils));
        	    }
        		// �����
        	    else
        	    {
        	    	// ���������� �������� ������ ��� �������� ��������� �������
        			*(mb_servc_la->ptx + cntmbreg) = (((*(pMBmemory_la + startadress + cntmasreg) >> startadresscoils) & 0xFF)
        										| ((*(pMBmemory_la + startadress + cntmasreg + 1) ) << (16 - startadresscoils))) & ( 0xFF >> (8 - sumshiftregcoils));
        	    }
        	}
        	// �����
        	else
        	{
        		// ���� ������ �������
        		if (!numbcntmas)
        	    {
        			// ���������� �������� ������ ��� �������� �������
        	    	*(mb_servc_la->ptx + cntmbreg) = ((*(pMBmemory_la + startadress + cntmasreg) >> startadresscoils) & 0xFF);
        	    }
        		// �����
        	   	else
        	   	{
        	   		// ���������� �������� ������ ��� �������� �������
        	   		*(mb_servc_la->ptx + cntmbreg) = (((*(pMBmemory_la + startadress + cntmasreg) >> startadresscoils) & 0xFF)
        	   									   | ((*(pMBmemory_la + startadress + cntmasreg + 1) ) << (16 - startadresscoils))) & 0xFF;
        	    }
        	}
    	}
    	numbcntmas++;
    }
    // ������ ������� ���������� ����������� �����
    usCRC16 = usMBCRC16((Uchar*) & *(mb_servc_la->ptx - 2), (*(mb_servc_la->ptx) + 3));
    // ������ ������� �������� ������� �����
    *(mb_servc_la->ptx + 1 + *(mb_servc_la->ptx)) = (Uchar)(usCRC16 & 0xFF);
    // ������ ������� �������� ������� �����
    *(mb_servc_la->ptx + 2 + *(mb_servc_la->ptx)) = (Uchar)(usCRC16 >> 8);
    // ���������� ����� ���������� ������
    mb_servc_la->length_tx = 7 + *(mb_servc_la->ptx);
    // ��������� ����� ��������
    mb_servc_la->flgs.tx_rx = 1;
    // ������� ��������� ������
    return LMBStatus;
}


//----------------------------------------------------------------------------------------------------------------
// �������:  			MBReadDiscrInpts
// ��������: 			���������� ������� 2, ��������� modbus "������ ON/OFF ��������� ���������� ������"
// ����:  	  			��������� ������ ��������� ���������� modbus'�:
//						"
//						��� ����������:		�������������� ����������:	��� ����������:
//						Uint16				������ ����������� ������	mb_servc_l->rx
//						Uint16				������ ������������ ������	mb_servc_l->tx
//						"
//						��� ����������:		�������������� ����������:	��� ����������:
//						Uint16				��������� modbus �������	pMBmemory_l
// �����: 	  			��������� ������ ��������� ���������� modbus'�:
//						"
//						��� �������:		�������������� �������:		��� �������:
// 						Uint16				����� ������������ �������	mb_servc_la->length_tx
//						Uint16				��������� �� ���� �������	mb_servc_la->prx
//						Uint16				��������� �� �������� 		mb_servc_la->ptx
//											�������
//						Uint16				���� ����������� �������� 	mb_servc_la->flgs.tx_rx
//											tx_rx == 1 (�������) �����
//											(����)
//						"
// �����.����.�-���.:	��� �������			�������������� �������		��� �������
//						eMBErrorCode		��������� modbus �������	MBReadDiscrInpts
// ������ ������: 		MBReadDiscrInpts(MB_Servc *��������� ������ ��������� ���������� modbus'�, Uint16 *��������� modbus �������)
//----------------------------------------------------------------------------------------------------------------
eMBErrorCode MBReadDiscrInpts(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la)
{
	// ���������� ��������� ���������� ��������� modbus
	eMBErrorCode    LMBStatus = MB_ENOERR;
	// ���������� ��������� ����������
	Uint16 startadressdiskr, startadress, qnttofdiskr, bytecount = 1, cntmbreg = 0, numbcntmas = 0, cntmasreg = 0, sumshiftregdiskr;
	mb_servc.length_tx = 0;
	// ���������� �������� ���������� ������
	startadressdiskr =    (*(mb_servc_la->prx + 3) & 0xFF) + ((*(mb_servc_la->prx + 2) & 0xFF) << 8);
	// ���������� �������� ���������� ������
	qnttofdiskr =   (*(mb_servc_la->prx + 5) & 0xFF) + ((*(mb_servc_la->prx + 4) & 0xFF) << 8);

	// ���������� �������� ������� (�����)
	*(mb_servc_la->ptx++) =*(mb_servc_la->prx++);
	// ���� ���������� ���������� ����
    for (bytecount = 1; qnttofdiskr > 8; bytecount++ )
    {
    	// ��������� ��� ���������� ����
    	qnttofdiskr -= 8;
    }

    // ���������� �������� ������� (�����)
	*(mb_servc_la->ptx++) =*(mb_servc_la->prx++);

	// ���������� �������� �������� ���������� ����
	*(mb_servc_la->ptx) = bytecount;

	// ���� ���������� �������� ������������ ���������� ������
    for (startadress = 0; startadressdiskr >= 16; startadress++)
    {
    	// ���������� �� 8 ����� ��� ���������� ������ ������
    	startadressdiskr -= 16;
    }

    // ���� � ���� �������� ������ �� ������� ������
    for (cntmbreg = 1; cntmbreg <= *(mb_servc_la->ptx); cntmbreg++)
    {

    	// ���� ������� ������� ����� 2
    	if (numbcntmas == 2)
    	{
    		// ����� �������� �������
    		numbcntmas = 0;
    		// ��������� �������� � ���������� ��������
    		cntmasreg++;
    	}

    	// ���� ��������� ����� ������ 8 �������
    	if (startadressdiskr > 8)
    	{
    		// ���������� ���������� ��������
    	    sumshiftregdiskr = qnttofdiskr + startadressdiskr - 8;
    	    //  ���� ��������� �������� ������ ��� ����� 8
    	    if (sumshiftregdiskr > 8)
    	    {
    	    	// ���������� �������� ������ �������� �� 8
    	    	sumshiftregdiskr -= 8;
    	    	// ���������� ���������� ������� �������� ����
    	    	bytecount++;
    	    	// ���������� �������� �������� ���������� ����
    	    	*(mb_servc_la->ptx) = bytecount;
    	    }

    	    // ���� ���� ���������
    		if (!(bytecount - cntmbreg))
    		{
    			if (!numbcntmas)
    			{
    				// ���������� �������� ������ ��� �������� ��������� �������
    				*(mb_servc_la->ptx + cntmbreg) = (((*(pMBmemory_la + startadress + cntmasreg) >> startadressdiskr) & 0xFF)
    											   | ((*(pMBmemory_la + startadress + cntmasreg + 1) ) << (16 - startadressdiskr))) & ( 0xFF >> (8 - sumshiftregdiskr));
    			}
    			else
    			{
    				//  ���������� �������� ������ ��� �������� ��������� �������
    				*(mb_servc_la->ptx + cntmbreg) = ((*(pMBmemory_la + startadress + cntmasreg) >> startadressdiskr) & 0xFF) & ( 0xFF >> (8 - sumshiftregdiskr));
    			}
    		}
    		else
    		{
    			// ���� ������ �������
    			if (!numbcntmas)
    			{
    				// ���������� �������� ������ ��� �������� �������
    				*(mb_servc_la->ptx + cntmbreg) = (((*(pMBmemory_la + startadress + cntmasreg) >> startadressdiskr) & 0xFF)
    											   | ((*(pMBmemory_la + startadress + cntmasreg + 1) ) << (16 - startadressdiskr))) & 0xFF;
    			}
    			// �����
    			else
    			{
    				// ���������� �������� ������ ��� �������� �������
    				*(mb_servc_la->ptx + cntmbreg) = ((*(pMBmemory_la + startadress + cntmasreg) >> startadressdiskr) & 0xFF);
    			}
    		}
    	}
    	// �����
    	else
    	{
    		// ���������� ���������� ��������
       	    sumshiftregdiskr = qnttofdiskr + startadressdiskr;

       	    // ���� ���������� ��� ������ 8
        	if (sumshiftregdiskr > 8)
        	{
        		// ���������� �������� ������ �������� �� 8
        		sumshiftregdiskr -= 8;
        		// ���������� ���������� ������� �������� ����
        		bytecount++;
        		// ���������� �������� �������� ���������� ����
        	    *(mb_servc_la->ptx) = bytecount;
        	}

        	// ���� ���� ���������
        	if (!(bytecount - cntmbreg))
        	{
        		//  ���� ������ �������
        		if (!numbcntmas)
        	    {
        			// ���������� �������� ������ ��� �������� ��������� �������
        	    	*(mb_servc_la->ptx + cntmbreg) = ((*(pMBmemory_la + startadress + cntmasreg) >> startadressdiskr) & 0xFF) & ( 0xFF >> (8 - sumshiftregdiskr));
        	    }
        		// �����
        	    else
        	    {
        	    	// ���������� �������� ������ ��� �������� ��������� �������
        			*(mb_servc_la->ptx + cntmbreg) = (((*(pMBmemory_la + startadress + cntmasreg) >> startadressdiskr) & 0xFF)
        										   | ((*(pMBmemory_la + startadress + cntmasreg + 1) ) << (16 - startadressdiskr))) & ( 0xFF >> (8 - sumshiftregdiskr));
        	    }
        	}
        	// �����
        	else
        	{
        		//   ���� ������ �������
        		if (!numbcntmas)
        	    {
        			// ���������� �������� ������ ��� �������� �������
        	    	*(mb_servc_la->ptx + cntmbreg) = ((*(pMBmemory_la + startadress + cntmasreg) >> startadressdiskr) & 0xFF);
        	    }
        	   	else
        	   	{
        	   		// ���������� �������� ������ ��� �������� �������
        	   		*(mb_servc_la->ptx + cntmbreg) = (((*(pMBmemory_la + startadress + cntmasreg) >> startadressdiskr) & 0xFF)
        	   		        	    			   | ((*(pMBmemory_la + startadress + cntmasreg + 1) ) << (16 - startadressdiskr))) & 0xFF;
        	    }
        	}
    	}

    	// ������� � ���������� �������
    	numbcntmas++;
    }

    // ������ ������� ���������� ����������� �����
    usCRC16 = usMBCRC16((Uchar*) & *(mb_servc_la->ptx - 2), (*(mb_servc_la->ptx) + 3));
    // ������ ������� �������� ������� �����
    *(mb_servc_la->ptx + 1 + *(mb_servc_la->ptx)) = (Uchar)(usCRC16 & 0xFF);
    // ������ ������� �������� ������� �����
    *(mb_servc_la->ptx + 2 + *(mb_servc_la->ptx)) = (Uchar)(usCRC16 >> 8);
    // ���������� ����� ���������� ������
    mb_servc_la->length_tx = 7 + *(mb_servc_la->ptx);
    // ��������� ����� ��������
    mb_servc_la->flgs.tx_rx = 1;
    // ������� ��������� ������
    return LMBStatus;
}


//----------------------------------------------------------------------------------------------------------------
// �������:  			MBReadHoldingReg
// ��������: 			���������� ������� 3, ��������� modbus "������ ���������"
// ����:  	  			��������� ������ ��������� ���������� modbus'�:
//						"
//						��� ����������:		�������������� ����������:	��� ����������:
//						Uint16				������ ����������� ������	mb_servc_l->rx
//						Uint16				������ ������������ ������	mb_servc_l->tx
//						"
//						��� ����������:		�������������� ����������:	��� ����������:
//						Uint16				��������� modbus �������	pMBmemory_l
// �����: 	  			��������� ������ ��������� ���������� modbus'�:
//						"
//						��� �������:		�������������� �������:		��� �������:
// 						Uint16				����� ������������ �������	mb_servc_la->length_tx
//						Uint16				��������� �� ���� �������	mb_servc_la->prx
//						Uint16				��������� �� �������� 		mb_servc_la->ptx
//											�������
//						Uint16				���� ����������� �������� 	mb_servc_la->flgs.tx_rx
//											tx_rx == 1 (�������) �����
//											(����)
//						"
// �����.����.�-���.:	��� �������			�������������� �������		��� �������
//						eMBErrorCode		��������� modbus �������	MBReadHoldingReg
// ������ ������: 		MBReadHoldingReg(MB_Servc *��������� ������ ��������� ���������� modbus'�, Uint16 *��������� modbus �������)
//----------------------------------------------------------------------------------------------------------------
eMBErrorCode MBReadHoldingReg(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la)
{
	// ���������� ��������� ���������� ��������� modbus
	eMBErrorCode    LMBStatus = MB_ENOERR;
	// ���������� ���������� (��������� ������, ���������� ������, ������� ������� ���������
	Uint16 startadress , numbofpoints, cntmbreg;
	// �������� ����� ��������
	mb_servc_la->length_tx = 0;
	// ���������� �������� ���������� ������
	startadress =  (*(mb_servc_la->prx + 3) & 0xFF) + ((*(mb_servc_la->prx + 2) & 0xFF) << 8);
	// ���������� �������� ���������� ������
	numbofpoints = (*(mb_servc_la->prx + 5) & 0xFF) + ((*(mb_servc_la->prx + 4) & 0xFF) << 8);

	// ���������� �������� ������� (�����)
	*(mb_servc_la->ptx++) = *(mb_servc_la->prx++);
	// ���������� �������� ������� (����� �������)
	*(mb_servc_la->ptx++) = *(mb_servc_la->prx);
	// ���������� �������� �������� ���������� ����
	*(mb_servc_la->ptx++) = (numbofpoints * 2);

	// ���� � ���� �������� ������ �� ������� ������
    for (cntmbreg = 0; cntmbreg <= numbofpoints; cntmbreg++)
    {
    	// ���������� �������� ������ ��� ��������
    	*(mb_servc_la->ptx + (cntmbreg * 2)) = (*(pMBmemory_la + startadress + cntmbreg) & 0xFF00) >> 8;
    	*(mb_servc_la->ptx + (cntmbreg * 2) + 1) = (*(pMBmemory_la + startadress + cntmbreg) & 0xFF);
    }
    // ������ ������� ���������� ����������� �����
    usCRC16 = usMBCRC16((Uchar*) & *(mb_servc_la->ptx - 3), (*(mb_servc_la->ptx - 1) + 3));
    // ������ ������� �������� ������� �����
    *(mb_servc_la->ptx + *(mb_servc_la->ptx - 1)) = (Uchar)( usCRC16 & 0xFF );
    // ������ ������� �������� ������� �����
    *(mb_servc_la->ptx + *(mb_servc_la->ptx - 1) + 1) = (Uchar)( usCRC16 >> 8 );
    // ���������� ����� ���������� ������
    mb_servc_la->length_tx = 7 + *(mb_servc_la->ptx - 1);
    // ��������� ����� ��������
    mb_servc_la->flgs.tx_rx = 1;
    // ������� ��������� ������
    return LMBStatus;
}


//----------------------------------------------------------------------------------------------------------------
// �������:  			MBReadInptReg
// ��������: 			���������� ������� 4, ��������� modbus "������ ������� ���������"
// ����:  	  			��������� ������ ��������� ���������� modbus'�:
//						"
//						��� ����������:		�������������� ����������:	��� ����������:
//						Uint16				������ ����������� ������	mb_servc_l->rx
//						Uint16				������ ������������ ������	mb_servc_l->tx
//						"
//						��� ����������:		�������������� ����������:	��� ����������:
//						Uint16				��������� modbus �������	pMBmemory_l
// �����: 	  			��������� ������ ��������� ���������� modbus'�:
//						"
//						��� �������:		�������������� �������:		��� �������:
// 						Uint16				����� ������������ �������	mb_servc_la->length_tx
//						Uint16				��������� �� ���� �������	mb_servc_la->prx
//						Uint16				��������� �� �������� 		mb_servc_la->ptx
//											�������
//						Uint16				���� ����������� �������� 	mb_servc_la->flgs.tx_rx
//											tx_rx == 1 (�������) �����
//											(����)
//						"
// �����.����.�-���.:	��� �������			�������������� �������		��� �������
//						eMBErrorCode		��������� modbus �������	MBReadInptReg
// ������ ������: 		MBReadInptReg(MB_Servc *��������� ������ ��������� ���������� modbus'�, Uint16 *��������� modbus �������)
//----------------------------------------------------------------------------------------------------------------
eMBErrorCode MBReadInptReg(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la)
{
	// ���������� ��������� ���������� ��������� modbus
	eMBErrorCode    LMBStatus = MB_ENOERR;
	// ���������� ���������� (��������� �����, ���������� ������, ������� ������� ���������
	Uint16 startadress, numbofpoints, cntmbreg;
	// ���������� ����� ��������
	mb_servc_la->length_tx = 0;
	// ���������� �������� ���������� ������
	startadress =  (*(mb_servc_la->prx + 3) & 0xFF) + ((*(mb_servc_la->prx + 2) & 0xFF) << 8);
	// ���������� �������� ���������� ������
	numbofpoints = (*(mb_servc_la->prx + 5) & 0xFF) + ((*(mb_servc_la->prx + 4) & 0xFF) << 8);

	// ���������� �������� ������� (�����)
	*(mb_servc_la->ptx++) = *(mb_servc_la->prx++);
	// ���������� �������� ������� (����� �������)
	*(mb_servc_la->ptx++) = *(mb_servc_la->prx);
	// ���������� �������� �������� ���������� ����
	*(mb_servc_la->ptx++) = (numbofpoints * 2);
	// ���� � ���� �������� ������ �� ������� ������
    for (cntmbreg = 0; cntmbreg <= numbofpoints; cntmbreg++)
    {
    	// ���������� �������� ������ ��� ��������
    	*(mb_servc_la->ptx + (cntmbreg * 2))= (*(pMBmemory_la + startadress + cntmbreg) & 0xFF00) >> 8;
    	*(mb_servc_la->ptx + (cntmbreg * 2) + 1)= (*(pMBmemory_la + startadress + cntmbreg) & 0xFF);
    }
    // ������ ������� ���������� ����������� �����
    usCRC16 = usMBCRC16((Uchar*) & *(mb_servc_la->ptx - 3), (*(mb_servc_la->ptx - 1) + 3));
    // ������ ������� �������� ������� �����
    *(mb_servc_la->ptx + *(mb_servc_la->ptx - 1)) = (Uchar)( usCRC16 & 0xFF );
    // ������ ������� �������� ������� �����
    *(mb_servc_la->ptx + *(mb_servc_la->ptx - 1) + 1) = (Uchar)( usCRC16 >> 8 );
    // ���������� ����� ���������� ������
    mb_servc_la->length_tx = 7 + *(mb_servc_la->ptx - 1);
    // ��������� ����� ��������
    mb_servc_la->flgs.tx_rx = 1;
    // ������� ��������� ������
    return LMBStatus;
}


//----------------------------------------------------------------------------------------------------------------
// �������:  			MBPresetSinglReg
// ��������: 			���������� ������� 5, ��������� modbus "������ ������ �������� � ������� ��������"
// ����:  	  			��������� ������ ��������� ���������� modbus'�:
//						"
//						��� ����������:		�������������� ����������:	��� ����������:
//						Uint16				������ ����������� ������	mb_servc_l->rx
//						Uint16				������ ������������ ������	mb_servc_l->tx
//						"
//						��� ����������:		�������������� ����������:	��� ����������:
//						Uint16				��������� modbus �������	pMBmemory_l
// �����: 	  			��������� ������ ��������� ���������� modbus'�:
//						"
//						��� �������:		�������������� �������:		��� �������:
// 						Uint16				����� ������������ �������	mb_servc_la->length_tx
//						Uint16				��������� �� ���� �������	mb_servc_la->prx
//						Uint16				��������� �� �������� 		mb_servc_la->ptx
//											�������
//						Uint16				���� ����������� �������� 	mb_servc_la->flgs.tx_rx
//											tx_rx == 1 (�������) �����
//											(����)
//						"
// �����.����.�-���.:	��� �������			�������������� �������		��� �������
//						eMBErrorCode		��������� modbus �������	MBPresetSinglReg
// ������ ������: 		MBPresetSinglReg(MB_Servc *��������� ������ ��������� ���������� modbus'�, Uint16 *��������� modbus �������)
//----------------------------------------------------------------------------------------------------------------
eMBErrorCode MBPresetSinglReg(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la)
{
	// ���������� ��������� ���������� ��������� modbus
	eMBErrorCode    LMBStatus = MB_ENOERR;
	// ���������� ���������� ���������� ������
	Uint16 startadress, cntmsg;
	// ���������� ���������� ������
	startadress = (*(mb_servc_la->prx + 3) & 0xFF) + ((*(mb_servc_la->prx + 2) & 0xFF) << 8);

	// ���������� ������ ��� ������	� ������
	*(pMBmemory_la + startadress) = (*(mb_servc_la->prx + 5) & 0xFF)|((*(mb_servc_la->prx + 4) & 0xFF) << 8);

	// ���� � ���� �������� ������
	for (cntmsg = 0; cntmsg < 4; cntmsg++)
	{
		// �������� �������� ������
		*(mb_servc_la->ptx++) = *(mb_servc_la->prx++);
	}

	// �������� �������� ������ ����� (Preset Data Hi)
	*(mb_servc_la->ptx++) = (*(pMBmemory_la + startadress) & 0xFF00) >> 8;
	// �������� �������� ������� ����� (Preset Data Lo)
	*(mb_servc_la->ptx++) = *(pMBmemory_la + startadress)  & 0xFF;
	// ���������� ����������� ����� CRC16
	usCRC16 = usMBCRC16( (Uchar*)(mb_servc_la->ptx - 6), 6);
	// �������� ������  ����������� ����� CRC16 Hi
	*(mb_servc_la->ptx++) =  (Uchar)( usCRC16 & 0xFF );
	// �������� ������ ����������� ����� CRC16 Lo
	*(mb_servc_la->ptx) =  (Uchar)( usCRC16 >> 8 );
	// ������� ���������� �����
	mb_servc_la->length_tx = 10;
	// ��������� ����� ���������� ��������
	mb_servc_la->flgs.tx_rx = 1;
    // ������� ��������� ������
    return LMBStatus;
}


//----------------------------------------------------------------------------------------------------------------
// �������:  			MBWriteSinglCoil
// ��������: 			���������� ������� 6, ��������� modbus "��������� ���������� ������ ON/OFF"
// ����:  	  			��������� ������ ��������� ���������� modbus'�:
//						"
//						��� ����������:		�������������� ����������:	��� ����������:
//						Uint16				������ ����������� ������	mb_servc_l->rx
//						Uint16				������ ������������ ������	mb_servc_l->tx
//						"
//						��� ����������:		�������������� ����������:	��� ����������:
//						Uint16				��������� modbus �������	pMBmemory_l
// �����: 	  			��������� ������ ��������� ���������� modbus'�:
//						"
//						��� �������:		�������������� �������:		��� �������:
// 						Uint16				����� ������������ �������	mb_servc_la->length_tx
//						Uint16				��������� �� ���� �������	mb_servc_la->prx
//						Uint16				��������� �� �������� 		mb_servc_la->ptx
//											�������
//						Uint16				���� ����������� �������� 	mb_servc_la->flgs.tx_rx
//											tx_rx == 1 (�������) �����
//											(����)
//						"
// �����.����.�-���.:	��� �������			�������������� �������		��� �������
//						eMBErrorCode		��������� modbus �������	MBWriteSinglCoil
// ������ ������: 		MBWriteSinglCoil(MB_Servc *��������� ������ ��������� ���������� modbus'�, Uint16 *��������� modbus �������)
//----------------------------------------------------------------------------------------------------------------
eMBErrorCode MBWriteSinglCoil(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la)
{
	// ���������� ��������� ���������� ��������� modbus
	eMBErrorCode    LMBStatus = MB_ENOERR;
	// ���������� ���������� ���������� ������
	Uint16 startadress, startadresscoils, cntmsg;

	// ���������� ���������� ������ �������
	startadresscoils = (*(mb_servc_la->prx + 3) & 0xFF) + ((*(mb_servc_la->prx + 2) & 0xFF) << 8);

	// ���� ���������� �������� ������������ ���������� ������
	for (startadress = 0; startadresscoils > 16; startadress++)
	{
		// ���������� �� 8 ����� ��� ���������� ������ ������
		startadresscoils -= 16;
	}

	// ���� ������� ���������� �� ��������� �������� ���� "1"
	if (*(mb_servc_la->prx + 4) == 0xFF)
	// ������������ ����
	*(pMBmemory_la + startadress) |= (1 << startadresscoils);

	// ���� ������� ���������� �� ��������� �������� ���� "0"
	if (*(mb_servc_la->prx + 4) == 0x00)
		// ������������ ����
	*(pMBmemory_la + startadress) &= ~(1 << startadresscoils);
	// ������ ������� ���������
	for (cntmsg = 0; cntmsg < 6; cntmsg++)
	{
		// �������� �������� ������
		*(mb_servc_la->ptx++) = *(mb_servc_la->prx++);
	}

	// ���������� ����������� ����� CRC16
	usCRC16 = usMBCRC16( (Uchar*) & *(mb_servc_la->ptx - 6), 6);
	// �������� ������  ����������� ����� CRC16 Hi
	*(mb_servc_la->ptx++) =  (Uchar)(usCRC16 & 0xFF);
	// �������� ������ ����������� ����� CRC16 Lo
	*(mb_servc_la->ptx) =  (Uchar)(usCRC16 >> 8);
	// ������� ���������� �����
	mb_servc_la->length_tx = 10;
	// ������������ ����� ���������� ��������
	mb_servc_la->flgs.tx_rx = 1;
    // ������� ��������� ������
    return LMBStatus;
}


//----------------------------------------------------------------------------------------------------------------
// �������:  			MBForceMultCoils
// ��������: 			���������� ������� 15, ��������� modbus "������ ���������� �����"
// ����:  	  			��������� ������ ��������� ���������� modbus'�:
//						"
//						��� ����������:		�������������� ����������:	��� ����������:
//						Uint16				������ ����������� ������	mb_servc_l->rx
//						Uint16				������ ������������ ������	mb_servc_l->tx
//						"
//						��� ����������:		�������������� ����������:	��� ����������:
//						Uint16				��������� modbus �������	pMBmemory_l
// �����: 	  			��������� ������ ��������� ���������� modbus'�:
//						"
//						��� �������:		�������������� �������:		��� �������:
// 						Uint16				����� ������������ �������	mb_servc_la->length_tx
//						Uint16				��������� �� ���� �������	mb_servc_la->prx
//						Uint16				��������� �� �������� 		mb_servc_la->ptx
//											�������
//						Uint16				���� ����������� �������� 	mb_servc_la->flgs.tx_rx
//											tx_rx == 1 (�������) �����
//											(����)
//						"
// �����.����.�-���.:	��� �������			�������������� �������		��� �������
//						eMBErrorCode		��������� modbus �������	MBForceMultCoils
// ������ ������: 		MBForceMultCoils(MB_Servc *��������� ������ ��������� ���������� modbus'�, Uint16 *��������� modbus �������)
//----------------------------------------------------------------------------------------------------------------
eMBErrorCode MBForceMultCoils(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la)
{

	// ���������� ��������� ���������� ��������� modbus
	eMBErrorCode    LMBStatus = MB_ENOERR;

	// � ������� ������ ������� �������� ��������� � ���������� ��� �������

    return LMBStatus;
}


//----------------------------------------------------------------------------------------------------------------
// �������:  			MBPresetMultRegs
// ��������: 			���������� ������� 16, ��������� modbus "������ ���������� ���������"
// ����:  	  			��������� ������ ��������� ���������� modbus'�:
//						"
//						��� ����������:		�������������� ����������:	��� ����������:
//						Uint16				������ ����������� ������	mb_servc_l->rx
//						Uint16				������ ������������ ������	mb_servc_l->tx
//						"
//						��� ����������:		�������������� ����������:	��� ����������:
//						Uint16				��������� modbus �������	pMBmemory_l
// �����: 	  			��������� ������ ��������� ���������� modbus'�:
//						"
//						��� �������:		�������������� �������:		��� �������:
// 						Uint16				����� ������������ �������	mb_servc_la->length_tx
//						Uint16				��������� �� ���� �������	mb_servc_la->prx
//						Uint16				��������� �� �������� 		mb_servc_la->ptx
//											�������
//						Uint16				���� ����������� �������� 	mb_servc_la->flgs.tx_rx
//											tx_rx == 1 (�������) �����
//											(����)
//						"
// �����.����.�-���.:	��� �������			�������������� �������		��� �������
//						eMBErrorCode		��������� modbus �������	MBPresetMultRegs
// ������ ������: 		MBPresetMultRegs(MB_Servc *��������� ������ ��������� ���������� modbus'�, Uint16 *��������� modbus �������)
//----------------------------------------------------------------------------------------------------------------
eMBErrorCode MBPresetMultRegs(MB_Servc *mb_servc_la, Uint16 *pMBmemory_la)
{
	// ���������� ��������� ���������� ��������� modbus
	eMBErrorCode    LMBStatus = MB_ENOERR;
	// ���������� ��������� ����������
	Uint16 startadress, bytecount, cntmbreg, cntmsg;

	// ���������� ���������� ������
	startadress = (*(mb_servc_la->prx + 3) & 0xFF) + ((*(mb_servc_la->prx + 2) & 0xFF) << 8);
	// ���������� ���������� ����
	bytecount = (*(mb_servc_la->prx + 6) & 0xFF) >> 1;

	// ���� � ���� ������ ���������
	for (cntmbreg = 0; cntmbreg < bytecount; cntmbreg++)
	{
		// ������ �������� modbus
		*(pMBmemory_la + startadress + cntmbreg) = (*(mb_servc_la->prx + 8 + (cntmbreg * 2)) & 0xFF)|((*(mb_servc_la->prx + 7 + (cntmbreg * 2)) & 0xFF)<<8);
	}
	// ������ ��������� ������
	for (cntmsg = 0; cntmsg < 6; cntmsg++)
	{
		// �������� �������� ������
		*(mb_servc_la->ptx++) = *(mb_servc_la->prx++);
	}

	// ���������� ����������� ����� CRC16
	usCRC16 = usMBCRC16((Uchar*) & *(mb_servc_la->ptx - 6), 6);
	// �������� ������  ����������� ����� CRC16 Hi
	*(mb_servc_la->ptx++) =  (Uchar)(usCRC16 & 0xFF);
	// �������� ������ ����������� ����� CRC16 Lo
	*(mb_servc_la->ptx) =  (Uchar)(usCRC16 >> 8);
	// ������� ���������� �����
	mb_servc_la->length_tx = 10;
	// ������������ ����� ���������� ��������
	mb_servc_la->flgs.tx_rx = 1;
    // ������� ��������� ������
    return LMBStatus;
}
