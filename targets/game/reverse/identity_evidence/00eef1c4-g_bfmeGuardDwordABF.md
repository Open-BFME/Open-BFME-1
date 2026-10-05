# Scalar identity at VA 0x012EF1C4

Corrected: `?g_bfmeGuardDwordABF@@3IA` owns the 4-byte `unsigned int` scalar at VA 0x012EF1C4 (RVA 0x00EEF1C4).

Retail section: `.data`. Initial bytes: `00 00 00 00`. Initial value: `0`.

## Retail facts and contract

The builder at 0x005245F0 reads the low byte with mov dl, tests bit one, and sets the guard using or dword ptr [0x012EF1C4],ecx before filling two parse-table records. The dword write proves four-byte storage; the low-byte spelling is a narrow access to that same guard.

This is free scalar storage with no receiver. The read, write, and output-address sites below describe its argument contract independently of a decompiler. Each instruction comes from retail bytes. Body addresses use the repository ledger extent when available and Ghidra boundary evidence otherwise.

| Instruction VA | Body VA | Access | Retail instruction |
|---|---|---|---|
| 0x00524603 | 0x005245F0 | read | `mov dl, byte ptr [0x12ef1c4]` |
| 0x00524614 | 0x005245F0 | read and write | `or dword ptr [0x12ef1c4], ecx` |

The narrow scan of `data_rows.csv` finds no range overlapping this extent. The DIR32 scan finds no named start strictly inside it. All competing names begin at the same address; the raw probe records both tests. These candidate scalar ranges have no pointer initializer.

## Competing declarations

| DIR32 spelling | Game files declaring this spelling |
|---|---|
| `?g_bfmeGuardByteABF@@3EA` | 1 (`game/GameEngine/Source/Common/BfmeConv2129.cpp`) |
| `?g_bfmeGuardDwordABF@@3IA` | 1 (`game/GameEngine/Source/Common/BfmeConv2129.cpp`) |

Counts are scoped to typed declarations and definitions, including headers. Similar words in comments or expressions do not count.

## Correction and refutation

The defining translation unit is `game/GameEngine/Source/Common/BfmeConv2129.cpp`. The sanctioned `tools/add_data_match.py` measurement records its compiled symbol size and verifies its initializer against retail before adding a data row. All existing pins and competing DIR32 rows remain additive evidence; no pin is deleted or rewritten.
A nonzero DIR32 start inside the four-byte range, or evidence that the dword OR belongs to another object, would refute the four-byte guard. The current retyping passed with the original byte-load instruction unchanged.

## Raw local evidence

`build/rlink/scalars-1791167601/retail-012EF1C4.log` contains byte values, section, overlap checks, pins, and disassembly at every direct occurrence of this VA. `build/rlink/scalars-1791167601/declarations-012EF1C4.log` contains the unedited game search output. `build/rlink/scalars-1791167601/context-012EF1C4.log` records EA string bytes and their instruction addresses. Full bodies are in `build/rlink/scalars-1791167601/body-*.log` and `build/rlink/scalars-1791167601/ledger-body-*.log`; the exact ledger identities and extents are in `build/rlink/scalars-1791167601/supplement.log`. `build/rlink/scalars-1791167601/ilt-chains.log` retains each measured five-byte E9 chain. Reference searches are `build/rlink/scalars-1791167601/reference-search.log` and `build/rlink/scalars-1791167601/reference-types-exact.log`. Gate results and LINKED measurements are indexed in `build/worker-final.md`.
