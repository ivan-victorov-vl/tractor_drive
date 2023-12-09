################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"C:/Work/sespel/tractor_drive/F2833x_nonBIOS_flash.cmd" \
"C:/Work/sespel/tractor_drive/DSP2833x_Headers_nonBIOS.cmd" \
"./MainCPU-Main(1).obj" \
"./source/BaseDrive.obj" \
"./source/DSP2833x_ADC_cal.obj" \
"./source/DSP2833x_DefaultIsr.obj" \
"./source/DSP2833x_GlobalVariableDefs.obj" \
"./source/DSP2833x_PieCtrl.obj" \
"./source/DSP2833x_PieVect.obj" \
"./source/DSP2833x_SysCtrl.obj" \
"./source/DSP28xxx_CodeStartBranch_for_flash.obj" \
"./source/DSP28xxx_SectionCopy_nonBIOS.obj" \
"./source/FuncDrive.obj" \
"./source/MainCpuAdc.obj" \
"./source/MainCpuEpwm.obj" \
"./source/MainCpuSci.obj" \
"./source/MainCpuSpi.obj" \
"./source/MainInit.obj" \
"./source/MainLedIndctn.obj" \
"./source/MainModbus.obj" \
"./source/MainPanel.obj" \
"./source/MainSetting.obj" \
"./source/Main_CPU_CpuTimers.obj" \
"./source/MeasExtrnlDevice.obj" \
"./source/MenuModbus.obj" \
"./source/ProtectnDrive.obj" \
"./source/Smpl_table.obj" \
"./source/SysSrvc.obj" \
"C:/Work/sespel/tractor_drive/lib/rts2800_fpu32.lib" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include lib/subdir_vars.mk
-include source/subdir_vars.mk
-include subdir_rules.mk
-include lib/subdir_rules.mk
-include source/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
C:/Work/sespel/tractor_drive/main_CPU_(real)/../FLASH/MainCPU.out \

EXE_OUTPUTS__QUOTED += \
"C:\Work\sespel\tractor_drive\FLASH\MainCPU.out" \

BIN_OUTPUTS += \
C:/Work/sespel/tractor_drive/FLASH/MainCPU.hex \

BIN_OUTPUTS__QUOTED += \
"C:\Work\sespel\tractor_drive\FLASH\MainCPU.hex" \


# All Target
all: C:/Work/sespel/tractor_drive/main_CPU_(real)/../FLASH/MainCPU.out

# Tool invocations
C:/Work/sespel/tractor_drive/main_CPU_(real)/../FLASH/MainCPU.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on -z -m"C:/Work/sespel/tractor_drive/FLASH/MainCPU.map" --stack_size=0x380 --warn_sections -i"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/lib" -i"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" -i"C:/Work/sespel/tractor_drive/main_CPU_(real)" -i"C:/Work/sespel/tractor_drive" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="C:/Work/sespel/tractor_drive/FLASH/MainCPU_linkInfo.xml" --rom_model -o "C:/Work/sespel/tractor_drive/main_CPU_(real)/../FLASH/MainCPU.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

C:/Work/sespel/tractor_drive/FLASH/MainCPU.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/hex2000"  -o "C:/Work/sespel/tractor_drive/FLASH/MainCPU.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "MainCPU-Main(1).obj" "source\BaseDrive.obj" "source\DSP2833x_ADC_cal.obj" "source\DSP2833x_DefaultIsr.obj" "source\DSP2833x_GlobalVariableDefs.obj" "source\DSP2833x_PieCtrl.obj" "source\DSP2833x_PieVect.obj" "source\DSP2833x_SysCtrl.obj" "source\DSP28xxx_CodeStartBranch_for_flash.obj" "source\DSP28xxx_SectionCopy_nonBIOS.obj" "source\FuncDrive.obj" "source\MainCpuAdc.obj" "source\MainCpuEpwm.obj" "source\MainCpuSci.obj" "source\MainCpuSpi.obj" "source\MainInit.obj" "source\MainLedIndctn.obj" "source\MainModbus.obj" "source\MainPanel.obj" "source\MainSetting.obj" "source\Main_CPU_CpuTimers.obj" "source\MeasExtrnlDevice.obj" "source\MenuModbus.obj" "source\ProtectnDrive.obj" "source\Smpl_table.obj" "source\SysSrvc.obj" 
	-$(RM) "MainCPU-Main(1).d" "source\BaseDrive.d" "source\DSP2833x_DefaultIsr.d" "source\DSP2833x_GlobalVariableDefs.d" "source\DSP2833x_PieCtrl.d" "source\DSP2833x_PieVect.d" "source\DSP2833x_SysCtrl.d" "source\FuncDrive.d" "source\MainCpuAdc.d" "source\MainCpuEpwm.d" "source\MainCpuSci.d" "source\MainCpuSpi.d" "source\MainInit.d" "source\MainLedIndctn.d" "source\MainModbus.d" "source\MainPanel.d" "source\MainSetting.d" "source\Main_CPU_CpuTimers.d" "source\MeasExtrnlDevice.d" "source\MenuModbus.d" "source\ProtectnDrive.d" "source\Smpl_table.d" "source\SysSrvc.d" 
	-$(RM) "source\DSP2833x_ADC_cal.d" "source\DSP28xxx_CodeStartBranch_for_flash.d" "source\DSP28xxx_SectionCopy_nonBIOS.d" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-"C:/Work/sespel/tractor_drive/main_CPU_(real)/postBuildStep_F28335_flash.bat"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

