# Conversion throughput tools

These tools retain work between agents and shorten compiler experiments. They
do not change what counts as a conversion: the normal source, relocation,
identity, commit and push gates still apply. Neither a masked match nor an
author's partial score proves a function is correct.

## One eligibility predicate, leases, and the anonymous lane (2026-09-15)

`tools/eligibility.py` is the single answer to "is this address open work,
what has been tried, who is on it". `next_work.py`, every `tools/fleet/pick_*.py`
and `tools/brief.py` import it. Rules: a dump row (gen-dump note or `.asm`
source) is open; a dead-end verdict retires it; a deferral never does; a
banked stash outlives a later `blocked`; busy means a live `fleet_run` lease
or, until stopped-fleet reconciliation, an old seat `->` line in `seats.log`. The append-only
`build/fleet_*_claimed.txt` files are no longer read: a body a run touched
waits 48 h (`recent_run_rvas`, from the immutable run records) instead of
being claimed for ever. Measured before the change: `pick_finish.py` saw 147 of
381 servable near-misses; `next_work.py` had no stash tier at all.

The finish tier caps attempts (`finish_bodies(max_attempts=5)`) and honours a
cooldown on the stash header date (`cooldown_days=2`, the one cross-host
signal git carries). Measured 2026-09-16 over the last 800 verdict rows: 10
first attempts, 259 on bodies with eight or more prior verdicts, 550 on bodies
with six or more -- every default seat drew the same 270 near misses by
score, which is why the headline rose 0.47 pp in 20 hours instead of more.
`eligibility.hard_bodies()` is the hidden complement (272 bodies, 73 KB); the
`lunaxhigh` finish lane serves it uncapped, the luna lane gets the 77 that
are still cheap. `seat.sh` now runs the tracked `tools/fleet/pick_*.py`
directly; the untracked `build/pick_*.py` copies were never refreshed on other
hosts.

Finish measurements are diagnostic queue scores, never acceptance receipts.
`finish_measure.py` keeps a result only while the stash symbol and body, ledger
row and retail extent, probe logic, and the experiment store's verified compiler
object receipt remain current. A missing prerequisite, compiler failure or
timeout gets a short retry window. Qualified positive results rank ahead of
unmeasured bodies; valid zero-quality and failed probes rank behind them. Four
target briefs reserve one place for an unmeasured candidate when available.
The 0.9 author-score admission floor is unchanged because a lower floor has
not demonstrated an additional viable finish body.

The finish and anonymous pickers prepare candidates outside
`build/.fleet_claims.lock`, then recheck a bounded shortlist under that lock.
`fleet_run` still atomically claims only the live targets in the final brief;
parallel pickers may prepare the same candidate, but cannot launch duplicate
ownership in one checkout. Anonymous final validation reads the whole current
ledger so a newly claimed range excludes an overlapping carved candidate.
The context pack publishes its retail call index atomically under a separate
cache lock; the first run after this change rebuilds the old cache format.
In one isolated local replay, finish preparation took 1.00 s and final lock
region 0.40 s, while anonymous preparation took 7.03 s and final lock region
1.25 s, with no lock wait. These timings demonstrate shorter local picker
lock holds, not a measured fleet throughput gain. Deploy at a controlled seat
restart; do not replace tools beneath running controllers.

`tools/fleet_run.py` claims are leases: pid + expiry (`FLEET_LEASE_SECONDS`,
default session cap + 30 min). A lease is reclaimed only when expired AND the
pid is gone; an unknown pid is never reclaimed. Takeovers are recorded in the
`releases` table with the reason.

Lanes added to `seat.sh` / `launch_fleet.sh` (args: file big finish mid anon
review; defaults since 2026-09-16 are 10 0 2 8 15 2, no net new seats):

Measured 2026-09-16 over 1,500 verdict rows: the land rate is flat (~7%) from
100 B to 2,500 B and zero above, so bytes per attempt scale with size (4 B for
bodies under 100 B, 94 B for 1,000-2,500 B); 183 of that day's 348 landings
were under 100 B and delivered 7 KB. `pick_anon.py` therefore ranks by
`eligibility.expected_bytes` (size x (1 + warmth)), `pick_mid.py` serves
300-2,500 B largest first, and the finish lane drops to 2 seats because the
capped finish pool is ~30 bodies. Both pickers skip `boundary_suspect`
addresses: a `blocked` verdict whose evidence says the address is not a
function boundary (301 such bodies had been re-served for 559 sessions).

