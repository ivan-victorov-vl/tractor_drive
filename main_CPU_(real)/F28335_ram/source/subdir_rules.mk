################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
C:/Work/sespel/tractor_drive/RAM/BaseDrive.obj: ../source/BaseDrive.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/BaseDrive.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/DSP2833x_ADC_cal.obj: C:/Work/sespel/tractor_drive/source/DSP2833x_ADC_cal.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/DSP2833x_ADC_cal.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/DSP2833x_CodeStartBranch.obj: C:/Work/sespel/tractor_drive/source/DSP2833x_CodeStartBranch.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/DSP2833x_CodeStartBranch.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/DSP2833x_DefaultIsr.obj: C:/Work/sespel/tractor_drive/source/DSP2833x_DefaultIsr.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/DSP2833x_DefaultIsr.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/DSP2833x_GlobalVariableDefs.obj: C:/Work/sespel/tractor_drive/source/DSP2833x_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/DSP2833x_GlobalVariableDefs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/DSP2833x_PieCtrl.obj: C:/Work/sespel/tractor_drive/source/DSP2833x_PieCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/DSP2833x_PieCtrl.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/DSP2833x_PieVect.obj: C:/Work/sespel/tractor_drive/source/DSP2833x_PieVect.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/DSP2833x_PieVect.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/DSP2833x_SysCtrl.obj: C:/Work/sespel/tractor_drive/source/DSP2833x_SysCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/DSP2833x_SysCtrl.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/FuncDrive.obj: C:/Work/sespel/tractor_drive/source/FuncDrive.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/FuncDrive.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/MainCpuAdc.obj: ../source/MainCpuAdc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/MainCpuAdc.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/MainCpuEpwm.obj: ../source/MainCpuEpwm.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/MainCpuEpwm.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/MainCpuSci.obj: ../source/MainCpuSci.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/MainCpuSci.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/MainCpuSpi.obj: ../source/MainCpuSpi.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/MainCpuSpi.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/MainInit.obj: ../source/MainInit.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/MainInit.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/MainLedIndctn.obj: ../source/MainLedIndctn.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/MainLedIndctn.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/MainModbus.obj: C:/Work/sespel/tractor_drive/source/MainModbus.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/MainModbus.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/MainPanel.obj: ../source/MainPanel.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/MainPanel.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/MainSetting.obj: ../source/MainSetting.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/MainSetting.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/Main_CPU_CpuTimers.obj: C:/Work/sespel/tractor_drive/source/Main_CPU_CpuTimers.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/Main_CPU_CpuTimers.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/MeasExtrnlDevice.obj: ../source/MeasExtrnlDevice.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/MeasExtrnlDevice.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/MenuModbus.obj: ../source/MenuModbus.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/MenuModbus.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/ProtectnDrive.obj: ../source/ProtectnDrive.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/ProtectnDrive.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/Smpl_table.obj: ../source/Smpl_table.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/Smpl_table.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

C:/Work/sespel/tractor_drive/RAM/SysSrvc.obj: ../source/SysSrvc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=0 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="source/SysSrvc.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


