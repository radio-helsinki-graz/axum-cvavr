@echo off

call:myDosCopyFuncAxum Axum-Rack-AD
rem call:myDosCopyFuncAxum Axum-Rack-ADAT
call:myDosCopyFuncAxum Axum-Rack-Backplane
call:myDosCopyFuncAxum Axum-Rack-CNx
call:myDosCopyFuncAxum Axum-Rack-CRMDA
call:myDosCopyFuncAxum Axum-Rack-DA
call:myDosCopyFuncAxum Axum-Rack-DD
call:myDosCopyFuncAxum Axum-Rack-DD-SRC
call:myDosCopyFuncAxum Axum-Rack-DSP
call:myDosCopyFuncAxum Axum-Rack-ETXBase
call:myDosCopyFuncAxum Axum-Rack-FW
call:myDosCopyFuncAxum Axum-Rack-Hybrid
call:myDosCopyFuncAxum Axum-Rack-MICAD
call:myDosCopyFuncAxum Axum-Rack-PWR
call:myDosCopyFuncAxum Axum-UI-4FBP
call:myDosCopyFuncAxum Axum-UI-CRMP
call:myDosCopyFuncAxum Axum-UI-ETXBase
call:myDosCopyFuncAxum Axum-UI-PCR
call:myDosCopyFunc PPM-VU-Meter-2x60

pause&goto:eof

:myDosCopyFuncAxum
copy /V c:\cvavr\Sources\AXUM\%~1\*.eep z:\Firmware\AXUM\%~1\
copy /V c:\cvavr\Sources\AXUM\%~1\*.rom z:\Firmware\AXUM\%~1\
goto:eof

:myDosCopyFunc
copy /V c:\cvavr\Sources\%~1\*.eep z:\Firmware\AXUM\%~1\
copy /V c:\cvavr\Sources\%~1\*.rom z:\Firmware\AXUM\%~1\
goto:eof

