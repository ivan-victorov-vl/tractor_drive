################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
lib/rts2800_fpu32.exe: C:/Users/Lenovo/programs/TMS320F28335/tractor_drive/lib/rts2800_fpu32.lib $(GEN_CMDS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 -Ooff --opt_for_speed=1 --fp_reassoc=on --define=_DEBUG --define=LARGE_MODEL -g --optimize_with_debug=on --diag_warning=225 --diag_wrap=off --display_error_number --sat_reassoc=on -z -m"C:/Users/Lenovo/programs/TMS320F28335/tractor_drive/lib/FLASH/MainCPU.map" --stack_size=0x380 --warn_sections -i"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/lib" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" -i"C:/Users/Lenovo/programs/TMS320F28335/tractor_drive/main_CPU_(real)" -i"C:/Users/Lenovo/programs/TMS320F28335/tractor_drive" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="C:/Users/Lenovo/programs/TMS320F28335/tractor_drive/FLASH/MainCPU_linkInfo.xml" --rom_model -o "$@" "$<" "../28335_RAM_lnk.cmd" "../DSP2833x_Headers_nonBIOS.cmd" "../F28335.cmd" "../F2833x_nonBIOS_flash.cmd"
	@echo 'Finished building: "$<"'
	@echo ' '


