# Scalar identity at VA 0x012BA0D4

Corrected: `?chatSystemColor@@3HB` owns the 4-byte `const int` scalar at VA 0x012BA0D4 (RVA 0x00EBA0D4).

Retail section: `.data`. Initial bytes: `ff ff ff ff`. Initial value: `0xFFFFFFFF`.

## Retail facts and contract

ZH LANAPICallbacks.cpp:67 defines const Color chatSystemColor = GameMakeColor(255,255,255,255), with Color typedef int. Retail readers in LAN game creation, lobby, and game options pass this white dword to the chat listbox; the complete text scan has no writer. The existing const pin has this exact initial value.

This is free scalar storage with no receiver. The read, write, and output-address sites below describe its argument contract independently of a decompiler. Each instruction comes from retail bytes. Body addresses use the repository ledger extent when available and Ghidra boundary evidence otherwise.

| Instruction VA | Body VA | Access | Retail instruction |
|---|---|---|---|
| 0x008CCFF2 | 0x008CC980 | read | `mov edx, dword ptr [0x12ba0d4]` |
| 0x008CD105 | 0x008CC980 | read | `mov ecx, dword ptr [0x12ba0d4]` |
| 0x008CEDA5 | 0x008CEC00 | read | `mov eax, dword ptr [0x12ba0d4]` |
| 0x00919325 | 0x00919150 | read | `mov ecx, dword ptr [0x12ba0d4]` |
| 0x00A89984 | 0x00A89910 | read | `mov ecx, dword ptr [0x12ba0d4]` |
| 0x00A899A1 | 0x00A89910 | read | `mov edx, dword ptr [0x12ba0d4]` |
| 0x00A899D2 | 0x00A89910 | read | `mov ecx, dword ptr [0x12ba0d4]` |
| 0x00A89D4F | 0x00A89BD0 | read | `mov ecx, dword ptr [0x12ba0d4]` |

The narrow scan of `data_rows.csv` finds no range overlapping this extent. The DIR32 scan finds no named start strictly inside it. All competing names begin at the same address; the raw probe records both tests. These candidate scalar ranges have no pointer initializer.

## Competing declarations

| DIR32 spelling | Game files declaring this spelling |
|---|---|
| `?chatSystemColor@@3HA` | 1 (`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/LanGameOptionsMenu_StartPressed.cpp`) |
| `?chatSystemColor@@3HB` | 2 (`game/GameEngine/Source/GameNetwork/LANAPICallbacks.cpp`, `game/GameEngine/Source/GameNetwork/LANAPIOnGameCreate.cpp`) |

Counts are scoped to typed declarations and definitions, including headers. Similar words in comments or expressions do not count.

## Correction and refutation

The defining translation unit is `game/GameEngine/Source/GameNetwork/LANAPICallbacks.cpp`. The sanctioned `tools/add_data_match.py` measurement records its compiled symbol size and verifies its initializer against retail before adding a data row. All existing pins and competing DIR32 rows remain additive evidence; no pin is deleted or rewritten.
A retail writer to this address, a non-color argument use, or a non-const reference declaration would refute the const LAN system-color correspondence.

## Raw local evidence

`build/rlink/scalars-1791167601/retail-012BA0D4.log` contains byte values, section, overlap checks, pins, and disassembly at every direct occurrence of this VA. `build/rlink/scalars-1791167601/declarations-012BA0D4.log` contains the unedited game search output. `build/rlink/scalars-1791167601/context-012BA0D4.log` records EA string bytes and their instruction addresses. Full bodies are in `build/rlink/scalars-1791167601/body-*.log` and `build/rlink/scalars-1791167601/ledger-body-*.log`; the exact ledger identities and extents are in `build/rlink/scalars-1791167601/supplement.log`. `build/rlink/scalars-1791167601/ilt-chains.log` retains each measured five-byte E9 chain. Reference searches are `build/rlink/scalars-1791167601/reference-search.log` and `build/rlink/scalars-1791167601/reference-types-exact.log`. Gate results and LINKED measurements are indexed in `build/worker-final.md`.
