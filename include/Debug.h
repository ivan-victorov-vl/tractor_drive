//###########################################################################
//
// FILE:    Debug.h
//
// TITLE:   Debug board
//
//###########################################################################

#ifndef DEBUG_H_
#define DEBUG_H_

//! Нулевая точка тока фазы U
#define ZERO_VALUE_I_PHASE_U 2048
//! Нулевая точка тока фазы V
#define ZERO_VALUE_I_PHASE_V 2048
//! Нулевая точка тока фазы W
#define ZERO_VALUE_I_PHASE_W 2048
//! Нулевая точка тока фазы U1
#define ZERO_VALUE_I_PHASE_U1 2048
//! Нулевая точка тока фазы V1
#define ZERO_VALUE_I_PHASE_V1 2048
//! Нулевая точка тока фазы W1
#define ZERO_VALUE_I_PHASE_W1 2048

//! Нулевая точка напряжения фазы U
#define ZERO_VALUE_U_PHASE_U 2048
//! Нулевая точка напряжения фазы V
#define ZERO_VALUE_U_PHASE_V 2048
//! Нулевая точка напряжения фазы W
#define ZERO_VALUE_U_PHASE_W 2048
//! Нулевая точка напряжения фазы U1
#define ZERO_VALUE_U_PHASE_U1 2048
//! Нулевая точка напряжения фазы V1
#define ZERO_VALUE_U_PHASE_V1 2048
//! Нулевая точка напряжения фазы W1
#define ZERO_VALUE_U_PHASE_W1 2048

//! процент напряжения при котором происходит подача разрешение на дискретный выход DO1 при напряжение на Udc
#define DO1_ACTIVATION_IN_PERCENT 10


//! Модель с задатчиком интенсивности (Если требуется модель с задатчиком интенсивности, то нужно убрать комментирии)
//#define MODEL_INTENSITY_SET TRUE_VAL

#endif /* DEBUG_H_ */
