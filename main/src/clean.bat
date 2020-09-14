@echo off
for /D %%A in (*) do call :cleanit %%A
exit /B 0

:cleanit
call :cleanitup %1\Debug_Win32
call :cleanitup %1\Release_Win32
call :cleanitup %1\Debug_x64
call :cleanitup %1\Release_x64
exit /B 0

:cleanitup
echo Cleaning %1
if exist %1 rmdir /s /q %1
exit /B 0
