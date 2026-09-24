# Byte-match workflow audit, 2026-09-24

This audit began from clean commit `528e5c104b61290a6ecc8ba4f75bc4081817e49c`
in an isolated worktree. Snapshot `5d5409134799007e2ce61d5a16cb1df881d01912`
was treated as a list of hypotheses. The baseline relevant tests passed: 84 tests
and 19 subtests. At that initial snapshot, the unrelated full game build was red
with 44 byte mismatches and 86 DIR32 inconsistencies. Those counts are historical
and are not a current-master build result. The workflow changes did not alter
game-code bytes or weaken the byte gate. The local fleet logs and SQLite claims
were inspected read-only. No live controller was restarted, no production
reservation database was edited, and no paid fleet A/B run was performed.

## Findings and evidence

| Area | Result | Evidence and scope |
|---|---|---|
| A. Reservation lifecycle | Confirmed and repaired in the published runner path; controlled rollout still required | Mid/finish picks recorded several RVAs as ownerless `seat pick ->` entries, while `seat.sh` completed only `$STEM`. A later real-process reproduction also disproved the original process-group liveness assumption: a `setsid()` descendant could outlive normal release. The per-checkout coordination database now fails closed on loss, and new Linux runs use per-run cgroup-v2 containment. Legacy rows, old logs, separate checkout databases, and platform rollout remain guarded limits. |
| B. Finish ranking and freshness | Confirmed correctness defects | `finish_measure.rank_key` sorted every measured entry, including compile failures, ahead of an unmeasured viable stash. The picker did not filter such entries. The cache omitted symbol, ledger/target, toolchain/dependencies and probe logic; transient failures persisted until the stash body changed. Concurrent whole-file writes could lose results. These are diagnostic measurements, never acceptance receipts. |
| C. Claim-lock scope | Local lock reduction measured for the reviewer picker; fleet impact unmeasured | Isolated instrumentation of production pickers measured a 5.24 s finish lock hold with one probe and about 7.4 s for anonymous evidence preparation. A forced local wait was 2.45 s. A later reviewer-only slice reduced local hold and contended wait but increased single-pick wall time. These results show a local tradeoff, not a measured live throughput gain. |
| D. Repeat classification and blocker tags | Two tertiary naked-queue classification defects repaired; broader blocker policy remains exploratory | `eligibility` already has an attempt cap, quick-look exception, touched-target cooldown and explicit `unlocked.txt`; briefs deliver attempt history, and big-lane retries require a changed fingerprint. Later fixes make the naked-candidate queue use the latest exact-RVA verdict and the existing boundary-suspect predicate. A broad `regalloc` family still does not prove a shared prerequisite; family rotation or automatic cooldown has no measured outcome basis. |
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
pickers, retry policy, blocker grouping, and emitter discovery were deferred
at that checkpoint. A later, separately reviewed reviewer-picker slice is
recorded in [fleet-lock-scope-2026-09-24.md](analysis/fleet-lock-scope-2026-09-24.md).

## Implemented and verified

| Published commit | Change | Verification after rebase |
|---|---|---|
| `f9734c495e04b95a9f24822ae362e9a051ddb33f` | Advisory selections; claims on real brief targets; owner-scoped release and the initial PID/process-group supervision and guarded legacy reconciliation. The later detached-child reproduction showed that this supervision was incomplete. | 75 tests, 19 subtests; ledger and hooks green. |
| `244c15c01955f603b8f67c88f53d1d1fcf4eb113` | Finish ranking and exploration correction. | 21 targeted tests; hooks green. |
| `ded60dacad5a0032aea421ca6df4c4152cd6c9ea` | Current-input finish measurement receipts, transient retry and concurrent locked cache merge. | 79 tests; real MSVC 7.1 probe and used/unrelated-header checks; hooks green. |
| `fd330406005d245bff2718d6af72724ea5ae75e6` | Prepare finish and anonymous picks outside the shared lock; recheck before advisory output; atomic cold call-index cache. | 97 tests, 19 subtests after rebase; `check_csv`, syntax and push hooks green. |
| `80125dc93e` | Coordination UUID marker and fail-closed database/legacy initialization guards; missing or replaced state is not treated as an empty registry. | 89 fleet/throughput/harvest tests and 19 subtests after rebase; `check_csv` and normal push hooks passed. |
| `afea6de317` | Linux cgroup-v2 containment before exec, whole-unit completion/timeout handling, and stopped-fleet migration. Windows launches fail closed pending Job Object support. | Final affected post-rebase suite: 127 tests and 19 subtests; `check_csv` and normal push hooks passed. Real detached-child, crash, late-touch and timeout tests used an isolated delegated cgroup. |
| `9485330c3b` | Move review-picker ranking outside the advisory lock and recheck a bounded exact-RVA shortlist against current predicates. | 10 new production-function tests; integrated suite 163 tests and 19 subtests; `check_csv`, syntax and diff checks passed. Local paired replay results are below. |
| `38c9464088` | Make the tertiary naked-candidate queue use the latest exact-RVA verdict across renamed symbols, falling back to symbol-only history only when no RVA verdict exists. | Combined current-master retry/naked-candidate regression recheck during this refresh: 47 tests passed. This changes classification, not candidate weights or live fleet throughput. |
| `debc058ea85b` | Apply the shared boundary-suspect predicate to short blocked verdicts in the tertiary naked queue, while preserving explicit inspection and later reopening. | Included in the 47-test current-master retry/naked-candidate recheck above; no live throughput effect was measured. |
| `f98e2eb6a4` | Clarify that a blocker family is an exploratory broad tag, not proof of a shared prerequisite; selection and eligibility logic stayed unchanged. | The real dry-run selected the same 12 RVAs before and after; 19 blocker/eligibility tests passed. No family-rotation or shared-lever success rate is established. |

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

