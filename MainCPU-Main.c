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

//объявления функций--------------------------------------
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
//	Инициализация контроллера
	
	InitSysCtrl();
//	Отключение прерываний 
	DINT;
	InitPieCtrl();
//	Отключение прерываний и сброс флагов
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();
   	
	InitFlash();	
		 
//	Переименование функций обработки прерываний
	EALLOW;  // This is needed to write to EALLOW protected registers
//	PieVectTable.TINT0 = &cpu_timer0_isr;		//прерывание от таймера 0
	PieVectTable.XINT13 = &cpu_int13_isr;		//прерывание от int13
//	PieVectTable.TINT2 = &cpu_timer2_isr;		//прерывание от таймера 2
//	PieVectTable.SCIRXINTB = &scib_rx_isr;		//перрывание от SCIB
//	PieVectTable.SCIRXINTC = &scic_rx_isr;		//перрывание от SCIC
	PieVectTable.EPWM4_INT = &epwm4_timer_isr;	//прерывание от pwm4
	PieVectTable.EPWM6_INT = &epwm6_timer_isr;	//прерывание от pwm5
	EDIS;    // This is needed to disable write to EALLOW protected registers

//	Инициализация модулей
	InitCpuTimers();							// инициализировать Таймеры CPU

	InitSCIA();									//инициализировать SCIA	
	InitSCIB();									//инициализировать SCIB	
	InitSCIC();									//инициализировать SCIC
	InitSPIA();									//инициализировать SPIA

	P33V_ON();			//включить питание логики
		{//задержка после подачи питания____________
		Uint16 a;
		for(a = 0; a < 0xFFFF; a++) {};					
		}//_________________________________________

	InitMAX7301(EXP1_dev_SEL);
	InitMAX7301(EXP2_dev_SEL);
	InitAD7732(ADC1_dev_SEL);
	InitAD7732(ADC2_dev_SEL);

		//запуск обмена с SPI...............................
		spi_store.spi_dev = 0;
		Stup_SPI_exch(ADC1_dev_SEL);
		GpioDataRegs.GPACLEAR.all = spi_store.spi_dev;	//активировать выбранное устройство
		//выгрузить для передачи
		SpiaRegs.SPITXBUF = spi_store.data[spi_store.nmb_byte - spi_store.remn_nmb_byte];					
		spi_store.remn_nmb_byte--;							//уменьшить счетчик на 1
		//..................................................

//настройка модулей EPWM1 и EPWM2 для установки синхроимпульса запуска процесса передачи
	InitEPwm_4_6Timers(trans_per, trans_sync_lenth, trans_start);

	//Init_Data();

// Configure CPU-Timers:
//	ConfigCpuTimer(&CpuTimer0Regs, Prd0, 1);		//настроить таймер0 включить прерывание
	ConfigCpuTimer(&CpuTimer1Regs, Prd1, 0);		//настроить таймер1 выключить прерывание
	ConfigCpuTimer(&CpuTimer2Regs, Prd2, 0);		//настроить таймер1 выключить прерывание

// Enable CPU interrapts:
//	IER |= M_INT1;		//CPU int1 is connected to CPU-Timer 0
	IER |= M_INT3;		//CPU int3 is connected to epwm
	IER	|= M_INT8;		//CPU int8 is connected to SCIC
	IER	|= M_INT9;		//CPU int9 is connected to SCIA/B
	IER |= M_INT13;		//CPU int13 
//	IER |= M_INT14;		//CPU int14 is connected to CPU-Timer 2

//	CpuTimer0Regs.TCR.all = 0x4001;			// запустить таймер 0 (TSS bit = 0)
	CpuTimer1Regs.TCR.all = 0x4001;			// запустить таймер 1
	CpuTimer2Regs.TCR.all = 0x4001;			// запустить таймер 2

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
//проверка проведенной начальной инициализации


	Cells_Check(); 


