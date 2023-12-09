################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
C:/Work/sespel/tractor_drive/RAM/MainCPU-Main(1).obj: C:/Work/sespel/tractor_drive/MainCPU-Main(1).c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=4 --include_path="C:/ti/ccs810/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Work/sespel/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --diag_warning=225 --display_error_number --output_all_syms --obj_directory="C:/Work/sespel/tractor_drive/RAM" --preproc_with_compile --preproc_dependency="MainCPU-Main(1).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


