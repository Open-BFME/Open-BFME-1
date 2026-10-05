# Scalar identity at VA 0x012ED611

Corrected: `?TheBfmeOverrideCopyInProgress@@3_NA` owns the 1-byte `bool` scalar at VA 0x012ED611 (RVA 0x00EED611).

Retail section: `.data`. Initial bytes: `00`. Initial value: `false`.

## Retail facts and contract

ThingFactory::newOverride at 0x00539A80 sets the byte to one around the template-copy call and clears it afterward. CommandButton, CommandSet, CrateTemplate, and SpecialPower override writers use the same one/copy/zero contract. The byte setter at 0x004EB270 accepts an arbitrary unsigned char, so its declaration must be byte-gated independently.

This is free scalar storage with no receiver. The read, write, and output-address sites below describe its argument contract independently of a decompiler. Each instruction comes from retail bytes. Body addresses use the repository ledger extent when available and Ghidra boundary evidence otherwise.

| Instruction VA | Body VA | Access | Retail instruction |
|---|---|---|---|
| 0x004EB274 | 0x004EB270 | write | `mov byte ptr [0x12ed611], al` |
| 0x004EBF37 | 0x004EBE90 | write | `mov byte ptr [0x12ed611], bl` |
| 0x004EBF42 | 0x004EBE90 | write | `mov byte ptr [0x12ed611], 0` |
| 0x004EBFAC | 0x004EBE90 | write | `mov byte ptr [0x12ed611], bl` |
| 0x004EBFB7 | 0x004EBE90 | write | `mov byte ptr [0x12ed611], 0` |
| 0x004EC079 | 0x004EBE90 | write | `mov byte ptr [0x12ed611], bl` |
| 0x004EC084 | 0x004EBE90 | write | `mov byte ptr [0x12ed611], 0` |
| 0x00539AD8 | 0x00539A80 | write | `mov byte ptr [0x12ed611], 1` |
| 0x00539AE6 | 0x00539A80 | write | `mov byte ptr [0x12ed611], 0` |
| 0x00539C29 | 0x00539B40 | write | `mov byte ptr [0x12ed611], 1` |
| 0x00539C37 | 0x00539B40 | write | `mov byte ptr [0x12ed611], 0` |
| 0x00548651 | 0x00548600 | write | `mov byte ptr [0x12ed611], 1` |
| 0x00548661 | 0x00548600 | write | `mov byte ptr [0x12ed611], 0` |
| 0x0077A290 | 0x0077A230 | write | `mov byte ptr [0x12ed611], 1` |
| 0x0077A2A0 | 0x0077A230 | write | `mov byte ptr [0x12ed611], 0` |
| 0x0077A3C5 | 0x0077A320 | write | `mov byte ptr [0x12ed611], 1` |
| 0x0077A3D1 | 0x0077A320 | write | `mov byte ptr [0x12ed611], 0` |
| 0x0089DEA4 | 0x0089DE40 | write | `mov byte ptr [0x12ed611], 1` |
| 0x0089DEB4 | 0x0089DE40 | write | `mov byte ptr [0x12ed611], 0` |
| 0x008A3773 | 0x008A3710 | write | `mov byte ptr [0x12ed611], 1` |
| 0x008A3783 | 0x008A3710 | write | `mov byte ptr [0x12ed611], 0` |

The narrow scan of `data_rows.csv` finds no range overlapping this extent. The DIR32 scan finds no named start strictly inside it. All competing names begin at the same address; the raw probe records both tests. These candidate scalar ranges have no pointer initializer.

## Competing declarations

| DIR32 spelling | Game files declaring this spelling |
|---|---|
| `?TheBfmeOverrideCopyInProgress@@3_NA` | 7 (`game/GameEngine/Source/Common/RTS/SpecialPowerStoreParseSpecialPowerDefinition.cpp`, `game/GameEngine/Source/Common/Thing/ThingFactory_newOverride.cpp`, `game/GameEngine/Source/Common/Thing/ThingTemplate.cpp`, `game/GameEngine/Source/GameClient/GUI/ControlBar/CommandButtonOverride.cpp`, `game/GameEngine/Source/GameClient/GUI/ControlBar/CommandSetLifetime.cpp`, `game/GameEngine/Source/GameLogic/System/CrateSystem.cpp`, `game/GameEngine/Source/GameLogic/System/CrateSystem_newCrateTemplateOverride.cpp`) |
| `?g_Va012ED611@@3EA` | 1 (`game/GameEngine/Source/Common/SmallLeafBodies.cpp`) |

Counts are scoped to typed declarations and definitions, including headers. Similar words in comments or expressions do not count.

## Correction and refutation

The defining translation unit is `game/GameEngine/Source/Common/Thing/ThingFactory_newOverride.cpp`. The sanctioned `tools/add_data_match.py` measurement records its compiled symbol size and verifies its initializer against retail before adding a data row. All existing pins and competing DIR32 rows remain additive evidence; no pin is deleted or rewritten.
The arbitrary byte setter in SmallLeafBodies.cpp retains its original unsigned-char declaration. Retyping to bool changed its instructions; see the failed trial and passing recheck logs. It still refers to the old spelling and remains a linking blocker.
The five-byte thunk at VA 0x004136AB must route to the matched ThingTemplate copy assignment at VA 0x00539070. A different route, or stores that do not bracket that assignment, would refute the copy-in-progress role. The arbitrary-byte setter remains under its original declaration because bool normalization changed its bytes.

## Raw local evidence

`build/rlink/scalars-1791167601/retail-012ED611.log` contains byte values, section, overlap checks, pins, and disassembly at every direct occurrence of this VA. `build/rlink/scalars-1791167601/declarations-012ED611.log` contains the unedited game search output. `build/rlink/scalars-1791167601/context-012ED611.log` records EA string bytes and their instruction addresses. Full bodies are in `build/rlink/scalars-1791167601/body-*.log` and `build/rlink/scalars-1791167601/ledger-body-*.log`; the exact ledger identities and extents are in `build/rlink/scalars-1791167601/supplement.log`. `build/rlink/scalars-1791167601/ilt-chains.log` retains each measured five-byte E9 chain. Reference searches are `build/rlink/scalars-1791167601/reference-search.log` and `build/rlink/scalars-1791167601/reference-types-exact.log`. Gate results and LINKED measurements are indexed in `build/worker-final.md`.
`build/rlink/scalars-1791167601/override-copy-callee.log` records the E9 route to the matched ThingTemplate copy-assignment body and its initial field accesses. `build/rlink/scalars-1791167601/build-009.log` records the refusing byte-setter retyping; `build/rlink/scalars-1791167601/build-rechecks.log` verifies its restored declaration.
