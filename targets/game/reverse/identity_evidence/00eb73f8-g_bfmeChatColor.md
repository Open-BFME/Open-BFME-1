# Scalar identity at VA 0x012B73F8

Corrected: `?g_bfmeChatColor@@3HA` owns the 4-byte `int` scalar at VA 0x012B73F8 (RVA 0x00EB73F8).

Retail section: `.data`. Initial bytes: `00 00 ff ff`. Initial value: `0xFFFF0000`.

## Retail facts and contract

The only two retail references are DisconnectMenu removePlayer (0x0090EB00) and showChat (0x0090EF20), passing the dword to the chat listbox. The initial red ARGB value matches ZH DisconnectMenu.cpp static const chatNormalColor, not the cyan LANAPICallbacks constant with the same source word. The existing g_bfmeChatColor pin distinguishes this mutable BFME storage from the unrelated LAN constant.

This is free scalar storage with no receiver. The read, write, and output-address sites below describe its argument contract independently of a decompiler. Each instruction comes from retail bytes. Body addresses use the repository ledger extent when available and Ghidra boundary evidence otherwise.

| Instruction VA | Body VA | Access | Retail instruction |
|---|---|---|---|
| 0x0090EBE6 | 0x0090EB00 | read | `mov edx, dword ptr [0x12b73f8]` |
| 0x0090EF39 | 0x0090EF20 | read | `mov eax, dword ptr [0x12b73f8]` |

The narrow scan of `data_rows.csv` finds no range overlapping this extent. The DIR32 scan finds no named start strictly inside it. All competing names begin at the same address; the raw probe records both tests. These candidate scalar ranges have no pointer initializer.

## Competing declarations

| DIR32 spelling | Game files declaring this spelling |
|---|---|
| `?chatNormalColor@@3HA` | 1 (`game/GameEngine/Source/GameClient/GUI/DisconnectMenu/DisconnectMenu.cpp`) |
| `?g_bfmeChatColor@@3HA` | 1 (`game/GameEngine/Source/GameClient/GUI/AptScreenFactories.cpp`) |

Counts are scoped to typed declarations and definitions, including headers. Similar words in comments or expressions do not count.

## Correction and refutation

The LAN const `chatNormalColor` is a different COFF spelling and is excluded from the mutable disconnect-color count.
The defining translation unit is `game/GameEngine/Source/GameClient/GUI/DisconnectMenu/DisconnectMenu.cpp`. The sanctioned `tools/add_data_match.py` measurement records its compiled symbol size and verifies its initializer against retail before adding a data row. All existing pins and competing DIR32 rows remain additive evidence; no pin is deleted or rewritten.
The claim would be refuted if either witnessed use supplies the value in a non-color argument position, or if the disconnect constant differs from the reference red ARGB value. This does not rename the independent cyan LAN constant.

## Raw local evidence

`build/rlink/scalars-1791167601/retail-012B73F8.log` contains byte values, section, overlap checks, pins, and disassembly at every direct occurrence of this VA. `build/rlink/scalars-1791167601/declarations-012B73F8.log` contains the unedited game search output. `build/rlink/scalars-1791167601/context-012B73F8.log` records EA string bytes and their instruction addresses. Full bodies are in `build/rlink/scalars-1791167601/body-*.log` and `build/rlink/scalars-1791167601/ledger-body-*.log`; the exact ledger identities and extents are in `build/rlink/scalars-1791167601/supplement.log`. `build/rlink/scalars-1791167601/ilt-chains.log` retains each measured five-byte E9 chain. Reference searches are `build/rlink/scalars-1791167601/reference-search.log` and `build/rlink/scalars-1791167601/reference-types-exact.log`. Gate results and LINKED measurements are indexed in `build/worker-final.md`.
