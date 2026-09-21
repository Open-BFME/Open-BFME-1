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

### Hours 2-4 — 18:30Z to 22:00Z (interrupted)

At 18:48Z every Sonnet seat hit the account's session usage limit (reset
22:00Z); all seven lanes died mid-body and the orchestrator waited. Snapshot at
22:01Z compared with the fleet base: fleet 8 bodies / 2,571 B (one more since
hour 1: 0x001C6E00, 214 B, lane C4); repository-wide +8,386 B / +0.09 pp
(67.04% -> 67.13%), of which +3,323 B is new total-exact coverage; other
contributors added ~5.8 KB during the outage. Three worktrees kept unverified
candidates (0x0023A380, 0x001A12D0, 0x00364E70) that the resumed lanes start
from. Restart at 22:05Z with four seats instead of seven so the next usage
window lasts ~3 hours instead of ~1.5.

### Hour 5 — 22:00Z to 23:05Z (four seats)

Snapshot compared with fleet base `9daa1c571c`: fleet 11 bodies / 3,653 B
cumulative; this hour 3 bodies / 1,082 B. Repository-wide +11,812 B /
+0.12 pp (67.04% -> 67.16%) since the fleet base, +4,491 B of it new
total-exact coverage.

| RVA | Bytes | Lane | Result |
|---|---:|---|---|
| 0x000D3BE0 | 418 | C9r | STLport hashtable<Value,AsciiString>::resize instantiation |
| 0x00326C00 | 332 | C8r | ScriptConditions two-parameter predicate |
| 0x00326DA0 | 332 | C8r | Its twin, landed from the first one's source |

Four seats banked seven further candidates (0.27-0.87) without landing
them. The carved pool with a known caller and at most one prior attempt is
now fully assigned; the next seats draw 100-300 B gen_asm dump bodies ranked
by landed-neighbour density.

### Hour 6 — 23:05Z to 00:05Z (four seats)

Fleet 20 bodies / 4,963 B cumulative; this hour 9 bodies / 1,310 B, every
one a 126-168 B gen_asm dump in an address range dense with landed C++
(lanes D2-D5). Repository-wide +13,212 B / +0.14 pp (67.04% -> 67.18%)
since the fleet base.

| RVA | Bytes | Result |
|---|---:|---|
| 0x0081EDD0 | 168 | CompressMemory |
| 0x0016DF90 | 160 | Opaque Object lookup |
| 0x007AE900 | 149 | Opaque Coord3D evaluator |
| 0x0046F3D0 | 149 | DrawImageAt (mode-source variant) |
| 0x002D49E0 | 147 | CostModifierUpgrade::upgradeImplementation |
| 0x004942C0 | 146 | Opaque run() |
| 0x0046F060 | 137 | DrawImageAt |
| 0x0026FA80 | 128 | Opaque evaluate(int) |
| 0x002C5240 | 126 | AI command dispatcher sharing the landed Rva002C45E0 vtable |

The warm-neighbourhood dump picker (100-300 B, at most one prior verdict,
ranked by landed rows within 0x1000 bytes) is the campaign's best lane by
landings per seat-hour; the carved lane's remaining bodies (400-600 B) are
now mostly banked at 0.1-0.5. Twelve more bodies were banked this hour,
three of them at 0.92-0.93 with single register-role or SIB residues.
Recurring unsolved lever reported by four bodies: MSVC 7.1's choice of
which branch falls through to a shared return tail.

### Hours 7-9 — 00:05Z to 03:00Z (second outage)

The four seats hit the session usage limit again at 00:30Z (reset 03:00Z),
after ~2.5 hours of the second window. One more body landed before the cut:
0x00605F00 (179 B, STLport `_Rb_tree::insert_equal` instantiated in its own
TU). Fleet cumulative 21 bodies / 5,142 B; repository-wide +13,931 B /
+0.14 pp (67.04% -> 67.18%) since the fleet base, +5,121 B of it new
total-exact coverage. Restart at 03:05Z with three seats.

### Hour 10 — 03:00Z to 04:03Z (three seats)

Fleet 25 bodies / 6,153 B cumulative; this hour 4 bodies / 1,011 B, all
250-255 B gen_asm dumps from the warm-neighbourhood pool. Repository-wide
+14,992 B / +0.15 pp (67.04% -> 67.20%) since the fleet base.

| RVA | Bytes | Result |
|---|---:|---|
| 0x0084BA90 | 255 | STLport basic_ofstream<char> fd constructor |
| 0x001AAC30 | 255 | bfmeLookupByName (AsciiString -> entry) |
| 0x0046DA70 | 251 | WindowManager::bindShown |
| 0x0090CF90 | 250 | Texture-base constructor (Rva006D51B0 family) |

Three seats this window so the usage budget spreads over the whole reset
period instead of ~2.5 hours; landings per seat-hour are unchanged.