- `lunaanon` -- `pick_anon.py N min max`: anonymous dump bodies ranked by what
  the evidence pack can prove (strings 3, vtable 2, callers 2 each up to 3,
  layout 1, neighbours 1). A body with warmth 0 and two prior attempts waits;
  a body with a lead is served however often blind sessions bounced off it.
  The brief permits an opaque address-keeping name and prohibits a guessed one.
- `lunareview` -- `pick_review.py N lo hi`: banked bodies scoring 0.5..0.95
  whose latest verdict is a deferral. The reviewer checks what the byte gate
  cannot see (identity, layout, calling convention, callee names, wrong pins),
  repairs the stash, lands or re-banks with a corrected evidence line. Trial:
  measure landed bytes per reviewer-hour with `fleet_report.py` before
  expanding it.

The pilot is 20 anonymous bodies through `lunaanon` with `lunareview` behind
it; judge it by headline pp against `docs/baseline-2026-09-15.md`, not by
commits.

## Exception-frame bodies: detection and mechanical levers (2026-09-15)

57% of the open dump bytes (973 KB of 1.70 MB) carry a C++ exception frame,
and the blocker tags seats write most often are EH codegen. The evidence pack
now detects the frame from the bytes (fs:[0] registration, EH state stores,
by-value temporary saved-esp, state reset to -1) and prints an `EH FRAME`
block with the levers from docs/shape_levers.md that apply. `tools/eh_levers.py
SRC.cpp` turns the four mechanical levers (throw() per callee, /EHsc toggle,
`_STLP_NO_EXCEPTIONS`, nothrow `operator delete[]`) into a shape_search
choices file so their combinations are compiled under the usual budget before
a seat hand-iterates. Validated end to end on the 0.93 banked
PushButtonImageDrawThree body (7 trials compiled; that body's remaining
diff is not EH, which the run established in 3 minutes instead of a session).

## Retained attempts and compiler experiments

`re_log.py record ... partial --stash FILE --score N` preserves the prior body
and every alternative in `reverse/attempt_history/0xRVA/<sha256>.json`. The
existing `reverse/attempts/0xRVA.cpp` path remains the preferred candidate, and
only moves to a higher author score. A lower-scored submission cannot destroy
a better one. The log's `score=` describes that preferred file; `submitted=`
describes the new alternative. History is evidence, never compiled progress.
To try an archived alternative, extract its `source` JSON field to a scratch
`.cpp`. An incorrect optimistic score can still rank poorly: inspect the
alternatives and use actual compiler output when choosing a starting body.

`probe.py` now shares persistent objects under `build/experiments/`, checking
source, compiler binaries, options, environment, header-search directories,
dependency hashes and object hashes before reuse. Recompilation writes a new
object, leaving an older object intact for other readers. Unknown include roots
or implicit `CL` options disable reuse. Failed compilation diagnostics are
retained but are **not reused**, because a failed compile may not disclose all
its dependencies. Successful nonmatching compiles are cacheable.

`build/experiments.sqlite` records results by target bytes, emitted bytes,
relocation symbols and addends. Probe reports how many earlier experiments
produced that result, even when the source spelling changed. This is shared
within a checkout, not a distributed fleet cache. No cache object is an
acceptance receipt. Literal/opcode changes no longer default to a misleading
register-mirror diagnosis.

## Bounded source search

Write a JSON list of explicit source alternatives. Each `before` must occur
exactly once; edits cannot overlap. The original is always tested first.

```json
[{"before": "int a = loadA(); int b = loadB();",
  "after": ["int b = loadB(); int a = loadA();"]}]
```

```sh
python tools/shape_search.py Code/path/Foo.cpp 'MANGLED' 0xRVA \
  --size 101 --choices build/choices.json --max-trials 32 --plateau 8 --seconds 600
```

Only supply alternatives justified by the function's behavior; this example
requires the loads to be reorderable. The tool does not prove semantic
equivalence. It tests finite combinations, rejects assembly injection, retains
each source and result, and stops after the trial budget, a plateau without
improvement, or a masked shape match. The time budget is checked between
compiles. Best candidates and the unchanged starting body live in a unique
`build/shape_search/` directory. Restore a chosen body to its intended source
path and run normal verification; scratch paths can affect C++ code generation.

