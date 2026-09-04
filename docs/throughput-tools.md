# Conversion throughput tools

These tools retain work between agents and shorten compiler experiments. They
do not change what counts as a conversion: the normal source, relocation,
identity, commit and push gates still apply. Neither a masked match nor an
author's partial score proves a function is correct.

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
new records. All lanes consult one active-RVA table, and the wrapper atomically
claims the whole brief immediately before launch. Claims release when the
worker exits. A supervisor crash does not silently expire a surviving worker's
claims. After establishing that the worker stopped:

```sh
python tools/fleet_run.py --release RUN_ID --reason 'worker confirmed stopped'
```

Existing permanent picker lists remain conservative exclusions during
migration. This is not a full replacement of the scheduler or automatic
reclamation of legacy claims. Big-lane retries now require a changed preferred
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
