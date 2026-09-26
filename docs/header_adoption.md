# Header adoption: giving a type one definition instead of a thousand

## The problem is not missing headers

The tree has 533 headers against the original's 1,471, and the natural reading is
that headers need writing. That reading is wrong, and it sent an earlier plan
after 940 headers that did not need to exist.

`game/Libraries/Source/WWVegas/WWLib/ascii_string.h` is a complete, byte-evidenced
`AsciiString` and has been all along. When this lane started, 45 translation units
included it and **1,342 declared their own copy instead**. That is what makes the
tree unnavigable: not that a type has no definition to jump to, but that it has a
thousand, and no two of them agree about what the type can do.

Measured over the whole tree:

| | count |
|---|---|
| TU-local `class`/`struct` bodies inside `.cpp` | **60,921** |
| ...for a type a header already defines | 7,838 (426 types) |
| ...for a type with no header at all | 53,083 (33,900 types) |
| `.cpp` files | 15,180 |

## What adoption can and cannot buy

`tools/readability_metric.py` scores `SSoT` as
`1 - bodies / (bodies + cpp_files)`. Adopting **every** header that already
exists, for every TU that could take it, moves it:

    SSoT 19.9  ->  22.2

That is the whole ceiling of this lane: **2.3 points.** The metric is dominated by
the 53,083 bodies for types no header defines, and most of those are honest —
a TU standing up `struct Gen_p12pod { int a[3]; }` for an opaque vector element is
not the problem. The types that are the problem are the real ones: `AsciiString`
1,342, `Object` 815, `Player` 206. Judge this lane by those counts, not by SSoT.

## Cleanup loses to creation about 2:1

New `.cpp` files landing per day, and the shim bodies they bring:

| day | new `.cpp` | shim bodies | ...for a type that HAS a header |
|---|---|---|---|
| 2026-09-09 | 259 | 1,060 | 203 |
| 2026-09-10 | 308 | 1,306 | 260 |
| 2026-09-11 | 285 | 1,385 | 329 |
| 2026-09-12 | 274 | 1,309 | 343 |

The conversion fleet writes ~300 newly-adoptable bodies a day. The entire pool is
7,838, so the fleet reconstitutes this lane's whole reach every 26 days and adds
to it faster than a single session drains it. **Draining is not the finishing
move; the commit gate is.** `tools/adopt_header.py --check --staged` refuses a
staged source that redeclares a type with a canonical header, and `--fix-staged`
does the swap. Without that, this lane is a treadmill.

## Which header is canonical

The earlier inventory found 62 types defined by more than one header, including the
high-leverage ones:

| type | TU-local | headers |
|---|---|---|
| `AsciiString` | 1,342 | `ascii_string.h` (507 includers), `module_factory.h` (2) |
| `Coord3D` | 506 | `basetype.h`, `coord.h`, `coord3d.h` |
| `GameLogic` | 354 | `game_engine_subsystems.h`, `game_logic.h`, `game_logic_dispatch.h` |
| `INI` | 350 | `INI.h`, `fx_particle_system.h` |
| `ICoord2D` | 126 | `basetype.h`, `coord.h`, `icoord.h` |
| `Snapshot` | 115 | `Snapshot.h`, `snapshot.h` |

**The byte gate cannot pick between them.** It says a spelling compiles to the
same bytes, never that it is the right one — the same blindness that lets a
plausible wrong member name through. `AsciiString` was safe to call: the two
definitions have the same layout and one has 507 includers to the other's 2.
`Coord3D`'s three disagree structurally (`coord3d.h` gives it a base class), so
it is not in `HEADERS` and must not be added until somebody settles it on
evidence. `HEADERS` holds only types with exactly one definition in the tree.

## The tool

    python3 tools/adopt_header.py --type StringBase --count 250 --commit
    python3 tools/adopt_header.py --check --staged     # what the hook runs
    python3 tools/adopt_header.py --fix-staged         # the fix it names

A TU is a candidate when its shim has the header's layout (for these three types,
exactly one scalar member, no array) and spells nothing the header brings in.
Collisions are derived from the header text and its quoted includes rather than
listed, because the set differs per header: `ascii_string.h` pulls in
`string_base.h`, so a TU with its own `class StringBase` cannot take it.

Adopt in dependency order. `StringBase` first: it unblocks 68 `AsciiString`
candidates that were only refused for carrying their own copy of it.

## Traps this lane has already paid for

**`build.sh` reports compile failures on stderr.** The first version of the gate
captured stdout and stderr separately, parsed only stdout, and printed
`byte gate: 8 kept, 0 reverted` for a batch in which **five had not compiled at
all.** A gate that cannot explain a failure now raises instead of guessing.