## Donors, handoffs and scheduling

```sh
python tools/source_donors.py --refresh --max-size 1000
python tools/source_donors.py 0x00089CE0 101
```

The index groups existing C++ by retail operand shape. Briefs include matching
donor sources when an index exists; lookups reject changed source or retail
hashes. Refresh includes new landings. Donors suggest layouts and compiler
options, but their callee pins and constants must be checked per target.

Class briefs now receive the picker's entire NOTE and slot table via
`--note-file`. The ZH header lookup searches GeneralsMD with a real regex word
boundary, skips forward declarations, and reads the actual class definition.
Named, warm classes sort before larger anonymous tables; this ranking
still needs a measured comparison. Latest-verdict parsing honors retractions
and ignores addresses merely cited in evidence. A refuted boundary does not
automatically refute every body with the same normalized instruction shape.

Record `blocker=NAME` in attempt evidence for a shared missing type, callee or
compiler construct. `fleet_report.py` groups these explicit reports, so a lead
can assign one investigation and return the result to affected bodies.

## Run history and claims

New `seat.sh` sessions run through `tools/fleet_run.py`. Each run gets a unique
ID, an immutable brief, a filtered transcript, elapsed time, starting Git head,
targets and actual process exit code in `build/fleet_runs/<id>/`. The historical
log filename becomes a pointer; an existing transcript is preserved under a
unique `.before-<id>` name. Transcripts retain the existing diff/line filtering;
they are not complete raw agent event streams. Tokens and cost remain unknown
when the command emits plain text; transcript size is not a usage measure.

The wrapper exports `BFME_RUN_ID`; `add_match.py` and `re_log.py` attach it to
new records. Picker output is advisory. All lanes consult one active-RVA table,
and the wrapper atomically claims only the targets that survived brief filtering
immediately before launch. A failed brief or launch cannot strand a picker
reservation. The wrapper checks those targets against the live ledger and
releases the entire run's claims when its worker exits. Only bodies recorded in
`touched.txt` receive post-run cooldown. A supervisor crash, unknown PID or
surviving POSIX process group keeps its claims for operator review. After
establishing that the entire worker group stopped:

```sh
python tools/fleet_run.py --release RUN_ID --reason 'worker confirmed stopped'
```

Old `seats.log` records have no reliable owner or date. Keep them as
conservative exclusions until a controlled restart. Do not overwrite scripts
beneath running controllers. Stop all old seats and direct launchers, verify
that no worker is still alive, then inspect the old log without changing it:

```sh
python3 tools/fleet/reconcile_legacy.py
```

The dry run prints outstanding tokens, the exact log SHA, and the number of
run claims. Investigate and release named claims only after verifying their
workers have stopped. With the old controllers stopped and zero claims, run
`python3 tools/fleet/reconcile_legacy.py --apply --stopped-fleet --log-sha SHA`
using the SHA just printed. The tool refuses a changed log or any remaining
claim, appends scoped closing events, and writes an atomic local cutover
marker. Repeat the dry run to confirm zero outstanding tokens before starting
new controllers through the usual copy-and-launch workflow. If an old
controller later writes an ownership event, the reader honors it again. Do
not apply this migration to a live fleet. The SQLite registry is per checkout;
separate writer clones have independent claims and still rely on the normal
Git publication guards.

This is not a full scheduler replacement. Big-lane retries require a changed preferred
source body, a live partial of at least 0.5, and a remaining dump. Merely
changing the score/date no longer buys another session.

## Publication and measurement

Harvest stages fleet evidence and cited C++ sources explicitly. It refuses an
existing index or changed shared dependencies instead of incorporating another
writer's work. A separate harvester lock serializes publication; the landing
lock is released during fetch, rebase, worktree checking and push. Validation
runs the **rebased worktree's** checker. If a worker advances the ledger while
publication runs, local synchronization is deferred and its edits are retained
for the next harvest. Shared-checkout source writes remain advisory; a complete
immutable source-receipt publication protocol is still follow-up work.

```sh
git fetch origin master
python tools/fleet_report.py --ref origin/master
python tools/fleet_report.py --freeze 24
```

Reports distinguish published ledger attribution from a fresh byte gate or
compute cost, and deduplicate overlapping aliases within each run. Freeze
copies a deterministic size-stratified sample of available partials with source
hashes and retail identity into a unique `build/evaluation_sets/` directory.
Use the same starting set and equal budgets for a controlled comparison. The
tool does not itself run paid model sessions or infer tokens from log sizes.

