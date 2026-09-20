# Conversion campaign, 2026-09-20

Start: 2026-09-20T17:12Z. Planned duration: 36 hours. Orchestrator: Claude
(Fable 5.1); workers: Claude Sonnet 5 sessions, one git worktree each, six
concurrent seats. Host: Apple Silicon Mac, MSVC 7.1 under Wine 11 + Rosetta 2.

## Prior twelve hours

Measured between `61d14457a854a66e411b4645ad3e8b6b5016c84f` (last commit
reachable before the 05:12Z cutoff) and `ea5778798f31df02cc31d3b0f2eb1cc0876c5355`
(origin/master at 17:07Z) with `python3 tools/progress.py BASE..HEAD`.
967 commits by three contributors; commit count is not conversion progress.

| Metric | Before | After | Change |
|---|---:|---:|---:|
| Rebuildable non-padding code | 66.90% | 67.04% | +13,287 B / +0.14 pp |
| Authored C++ | 40.82% | 40.96% | +13,319 B / +0.14 pp |
| Vendored source | 311,008 B | 310,976 B | -32 B |
| Generated C++ / prebuilt libraries | — | — | 0 B |
| Total exact coverage (full .text denominator) | 8,671,776 B | 8,679,622 B | +7,846 B / +0.06 pp |
| ASM-only exact (dumps) | — | 3,228,162 B | -5,441 B |

Non-padding denominator 9,702,173 B; `.text` denominator 13,049,856 B.
Roughly 59% of the headline gain was new coverage (unclaimed bytes landed as
C++) and 41% was transfer out of existing dumps. Throughput was ~1,100
authored B/hour, about a third of the 3,143 B/hour measured before the
2026-09-16 campaign. Most of the window's commits were carved one-byte
returns and no-op bodies; the last 2,500 `re_attempts.log` verdicts across
all engines land at ~0.3%, so the cheap tail of the pool is gone.

Remaining at the start snapshot: 4,752 open dump bodies (1,676,807 B), of
which only 32 have never been attempted; 2,241 carved anonymous bodies
without a ledger row; banked near-misses at score >= 0.95 hold 224 bodies /
68,168 B, each with 5-24 prior attempts. 79 distinct bodies at >= 0.97 cite a
SIB base/index residue as their blocker, as do 40 of the 51 residual bytes in
`SegLineRendererClass::Render` (14,081 B, 0.9964).

## Initial allocation (17:55Z, fleet base `9daa1c571c`)

| Seat | Lane | Targets |
|---|---|---|
| wt1 | A1 near-miss finish | 0x001CA2E0 0x001F6250 0x008BEF00 0x00886B00 0x009471F0 |
| wt2 | A2 near-miss finish | 0x00796310 0x0023B7A0 0x0077D150 0x00226A80 0x0078D410 0x005151F0 |
| wt3 | C1 carved anonymous, callers known, <=1 attempt | 0x00597130 0x00159AD0 0x0026B9D0 0x0014DAB0 0x00789E60 0x0019BF40 |
| wt4 | C2 carved anonymous, callers known, <=1 attempt | 0x00269780 0x00377060 0x006164E0 0x00702920 0x00342E40 0x003E11E0 |
| wt5 | R  compiler research: two-register SIB base/index rule | witnesses 0x0078D410 0x007901F0 0x005A0450 0x0045C2F0 |
| wt6 | D  mid-size bodies from the densest landed-C++ file | 0x00513BF0 0x008312E0 0x009B58F0 0x00851BF0 0x00155490 0x005ADC10 |

Lane R is the breakthrough bet: if a clean-C++ property that steers MSVC's
base/index choice exists, it unblocks the four one-byte lea bodies, the GUI
draw family and the 14 KB SegLine body in one lever. The Zero Hour packet
tier was checked first and found spent (one live packet of nine).

## Hourly assessments

(appended below as they are taken)

### Hour 1 — 17:29Z to 18:30Z

Snapshot `b07e210d09`, compared with fleet base `9daa1c571c`.

| Metric | Change during interval |
|---|---:|
| Fleet: verified/pushed bodies | 7 |
| Fleet: landed bytes | 2,357 B |
| All contributors: rebuildable / authored bytes | +2,739 B / +0.03 pp (67.04% -> 67.07%) |
| All contributors: total exact coverage | +2,559 B |
| All contributors: generated / vendored / prebuilt | 0 B |

Six of the seven landings are carved anonymous bodies (no ledger row before),
so this hour was new coverage rather than dump transfer. Rate: 2,357 fleet
B/hour against the prior twelve-hour repository average of 1,107 B/hour.

| RVA | Bytes | Lane | Result |
|---|---:|---|---|
| 0x00789E60 | 1,179 | C1 | SimpleScene-family Customized_Render; exact on the first probe from a landed sibling |
| 0x002D55F0 | 269 | C6 | Opaque teardown body |
| 0x00770270 | 217 | C5 | STLport vector<Elem> destructor instantiation |
| 0x0045C8F0 | 185 | C4 | CameraMarkerList replace |
| 0x002D6840 | 180 | T | Flag-pair upgrade, near-twin of ModelConditionUpgrade::upgradeImplementation |
| 0x0023C9C0 | 179 | C4 | Opaque view predicate |
| 0x00402930 | 148 | C3 | Scalar constructor |

What did not work, measured: the two near-miss finish lanes (11 bodies at
0.97-0.995, each with 5-27 prior verdicts from stronger models) landed
nothing; the SIB research lane found a reproducible base/index flip in an
isolated function that does not transfer to any real body
(`docs/sib_lea_experiments.md`, with the orchestrator's flag sweep appended);
the ~1 KB carved lane and the vtable-slot lane (700-1,065 B bodies with prior
banks) landed nothing. The lanes that landed were small carved bodies
(150-330 B, <=1 prior attempt, a caller known) and near-twins of landed
bodies. Sonnet sessions also tend to stop after ~20 minutes believing their
budget is spent, so briefs now state the wall-clock budget explicitly and an
effort floor (a compilable candidate and eight probes before any verdict)
after one lane recorded five `blocked` verdicts in fifteen minutes.

Hour 2 allocation: all seven seats on small carved bodies with callers
(lanes C3-C8, C5b) and the deep lane E on the SidesList parse callback.
