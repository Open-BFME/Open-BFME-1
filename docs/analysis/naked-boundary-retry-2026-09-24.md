# Tertiary naked queue boundary retry, 2026-09-24

## Confirmed path and proposed repair

`list_naked_candidates.drop_logged` reads the shared latest RVA verdict and
attempt count, but its short-look exception leaves a latest `blocked` boundary
finding in the untried pool when the attempt count is zero. The real log's
`0x005CB600` is one such case: `eligibility.boundary_suspect` is true,
`attempt_counts` is zero, and `drop_logged` keeps it with no deferred marker.
The main anonymous fleet picker already uses `boundary_suspect` to skip the
same address. This is a correctness defect in the tertiary queue's work
classification; no live fleet cost or throughput impact has been measured.

Smallest fix: for an RVA-bearing naked candidate, apply the existing
`eligibility.boundary_suspect(rva, records)` predicate to the current latest
verdict before treating a short deferral as untried. Suppress that candidate
from the default draw, as the fleet picker does. Keep `--include-logged` as
the explicit inspection override; do not retire the RVA, alter attempt
counts, or change candidate weights. A later verdict whose evidence does not
indicate a bad boundary should reopen the candidate automatically.

Invariants: latest exact-RVA evidence wins across renamed symbols; a
three-field symbol-only finding remains symbol-scoped; one short look without
boundary evidence stays in the untried pool; a suspect cannot be drawn by the
default queue but remains inspectable; no game-code or byte-acceptance path
changes. Compatibility requires no migration because this derives directly
from the standing log. Benefit is measured by the queue no longer returning
known suspect boundaries, not by inferred fleet throughput. Tests should call
the production queue function with a temporary log and cover later reopening,
renamed verdicts, and unaffected short looks.

Alternative: count all short blocked verdicts as attempts. That would demote
unrelated diagnostic looks and does not express the specific boundary
constraint. Adding another retry framework would duplicate the shared
eligibility rule. Changing the default fleet picker is unnecessary because it
already uses the predicate.

## Adversarial design review before production change

**Decision: proceed narrowly.** The shared predicate is evidence-text based,
so a later `blocked` note that merely quotes an old suspect phrase could still
be a false positive. This queue must neither add its own phrase rules nor turn
the finding into a permanent dead end. `--include-logged` and a later current
verdict remain ways to inspect or reopen it. It only governs the exact RVA;
another boundary for the same symbol must stay available. A short diagnostic
look without the boundary phrase must remain untried; demoting all short looks
would hide many bodies that had no genuine conversion attempt. The queue is
advisory and does not own a reservation or waive any acceptance gate.

The red production-function regression confirms the target failure: a short
`blocked` verdict under a different name makes `boundary_suspect` true, while
`drop_logged` currently returns the placeholder as untried. Two control tests
already pass: a later non-boundary `partial` reopens the RVA, and a finding at
one RVA does not hide a different boundary. The implementation should make
only that failing case change; broader blocker taxonomy and cap policy are
deferred pending evidence.

## Post-implementation review

The production diff adds one cached log-record read and one call to the
existing shared predicate inside the exact-RVA branch. It does not alter
retirement, attempt counts, queue weights, CLI overrides, worker claims, or
acceptance. The previously red cross-name suspect test is green, as are the
reopening and other-RVA controls and the existing short-look test. The real
`0x005CB600` record now yields `(kept=[], dropped=1)`. The two log snapshots
are read separately and a concurrent append could briefly change this
advisory classification; no reservation or publication depends on it. There
is no evidence of a live-throughput improvement from this local correction.
