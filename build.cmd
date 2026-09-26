@echo off
rem Windows entry point for tools\build.py (cmd or PowerShell). Same arguments as build.sh.
rem   build.cmd                              full gate
rem   build.cmd game\path\file.cpp           one TU
py -3 "%~dp0tools\build.py" %*
exit /b %ERRORLEVEL%
