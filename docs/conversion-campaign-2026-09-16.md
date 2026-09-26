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

### Hour 1 — 14:25:20 to 15:25:37 UTC

Snapshot: `6b2fd3a71608f2bfcac80f7fcb0489c80711f678`.

| Metric | Change during interval |
|---|---:|
| Fleet: verified/pushed dump-to-C++ bodies | 10 |
| Fleet: authored/rebuildable bytes | +2,816 B / +0.02902 pp |
| All contributors: rebuildable bytes | +3,999 B / +0.04122 pp |
| All contributors: authored C++ bytes | +4,234 B / +0.04364 pp |
| All contributors: generated C++ bytes | -235 B |
| All contributors: total exact coverage | +287 B |

The fleet transferred existing dump ranges; it did not enlarge total exact
coverage. Its first-hour output is slightly below the prior twelve-hour
repository average of 3,143 authored B/hour. The populations differ, and model
cost has not been measured, so this is context rather than a speedup claim.

Fleet landings, each scoped byte-verified and pushed through normal hooks:

| RVA | Bytes | Result |
|---|---:|---|
| 0x0021C820 | 96 | Opaque position-range dispatcher |
| 0x0023D130 | 92 | Opaque resolver returning the witnessed subobject |
| 0x003C2830 | 326 | Mission-objective vector Xfer; local lifetime/width lever |
| 0x002E7410 | 225 | Opaque filtered event dispatcher |
| 0x0071C9C0 | 397 | Opaque matrix/bounds record update |
| 0x00346560 | 1,118 | ScriptEngine action dispatcher |
| 0x000D74B0 | 269 | Opaque hash-map snapshot transfer |
| 0x002060B0 | 61 | Opaque indexed three-word copy |
| 0x0046F6F0 | 206 | Slash-to-dot string utility |
| 0x0024B7C0 | 26 | Opaque field-null forwarder |

Eight donor-backed landings account for 1,372 B; the two larger near-match
finishes account for 1,444 B. Donor work therefore had the stronger body yield,
while the script dispatcher provided the largest individual byte gain. Repeated
GUI/register-shape passes and the TeamFactory follow-up made no progress.
Large anonymous audio/pathfinder/MapObject investigations were stopped; one
audio bank failed the orchestrator's independent compile and was rejected.
Its useful evidence is recorded as `blocked`, not as a scored partial.

Allocation change for hour 2: continue donor-backed INI and particle-template
work and the constructor with a matched destructor; prefer those approaches
for freed slots. Retain bounded library/terrain and near-match investigations
only while they produce new byte or ABI evidence. End the long containment
pass before another sibling; shorten unchanged near-match retries. Every slot
remains separately claimed, with fresh worktrees based on recent master.
The ordinary exact-donor pool is nearly exhausted, so existing near/fuzzy
donor scans supply leads; compiler cleanup funclet counts are not treated as
ordinary conversion work. All ten slots were occupied at the assessment.

Validation: all ten landings passed scoped gates, pin consistency, and normal
commit/push hooks. The script dispatcher's 36 tail table pointers and all
remaining table bytes were independently checked in addition to its body.
Initial stale-object identity checks were repaired by scoped rebuilds; an
incidental broader check exposed pre-existing relocation failures, so no
repository-wide green build is claimed. Reusable Xfer/x87 findings are in
`docs/shape_levers.md`; donor and measured-bank guidance is in
`docs/throughput-tools.md`.

Local transcripts, briefs, snapshots and active assignments live under
`build/orchestrator-20260916/` (untracked). The 36-hour campaign remains in progress.


### Hour 2 — 15:25:37 to 16:25:21 UTC

Snapshot: `969a884d8a` (after synchronization and ledger validation).

| Metric | Change during interval |
|---|---:|
| Fleet: verified/pushed dump-to-C++ bodies | 9 |
| Fleet: authored/rebuildable bytes | +2,040 B / +0.02103 pp |
| All contributors: rebuildable/authored bytes | +4,620 B / +0.04762 pp |
| All contributors: generated/inputs/vendor/prebuilt bytes | 0 B |
| All contributors: total exact coverage | 0 B |
| Fleet cumulative | 19 bodies / 4,856 B / +0.05005 pp |

