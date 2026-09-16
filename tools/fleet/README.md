# Fleet orchestration instruments

Tracked copies of the scripts that ran the 2026-09-04 luna fleet (40 codex
`gpt-5.6-luna` sessions at reasoning effort max). They execute from `build/`,
which is gitignored scratch, so the orchestrator copies this directory to
`build/` before launching: `cp tools/fleet/* build/`.

The throughput update adds immutable run records, cross-lane active RVA claims,
complete class-note delivery, donor briefs and bounded compiler search. See
[the operating guide](../../docs/throughput-tools.md) for deployment and
measurement. Copy scripts only when seats are being restarted; merging a tool
change does not replace a shell that is already executing an older copy.

| Script | Role |
|---|---|
| `launch_fleet.sh N B F M A R` | start N file-lane, B big-body, F finish-lane, M mid-lane, A anonymous-lane, R reviewer seats plus the watchdog and harvest loop |
| `seat.sh ENGINE SEAT` | one seat loop; engines `luna`, `lunamid`, `lunaclass`, `lunafin`, `lunabig`, `lunaanon`, `lunareview`, `lunaxhigh*`, `solhigh*`, `grok*`; SESSION_CAP default 150 min |
| `pick_file.py` | claim a dump file, ordered by landed-neighbour density (46.5% vs 19.5% land rate) |
| `pick_mid.py` | claim 3 bodies of 300..2500 B, largest first, from the file with the densest landed C++ neighbourhood; skips boundary suspects |
| `pick_class.py` | claim the warmest vtable (most slots landed, some still dumps) and print its slot table |
| `vtable_rank.py` | build the vtable ranking `pick_class.py` reads; game classes have no RTTI |
| `pick_finish.py` | claim near-landed stashes (`N MIN_SCORE MAX_ATTEMPTS COOLDOWN_DAYS`, default `2 0.9 5 2`); reads the stash on disk, not only the latest verdict; luna seats get bodies under 5 verdicts and not re-banked in 2 days, `lunaxhigh` seats get the hard set too (`0 0`) |
| `pick_anon.py` | claim anonymous dump bodies ranked by expected bytes (size x (1 + evidence warmth): callers via thunk, strings, vtable, layout); skips boundary suspects |
| `carve_unclaimed.py` | derive deterministic anonymous candidates from uncovered `.text` using REL32 starts, advisory Ghidra starts, and decoded terminal/padding evidence; regenerate after landings |
| `pick_review.py` | claim banked bodies 0.5..0.95 for a reviewer seat (identity, layout, convention, pins) |
| `harvest.py`, `harvest_loop.sh`, `ledger_prep.py` | the only VCS path while seats run: repair mechanical ledger states under the lock, commit, rebase in `build/wt`, push |
| `ledger_watchdog.py` | keep the ledgers landable between harvests |
| `retire_seat.ps1` | kill one seat's loop and only its own session; call with `-Seats @(...) -Stems @(...)` via `-Command`, never `-File` |
| `launch_unblock.sh TAG BRIEF` | one lead-directed session with a hand-written brief (pre-resolved callees, a lever to apply) |

Measured on 2026-09-04: origin/master gained +1.05 pp recovered-as-source in
the 12 h after launch against +0.59 pp in the 12 h before. Bytes per session by
lane are in the orchestrator's notes; mid and class lanes beat the file lane.
