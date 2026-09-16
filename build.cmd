@echo off
rem Windows entry point for ./build.sh (cmd or PowerShell). Same arguments.
rem   build                     full gate
rem   build Code\path\file.cpp  one TU
powershell.exe -NoLogo -NoProfile -NonInteractive -ExecutionPolicy Bypass -File "%~dp0build.ps1" %*
exit /b %ERRORLEVEL%
