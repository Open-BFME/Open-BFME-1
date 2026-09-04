# Fleet orchestration instruments

Tracked copies of the scripts that ran the 2026-09-04 luna fleet (40 codex
`gpt-5.6-luna` sessions at reasoning effort max). They execute from `build/`,
which is gitignored scratch, so the orchestrator copies this directory to
`build/` before launching: `cp tools/fleet/* build/`.

| Script | Role |
|---|---|
| `launch_fleet.sh N B F M` | start N file-lane, B big-body, F finish-lane, M mid-lane seats plus the watchdog and harvest loop |
| `seat.sh ENGINE SEAT` | one seat loop; engines `luna`, `lunamid`, `lunaclass`, `lunafin`, `lunabig`, `solhigh*`, `grok*`; SESSION_CAP default 150 min |
| `pick_file.py` | claim a dump file, ordered by landed-neighbour density (46.5% vs 19.5% land rate) |
| `pick_mid.py` | claim 3 bodies of 300..1000 B from the file with the densest landed C++ neighbourhood |
| `pick_class.py` | claim the warmest vtable (most slots landed, some still dumps) and print its slot table |
| `vtable_rank.py` | build the vtable ranking `pick_class.py` reads; game classes have no RTTI |
| `pick_finish.py` | claim near-landed stashes (score 0.9+) |
| `harvest.py`, `harvest_loop.sh`, `ledger_prep.py` | the only VCS path while seats run: repair mechanical ledger states under the lock, commit, rebase in `build/wt`, push |
| `ledger_watchdog.py` | keep the ledgers landable between harvests |
| `retire_seat.ps1` | kill one seat's loop and only its own session; call with `-Seats @(...) -Stems @(...)` via `-Command`, never `-File` |
| `launch_unblock.sh TAG BRIEF` | one lead-directed session with a hand-written brief (pre-resolved callees, a lever to apply) |

Measured on 2026-09-04: origin/master gained +1.05 pp recovered-as-source in
the 12 h after launch against +0.59 pp in the 12 h before. Bytes per session by
lane are in the orchestrator's notes; mid and class lanes beat the file lane.
