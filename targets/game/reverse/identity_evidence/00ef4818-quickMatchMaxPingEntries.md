# Scalar identity at VA 0x012F4818

Corrected: `?quickMatchMaxPingEntries@@3HA` owns the 4-byte `int` scalar at VA 0x012F4818 (RVA 0x00EF4818).

Retail section: `.data`. Initial bytes: `00 00 00 00`. Initial value: `0`.

## Retail facts and contract

The quick-match gadget initializer at 0x009091F0 computes (pingTimeout-1)/100+1, stores the signed dword, iterates that many ping entries, and clamps the selected index to value-1. The request at 0x00909B30 applies the same upper bound. The progress body at 0x00905410 reads it as its denominator. The ping-entry role is broader and directly established by its writer.

This is free scalar storage with no receiver. The read, write, and output-address sites below describe its argument contract independently of a decompiler. Each instruction comes from retail bytes. Body addresses use the repository ledger extent when available and Ghidra boundary evidence otherwise.

| Instruction VA | Body VA | Access | Retail instruction |
|---|---|---|---|
| 0x00905411 | 0x00905410 | read | `mov eax, dword ptr [0x12f4818]` |
| 0x0090972A | 0x009091F0 | write | `mov dword ptr [0x12f4818], edx` |
| 0x0090977D | 0x009091F0 | read | `mov eax, dword ptr [0x12f4818]` |
| 0x009097D1 | 0x009091F0 | read | `mov eax, dword ptr [0x12f4818]` |
| 0x00909C99 | 0x00909B30 | read | `mov ecx, dword ptr [0x12f4818]` |

The narrow scan of `data_rows.csv` finds no range overlapping this extent. The DIR32 scan finds no named start strictly inside it. All competing names begin at the same address; the raw probe records both tests. These candidate scalar ranges have no pointer initializer.

## Competing declarations

| DIR32 spelling | Game files declaring this spelling |
|---|---|
| `?g_bfmeQuickMatchProgressDenom@@3HA` | 1 (`game/GameEngine/Source/GameClient/GUI/BfmeQuickMatchProgressBody.cpp`) |
| `?quickMatchMaxPingEntries@@3HA` | 3 (`game/GameEngine/Source/GameClient/GUI/AptScreenFactories.cpp`, `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuInitGadgets.cpp`, `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuRequest.cpp`) |

Counts are scoped to typed declarations and definitions, including headers. Similar words in comments or expressions do not count.

## Correction and refutation

The defining translation unit is `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuInitGadgets.cpp`. The sanctioned `tools/add_data_match.py` measurement records its compiled symbol size and verifies its initializer against retail before adding a data row. All existing pins and competing DIR32 rows remain additive evidence; no pin is deleted or rewritten.
The stored value must bound the initializer loop of 100-unit millisecond options and the request selection. A separate progress-only counter or another loop-bound address would refute the ping-entry spelling.

## Raw local evidence

`build/rlink/scalars-1791167601/retail-012F4818.log` contains byte values, section, overlap checks, pins, and disassembly at every direct occurrence of this VA. `build/rlink/scalars-1791167601/declarations-012F4818.log` contains the unedited game search output. `build/rlink/scalars-1791167601/context-012F4818.log` records EA string bytes and their instruction addresses. Full bodies are in `build/rlink/scalars-1791167601/body-*.log` and `build/rlink/scalars-1791167601/ledger-body-*.log`; the exact ledger identities and extents are in `build/rlink/scalars-1791167601/supplement.log`. `build/rlink/scalars-1791167601/ilt-chains.log` retains each measured five-byte E9 chain. Reference searches are `build/rlink/scalars-1791167601/reference-search.log` and `build/rlink/scalars-1791167601/reference-types-exact.log`. Gate results and LINKED measurements are indexed in `build/worker-final.md`.
