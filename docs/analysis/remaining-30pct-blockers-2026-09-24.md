# The last 29.5%: where the bytes are and what blocks them (2026-09-24)

Measured on `4adaa6ee1` (origin/master, 2026-09-24) with the ledger, the
attempt log and the retail image. Nothing here is a byte-match claim; it is a
map for choosing lanes. Every figure has its reproduction command at the end.

## Where the remaining bytes are

`python3 tools/progress.py`: **70.48%** of non-padding `.text` (9,702,173 B)
rebuilds from what we hold. The other 29.5% is two pools:

| pool | bytes | share | meaning |
|---|---:|---:|---|
| dumps | 2,029,028 | 20.91% | boundary proven, retail bytes re-emitted (MASM `.asm` or naked/`__emit`) |
| unclaimed | 835,222 | 8.61% | no boundary proven yet |

Rate: `progress.py <ref>` against master on 09-14, 09-18 and 09-21 gives
**+6.17, +4.77 and +3.30 pp** to today. The last three days ran ~1.1 pp/day;
the 09-20 campaign note's ~1.1 KB/hour was one fleet's window, not the
repository's rate.

### The 1.50 MB held as `.asm` (4,254 bodies)

| size | bodies | bytes | share |
|---|---:|---:|---:|
| < 64 | 1,888 | 35,830 | 2.4% |
| 64-255 | 709 | 117,009 | 7.8% |
| 256-1,023 | 1,340 | 700,404 | 46.8% |
| 1,024-4,095 | 295 | 490,317 | 32.8% |
| 4,096-16,383 | 21 | 133,697 | 8.9% |
| >= 16,384 | 1 | 18,655 | 1.2% |

* **97% of the bytes are anonymous `?d_` bodies** (1,453,676 B); 42 KB is named.
* Only 10 bodies (15 KB) have never been attempted. 550 bodies (235 KB) have
  six or more verdicts.
* Latest verdict by bytes: `blocked` 920 KB, `partial` 483 KB, `no-match` 47 KB.
* **The `blocker=` taxonomy covers 11% of the bytes.** 3,976 of 4,254 bodies
  (1.33 MB) carry no tag in their latest verdict, and 3,106 (743 KB) have never
  been scored. Clustering by tag (`tools/blockers.py`) cannot see most of the
  pool; `blocker-family-2026-09-24.md` found the tags that exist barely repeat.
* Banked near-misses at score >= 0.9: **342 bodies, 115,541 B (1.2 pp)**. The
  finish tier shows none of them because every one is over the attempt cap or
  in cooldown.

## Blockers, by the bytes behind them

### 1. Core game classes have no header (largest)

A TU that needs `Object` declares its own partial copy, padded out to the
fields it touches. `grep -rlE '^(class|struct) X( *[:{]|$)' Code --include=*.cpp`:

| type | TU-local copies | header |
|---|---:|---|
| `Object` | 998 | none |
| `GameLogic` | 432 | three disagreeing |
| `INI` | 399 | two |
| `UnicodeString` | 333 | `unicode_string.h` |
| `Player` | 257 | none |
| `AIUpdateInterface` | 211 | none |
| `ThingTemplate` | 183 | none |
| `GameWindow` | 165 | two |
| `Drawable` | 148 | none |
| `Team` | 128 | none |
| `Pathfinder` | 120 | none |

Every new body re-derives the offsets it needs, and a wrong guess surfaces
later as a "layout drift" near-miss that nobody can attribute. Latest verdicts
that mention layout, offset or drift cover **753 KB, half of the `.asm` bytes**.
The classes those verdicts name most, by bytes: `Object` 88 KB (154 bodies),
`AsciiString` 67 KB, `GameLogic` 42 KB, `Apt` 35 KB, `DX8Wrapper` 31 KB,
`GameClient` 28 KB, `Pathfinder` 27 KB, `Drawable` 27 KB, `UnicodeString`
26 KB. (Keyword presence in free text, overlapping; it locates bytes, it does
not prove cause.)

The evidence to start exists: `bfme_layouts.json` witnesses 39 `Object`, 40
`Player` and 41 `AIUpdateInterface` members, and the 998 local copies are
themselves 998 byte-verified partial witnesses. A header ends the re-derivation
for every future body, and `adopt_header.py --check --staged` keeps new TUs from
redeclaring a covered type.

### 2. Large bodies: 43% of the dump bytes, almost no landings

Bodies >= 1 KB are 317 bodies and ~642 KB. `tools/yield_model.py` measures
P(land) = 8.8% above 512 B; the 09-20 campaign's ~1 KB lanes landed nothing.
The 25 largest hold ~180 KB and their best banks score 0.05-0.6 (except
`SegLineRendererClass::Render`, 0.996). Verdicts citing an EH/SEH prologue or
frame cover 32% of dump bytes. Many of these are downstream of #1: the
`whales.md` recipes stop on `GlobalData`, `Object`/`Drawable` and GameSpy
layout drift.

### 3. Unclaimed 8.6%: the carve pool is spent

`tools/gap_census.py` proves 3,489 function starts in the gaps covering
693,346 B; 162 KB has no proven start. `targets/game/reverse/carved.csv` serves 397 rows /
406,956 B and all but 155 B of it has been attempted. The ~290 KB of proven
starts that never became carved rows is the next pool, and what it needs is end
evidence (`BoundaryValidator.check_end`), not more attempts on the served rows.
`carve_unclaimed.py` needs `capstone`, which a fresh container lacks.

### 4. Near-miss residue: problems without a known lever

The 342 banks at >= 0.9 stall on SIB base/index choice, block order and
register roles (`sib_lea_experiments.md`, `shape_levers.md`). One open
hypothesis there is that retail used a different `c2.dll` build. **The Rich
header says otherwise:** decoding it from `lotrbfme.exe` (the `DanS` marker
checks) gives

| prodid | tool | build | objects |
|---|---|---:|---:|
| 0x60 | Utc1310_CPP | 3077 | 1,266 |
| 0x5f | Utc1310_C | 3077 / 2067 / 2179 | 184 / 12 / 1 |
| 0x0f | Masm 7.10 | 3077 | 11 |
| 0x5a | Linker 7.10 | 3077 | 1 |

plus VC6-era (9178) and older objects that belong to prebuilt libraries. Every
C++ object came out of 13.10.3077, the toolchain the repository already uses.
The residue needs a source-level lever; a compiler swap will not produce one.

### 5. Measurement gaps

The untagged 89% and the unscored 50% are why no tool can say which blocker a
lane should attack. Tagging a verdict with the class whose layout it lacks
(`blocker=layout/Object+0x1c0`) would make #1 schedulable body by body.

## Recommended order

1. Canonical headers from witnessed layouts, `Object` first, then `Player`,
   `AIUpdateInterface`, `Drawable`, `ThingTemplate`. The hook runs the full
   gate for a staged `.h` against `targets/game/reverse/full_gate_baseline.txt`, so one
   header landing costs one full gate.
2. A layout-tagged re-sweep of the large-body banks once a header exists.
3. End-evidence for the ~290 KB of proven starts outside `carved.csv`.

## Reproduce

    python3 tools/progress.py [<ref>]
    python3 tools/gap_census.py
    python3 tools/next_work.py --ranked --limit 3
    # dump census: matched rows whose source ends in .asm, joined on RVA to
    # the latest targets/game/reverse/re_attempts.log verdict and its score= / blocker= fields
    # Rich header: XOR the dwords between 0x80 and 'Rich' with the key that
    # follows 'Rich'; each (prodid<<16|build, count) pair follows 'DanS'.
