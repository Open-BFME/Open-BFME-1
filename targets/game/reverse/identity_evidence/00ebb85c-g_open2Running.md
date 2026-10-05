# Scalar identity at VA 0x012BB85C

Corrected: `?g_open2Running@@3EA` owns the 1-byte `unsigned char` scalar at VA 0x012BB85C (RVA 0x00EBB85C).

Retail section: `.data`. Initial bytes: `01`. Initial value: `1`.

## Retail facts and contract

The setter at 0x00B82E80 compares the input byte with the stored state, writes it, and starts or stops a timeGetTime-based accumulated stopwatch. Renderer initialization at 0x00B82ED0 tests that same byte when accumulating elapsed time. The running-state role is established by these instructions.

This is free scalar storage with no receiver. The read, write, and output-address sites below describe its argument contract independently of a decompiler. Each instruction comes from retail bytes. Body addresses use the repository ledger extent when available and Ghidra boundary evidence otherwise.

| Instruction VA | Body VA | Access | Retail instruction |
|---|---|---|---|
| 0x00B82E84 | 0x00B82E80 | read | `cmp byte ptr [0x12bb85c], al` |
| 0x00B82E8E | 0x00B82E80 | write | `mov byte ptr [0x12bb85c], al` |
| 0x00B82F66 | 0x00B82ED0 | read | `mov al, byte ptr [0x12bb85c]` |

The narrow scan of `data_rows.csv` finds no range overlapping this extent. The DIR32 scan finds no named start strictly inside it. All competing names begin at the same address; the raw probe records both tests. These candidate scalar ranges have no pointer initializer.

## Competing declarations

| DIR32 spelling | Game files declaring this spelling |
|---|---|
| `?g_open2Running@@3EA` | 1 (`game/GameEngine/Source/Common/Open2Conv007.cpp`) |
| `?rva012BB85C@@3EA` | 1 (`game/Libraries/Source/WWVegas/WW3D2/RendererInitialize00782ED0.cpp`) |

Counts are scoped to typed declarations and definitions, including headers. Similar words in comments or expressions do not count.

## Correction and refutation

The defining translation unit is `game/GameEngine/Source/Common/Open2Conv007.cpp`. The sanctioned `tools/add_data_match.py` measurement records its compiled symbol size and verifies its initializer against retail before adding a data row. All existing pins and competing DIR32 rows remain additive evidence; no pin is deleted or rewritten.
If the zero-input path does not add current time minus the saved start into the accumulated time, or if the nonzero path does not save the current time, the running-state role is wrong.

## Raw local evidence

`build/rlink/scalars-1791167601/retail-012BB85C.log` contains byte values, section, overlap checks, pins, and disassembly at every direct occurrence of this VA. `build/rlink/scalars-1791167601/declarations-012BB85C.log` contains the unedited game search output. `build/rlink/scalars-1791167601/context-012BB85C.log` records EA string bytes and their instruction addresses. Full bodies are in `build/rlink/scalars-1791167601/body-*.log` and `build/rlink/scalars-1791167601/ledger-body-*.log`; the exact ledger identities and extents are in `build/rlink/scalars-1791167601/supplement.log`. `build/rlink/scalars-1791167601/ilt-chains.log` retains each measured five-byte E9 chain. Reference searches are `build/rlink/scalars-1791167601/reference-search.log` and `build/rlink/scalars-1791167601/reference-types-exact.log`. Gate results and LINKED measurements are indexed in `build/worker-final.md`.
