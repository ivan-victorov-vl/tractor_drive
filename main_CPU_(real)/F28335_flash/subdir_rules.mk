################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
MainCPU-Main(1).obj: C:/Users/Lenovo/programs/TMS320F28335/tractor_drive/MainCPU-Main(1).c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --include_path="/packages/ti/xdais" --include_path="C:/Users/Lenovo/programs/TMS320F28335/tractor_drive/include" --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on --preproc_with_compile --preproc_dependency="MainCPU-Main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


