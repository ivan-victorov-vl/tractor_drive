//----------------------------------------------------------------------------------
//	FILE:			MainCPU-Main.C
//----------------------------------------------------------------------------------


#include "PeripheralHeaderIncludes.h"
#include "MainCPU-Main.h"					
#include "Smpl_table.h"

#define	mark1_toggle	GpioDataRegs.GPBTOGGLE.bit.GPIO39
#define	mark1_dat		GpioDataRegs.GPBDAT.bit.GPIO39
#define	mark2_toggle	GpioDataRegs.GPCTOGGLE.bit.GPIO84
#define	mark2_dat		GpioDataRegs.GPCDAT.bit.GPIO84
#define	mark3_toggle	GpioDataRegs.GPBTOGGLE.bit.GPIO46

//���������� �������--------------------------------------
//interrupt void cpu_timer0_isr(void);
//interrupt void cpu_timer1_isr(void);
//interrupt void cpu_timer2_isr(void);
//interrupt void scib_rx_isr(void);
//interrupt void scic_rx_isr(void);
interrupt void epwm4_timer_isr(void);
interrupt void epwm6_timer_isr(void);
interrupt void cpu_int13_isr(void);

void Init_Data();
void InitFlash();
void InitEPwm_4_6Timers(int16 prd, int16 sync_lnth, int16 start_lnth);
void InitSCIA(void);
void InitSCIB(void);
void InitSCIC(void);
void InitSPIA(void);
void InitSysCtrl(void);
void InitPieCtrl(void);
void InitPieVectTable(void);

void InitMAX7301(Uint16 device);
void InitAD7732(Uint16 device);

