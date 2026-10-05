# Scalar identity at VA 0x012F3D4A

Corrected: `?LANbuttonPushed@@3_NA` owns the 1-byte `bool` scalar at VA 0x012F3D4A (RVA 0x00EF3D4A).

Retail section: `.data`. Initial bytes: `00`. Initial value: `false`.

## Retail facts and contract

ZH LanLobbyMenu.cpp:65 defines Bool LANbuttonPushed=false. Retail LAN callbacks and menu input writers set this byte to one, lobby initialization clears it, and LAN/menu readers test it to gate transition processing. These operations match the reference boolean contract.

This is free scalar storage with no receiver. The read, write, and output-address sites below describe its argument contract independently of a decompiler. Each instruction comes from retail bytes. Body addresses use the repository ledger extent when available and Ghidra boundary evidence otherwise.

| Instruction VA | Body VA | Access | Retail instruction |
|---|---|---|---|
| 0x008CB197 | 0x008CB190 | read | `mov al, byte ptr [0x12f3d4a]` |
| 0x008CD4AC | 0x008CD470 | read | `mov al, byte ptr [0x12f3d4a]` |
| 0x008CDAB7 | 0x008CDA50 | write | `mov byte ptr [0x12f3d4a], bl` |
| 0x008CDFC0 | 0x008CDF20 | read | `mov al, byte ptr [0x12f3d4a]` |
| 0x008CE06E | 0x008CDF20 | read | `mov al, byte ptr [0x12f3d4a]` |
| 0x008CE27D | 0x008CDF20 | read | `mov al, byte ptr [0x12f3d4a]` |
| 0x008CE509 | 0x008CDF20 | read | `mov al, byte ptr [0x12f3d4a]` |
| 0x008CE7B7 | 0x008CE7B0 | read | `mov al, byte ptr [0x12f3d4a]` |
| 0x008CEA41 | 0x008CE980 | read | `cmp byte ptr [0x12f3d4a], bl` |
| 0x008CEC8B | 0x008CEC00 | read | `mov al, byte ptr [0x12f3d4a]` |
| 0x008CECAF | 0x008CEC00 | write | `mov byte ptr [0x12f3d4a], 1` |
| 0x008CEEB0 | 0x008CEC00 | read | `mov al, byte ptr [0x12f3d4a]` |
| 0x008CEF57 | 0x008CEC00 | read | `mov al, byte ptr [0x12f3d4a]` |
| 0x008CF13A | 0x008CEC00 | read | `mov al, byte ptr [0x12f3d4a]` |
| 0x008CF21F | 0x008CEC00 | read | `mov al, byte ptr [0x12f3d4a]` |
| 0x008CF4CC | 0x008CF440 | write | `mov byte ptr [0x12f3d4a], 0` |
| 0x008D2728 | 0x008D2700 | write | `mov byte ptr [0x12f3d4a], 0` |
| 0x008D3B22 | 0x008D3970 | write | `mov byte ptr [0x12f3d4a], 1` |
| 0x00A87111 | 0x00A870F0 | read | `mov al, byte ptr [0x12f3d4a]` |
| 0x00A87170 | 0x00A870F0 | read | `mov al, byte ptr [0x12f3d4a]` |
| 0x00A87351 | 0x00A870F0 | read | `mov al, byte ptr [0x12f3d4a]` |
| 0x00A88AF3 | 0x00A88AD0 | write | `mov byte ptr [0x12f3d4a], 1` |
| 0x00A894F9 | 0x00A894B0 | write | `mov byte ptr [0x12f3d4a], 1` |
| 0x00A89945 | 0x00A89910 | write | `mov byte ptr [0x12f3d4a], 1` |
| 0x00A8AB0D | 0x00A8A900 | write | `mov byte ptr [0x12f3d4a], 1` |

The narrow scan of `data_rows.csv` finds no range overlapping this extent. The DIR32 scan finds no named start strictly inside it. All competing names begin at the same address; the raw probe records both tests. These candidate scalar ranges have no pointer initializer.

## Competing declarations

| DIR32 spelling | Game files declaring this spelling |
|---|---|
| `?LANbuttonPushed@@3_NA` | 10 (`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/LanGameOptionsMenu.cpp`, `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/LanLobbyMenu.cpp`, `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/LanLobbyMenu_init.cpp`, `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/NetworkDirectConnect.cpp`, `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/NetworkDirectConnectSystem.cpp`, `game/GameEngine/Source/GameNetwork/LANAPICallbacks.cpp`, `game/GameEngine/Source/GameNetwork/LANAPIOnGameCreate.cpp`, `game/GameEngine/Source/GameNetwork/LANAPIOnGameJoin.cpp`, `game/GameEngine/Source/GameNetwork/LANAPI_OnPlayerLeave.cpp`, `game/GameEngine/Source/GameNetwork/lanapi.cpp`) |
| `?g_bfmeFlag1006@@3DA` | 1 (`game/GameEngine/Source/Common/BfmeConv1006.cpp`) |

Counts are scoped to typed declarations and definitions, including headers. Similar words in comments or expressions do not count.

## Correction and refutation

The defining translation unit is `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/LanLobbyMenu.cpp`. The sanctioned `tools/add_data_match.py` measurement records its compiled symbol size and verifies its initializer against retail before adding a data row. All existing pins and competing DIR32 rows remain additive evidence; no pin is deleted or rewritten.
A different reference Bool definition, or retail stores representing values outside the menu transition flag contract, would refute LANbuttonPushed. The reference owner and the witnessed callback/menu readers must agree.

## Raw local evidence

`build/rlink/scalars-1791167601/retail-012F3D4A.log` contains byte values, section, overlap checks, pins, and disassembly at every direct occurrence of this VA. `build/rlink/scalars-1791167601/declarations-012F3D4A.log` contains the unedited game search output. `build/rlink/scalars-1791167601/context-012F3D4A.log` records EA string bytes and their instruction addresses. Full bodies are in `build/rlink/scalars-1791167601/body-*.log` and `build/rlink/scalars-1791167601/ledger-body-*.log`; the exact ledger identities and extents are in `build/rlink/scalars-1791167601/supplement.log`. `build/rlink/scalars-1791167601/ilt-chains.log` retains each measured five-byte E9 chain. Reference searches are `build/rlink/scalars-1791167601/reference-search.log` and `build/rlink/scalars-1791167601/reference-types-exact.log`. Gate results and LINKED measurements are indexed in `build/worker-final.md`.
