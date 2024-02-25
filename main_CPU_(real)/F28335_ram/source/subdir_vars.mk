################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
C:/Work/sespel/tractor_drive/source/DSP2833x_ADC_cal.asm \
C:/Work/sespel/tractor_drive/source/DSP2833x_CodeStartBranch.asm 

C_SRCS += \
../source/BaseDrive.c \
C:/Work/sespel/tractor_drive/source/DSP2833x_DefaultIsr.c \
C:/Work/sespel/tractor_drive/source/DSP2833x_GlobalVariableDefs.c \
C:/Work/sespel/tractor_drive/source/DSP2833x_PieCtrl.c \
C:/Work/sespel/tractor_drive/source/DSP2833x_PieVect.c \
C:/Work/sespel/tractor_drive/source/DSP2833x_SysCtrl.c \
C:/Work/sespel/tractor_drive/source/FuncDrive.c \
../source/MainCpuAdc.c \
../source/MainCpuEpwm.c \
../source/MainCpuSci.c \
../source/MainCpuSpi.c \
../source/MainInit.c \
C:/Work/sespel/tractor_drive/source/MainModbus.c \
../source/MainPanel.c \
../source/MainSetting.c \
C:/Work/sespel/tractor_drive/source/Main_CPU_CpuTimers.c \
../source/MeasExtrnlDevice.c \
../source/MenuModbus.c \
../source/ProtectnDrive.c \
../source/Smpl_table.c \
../source/SysSrvc.c 

C_DEPS += \
./source/BaseDrive.d \
./source/DSP2833x_DefaultIsr.d \
./source/DSP2833x_GlobalVariableDefs.d \
./source/DSP2833x_PieCtrl.d \
./source/DSP2833x_PieVect.d \
./source/DSP2833x_SysCtrl.d \
./source/FuncDrive.d \
./source/MainCpuAdc.d \
./source/MainCpuEpwm.d \
./source/MainCpuSci.d \
./source/MainCpuSpi.d \
./source/MainInit.d \
./source/MainModbus.d \
./source/MainPanel.d \
./source/MainSetting.d \
./source/Main_CPU_CpuTimers.d \
./source/MeasExtrnlDevice.d \
./source/MenuModbus.d \
./source/ProtectnDrive.d \
./source/Smpl_table.d \
./source/SysSrvc.d 

OBJS += \
C:/Work/sespel/tractor_drive/RAM/BaseDrive.obj \
C:/Work/sespel/tractor_drive/RAM/DSP2833x_ADC_cal.obj \
C:/Work/sespel/tractor_drive/RAM/DSP2833x_CodeStartBranch.obj \
C:/Work/sespel/tractor_drive/RAM/DSP2833x_DefaultIsr.obj \
C:/Work/sespel/tractor_drive/RAM/DSP2833x_GlobalVariableDefs.obj \
C:/Work/sespel/tractor_drive/RAM/DSP2833x_PieCtrl.obj \
C:/Work/sespel/tractor_drive/RAM/DSP2833x_PieVect.obj \
C:/Work/sespel/tractor_drive/RAM/DSP2833x_SysCtrl.obj \
C:/Work/sespel/tractor_drive/RAM/FuncDrive.obj \
C:/Work/sespel/tractor_drive/RAM/MainCpuAdc.obj \
C:/Work/sespel/tractor_drive/RAM/MainCpuEpwm.obj \
C:/Work/sespel/tractor_drive/RAM/MainCpuSci.obj \
C:/Work/sespel/tractor_drive/RAM/MainCpuSpi.obj \
C:/Work/sespel/tractor_drive/RAM/MainInit.obj \
C:/Work/sespel/tractor_drive/RAM/MainModbus.obj \
C:/Work/sespel/tractor_drive/RAM/MainPanel.obj \
C:/Work/sespel/tractor_drive/RAM/MainSetting.obj \
C:/Work/sespel/tractor_drive/RAM/Main_CPU_CpuTimers.obj \
C:/Work/sespel/tractor_drive/RAM/MeasExtrnlDevice.obj \
C:/Work/sespel/tractor_drive/RAM/MenuModbus.obj \
C:/Work/sespel/tractor_drive/RAM/ProtectnDrive.obj \
C:/Work/sespel/tractor_drive/RAM/Smpl_table.obj \
C:/Work/sespel/tractor_drive/RAM/SysSrvc.obj 

ASM_DEPS += \
./source/DSP2833x_ADC_cal.d \
./source/DSP2833x_CodeStartBranch.d 