//void TransfData(Uint16 Data_out[], Uint16 numb_mes);
void Cells_Check();
void Exch_data_SPI(Uint16 device, Uint16* message);
void Stup_SPI_exch(Uint16 dev_sel);
void Get_RX_SCI(volatile struct SCI_REGS *ScixRegs, Uint16 RXmode, struct TX_FRAME *txd, union	CELL_DATA_UNION	_cell[], struct STORE_DATA *store[]);
//===================================================================
void main(void)
{
//-------------------------------------------------------------------------------------
//	������������� �����������
	
	InitSysCtrl();
//	���������� ���������� 
	DINT;
	InitPieCtrl();
//	���������� ���������� � ����� ������
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();
   	
	InitFlash();	
		 
//	�������������� ������� ��������� ����������
	EALLOW;  // This is needed to write to EALLOW protected registers
//	PieVectTable.TINT0 = &cpu_timer0_isr;		//���������� �� ������� 0
	PieVectTable.XINT13 = &cpu_int13_isr;		//���������� �� int13
//	PieVectTable.TINT2 = &cpu_timer2_isr;		//���������� �� ������� 2
//	PieVectTable.SCIRXINTB = &scib_rx_isr;		//���������� �� SCIB
//	PieVectTable.SCIRXINTC = &scic_rx_isr;		//���������� �� SCIC
	PieVectTable.EPWM4_INT = &epwm4_timer_isr;	//���������� �� pwm4
	PieVectTable.EPWM6_INT = &epwm6_timer_isr;	//���������� �� pwm5
	EDIS;    // This is needed to disable write to EALLOW protected registers

//	������������� �������
	InitCpuTimers();							// ���������������� ������� CPU

	InitSCIA();									//���������������� SCIA	
	InitSCIB();									//���������������� SCIB	
	InitSCIC();									//���������������� SCIC
	InitSPIA();									//���������������� SPIA

	P33V_ON();			//�������� ������� ������
		{//�������� ����� ������ �������____________
		Uint16 a;
		for(a = 0; a < 0xFFFF; a++) {};					
		}//_________________________________________

	InitMAX7301(EXP1_dev_SEL);
	InitMAX7301(EXP2_dev_SEL);
	InitAD7732(ADC1_dev_SEL);
	InitAD7732(ADC2_dev_SEL);

		//������ ������ � SPI...............................
		spi_store.spi_dev = 0;
		Stup_SPI_exch(ADC1_dev_SEL);
		GpioDataRegs.GPACLEAR.all = spi_store.spi_dev;	//������������ ��������� ����������
		//��������� ��� ��������
		SpiaRegs.SPITXBUF = spi_store.data[spi_store.nmb_byte - spi_store.remn_nmb_byte];					
		spi_store.remn_nmb_byte--;							//��������� ������� �� 1
		//..................................................

//��������� ������� EPWM1 � EPWM2 ��� ��������� �������������� ������� �������� ��������
	InitEPwm_4_6Timers(trans_per, trans_sync_lenth, trans_start);

	//Init_Data();

// Configure CPU-Timers:
//	ConfigCpuTimer(&CpuTimer0Regs, Prd0, 1);		//��������� ������0 �������� ����������
	ConfigCpuTimer(&CpuTimer1Regs, Prd1, 0);		//��������� ������1 ��������� ����������
	ConfigCpuTimer(&CpuTimer2Regs, Prd2, 0);		//��������� ������1 ��������� ����������

// Enable CPU interrapts:
//	IER |= M_INT1;		//CPU int1 is connected to CPU-Timer 0
	IER |= M_INT3;		//CPU int3 is connected to epwm
	IER	|= M_INT8;		//CPU int8 is connected to SCIC
	IER	|= M_INT9;		//CPU int9 is connected to SCIA/B
	IER |= M_INT13;		//CPU int13 
//	IER |= M_INT14;		//CPU int14 is connected to CPU-Timer 2

//	CpuTimer0Regs.TCR.all = 0x4001;			// ��������� ������ 0 (TSS bit = 0)
	CpuTimer1Regs.TCR.all = 0x4001;			// ��������� ������ 1
	CpuTimer2Regs.TCR.all = 0x4001;			// ��������� ������ 2

// Enable PIE
//	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;	//timer0
	PieCtrlRegs.PIEIER3.bit.INTx4 = 1;	//pwm4
	PieCtrlRegs.PIEIER3.bit.INTx6 = 1;	//
//	PieCtrlRegs.PIEIER9.bit.INTx1 = 1;	//SCIA_RX
//	PieCtrlRegs.PIEIER9.bit.INTx3 = 1;	//SCIB_RX
//	PieCtrlRegs.PIEIER8.bit.INTx5 = 1;	//SCIC_RX

// Enable global Interrupts and higher priority real-time debug events:
	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM
//-------------------------------------------------------
//�������� ����������� ��������� �������������


	Cells_Check(); 


//*****************************************************************************************************
// Step 6. �������� ����:
	for(;;)
		{//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			{//����� ������� � SPI ������������  ++++++++++++++++++++++++++++++++++++++++++++++++
			static Uint16 a = 0;
			static Uint16 b = 0;
			static Uint16 c = 0;

			if(SpiaRegs.SPISTS.bit.INT_FLAG)	//���� ���� ���������� �������� ����������
				{//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
				Deact_SPI_dev();			//��������� ��� ���������� SPI

				{Uint16 i;
				for(i=0;i<5;i++) {};}		//�������� 

				//��������� �������� ���������		
				spi_store.data[spi_store.nmb_byte - (spi_store.remn_nmb_byte + 1)] = SpiaRegs.SPIRXBUF;

				if(!spi_store.remn_nmb_byte)			//���� ������� ��������� ����, ��
					{//------------------------------------------------
					if(c & CpuTimer1Regs.TCR.bit.TIF)  		//��������� ���������� ������ ADC
				 		{
				  		if(a) {Stup_SPI_exch(ADC1_dev_SEL);}
						else  {Stup_SPI_exch(ADC2_dev_SEL);}
						a ^=1;										//������������� ���� ����������� ������ ADC
						c ^=1;
				 		CpuTimer1Regs.TCR.bit.TIF = 1;      		//�������� ����
						}
					else
						{
						if(b) {Stup_SPI_exch(EXP1_dev_SEL);}
						else  {Stup_SPI_exch(EXP2_dev_SEL);}
						b ^=1;										//������������� ���� ����������� ������ EXP
						c ^=1;
						}
					}//------------------------------------------------

				GpioDataRegs.GPACLEAR.all = spi_store.spi_dev;	//������������ ��������� ����������
				//��������� ��� ��������
				SpiaRegs.SPITXBUF = spi_store.data[spi_store.nmb_byte - spi_store.remn_nmb_byte];					
				spi_store.remn_nmb_byte--;							//��������� ������� �� 1

				}//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			}//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//�������� ������� ������� ������------------------------------------------
		if(S_D_MODE == SINGLE_MODE) 
			{//������� ����� ��������� ������^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			if(MSmode != sngl_mode)			//���� ����� ������, ��
				{//-----------------------------------------
				SciaRegs.SCICTL1.bit.RXENA	= 0;	//��������� ��������  RS485_2  (�)
				ScicRegs.SCICTL1.bit.RXENA	= 0;	//��������� ��������  RS485_1  (c)

				XIntruptRegs.XNMICR.bit.ENABLE = 0;	//��������� ���������� �����

				MSmode = sngl_mode;
				}//-----------------------------------------
			}//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		else //if S_D_MODE == DOUBLE_MODE
			{//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  
			SciaRegs.SCICTL1.bit.RXENA	= 0;	//��������� ��������  SCI�  (�)
			ScicRegs.SCICTL1.bit.RXENA	= 1;	//�������� ��������  SCIc  (c)

			DE1_RS485_dsbl();					//��������� ���������� RS485_1
			DE2_RS485_dsbl();					//��������� ���������� RS485_2

			if	(M_S_MODE == MASTER_MODE)
				{//����� ������ ������, �������>>>>>>>>>>>>>>>>>>>		  */
				if(MSmode != master_mode) //���� ����� ������, ��
					{//-----------------------------------------
					EALLOW;  // This is needed to write to EALLOW protected registers
						GpioCtrlRegs.GPBMUX1.bit.GPIO35  = 	0; 	// 0=GPIO,  1=SCIA-TX,  2=Resv,  3=Resv
						XIntruptRegs.XNMICR.bit.ENABLE = 0;					//
					EDIS;    // This is needed to disable write to EALLOW protected registers
					MSmode = master_mode;
					}//-----------------------------------------
				}//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			else //if M_S_MODE == SLAVE_MODE	
				{//����� ������ ������, �������>>>>>>>>>>>>>>>>>>>
				if(MSmode != slave_mode)  //���� ����� ������, ��
					{//-----------------------------------------
					EALLOW;  // This is needed to write to EALLOW protected registers
						GpioCtrlRegs.GPBMUX1.bit.GPIO35  = 	1; 	// 0=GPIO,  1=SCIA-TX,  2=Resv,  3=Resv
						XIntruptRegs.XNMICR.bit.ENABLE = 1;		//��������� ���������� �� �����
					EDIS;    // This is needed to disable write to EALLOW protected registers

					MSmode = slave_mode;
					}//-----------------------------------------
				}//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			}//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		if(ON_OFF) Prmt_Work = off;			//��������� ������
		else 	   Prmt_Work = on;			//��������� ������

		Cells_Check();

		}//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//*****************************************************************************************************
} 	
//========================================================================

//-------------------------------------------------------------------------------------/
//-------------------------------------------------------------------------------------/
	//��� ������� ������������ ������� ���������� 1 �� ������ ��� ������ �� ������ sync_in--
	interrupt void cpu_int13_isr(void)
		{
		EPwm4Regs.TBCTL.bit.SWFSYNC = 1;
		sync_ok = 1;
		}

//-------------------------------------------------------------------------------------/
//-------------------------------------------------------------------------------------/

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
	//������� �� ���������� �� ������� PWM4-----------------------------------
	//�������� ������ SCI, �������� ����������� ��������� ������
	interrupt void epwm4_timer_isr(void) 
		{ //SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
		if(MSmode == master_mode)
			{//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			Drp_sync_4slv(); 		//�������� ������ ������������� ��� ��������

			Get_RX_SCI(&ScicRegs, RX_FROM_SLAVE, &tx_4slv, slv_cell, store_slv_indx);

			Set_sync_4slv();		//���������� ������ ������������� ��� ��������
			}//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		if((sync_ok) & (MSmode == slave_mode))
			{//--------------------------------------------------------------------------

			//��������� ������ �� ����� SCIC~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			retr_mstr_cell[9]=0;				//�������� ������� ��������������� ������
			if(ScicRegs.SCIRXST.bit.RXERROR)				//���� ������, ��:
				{//-----------------------------------------------------------------------
				ScicRegs.SCICTL1.bit.RXENA	=	0;			//��������� ��������

				ScicRegs.SCICTL1.bit.SWRESET = 0;			//�������� �����
				ScicRegs.SCICTL1.bit.SWRESET = 1;
				ScicRegs.SCIFFRX.bit.RXFIFORESET = 0;		//�������� ��������� FIFO RX	
				ScicRegs.SCIFFRX.bit.RXFIFORESET = 1;
				}//----------------------------------------------------------------------

			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			else //���� ������ ���, ��:
				{//====================================================================
				for(;ScicRegs.SCIFFRX.bit.RXFFST;)
					{//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
					retr_mstr_cell[retr_mstr_cell[9]] = ScicRegs.SCIRXBUF.all & 0xFF;		//��������� ���� ���������
					retr_mstr_cell[9]++;		
					}//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
				}//====================================================================

			ScicRegs.SCICTL1.bit.RXENA	=	1;			//�������� ��������
			//����� ��������� ������ �� ����� SCIC~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			//��������� ������ �� ����� SCIB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			retr_cell_mstr[9]=0;				//�������� ������� ��������������� ������
			if(ScibRegs.SCIRXST.bit.RXERROR)				//���� ������, ��:
				{//-----------------------------------------------------------------------
				ScibRegs.SCICTL1.bit.RXENA	=	0;			//��������� ��������

				ScibRegs.SCICTL1.bit.SWRESET = 0;			//�������� �����
				ScibRegs.SCICTL1.bit.SWRESET = 1;
				ScibRegs.SCIFFRX.bit.RXFIFORESET = 0;		//�������� ��������� FIFO RX	
				ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;
				}//----------------------------------------------------------------------

			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			else //���� ������ ���, ��:
				{//====================================================================
				for(;ScibRegs.SCIFFRX.bit.RXFFST;)
					{//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
					retr_cell_mstr[retr_cell_mstr[9]] = ScibRegs.SCIRXBUF.all & 0xFF;		//��������� ���� ���������
					retr_cell_mstr[9]++;		
					}//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
				}//====================================================================
			ScibRegs.SCICTL1.bit.RXENA	=	1;			//�������� ��������
	 		//����� ��������� ������ �� ����� SCIB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			}//-------------------------------------------------------------------------- 
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




		if(MSmode != slave_mode)		
			{//��������� ������ �� ����� SCIB+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			Get_RX_SCI(&ScibRegs, RX_FROM_CELLS, &tx, cell, store_indx);
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

			
			//����������� ������� ������� ������
			if(CpuTimer2Regs.TCR.bit.TIF)
				{//-------------------------------------------------------
				Uint16 i;
				//������� ���������� �������� �������
				//������� �������
				//-------------------------------------------------------
				CurNum_Smpl[0]++;			//���������������� �������� ������ �������� �������
				CurNum_Smpl[1]++;
				CurNum_Smpl[2]++;

				for(i=0;i<3;i++)
					{
/*					if(CurNum_Smpl[i] <= 90) tx.Smpl_F[i].all = Smpl_sin[CurNum_Smpl[i]];
					else
						{
						if(CurNum_Smpl[i] <= 180) tx.Smpl_F[i].all = Smpl_sin[180-CurNum_Smpl[i]];
						else
							{
							if(CurNum_Smpl[i] <= 270) tx.Smpl_F[i].all = 2*Smpl_sin[0] - Smpl_sin[CurNum_Smpl[i]-180];
							else
								{
								if(CurNum_Smpl[i] < 360) tx.Smpl_F[i].all = 2*Smpl_sin[0] - Smpl_sin[360-CurNum_Smpl[i]];
								else
									{
									CurNum_Smpl[i] = 0;
									tx.Smpl_F[i].all = Smpl_sin[0];
						}	}	}	}	

					tx_4slv.Smpl_F[i].all = tx.Smpl_F[i].all;		//��������� �������� ��� ��������
*/
					if(CurNum_Smpl[i] <= 90) Smpl_F[i] = Smpl_sin[CurNum_Smpl[i]];
					else
						{
						if(CurNum_Smpl[i] <= 180) Smpl_F[i] = Smpl_sin[180-CurNum_Smpl[i]];
						else
							{
							if(CurNum_Smpl[i] <= 270) Smpl_F[i] = 2*Smpl_sin[0] - Smpl_sin[CurNum_Smpl[i]-180];
							else
								{
								if(CurNum_Smpl[i] < 360) Smpl_F[i] = 2*Smpl_sin[0] - Smpl_sin[360-CurNum_Smpl[i]];
								else
									{
									CurNum_Smpl[i] = 0;
									Smpl_F[i] = Smpl_sin[0];
						}	}	}	}					}
				CpuTimer2Regs.TCR.bit.TIF = 1;		//�������� ����
				}//-------------------------------------------------------
			}//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						 
		EPwm4Regs.ETCLR.bit.INT = 1;				//�������� ����
		PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
		}//SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
	//������� �� ���������� �� ������� PWM6-----------------------------------
	//��������� �������� ������	������ 55,52 ���
	interrupt void epwm6_timer_isr(void)
		{//SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
		static	Uint16 frame_cnt = 0;		//���������� ��� ����� �������
		
		//---------------------------------------------------------------------------
			frame_cnt++;							//���������������� ������� ���������
			if(frame_cnt == 30)						//���� ���� ������ ������� ��������,
				{tx.serv.bit.saw_sync = 1;			//���������� ��� ������������� ������� ����
				 frame_cnt = 0;}						//�������� �������
			else 
				{tx.serv.bit.saw_sync = 0;}			//�������� ��� ������������� ������� ����
			if(frame_cnt == 29)						//���� ���� ������ ������� ��������,
				{tx_4slv.serv.bit.saw_sync = 1;}			//���������� ��� ������������� ������� ����
			else 
				{tx_4slv.serv.bit.saw_sync = 0;}
		//---------------------------------------------------------------------------


			if(MSmode != slave_mode)	
				{//===========================================================================================================
				//������������ �������� ��� �������� ������------------------------------
				if(tx.serv.bit.mode)		//���� ���������� ������� �����, ��
					{//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
								tx.Smpl_F[0].all = store_Smpl_F[0];
								tx.Smpl_F[1].all = store_Smpl_F[1];
								tx.Smpl_F[2].all = store_Smpl_F[2];

					//������������ ������� ��� �������� ������:
					tx_frame[0] = tx.serv.all;
					tx_frame[1] = tx.Smpl_F[0].byte.low;	//�������� ������� ���������
					tx_frame[2] = tx.Smpl_F[0].byte.high;	//�������� ������� ���������
					tx_frame[3] = tx.Smpl_F[1].byte.low;	//�������� ������� ���������
					tx_frame[4] = tx.Smpl_F[1].byte.high;	//�������� ������� ���������
					tx_frame[5] = tx.Smpl_F[2].byte.low;	//�������� ������� ���������
					tx_frame[6] = tx.Smpl_F[2].byte.high;	//�������� ������� ���������
					tx_frame[7] = tx.CRC;
					
					tx.serv.bit.cell_indx++;
					if(tx.serv.bit.cell_indx >= NUMB_OF_CELLS) tx.serv.bit.cell_indx = 0;

					}//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

				//������������ �������� ��� ������ �������������------------------------------
				else
					{//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
					static	Uint16	param_cnt = 0;		//������ ��������������� ���������� ��� ����� ����������
					static	Uint16	i_cell_cnt = 0;		//���������� ��� ����� �����						
									
					//������������ ������� ��� ������ �������������:						
					tx_frame[0] = tx.serv.all;
					tx_frame[1] = cell[i_cell_cnt].word.cell_indx;	//�������� ����� ������ � ����
					tx_frame[2] = cell[i_cell_cnt].word.phase_indx;	//�������� ����� ����
					tx_frame[3] = param_cnt;						//�������� ����� ���������
					tx_frame[4] = 0;								//�������� 0
					tx_frame[5] = 0;								//�������� 0
					tx_frame[6] = 0;								//�������� 0
					tx_frame[7] = tx.CRC;

					param_cnt++;
					if(param_cnt >= nmb_of_askprm)
						{//--------------------------
						param_cnt = 0;
						i_cell_cnt++;
						if(i_cell_cnt >= NUMB_OF_CELLS * 3)	{i_cell_cnt = 0;}														
						}//--------------------------	
					}//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
				//-----------------------------------------------------------------------
				
					{//��������� �������� -----------------------------
					Uint16 i;
					ScibRegs.SCIFFTX.bit.TXFIFOXRESET = 0;	//�������� ��������� FIFO TX
					ScibRegs.SCIFFTX.bit.TXFIFOXRESET = 1;

					for(i=0;i < numb_mes;i++) 
						ScibRegs.SCITXBUF = tx_frame[i] & 0xFF;//�������� � ����� �������� ������� ���������
					}//------------------------------------------------
					
					{//��������� ������� �� ����� ����� ������� �����--
					Uint16 a;
					struct	STORE_DATA  *b;

					store_indx[1]->serv.all = tx_frame[0];
					for(a=0;a < 6;a++)	 store_indx[1]->data[a] = tx_frame[a+1];
					//����� ��������	
					b = store_indx[0];
					store_indx[0] = store_indx[1];
					store_indx[1] =  b;
					}//------------------------------------------------
				}//===========================================================================================================


				if(MSmode == master_mode)
					{//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
					//������������ �������� ��� �������� ������------------------------------
					if(tx_4slv.serv.bit.mode)		//���� ���������� ������� �����, ��
						{//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
								store_Smpl_F[0] = tx_4slv.Smpl_F[0].all = Smpl_F[0];
								store_Smpl_F[1] = tx_4slv.Smpl_F[1].all = Smpl_F[1];
								store_Smpl_F[2] = tx_4slv.Smpl_F[2].all = Smpl_F[2];


						//������������ ������� ��� �������� ������:
						tx_frame[0] = tx_4slv.serv.all;
						tx_frame[1] = tx_4slv.Smpl_F[0].byte.low;	//�������� ������� ���������
						tx_frame[2] = tx_4slv.Smpl_F[0].byte.high;	//�������� ������� ���������
						tx_frame[3] = tx_4slv.Smpl_F[1].byte.low;	//�������� ������� ���������
						tx_frame[4] = tx_4slv.Smpl_F[1].byte.high;	//�������� ������� ���������
						tx_frame[5] = tx_4slv.Smpl_F[2].byte.low;	//�������� ������� ���������
						tx_frame[6] = tx_4slv.Smpl_F[2].byte.high;	//�������� ������� ���������
						tx_frame[7] = tx_4slv.CRC;
						
						tx_4slv.serv.bit.cell_indx++;
						if(tx_4slv.serv.bit.cell_indx >= NUMB_OF_CELLS) tx_4slv.serv.bit.cell_indx = 0;

						}//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
					//-----------------------------------------------------------------------

					//������������ �������� ��� ������ �������������------------------------------
					else
						{//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
						static	Uint16	param_cnt_slv = 0;		//������ ��������������� ���������� ��� ����� ����������
						static	Uint16	i_cell_cnt_slv = 0;		//���������� ��� ����� �����						

						//������������ ������� ��� ������ �������������:						
						tx_frame[0] = tx_4slv.serv.all;
						tx_frame[1] = slv_cell[i_cell_cnt_slv].word.cell_indx;	//�������� ����� ������ � ����
						tx_frame[2] = slv_cell[i_cell_cnt_slv].word.phase_indx;	//�������� ����� ����
						tx_frame[3] = param_cnt_slv;						//�������� ����� ���������
						tx_frame[4] = 0;								//�������� 0
						tx_frame[5] = 0;								//�������� 0
						tx_frame[6] = 0;								//�������� 0
						tx_frame[7] = tx_4slv.CRC;

						param_cnt_slv++;
						if(param_cnt_slv == nmb_of_askprm)
							{//---------------------------
							param_cnt_slv = 0;
							i_cell_cnt_slv++;
							if(i_cell_cnt_slv == NUMB_OF_CELLS * 3)	 {i_cell_cnt_slv = 0;}
							}//---------------------------	
						}//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
					//-----------------------------------------------------------------------
					
						{//��������� �������� ��� ������������ ------------------
						Uint16 i;
						ScicRegs.SCIFFTX.bit.TXFIFOXRESET = 0;	//�������� ��������� FIFO TX
						ScicRegs.SCIFFTX.bit.TXFIFOXRESET = 1;

						for(i=0;i < numb_mes;i++) 
							ScicRegs.SCITXBUF = tx_frame[i] & 0xFF;//�������� � ����� �������� ������� ���������
						}//------------------------------------------------------
					
						{//��������� ������� �� ����� ����� ������� �����
						Uint16 a;
						struct	STORE_DATA  *b;

						store_slv_indx[3]->serv.all = tx_frame[0];
						for(a=0;a < 6;a++)	 store_slv_indx[3]->data[a] = tx_frame[a+1];
						//����� ��������	
						b = store_slv_indx[0];
						store_slv_indx[0] =  store_slv_indx[3];
						store_slv_indx[3] =  store_slv_indx[2];
						store_slv_indx[2] =  store_slv_indx[1];
						store_slv_indx[1] =  b;
						}

					}//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


			if((sync_ok) & (MSmode == slave_mode))
				{//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
				Uint16 i;
				ScicRegs.SCIFFTX.bit.TXFIFOXRESET = 0;	//�������� ��������� FIFO TX
				ScicRegs.SCIFFTX.bit.TXFIFOXRESET = 1;

				for(i=0;i < retr_cell_mstr[9];i++) 
				ScicRegs.SCITXBUF = retr_cell_mstr[i] & 0xFF;//�������� � ����� �������� ������� ���������

				//------------------------
				ScibRegs.SCIFFTX.bit.TXFIFOXRESET = 0;	//�������� ��������� FIFO TX
				ScibRegs.SCIFFTX.bit.TXFIFOXRESET = 1;

				for(i=0;i < retr_mstr_cell[9];i++) 
					ScibRegs.SCITXBUF = retr_mstr_cell[i] & 0xFF;//�������� � ����� �������� ������� ���������

				sync_ok = 0;
				}//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			EPwm6Regs.ETCLR.bit.INT = 1;					//�������� ����
			PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
		} //SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//������� �������� ���������� �������������-------------------------------
void Cells_Check()
	{
	Uint16	tot_err = 0;
	Uint16	tot_slv_err = 0;

	if(MSmode != slave_mode)
		{//====================================================================
			{//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			Uint16 i;
			tot_cell_ready = 1;
			tot_sgnl_err = 0;

			for(i=0;i < NUMB_OF_CELLS * 3;i++)	//��������� �������� ������������� ���� �����
				{//----------------------------------
				tot_cell_ready &= cell[i].word.W1flags.bit.C_ready;	//���������� ����� ������� ���������� �����, ���� ��� ���
				tot_sgnl_err |= cell[i].word.sgnl_err;
				}//----------------------------------

			if(tot_cell_ready & (!tot_sgnl_err)) {tot_err = 0;}
			else 								 {tot_err = 1;} 									
			}//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		if(MSmode == master_mode)
			{//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		  		{//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				Uint16 i;
				tot_cell_ready_slv = 1;
				tot_sgnl_err_slv = 0;

				for(i=0;i < NUMB_OF_CELLS * 3;i++)	//��������� �������� ������������� ���� �����
					{//----------------------------------
					tot_cell_ready_slv &= slv_cell[i].word.W1flags.bit.C_ready;	//���������� ����� ������� ���������� �����, ���� ��� ���
					tot_sgnl_err_slv |= slv_cell[i].word.sgnl_err;
					}//----------------------------------

				if(tot_cell_ready_slv & (!tot_sgnl_err_slv))	{tot_slv_err = 0;}
				else											{tot_slv_err = 1;}
				}//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			}//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  	  //====================================================================
		if(tot_err)
			{//----------------------------------
			R_LED_on();
			G_LED_off();

				tx.serv.bit.mode = INIT_MODE; 
				tx_4slv.serv.bit.mode = INIT_MODE;
			}//----------------------------------
		else
			{//----------------------------------
			if((tot_slv_err) & (MSmode == master_mode))
				{//--------------------
				R_LED_on();

				if(Prmt_Work == on)	{G_LED_on();}
				else  				{G_LED_off();}

				tx.serv.bit.mode = INIT_MODE; 
				tx_4slv.serv.bit.mode = INIT_MODE;
				}//--------------------
			else
				{//--------------------
				R_LED_off();

				if(Prmt_Work == on)
					{
					tx.serv.bit.mode = tx_4slv.serv.bit.mode = WORK_MODE;
					G_LED_on(); 
					}
				else 
					{
					tx.serv.bit.mode = tx_4slv.serv.bit.mode = INIT_MODE;
					G_LED_off(); 					
					}
				}//-------------------- 
			}//----------------------------------

		}//====================================================================
	else
		{//====================================================================
		R_LED_off();
		G_LED_off(); 
		}//====================================================================	
	}
//------------------------------------------------------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//������� ������������� ������ ����� � ��������------------------------------
void Init_Data()
{
Uint16	i, a;
Uint16	n = &cell[0].word.cell_indx - &cell[0].all[0];	//���������� ���������� ���������� ��� ���������

	for(a = 0;a < 3;a++)		//���� ���
		{
		for(i=0;i < NUMB_OF_CELLS;i++)		//���� �����
			{
			Uint16	j, k = NUMB_OF_CELLS * a + i;

			for(j=0;j < n;j++) cell[k].all[j] = 0;		//��������� ������ ����� �������
			cell[k].word.cell_indx	= i;				//���������� ����� ������ � ����
			cell[k].word.phase_indx = a;				//���������� ����� ����
			cell[k].word.init_done = 0;					//�������� ������� ������ ������������� ������
			cell[k].word.sgnl_err = 0;					//�������� ������� ������ ����� � �������
			}
		}
	for(a = 0;a < 3;a++)		//���� ���
		{
		for(i=0;i < NUMB_OF_CELLS;i++)		//���� �����
			{
			Uint16	j, k = NUMB_OF_CELLS * a + i;

			for(j=0;j < n;j++) slv_cell[k].all[j] = 0;		//��������� ������ ����� �������
			slv_cell[k].word.cell_indx	= i;				//���������� ����� ������ � ����
			slv_cell[k].word.phase_indx = a;				//���������� ����� ����
			slv_cell[k].word.init_done = 0;					//�������� ������� ������ ������������� ������
			slv_cell[k].word.sgnl_err = 0;					//�������� ������� ������ ����� � �������
			}
		}
	//������������ ������� ������ ������������ ���������� ��� ��������� �������������
	nmb_of_askprm =	tot_nmb_of_askprm;
	for(i=0;i<nmb_of_askprm;i++) par_nmb_list[i] = i;
//	reset_init_on = 1;				//���������� ������� ��������� �������������

	//������������� ������ ��� ��������-----------
	{		//������� ������ ��� ��������
	Uint16* p = &tx.serv.all;
	Uint16 i;
	for(i=0;i<8;i++) *(p + i) = 0;
	
	p = &tx_4slv.serv.all;
	for(i=0;i<8;i++) *(p + i) = 0;
	}//-------------------------------------------

	tx.serv.bit.mode = INIT_MODE;					//���������� �����
	tx.serv.bit.cell_indx = 0;							//���������� �������� ������ �����
	tx.Smpl_F[0].all = tx.Smpl_F[1].all = tx.Smpl_F[2].all = mid_lvl; //��������� ������� ������� �������

	tx_4slv.serv.bit.mode = INIT_MODE;					//���������� �����
	tx_4slv.serv.bit.cell_indx = 0;							//���������� �������� ������ �����
	tx_4slv.Smpl_F[0].all = tx_4slv.Smpl_F[1].all = tx_4slv.Smpl_F[2].all = mid_lvl; //��������� ������� ������� �������

	//������������� ������---------------------------
	{		//������� ������
	Uint16* p = &store[0].serv.all;
	Uint16 i;
	for(i=0;i<8*3;i++) *(p + i) = 0;
	p = &store_slv[0].serv.all;
	for(i=0;i<8*4;i++) *(p + i) = 0;
	}//-----------------------------------------------

	EALLOW;  // This is needed to write to EALLOW protected registers
		GpioIntRegs.GPIOXNMISEL.bit.GPIOSEL = 28;			//������� ���� 28 � ������� �����������
		XIntruptRegs.XNMICR.bit.POLARITY = 0;				//������� ���������� NMINT �� ��������� ������ �������
		XIntruptRegs.XNMICR.bit.ENABLE = 0;					//
		XIntruptRegs.XNMICR.bit.SELECT = 1;					//������� ���������� int13
	EDIS;    // This is needed to disable write to EALLOW protected registers

	SciaRegs.SCICTL1.bit.RXENA	= 0;	//��������� ��������  RS485_2  (�)
	ScicRegs.SCICTL1.bit.RXENA	= 0;	//��������� ��������  RS485_1  (c)
	XIntruptRegs.XNMICR.bit.ENABLE = 0;	//��������� ���������� �����
	MSmode = sngl_mode;

	Exp1_regs.GPout.all = 0xFFFFFFFF;
	Exp2_regs.GPout.all = 0xFFFFFFFF;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//������� ��������� spi ��������
void Stup_SPI_exch(Uint16 dev_sel)
	{
	//���������� ���������� 
	if(spi_store.spi_dev == ADC1_dev_SEL) {AD7732_1.adc1 = (spi_store.data[2] & 0xFF) + (spi_store.data[1] * 0x100);}

	if(spi_store.spi_dev == ADC2_dev_SEL) {AD7732_2.adc1 = (spi_store.data[2] & 0xFF) + (spi_store.data[1] * 0x100);}

	if(spi_store.spi_dev == EXP1_dev_SEL) {Exp1_regs.GPin.byte.GP4_11 = spi_store.data[1] & 0xFF;
										   Exp1_regs.GPin.byte.GP12_19 = spi_store.data[2] & 0xFF;}
										   
	if(spi_store.spi_dev == EXP2_dev_SEL) {Exp2_regs.GPin.byte.GP4_11 = spi_store.data[1] & 0xFF;
										   Exp2_regs.GPin.byte.GP12_19 = spi_store.data[2] & 0xFF;}
	//��������� SPI
	if((dev_sel == ADC1_dev_SEL) || (dev_sel == ADC2_dev_SEL))
		{
		SpiaRegs.SPICCR.bit.SPICHAR = 0x7;			//�������� ����� �� 8 ���
		SpiaRegs.SPICCR.bit.CLKPOLARITY = 1;		//������ ������ �� ����� �� ���������� ������
		SpiaRegs.SPICTL.bit.CLK_PHASE = 0;			//��������� �������� ������� clk
		SpiaRegs.SPIBRR = 74;						//���������� ������� LSPCLK/(74+1) (1 ���) 

		spi_store.spi_dev = dev_sel;
		spi_store.remn_nmb_byte = 3;
		spi_store.nmb_byte = 3;
		spi_store.data[0] = (R_ad7732 + Ch1_Data_adr) * 0x100;
		spi_store.data[1] = 0;
		spi_store.data[2] = 0;
		}
	if((dev_sel == EXP1_dev_SEL) || (dev_sel == EXP2_dev_SEL))
		{ 
		SpiaRegs.SPICCR.bit.SPICHAR = 0xF;			//�������� ����� �� 16 ���
		SpiaRegs.SPICCR.bit.CLKPOLARITY = 0;		//������ ������ �� ����� �� ������������ ������
		SpiaRegs.SPICTL.bit.CLK_PHASE = 1;			//�������� �������� ������� clk
		SpiaRegs.SPIBRR = 9;						//���������� ������� LSPCLK/(9+1) (7.5 ���) 

		spi_store.spi_dev = dev_sel;
		spi_store.remn_nmb_byte = 4;
		spi_store.nmb_byte = 4;
		spi_store.data[0] = MX7301_R_code + adr_GP4_11;
		spi_store.data[1] = MX7301_R_code + adr_GP12_19;
		spi_store.data[2] = MX7301_W_code + adr_GP12_19 + Exp1_regs.GPout.byte.GP12_19;
		spi_store.data[3] = MX7301_W_code + adr_GP20_27 + Exp1_regs.GPout.byte.GP20_27;
		}
		{Uint16 i;
		for(i=0;i<50;i++) {};}
	}
//---------------------------------------------------------------------------
//--------------------------------------------------------------------------- 



//������� ��������� �������� ������ �� SCI. ��������� � ������� ���������� �� ������
void Get_RX_SCI(volatile struct SCI_REGS *ScixRegs, Uint16 RXmode, struct TX_FRAME *txd, union	CELL_DATA_UNION	_cell[], struct STORE_DATA *st_pnt[])
	{//########################################################################################

	static struct	SCIRX_DATA	RXd_frm_clls;		//��������������� ������ ��������
	static struct	SCIRX_DATA	RXd_frm_slv;		//��������������� ������ ��������
	struct			SCIRX_DATA	*RXdat;			//���������

	if(RXmode == RX_FROM_SLAVE) RXdat = &RXd_frm_slv;
	else				   		RXdat = &RXd_frm_clls;

		//------------------------------------------------------------------------------------
		if(ScixRegs->SCIRXST.bit.RXERROR)				//���� ������, ��:
			{//-----------------------------------------------------------------------
			ScixRegs->SCICTL1.bit.RXENA	=	0;			//��������� ��������

			txd->serv.bit.mode = INIT_MODE;		//���������� ����� �������������
			//���������� ������� ������ ����� � ����������� �������				
			_cell[st_pnt[1]->data[1] * NUMB_OF_CELLS + st_pnt[1]->data[0]].word.sgnl_err = 1;
			}//----------------------------------------------------------------------

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		else //���� ������ ���, ��:
			{//====================================================================
			for(;ScixRegs->SCIFFRX.bit.RXFFST;)
				{//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
				RXdat->new_datain[RXdat->numb_frames] = ScixRegs->SCIRXBUF.all & 0xFF;		//��������� ���� ���������
				RXdat->numb_frames++;		
				}//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

			if(st_pnt[1]->serv.bit.mode)				//���� ��� ���������� ������� �����, ��
				{//****************************************************************
				if(RXdat->numb_frames == 9)//���� ���������� �������� ������ �����, ��:
					{//"""""""""""""""""""""""""""""""""""""""""""""""""
					Uint16	n, i;

					for(i=0;i<3;i++)
						{//���������� ����� ������ � ���������������
						n = ((RXdat->new_datain[i*3] & 0x30) / 0x10) * NUMB_OF_CELLS + (RXdat->new_datain[i*3] & 0xF);

						_cell[n].word.An_Val.named.UDC = new_datain[i*3+1];				//��������� �������� ������������� ����������
						_cell[n].word.W1flags.bit.C_ready = new_datain[i*3] / 0x80;			//��������� ���� ���������� � ������
						_cell[n].word.W1flags.bit.protect_C = new_datain[i*3+2] / 0x80;		//��������� ���� ������������ ������
						_cell[n].word.W1flags.bit.pre_protect_C = (new_datain[i*3+2] & 0x40) / 0x40; //��������� ���� ��������������
						}
					}//"""""""""""""""""""""""""""""""""""""""""""""""""

				else //���� ���������� �������� ������ �� �����, ��:
					{//"""""""""""""""""""""""""""""""""""""""""""""""""
					err_frames++;						//��������� ������� ������
					txd->serv.bit.mode = INIT_MODE;		//���������� ����� �������������
					//���������� ������� ������ ����� � ����������� �������				
					_cell[st_pnt[1]->data[1] * NUMB_OF_CELLS + st_pnt[1]->data[0]].word.sgnl_err = 1;
					}//"""""""""""""""""""""""""""""""""""""""""""""""""			
				}//*****************************************************************
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

			else //���� ���������� ����� �������������
				{//*****************************************************************
				if(RXdat->numb_frames == 5)		//���� ���������� �������� ������ �����, ��:
					{//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
					if(RXdat->new_datain[0] & 0x80)		//���� ��� ���� �������� ���������� 
						{							//(������ ����� � ���������� ������� ���������), ��
						//���� �� ����������
						}

					else							//���� ������ ����� �� ������ ���������, ��
						{//------------------------------------------------
						RXdat->Nc_resp =  RXdat->new_datain[4] * NUMB_OF_CELLS + RXdat->new_datain[3]; 		//���������� ����� ������ �� ���������
						RXdat->Nc_req = st_pnt[1]->data[1] * NUMB_OF_CELLS + st_pnt[1]->data[0];	//���������� � ������ �� ������
						RXdat->Np_resp =  RXdat->new_datain[0] & 0x3F;								//���������� � ��������� �� ���������																	//������� 
						RXdat->Np_req = st_pnt[1]->data[2];								//���������� � ��������� �� ������

						if((RXdat->Nc_resp != RXdat->Nc_req)||(RXdat->Np_resp != RXdat->Np_req))	//���� ����� ������ ��� ����� ��������� � ������� 
							{											//�� ��������� � ��������, ��
							RXdat->p_cnt = 0;
							_cell[RXdat->Nc_req].word.sgnl_err = 1;	 //���������� ������� ������ ����� � �������
							}								 
						else	//���� �������� ������ ������� � ������ ���������, ��
							{//��������� �������� �������� ����������
							_cell[RXdat->Nc_resp].all[RXdat->Np_resp] = RXdat->new_datain[2] * 0x100 + RXdat->new_datain[1]; 
							RXdat->p_cnt++;
							if(RXdat->Np_resp == nmb_of_askprm - 1) // ���� ����� ���������� ���������
								{
								//���� ������� ���������� ����� ������������� ��������, �������� ������� ������										
								if(RXdat->p_cnt == nmb_of_askprm)	   
									{
								 	_cell[RXdat->Nc_req].word.sgnl_err = 0;	 //�������� ������� ������ ����� � �������
									}
								RXdat->p_cnt = 0;				   				//�������� ������� ����������
							}	}	
						}//----------------------------------------------------	
					}//"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

				else ////���� ���������� �������� ������ �� �����, ��:
					{//"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
					err_frames++;						//��������� ������� ������	
					txd->serv.bit.mode = INIT_MODE;		//���������� ����� �������������

					//���������� ������� ������ ����� � �������				
					_cell[st_pnt[1]->data[1] * NUMB_OF_CELLS + st_pnt[1]->data[0]].word.sgnl_err = 1;
					}//"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""					
				}//*****************************************************************
			}//====================================================================
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		RXdat->numb_frames = 0;							//�������� ������� ���������

		ScixRegs->SCICTL1.bit.SWRESET = 0;			//�������� �����
		ScixRegs->SCICTL1.bit.SWRESET = 1;
		ScixRegs->SCIFFRX.bit.RXFIFORESET = 0;		//�������� ��������� FIFO RX	
		ScixRegs->SCIFFRX.bit.RXFIFORESET = 1;
		ScixRegs->SCICTL1.bit.RXENA	=	1;			//�������� ��������
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	}//########################################################################################





