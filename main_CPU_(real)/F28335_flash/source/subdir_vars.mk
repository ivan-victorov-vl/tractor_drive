################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
C:/Work/sespel/tractor_drive/source/DSP2833x_ADC_cal.asm \
C:/Work/sespel/tractor_drive/source/DSP28xxx_CodeStartBranch_for_flash.asm \
C:/Work/sespel/tractor_drive/source/DSP28xxx_SectionCopy_nonBIOS.asm 

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
../source/MainLedIndctn.c \
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
./source/MainLedIndctn.d \
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
./source/BaseDrive.obj \
./source/DSP2833x_ADC_cal.obj \
./source/DSP2833x_DefaultIsr.obj \
./source/DSP2833x_GlobalVariableDefs.obj \
./source/DSP2833x_PieCtrl.obj \
./source/DSP2833x_PieVect.obj \
./source/DSP2833x_SysCtrl.obj \
./source/DSP28xxx_CodeStartBranch_for_flash.obj \
./source/DSP28xxx_SectionCopy_nonBIOS.obj \
./source/FuncDrive.obj \
./source/MainCpuAdc.obj \
./source/MainCpuEpwm.obj \
./source/MainCpuSci.obj \
./source/MainCpuSpi.obj \
./source/MainInit.obj \
./source/MainLedIndctn.obj \
./source/MainModbus.obj \
./source/MainPanel.obj \
./source/MainSetting.obj \
./source/Main_CPU_CpuTimers.obj \
./source/MeasExtrnlDevice.obj \
./source/MenuModbus.obj \
./source/ProtectnDrive.obj \
./source/Smpl_table.obj \
./source/SysSrvc.obj 

ASM_DEPS += \
./source/DSP2833x_ADC_cal.d \
./source/DSP28xxx_CodeStartBranch_for_flash.d \
./source/DSP28xxx_SectionCopy_nonBIOS.d 

OBJS__QUOTED += \
"source\BaseDrive.obj" \
"source\DSP2833x_ADC_cal.obj" \
"source\DSP2833x_DefaultIsr.obj" \
"source\DSP2833x_GlobalVariableDefs.obj" \
"source\DSP2833x_PieCtrl.obj" \
"source\DSP2833x_PieVect.obj" \
"source\DSP2833x_SysCtrl.obj" \
"source\DSP28xxx_CodeStartBranch_for_flash.obj" \
"source\DSP28xxx_SectionCopy_nonBIOS.obj" \
"source\FuncDrive.obj" \
"source\MainCpuAdc.obj" \
"source\MainCpuEpwm.obj" \
"source\MainCpuSci.obj" \
"source\MainCpuSpi.obj" \
"source\MainInit.obj" \
"source\MainLedIndctn.obj" \
"source\MainModbus.obj" \
"source\MainPanel.obj" \
"source\MainSetting.obj" \
"source\Main_CPU_CpuTimers.obj" \
"source\MeasExtrnlDevice.obj" \
"source\MenuModbus.obj" \
"source\ProtectnDrive.obj" \
"source\Smpl_table.obj" \
"source\SysSrvc.obj" 

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
"source\MainLedIndctn.d" \
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
"source\DSP28xxx_CodeStartBranch_for_flash.d" \
"source\DSP28xxx_SectionCopy_nonBIOS.d" 

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
"../source/MainLedIndctn.c" \
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
"C:/Work/sespel/tractor_drive/source/DSP28xxx_CodeStartBranch_for_flash.asm" \
"C:/Work/sespel/tractor_drive/source/DSP28xxx_SectionCopy_nonBIOS.asm" 


