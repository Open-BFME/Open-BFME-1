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
| `launch_fleet.sh N B F M A R C K` | start N file-lane, B big-body, F finish-lane, M mid-lane, A anonymous-lane, R reviewer, C class-lane and K blocker-lane seats plus the watchdog and harvest loop (defaults `6 0 2 8 15 2 4 1`) |
| `seat.sh ENGINE SEAT` | one seat loop; engines `luna`, `lunamid`, `lunaclass`, `lunablock`, `lunafin`, `lunabig`, `lunaanon`, `lunareview`, `lunaxhigh*`, `solhigh*`, `grok*`; SESSION_CAP default 150 min; a session that fails inside `FLEET_ABORT_SECONDS` (300) backs the seat off 60 s doubling to 30 min (30 min at once on a usage-limit message) |
| `pick_file.py` | claim a dump file, ordered by landed-neighbour density (46.5% vs 19.5% land rate) |
| `pick_big.py` | claim one large body (1000..2500 B), fewest prior attempts first then largest; the `*big` seat stays on it for up to 3 sessions while its stash keeps changing |
| `pick_mid.py` | claim 3 bodies of 300..2500 B, largest first, from the file with the densest landed C++ neighbourhood; skips boundary suspects |
| `pick_class.py` | serve the warmest vtable that still has a servable dump slot (`eligibility.servable`: leases, touched cooldown, attempt cap, dead ends, suspect boundaries, `unlocked.txt`) and print its slot table; there is no permanent claim file |
| `pick_blocker.py` | cluster open bodies whose latest verdict names the same `blocker=` family (`tools/blockers.py`) and hand the largest cluster to one session; `--report` lists every family |
| `vtable_rank.py` | build the vtable ranking `pick_class.py` reads; game classes have no RTTI |
| `pick_finish.py` | claim near-landed stashes (`N MIN_SCORE MAX_ATTEMPTS COOLDOWN_DAYS`, default `2 0.9 5 2`); ranks on the compiler's measurement of the stash (`tools/finish_measure.py`, cached in `build/finish_measured.json`), the author score only orders what is not measured yet; luna seats get bodies under 5 verdicts and not re-banked in 2 days, `lunaxhigh` seats get the hard set too (`0 0`) |
| `pick_anon.py` | claim anonymous dump bodies ranked by expected bytes (size x (1 + evidence warmth): callers via thunk, strings, vtable, layout); skips boundary suspects |
| `tools/carve_unclaimed.py` | derive deterministic anonymous candidates from uncovered `.text` using REL32 starts, advisory Ghidra starts, and decoded terminal/padding evidence; regenerate after landings |
| `pick_review.py` | claim banked bodies 0.5..0.95 for a reviewer seat (identity, layout, convention, pins) |
| `harvest.py`, `harvest_loop.sh`, `ledger_prep.py` | the only VCS path while seats run: repair mechanical ledger states under the lock, commit, rebase in `build/wt`, push |
| `ledger_watchdog.py` | keep the ledgers landable between harvests |
| `retire_seat.ps1` | kill one seat's loop and only its own session; call with `-Seats @(...) -Stems @(...)` via `-Command`, never `-File` |
| `harvest_alarm.log` | `build/fleet_logs/harvest_alarm.log`: one line per harvest that needed hands; the 5 MB `harvest.log` hid a three-day wedge |
| `launch_unblock.sh TAG BRIEF` | one lead-directed session with a hand-written brief (pre-resolved callees, a lever to apply) |

Measured on 2026-09-04: origin/master gained +1.05 pp recovered-as-source in
the 12 h after launch against +0.59 pp in the 12 h before. Bytes per session by
lane are in the orchestrator's notes; mid and class lanes beat the file lane.

## Cooldown and aborted runs (2026-09-21)

A run cools down only the targets it WORKED ON. `probe.py`, `re_log.py` and
`add_match.py` append the address to `build/fleet_runs/<run>/touched.txt`
(`fleet_run.mark_touched`); `eligibility.recent_run_rvas` reads it. The rest of
a brief returns to the queue when the lease ends. Measured over this host's real
sessions before the change: the file lane worked on 33 of 375 briefed bodies
and cooled all 375 for 48 h.

A run that exits non-zero inside `FLEET_ABORT_SECONDS` having touched nothing
is recorded `status: "aborted"` and cools nothing. On 2026-09-18 a usage limit
produced 2,680 such runs in a day on one host; they had 1,796 bodies on
cooldown when the fleet stopped, against 375 from real sessions.
