# Conversion campaign, 2026-09-16

Start: 2026-09-16T14:25:20.177606+00:00. Planned duration: 36 hours. Worker cap: ten concurrent
`gpt-5.6-luna` CLI sessions with `model_reasoning_effort="max"`.

## Prior twelve hours

Measured between `c2ec462aa90dfe80132b3e5bf8a09d30cad1ce08` and
`319597e3f1920968bb1bb2883d3808a585d73727` using `python3 tools/progress.py BASE..HEAD`.
The former is the last reachable commit before the twelve-hour cutoff.
There are 488 commits in this range; commit count is not conversion progress.

| Metric | Before | After | Change |
|---|---:|---:|---:|
| Rebuildable non-padding code | 64.85953% | 65.24747% | +37,638 B / +0.38793 pp |
| Authored C++ | 38.76988% | 39.15866% | +37,720 B / +0.38878 pp |
| Generated C++ | 1,166,723 B | 1,166,641 B | -82 B |
| Vendored source | 311,905 B | 311,905 B | 0 B |
| Prebuilt libraries | 1,052,635 B | 1,052,635 B | 0 B |
| Total exact coverage (padding-inclusive denominator) | 8,552,180 B | 8,554,215 B | +2,035 B |

The non-padding denominator is 9,702,173 B. The total `.text` denominator is
13,049,856 B. These percentages answer different questions and must not be mixed.
The live headline includes generated C++ and prebuilt libraries. This campaign
corrected `progress.py`'s stale introductory prose, which described an older
authored-plus-vendored headline; metric computation is unchanged.
Metrics are ledger-derived; byte verification is a separate build result.

Most progress transferred already bounded retail dumps into authored C++.
Only 2,035 B enlarged total exact coverage. The preceding and latest six-hour
segments added 18,122 B and 19,516 B to rebuildability respectively.
Authored growth averaged 3,143 B/hour across the twelve hours.

A changed-row scan finds 219 added authored-source rows and 186 net rows, but
row sizes are not deduplicated coverage and do not replace the byte metrics.
Large contributors include STLport time facets (1,273 B), tree toppling update
(1,207 B), Lua script-function registration (1,162 B), worker build/repair
position selection (1,154 B), and terrain background rendering (1,044 B).
These are net changed-row sizes by source, not independent attribution of the
headline. Existing-source conversions can change coverage without row edits.

## Initial allocation

Six near-match lanes: default-window drawing, radio-button drawing, network
region handling, Xfer mission-objective vectors, Team/TeamFactory, and a
related three-body object cluster. Four anonymous lanes: 0x006AEF20,
0x003F6090, 0x00346560, and 0x00088480. All assignments have separate worktrees,
explicit RVA claims, and centrally reviewed integration. Workers cannot push.

The Xfer lane investigates same-TU helper visibility and calling conventions.
Each lane must preserve independently proven reusable discoveries. A documented
single-SIB dead end was identified early in the draw lanes and flagged for
prompt retirement rather than another spelling sweep.

## Hourly assessments

First verified push: `e9995f1f72`, the 96-byte address-derived position-range
dispatch at 0x0021C820. This is +0.000989 pp, rounded to +0.00 pp by the CLI.
The six-hour comparison and prior-twelve-hour totals above exclude this run.

The two GUI draw seats produced no byte improvement and were reassigned after
approximately nine minutes to donor-backed bodies at 0x000D74B0 and 0x0023D130.
Their negative experiment evidence remains in the isolated worktrees.

Pending first hourly assessment. Local detailed transcripts, briefs, baseline output and
active assignments live under `build/orchestrator-20260916/` (untracked).