Fleet byte output fell 27.6% from hour one's 2,816 B. Repository-wide authored
output rose from 4,234 to 4,620 B; 2,580 B of this interval came from other
contributors. Current rebuildability is 6,339,041 B of 9,702,173 non-padding
bytes. These are transfers out of existing dumps, not new exact coverage.

| RVA | Bytes | Result |
|---|---:|---|
| 0x00339120 | 146 | Opaque particle-template allocation |
| 0x00900E40 | 417 | Alternate constructor with native StringClass lifetime |
| 0x000941D0 | 233 | INI integer-definition parser |
| 0x004525B0 | 152 | STL tree equality over string-shaped keys |
| 0x001CCB20 | 400 | Object condition propagation |
| 0x00606E60 | 207 | Native STL tree copy constructor |
| 0x004233A0 | 146 | Eva position-aware trigger flag update |
| 0x006A0730 | 169 | Pointer-key hash insertion |
| 0x006070E0 | 170 | Native tree aggregate constructor |

Native STL layouts and related constructors produced reusable evidence:
`0x00606E60` establishes the node/payload sizes used by `0x006070E0`;
grouping the latter's prefix subobject reproduces its exception state.
The pointer-key insertion disproved a stale generated payload name using
its eight-byte node allocation. The earlier 26-byte forwarder's unproven
containment wording was corrected without claiming new bytes.

The renderer and audio investigations produced independently recompiled banks,
but no conversions. Map-image setup improved from 492 to 279 differing
non-relocation bytes and remains 32 bytes short of its complete 659-byte
boundary. Existing author scores were not inflated to promote the newer bank.
The Player helper's previously disputed two-argument callee ABI was proved;
its new 156-byte bank still differs in two register bytes and earns no progress.

The fuzzy donor scan now uses the shared eligibility rules and active claims,
streams ledger rows, caches repeated byte masks, and honors `--help`. A wider
scan produced 14 leads before filtering and nine live/unclaimed leads afterward;
retired and busy addresses were independently checked. This tooling contributes
zero bytes to the completion figures.

Hour 3 allocation: retain native STL map/tree and related constructor work in
lanes 2, 5 and 10; continue the nearly exact Eva parser with header/identity
review before its larger sibling. Lane 4 now handles a smaller file-opening
routine from its served file. Finish the short Object and map-filter siblings
under bounded timeboxes. Retire the renderer and texture investigations after
the current measured probes, and move those slots to fresh donor-backed
vector/script work. Lane 9 was stopped after a second long ABI-only W3D round
and reassigned to a 238-byte Team lookup with a verified donor. No speculative
helper pins or unmeasured sources were integrated.

All nine landings passed independent scoped builds and normal commit/push
hooks. The own-row sweep found 19 unique addresses backed by tracked C++.
One push raced another contributor; rebase, ledger recheck and normal retry
succeeded. The same repository-wide build limitation reported in hour 1
remains; this assessment does not claim a full green gate.
Next assessment is due around 17:25 UTC.


### Concurrent parser landing correction (16:52 UTC)

The post-batch address sweep found two rows for `0x00425C90` (342 bytes).
Another contributor's `be2a7bf401` landed the parser at 16:32 UTC; our
`7832a37766` followed at 16:36 UTC after a union merge retained both claims.
The fleet therefore receives **zero incremental conversion bytes** for that
parser. Its independently proved assignment ABI and string-header adoption
are retained in one consolidated INI source, with an address-derived callback
owner because the registry proves the block role, not the original C++ method
name. The duplicate row/source is retired. The first two hourly snapshots
precede this race and are unaffected; the third-hour fleet tally excludes
these 342 bytes. Ledger range union already prevented the duplicate from
inflating the repository-wide byte metric.

### Hour 3 — 17:25 UTC

Snapshot `efbc72cbee`, compared with `969a884d8a`. The fleet landed nine
new bodies totaling 2,343 bytes (+0.02415 percentage points), bringing its
corrected cumulative contribution to 28 bodies / 7,199 bytes (+0.07420 pp).
This excludes the concurrent 342-byte parser conversion described above.
Fleet bytes increased 14.9% from hour 2; repository-wide authored/rebuildable
bytes increased 3,806 (+0.03923 pp), down 17.6% from the previous hour.
Other contributors account for 1,463 of this hour's net bytes.

