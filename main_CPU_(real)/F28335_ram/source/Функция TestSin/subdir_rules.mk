################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
C:/Work/Projects/Drive\ gidromash/MAIN_CPU_(real)_U_F/RAM/TestSin.obj: ../source/Функция\ TestSin/TestSin.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/Work/Projects/Drive gidromash/MAIN_CPU_(real)_U_F/include" --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --opt_for_speed=4 --output_all_syms --obj_directory="C:/Work/Projects/Drive gidromash/MAIN_CPU_(real)_U_F/RAM" --preproc_with_compile --preproc_dependency="source/Функция TestSin/TestSin.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