**One bad TU aborts the whole scoped build.** `compile_source` raises SystemExit,
so a batch gate learns nothing about the other 199 files. Gating each file alone,
eight at a time, costs 0.6s per file and attributes every rejection exactly. This
replaced a retry loop that needed nine rounds to converge on 40 files.

**Do not predict what the compiler knows.** About a third of layout-clean shims
still fail, because they declare methods the header lacks (`releaseBuffer`,
`freeBytes`, `bfmeCompare1294`). Telling those apart from calls inside inline
bodies means parsing C++ with regex; two attempts produced `arguments`, `ctor` and
`return` as method names. Ask the compiler and record the answer in
`targets/game/reverse/header_adopt_blocked.tsv`, which is the exemption list.

**`StringBase` is a template in all 431 of its copies.** Replacing the class body
alone leaves `template <typename T>` hanging over an `#include`. The shim pattern
consumes that line.

**Some files cannot be committed at all.** They define a function no ledger row
declares, which predates this lane and needs a row, not a header. `build.sh` is
silent about it; only the hook says so, and it names the file. The tool sheds what
the hook names and records it.

**`identity_guard` will fail on a stale object.** Compiling a few hundred TUs
surfaces `multi_name.different: 0 -> 2`. The check prints its own verdict —
`-> DIRTY`, and the source whose object no longer matches. Rebuild that one source
and re-run; it is an artifact, not a ledger defect. Never settle a row to go green.

## What is left

490 TUs adopted and byte-verified; `ascii_string.h` includers 45 -> 507. The pool
of shims that pass the pre-filter is **empty** -- every remaining copy either has a
different layout, spells something the header brings in, or was refused by the
compiler and recorded. The gate is what carries this from here.

| type | TU-local copies left | why they stay |
|---|---|---|
| `AsciiString` | 489 | 99 different layout, 68 own `StringBase`, 50 own `operator==`, 47 own `Header` |
| `StringBase` | 316 | 90 own `Header`, 86 different layout |
| `UnicodeString` | 112 | 24 different layout, 13 own `StringBase` |
| recorded compiler refusals | 442 | declare `releaseBuffer`, `freeBytes`, `bfmeCompare1294` -- methods the header does not have |

The factory header now includes the canonical `AsciiString` definition; its
private copy is gone. One follow-up remains:

* **The compiler refusals name what the header is missing.** 442 shims declare
  `releaseBuffer` and friends. Adding those to `ascii_string.h` -- on evidence,
  not on demand -- would reopen most of that pool in one full gate.

## Member-name evidence snapshot (2026-09-24)

The earlier bulk-rename proposal was based on a witness that has since been
re-generated from `--compile` objects alone (commit `ca805da376`). The current
oracle does **not** support applying that recipe as written:

* `python3 tools/name_oracle.py --class AsciiString --offset 0` exits 2:
  there is no BFME witness for `AsciiString`; its `m_data` result is only a ZH
  layout hint, which does not prove the retail member name.
* `python3 tools/name_oracle.py --class UnicodeString --offset 0` reports
  `m_data` at confidence 1.00. `unicode_string.h` still spells the member
  `m_text`, and `python3 tools/name_oracle.py --check
  game/Libraries/Source/WWVegas/WWLib/unicode_string.h` reports one conflict.
  This is a real disagreement to review, not a basis for renaming every
  `m_text` occurrence across both string classes.

The witness is an inference from aligned retail accesses, not direct source
symbols; `docs/bfme_layouts.md` documents its limits, including ambiguous tiny
bodies. Resolve the Unicode disagreement with the relevant uses and witness
provenance before changing names. Do not infer an `AsciiString` name from the
ZH hint.

This is a recorded evidence snapshot, not a current gate forecast. A staged
header or shim runs the full gate. The hook compares its red rows against the
shrink-only `targets/game/reverse/full_gate_baseline.txt` via `tools/gate_baseline.py`; it
rejects new red rows and gate failures before byte comparison, while known red
rows do not by themselves prohibit a header change. Commit `9c397c6e37` landed
`Object` headers and moved 52 TUs on 2026-09-24, so the former claim that no
header could land is obsolete. The hook and baseline are authoritative for a
new change.

The earlier bulk rename experiment was measured before the witness
regeneration. It byte-verified 424 includers, with one pre-existing failing TU,
and found two traps that remain useful when reviewing a member rename:

* Member uses can be unqualified: `unicode_string.cpp` refers to `m_text`
  inside `UnicodeString` methods, so searching only `\.m_text` and `->m_text`
  misses them. Identify the declaring class before changing a same-spelled
  member in another type.
* A cached object can make a scoped header build look green without compiling
  the changed source. Check the `Compile: N of M` line and ensure the edited
  source was rebuilt.

Those historical results do not establish that a proposed rename is correct
under the current witness, nor that the full gate will pass today.
