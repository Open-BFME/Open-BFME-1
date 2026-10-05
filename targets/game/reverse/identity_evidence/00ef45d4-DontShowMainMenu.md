# Scalar identity at VA 0x012F45D4

Corrected: `?DontShowMainMenu@@3_NA` owns the 1-byte `bool` scalar at VA 0x012F45D4 (RVA 0x00EF45D4).

Retail section: `.data`. Initial bytes: `00`. Initial value: `false`.

## Retail facts and contract

ZH WOLLobbyMenu.cpp:101 defines Bool DontShowMainMenu=false, and PopupSaveLoad tests it with justEntered. Retail SaveLoadMenuUpdate at 0x008DF9C0 uses that same guard; WOL init and ScoreScreen init set it, and WOL shutdown and ScoreScreen shutdown clear it. ZH g_playMusic controls ScoreScreen update music and is a separate datum; the retail uses here establish menu suppression.

This is free scalar storage with no receiver. The read, write, and output-address sites below describe its argument contract independently of a decompiler. Each instruction comes from retail bytes. Body addresses use the repository ledger extent when available and Ghidra boundary evidence otherwise.

| Instruction VA | Body VA | Access | Retail instruction |
|---|---|---|---|
| 0x008DF9CE | 0x008DF9C0 | read | `mov al, byte ptr [0x12f45d4]` |
| 0x008E2705 | 0x008E2700 | write | `mov byte ptr [0x12f45d4], 0` |
| 0x008E8DE6 | 0x008E8DC0 | write | `mov byte ptr [0x12f45d4], 1` |
| 0x008FB039 | 0x008FAF70 | write | `mov byte ptr [0x12f45d4], bl` |
| 0x008FC254 | 0x008FBBE0 | write | `mov byte ptr [0x12f45d4], 1` |

The narrow scan of `data_rows.csv` finds no range overlapping this extent. The DIR32 scan finds no named start strictly inside it. All competing names begin at the same address; the raw probe records both tests. These candidate scalar ranges have no pointer initializer.

## Competing declarations

| DIR32 spelling | Game files declaring this spelling |
|---|---|
| `?DontShowMainMenu@@3_NA` | 6 (`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/MainMenu.cpp`, `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupSaveLoad.cpp`, `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ScoreScreen.cpp`, `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLobbyMenu.cpp`, `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLobbyMenuShutdown_Thunk.cpp`, `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLobbyMenuUpdate.cpp`) |
| `?g_playMusic@@3_NA` | 2 (`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ScoreScreen.cpp`, `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ScoreScreenInit.cpp`) |

Counts are scoped to typed declarations and definitions, including headers. Similar words in comments or expressions do not count.

## Correction and refutation

The defining translation unit is `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLobbyMenu.cpp`. The sanctioned `tools/add_data_match.py` measurement records its compiled symbol size and verifies its initializer against retail before adding a data row. All existing pins and competing DIR32 rows remain additive evidence; no pin is deleted or rewritten.
The SaveLoadMenuUpdate read must guard justEntered menu suppression, and the WOL/score transitions must write that same byte. A retail music-playback reader at this address would require reopening the distinction from g_playMusic.

## Raw local evidence

`build/rlink/scalars-1791167601/retail-012F45D4.log` contains byte values, section, overlap checks, pins, and disassembly at every direct occurrence of this VA. `build/rlink/scalars-1791167601/declarations-012F45D4.log` contains the unedited game search output. `build/rlink/scalars-1791167601/context-012F45D4.log` records EA string bytes and their instruction addresses. Full bodies are in `build/rlink/scalars-1791167601/body-*.log` and `build/rlink/scalars-1791167601/ledger-body-*.log`; the exact ledger identities and extents are in `build/rlink/scalars-1791167601/supplement.log`. `build/rlink/scalars-1791167601/ilt-chains.log` retains each measured five-byte E9 chain. Reference searches are `build/rlink/scalars-1791167601/reference-search.log` and `build/rlink/scalars-1791167601/reference-types-exact.log`. Gate results and LINKED measurements are indexed in `build/worker-final.md`.
