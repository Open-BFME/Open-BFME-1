# Fleet picker lock-scope checkpoint, 2026-09-24

Baseline: current-master `5816c66391`, clean isolated worktree. The earlier
audit at `5d54091347` is a hypothesis, not the diagnosis. Commits
`f9734c495e`, `244c15c019`, `ded60dacad5`, and `fd33040600` already fixed
the reservation/finish issues they addressed and moved finish and anonymous
pool preparation outside `.fleet_claims.lock`. Their behavior still needs
independent review; do not reimplement those changes from the old audit.
Before further fleet edits, 97 relevant pytest cases and 19 subtests passed.
No active fleet seat/controller, deployed `build/seat.sh`, measurement cache,
or claims DB was found on this host. The main checkout has only one old run
record and an old seats log, so these timings do **not** measure live backlog,
fleet cost, or delivered byte throughput.

## Confirmed local lock behavior

`pick_mid.py`, `pick_review.py`, `pick_big.py`, `pick_blocker.py`,
`pick_file.py`, and `pick_class.py` acquire the shared advisory lock before
reading current eligibility and scoring whole pools. The lock remains held
until process exit. `pick_finish.py` and `pick_anon.py` now prepare outside it
and recheck bounded candidates inside. `fleet_run.py` makes the authoritative
atomic lease in SQLite after the brief; an advisory picker result does not own
an address.

An isolated worktree replay used the **real picker entry points**, current
ledger, `--dry` where supported, and `strace -T` on `flock`/process exit.
Uncontended shared-lock holds were mid 1.43 s, review 1.43 s, big 1.11 s,
blocker 1.22 s, class 0.89 s, and file 0.52 s (one run each; class used a
read-only copy of the existing ranking cache). When mid and review started
together, one waited 1.415 s for the other's lock. This confirms **local
contention**, not a fleet-wide throughput bottleneck. For the same mid target,
`brief.py` spent 1.77 s generating a one-body brief outside the lock; a
dummy `fleet_run.py` worker was spawned 1.20 s after runner start, also
outside the picker lock. The real worker ran only `python3 -c pass` in the
isolated worktree and its lease was released.

After the `80125dc93e` coordination guard, a warm current-master replay of
the real review picker still held the lock from `flock` to process exit for
1.376 s. Two concurrent real review picker processes made one wait 1.367 s;
both returned the same advisory RVAs, which remains safe only because the
runner's SQLite claim is authoritative. This replay used the isolated
worktree's test database (automatically initialized from zero old claims) and
`--dry`; it did not touch a live fleet registry or establish fleet impact.
An instrumented `cProfile` run attributed 2.42 of its 2.59 seconds to
`eligibility.finish_bodies`, including 2.04 seconds walking all 169,271
ledger rows through `open_dumps`; profiler overhead makes these unsuitable
as absolute timings. The attribution supports limiting the under-lock pass
to the prepared shortlist while still checking the whole CSV for torn rows.

## Proposed first patch: mid and review, before production changes

Move whole-pool preparation and ranking out of the lock for these two
measured contending pickers. Keep a bounded shortlist (up to 32 ranked mid
groups or 32 review bodies), then acquire the existing lock and re-read the
current ledger, verdicts, attempts, unlocks, busy leases and touched cooldowns
for those addresses. Reuse `eligibility.open_dumps`/`finish_bodies` and the
lane's existing filters; do not create another definition of open work.
Choose the first still-valid group/body, logging only this advisory final
selection. If every shortlisted candidate is stale, return no pick and let
the seat's bounded next loop retry from a fresh pool. `fleet_run` must still
atomically claim the filtered brief targets immediately before launch.

Alternative of removing the picker lock entirely would permit more stale
brief work with no final picker check. Ranking the whole pool again under the
lock preserves the measured wait. A generic scheduler rewrite is unnecessary.
This patch changes no scoring policy, lane size window, attempt cap, lease
rule, publication gate, or old-log migration.

Expected effect: shorter local mid/review lock holds, to be measured with the
same isolated replay. Actual fleet throughput and accepted bytes per worker
hour remain unmeasured. The new tests must call production `prepare`/`finalize`
or CLI entry points and cover a target landed, resized, retired, cooled,
claimed, or unlocked while preparation runs; an exhausted shortlist; a
concurrent picker race; and a runner claim conflict. Test any stale brief with
the real `fleet_run` entry point in a temporary repository, never production.

Adversarial review questions before implementation: Can a previously ranked
group become non-contiguous or cross a new landed range? Can a removed unlock
allow a capped body through? Does `load_rows(rvas=...)` still detect a torn
ledger? Can the bounded shortlist starve all valid work if its first 32
groups race, or spin indefinitely? Could a worker launch between final picker
validation and runner claim? (The runner must reject that claim, not trust
the picker.) Could `seats.log` diagnostics be mistaken for ownership? Are
multiple worktrees' local locks/leases being falsely treated as global?

Decision pending independent adversarial review and the higher-priority
reservation lifecycle repair. The other four picker locks are confirmed by
source and short local holds, but this checkpoint does not yet justify a
multi-lane rewrite; review them as separate small patches if measured
contention remains after the first repair.