The reviewer-picker slice in `9485330c3b` moved whole-pool ranking out of the
advisory lock and rechecked a bounded exact-RVA shortlist. Its ten new tests passed;
the integrated fleet suite passed 163 tests and 19 subtests. Three paired local
entry-point replays reduced review lock hold from 1.364–1.388 s to
0.451–0.471 s and the contended wait from 1.336–1.358 s to 0.425–0.451 s.
The same replay increased single-pick wall time from 1.444–1.475 s to
1.884–1.946 s because it rereads the ledger. Two-picker elapsed time improved
from 2.794–2.809 s to 2.386–2.411 s. These are local dispatch timings, not
accepted bytes or measured fleet throughput. The design, stale-shortlist
checks, and documented single-picker tradeoff are in
[the reviewer lock-scope note](analysis/fleet-lock-scope-2026-09-24.md).

The later naked-queue commits `38c9464088` and `debc058ea85b` fix only the
tertiary conversion queue: latest exact-RVA verdicts take precedence across
renamed dump symbols, and the existing boundary-suspect predicate suppresses
short blocked boundary records from the default draw. They do not change
`next_work.py`, fleet ranking, retry weights or caps, or candidate ownership.
The 47-test recheck covers those paths; annotation and `void` verdicts still
make the shared retry count approximate. See the [identity-aware retry
note](analysis/naked-retry-identity-2026-09-24.md) and [boundary retry
note](analysis/naked-boundary-retry-2026-09-24.md).

The blocker-family commit `f98e2eb6a4` changes operator wording only. Its dry
run preserved the selected twelve RVAs; family rotation, cooldown, and claims
of a shared prerequisite remain deferred until real batch outcomes are
recorded. The [blocker-family review](analysis/blocker-family-2026-09-24.md)
documents why the current tags do not justify changing selection policy.

## Remaining limits and rollout

The claim table is local to one checkout; independent clones have no shared
launch-exclusion guarantee. Picker validation can race a subsequent ledger
write, so the runner checks again before launch; no transaction spans Git
publication and SQLite. The original review's unknown-liveness conclusion was
too strong: its process-group check did not find a `setsid()` descendant. The
two real-process reproducers above showed that the pre-containment runner could
release while that child remained alive. The separate coordination database
guard published as `80125dc93e` prevents silent database recreation; it does
not prove descendant termination.

The cgroup patch now assigns each Linux worker to a delegated cgroup-v2 unit
before opening its exec gate. Real local process tests verified detached-child
tracking, supervisor-crash ownership, and whole-unit timeout kill. Reads do not
kill workers; reclaim and release require an empty cgroup and an absent direct
PID, while cgroup-less historical claims require a stopped-fleet assertion
bound to a fresh status SHA. These tests ran in isolated temporary repositories
and cgroups. No live database, controller, or production fleet was touched,
and no live throughput claim was measured.

Rollout requires a controlled fleet restart and a delegated writable Linux
cgroup-v2 child with `cgroup.procs`, `cgroup.events`, and `cgroup.kill`. If the
host lacks that delegation or a state read is unknown, new launches fail
closed. Windows launches also fail closed until a separately reviewed native
Job Object implementation and integration test exist. The cgroup design
protects against accidental detachment, not hostile same-UID workers that
deliberately migrate themselves to another writable cgroup.

Deploy only at a controlled fleet restart. Do not overwrite scripts under
running shells. First stop old controllers and direct launchers, inspect
`python3 tools/fleet_run.py --coordination-status` and the dry-run
`python3 tools/fleet/reconcile_legacy.py`, and verify every old worker has
stopped. For an existing checkout that needs coordination initialization or
cgroup-schema migration, use the status snapshot's SHA with the guarded
`--init-coordination --stopped-fleet --state-sha` procedure; then reconcile
old log assignments with the dry-run SHA and guarded
`--apply --stopped-fleet --log-sha` procedure in
[throughput-tools.md](throughput-tools.md). Restore a missing or mismatched
marked database rather than initializing over it. The initial audit snapshot
recorded four old log tokens and 23 SQLite claims; a later isolated read found
no local claims database, so those counts are historical and do not describe
current coordination state. No cutover was applied.
After restart, observe claim conflicts, picker lock wait/hold, cache hit rate,
brief waste and landed bytes per worker-hour before claiming a throughput gain.
