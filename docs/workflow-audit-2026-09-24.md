# Byte-match workflow audit, 2026-09-24

This audit began from clean commit `528e5c104b61290a6ecc8ba4f75bc4081817e49c`
in an isolated worktree. Snapshot `5d5409134799007e2ce61d5a16cb1df881d01912`
was treated as a list of hypotheses. The baseline relevant tests passed: 84 tests
and 19 subtests. The original checkout's unrelated full game build was already
red (44 byte mismatches and 86 new DIR32 inconsistencies); this audit did not
change game-code bytes or weaken that gate. The local fleet logs and SQLite
claims were inspected read-only. No live controller was restarted, no production
reservation database was edited, and no paid fleet A/B run was performed.

## Findings and evidence

| Area | Result | Evidence and scope |
|---|---|---|
| A. Reservation lifecycle | Confirmed correctness defect | Mid/finish picks recorded several RVAs as ownerless `seat pick ->` entries, while `seat.sh` completed only `$STEM`. `eligibility.busy_rvas` replayed the log without expiry or liveness. A real-function replay left the other RVAs busy after the run ended; brief failures and filtering stranded picks, while a late `done` could clear a newer mark. `fleet_run` already had atomic run claims, but old log marks obscured eligibility. |
| B. Finish ranking and freshness | Confirmed correctness defects | `finish_measure.rank_key` sorted every measured entry, including compile failures, ahead of an unmeasured viable stash. The picker did not filter such entries. The cache omitted symbol, ledger/target, toolchain/dependencies and probe logic; transient failures persisted until the stash body changed. Concurrent whole-file writes could lose results. These are diagnostic measurements, never acceptance receipts. |
| C. Claim-lock scope | Confirmed local lock hold; fleet impact unmeasured | Isolated instrumentation of production pickers measured a 5.24 s finish lock hold with one probe and about 7.4 s for anonymous evidence preparation. A forced local wait was 2.45 s. This demonstrates avoidable shared-lock occupancy, not a measured live throughput loss. |
| D. Unchanged repeats and blocker tags | Existing controls work; policy concern unmeasured | `eligibility` already has an attempt cap, quick-look exception, touched-target cooldown and explicit `unlocked.txt`; briefs deliver attempt history, and big-lane retries require a changed fingerprint. Recent stalled examples included distinct identity/ABI, reconstruction, translation-unit, and exact-codegen problems. A broad `regalloc` family covered 101 unrelated bodies (40,653 B); that label did not prove a shared prerequisite. |
| E. Existing emitters | Existing discovery route operates | `find_emitter.py` maps symbols to translation units, and `add_match.py` verifies a repointed row. Recent ledger-only verified landings demonstrated the path. No missing discovery subsystem was established. |

The checked-in scripts and deployed copies can differ. This audit confirmed
source behavior and isolated reproductions; its read-only host records do not
establish fleet-wide backlog, cost, collision frequency, or throughput.

## Design decisions made before implementation

The first design considered UUID prelaunch reservations in the existing SQLite
table. An independent review identified token handoff, partial filtering,
controller-PID ambiguity, failed-launch cleanup, cross-worktree state, and
surviving-child hazards. A second adversarial pass rejected that extra state:
selection can remain advisory because `fleet_run.claim` already excludes a
second *launched* worker in one checkout. It may cost duplicate brief work, so
that cost remains a measurement question. The final design claims only the
unique targets actually present in the filtered brief immediately before
`Popen`, validates current open rows and sizes, and releases by exact run ID.
Unknown or surviving processes retain ownership. Old ownerless log entries
cannot be inferred safe online; a dry-run-first, stopped-fleet cutover is the
only reconciliation path. This choice preserves the separate meanings of
selected, assigned, touched and landed.

