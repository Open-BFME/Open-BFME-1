# Scalar identity at VA 0x012F3E6D

Corrected: `?g_bfmeDirtyYH@@3_NA` owns the 1-byte `bool` scalar at VA 0x012F3E6D (RVA 0x00EF3E6D).

Retail section: `.data`. Initial bytes: `00`. Initial value: `false`.

## Retail facts and contract

The MapSelect menu readers at 0x008D1020 and 0x008D1BD0 test the byte, initialization and the cancel path clear it, and the label commit at 0x008D1080 sets it before updating the map label and requesting shell transition. ZH MapSelectMenu.cpp uses Bool for the corresponding buttonPushed flag. The bool spelling matches that flag contract.

This is free scalar storage with no receiver. The read, write, and output-address sites below describe its argument contract independently of a decompiler. Each instruction comes from retail bytes. Body addresses use the repository ledger extent when available and Ghidra boundary evidence otherwise.

| Instruction VA | Body VA | Access | Retail instruction |
|---|---|---|---|
| 0x008D1020 | 0x008D1020 | read | `mov al, byte ptr [0x12f3e6d]` |
| 0x008D10AE | 0x008D1080 | write | `mov byte ptr [0x12f3e6d], 1` |
| 0x008D13A9 | 0x008D1370 | write | `mov byte ptr [0x12f3e6d], bl` |
| 0x008D1B0A | 0x008D1B00 | write | `mov byte ptr [0x12f3e6d], 0` |
| 0x008D1BD0 | 0x008D1BD0 | read | `mov al, byte ptr [0x12f3e6d]` |

The narrow scan of `data_rows.csv` finds no range overlapping this extent. The DIR32 scan finds no named start strictly inside it. All competing names begin at the same address; the raw probe records both tests. These candidate scalar ranges have no pointer initializer.

## Competing declarations

| DIR32 spelling | Game files declaring this spelling |
|---|---|
| `?g_bfmeDirtyYH@@3EA` | 1 (`game/GameEngine/Source/Common/BfmeConv2123.cpp`) |
| `?g_bfmeDirtyYH@@3_NA` | 1 (`game/GameEngine/Source/Common/BfmeLabelCommitYH.cpp`) |

Counts are scoped to typed declarations and definitions, including headers. Similar words in comments or expressions do not count.

## Correction and refutation

The defining translation unit is `game/GameEngine/Source/Common/BfmeLabelCommitYH.cpp`. The sanctioned `tools/add_data_match.py` measurement records its compiled symbol size and verifies its initializer against retail before adding a data row. All existing pins and competing DIR32 rows remain additive evidence; no pin is deleted or rewritten.
The MapSelect shutdown/update predicates must read the same byte the label commit sets. A different address or a wider state value in these sites would refute the boolean commit-flag correspondence.

## Raw local evidence

`build/rlink/scalars-1791167601/retail-012F3E6D.log` contains byte values, section, overlap checks, pins, and disassembly at every direct occurrence of this VA. `build/rlink/scalars-1791167601/declarations-012F3E6D.log` contains the unedited game search output. `build/rlink/scalars-1791167601/context-012F3E6D.log` records EA string bytes and their instruction addresses. Full bodies are in `build/rlink/scalars-1791167601/body-*.log` and `build/rlink/scalars-1791167601/ledger-body-*.log`; the exact ledger identities and extents are in `build/rlink/scalars-1791167601/supplement.log`. `build/rlink/scalars-1791167601/ilt-chains.log` retains each measured five-byte E9 chain. Reference searches are `build/rlink/scalars-1791167601/reference-search.log` and `build/rlink/scalars-1791167601/reference-types-exact.log`. Gate results and LINKED measurements are indexed in `build/worker-final.md`.
