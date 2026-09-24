# Naked conversion queue attempt identity, 2026-09-24

Baseline `1d637e1bd76698c15a69446f02d59ef671452584` in an isolated clean
worktree: 45 relevant tests and `check_csv` passed. This finding arose during
the repeated-attempt audit, not from the prior audit snapshot. It affects the
tertiary `list_naked_candidates.py` conversion queue; there is no claim that
the live fleet or default `next_work.py` ranking used this mistaken count.

## Confirmed behavior and path

`list_naked_candidates.drop_logged` asks `re_log.is_deferred` and
`re_log.attempts` for the candidate's **current symbol**. Attempt evidence is
now often written under a proven real name while the byte-true dump ledger
still holds its address-derived placeholder. For the current dump at
`0x002F75D0`, the production function reports one deferred attempt for
`?d_002f75d0@@YAXXZ`, while `eligibility.attempt_counts` reports eleven
non-quick-look verdict rows at the same RVA; the latest RVA verdict is
`blocked`. A placeholder with **no** own verdict can even be classified as
untried despite later real-name deferrals at its RVA, making it eligible
ahead of genuinely fresh work. When the placeholder has an old verdict, the
printed repeat count and JSON metadata understate its history. Among tried
bodies, `select_candidate` does **not** order by attempt count; it retains
its existing size-based yield draw. This is a demonstrated classification and
reporting defect with an observed triage effect, not a measured fleet cost or
throughput bottleneck.

## Proposed repair before code

For candidates with an RVA, ask the existing canonical
`eligibility.latest_verdicts` and `eligibility.attempt_counts` once per
`drop_logged` call. The latest live exact-RVA verdict, regardless of symbol,
decides retirement or deferral. If it is a deferral, use a positive RVA count
as the existing approximate `deferred_attempts` count; a lone quick look has
zero count and remains untried. If it is a resolution, leave
the candidate untagged. Only when no exact-RVA verdict exists, consult a new
tiny `re_log.symbol_only_status(symbol)` accessor into its already parsed
index, preserving genuine three-field symbol-only dead ends and deferrals.
For candidates with no valid RVA, keep the existing `re_log` fallback.

This ordering also means a later exact-RVA partial releases an old three-field
no-match for the same name, as the current queue already does. A latest
different-name exact-RVA no-match retires the placeholder instead of letting
an old placeholder blocked verdict override it. Do not change `re_log`'s
symbol-aware index, global retry caps, queue weighting, `next_work`, or
explicit assignment. Regressions must call the real `drop_logged` function
with a temporary attempt log containing renamed work, a different-name
dead-end, a symbol-only finding, and a retracted boundary.

## Adversarial design review

`eligibility.attempt_counts` is the repository's current RVA count and
excludes short diagnostic looks, but it counts other five-field annotations
and `void` rows. A read-only scan of this log found 173 such annotations and
114 void rows; 47 and 101 RVAs respectively also carry deferrals. Thus the
proposed count is a consistent **existing queue estimate**, not an exact
number of substantial sessions. This narrow repair must not add a hard cap or
change size weights based on it. Renaming could represent new identity
evidence, but a deferral keeps the candidate open, its banked source remains,
and an explicit address assignment still works. A three-field symbol-only
verdict has no proven RVA and must stay symbol-scoped. Using a separate local
parser would create another attempt definition. Load each existing log index
once per candidate batch, not once per body; no throughput benefit follows
from this correction. Exact-RVA matching uses the repository's established
address key,
which does not include size; changing that rule across all queues is a
separate migration and is not justified by this finding.

An independent review found a more serious current failure at `0x003E3F70`:
the placeholder's old `blocked` masks a later exact-RVA `no-match` under the
proven name `Pathfinder::removePos`. It also challenged precedence: the
exact-RVA latest must win over three-field status, or an old symbol-only
`no-match` would re-retire a later exact-RVA `partial`. Revised the design to
make exact-RVA status primary and symbol-only evidence the fallback. **Proceed**
with the narrow queue classification repair and targeted tests.

## Post-implementation adversarial review

The independent diff review caught that a latest short `blocked` quick look
has zero canonical attempts. The first implementation defaulted a missing RVA
count to one and would have falsely moved it out of the untried pool. A
regression reproduced that failure, then the implementation was revised to
tag only positive canonical counts. The address-based verdict precedence and
exact-boundary `void` behavior matched the reviewed design. The broader
annotation and `void` overcount in the shared effort estimate remains a
separate issue and is not used here as a hard cap.