Finish measurements use a current hypothesis fingerprint plus the experiment
store's verified object receipt, rather than a new include/dependency walker.
Positive measured quality ranks ahead of unmeasured work; valid zero-quality
and failed probes rank behind it. A four-target brief leaves an exploration
slot for unmeasured work. An environmental failure retries after 30 minutes;
a stable poor result remains cached until relevant inputs change. The 0.9
author-score admission floor remains: in one 20-stash sample from 0.8–0.9,
all compiled but none measured at least 0.9 quality. That sample does not
prove a lower floor useless, and it does not justify a policy change.

For lock scope, only the measured finish and anonymous preparation paths moved
outside `.fleet_claims.lock`. The final bounded finish shortlist uses canonical
eligibility and current row sizes. Anonymous final validation reads the full
ledger to reject carved overlaps before choosing from a bounded shortlist.
`fleet_run` still performs the authoritative atomic claim and prelaunch row
check. The context pack's cold call-index cache gained a separate lock and
atomic image-bound publication before preparation was moved. Other lane
pickers, retry policy, blocker grouping, and emitter discovery were deferred.

## Implemented and verified

| Published commit | Change | Verification after rebase |
|---|---|---|
| `f9734c495e04b95a9f24822ae362e9a051ddb33f` | Advisory selections; claims on real brief targets; owner-scoped release, safe supervision and guarded legacy reconciliation. | 75 tests, 19 subtests; ledger and hooks green. |
| `244c15c01955f603b8f67c88f53d1d1fcf4eb113` | Finish ranking and exploration correction. | 21 targeted tests; hooks green. |
| `ded60dacad5a0032aea421ca6df4c4152cd6c9ea` | Current-input finish measurement receipts, transient retry and concurrent locked cache merge. | 79 tests; real MSVC 7.1 probe and used/unrelated-header checks; hooks green. |
| `fd330406005d245bff2718d6af72724ea5ae75e6` | Prepare finish and anonymous picks outside the shared lock; recheck before advisory output; atomic cold call-index cache. | 97 tests, 19 subtests after rebase; `check_csv`, syntax and push hooks green. |

The post-implementation reviews caught and fixed: missing-record and
interrupted leases being treated as dead; a PID-recording transaction race;
surviving POSIX descendants; a mutating migration dry run; a receipt-less
positive cache entry; a late failure overwriting a positive result; stale
retail-image snapshots; an anonymous unlock disappearing during preparation;
and syntactically valid but malformed call-index data. Regression tests invoke
production functions or entry points, including two concurrent runner
processes, six concurrent cold cache readers, brief filtering/failure,
owner-safe late cleanup, carved overlap, changed rows, contention, transient
failure recovery and real compiler dependencies.

An isolated warm replay after the lock change measured finish preparation at
1.00 s with a 0.40 s final lock region, and anonymous preparation at 7.03 s
with a 1.25 s final lock region; lock wait was zero. Total local anonymous
wall time did not improve. These timings support reduced lock occupancy only.
All four correctness commits added **zero game-code bytes**, as expected for
fleet tooling. No claim of increased fleet throughput follows from the tests.

## Remaining limits and rollout

The claim table is local to one checkout; independent clones have no shared
launch-exclusion guarantee. Picker validation can race a subsequent ledger
write, so the runner checks again before launch; no transaction spans Git
publication and SQLite. A worker that deliberately detaches from its POSIX
group, or native Windows descendants after a normal parent exit, cannot be
proved dead by the local Linux tests. Unknown liveness remains busy until an
operator verifies it and releases the named run. Windows process behavior and
live fleet throughput were not measured here.

Deploy only at a controlled fleet restart. Do not overwrite scripts under
running shells. First stop old controllers and direct launchers, inspect
`python3 tools/fleet/reconcile_legacy.py` in dry-run mode, verify every old
worker has stopped, and follow the guarded `--apply --stopped-fleet --log-sha`
procedure in [throughput-tools.md](throughput-tools.md). The local dry run
reported four old log tokens and 23 SQLite claims; no cutover was applied.
After restart, observe claim conflicts, picker lock wait/hold, cache hit rate,
brief waste and landed bytes per worker-hour before claiming a throughput gain.
