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

For manual finish work, `next_work.py` prints a `finish_measure.py --one` start
command. It compiles the banked body, resolves a stale stash-header symbol to a
symbol actually defined in the object, and prints a follow-up `probe.py`
command using the same Python environment. The reported quality is diagnostic:
the chosen symbol can still be the wrong identity, and only the normal strict
byte, relocation, identity and publication gates can land the body.

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

`tools/fleet_run.py` claims carry a direct PID, lease expiry, and (for new
runs) a Linux cgroup-v2 path. The record status and a dead PID alone never
prove a detached descendant stopped. Automatic reclaim requires an expired
lease, positively empty `cgroup.events`, and no live recorded direct PID; a
no-PID pre-exec claim additionally needs its intact starting record and
`launch_phase=preexec`. Legacy rows with no cgroup path remain busy until a
stopped-fleet, snapshot-bound named release. Takeovers retain their proof in
the `releases` table.

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
it; judge it by headline pp, not by commits.

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
and every alternative in `targets/game/reverse/attempt_history/0xRVA/<sha256>.json`. The
existing `targets/game/reverse/attempts/0xRVA.cpp` path remains the preferred candidate, and
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
python tools/shape_search.py game/path/Foo.cpp 'MANGLED' 0xRVA \
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
reservation. The wrapper checks those targets against the live ledger. Each
run is assigned to its own Linux cgroup-v2 unit before the worker's exec gate
opens. Claims are released only after `cgroup.events` reports `populated 0`;
timeout uses `cgroup.kill` for the whole unit. Only bodies recorded in
`touched.txt` receive post-run cooldown, after contained descendants stop.
Reads, pickers and lease recovery never kill a worker. An expired claim is
reclaimable only when its cgroup is verified empty and its recorded direct PID
is absent. A pre-exec claim with no PID is recoverable only from a valid
starting record with touch tracking enabled. For contained claims, the DB path,
record path and record run ID must agree; missing or inconsistent metadata
stays busy. Old claims with a NULL cgroup path remain busy automatically.

To release a cgroup-less legacy claim, first stop every seat and direct
launcher, verify that no worker remains, then bind the explicit operator
assertion to a fresh read-only coordination snapshot:

```sh
python3 tools/fleet_run.py --coordination-status
python3 tools/fleet_run.py --release RUN_ID --reason 'workers verified stopped' \
  --stopped-fleet --state-sha SHA
```

Old `seats.log` records have no reliable owner or date. Keep them as
conservative exclusions until a controlled restart. Do not overwrite scripts
beneath running controllers. Stop all old seats and direct launchers, verify
that no worker is still alive, then inspect the old log without changing it:

```sh
python3 tools/fleet_run.py --coordination-status
python3 tools/fleet/reconcile_legacy.py
```

The claims database now has a durable UUID marker at
`build/fleet_coordination.json`. If the database is missing, replaced, corrupt,
or has lost its claims schema, every new claim fails closed. A fresh checkout
initializes on first use. For an existing checkout with an unmarked old
database or only historical `seats.log` assignments, stop every controller
and worker, inspect the status and live processes, then initialize from the
exact `snapshot_sha256` printed by the status command:

```sh
python3 tools/fleet_run.py --init-coordination --stopped-fleet --state-sha SHA
```

The cgroup rollout also requires a delegated writable child under Linux cgroup
v2, including `cgroup.procs`, `cgroup.events`, and `cgroup.kill`. If delegation
or an event read is unavailable, launch and automatic release fail closed; no
process-group fallback is used. A marked database from before cgroup claims
reports `requires_cgroup_migration`; perform the same stopped-fleet, snapshot-
bound initialization before the runner adds the nullable `cgroup_path` column.
The migration validates all existing marked schema fields and leaves old
NULL-path claims busy for named, guarded operator release. On Windows this
runner intentionally rejects launches until a native Job Object containment
path has separate implementation and integration tests.

Migration preserves old claims and release rows. It refuses a live recorded or
claimed PID. A run directory with no database, or a marker with a
missing or mismatched database, requires restoration of the original database;
initialization cannot erase that uncertainty. Keep old controllers stopped
through the subsequent legacy reconciliation. This is a per-checkout cutover,
not a fleet-wide reset or a reason to overwrite scripts under running seats.

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

## Per-file link check (2026-09-29)