Deploy tracked fleet scripts through the existing copy-and-launch procedure
when seats are restarted. Do not overwrite scripts underneath running shells.
`launch_fleet.sh` builds the donor index before new seats start. The probe,
brief and attempt changes are ordinary tracked tools; existing copied seat
controllers will not acquire all new behavior merely because Git advances.

## Validation on 2026-09-04

Targeted tests cover preserved attempts, terminal decoding, conservative cache
invalidation, concurrent cache requests, relocation-sensitive history, failed
worker processes, claims, bounded search and publication using isolated real
Git repositories. A real MSVC probe compiled once and reused its object on the
next invocation. A two-trial smoke test deliberately changed an existing donor
to `/Od`; search selected `/O2`, recovering its known 101-byte masked shape
from the 204-byte variant. This validates the search mechanism, not a new
conversion. The donor index contained 39,452 rows and a 24-body evaluation set
was frozen in scratch.

The broader suite also exposes existing failures unrelated to these changes:
`test_next_work::test_corrupt_ledger` omits `build.py` from its fixture;
`test_pin_consistency::test_the_gamewindow_colour_setters_are_reported` assumes
a live defect still exists. Readability tests cannot collect on native Windows
because they call `os.geteuid()`. Do not describe that broader suite as green.
Fleet-wide accepted bytes per compute dollar and speedup magnitude remain
unmeasured; a controlled run is the next evaluation step.


## Donor triage observed on 2026-09-16

An anonymous owner is not itself a reason to discard a measured donor. Keep an
address-derived owner, verify each callee and field offset independently, and
use the donor for compiler shape. Examples landed during the conversion
campaign: 0x002E7410 (225 B) from 0x002E7530, 0x0071C9C0 (397 B) from
0x00733000, and 0x0046F6F0 (206 B) from its inverse at 0x0046F800.
`source_donors.py` supplies exact operand-shape hypotheses. When that pool is
dry, existing `neartwin_scan.py` and `fuzzy_twin_scan.py` can supply a small
number of size-tolerant leads. `fuzzy_twin_scan.py` now applies `eligibility.py`
and active claims itself; recheck a result before assignment because another
worker may claim or land it after the scan. Its argument parser handles
`--help` without scanning, and repeated retail masks are cached for one run.
Filter `neartwin_scan.py` results before assignment. Both masks are heuristic,
and some donors contain assembly lifts. Such donors are evidence to inspect,
not clean C++ to copy. A scan of 562 operand-shape hits left only five below
RVA 0x009F0000; most remaining hits were compiler cleanup funclets. A large
hit count must not be presented as a healthy ordinary-function queue.

A worker's final source must be the exact source it last compiled and probed.
If a timebox stops an experiment after an edit, bank the earlier measured
snapshot or record `blocked`. Do not attach the previous snapshot's score to
the newer edit. The campaign rejected an audio candidate on this check: its
last measured draft had 713 differing bytes, while its later bank failed to
compile. An untracked new source or an unstaged deleted bank in a worker
worktree is expected when the orchestrator owns staging; it is not a reason
to rearrange a verified conversion merely to satisfy the worker's index.

The size-tolerant `fuzzy_twin_scan.py` donor pool uses `progress.py`'s shared
per-row naked/emit classifier. It supplies every matched row in each candidate
source, including rows below the requested minimum size, so genuine C++ in a
mixed file is retained. A `.cpp` suffix alone is not donor evidence: the
`0x002FB170` assembly lift previously generated three misleading ScriptActions
leads. Active claims and retired addresses still use `eligibility.py`.

`tools/callees.py RVA SIZE` also lists direct calls through absolute IAT
slots, resolving DLL/export names from the PE import directory through
`pin_consistency.import_table()`. This is independent of ledger names.
For example, the audio body at `0x006AEF20` calls `_AIL_open_stream@12`,
`_AIL_stream_ms_position@12` and `_AIL_stream_loop_count@4`; their slots
are not unknown ABI targets merely because the direct-call inventory lacks
them. The report keeps slot VAs separate from function RVAs. It does not
resolve arbitrary register or vtable calls, and export names do not prove
argument types. Instruction-boundary tests cover embedded opcode bytes,
truncation, repeated imports and non-IAT absolute calls.
