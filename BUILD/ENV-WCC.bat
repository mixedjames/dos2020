@REM ***************************************************************************
@REM   NOTES: (because I don't do this stuff very often any more)
@REM ***************************************************************************

@REM !!! IMPORTANT !!!
@REM Ensure paths to your Watcom and DOSBox directories are set correctly.

@SET WATCOM=C:\WATCOM
@SET NASM=c:\Program Files (x86)\nasm\
@SET DOSBOX=c:\Program Files (x86)\DOSBox-0.74-2\

@REM !!! IMPORTANT !!!
@REM Don't fiddle after this point

@SET PATH=%WATCOM%\BINNT;%WATCOM%\BINW;%PATH%
@SET PATH=%NASM%;%PATH%
@SET PATH=%DOSBOX%;%PATH%
@SET WATCOM_BUILD_ENV=TRUE

@CD ..\CODE

@CMD