@echo off
rem Nightly audit launcher (tools/audit/nightly.py). Advisory: it never pushes and never blocks.
rem
rem Usage:  run_nightly.cmd <dedicated-audit-worktree> [extra nightly.py args]
rem
rem The worktree must be one no agent works in: the red team edits a unit, runs
rem the gate and restores it there. Create it once:
rem     git -C <repo> worktree add <repo>\..\audit-worktree origin/master
rem
rem Windows Task Scheduler, once (cmd prompt; one task per repo):
rem     schtasks /Create /TN "Open-BFME2 audit" /SC DAILY /ST 03:30 ^
rem       /TR "\"C:\path\audit-bfme2\tools\audit\run_nightly.cmd\" \"C:\path\audit-bfme2\""
rem   Task properties: "Run whether user is logged on or not" only if the Codex and
rem   Claude CLIs are logged in for that account; "Stop the task if it runs longer
rem   than 6 hours"; "Do not start a new instance" if one is still running.
rem Output: <worktree>\build\audit\runs\<stamp>\report.md, queue in build\audit\queue.json,
rem log in build\audit\nightly.log.
setlocal
if "%~1"=="" (
  echo usage: %~nx0 ^<audit-worktree^> [nightly.py args]
  exit /b 2
)
set "WT=%~1"
shift
cd /d "%WT%" || exit /b 2
if not exist build\audit mkdir build\audit
git status --porcelain --untracked-files=no > build\audit\dirty.txt
for %%A in (build\audit\dirty.txt) do if %%~zA gtr 0 (
  echo %DATE% %TIME% refusing: %WT% has local changes >> build\audit\nightly.log
  exit /b 2
)
git fetch --quiet origin master >> build\audit\nightly.log 2>&1
git checkout --quiet --detach origin/master >> build\audit\nightly.log 2>&1 || exit /b 2
set PYTHONIOENCODING=utf-8
py -3 tools\audit\nightly.py %1 %2 %3 %4 %5 %6 %7 %8 %9 >> build\audit\nightly.log 2>&1
exit /b %ERRORLEVEL%