The snapshot holds 6,342,847 rebuildable bytes (65.38%) and 3,811,901 authored
C++ bytes (39.29%). Generated C++, vendored source and attached libraries were
unchanged. Total exact coverage increased 234 bytes; the remaining conversion
gain moved already bounded assembly into verified C++. These categories are
not interchangeable.

Native STL vector assignment, float-map indexing, registry strings and
donor-backed supplier code produced verified progress. Recovered nullable
inline-helper structure and a native waypoint map also matched after this
snapshot and will count in hour 4 only once pushed. A map-control reconstruction
now has the exact 427-byte size but 29 stack-home differences: its bank and
lifetime discovery are preserved, with zero completion credit.

Hour 4 allocation favors native STL and concrete donor adaptations: string
concatenation, waypoint maps, related parser helpers, and an AI state with a
verified donor. Newly freed slots receive fresh destructor/cluster work.
Persistent tiny loop-alignment, register-tail and EH-layout misses are stopped
after their current bounded trials; useful banks remain available. The
memory-tracker cluster has two successful scoped checks awaiting independent
review. No slot is reserved solely to inflate agent count.

All nine credited conversions passed independent scoped byte verification and
normal commit/push hooks. Duplicate-address review led to the parser correction
above. Concurrent pushes were handled by rebase and normal rechecking. No new
full-repository-green claim is made. Next assessment: about 18:25 UTC.

### Hour 4 — 18:25 UTC

Snapshot `58cb9aaa35`, compared with `efbc72cbee`. The fleet pushed 16
new bodies totaling 4,500 bytes (+0.04638 percentage points), bringing its
corrected cumulative contribution to 44 bodies / 11,699 bytes (+0.12058 pp).
Fleet byte yield increased 92.1% from hour 3. Repository-wide authored and
rebuildable coverage grew 6,016 bytes (+0.06201 pp), up 58.1%; other
contributors account for 1,516 net bytes.

The snapshot holds 6,348,863 rebuildable bytes (65.44%) and 3,817,917
authored C++ bytes (39.35%). Generated, vendored and attached-library bytes
were unchanged. Total exact coverage rose 222 bytes; most of the conversion
gain replaced already bounded assembly. All credited bodies passed root
scoped verification and normal commit/push hooks. The latest 42-body audit
found one tracked source per address; the subsequent parser and pathfinding
callback also passed their scoped hooks. No full-repository-green claim is
made. Concurrent push races were resolved with rebase, ledger checks and
normal retries.

Productive approaches included memory-tracker and loader-hook routines,
a native waypoint map, a donor-backed AI state, two destructors modeled with
witnessed member lifetimes, LAN/UI callbacks, and a pathfinding callback.
The INI factory-vector callback landed when its created element reused the
incoming data argument slot. The pathfinding callback required a full-width
integer return rather than a byte return. These compiler and lifetime
findings are recorded in the sources and `docs/shape_levers.md`. Review also
removed two unused helper pins that had confused virtual addresses with RVAs.

The donor scanner now excludes assembly-backed donor rows using the existing
progress classifier, including mixed-source files. A wider scan found 25
leads totaling 4,522 bytes; this is a candidate inventory, not a promise of
conversions. Seventeen relevant progress-classifier checks passed; the test
script later hit an existing README-heading assertion (`## Status` absent).
A 987-byte URL builder is banked with ten EH saved-stack-pointer differences
and a portable include path. It receives zero completion credit. Two AI
bucket reconstructions and a constructor blocker were also preserved.

Hour 5 allocation favors fresh concrete donors and successful file clusters:
LAN player-slot selection, a waypoint callback, the remaining pathfinding
sibling, and the nullable-helper pattern applied to a particle initializer.
A larger Worker construction bank gets a bounded coordinate/lifetime
investigation. The unsuccessful AI bucket lane was reassigned; constructor
and LAN register-layout loops were closed after finite trials. Long ABI
investigations must produce a first probe or a precise blocker, rather than
continue searching for original semantic names. All ten CLI lanes remain
independently assigned; no duplicate function work was introduced.
Next assessment: about 19:25 UTC.
