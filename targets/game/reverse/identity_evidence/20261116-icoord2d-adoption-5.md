# ICoord2D source adoptions: tasks 80-98 of 200

Immediate baseline `93073c1d21a7b8de5521f887b98192427404ba41`.
Contract, reference mapping and proof method: [common evidence](20261116-icoord2d-contract.md).
One adopted existing source unit is one task; no new function or authored-byte claim.
The unchanged WWMath/icoord.cpp provider independently passes15/15 retail rows;
its source and icoord.h inputs remain unchanged from the round baseline. Later
combined scopes include it alongside the unchanged string providers. No provider
inheritance or method body is changed or newly asserted by the data header.
Normal combined gate:208/208 functions across24 files;
428 DIR32 references and body guard OK.
Consumers retain19 rows/8775B.
Native state-writer cleanup locator updates:0.

| Task | Source | Retained RVAs |
|---|---|---|
| 80 | `game/GameEngine/Source/GameLogic/AI/AIAttackMeleeEngageState_xfer.cpp` | `0x00177F40` |
| 81 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/MapSelectorTooltip.cpp` | `0x004F1760` |
| 82 | `game/GameEngine/Source/GameLogic/AI/PathfinderIterateCellsAlongLineRva003D79C0.cpp` | `0x003D79C0` |
| 83 | `game/GameEngine/Source/GameLogic/AI/PathfinderIterateCircular2.cpp` | `0x003F18E0` |
| 84 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PositionStartSpotControls.cpp` | `0x0044F960` |
| 85 | `game/GameEngine/Source/GameLogic/Pathfinder/PathfindE1fe0.cpp` | `0x003E1FE0` |
| 86 | `game/GameEngine/Source/GameLogic/AI/pathfind_tightenPath.cpp` | `0x003F5FD0` |
| 87 | `game/GameEngine/Source/GameClient/Drawable_drawBombed.cpp` | `0x00418490` |
| 88 | `game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/W3DGameWindowDrawText.cpp` | `0x0078D6D0` |
| 89 | `game/GameEngine/Source/GameClient/Drawable_drawEnthusiastic.cpp` | `0x0041A780` |
| 90 | `game/GameEngine/Source/GameLogic/AI/PathfinderObjectCell.cpp` | `0x003DEFB0` |
| 91 | `game/GameEngineDevice/Source/MilesAudioDevice/Rva006956D0ScreenCenter.cpp` | `0x006956D0` |
| 92 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/SkirmishPositionAdditionalImages.cpp` | `0x00452AD0` |
| 93 | `game/GameEngine/Source/GameLogic/AI/PathfinderClassifyFence.cpp` | `0x003F7D10` |
| 94 | `game/GameEngineDevice/Source/Win32Device/GameClient/Win32Mouse_initCursorResources.cpp` | `0x006BC360` |
| 95 | `game/GameEngine/Source/GameLogic/AI/PathfinderIterateCellsAlongLineRva003E3650.cpp` | `0x003E3650` |
| 96 | `game/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMapRva0074B480.cpp` | `0x0074B480` |
| 97 | `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayDrawOpenRect.cpp` | `0x006E9D40` |
| 98 | `game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/GUICallbacks/W3DCommandBarGridDraw.cpp` | `0x00799FA0` |

Frozen-census before:18/19 LINKS,8560B.
After:18/19 LINKS,8560B. No loss.
Staged current-provider preview: 19/19 UNKNOWN, 0/19 LINKS, 0/19 blocked. Unknown results authorize no LINKED claim.
No complete-image link, runtime or memory/crash-fix claim.
Unselected or failed private trials are not applied or counted. Original/control
and normal objects, CodeView, complete section/relocation graphs, reservations
and prior attempts are retained in this round diagnostics.

The original before-preview includes refused candidates; statistics above
count only the finally selected sources. Ordinary-source refusals are restored
and uncounted. See attempt_support/20261116-icoord2d-native-context.md for
the batch5 compiler-context boundary.