## Distinct adversarial pass on the proposal, before code

The initial proposal needs a narrower final check. `pick_mid` currently
derives its group from the ordered eligible bodies in one source file. After
preparation, a member may land, change size or source, acquire a lease, enter
the touched cooldown, reach the attempt cap, become a boundary suspect, or
lose its unlock. A final check of the row alone is insufficient: it must
re-evaluate all of those lane rules for every member and reject the entire
group if any member fails. The current mid lane forms only contiguous sliding
groups of eligible bodies within a source. A newly eligible row between
prepared members changes that group, so final validation must recompute
eligible mids in that source and require the prepared group to remain
contiguous in the current ordered list. Neighbour density is only an advisory
ranking input. `pick_review` must
re-read the stash and enforce both score bounds plus the latest deferred
verdict, lease and cooldown. A changed stash within the score window may be
served, but its original rank is stale; this is an advisory-quality risk,
not ownership authority.

The top-32 limit can return no pick even while lower-ranked work exists.
The seat retries on a fresh scan after a delay, which bounds work in one
cycle but does **not** rule out starvation across repeated contention. Test
the exhaustion path and record this limitation. Two pickers may still print
the same advisory RVA: only `fleet_run`'s atomic brief-target claim prevents
simultaneous ownership while the first claim remains live. A negative test
must keep the first runner active through the second claim. It does not prove
that a second runner cannot launch the same RVA after the first releases it.
A separate checkout has a separate lock and claims DB, so the patch must not
claim cross-checkout launch exclusion.

`eligibility.load_rows(rvas=...)` still reads the whole CSV to check for a
torn row. If the final pass also rescans the whole attempts log, live leases,
run records and stashes, lock occupancy may remain material. Measure the
post-change hold and wait with the same production entry points; if the
region is not meaningfully shorter, revise or defer rather than retaining
complexity without demonstrated local benefit. A ledger publish between
picker validation and worker launch remains possible. `.fleet_claims.lock`
is used by pickers, but ledger, verdict and stash writers use different
coordination; the SQLite claim operation does not take that flock. The
runner's current prelaunch validation checks open identity and size, but
**not** all picker cooldown, cap, or review predicates. Thus the two-phase
picker is an advisory stale-work reduction only, not a transactional
guarantee of lane eligibility at launch. Preserving strict lane eligibility
at launch would require a separate runner-side policy gate with its own
design and tests, not a claim that the picker lock provides it. The existing
byte-match publication gates remain authoritative.

**Independent review verdict: REVISE.** Final validation must cover every
existing lane predicate and preserve mid's contiguous eligible-group rule,
not merely ledger openness; rank a bounded shortlist outside the lock, do no
full-pool scoring under it, and use one bounded final pass with no immediate
retry loop. State the picker/runner race and possible shortlist starvation as
limits, and test simultaneous runner claims with the first owner still live.
Do not implement until the higher-priority reservation repair is complete and
this narrower advisory-only design is reviewed again. If post-change local
lock hold is not materially shorter, defer the added complexity; no live
throughput benefit is established by these timings.

## Revised candidate slice awaiting a second review

Start with `pick_review.py` alone. It has no contiguous-group rule, so this
is the smallest way to test whether moving ranking outside the lock yields a
material local wait reduction. Prepare and rank all currently eligible review
bodies outside the lock. Inside the lock, re-read the current ledger for at
most the top `max(32, n_want)` addresses, the latest verdicts, live claims,
recent touches, and those addresses' stashes. The current target size must
still equal the size in the prepared shortlist, or the old bank may describe
a different extent. Pass the filtered rows to the existing
`finish_bodies` predicate, apply the current `[lo, hi)` score, deferral,
busy, and recent-touch rules, then choose up to `n_want` survivors in the
prepared order. If none survives, return no pick. The next seat cycle takes a
fresh snapshot; no in-process retry loop or alternate policy is introduced.
The prepared order can be stale when a stash score changes. That affects
advisory priority, not the safety of the final lane predicate.

The patch must be measured with the same local `flock` trace before it can
be retained. Review-lane behavior tests must call the real picker on a
temporary checkout and change a candidate between preparation and final
validation: landed, resized, dead-end verdict, score outside either bound,
claimed, or touched. Keep the first runner's claim live while testing a
second runner's rejection. Do not claim that the picker lock closes the
post-selection race; a separate runner-side policy gate would need its own
review. `pick_mid.py` and the four other measured picker lanes stay unchanged
in this first slice. Mid's contiguity and the size of its final source scan
need a separate performance and correctness review.

Decision: **defer implementation pending completion of lifecycle A and a
second adversarial review of this narrower slice.** Local lock contention is
confirmed, but live dispatch and fleet-throughput benefit remain unmeasured.

## Second adversarial review of the review-only slice

