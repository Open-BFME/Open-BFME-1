# Scalar identity at VA 0x012A6F30

Corrected: `?g_debugCRCFromFrame@@3HA` owns the 4-byte `int` scalar at VA 0x012A6F30 (RVA 0x00EA6F30).

Retail section: `.data`. Initial bytes: `ff ff ff ff`. Initial value: `-1`.

## Retail facts and contract

The parser at VA 0x00461260 writes the atoi result. The report at 0x00793880 reads it, compares -1, and formats EA string " -debugCRCFromFrame %d" at VA 0x010EB688.

This is free scalar storage with no receiver. The read, write, and output-address sites below describe its argument contract independently of a decompiler. Each instruction comes from retail bytes. Body addresses use the repository ledger extent when available and Ghidra boundary evidence otherwise.

| Instruction VA | Body VA | Access | Retail instruction |
|---|---|---|---|
| 0x00461284 | 0x00461260 | write | `mov dword ptr [0x12a6f30], eax` |
| 0x00793F3B | 0x00793880 | read | `mov eax, dword ptr [0x12a6f30]` |

The narrow scan of `data_rows.csv` finds no range overlapping this extent. The DIR32 scan finds no named start strictly inside it. All competing names begin at the same address; the raw probe records both tests. These candidate scalar ranges have no pointer initializer.

## Competing declarations

| DIR32 spelling | Game files declaring this spelling |
|---|---|
| `?g_debugCRCFromFrame@@3HA` | 1 (`game/GameEngine/Source/GameLogic/System/GameLogicPopulateGameReport.cpp`) |
| `?g_value12A6F30@@3HA` | 1 (`game/GameEngine/Source/Common/T3CommandLineParsers.cpp`) |

Counts are scoped to typed declarations and definitions, including headers. Similar words in comments or expressions do not count.

## Correction and refutation

The defining translation unit is `game/GameEngine/Source/Common/T3CommandLineParsers.cpp`. The sanctioned `tools/add_data_match.py` measurement records its compiled symbol size and verifies its initializer against retail before adding a data row. All existing pins and competing DIR32 rows remain additive evidence; no pin is deleted or rewritten.
Re-read the report call at VA 0x00793F4D and its preceding load: a different string than debugCRCFromFrame, or a load from another VA, would refute this name.

## Raw local evidence

`build/rlink/scalars-1791167601/retail-012A6F30.log` contains byte values, section, overlap checks, pins, and disassembly at every direct occurrence of this VA. `build/rlink/scalars-1791167601/declarations-012A6F30.log` contains the unedited game search output. `build/rlink/scalars-1791167601/context-012A6F30.log` records EA string bytes and their instruction addresses. Full bodies are in `build/rlink/scalars-1791167601/body-*.log` and `build/rlink/scalars-1791167601/ledger-body-*.log`; the exact ledger identities and extents are in `build/rlink/scalars-1791167601/supplement.log`. `build/rlink/scalars-1791167601/ilt-chains.log` retains each measured five-byte E9 chain. Reference searches are `build/rlink/scalars-1791167601/reference-search.log` and `build/rlink/scalars-1791167601/reference-types-exact.log`. Gate results and LINKED measurements are indexed in `build/worker-final.md`.
