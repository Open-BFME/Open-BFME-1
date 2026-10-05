# Scalar identity at VA 0x012F0478

Corrected: `?g_bfmeDockingTraceActive@@3_NA` owns the 1-byte `bool` scalar at VA 0x012F0478 (RVA 0x00EF0478).

Retail section: `.data`. Initial bytes: `00`. Initial value: `false`.

## Retail facts and contract

Worker and Dozer newTask set the byte around their docking-position search and clear it on each exit. TerrainLogic, AIUpdateInterface, Worker position search, and Object contact-point helpers test it together with TheCRCParameterCheck before their EA diagnostic strings. The existing docking-trace pin and the nested readers establish the shared trace scope.

This is free scalar storage with no receiver. The read, write, and output-address sites below describe its argument contract independently of a decompiler. Each instruction comes from retail bytes. Body addresses use the repository ledger extent when available and Ghidra boundary evidence otherwise.

| Instruction VA | Body VA | Access | Retail instruction |
|---|---|---|---|
| 0x005AF62C | 0x005AF610 | read | `mov al, byte ptr [0x12f0478]` |
| 0x005AF6DD | 0x005AF610 | read | `mov al, byte ptr [0x12f0478]` |
| 0x005AF75B | 0x005AF610 | read | `mov al, byte ptr [0x12f0478]` |
| 0x005AF7EA | 0x005AF610 | read | `mov al, byte ptr [0x12f0478]` |
| 0x005AF8C0 | 0x005AF610 | read | `mov al, byte ptr [0x12f0478]` |
| 0x005AF947 | 0x005AF610 | read | `mov al, byte ptr [0x12f0478]` |
| 0x005AF980 | 0x005AF610 | read | `mov al, byte ptr [0x12f0478]` |
| 0x005AFA07 | 0x005AF610 | read | `mov al, byte ptr [0x12f0478]` |
| 0x005C3169 | 0x005C3160 | read | `mov al, byte ptr [0x12f0478]` |
| 0x005C32BA | 0x005C3160 | read | `mov al, byte ptr [0x12f0478]` |
| 0x005C337C | 0x005C3160 | read | `mov al, byte ptr [0x12f0478]` |
| 0x00672803 | 0x00672800 | read | `mov al, byte ptr [0x12f0478]` |
| 0x00672900 | 0x00672800 | read | `mov al, byte ptr [0x12f0478]` |
| 0x00672953 | 0x00672800 | read | `mov al, byte ptr [0x12f0478]` |
| 0x0067299B | 0x00672800 | read | `mov al, byte ptr [0x12f0478]` |
| 0x006B8AE9 | 0x006B8A00 | write | `mov byte ptr [0x12f0478], 1` |
| 0x006B8B74 | 0x006B8A00 | write | `mov byte ptr [0x12f0478], 0` |
| 0x006B8C30 | 0x006B8A00 | write | `mov byte ptr [0x12f0478], 0` |
| 0x006C8A29 | 0x006C8A20 | read | `mov al, byte ptr [0x12f0478]` |
| 0x006C8B00 | 0x006C8A20 | read | `mov al, byte ptr [0x12f0478]` |
| 0x006C8C1D | 0x006C8A20 | read | `mov al, byte ptr [0x12f0478]` |
| 0x006C8C98 | 0x006C8A20 | read | `mov al, byte ptr [0x12f0478]` |
| 0x006C8D3F | 0x006C8A20 | read | `mov al, byte ptr [0x12f0478]` |
| 0x006C8D6D | 0x006C8A20 | read | `mov al, byte ptr [0x12f0478]` |
| 0x006C8DEB | 0x006C8A20 | read | `mov al, byte ptr [0x12f0478]` |
| 0x006C8E59 | 0x006C8A20 | read | `mov cl, byte ptr [0x12f0478]` |
| 0x006C9C43 | 0x006C9C40 | read | `mov al, byte ptr [0x12f0478]` |
| 0x006C9D10 | 0x006C9C40 | read | `mov al, byte ptr [0x12f0478]` |
| 0x006C9D43 | 0x006C9C40 | read | `mov al, byte ptr [0x12f0478]` |
| 0x006CA23A | 0x006CA130 | write | `mov byte ptr [0x12f0478], 1` |
| 0x006CA2C2 | 0x006CA130 | write | `mov byte ptr [0x12f0478], 0` |
| 0x006CA383 | 0x006CA130 | write | `mov byte ptr [0x12f0478], 0` |
| 0x00C7F590 | 0x00C7F590 | read | `mov al, byte ptr [0x12f0478]` |

The narrow scan of `data_rows.csv` finds no range overlapping this extent. The DIR32 scan finds no named start strictly inside it. All competing names begin at the same address; the raw probe records both tests. These candidate scalar ranges have no pointer initializer.

## Competing declarations

| DIR32 spelling | Game files declaring this spelling |
|---|---|
| `?g_bfmeDockingTraceActive@@3_NA` | 5 (`game/GameEngine/Source/GameLogic/Map/FindPositionAround001AF610.cpp`, `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdateNewTaskBfme.cpp`, `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdateFindGoodBuildOrRepairPosition.cpp`, `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdateFindGoodBuildOrRepairPositionAndTarget.cpp`, `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdateNewTaskBfme.cpp`) |
| `?g_contactPointDebug@@3EA` | 1 (`game/GameEngine/Source/GameLogic/Object/Object_getWorldspaceBestContactPoint.cpp`) |

Counts are scoped to typed declarations and definitions, including headers. Similar words in comments or expressions do not count.

## Correction and refutation

The defining translation unit is `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdateNewTaskBfme.cpp`. The sanctioned `tools/add_data_match.py` measurement records its compiled symbol size and verifies its initializer against retail before adding a data row. All existing pins and competing DIR32 rows remain additive evidence; no pin is deleted or rewritten.
The active stores must bracket the docking-position search and the nested readers must guard the recorded contact-point and position diagnostics. If those operations concern independent scopes or another address, the shared docking-trace role is wrong.

## Raw local evidence

`build/rlink/scalars-1791167601/retail-012F0478.log` contains byte values, section, overlap checks, pins, and disassembly at every direct occurrence of this VA. `build/rlink/scalars-1791167601/declarations-012F0478.log` contains the unedited game search output. `build/rlink/scalars-1791167601/context-012F0478.log` records EA string bytes and their instruction addresses. Full bodies are in `build/rlink/scalars-1791167601/body-*.log` and `build/rlink/scalars-1791167601/ledger-body-*.log`; the exact ledger identities and extents are in `build/rlink/scalars-1791167601/supplement.log`. `build/rlink/scalars-1791167601/ilt-chains.log` retains each measured five-byte E9 chain. Reference searches are `build/rlink/scalars-1791167601/reference-search.log` and `build/rlink/scalars-1791167601/reference-types-exact.log`. Gate results and LINKED measurements are indexed in `build/worker-final.md`.