The review lane has no group-contiguity invariant, so a bounded exact-RVA
recheck can preserve its current eligibility rules. The final pass must use
`eligibility.load_rows(rvas=...)`, then `finish_bodies` on those *current* rows,
and must compare each current `target_size` with the prepared size. It must
re-read the latest verdict, stash score and non-lift status, busy claims and
recent touches while holding the advisory lock. A formerly selected body that
landed, changed size, lost its stash, left `[lo, hi)`, became a dead end, or
ceased to have a deferred latest verdict must be dropped. The prepared score
must never override these current predicates.

The bounded pass still walks the complete ledger to detect a torn row, and
busy/touch queries can perform filesystem and SQLite reads. Its lock hold may
therefore remain close to the baseline. Retain the patch only if an identical
local entry-point replay shows a material reduction in hold and concurrent
wait, with no extra post-filter picks. Do not extrapolate those timings to
accepted bytes or fleet cost. A fixed top-32 shortlist can temporarily miss
lower-ranked valid work when every shortlisted RVA goes stale; one seat cycle
then returns empty and the next cycle prepares afresh. This is a bounded
quality limitation, not a reason to add an unbounded under-lock retry.

The lock does not serialize ledger writers, other worktrees, or runner claims.
Two pickers can still return the same advisory RVA, and a landing or new claim
can occur after finalization. The runner's existing open-row/size validation
and SQLite transaction remain the launch authority within one coordination
root. A temporary-repository concurrency test must keep owner A active while
owner B attempts the same brief; tests must not imply cross-worktree ownership.
Normal byte, relocation, identity and publication gates remain untouched.

**Decision: PROCEED with one review-picker patch after lifecycle A is
published**, subject to the real-entry-point stale-candidate, concurrent
claim and measured-hold checks above. If the local hold does not improve
materially, revert the experiment and defer the other picker lanes. Mid's
contiguous group and the class/file/blocker lanes need separate designs; this
approval does not cover them.

Lifecycle A is now published at `afea6de317`. The isolated worktree's old,
empty test claims DB reported `requires_cgroup_migration`; a read-only status
showed zero claims, releases, records and live units. We applied the guarded
stopped-fleet migration with that status SHA **only to this isolated test DB**.
No production coordination state or controller was touched. At the new
baseline, the real review picker held the lock 1.385 s in one uncontended
`strace` run. Two concurrent picker entry points had holds of 1.389 and
1.368 s; one waited 1.354 s. Both returned the same advisory pair, as
expected. The affected baseline pytest set passed: 40 tests.

An independent second reviewer examined the revised design and pre-change
tests after lifecycle A published. Verdict: **PROCEED as an advisory-only
experiment**, retaining the patch only if the identical real-entry-point
trace materially reduces hold and wait. The reviewer confirmed the final
predicate list and highlighted four missing negatives: a resolved latest
verdict with an unchanged dump row, an unrelated torn CSV row, exact tie
ordering, and two advisory picks preceding one live atomic runner claim. Those
tests were added before production code changed. The reviewer also required
that an exhausted top-32 cycle be followed by a fresh preparation; that
assertion was added. Cross-worktree ownership, concurrent ledger publication,
and live fleet throughput remain explicitly outside the picker lock's proof.

## Post-change local replay and implementation audit

The review picker now ranks outside the lock, then re-reads at most the top
`max(32, n_want)` exact RVAs under it. The final pass calls the existing
`load_rows`, `finish_bodies`, latest-verdict, busy-claim and touched-run
functions; it compares current target sizes and stash scores with the review
lane's current bounds. It returns only advisory picks, and the runner still
claims the actual filtered brief in SQLite. No new acceptance or publication
path exists. The ten new production-function regression cases passed. The
relevant integrated suite passed **163 tests and 19 subtests**; `check_csv`,
syntax and diff checks passed before commit.

Three paired `strace -ttt -T -e flock` replays of the old and new real picker
entry points on the same isolated worktree produced the same two advisory
RVAs. Uncontended lock hold fell from 1.364–1.388 s to 0.451–0.471 s.
Two concurrent processes had a contended wait of 1.336–1.358 s before and
0.425–0.451 s after. Their combined elapsed time fell from 2.794–2.809 s
to 2.386–2.411 s. An isolated single pick's total elapsed time **rose** from
1.444–1.475 s to 1.884–1.946 s, because the final scan rereads the whole
ledger to detect a torn row. This is a measured local shared-lock improvement
with a real single-picker cost, not a demonstrated live-fleet throughput gain.
The picker keeps the patch because the bounded concurrent replay improved and
the final predicates passed the stale-work cases; a live rollout must observe
reviewer-seat contention and useful work delivered before making a throughput
claim. Aggregate preparation CPU and I/O under more reviewer seats remain
unmeasured.

The independent post-implementation review found one test-portability defect:
the live-runner concurrency case assumed a delegated Linux cgroup on every
host, while the production runner correctly fails closed without one. The
test now checks that capability and skips only the real-process case when it
is unavailable; a separate portable test still exercises two advisory picks
and the atomic direct claim conflict. The reviewer found no production
ownership or fallback defect. Concurrent stash removal can still raise during
`finish_bodies`' two reads; that fails closed and predates this picker change,
so it is left for a separate eligibility review rather than silently treating
an unreadable stash as valid.
