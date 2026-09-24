# File-lane picker and brief eligibility, 2026-09-24

## Investigation and reproduction before production changes

Current master was `b2b06e0f59847aa71e8807cb2ea8f6c48ef3ce18` in a clean isolated
worktree. The relevant baseline passed 133 tests and 19 subtests. Checked-in
`seat.sh` calls `pick_file.py 12`, then `brief.py --dump ... --max-size 2500`.
The picker counts every `.asm` ledger row; the brief removes a row above 2500
bytes or with a latest dead-end verdict. A failed brief creates no runner claim,
so the unchanged picker may return the same file on the next seat cycle.

A temporary fixture invoking the real picker twice returned the same file even
though `eligibility.open_dumps` reported zero open rows. Invoking the real brief
entry point on that fixture exited with `brief: no live dump targets`. Three
new production-entry-point regressions are red before a fix: 12 dead-end rows,
12 oversized rows, and 11 live rows plus one dead-end row all meet the picker's
12-row minimum. On the current ledger, 11 of 84 `.asm` files with at least 12
raw rows have fewer than 12 rows that the brief could serve. None currently has
zero; the fixture proves the failure mode, not a measured live retry frequency.
The main checkout's old `seats.log` and unmarked SQLite database were inspected
read-only; no current fleet controller was observed. They do not establish
fleet cost or throughput.

## Proposed narrow fix

Use `eligibility.load_rows` and `eligibility.open_dumps` with the current
exact-RVA verdicts to build the file pool from rows the brief can actually
accept. Apply the same max-size argument as the file seat's brief; pass that
argument explicitly from `seat.sh`. Count unique body RVAs per file, and keep
its existing landed-neighbour ranking and active-file exclusion. A file with
fewer than the requested live bodies is not selected. Other lanes and explicit
RVA assignments remain available for its remaining bodies. The picker remains
advisory; `brief.py` filters again and `fleet_run` atomically claims the final
brief targets before launch.

Alternatives considered: skipping only completely empty files would leave
misleading file scores and the underfilled 12-body threshold; changing the
brief's global rules would also affect explicit assignments and other lanes.
Moving this entire picker outside the lock is a separate lock-scope change
without a measured benefit here. No new eligibility definition, lease state,
or retry policy is needed. Compatibility needs no state migration. The
expected benefit is removal of these empty or underfilled file selections;
it is not a claim about accepted bytes or live fleet throughput.

## Separate adversarial review of the proposal

**Proceed with the narrow pool correction.** The size bound must be shared
with the actual seat invocation, or a later seat edit can recreate the bug.
The active-file check must still inspect all `.asm` rows: a worker may own a
row that was landed or retired after launch. Unique RVAs must determine the
minimum so aliases cannot make an 11-body file look like a 12-body file.
The current ledger has no duplicate `.asm` RVA, so that guard is conservative.
The brief may still filter a row after the pick because ledger and verdict
writers do not take the picker lock; the runner's live-row/size check and
atomic claim remain authoritative. This patch must not claim a transactional
picker-to-brief snapshot or cross-worktree ownership. It must not apply the
attempt cap or touched cooldown to explicit briefs as a side effect.

Reading latest verdicts under the existing picker lock could lengthen its
hold. Measure the same real entry point before and after; if the lock cost is
material, revise the snapshot arrangement instead of accepting a throughput
regression for an unmeasured live issue. Tests should cover filtered and
unfiltered files, existing active-file exclusion, and the real brief failure.
No acceptance, relocation, identity, or publication gate changes.

## Review revision after the first isolated replay

The first patch passed its targeted tests but scanned all 169,279 rows twice
under the picker lock. In the same isolated `strace` replay its hold grew from
0.53 s to 1.09 s. Timed production helpers attributed about 0.44 s to
`open_dumps` over the whole ledger. This is a material local regression, so
the first version is rejected. The revised code gives `open_dumps` only the
`.asm` rows already identified by the file picker; the canonical predicate
still decides retirement and size, while the full ledger scan remains for
landed-neighbour ranking and active-file exclusion. Recheck the real picker
hold and affected tests before accepting this revision. These local timings
say nothing about live fleet throughput.

## Post-implementation adversarial review and verification

The revised diff changes only file-lane advisory selection and passes the
same maximum size to picker and brief. It does not alter `brief.py`, SQLite
ownership, cgroup lifetime, touched cooldowns, exact matching, relocations,
identity checks, or publication hooks. The picker still scans every `.asm`
row for an active owner, even when that row is now too large or retired. Tests
exercise that negative case, a duplicated RVA, no-live and underfilled files,
and a full 12-body file. A ledger or verdict change after selection can still
make the brief empty; the brief then fails before any claim, and a subsequent
seat cycle takes a fresh snapshot. A worker cannot rely on this advisory
picker for launch authority.

Three paired local production-entry-point replays gave the old file picker
0.538–0.574 s under the shared lock and 0.627–0.665 s wall time. The revised
picker held the lock 0.658–0.662 s and took 0.747–0.755 s wall time. This
roughly 0.1 s local cost is retained for the confirmed selection correction;
no fleet-wide throughput gain or loss is inferred. The old picker chose
`d_0001466e.asm`, which has 16 raw but only 7 briefable rows. The revised
picker chose `d_0015f070.asm`; the real brief produced 12 live targets totaling
5,452 bytes, with one retired row removed, in 1.892 s. A dummy worker launched
through the real `fleet_run.py` in this isolated worktree and exited in 1.124 s;
the 12 claims were all released, no target was touched or cooled, and the
cgroup was verified empty. This measured dispatch path used no paid worker.

The isolated lock replay also measured current mid pre-lock startup 0.085 s,
forced wait 0.307 s and hold 1.457 s, versus review preparation before the
lock 1.501 s, forced wait 0.304 s and hold 0.479 s. Those are local timings;
mid's two-phase design remains deferred because its contiguous-group and
stale-ledger rules need a separate review. There is no active fleet controller
here and no live dispatch/cost measurement.

The affected integrated suite passed **223 tests and 22 subtests**; three
`test_delta_sources.py` parameter cases were intentionally skipped because
they target the pre-push argument chunker. The real compiler dependency test
ran. `check_csv` passed on 169,279 function rows and 88,974 symbol rows;
Python compilation, shell syntax, and diff checks passed. No baseline was
changed. The system `/usr/bin/python` lacks Capstone on this host, while the
test virtual environment has it; a controlled fleet rollout must use an
environment that can generate real briefs. No live controller, old claim
registry, or deployed script copy was changed. Deploy this seat-script change
only on a controlled restart, following the existing coordination/cgroup
migration procedure in `docs/throughput-tools.md`.