`python3 tools/link_check.py <source-or-object>...` answers, in seconds, whether
one file would link cleanly (the LINKED test of `tools/link_census.py`) without
running link.exe. It compiles the source when its object is stale, reads the
object and checks it against the index the last census wrote
(`build/link_census/link_index.pkl`):

- **unresolved**: a name no other object defines and no import library in the
  toolchain would supply for an import retail has (`link_census.excused`).
- **duplicate**: link.exe compares each definition with the first one in link
  order and reports the pair when either is exclusive (an ordinary section or
  a `/Gy` NODUPLICATES COMDAT); two inline copies fold silently.
- **comdat**: a COMDAT copy that is not retail's body. Retail truth decides
  where the symbol has a retail address (bytes and relocation targets checked
  against the image); otherwise the first copy in link order is the one kept.
- **addresses**: a hard-coded image address in the source (`link_debt.py`).
- **selected** (`wrong_selected` in `link_status.csv`): a name the file defines
  or references whose definition the link KEEPS is proven not retail's: the
  kept COMDAT copy fails retail truth, or two objects define the name and the
  kept one is not the ledger owner's. The census reads the kept definition
  from a `/MAP` relink; the check uses the census's holder, else the first
  definer in link order. A name with no retail address or owner counts
  against no one.

It prints the file's LINKED bytes at the census and after your change. The
census stays the record; the check is a preview and can be stale by whatever
other files changed since.

`--next` ranks names by the bytes their fix alone would link; the daily
census publishes it as `link_queue.csv`, served by `link_check.py next`.

No index yet? It is written by `python3 tools/link_census.py --build --history`
(the daily census) or `--status` on the census's own tree.

`python3 tools/data_check.py <source>` checks the current object's initialized
data against retail, using ledger anchors and addresses independently derived
from retail references. It compares initializer bytes and relocation targets;
masking a pointer does not prove it. Exit 0 means all examined data is proved,
1 means a contradiction, and 2 means insufficient evidence (including BSS or
unplaced sections). Run it when defining a global or table. It does not prove
the declared extent, alignment, startup behavior, or whole-program linkage.