### Hour 11 — 04:03Z to 05:05Z (three seats)

Fleet 30 bodies / 7,044 B cumulative; this hour 5 bodies / 891 B.
Repository-wide +15,977 B / +0.16 pp (67.04% -> 67.21%) since the fleet
base; +5,265 B of that is new total-exact coverage.

| RVA | Bytes | Result |
|---|---:|---|
| 0x0084C8F0 | 248 | STLport basic_fstream<char> pathname constructor (plain explicit instantiation) |
| 0x0036E420 | 246 | Castle canUnpack |
| 0x0051BCE0 | 173 | Opaque stdcall callback |
| 0x006ACE90 | 113 | addNamedRoom |
| 0x00463BA0 | 111 | Opaque Coord2D/text draw helper |

Two STLport near-twins (0x0084C6F0, 0x0084CEA0) banked at 0.94: ICF
near-twins of the fstream constructor that hardcode a default argument,
and any out-of-class specialization or new derived class picks up a spare
hidden virtual-base parameter (`ret 0x10` vs `ret 0xc`) that a single-TU
compile cannot elide.

### Hour 12 — 05:05Z to 06:05Z (three seats)

Fleet 36 bodies / 8,214 B cumulative; this hour 6 bodies / 1,170 B.
Repository-wide +17,227 B / +0.18 pp (67.04% -> 67.22%) since the fleet
base; +5,345 B of that is new total-exact coverage.

| RVA | Bytes | Result |
|---|---:|---|
| 0x006EB070 | 252 | Render2DClass::Add_Tri (real identity, sibling of the landed Add_Quad) |
| 0x007F2C10 | 249 | GameSpy rank-period serializer |
| 0x001C6640 | 248 | BitFlags<116>::xfer (explicit instantiation, exact on the first probe) |
| 0x0016D270 | 153 | Opaque invoke() |
| 0x001FCA90 | 151 | Opaque invoke() returning bool |
| 0x009A36F0 | 117 | Opaque apply(param) |

## Mid-campaign comparison (12.6 hours in)

| Window | Rebuildable | Authored C++ | Total exact |
|---|---:|---:|---:|
| Prior 12 h (61d14457a8..ea5778798f, all contributors) | +13,287 B / +0.14 pp | +13,319 B | +7,846 B |
| Campaign 17:29Z..06:05Z (all contributors) | +17,227 B / +0.18 pp | +15,334 B | +5,345 B |
| of which the fleet's landings | 8,214 B in 36 bodies | | |

About 5.5 of the 12.6 hours were lost to two account usage-limit resets
(18:48Z-22:00Z and 00:30Z-03:00Z), during which no seat could run. Per
active seat-hour the fleet lands ~1 body / ~230 B. What works: 100-250 B
gen_asm dumps with at most two prior verdicts, ranked by landed C++ within
0x1000 bytes, with the neighbours' sources as donors; STLport and BitFlags
template instantiations named in `reloc_names.csv`, instantiated in their
own TU; near-twins of landed bodies. What does not: banked near-misses at
0.97+ with five or more prior verdicts, bodies over ~600 B, and any body
whose residue is a single SIB byte, a register-role swap or a loop-head
alignment pad. The SIB base/index rule remains unreachable from clean C++
and from every compiler flag tried (`docs/sib_lea_experiments.md`).

### Hour 13 — 06:05Z to 08:00Z (third outage)

Four more bodies landed before the seats hit the usage limit again at
~06:40Z (reset 08:00Z): 0x001ABBB0 (168 B, Waypoint gate), 0x00465D50
(137 B), 0x000D4360 (116 B), 0x000D3DF0 (111 B, BitFlags<181>::xfer).
Fleet 40 bodies / 8,746 B cumulative; repository-wide +17,897 B / +0.18 pp
(67.04% -> 67.23%) since the fleet base. Three worktrees kept unverified
candidates (0x008CF3C0, 0x00006D20, 0x000FB2E0) for the resumed seats.
Restart at 08:05Z with three seats.

### Hour 14 — 08:00Z to 09:02Z (three seats)

Fleet 44 bodies / 9,755 B cumulative; this hour 4 bodies / 1,009 B.
Repository-wide +18,967 B / +0.20 pp (67.04% -> 67.24%) since the fleet
base.

| RVA | Bytes | Result |
|---|---:|---|
| 0x002D4850 | 309 | CostModifierUpgrade::onCapture (real identity, third body of that file family) |
| 0x0089D4C0 | 238 | Apt string-list predicate |
| 0x0051BB80 | 236 | Opaque update(int) virtual |
| 0x006091B0 | 226 | Opaque setEnabled(bool) |

The 100-250 B warm pool is spent (its tail is SecuROM stubs and split tail
fragments that no calling convention expresses); seats move to 250-400 B
with at most one prior verdict. Two identities were recovered without a
landing (Player::processAddTeamGameMessage at 0x000D2A60 from its landed
neighbours; an ICF-shared SpecialPowerModule::getPercentReady override at
0x0026AAC0 from five vtables) and banked at 0.29 / 0.74.

