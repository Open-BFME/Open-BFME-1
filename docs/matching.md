# Matching a function

1. Write the C++ under `game/` at its official-tree path (see
   [Reference source](#reference-source)) and add its row to
   `targets/game/reverse/functions.csv`.
2. Run `./build.sh game/path/to/file.cpp` (or a function name). It compiles
   that source with MSVC 7.1 and byte-compares it; any mismatch fails.
3. Commits and pushes gate only their delta; the commit hook adds the full
   gate after a header or shim change. After resolving a merge, run the full
   gate once yourself: `python3 tools/gate_baseline.py --check`.

## Relocations

The build fills relocation slots, so those bytes need not match, but it
checks what they point at.

- **DIR32** (constants, vtables, string literals). A string literal must
  byte-equal the string at the referenced address (`verify_string_refs`), so
  `"%S"` and `"%ls"` differ. A global or vtable symbol must resolve to one
  address across all its references (`verify_dir32_consistency`). Write the
  real literal, not a lookalike.
- **REL32** (calls, jumps). A matched callee resolves automatically. For
  anything else (CRT helpers like `__ftol2`, functions not yet matched) add
  `name,address` to `targets/game/reverse/symbols.csv`; the build prints the
  unresolved name. Get the address by disassembling the call in the target,
  or from the Ghidra inventory (`tools/ghidra/`).
- Append pins with the file's own line terminator (CRLF). `check_csv` rejects
  a mixed file; `python3 tools/dedup_csv.py` repairs one.

Leaf functions (no calls) are the easiest; pins make the rest matchable.

## Iteration tools

- `python3 tools/explain_mismatch.py <decorated-symbol>` compiles the function
  and prints the first byte difference, byte windows and side-by-side
  target/compiled disassembly.
- `python3 tools/list_naked_candidates.py game` picks one tracked naked-asm
  body and prints its `./build.sh '<symbol>'` command. `--ranked --groups`
  shows repeated byte patterns; `--all` includes untracked functions.
- The naked-candidate queue and `tools/audit_ret_arity.py` need the `capstone`
  package (`python3 -m pip install -r tools/requirements.txt`). A missing
  decoder is an error, never a reason to skip the check.

## MSVC 7.1 shaping

Start with `docs/shape_levers.md`. It maps each "everything matches except..."
symptom to the source change that fixes it.

A near-match is a failure. If a candidate differs only by register choice,
branch layout or x87 operand order, revert it unless the exact decorated-symbol
check passes.

Known traps. When a diff shows one, move to another function family, or first
prove the exact instruction shape in a targeted build:

- `register` does not make MSVC 7.1 preload a constant. `Matrix4D::Set(const
  Coord3D&)` keeps `0x3f800000` near first use; the target loads it early.
- Equivalent x87 expressions compile differently. Commuted multiply operands
  change the `fld`/`fmul` order (`Coord3D::CrossProduct`).
- Ternary min/max can flip between integer bit copies and x87 stores.
  `RealRange::combine` needs both the target's condition flags and its raw
  float copy.
- Pointer/index loops are unstable. `Matrix4D::IsExactlyEqualTo` does not give
  the target's four-dword xor/or block.
- Virtual-call wrappers can match in meaning but save registers or branch
  differently (`Xfer::XferRawBytes`).

One positive pattern: MSVC 7.1 groups overloaded virtual operators at the first
overload's slot, in reverse declaration order. The `Debug` shim declares its
stream overloads so `float`, `unsigned int`, `int` and `const char *` land at
the target's vtable slots `0x20`, `0x30`, `0x34` and `0x38`.

## Reference source

BFME is the SAGE engine. Most of its original source survives in the vendored
`inputs/reference/CnC_Generals_Zero_Hour/` (GPLv3, like this repo). BFME forks
from Zero Hour: **always port from `GeneralsMD/`, never `Generals/`.** Many
functions match verbatim. The binary is the source of truth.

`tools/ghidra/README.md` covers the Ghidra function inventory, including why
its sizes are not exact body extents.

### Rows sourced from the vendored tree

- A ledger row may name an `inputs/reference/` file directly; `./build.sh
  <that file>` builds it.
- Never edit that tree: its value is being unmodified upstream. Its files
  carry no `// stlport` marker or `// cl:` line; `build.py` derives both from
  the path (the ZH include set, and STLport everywhere outside
  `Libraries/Source/WWVegas/`).
- `tools/conversion_gate.py` scans only `game/` for `__emit` lifts (some
  vendored files legitimately contain `__emit`). Its rule that a matched RVA
  keeps its clean C++ source covers these rows too.
- Do not try to string-anchor `tools/zh_sweep.py`'s exact matches that place
  at more than one address. The ones distinctive enough to anchor are already
  claimed.

## Third-party code the binary links

Read each library's provenance before drawing conclusions from its files.

- **nbench / BYTEmark 2.1, pre-Dierks** (`0x008739A0-0x0087A4A0`):
  `inputs/vendor/nbench/` holds the 2.2.3 tarball, used for headers only (LSM
  copying policy: "freely distributable"); `inputs/vendor/nbench/PROVENANCE.md` explains.
- **GameSpy Chat + Peer** (Chat `0x0085E000-0x00870000`, Peer
  `0x00870000-0x00878000`): permitted. The owner confirmed that the project's
  permission covers the 2007 GameSpy SDK, Chat and Peer included. The files
  still carry no grant, so read
  `game/GameEngine/Source/GameNetwork/GameSpy/PROVENANCE.txt` for the scope
  and its limits before judging from the tree.