A data-only TU (ZH's `Common/Language.cpp` defines only `OurLanguage`) owns
its globals in `targets/game/reverse/data_rows.csv`: land one with
`python3 tools/add_data_match.py <symbol> <address> --va|--rva <source> --model M
--evidence TEXT`. The size must be proven from the object. An initialised symbol
must equal retail with every relocation on retail's pointer; a zero-filled one
must be zero at its own address, since MSVC orders a TU's .bss by name.
check_csv validates the ledger. `./build.sh <source>` and the full gate re-verify
it (`tools/data_rows.py`).

`python3 tools/reloc_ledger.py` (~2 min, after `tools/dump_relocs.py --all`)
writes `build/reloc_ledger/`: one typed row per reference into or pointer
held by .rdata/.data/STLPORT_, with provenance (compiler relocation of a placed
object, dump analysis, EH/FieldParse structure, vftable slot, use-proven) and
the data partition (object-defined, linker-built, scaffold; size proven or
inferred). A pointer scan only fills `review_scan.csv`; nothing links from it.
`review_types.csv` lists data names whose declared type disagrees with a use,
a structure or another copy. `python3 tools/data_scaffold.py [--link-check]
[--trial-link]` turns the scaffold items into COFF objects (retail bytes,
DIR32 at every non-scan row, one label per address, other names as weak
aliases), verifies them at retail and moved placements, and links the whole
program without /FORCE. Scaffolding is never progress.

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

## Publisher (tools/publisher.py, 2026-10-05)

The publisher is the only writer of master. Seats submit units; isolated
builders gate them with a pinned checker; the publisher fast-forwards master
only to a tip whose signed receipt names exactly the current head. Design,
limits and commands are in the module docstring. It replaces
`landing_service.py` for publication: that service ran the candidate's own
pre-push, inherited credentials into unit `verify` commands, and slept ten
minutes after every pass. The file imports nothing from this repository;
BFME2 copies `publisher.py`, `publisher_load.py` and `publisher_pre_push.sh`
unchanged.

Capacity at 300 units/h. The gate model is 60 s + 20 s per unit per batch
(Fable's 8 minutes per 20-unit batch); `publisher_load.py simulate`, 6 h:

| red units | blame lines | builders | units/h | p95 wait |
|---|---|---|---|---|
| 1% | no | 4 | 290 | 16 min |
| 3% | no | 8 | 291 | 15 min |
| 3% | yes (90%) | 6 | 283 | 14 min |
| 10% | either | 8 | 130-146 | over 3 h, queue grows |

One builder tops out near 180 units/h even with no red units. Red units cost
the most, so the checker should print `PUBLISHER-BLAME: <path>` for each path
it fails. The publisher then probes the blamed unit alone instead of
bisecting. Operators above 20% red lose half their rate and the spare
capacity (slow lane).

Scope rules (2026-10-06). Every unit declares the globs it may touch
(`submit --scope GLOB ... [--forbid GLOB]`, or `--scope-from-diff`); there
are no exempt paths, so ledgers, headers, build files, tools/ and .githooks/
must be declared like sources. Two units with overlapping scopes are never in
flight together (serialized, not rejected). A unit whose rebased diff leaves
its scope is rejected with the paths (`out-of-scope`). After `retry_limit`
(3) gate failures with the same approach (its +/- lines outside ledger files)
for the same target, an equivalent submission is refused (`retry-limit`)
until the blobs in the target's non-ledger scope or the checker change.

Row scope (2026-10-06). Row ledgers are scoped by row: `functions.csv` by
`target_rva`, `symbols.csv` by `name`, `data_rows.csv` by `address`, and the
other union-merged ledgers by whole line. `--scope-from-diff` and the shim emit
tokens such as `targets/game/reverse/functions.csv#0x00401000`. Units on
different rows overlap only where they share another path. A unit that touches
a file others `#include` (by file name, transitively, as
`header_dependents.py` decides) overlaps every unit that touches one of those
includers. Over the last 7 days of master (7,168 commits, 22% touching
`functions.csv`), 16% of commits overlap another within 15 minutes under row
scope, against 62% under whole-file scope. Replaying those footprints at 300/h
(3% red, blame lines) gives 238/h with p95 48 min on 6 builders under row
scope, against 121/h with p95 228 min under whole-file scope.

Builders and re-verification. Builders are registered per host and operator
(`publisher.py builder --state S NAME --operator OP [--command JSON --home DIR]`)
and sign receipts with their own key. Remote builders fetch candidates from
`stage_remote`. Every high-risk green (headers, baselines, whitelists,
gen_asm/gen_small, checker paths), a `reverify_share` sample of the other
greens, and every lone red are rebuilt by a different operator. Builders that
lose the vote, or whose receipts do not verify, are quarantined
(`quarantine.json`). Several publishers may run against one branch: a push is a
fast-forward compare-and-swap, and the loser regates.

Promotion fixtures. `promote` refuses without exploit and benign fixtures and
without `ledger_cmd`. Generate the set on the head being promoted:
`python3 tools/publisher_fixtures/make_fixtures.py tools/publisher_fixtures/bfme1/cases.json OUT --rev <sha>`,
then promote with `--fixtures OUT` and
`ledger_cmd="bash tools/publisher_fixtures/bfme1/ledger.sh"`
(`PUBLISHER_FULL_GATE=1` adds the full byte gate).

Judges. `tools/judges.json` (protected) is the repo's only judge allowlist:
gpt-6-astra, gpt-6.1-sol, claude-opus-5-5 and claude-fable-5-1. `tools/judges.py`
is the only runner: `judge_call(judge, prompt)` runs only those judges and
records the model the CLI itself says answered, never one the answer or a
`model=` note names; `counted()` decides in process, and a record read back from
disk counts only through `verify_record(record, key)` (signed with
`JUDGE_RUNNER_KEY`). The audit panel (`tools/audit/panel.py`), the name lane's
`ask`, `model_routing.judge_allowed` and `variant_search` all go through it.

### Cutover runbook (admins)

1. **Publisher host.** It holds the bot's push credential: a GitHub App or
   deploy key that is the only bypass actor on master. Builders run as
   another OS user (`builder_prefix`, e.g. `["sudo","-u","builder"]`) with no
   credential. Build hosts need the toolchain and a warm `build/`
   (`clean_keep`).
2. **Init.**
   `python3 tools/publisher.py init --state /srv/pub --target <origin URL>
   --set 'checker_paths=["tools",".githooks","build.sh","build.cmd"]'
   --set 'toolchain_paths=["inputs/toolchains"]' --set builders=6
   --set 'submit_remote="<origin URL>"'`, and `--set gate=...` to the
   pre-push call `landing_service.DEFAULT_GATE` makes.
   The gate runs the bundle's `.githooks/pre-push`, overlaid on the candidate
   and hidden from `git diff` (skip-worktree).
3. **Operators.** Run `publisher.py operator --state /srv/pub <name>
   --rate <units/h> --burst <n> [--infra]` once per operator fleet. Send the
   printed key file to that fleet's host only. The key identifies the
   operator; commit authors are ignored.
4. **Checker.** Keep the exploit fixtures (`fixtures.json`: patch plus
   `reject`/`pass`) on the publisher host. Set `ledger_cmd` to the full-ledger
   check. Then run `publisher.py promote --state /srv/pub <master sha>
   --fixtures <dir> [--accept-diff <file>]`. A later verifier commit counts
   only after its own promotion; landing on master does not make it trusted.
5. **Shadow.** Before the flip, drain into a scratch branch (`--set
   'branch="publisher-shadow"'`) for a day. Compare its receipts and
   rejections with direct pushes.
6. **Ruleset (the flip).** In repository rules, add a branch ruleset on
   `master` that restricts updates, blocks force pushes and deletions, and
   bypasses only the publisher bot. `refs/submit/*` stays writable, as
   `refs/claims/*` is today. Prove it: a `--no-verify` push and a GitHub API
   fast-forward of master must both fail. Until then a direct push still
   lands, and the publisher only logs `foreign_push`
   (`test_no_verify_direct_push_is_only_stopped_by_the_admin_ruleset`).
7. **Fleets.** Replace `git push` with `python3 tools/publisher.py submit
   --operator <name> --key-file <key> --remote origin --scope <glob> ... <base>..HEAD` and read
   `PUBLISHER-SUBMITTED`/the unit id. Hosts that still push can install
   `tools/publisher_pre_push.sh`, which turns a push to master into a
   submission. The harvest pipeline's API fast-forward must move to `submit`.
8. **Run.** `publisher.py drain --state /srv/pub` under a supervisor;
   `status` prints queue depth per operator, p50/p95 wait and builders busy.
   Exit criterion: queue depth flat for 24 h at peak load.
9. **Rollback.** Delete the ruleset; seats push as before. The journal and
   receipts stay; on restart the publisher settles a half-done publication.

### Rollout: shadow, then enforce (2026-10-06)


Two stages, each switched by one committed file, `targets/game/reverse/publisher_mode` (`off`,
`shadow`, `enforce`). The pre-push hook reads it at the remote tip, never
from the outgoing commits, so a push cannot change its own mode, and the
file is a protected path (Verifier-Change trailer).

**Stage A, shadow (shipped).** The last line of `.githooks/pre-push` runs
`tools/publisher_hook.py` after every other check has passed. The push
goes ahead unchanged. A detached process waits until the push has landed
(the remote-tracking ref contains the tip), then submits the same range to
`refs/submit/<operator>/<unit>` with its diff as scope. It cannot fail or
slow the push; it only logs to `.git/publisher-hook.log`. The hook step
costs about 0.3 s on Windows. A submission takes 0.7-1.1 s in the
background against a local remote. The operator is the git author name,
lowercased, with runs of other characters turned into `-`. In v1 it is
UNAUTHENTICATED: the envelope is signed with a key anyone can derive from
that name (`auth=none-v1`). An operator an admin later issues a real key
to (`publisher.py operator`) can no longer be impersonated that way.

The publisher host runs `tools/publisher_service.py`, one state directory
per repository. In shadow it fetches `refs/heads/master` and
`refs/submit/*` from origin and writes nothing there. It publishes to
branch `publisher-shadow` of a local bare mirror, and its results go to
the mirror's `refs/publisher/results`. The shadow checker follows master
(auto-promotion), so a red unit is one that passed the seat's own hook but
failed the pinned gate. When the service is idle it resets the shadow
branch to master (`resync` event), so drift from units red here or
commits pushed without a submission does not pile up. Per-unit rows
(latency, verdict, red rate over the last 100 gated units, queue depth) go
to `metrics.csv`, one row per minute to `queue.csv`, and the day's
go/no-go to `health-<date>.json`.

**This host** (`publisher_state\` next to the worktrees; both repos;
setup already run):

    publisher_state\run_publisher.cmd      start both (supervised, restarts on exit)
    publisher_state\stop_publisher.cmd     stop both after the current step
    py -3 publisher_state\bfme2\bin\publisher_service.py status --state publisher_state\bfme2
    py -3 publisher_state\bfme2\bin\publisher_service.py health --state publisher_state\bfme2 [--hours 24]

`run_publisher.sh` does the same from Git Bash. Builders: 8 for BFME2 and
4 for BFME1, each gate at `BUILD_POOL=2`, so at most 24 compiles at once
on 24 cores. A builder's HOME is its scratch dir, so `publisher_gate.py`
hard-links its `~/.cache/open-bfme-build.lock` to the host's. Full builds
(more than 8 TUs: header, toolchain and wide units) therefore serialize
with every other clone's full builds on this PC. Per-file verifies take
no lock and compete for cores only. Fleets building on this PC slow the
gates; nothing else interferes. BFME2's `reference/open-bfme-1` comes from
`state\toolchains\<gitlink sha>`, a clone the service provisions for every
head and for any unit that moves the gitlink.

**Measured on this PC** (the 12 master commits ending at 427e5d5309
replayed through the real gate, 4 cold builders, scope serialization on,
all green): 4 batches, 246 s wall (176 units/h), 67-79 s per gate
including a 40,931-file first checkout, p95 latency 245 s. That is about 4x
this fleet's 45 units/h. For BFME2 the same run without serialization
gave 1,618 units/h and with it 147.

**When this PC is off** nothing is lost. Shadow: seats push as before and
submissions pile up on `refs/submit/*`. On restart they are ingested in
landing order, and the gap shows as queue depth, not as latency. Enforce:
pushes are refused and queued in the same way; master stops moving until
the service is back, then drains the backlog.

**Go/no-go for stage B** (`health`, 24 h window, all must pass): at least
100 units finished; queue at most 40 at the end, mean depth in the last
quarter at most 10 above the first, and at least 95% of enqueued units
finished; p95 latency at most 30 min; red rate at most 3%, with every red
unit looked at; at most 5% did not apply; a heartbeat row for 95% of the
minutes; at most 5 errors and no refused receipt. Get GO on two
consecutive days that include a fleet peak.

**Stage B, enforce (prepared, not run).** In order:

1. Promote the checker by hand (`publisher.py promote --state DIR <master
   sha> --fixtures ...`). Auto-promotion stops in enforce.
2. Land a commit that sets `targets/game/reverse/publisher_mode` to `enforce` (Verifier-Change). From
   then on the hook submits synchronously and refuses the push (exit 3)
   with `PUBLISHER-QUEUED <unit>` and how to check:
   `python3 tools/publisher_hook.py status <unit>` (queued / pending /
   landed / rejected, read from `refs/publisher/results` on origin). A seat
   that keeps working on top of queued commits gets them left out of its
   next unit, which is ordered `after` them. After a rejection: fix,
   `git pull --rebase`, push again; identical bytes are the same unit.
3. Within a minute the service sees the mode, fast-forwards origin master
   itself, deletes the submit refs it ingested and publishes results.
4. Admin, so `--no-verify` and other accounts cannot bypass the hook. This
   is classic branch protection: it covers only branches matching
   `master`, so `refs/submit/*` and `refs/claims/*` stay writable, and the
   existing "Protect master" ruleset (no force push, no deletion) stays as
   it is. `enforce_admins` is required because two other org admins push.

       gh api -X PUT repos/Open-BFME/Open-BFME-1/branches/master/protection --input - <<'JSON'
       {"required_status_checks": null, "enforce_admins": true,
        "required_pull_request_reviews": null,
        "restrictions": {"users": ["Ancalgonn"], "teams": [], "apps": []},
        "allow_force_pushes": false, "allow_deletions": false}
       JSON

   Prove it: a push to master from any other account fails, and a push to
   `refs/submit/x/y` from that account succeeds. Ancalgonn is also the
   publisher's account. If a fleet on this PC pushes as Ancalgonn, only
   its hook stops it (enforce mode). A dedicated bot account in the
   restriction list closes that gap.

**Rollback.** Land `targets/game/reverse/publisher_mode` = `shadow` (or `off`). The service keeps
origin as its target until the units queued under enforce have landed,
then goes back to the mirror. Remove the protection with
`gh api -X DELETE repos/Open-BFME/Open-BFME-1/branches/master/protection`.

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

## Agent tool verbs, similarity, variant search, reference snapshots (2026-10-06)

Agents call these fixed verbs rather than writing one-off scripts. Each verb takes
typed arguments (RVAs are hex, sizes are decimal bytes) and prints JSON with `--json`
(the `ghidra_refdb.py` verbs always print JSON). None of them writes the ledger.

| Verb | Answers |
|---|---|
| `python3 tools/ghidra_refdb.py fn DB RVA\|NAME` | Ghidra's function at or containing an RVA: boundary, body ranges, name, signature |
| `python3 tools/ghidra_refdb.py callers DB RVA` / `callees DB RVA` | call-graph edges |
| `python3 tools/ghidra_refdb.py xrefs-to DB RVA` / `xrefs-from DB RVA` | every reference, with kind and operand |
| `python3 tools/ghidra_refdb.py strings DB RVA` | strings a function references |
| `python3 tools/ghidra_refdb.py switch DB RVA` | jump-table targets in case order |
| `python3 tools/ghidra_refdb.py type DB NAME` | a Ghidra data type with members / enum values |
| `python3 tools/similar.py near RVA [--of GAME] [--json]` | the matched functions (any game) this body most resembles, with their sources |
| `python3 tools/next_work.py --tier similar` | an unclaimed function served next to its nearest matched neighbours |
| `python3 tools/variant_search.py SOURCE SYMBOL RVA SIZE` | model-proposed rewrites, compiled in parallel and scored by the gate |
| `python3 tools/model_routing.py route --size N` | which models may take this task, best first |
| `python3 tools/model_routing.py judge --model M` | whether M is on the protected judge list |
| `python3 tools/build.py SOURCE` | the byte gate: the only acceptance |

### Reference snapshots (Ghidra, read-only)

The analysed Ghidra project (BFME1, BFME2 and RotWK) is exported to one SQLite file
per binary with tables `functions`, `xrefs`, `strings`, `data`, `switches`, `types` and
`meta`. Snapshots are not committed. Local path: `build/refdb/<program>.sqlite`, for
example `build/refdb/bfme1_lotrbfme.exe-37ec98.sqlite`. Published path: a GitHub release
tagged `refdb-YYYYMMDD` carrying `refdb-<program>-<content12>.sqlite`, where
`content12` is the first 12 hex digits of `meta.content_sha256`. Fetch it with
`gh release download refdb-YYYYMMDD -p 'refdb-*' -D build/refdb`.

Build one with:

    python3 tools/ghidra_refdb.py export --project <dir>/witchking.gpr \
        --program bfme1_lotrbfme.exe-37ec98 --program rotwk_game.dat-c9e1ec

The exporter copies the project first and never opens the owner's copy. It needs
Ghidra 12.1 and JDK 21 (`GHIDRA_INSTALL_DIR`/`JAVA_HOME`, or under `inputs/toolchains`).
Two exports of the same project state give byte-identical files and the same
`content_sha256`. Check `meta.executable_sha256` against the repo baseline before you
trust its RVAs. The shared project's BFME1 program was imported from a
binary that differs from `inputs/baselines/.../lotrbfme.exe` in 190 bytes; its
function entries agree with `ghidra_functions.csv` (78,501 of 78,506).

Snapshot names are Ghidra's. They are not identity evidence.

### Name sync into Ghidra

`ghidra_refdb.py sync-plan DB` lists the ledger names that may go into the canonical
project. A name qualifies only if it has evidence behind it:

- `export`: the PE export table names it.
- `ilt`: the ILT oracle confirmed it (an `ilt-verified=` note on a matched row).
- `reloc`: a byte-true call proved it (`targets/game/reverse/reloc_names.csv`, `identity=real`).

A matched row on its own does not qualify, because the agent picked that name.
Placeholders never sync. Only `ilt` may replace a name that is not a placeholder.
`sync-apply` writes the plan into the canonical project with
`tools/ghidra/apply_names.java`, tagging each function `refdb-sync tier=...`.

### Similarity instead of BSim

`tools/similar.py` builds the cross-game index from masked instruction n-grams (2-
and 3-grams with registers and large constants masked, stop-words dropped, Jaccard
ranking) in about 25 s for 124k functions. It does not need the BSim database that
a full decompile of every function would require. `tools/ghidra/bsim_query.java`
stays for WorldBuilder matching. Other games are added with
`SIMILAR_GAMES="bfme2=EXE,FUNCTIONS[,LEDGER];rotwk=EXE,SNAPSHOT"`.
