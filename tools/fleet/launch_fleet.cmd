@echo off
rem Windows entry point for tools/fleet/launch_fleet.sh. Double-click or run
rem from cmd/PowerShell; same six seat-count arguments as the .sh:
rem   launch_fleet.cmd 10 0 10 5 10 2   (file big finish mid anon review)
setlocal
set "BASH=%ProgramFiles%\Git\bin\bash.exe"
if not exist "%BASH%" set "BASH=%ProgramFiles(x86)%\Git\bin\bash.exe"
if not exist "%BASH%" set "BASH=%LOCALAPPDATA%\Programs\Git\bin\bash.exe"
if not exist "%BASH%" (
  echo Git Bash not found; install Git for Windows.
  exit /b 2
)
cd /d "%~dp0..\.."
"%BASH%" tools/fleet/launch_fleet.sh %*
exit /b %ERRORLEVEL%
