@echo off
pushd ..\..\
setlocal

:process_arg
if "%1"=="" goto end_process_arg
set name=%1
set value=

:process_arg_value
if NOT "%value%"=="" set value=%value% %2
if "%value%"=="" set value=%2
shift
if "%2"=="!" goto set_arg
if "%2"=="" goto set_arg
goto process_arg_value

:set_arg
set %name%=%value%
shift
shift
goto process_arg
:end_process_arg

echo. > temp_postBuildStep_F28335_flash.bat

echo rem -------------------- Begin Custom Post Build Steps ------------- >> temp_postBuildStep_F28335_flash.bat
echo del *.lkf >> temp_postBuildStep_F28335_flash.bat
echo rem -------------------- End Custom Post Build Steps --------------- >> temp_postBuildStep_F28335_flash.bat

call temp_postBuildStep_F28335_flash.bat
del temp_postBuildStep_F28335_flash.bat

endlocal
popd
