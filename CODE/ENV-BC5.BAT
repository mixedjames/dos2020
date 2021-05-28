REM ****************************************************************************
REM   NOTES: (because I don't do this stuff very often any more)
REM     - START command allows use to start DOSBox without leaving another
REM       Command Prompt open cluttering up the taskbar
REM     - Empty quotes are intentional - this would be the title of the new
REM       Command Prompt window but since it doesn't stick about we don't care
REM     - Lack of quotes around the DOXBox path is correct! (Turns out I've
REM       been doing this wrong for years...)
REM ****************************************************************************

SET PATH=c:\Program Files (x86)\DOSBox-0.74-2\;%PATH%
START "" DOSBOX.EXE -conf CONFIG\BCC.CFG