### Hour 15 — 09:02Z to 10:02Z (three seats)

Fleet 45 bodies / 10,077 B cumulative; this hour 1 body / 322 B
(0x00210730, opaque owner method). Repository-wide +19,362 B / +0.20 pp
(67.04% -> 67.24%) since the fleet base. Six more banks (0.15-0.89); the
0.89 at 0x007647D0 (W3DScriptedModelDraw transform update, 313 B) differs
only by an ecx/edx register swap across two field copies. Seats in the
250-400 B band land about one body per session and stop at ~45 minutes,
so a fourth seat is added for the rest of this usage window.

### Hours 16-18 — 10:02Z to 13:00Z (fourth outage)

One landing before the seats hit the usage limit again at ~11:00Z (reset
13:00Z): 0x000D2CE0 (256 B, Player::addAIGroupToCurrentSelection), closed
by `#define _STLP_NO_EXCEPTIONS 1` ahead of `<vector>` — found by
`eh_levers.py` + `shape_search.py` in two trials. Fleet 46 bodies /
10,333 B cumulative; repository-wide +19,871 B / +0.20 pp (67.04% ->
67.25%) since the fleet base.

Two research rounds on the whole-body callee-saved register mirror (the
residue behind at least eight of today's banks) found the mechanism — an
embedded `this+N` sub-object reused across two or more calls takes ESI
and demotes `this`; only genuine loop structure changes the ranking; extra
or folded uses of `this` and first-use order do nothing — but no clean-C++
reversal. Written up in `docs/register_mirror_experiments.md`. The
seats' conclusion stands: such banks are identification gaps, not lever
problems. Restart at 13:05Z with four seats: cluster bodies near today's
landings, the 250-450 B and 400-600 B warm pools, and twice-attempted
carved bodies with stashes.

### Hour 19 — 13:00Z to 14:03Z (four seats)

Fleet 48 bodies / 10,769 B cumulative; this hour 2 bodies / 436 B:
0x00328680 (281 B, ScriptConditions::evaluatePlayerHasNOrFewerBases, from
the cluster lane that seeds each seat with bodies within 0x800 bytes of a
body the fleet landed today) and 0x006AD590 (155 B, an audio
priority/volume adjuster resumed from an interrupted candidate).
Repository-wide +21,707 B / +0.22 pp (67.04% -> 67.26%) since the fleet
base; +7,281 B of that is new total-exact coverage.

### Hour 20 — 14:03Z to 15:03Z (three to four seats)

No fleet landing this hour; nine banks, the best a 0.99 at 0x004BCCE0
(402 B command-button progress dispatcher: two isolated eax/edx register
picks for a vtable pointer) and a 0.97 at 0x002D8C10. Fleet 48 bodies /
10,769 B cumulative; repository-wide +22,155 B / +0.23 pp (67.04% ->
67.27%) since the fleet base. Two prior author-estimated scores of 0.78
were re-measured at 0.27 and 0.44 and corrected in the log. Levers
recorded this hour: `extern const T NAME;` for a fixed-VA aggregate
constant (folds each dword to an absolute address where a cast copies
through a register loop); dropping a long-lived duplicate pointer local to
pull `this` back into retail's register; a named float local to keep the
x87 value across a branch; an implicit destructor with per-member owner
wrappers to remove a spurious vtable store.

### Hours 21-23 — 15:03Z to 18:00Z (fifth outage)

One landing before the usage limit hit again at ~15:35Z (reset 18:00Z):
0x00225960 (249 B, opaque owner method). Fleet 49 bodies / 11,018 B
cumulative; repository-wide +25,321 B / +0.26 pp (67.04% -> 67.30%) since
the fleet base. Restart at 18:05Z with three seats on the resumed lists
(100-700 B warm dumps and the untouched 600-900 B carved pool).

### Hour 24 — 18:00Z to 19:02Z (three seats)

No fleet landing; nine banks. Fleet 49 bodies / 11,018 B cumulative;
repository-wide +29,315 B / +0.30 pp (67.04% -> 67.34%) since the fleet
base, +10,985 B of it new total-exact coverage. The 100-700 B warm-dump
pool with at most two prior verdicts is exhausted of tractable bodies:
what remains there is x87 interpolation chains, split tail fragments,
SecuROM stubs, register-mirror residues and hand-written SSE dispatch (one
Bink body reaches exact bytes only as `naked` asm and is correctly refused
by the anti-lift gate). Seats move to the 500-800 B pool with one prior
verdict (306 bodies / 197 KB), triaging each list for landed same-class
siblings before writing anything. Identity found this hour without a
landing: GeometryInfo::DoXfer at 0x00880600 (vtable slot 3, three landed
constructors install the table).