//*****************************************************************************************************
// Step 6. основной цикл:
	for(;;)
		{//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			{//обмен данными с SPI устройствами  ++++++++++++++++++++++++++++++++++++++++++++++++
			static Uint16 a = 0;
			static Uint16 b = 0;
			static Uint16 c = 0;

			if(SpiaRegs.SPISTS.bit.INT_FLAG)	//если флаг завершения передачи установлен
				{//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
				Deact_SPI_dev();			//отключить все устройства SPI

				{Uint16 i;
				for(i=0;i<5;i++) {};}		//задержка 

				//сохранить принятое сообщение		
				spi_store.data[spi_store.nmb_byte - (spi_store.remn_nmb_byte + 1)] = SpiaRegs.SPIRXBUF;

				if(!spi_store.remn_nmb_byte)			//если передан последний байт, то
					{//------------------------------------------------
					if(c & CpuTimer1Regs.TCR.bit.TIF)  		//проверить разрешение чрения ADC
				 		{
				  		if(a) {Stup_SPI_exch(ADC1_dev_SEL);}
						else  {Stup_SPI_exch(ADC2_dev_SEL);}
						a ^=1;										//инвертировать флаг очередности чтения ADC
						c ^=1;
				 		CpuTimer1Regs.TCR.bit.TIF = 1;      		//сбросить флаг
						}
					else
						{
						if(b) {Stup_SPI_exch(EXP1_dev_SEL);}
						else  {Stup_SPI_exch(EXP2_dev_SEL);}
						b ^=1;										//инвертировать флаг очередности чтения EXP
						c ^=1;
						}
					}//------------------------------------------------

				GpioDataRegs.GPACLEAR.all = spi_store.spi_dev;	//активировать выбранное устройство
				//выгрузить для передачи
				SpiaRegs.SPITXBUF = spi_store.data[spi_store.nmb_byte - spi_store.remn_nmb_byte];					
				spi_store.remn_nmb_byte--;							//уменьшить счетчик на 1

				}//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			}//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//проверка задания двойной работы------------------------------------------
		if(S_D_MODE == SINGLE_MODE) 
			{//включен режим одиночной работы^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			if(MSmode != sngl_mode)			//если смена режима, то
				{//-----------------------------------------
				SciaRegs.SCICTL1.bit.RXENA	= 0;	//выключить приемник  RS485_2  (а)
				ScicRegs.SCICTL1.bit.RXENA	= 0;	//выключить приемник  RS485_1  (c)

				XIntruptRegs.XNMICR.bit.ENABLE = 0;	//отключить прерывание порта

				MSmode = sngl_mode;
				}//-----------------------------------------
			}//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		else //if S_D_MODE == DOUBLE_MODE
			{//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  
			SciaRegs.SCICTL1.bit.RXENA	= 0;	//выключить приемник  SCIа  (а)
			ScicRegs.SCICTL1.bit.RXENA	= 1;	//включить приемник  SCIc  (c)

			DE1_RS485_dsbl();					//выключить передатчик RS485_1
			DE2_RS485_dsbl();					//выключить передатчик RS485_2

			if	(M_S_MODE == MASTER_MODE)
				{//режим парной работы, ведущий>>>>>>>>>>>>>>>>>>>		  */
				if(MSmode != master_mode) //если смена режима, то
					{//-----------------------------------------
					EALLOW;  // This is needed to write to EALLOW protected registers
						GpioCtrlRegs.GPBMUX1.bit.GPIO35  = 	0; 	// 0=GPIO,  1=SCIA-TX,  2=Resv,  3=Resv
						XIntruptRegs.XNMICR.bit.ENABLE = 0;					//
					EDIS;    // This is needed to disable write to EALLOW protected registers
					MSmode = master_mode;
					}//-----------------------------------------
				}//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			else //if M_S_MODE == SLAVE_MODE	
				{//режим парной работы, ведомый>>>>>>>>>>>>>>>>>>>
				if(MSmode != slave_mode)  //если смена режима, то
					{//-----------------------------------------
					EALLOW;  // This is needed to write to EALLOW protected registers
						GpioCtrlRegs.GPBMUX1.bit.GPIO35  = 	1; 	// 0=GPIO,  1=SCIA-TX,  2=Resv,  3=Resv
						XIntruptRegs.XNMICR.bit.ENABLE = 1;		//разрешить прерывание от порта
					EDIS;    // This is needed to disable write to EALLOW protected registers

					MSmode = slave_mode;
					}//-----------------------------------------
				}//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			}//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		if(ON_OFF) Prmt_Work = off;			//запретить работу
		else 	   Prmt_Work = on;			//разрешить работу

		Cells_Check();

		}//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//*****************************************************************************************************
} 	
//========================================================================

//-------------------------------------------------------------------------------------/
//-------------------------------------------------------------------------------------/
	//эта функция обрабатывает внешнее прерывание 1 по сбросу лог уровня на выводе sync_in--
	interrupt void cpu_int13_isr(void)
		{
		EPwm4Regs.TBCTL.bit.SWFSYNC = 1;
		sync_ok = 1;
		}

