# Header adoption: giving a type one definition instead of a thousand

Most headers the tree needs already exist. The problem is TU-local copies:
`game/Libraries/Source/WWVegas/WWLib/ascii_string.h` is a complete, byte-evidenced
`AsciiString`, yet over a thousand TUs declared their own. Adopt existing headers
before writing new ones.

Judge this lane by the TU-local copy counts of real types (`AsciiString`, `Object`,
`Player`), not by `SSoT` in `tools/readability_metric.py`. That metric is dominated
by opaque shims for types no header defines, which are mostly honest.

## The tool

    python3 tools/adopt_header.py --type StringBase --count 250 --commit
    python3 tools/adopt_header.py --check --staged     # what the commit hook runs
    python3 tools/adopt_header.py --fix-staged         # swap, byte-gate, restage

The hook refuses a staged source that redeclares `AsciiString`, `UnicodeString` or
`StringBase` in a form the header could replace; `--fix-staged` does the swap.
Conversions keep writing new shims, so this gate, not batch cleanup, is what
finishes the lane.

A TU is a candidate when its shim has the header's layout (the same number of
scalar members and no array) and spells nothing the header brings in, including
through the header's quoted includes: `ascii_string.h` pulls in `string_base.h`,
so a TU with its own `StringBase` cannot take it. Adopt in dependency order,
`StringBase` first.

## Which header is canonical

The byte gate cannot choose between two headers that define a type; it only shows
that a spelling compiles to the same bytes. So the tool takes only types that
exactly one header defines, plus `AsciiString` and `UnicodeString`, whose headers
were settled by review. `Coord3D`'s three headers disagree structurally
(`coord3d.h` gives it a base class); do not adopt it, or other multi-header types
such as `GameLogic`, `INI`, `ICoord2D` and `Snapshot`, until one is settled on
evidence.

## Traps

- Ask the compiler; do not predict. Many layout-clean shims still fail because they
  declare methods the header lacks (`releaseBuffer`, `freeBytes`,
  `bfmeCompare1294`), and regex cannot tell those from calls in inline bodies.
  Record each refusal in `targets/game/reverse/header_adopt_blocked.tsv`, the
  exemption list.
- Gate one file at a time. `build.sh` stops at the first compile error and reports
  it on stderr, so a batch gate learns nothing about the other files.
- Replace a `StringBase` shim together with its `template <typename T>` line.
- A cached object can make a scoped build look green without compiling the edited
  source. Check the `Compile: N of M` line.
- If `identity_guard` fails after many compiles, read its verdict: `-> DIRTY` means
  stale objects. Rebuild the sources it names and re-run. Never edit the ledger to
  go green.
- A staged header or shim runs the full gate against the shrink-only
  `targets/game/reverse/full_gate_baseline.txt` (`tools/gate_baseline.py`). Known
  red rows do not block a header change; new ones do.

## What is left

No shim that passes the pre-filter remains; the commit hook carries the lane. The
remaining copies have a different layout, spell something the header brings in
(`StringBase`, `operator==`, `Header`), or were refused by the compiler. Those
refusals name what `ascii_string.h` lacks: adding the missing methods, on evidence,
would reopen most of that pool in one full gate.

## Member names in the string headers

- `name_oracle.py --class AsciiString --offset 0` exits 2: there is no BFME
  witness, and `m_data` is only a ZH hint. Do not rename from it.
- The witness names `UnicodeString+0x0` `m_data`; `unicode_string.h` spells it
  `m_text`, and `name_oracle.py --check` reports the conflict. Settle it from the
  uses and the witness provenance before renaming.
- Member uses can be unqualified (`m_text` inside `UnicodeString` methods), so a
  search for `.m_text` and `->m_text` misses them. Identify the declaring class
  before renaming a same-spelled member in another type.
