# Retire seats safely: kill each seat's loop, then only the codex session that loop owns
# (matched by engine+seat in the loop command and by the dump stem in the session command).
param([string[]]$Seats, [string[]]$Stems)
for ($i = 0; $i -lt $Seats.Count; $i++) {
  $seat = $Seats[$i]; $stem = $Stems[$i]
  $eng = $seat -replace '\d+$',''; $num = $seat -replace '^\D+',''
  $loops = Get-CimInstance Win32_Process -Filter "Name='bash.exe'" | Where-Object { $_.CommandLine -match ("seat\.sh " + $eng + " " + $num + "$") }
  foreach ($l in $loops) { Stop-Process -Id $l.ProcessId -Force -ErrorAction SilentlyContinue }
  $sess = Get-CimInstance Win32_Process | Where-Object { $_.CommandLine -match 'gpt-5\.6-luna' -and $_.CommandLine -match $stem -and $_.Name -match 'timeout|node|codex|cmd' }
  foreach ($p in $sess) { Stop-Process -Id $p.ProcessId -Force -ErrorAction SilentlyContinue }
  "retired $seat ($stem): loops=$(@($loops).Count) session-procs=$(@($sess).Count)"
}
