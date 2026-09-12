@echo off
title BFME1 - Smooth 60 (rev 3)
rem Run from your BFME1 folder (next to lotrbfme.exe). Add -win for windowed.
if not exist "%~dp0lotrbfme-smooth60.exe" ( echo lotrbfme-smooth60.exe not found next to this file & pause & exit /b 1 )
cd /d "%~dp0"
start "" "%~dp0lotrbfme-smooth60.exe" %*
exit /b 0
