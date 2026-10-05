# Scalar identity at VA 0x012B9664

Corrected: `?g_bfmePeerReqE8@@3HA` owns the 4-byte `int` scalar at VA 0x012B9664 (RVA 0x00EB9664).

Retail section: `.data`. Initial bytes: `ff ff ff ff`. Initial value: `-1`.

## Retail facts and contract

The response writer at 0x008DD2B0 stores this dword from its second rank response. The request at 0x0093AB90 copies it into stack PeerRequest offset 0xE8; profile and best-ladder readers compare it as signed and treat nonpositive ranks as absent. The existing pin names the independently witnessed request field.

This is free scalar storage with no receiver. The read, write, and output-address sites below describe its argument contract independently of a decompiler. Each instruction comes from retail bytes. Body addresses use the repository ledger extent when available and Ghidra boundary evidence otherwise.

| Instruction VA | Body VA | Access | Retail instruction |
|---|---|---|---|
| 0x004A676B | 0x004A5D40 | read | `mov eax, dword ptr [0x12b9664]` |
| 0x004A6781 | 0x004A5D40 | address supplied | `mov eax, 0x12b9664` |
| 0x008DBC54 | 0x008DBBF0 | read | `mov edx, dword ptr [0x12b9664]` |
| 0x008DD4CA | 0x008DD2B0 | write | `mov dword ptr [0x12b9664], ecx` |
| 0x008DD4F3 | 0x008DD2B0 | read | `mov ecx, dword ptr [0x12b9664]` |
| 0x008DD5AC | 0x008DD2B0 | read | `mov edx, dword ptr [0x12b9664]` |
| 0x0093ABB8 | 0x0093AB90 | read | `mov ecx, dword ptr [0x12b9664]` |
| 0x009477A1 | 0x00947730 | read | `mov esi, dword ptr [0x12b9664]` |
| 0x009553FA | 0x00954AA0 | read | `mov eax, dword ptr [0x12b9664]` |
| 0x00955410 | 0x00954AA0 | address supplied | `mov eax, 0x12b9664` |
| 0x0095B7F2 | 0x0095B200 | read | `mov ecx, dword ptr [0x12b9664]` |
| 0x0095BDA3 | 0x0095BDA0 | write | `mov dword ptr [0x12b9664], eax` |

The narrow scan of `data_rows.csv` finds no range overlapping this extent. The DIR32 scan finds no named start strictly inside it. All competing names begin at the same address; the raw probe records both tests. These candidate scalar ranges have no pointer initializer.

## Competing declarations

| DIR32 spelling | Game files declaring this spelling |
|---|---|
| `?g_bfmeAMG@@3HA` | 1 (`game/GameEngine/Source/Common/BfmeConv904.cpp`) |
| `?g_bfmePeerReqE8@@3HA` | 5 (`game/GameEngine/Source/GameClient/GUI/BfmeOnlineProfileScreenRva00554AA0.cpp`, `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineHome.cpp`, `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupPlayerInfo_responses.cpp`, `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/UpdateBestLadderRanks004DBBF0.cpp`, `game/GameEngine/Source/GameClient/GUI/OnlineCustomMatchPeerRequest19.cpp`) |

Counts are scoped to typed declarations and definitions, including headers. Similar words in comments or expressions do not count.

## Correction and refutation

The defining translation unit is `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupPlayerInfo_responses.cpp`. The sanctioned `tools/add_data_match.py` measurement records its compiled symbol size and verifies its initializer against retail before adding a data row. All existing pins and competing DIR32 rows remain additive evidence; no pin is deleted or rewritten.
Recalculate the request stack base at VA 0x0093AB90. If the load is not stored at request offset 0xE8, the field-based spelling is wrong.

## Raw local evidence

`build/rlink/scalars-1791167601/retail-012B9664.log` contains byte values, section, overlap checks, pins, and disassembly at every direct occurrence of this VA. `build/rlink/scalars-1791167601/declarations-012B9664.log` contains the unedited game search output. `build/rlink/scalars-1791167601/context-012B9664.log` records EA string bytes and their instruction addresses. Full bodies are in `build/rlink/scalars-1791167601/body-*.log` and `build/rlink/scalars-1791167601/ledger-body-*.log`; the exact ledger identities and extents are in `build/rlink/scalars-1791167601/supplement.log`. `build/rlink/scalars-1791167601/ilt-chains.log` retains each measured five-byte E9 chain. Reference searches are `build/rlink/scalars-1791167601/reference-search.log` and `build/rlink/scalars-1791167601/reference-types-exact.log`. Gate results and LINKED measurements are indexed in `build/worker-final.md`.
