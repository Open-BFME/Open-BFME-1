# ICoord2D source adoptions: tasks 178-194 of 200

Immediate baseline `cb79bfbddef44224776d37ababdf81e0c32b5183`.
Contract, reference mapping and proof method: [common evidence](20261116-icoord2d-contract.md).
One adopted existing source unit is one task; no new function or authored-byte claim.
The unchanged WWMath/icoord.cpp provider independently passes15/15 retail rows;
its source and icoord.h inputs remain unchanged from the round baseline. Later
combined scopes include it alongside the unchanged string providers. No provider
inheritance or method body is changed or newly asserted by the data header.
Normal combined gate:234/234 functions across22 files;
502 DIR32 references and body guard OK.
Consumers retain45 rows/19348B.
Native state-writer cleanup locator updates:2.

| Task | Source | Retained RVAs |
|---|---|---|
| 178 | `game/GameEngine/Source/GameLogic/Object/Update/AIUpdateBlockedBy.cpp` | `0x00150510`, `0x00274630` |
| 179 | `game/GameEngine/Source/GameLogic/Pathfinder/PathfindLayerAllocateCells.cpp` | `0x00C1FF20`, `0x003FBED0` |
| 180 | `game/GameEngine/Source/GameLogic/AI/PathfinderRva003E49F0.cpp` | `0x003E4680`, `0x003E49F0` |
| 181 | `game/GameEngine/Source/GameLogic/AI/PathfinderStepD4F90.cpp` | `0x003D4F90`, `0x003E11E0` |
| 182 | `game/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadar_buildTerrainTexture.cpp` | `0x006C39D0`, `0x00C49F90` |
| 183 | `game/GameEngine/Source/GameClient/DrawableCaptionAndAmbient.cpp` | `0x00420150`, `0x0041AD20` |
| 184 | `game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/Gadget/W3DPushButtonDraw_Thunk.cpp` | `0x00794D30`, `0x00793EE0` |
| 185 | `game/GameEngine/Source/GameLogic/Map/TerrainLogicCountTrees.cpp` | `0x001A6370`, `0x001A19B0`, `0x001A19A0` |
| 186 | `game/GameEngine/Source/Common/Rva00900E40Constructor.cpp` | `0x00900E40`, `0x003F7A00`, `0x006BE4F0` |
| 187 | `game/GameEngine/Source/GameLogic/Map/PolygonTrigger_pointInTrigger.cpp` | `0x0018FA20`, `0x0018F8A0`, `0x0018F400` |
| 188 | `game/GameEngine/Source/GameClient/GUI/ProcessAnimateWindowSlideFromBottomTimed_initReverseAnimateWindow_Thunk.cpp` | `0x00496830`, `0x00496860`, `0x00105750` |
| 189 | `game/GameEngine/Source/GameLogic/AI/PathfinderPickBridge.cpp` | `0x003D8C40`, `0x003FBB20`, `0x003FBAB0` |
| 190 | `game/GameEngine/Source/GameClient/GUI/ProcessAnimateWindowInitAnimate.cpp` | `0x00496920`, `0x004974F0`, `0x00496000` |
| 191 | `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisualBfme.cpp` | `0x007304E0`, `0x00730B60`, `0x00730BD0` |
| 192 | `game/GameEngine/Source/GameLogic/AI/PathfinderFindGroundPath.cpp` | `0x003F2160`, `0x003E2620`, `0x003D5DE0` |
| 193 | `game/GameEngine/Source/GameClient/GUI/Gadget/GadgetComboBoxInput.cpp` | `0x004B3E30`, `0x004B4010`, `0x004B42F0` |
| 194 | `game/GameEngine/Source/GameLogic/AI/PathfinderCellPredicates.cpp` | `0x003D95A0`, `0x003D94A0`, `0x003D9430`, `0x003D9520` |

Frozen-census before:8/17 LINKS,6774B.
After:8/17 LINKS,6774B. No loss.
Staged current-provider preview: 17/17 UNKNOWN, 0/17 LINKS, 0/17 blocked. Unknown results authorize no LINKED claim.
No complete-image link, runtime or memory/crash-fix claim.
Unselected or failed private trials are not applied or counted. Original/control
and normal objects, CodeView, complete section/relocation graphs, reservations
and prior attempts are retained in this round diagnostics.
