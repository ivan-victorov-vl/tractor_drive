//###########################################################################
//
// File: MainExtrnlDevice.h
//
// Description: MainExtrnlDevice.c header file
//
//###########################################################################

#ifndef MEASEXTRNLDEVICE_H_
#define MEASEXTRNLDEVICE_H_

////////////////////// DECLARATION OF NAMED CONSTANTS //////////////////////
// shift resolver relative to absolute zero to bring the rotor to 0
#define SHIFT_RES 230

//////////////// DECLARATION OF EXTERNAL ACCESS TO FUNCTIONS /////////////////////
// declaration of external access to the HandlrExtrnlFastDevice function
extern void HandlrExtrnlFastDevice(Data_PMSM_S *md_motor_l);

#endif
