# Fleet reservation lifecycle review — 2026-09-24

## Decision

Revise lifecycle A before treating automatic claim release as safe. In the
reviewed snapshot `4f0ac014861dce417ab5a7170c68f1412ca5a34f`, claim creation is
atomic within one checkout and release is owner-scoped, but process liveness
tracks only the direct worker PID and original POSIX process group.

On normal exit, `tools/fleet_run.py:159-169,396-415` releases claims when the
original process group is empty. A descendant can call `setsid()`, close the
captured streams, and keep writing after its parent exits. On Windows,
`surviving_group()` always returns false. The expired-lease path also trusts
only the direct PID; if the supervisor dies, a surviving descendant is
unnoticed after that PID exits.

## Reproduction evidence

Scratch-only scripts were run from the audit worktree, with all runner state in
`TemporaryDirectory` instances. The commands and output paths are:

- `python3 build/reproduce_detached_descendant.py` →
  `build/detached-reproducer-output.json`: production `fleet_run.execute()`
  returned 0 while a detached child remained alive; `surviving_group=false`,
  `active_rvas=[]`, the claims table was empty, and the release reason was
  `worker exited`.
- `python3 build/reproduce_expired_lease_with_detached_descendant.py` →
  `build/expired-lease-reproducer-output.json`: after SIGKILL of the runner and
  exit of its direct worker, an expired lease was absent from `active_rvas` and
  a replacement owner claimed the same RVA while a detached descendant was
  alive.
- `python3 build/verify_cgroup_descendant_tracking.py` →
  `build/cgroup-descendant-test-output.json`: a blocked worker was moved into a
  temporary delegated cgroup before it forked. Its detached grandchild stayed
  in that cgroup after the direct worker exited; `cgroup.events` stayed
  `populated 1`, and a timer writing `1` to `cgroup.kill` brought it to
  `populated 0`. The empty temporary cgroup was removed.

These tests do not touch fleet coordination databases or source files. The
cgroup check covers accidental `setsid()`/stdio escape, not hostile same-UID
code that deliberately migrates itself to another writable cgroup.

## Design gate

**Linux cgroup v2 — proceed.** Create a per-run cgroup, then persist its path
inside the SQLite claim transaction before starting any worker. Launch a tiny
bootstrap that blocks before workload code, move and verify its PID in
`cgroup.procs`, check `/proc/<pid>/cgroup` and `cgroup.events`, then release it
to `exec` the requested command. This closes the pre-assignment fork race;
children remain accounted for after `setsid()`.

Keep the cgroup path queryable after supervisor loss. Claims remain busy while
`populated` is nonzero or cannot be read; reads by `eligibility` and claim
recovery must never kill an active writer. The normal supervisor keeps its
timer active until the whole cgroup is empty and may use `cgroup.kill` at the
configured cap. A separate reaper/operator action is required to kill an
orphaned populated cgroup. On normal completion, wait for `populated 0`, then
snapshot `touched.txt` and release the SQLite claim before removing the empty
cgroup. If setup fails after claiming but before workload code starts, stop the
blocked bootstrap, verify the unit empty, release the claim, and remove the
cgroup; otherwise retain unknown ownership.

For supervisor-crash recovery, record that touch tracking is live before
launch. `recent_run_rvas` must read the run's `touched.txt` dynamically or
refresh the snapshot after the cgroup empties. Do not cool every brief target:
untouched siblings must return to the queue. Add a fast nonzero direct-exit
test where a contained descendant touches an RVA later; after the unit empties,
the touch must prevent `aborted(record)` from suppressing that body's cooldown,
while an untouched sibling gets no cooldown.

The user-owned cgroup interface is not a security boundary against hostile
same-UID code. The supported worker contract must prohibit intentional
migration to another writable cgroup or use of an external manager that moves
the process. If cgroup creation, assignment, or querying fails, reject the
launch; do not silently fall back to the process group.

**Windows Job Objects — defer implementation and activation.** The current
Windows branch cannot observe descendants. Implement a Job Object with
breakaway disabled, suspended process assignment, active-process querying, and
job-wide timeout termination only with native Windows integration tests. Until
then, reject Windows launches before the worker starts.

**Cgroup-less expired-lease guard — proceed as a separate narrow mitigation.**
For legacy claims with no containment path, reclaim an expired claim only when
the run record is terminal (`finished`, `failed`, or `aborted`) and the direct
PID is gone. `starting`/`interrupted` records remain busy for operator review.
A verified-empty cgroup overrides stale run status. This protects an interrupted
supervisor without leaving successful runs as permanent claims, but it does
not fix normal-exit release of a detached child; lifecycle A is incomplete
until Linux containment is in place.

In the isolated audit worktree, this narrow guard is implemented in
`tools/fleet_run.py`. Its tests keep expired `starting`/`interrupted` records,
missing records, unknown PIDs, and live PIDs busy; a terminal record plus a
dead PID remains reclaimable. The real supervisor-crash regression creates a
detached descendant, kills the runner, waits for its direct child to exit,
expires the lease, and verifies that the same RVA cannot be claimed by a
replacement while the descendant lives. Existing ordinary nonzero-exit and
missing-executable tests still verify that a live supervisor releases its own
completed or failed launch. After rebasing to `6b73ffcfa9c862d3`, the relevant
fleet and throughput tests pass: 65 tests and 19 subtests. This mitigation is
not the full containment implementation.

## Remaining scope

Claims databases are per checkout; different worktrees/clones do not exclude
one another. This is acceptable only if all coordinated seats use one
canonical checkout. Legacy reconciliation also has a fail-closed recovery gap:
after cutover, a late old-style `->` event remains busy and the reconciler
refuses to append a closing `done` event even after a stopped-fleet check.
Provide a guarded second reconciliation or document a verified manual closure
procedure.

The primary checkout's supplied log contains two old `seat pick ->` lines and
one finished historical run record. The supplied process inventory found no
active fleet runner or local claims database; these artifacts do not establish
current backlog or another worktree's state.
