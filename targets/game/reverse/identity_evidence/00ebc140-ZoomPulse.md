# Scalar identity at VA 0x012BC140

Corrected: `?ZoomPulse@@3HA` owns the 4-byte `int` scalar at VA 0x012BC140 (RVA 0x00EBC140).

Retail section: `.data`. Initial bytes: `01 00 00 00`. Initial value: `1`.

## Retail facts and contract

ScreenZoomFilter::set at 0x00BD1F00 changes the value by three, clamps at 0 and 30, flips the adjacent pulse-direction byte, and selects tactical-view modes and filters at the endpoints. Reset writers at 0x00B3A860 and 0x00B3B540 set it to one. These reads and writes confirm the pulse-state role.

This is free scalar storage with no receiver. The read, write, and output-address sites below describe its argument contract independently of a decompiler. Each instruction comes from retail bytes. Body addresses use the repository ledger extent when available and Ghidra boundary evidence otherwise.

| Instruction VA | Body VA | Access | Retail instruction |
|---|---|---|---|
| 0x00B3A87B | 0x00B3A860 | write | `mov dword ptr [0x12bc140], 1` |
| 0x00B3B570 | 0x00B3B540 | write | `mov dword ptr [0x12bc140], 1` |
| 0x00BD1F2D | 0x00BD1F00 | read | `mov eax, dword ptr [0x12bc140]` |
| 0x00BD1F63 | 0x00BD1F00 | write | `mov dword ptr [0x12bc140], 0x1e` |
| 0x00BD1F85 | 0x00BD1F00 | read | `mov eax, dword ptr [0x12bc140]` |
| 0x00BD1F9A | 0x00BD1F00 | write | `mov dword ptr [0x12bc140], eax` |
| 0x00BD1FB2 | 0x00BD1F00 | write | `mov dword ptr [0x12bc140], ebp` |
| 0x00BD1FD8 | 0x00BD1F00 | write | `mov dword ptr [0x12bc140], eax` |
| 0x00BD2A3B | 0x00BD24A0 | read | `mov eax, dword ptr [0x12bc140]` |
| 0x00BD2A6F | 0x00BD24A0 | write | `mov dword ptr [0x12bc140], eax` |
| 0x00BD2A7D | 0x00BD24A0 | write | `mov dword ptr [0x12bc140], 0` |
| 0x00BD2A8F | 0x00BD24A0 | write | `mov dword ptr [0x12bc140], eax` |
| 0x00BD2AAE | 0x00BD24A0 | read | `mov eax, dword ptr [0x12bc140]` |

The narrow scan of `data_rows.csv` finds no range overlapping this extent. The DIR32 scan finds no named start strictly inside it. All competing names begin at the same address; the raw probe records both tests. These candidate scalar ranges have no pointer initializer.

## Competing declarations

| DIR32 spelling | Game files declaring this spelling |
|---|---|
| `?R2Glob012BC140@@3HA` | 1 (`game/GameEngine/Source/Common/R2GuardedGlobalCalls.cpp`) |
| `?ZoomPulse@@3HA` | 1 (`game/GameEngineDevice/Source/W3DDevice/GameClient/ScreenZoomFilterSet.cpp`) |

Counts are scoped to typed declarations and definitions, including headers. Similar words in comments or expressions do not count.

## Correction and refutation

The defining translation unit is `game/GameEngineDevice/Source/W3DDevice/GameClient/ScreenZoomFilterSet.cpp`. The sanctioned `tools/add_data_match.py` measurement records its compiled symbol size and verifies its initializer against retail before adding a data row. All existing pins and competing DIR32 rows remain additive evidence; no pin is deleted or rewritten.
If the endpoint tests or the add/subtract-three instructions in ScreenZoomFilter::set refer to a different address, the pulse-state correspondence is wrong.

## Raw local evidence

`build/rlink/scalars-1791167601/retail-012BC140.log` contains byte values, section, overlap checks, pins, and disassembly at every direct occurrence of this VA. `build/rlink/scalars-1791167601/declarations-012BC140.log` contains the unedited game search output. `build/rlink/scalars-1791167601/context-012BC140.log` records EA string bytes and their instruction addresses. Full bodies are in `build/rlink/scalars-1791167601/body-*.log` and `build/rlink/scalars-1791167601/ledger-body-*.log`; the exact ledger identities and extents are in `build/rlink/scalars-1791167601/supplement.log`. `build/rlink/scalars-1791167601/ilt-chains.log` retains each measured five-byte E9 chain. Reference searches are `build/rlink/scalars-1791167601/reference-search.log` and `build/rlink/scalars-1791167601/reference-types-exact.log`. Gate results and LINKED measurements are indexed in `build/worker-final.md`.
