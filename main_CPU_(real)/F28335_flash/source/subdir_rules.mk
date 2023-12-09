################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
source/BaseDrive.obj: ../source/BaseDrive.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/BaseDrive.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/DSP2833x_ADC_cal.obj: C:/Work/sespel/tractor_drive/source/DSP2833x_ADC_cal.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/DSP2833x_ADC_cal.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/DSP2833x_DefaultIsr.obj: C:/Work/sespel/tractor_drive/source/DSP2833x_DefaultIsr.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/DSP2833x_DefaultIsr.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/DSP2833x_GlobalVariableDefs.obj: C:/Work/sespel/tractor_drive/source/DSP2833x_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/DSP2833x_GlobalVariableDefs.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/DSP2833x_PieCtrl.obj: C:/Work/sespel/tractor_drive/source/DSP2833x_PieCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/DSP2833x_PieCtrl.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/DSP2833x_PieVect.obj: C:/Work/sespel/tractor_drive/source/DSP2833x_PieVect.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/DSP2833x_PieVect.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/DSP2833x_SysCtrl.obj: C:/Work/sespel/tractor_drive/source/DSP2833x_SysCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/DSP2833x_SysCtrl.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/DSP28xxx_CodeStartBranch_for_flash.obj: C:/Work/sespel/tractor_drive/source/DSP28xxx_CodeStartBranch_for_flash.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/DSP28xxx_CodeStartBranch_for_flash.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/DSP28xxx_SectionCopy_nonBIOS.obj: C:/Work/sespel/tractor_drive/source/DSP28xxx_SectionCopy_nonBIOS.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/DSP28xxx_SectionCopy_nonBIOS.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/FuncDrive.obj: C:/Work/sespel/tractor_drive/source/FuncDrive.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/FuncDrive.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/MainCpuAdc.obj: ../source/MainCpuAdc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/MainCpuAdc.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/MainCpuEpwm.obj: ../source/MainCpuEpwm.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/MainCpuEpwm.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/MainCpuSci.obj: ../source/MainCpuSci.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/MainCpuSci.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/MainCpuSpi.obj: ../source/MainCpuSpi.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/MainCpuSpi.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/MainInit.obj: ../source/MainInit.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/MainInit.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/MainLedIndctn.obj: ../source/MainLedIndctn.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/MainLedIndctn.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/MainModbus.obj: C:/Work/sespel/tractor_drive/source/MainModbus.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/MainModbus.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/MainPanel.obj: ../source/MainPanel.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/MainPanel.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/MainSetting.obj: ../source/MainSetting.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/MainSetting.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/Main_CPU_CpuTimers.obj: C:/Work/sespel/tractor_drive/source/Main_CPU_CpuTimers.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/Main_CPU_CpuTimers.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/MeasExtrnlDevice.obj: ../source/MeasExtrnlDevice.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/MeasExtrnlDevice.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/MenuModbus.obj: ../source/MenuModbus.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/MenuModbus.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/ProtectnDrive.obj: ../source/ProtectnDrive.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/ProtectnDrive.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/Smpl_table.obj: ../source/Smpl_table.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/Smpl_table.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/SysSrvc.obj: ../source/SysSrvc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="source/SysSrvc.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