OBJS__QUOTED += \
"C:\Work\sespel\tractor_drive\RAM\BaseDrive.obj" \
"C:\Work\sespel\tractor_drive\RAM\DSP2833x_ADC_cal.obj" \
"C:\Work\sespel\tractor_drive\RAM\DSP2833x_CodeStartBranch.obj" \
"C:\Work\sespel\tractor_drive\RAM\DSP2833x_DefaultIsr.obj" \
"C:\Work\sespel\tractor_drive\RAM\DSP2833x_GlobalVariableDefs.obj" \
"C:\Work\sespel\tractor_drive\RAM\DSP2833x_PieCtrl.obj" \
"C:\Work\sespel\tractor_drive\RAM\DSP2833x_PieVect.obj" \
"C:\Work\sespel\tractor_drive\RAM\DSP2833x_SysCtrl.obj" \
"C:\Work\sespel\tractor_drive\RAM\FuncDrive.obj" \
"C:\Work\sespel\tractor_drive\RAM\MainCpuAdc.obj" \
"C:\Work\sespel\tractor_drive\RAM\MainCpuEpwm.obj" \
"C:\Work\sespel\tractor_drive\RAM\MainCpuSci.obj" \
"C:\Work\sespel\tractor_drive\RAM\MainCpuSpi.obj" \
"C:\Work\sespel\tractor_drive\RAM\MainInit.obj" \
"C:\Work\sespel\tractor_drive\RAM\MainModbus.obj" \
"C:\Work\sespel\tractor_drive\RAM\MainPanel.obj" \
"C:\Work\sespel\tractor_drive\RAM\MainSetting.obj" \
"C:\Work\sespel\tractor_drive\RAM\Main_CPU_CpuTimers.obj" \
"C:\Work\sespel\tractor_drive\RAM\MeasExtrnlDevice.obj" \
"C:\Work\sespel\tractor_drive\RAM\MenuModbus.obj" \
"C:\Work\sespel\tractor_drive\RAM\ProtectnDrive.obj" \
"C:\Work\sespel\tractor_drive\RAM\Smpl_table.obj" \
"C:\Work\sespel\tractor_drive\RAM\SysSrvc.obj" 

C_DEPS__QUOTED += \
"source\BaseDrive.d" \
"source\DSP2833x_DefaultIsr.d" \
"source\DSP2833x_GlobalVariableDefs.d" \
"source\DSP2833x_PieCtrl.d" \
"source\DSP2833x_PieVect.d" \
"source\DSP2833x_SysCtrl.d" \
"source\FuncDrive.d" \
"source\MainCpuAdc.d" \
"source\MainCpuEpwm.d" \
"source\MainCpuSci.d" \
"source\MainCpuSpi.d" \
"source\MainInit.d" \
"source\MainModbus.d" \
"source\MainPanel.d" \
"source\MainSetting.d" \
"source\Main_CPU_CpuTimers.d" \
"source\MeasExtrnlDevice.d" \
"source\MenuModbus.d" \
"source\ProtectnDrive.d" \
"source\Smpl_table.d" \
"source\SysSrvc.d" 

ASM_DEPS__QUOTED += \
"source\DSP2833x_ADC_cal.d" \
"source\DSP2833x_CodeStartBranch.d" 

C_SRCS__QUOTED += \
"../source/BaseDrive.c" \
"C:/Work/sespel/tractor_drive/source/DSP2833x_DefaultIsr.c" \
"C:/Work/sespel/tractor_drive/source/DSP2833x_GlobalVariableDefs.c" \
"C:/Work/sespel/tractor_drive/source/DSP2833x_PieCtrl.c" \
"C:/Work/sespel/tractor_drive/source/DSP2833x_PieVect.c" \
"C:/Work/sespel/tractor_drive/source/DSP2833x_SysCtrl.c" \
"C:/Work/sespel/tractor_drive/source/FuncDrive.c" \
"../source/MainCpuAdc.c" \
"../source/MainCpuEpwm.c" \
"../source/MainCpuSci.c" \
"../source/MainCpuSpi.c" \
"../source/MainInit.c" \
"C:/Work/sespel/tractor_drive/source/MainModbus.c" \
"../source/MainPanel.c" \
"../source/MainSetting.c" \
"C:/Work/sespel/tractor_drive/source/Main_CPU_CpuTimers.c" \
"../source/MeasExtrnlDevice.c" \
"../source/MenuModbus.c" \
"../source/ProtectnDrive.c" \
"../source/Smpl_table.c" \
"../source/SysSrvc.c" 

ASM_SRCS__QUOTED += \
"C:/Work/sespel/tractor_drive/source/DSP2833x_ADC_cal.asm" \
"C:/Work/sespel/tractor_drive/source/DSP2833x_CodeStartBranch.asm" 