//-------------------------------------------------------------------------------------/
//-------------------------------------------------------------------------------------/

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
	//функция по прерыванию от таймера PWM4-----------------------------------
	//проверка приема SCI, проверка целостности принятого фрейма
	interrupt void epwm4_timer_isr(void) 
		{ //SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
		if(MSmode == master_mode)
			{//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			Drp_sync_4slv(); 		//сбросить сигнал синхронизации для ведомого

			Get_RX_SCI(&ScicRegs, RX_FROM_SLAVE, &tx_4slv, slv_cell, store_slv_indx);

			Set_sync_4slv();		//установить сигнал синхронизации для ведомого
			}//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		if((sync_ok) & (MSmode == slave_mode))
			{//--------------------------------------------------------------------------

			//ОБРАБОТКА ПРИЕМА ПО ЛИНИИ SCIC~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			retr_mstr_cell[9]=0;				//сбросить счетчик ретранслируемых байтов
			if(ScicRegs.SCIRXST.bit.RXERROR)				//если ошибка, то:
				{//-----------------------------------------------------------------------
				ScicRegs.SCICTL1.bit.RXENA	=	0;			//выключить приемник

				ScicRegs.SCICTL1.bit.SWRESET = 0;			//сбросить флаги
				ScicRegs.SCICTL1.bit.SWRESET = 1;
				ScicRegs.SCIFFRX.bit.RXFIFORESET = 0;		//сбросить указатель FIFO RX	
				ScicRegs.SCIFFRX.bit.RXFIFORESET = 1;
				}//----------------------------------------------------------------------

			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			else //если ошибок нет, то:
				{//====================================================================
				for(;ScicRegs.SCIFFRX.bit.RXFFST;)
					{//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
					retr_mstr_cell[retr_mstr_cell[9]] = ScicRegs.SCIRXBUF.all & 0xFF;		//сохранить байт сообщения
					retr_mstr_cell[9]++;		
					}//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
				}//====================================================================

			ScicRegs.SCICTL1.bit.RXENA	=	1;			//включить приемник
			//Конец ОБРАБОТКи ПРИЕМА ПО ЛИНИИ SCIC~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			//ОБРАБОТКА ПРИЕМА ПО ЛИНИИ SCIB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			retr_cell_mstr[9]=0;				//сбросить счетчик ретранслируемых байтов
			if(ScibRegs.SCIRXST.bit.RXERROR)				//если ошибка, то:
				{//-----------------------------------------------------------------------
				ScibRegs.SCICTL1.bit.RXENA	=	0;			//выключить приемник

				ScibRegs.SCICTL1.bit.SWRESET = 0;			//сбросить флаги
				ScibRegs.SCICTL1.bit.SWRESET = 1;
				ScibRegs.SCIFFRX.bit.RXFIFORESET = 0;		//сбросить указатель FIFO RX	
				ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;
				}//----------------------------------------------------------------------

			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			else //если ошибок нет, то:
				{//====================================================================
				for(;ScibRegs.SCIFFRX.bit.RXFFST;)
					{//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
					retr_cell_mstr[retr_cell_mstr[9]] = ScibRegs.SCIRXBUF.all & 0xFF;		//сохранить байт сообщения
					retr_cell_mstr[9]++;		
					}//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
				}//====================================================================
			ScibRegs.SCICTL1.bit.RXENA	=	1;			//включить приемник
	 		//Конец ОБРАБОТКи ПРИЕМА ПО ЛИНИИ SCIB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			}//-------------------------------------------------------------------------- 
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




		if(MSmode != slave_mode)		
			{//ОБРАБОТКА ПРИЕМА ПО ЛИНИИ SCIB+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			Get_RX_SCI(&ScibRegs, RX_FROM_CELLS, &tx, cell, store_indx);
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

			
			//определение отсчета функции синуса
			if(CpuTimer2Regs.TCR.bit.TIF)
				{//-------------------------------------------------------
				Uint16 i;
				//функция обновления текущего отсчета
				//сигнала задания
				//-------------------------------------------------------
				CurNum_Smpl[0]++;			//инкрементировать значение номера текущего отсчета
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

					tx_4slv.Smpl_F[i].all = tx.Smpl_F[i].all;		//сохранить значение для ведомого
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
				CpuTimer2Regs.TCR.bit.TIF = 1;		//сбросить флаг
				}//-------------------------------------------------------
			}//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						 
		EPwm4Regs.ETCLR.bit.INT = 1;				//очистить флаг
		PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
		}//SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
	//функция по прерыванию от таймера PWM6-----------------------------------
	//запускает передачу данных	каждые 55,52 мкс
	interrupt void epwm6_timer_isr(void)
		{//SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
		static	Uint16 frame_cnt = 0;		//переменная для счета посылок
		
		//---------------------------------------------------------------------------
			frame_cnt++;							//инкрементировать счетчик сообщений
			if(frame_cnt == 30)						//если счет достиг нужного значения,
				{tx.serv.bit.saw_sync = 1;			//установить бит синхронизации базовой пилы
				 frame_cnt = 0;}						//обнулить счетчик
			else 
				{tx.serv.bit.saw_sync = 0;}			//сбросить бит синхронизации базовой пилы
			if(frame_cnt == 29)						//если счет достиг нужного значения,
				{tx_4slv.serv.bit.saw_sync = 1;}			//установить бит синхронизации базовой пилы
			else 
				{tx_4slv.serv.bit.saw_sync = 0;}
		//---------------------------------------------------------------------------


			if(MSmode != slave_mode)	
				{//===========================================================================================================
				//формирование передачи для рабочего режима------------------------------
				if(tx.serv.bit.mode)		//если установлен рабочий режим, то
					{//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
								tx.Smpl_F[0].all = store_Smpl_F[0];
								tx.Smpl_F[1].all = store_Smpl_F[1];
								tx.Smpl_F[2].all = store_Smpl_F[2];

					//сформировать посылку для рабочего режима:
					tx_frame[0] = tx.serv.all;
					tx_frame[1] = tx.Smpl_F[0].byte.low;	//записать младшее полуслово
					tx_frame[2] = tx.Smpl_F[0].byte.high;	//записать старшее полуслово
					tx_frame[3] = tx.Smpl_F[1].byte.low;	//записать младшее полуслово
					tx_frame[4] = tx.Smpl_F[1].byte.high;	//записать старшее полуслово
					tx_frame[5] = tx.Smpl_F[2].byte.low;	//записать младшее полуслово
					tx_frame[6] = tx.Smpl_F[2].byte.high;	//записать старшее полуслово
					tx_frame[7] = tx.CRC;
					
					tx.serv.bit.cell_indx++;
					if(tx.serv.bit.cell_indx >= NUMB_OF_CELLS) tx.serv.bit.cell_indx = 0;

					}//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

				//формирование передачи для режима инициализации------------------------------
				else
					{//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
					static	Uint16	param_cnt = 0;		//ввести вспомогательную переменную для счета параметров
					static	Uint16	i_cell_cnt = 0;		//переменная для счета ячеек						
									
					//сформировать посылку для режима инициализации:						
					tx_frame[0] = tx.serv.all;
					tx_frame[1] = cell[i_cell_cnt].word.cell_indx;	//записать номер ячейки в фазе
					tx_frame[2] = cell[i_cell_cnt].word.phase_indx;	//записать номер фазы
					tx_frame[3] = param_cnt;						//записать номер параметра
					tx_frame[4] = 0;								//записать 0
					tx_frame[5] = 0;								//записать 0
					tx_frame[6] = 0;								//записать 0
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
				
					{//запустить передачу -----------------------------
					Uint16 i;
					ScibRegs.SCIFFTX.bit.TXFIFOXRESET = 0;	//сбросить указатель FIFO TX
					ScibRegs.SCIFFTX.bit.TXFIFOXRESET = 1;

					for(i=0;i < numb_mes;i++) 
						ScibRegs.SCITXBUF = tx_frame[i] & 0xFF;//записать в буфер отбросив старшее полуслово
					}//------------------------------------------------
					
					{//сохранить посылку на место более старого банка--
					Uint16 a;
					struct	STORE_DATA  *b;

					store_indx[1]->serv.all = tx_frame[0];
					for(a=0;a < 6;a++)	 store_indx[1]->data[a] = tx_frame[a+1];
					//сдвиг индексов	
					b = store_indx[0];
					store_indx[0] = store_indx[1];
					store_indx[1] =  b;
					}//------------------------------------------------
				}//===========================================================================================================


				if(MSmode == master_mode)
					{//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
					//формирование передачи для рабочего режима------------------------------
					if(tx_4slv.serv.bit.mode)		//если установлен рабочий режим, то
						{//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
								store_Smpl_F[0] = tx_4slv.Smpl_F[0].all = Smpl_F[0];
								store_Smpl_F[1] = tx_4slv.Smpl_F[1].all = Smpl_F[1];
								store_Smpl_F[2] = tx_4slv.Smpl_F[2].all = Smpl_F[2];


						//сформировать посылку для рабочего режима:
						tx_frame[0] = tx_4slv.serv.all;
						tx_frame[1] = tx_4slv.Smpl_F[0].byte.low;	//записать младшее полуслово
						tx_frame[2] = tx_4slv.Smpl_F[0].byte.high;	//записать старшее полуслово
						tx_frame[3] = tx_4slv.Smpl_F[1].byte.low;	//записать младшее полуслово
						tx_frame[4] = tx_4slv.Smpl_F[1].byte.high;	//записать старшее полуслово
						tx_frame[5] = tx_4slv.Smpl_F[2].byte.low;	//записать младшее полуслово
						tx_frame[6] = tx_4slv.Smpl_F[2].byte.high;	//записать старшее полуслово
						tx_frame[7] = tx_4slv.CRC;
						
						tx_4slv.serv.bit.cell_indx++;
						if(tx_4slv.serv.bit.cell_indx >= NUMB_OF_CELLS) tx_4slv.serv.bit.cell_indx = 0;

						}//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
					//-----------------------------------------------------------------------

					//формирование передачи для режима инициализации------------------------------
					else
						{//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
						static	Uint16	param_cnt_slv = 0;		//ввести вспомогательную переменную для счета параметров
						static	Uint16	i_cell_cnt_slv = 0;		//переменная для счета ячеек						

						//сформировать посылку для режима инициализации:						
						tx_frame[0] = tx_4slv.serv.all;
						tx_frame[1] = slv_cell[i_cell_cnt_slv].word.cell_indx;	//записать номер ячейки в фазе
						tx_frame[2] = slv_cell[i_cell_cnt_slv].word.phase_indx;	//записать номер фазы
						tx_frame[3] = param_cnt_slv;						//записать номер параметра
						tx_frame[4] = 0;								//записать 0
						tx_frame[5] = 0;								//записать 0
						tx_frame[6] = 0;								//записать 0
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
					
						{//запустить передачу для подчиненного ------------------
						Uint16 i;
						ScicRegs.SCIFFTX.bit.TXFIFOXRESET = 0;	//сбросить указатель FIFO TX
						ScicRegs.SCIFFTX.bit.TXFIFOXRESET = 1;

						for(i=0;i < numb_mes;i++) 
							ScicRegs.SCITXBUF = tx_frame[i] & 0xFF;//записать в буфер отбросив старшее полуслово
						}//------------------------------------------------------
					
						{//сохранить посылку на место более старого банка
						Uint16 a;
						struct	STORE_DATA  *b;

						store_slv_indx[3]->serv.all = tx_frame[0];
						for(a=0;a < 6;a++)	 store_slv_indx[3]->data[a] = tx_frame[a+1];
						//сдвиг индексов	
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
				ScicRegs.SCIFFTX.bit.TXFIFOXRESET = 0;	//сбросить указатель FIFO TX
				ScicRegs.SCIFFTX.bit.TXFIFOXRESET = 1;

				for(i=0;i < retr_cell_mstr[9];i++) 
				ScicRegs.SCITXBUF = retr_cell_mstr[i] & 0xFF;//записать в буфер отбросив старшее полуслово

				//------------------------
				ScibRegs.SCIFFTX.bit.TXFIFOXRESET = 0;	//сбросить указатель FIFO TX
				ScibRegs.SCIFFTX.bit.TXFIFOXRESET = 1;

				for(i=0;i < retr_mstr_cell[9];i++) 
					ScibRegs.SCITXBUF = retr_mstr_cell[i] & 0xFF;//записать в буфер отбросив старшее полуслово

				sync_ok = 0;
				}//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			EPwm6Regs.ETCLR.bit.INT = 1;					//очистить флаг
			PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
		} //SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//функция проверки завершения инициализации-------------------------------
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

			for(i=0;i < NUMB_OF_CELLS * 3;i++)	//проверить признаки инициализации всех ячеек
				{//----------------------------------
				tot_cell_ready &= cell[i].word.W1flags.bit.C_ready;	//установить общий признак готовности ячеек, если все гот
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

				for(i=0;i < NUMB_OF_CELLS * 3;i++)	//проверить признаки инициализации всех ячеек
					{//----------------------------------
					tot_cell_ready_slv &= slv_cell[i].word.W1flags.bit.C_ready;	//установить общий признак готовности ячеек, если все гот
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
//функция инициализации данных ячеек и передачи------------------------------
void Init_Data()
{
Uint16	i, a;
Uint16	n = &cell[0].word.cell_indx - &cell[0].all[0];	//определить количество параметров для обнуления

	for(a = 0;a < 3;a++)		//счет фаз
		{
		for(i=0;i < NUMB_OF_CELLS;i++)		//счет ячеек
			{
			Uint16	j, k = NUMB_OF_CELLS * a + i;

			for(j=0;j < n;j++) cell[k].all[j] = 0;		//обнуление данных кроме номеров
			cell[k].word.cell_indx	= i;				//определить номер ячейки в фазе
			cell[k].word.phase_indx = a;				//определить номер фазы
			cell[k].word.init_done = 0;					//обнулить признак ошибки инициализации ячейки
			cell[k].word.sgnl_err = 0;					//сбросить признак ошибки связи с ячейкой
			}
		}
	for(a = 0;a < 3;a++)		//счет фаз
		{
		for(i=0;i < NUMB_OF_CELLS;i++)		//счет ячеек
			{
			Uint16	j, k = NUMB_OF_CELLS * a + i;

			for(j=0;j < n;j++) slv_cell[k].all[j] = 0;		//обнуление данных кроме номеров
			slv_cell[k].word.cell_indx	= i;				//определить номер ячейки в фазе
			slv_cell[k].word.phase_indx = a;				//определить номер фазы
			slv_cell[k].word.init_done = 0;					//обнулить признак ошибки инициализации ячейки
			slv_cell[k].word.sgnl_err = 0;					//сбросить признак ошибки связи с ячейкой
			}
		}
	//формирование полного списка передаваемых параметров для стартовой инициализации
	nmb_of_askprm =	tot_nmb_of_askprm;
	for(i=0;i<nmb_of_askprm;i++) par_nmb_list[i] = i;
//	reset_init_on = 1;				//установить признак начальной инициализации

	//инициализация данных для передачи-----------
	{		//очистка данных для передачи
	Uint16* p = &tx.serv.all;
	Uint16 i;
	for(i=0;i<8;i++) *(p + i) = 0;
	
	p = &tx_4slv.serv.all;
	for(i=0;i<8;i++) *(p + i) = 0;
	}//-------------------------------------------

	tx.serv.bit.mode = INIT_MODE;					//установить режим
	tx.serv.bit.cell_indx = 0;							//установить операцию чтения ячеек
	tx.Smpl_F[0].all = tx.Smpl_F[1].all = tx.Smpl_F[2].all = mid_lvl; //выставить нулевой уровень функции

	tx_4slv.serv.bit.mode = INIT_MODE;					//установить режим
	tx_4slv.serv.bit.cell_indx = 0;							//установить операцию чтения ячеек
	tx_4slv.Smpl_F[0].all = tx_4slv.Smpl_F[1].all = tx_4slv.Smpl_F[2].all = mid_lvl; //выставить нулевой уровень функции

	//инициализация архива---------------------------
	{		//очистка архива
	Uint16* p = &store[0].serv.all;
	Uint16 i;
	for(i=0;i<8*3;i++) *(p + i) = 0;
	p = &store_slv[0].serv.all;
	for(i=0;i<8*4;i++) *(p + i) = 0;
	}//-----------------------------------------------

	EALLOW;  // This is needed to write to EALLOW protected registers
		GpioIntRegs.GPIOXNMISEL.bit.GPIOSEL = 28;			//связать вход 28 с внешним прерыванием
		XIntruptRegs.XNMICR.bit.POLARITY = 0;				//внешнее прерывание NMINT по падающему фронту сигнала
		XIntruptRegs.XNMICR.bit.ENABLE = 0;					//
		XIntruptRegs.XNMICR.bit.SELECT = 1;					//выбрать прерывание int13
	EDIS;    // This is needed to disable write to EALLOW protected registers

	SciaRegs.SCICTL1.bit.RXENA	= 0;	//выключить приемник  RS485_2  (а)
	ScicRegs.SCICTL1.bit.RXENA	= 0;	//выключить приемник  RS485_1  (c)
	XIntruptRegs.XNMICR.bit.ENABLE = 0;	//отключить прерывание порта
	MSmode = sngl_mode;

	Exp1_regs.GPout.all = 0xFFFFFFFF;
	Exp2_regs.GPout.all = 0xFFFFFFFF;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//функция настройки spi передачи
void Stup_SPI_exch(Uint16 dev_sel)
	{
	//сохранение результата 
	if(spi_store.spi_dev == ADC1_dev_SEL) {AD7732_1.adc1 = (spi_store.data[2] & 0xFF) + (spi_store.data[1] * 0x100);}

	if(spi_store.spi_dev == ADC2_dev_SEL) {AD7732_2.adc1 = (spi_store.data[2] & 0xFF) + (spi_store.data[1] * 0x100);}

	if(spi_store.spi_dev == EXP1_dev_SEL) {Exp1_regs.GPin.byte.GP4_11 = spi_store.data[1] & 0xFF;
										   Exp1_regs.GPin.byte.GP12_19 = spi_store.data[2] & 0xFF;}
										   
	if(spi_store.spi_dev == EXP2_dev_SEL) {Exp2_regs.GPin.byte.GP4_11 = spi_store.data[1] & 0xFF;
										   Exp2_regs.GPin.byte.GP12_19 = spi_store.data[2] & 0xFF;}
	//настройка SPI
	if((dev_sel == ADC1_dev_SEL) || (dev_sel == ADC2_dev_SEL))
		{
		SpiaRegs.SPICCR.bit.SPICHAR = 0x7;			//передача слова из 8 бит
		SpiaRegs.SPICCR.bit.CLKPOLARITY = 1;		//подача данных на выход по спадающему фронту
		SpiaRegs.SPICTL.bit.CLK_PHASE = 0;			//выключить задержку сигнала clk
		SpiaRegs.SPIBRR = 74;						//установить частоту LSPCLK/(74+1) (1 МГц) 

		spi_store.spi_dev = dev_sel;
		spi_store.remn_nmb_byte = 3;
		spi_store.nmb_byte = 3;
		spi_store.data[0] = (R_ad7732 + Ch1_Data_adr) * 0x100;
		spi_store.data[1] = 0;
		spi_store.data[2] = 0;
		}
	if((dev_sel == EXP1_dev_SEL) || (dev_sel == EXP2_dev_SEL))
		{ 
		SpiaRegs.SPICCR.bit.SPICHAR = 0xF;			//передача слова из 16 бит
		SpiaRegs.SPICCR.bit.CLKPOLARITY = 0;		//подача данных на выход по нарастающему фронту
		SpiaRegs.SPICTL.bit.CLK_PHASE = 1;			//включить задержку сигнала clk
		SpiaRegs.SPIBRR = 9;						//установить частоту LSPCLK/(9+1) (7.5 МГц) 

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



//функция обработки принятых данных по SCI. аргументы в функцию передаются по ссылке
void Get_RX_SCI(volatile struct SCI_REGS *ScixRegs, Uint16 RXmode, struct TX_FRAME *txd, union	CELL_DATA_UNION	_cell[], struct STORE_DATA *st_pnt[])
	{//########################################################################################

	static struct	SCIRX_DATA	RXd_frm_clls;		//вспомогательные данные ведущего
	static struct	SCIRX_DATA	RXd_frm_slv;		//вспомогательные данные ведомого
	struct			SCIRX_DATA	*RXdat;			//указатель

	if(RXmode == RX_FROM_SLAVE) RXdat = &RXd_frm_slv;
	else				   		RXdat = &RXd_frm_clls;

		//------------------------------------------------------------------------------------
		if(ScixRegs->SCIRXST.bit.RXERROR)				//если ошибка, то:
			{//-----------------------------------------------------------------------
			ScixRegs->SCICTL1.bit.RXENA	=	0;			//выключить приемник

			txd->serv.bit.mode = INIT_MODE;		//установить режим инициализации
			//установить признак ошибки связи с запрошенной ячейкой				
			_cell[st_pnt[1]->data[1] * NUMB_OF_CELLS + st_pnt[1]->data[0]].word.sgnl_err = 1;
			}//----------------------------------------------------------------------

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		else //если ошибок нет, то:
			{//====================================================================
			for(;ScixRegs->SCIFFRX.bit.RXFFST;)
				{//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
				RXdat->new_datain[RXdat->numb_frames] = ScixRegs->SCIRXBUF.all & 0xFF;		//сохранить байт сообщения
				RXdat->numb_frames++;		
				}//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

			if(st_pnt[1]->serv.bit.mode)				//если был установлен рабочий режим, то
				{//****************************************************************
				if(RXdat->numb_frames == 9)//если количество принятых байтов верно, то:
					{//"""""""""""""""""""""""""""""""""""""""""""""""""
					Uint16	n, i;

					for(i=0;i<3;i++)
						{//определить номер ячейки в преобразователе
						n = ((RXdat->new_datain[i*3] & 0x30) / 0x10) * NUMB_OF_CELLS + (RXdat->new_datain[i*3] & 0xF);

						_cell[n].word.An_Val.named.UDC = new_datain[i*3+1];				//сохранить значение выпрямленного напряжения
						_cell[n].word.W1flags.bit.C_ready = new_datain[i*3] / 0x80;			//сохранить флаг готовности к работе
						_cell[n].word.W1flags.bit.protect_C = new_datain[i*3+2] / 0x80;		//сохранить флаг срабатывания защиты
						_cell[n].word.W1flags.bit.pre_protect_C = (new_datain[i*3+2] & 0x40) / 0x40; //сохранить флаг предупреждения
						}
					}//"""""""""""""""""""""""""""""""""""""""""""""""""

				else //если количество принятых байтов не верно, то:
					{//"""""""""""""""""""""""""""""""""""""""""""""""""
					err_frames++;						//увеличить счетчик ошибок
					txd->serv.bit.mode = INIT_MODE;		//установить режим инициализации
					//установить признак ошибки связи с запрошенной ячейкой				
					_cell[st_pnt[1]->data[1] * NUMB_OF_CELLS + st_pnt[1]->data[0]].word.sgnl_err = 1;
					}//"""""""""""""""""""""""""""""""""""""""""""""""""			
				}//*****************************************************************
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

			else //если установлен режим инициализации
				{//*****************************************************************
				if(RXdat->numb_frames == 5)		//если количество принятых байтов верно, то:
					{//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
					if(RXdat->new_datain[0] & 0x80)		//если бит кода операции установлен 
						{							//(пришел ответ о сохранении ячейкой параметра), то
						//пока не реализован
						}

					else							//если пришел ответ на запрос параметра, то
						{//------------------------------------------------
						RXdat->Nc_resp =  RXdat->new_datain[4] * NUMB_OF_CELLS + RXdat->new_datain[3]; 		//определить номер ячейки из сообщения
						RXdat->Nc_req = st_pnt[1]->data[1] * NUMB_OF_CELLS + st_pnt[1]->data[0];	//определить № ячейки из архива
						RXdat->Np_resp =  RXdat->new_datain[0] & 0x3F;								//определить № параметра из сообщения																	//запроса 
						RXdat->Np_req = st_pnt[1]->data[2];								//определить № параметра из архива

						if((RXdat->Nc_resp != RXdat->Nc_req)||(RXdat->Np_resp != RXdat->Np_req))	//если номер ячейки или номер параметра в запросе 
							{											//не совпадает с принятым, то
							RXdat->p_cnt = 0;
							_cell[RXdat->Nc_req].word.sgnl_err = 1;	 //установить признак ошибки связи с ячейкой
							}								 
						else	//если адресные данные запроса и ответа совпадают, то
							{//сохранить значение принятой переменной
							_cell[RXdat->Nc_resp].all[RXdat->Np_resp] = RXdat->new_datain[2] * 0x100 + RXdat->new_datain[1]; 
							RXdat->p_cnt++;
							if(RXdat->Np_resp == nmb_of_askprm - 1) // если номер переменной последний
								{
								//если счетчик параметров равен максимальному значению, сбросить признак ошибки										
								if(RXdat->p_cnt == nmb_of_askprm)	   
									{
								 	_cell[RXdat->Nc_req].word.sgnl_err = 0;	 //сбросить признак ошибки связи с ячейкой
									}
								RXdat->p_cnt = 0;				   				//сбросить счетчик параметров
							}	}	
						}//----------------------------------------------------	
					}//"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

				else ////если количество принятых байтов не верно, то:
					{//"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
					err_frames++;						//увеличить счетчик ошибок	
					txd->serv.bit.mode = INIT_MODE;		//установить режим инициализации

					//установить признак ошибки связи с ячейкой				
					_cell[st_pnt[1]->data[1] * NUMB_OF_CELLS + st_pnt[1]->data[0]].word.sgnl_err = 1;
					}//"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""					
				}//*****************************************************************
			}//====================================================================
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		RXdat->numb_frames = 0;							//обнулить счетчик сообщений

		ScixRegs->SCICTL1.bit.SWRESET = 0;			//сбросить флаги
		ScixRegs->SCICTL1.bit.SWRESET = 1;
		ScixRegs->SCIFFRX.bit.RXFIFORESET = 0;		//сбросить указатель FIFO RX	
		ScixRegs->SCIFFRX.bit.RXFIFORESET = 1;
		ScixRegs->SCICTL1.bit.RXENA	=	1;			//включить приемник
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	}//########################################################################################





