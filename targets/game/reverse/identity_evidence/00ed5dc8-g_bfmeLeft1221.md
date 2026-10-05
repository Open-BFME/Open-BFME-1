# Scalar identity at VA 0x012D5DC8

Corrected: `?g_bfmeLeft1221@@3HA` owns the 4-byte `int` scalar at VA 0x012D5DC8 (RVA 0x00ED5DC8).

Retail section: `.data`. Initial bytes: `ff ff ff ff`. Initial value: `-1`.

## Retail facts and contract

The seeder at 0x00CD3AB0 clears the dword. Reload at 0x00CD3AE0 tests -1 and sets 623 while resetting the next-state pointer. The next-value body at 0x00CD3C00 decrements the dword and reloads when negative before advancing the separate pointer. This is the number of state words left, rather than an array index.

This is free scalar storage with no receiver. The read, write, and output-address sites below describe its argument contract independently of a decompiler. Each instruction comes from retail bytes. Body addresses use the repository ledger extent when available and Ghidra boundary evidence otherwise.

| Instruction VA | Body VA | Access | Retail instruction |
|---|---|---|---|
| 0x00CD3AB7 | 0x00CD3AB0 | write | `mov dword ptr [0x12d5dc8], 0` |
| 0x00CD3AE0 | 0x00CD3AE0 | read | `cmp dword ptr [0x12d5dc8], -1` |
| 0x00CD3B0F | 0x00CD3AE0 | write | `mov dword ptr [0x12d5dc8], 0x26f` |
| 0x00CD3C00 | 0x00CD3C00 | read and write | `dec dword ptr [0x12d5dc8]` |

The narrow scan of `data_rows.csv` finds no range overlapping this extent. The DIR32 scan finds no named start strictly inside it. All competing names begin at the same address; the raw probe records both tests. These candidate scalar ranges have no pointer initializer.

## Competing declarations

| DIR32 spelling | Game files declaring this spelling |
|---|---|
| `?g_bfmeIndexFA@@3HA` | 1 (`game/GameEngine/Source/Common/Bfme5SeventyFour.cpp`) |
| `?g_bfmeLeft1221@@3HA` | 1 (`game/GameEngine/Source/Common/BfmeConv1221.cpp`) |

Counts are scoped to typed declarations and definitions, including headers. Similar words in comments or expressions do not count.

## Correction and refutation

The defining translation unit is `game/GameEngine/Source/Common/Bfme5SeventyFour.cpp`. The sanctioned `tools/add_data_match.py` measurement records its compiled symbol size and verifies its initializer against retail before adding a data row. All existing pins and competing DIR32 rows remain additive evidence; no pin is deleted or rewritten.
If the decrement branch is not the condition that reloads the separate next-state pointer, or if the value is directly used as an array index, the remaining-word interpretation is wrong.

## Raw local evidence

`build/rlink/scalars-1791167601/retail-012D5DC8.log` contains byte values, section, overlap checks, pins, and disassembly at every direct occurrence of this VA. `build/rlink/scalars-1791167601/declarations-012D5DC8.log` contains the unedited game search output. `build/rlink/scalars-1791167601/context-012D5DC8.log` records EA string bytes and their instruction addresses. Full bodies are in `build/rlink/scalars-1791167601/body-*.log` and `build/rlink/scalars-1791167601/ledger-body-*.log`; the exact ledger identities and extents are in `build/rlink/scalars-1791167601/supplement.log`. `build/rlink/scalars-1791167601/ilt-chains.log` retains each measured five-byte E9 chain. Reference searches are `build/rlink/scalars-1791167601/reference-search.log` and `build/rlink/scalars-1791167601/reference-types-exact.log`. Gate results and LINKED measurements are indexed in `build/worker-final.md`.
