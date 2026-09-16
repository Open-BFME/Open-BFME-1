#Requires -Version 5.1
# Windows entry point for ./build.sh. PowerShell and cmd cannot run a .sh
# file directly (Explorer asks what to open it with); this hands the same
# arguments to Git Bash, which build.sh, the pre-commit hook and the full gate
# already require on Windows.
#   .\build.ps1                       full gate (15-20 min)
#   .\build.ps1 Code\path\file.cpp    one TU, a few seconds
#   .\build.ps1 '?symbol@@...'        one function
$ErrorActionPreference = "Stop"
$root = Split-Path -Parent $MyInvocation.MyCommand.Path
$bash = @(
    "$env:ProgramFiles\Git\bin\bash.exe",
    "${env:ProgramFiles(x86)}\Git\bin\bash.exe",
    "$env:LOCALAPPDATA\Programs\Git\bin\bash.exe"
) | Where-Object { $_ -and (Test-Path $_) } | Select-Object -First 1
if (-not $bash) {
    $cmd = Get-Command bash.exe -ErrorAction SilentlyContinue
    if ($cmd) { $bash = $cmd.Source }
}
if (-not $bash) {
    Write-Error "Git Bash not found; install Git for Windows (build.sh needs bash)."
    exit 2
}
# Forward every argument unchanged; bash sees them as $1.. of build.sh.
$posix = @($args | ForEach-Object { "$_" -replace '\\', '/' })
& $bash "$root/build.sh" @posix
exit $LASTEXITCODE
