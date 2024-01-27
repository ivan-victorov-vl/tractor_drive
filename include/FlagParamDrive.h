//###########################################################################
//
// FILE:    FlagParamDrive.h
//
// TITLE:   Flag memory structure definition file
//
// NOTES:
//
//###########################################################################

#ifndef FLAGPARAMDRIVE_H_
#define FLAGPARAMDRIVE_H_



/////////////////////// DATA STRUCTURE DECLARATION //////////////////////////

/*
 * \brief Frequency inverter control flagsНажмите, чтобы использовать этот вариант
 */
typedef struct
{
	// 0 frequency converter network: 0 - disabled, 1 - enabled
	Uint16 net_drv :1;
	// 1 frequency inverter start: 0 - stop, 1 - start
	Uint16 strt_drv : 1;
	// 2 frequency inverter stop: 0 - stop, 1 - stop
	Uint16 stp_drv : 1;
	// 3 feedback from the angle control sensor: 0 - not signal, 1 - signal
	Uint16 ext_angle : 1;
    // 15 : 4 reserved
	Uint16 rsvd : 12;
} Flg_Adr01_Bits_S;

/*
 * \brief General memory of the 1st register
 */
typedef union
{
	Uint16               all;
	Flg_Adr01_Bits_S 	 bits;
} Flg_Adr01_Reg_S;

/*!
 *  \brief Inverter control flags
 */
typedef struct
{
    //! 0 frequency converter network: 0 - disabled, 1 - enabled
	Uint16 net_drv :1;
	//! 1 frequency converter operation readiness: 0 - off, 1 - on
	Uint16 read_drv : 1;
	//! 2 frequency converter operation: 0 - off, 1 - on
	Uint16 wrk_drv : 1;
	//3 frequency inverter start: 0 - off, 1 - on
	Uint16 strt_drv : 1;
	// 4 frequency inverter stop: 0 - off, 1 - on
	Uint16 stp_drv : 1;
	// 5 inverter error reset: 0 - off, 1 - on
    Uint16 reset_drv : 1;
	// 6 frequency converter fault:  0 - no fault, 1 - fault occurred
	Uint16 err_drv : 1;
	// 7 frequency converter fault by overcurrent protection: 0 - no fault, 1 - fault occurred
	Uint16 err_mi_drv : 1;
	// 8 frequency converter fault by driver protection: 0 - no fault, 1 - fault occurred
	Uint16 err_trnstr_drv : 1;
	// 15:9 reserved
	Uint16 rsvd : 8;
} Flg_Adr02_Bits_S;

/*!
 *  \brief General memory of the 2nd register
 */
typedef union
{
	Uint16               all;
	Flg_Adr02_Bits_S 	 bits;
} Flg_Adr02_Reg_S;

/*!
 *  \brief Inverter control flags
 */
typedef struct
{
	// 0 SEL button actuation flag: 0 - button did not actuate, 1 - button actuated
	Uint16 sel:1;
	// 1 flag of up button actuation: 0 - button did not actuate, 1 - button actuated
	Uint16  up:1;
	// 2 Down button operation flag: 0 - button did not operate, 1 - button operated
	Uint16  down:1;
	// reserved flags
    Uint16  rsvd : 13;
} Flg_Adr03_Bits_S;

/*!
 *  \brief General memory of register 3
 */
typedef union
{
	Uint16               all;
	Flg_Adr03_Bits_S 	 bits;
} Flg_Adr03_Reg_S;

/*!
 *  \brief Inverter common flag memory
 */
typedef struct
{
	Flg_Adr01_Reg_S bits_reg1;
	Flg_Adr02_Reg_S bits_reg2;
	Flg_Adr03_Reg_S bits_reg3;
} Flg_Cntrl_Drive_S;


#endif /* FLAGPARAMDRIVE_H_ */
