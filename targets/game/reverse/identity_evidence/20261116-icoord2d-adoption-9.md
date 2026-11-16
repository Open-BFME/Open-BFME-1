# ICoord2D source adoptions: tasks 158-177 of 200

Immediate baseline `e31f3ec3d3ec69ff03b47fbbefb6ece81026a362`.
Contract, reference mapping and proof method: [common evidence](20261116-icoord2d-contract.md).
One adopted existing source unit is one task; no new function or authored-byte claim.
The unchanged WWMath/icoord.cpp provider independently passes15/15 retail rows;
its source and icoord.h inputs remain unchanged from the round baseline. Later
combined scopes include it alongside the unchanged string providers. No provider
inheritance or method body is changed or newly asserted by the data header.
Normal combined gate:230/230 functions across26 files;
497 DIR32 references and body guard OK.
Consumers retain40 rows/12070B.
Native state-writer cleanup locator updates:3.

| Task | Source | Retained RVAs |
|---|---|---|
| 158 | `game/GameEngine/Source/GameClient/GUI/FullFadeTransition_draw.cpp` | `0x0059D5D0`, `0x0059D6E0` |
| 159 | `game/GameEngine/Source/GameClient/GUI/ProcessAnimateWindowSlideFromTop_reverseAnimateWindow.cpp` | `0x00497910`, `0x00496260` |
| 160 | `game/GameEngine/Source/GameClient/GUI/ProcessAnimateWindowSlideFromRight_updateAnimateWindow.cpp` | `0x004978B0`, `0x00495850` |
| 161 | `game/GameEngine/Source/GameLogic/AI/PathfindCellInfoRecord.cpp` | `0x003F6CA0`, `0x003F6940` |
| 162 | `game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarScheme_drawBackground.cpp` | `0x004AD600`, `0x004AD4C0` |
| 163 | `game/GameEngine/Source/GameClient/GUI/ProcessAnimateWindowSlideFromBottom_updateAnimateWindow_Thunk.cpp` | `0x00497940`, `0x004965B0` |
| 164 | `game/GameEngine/Source/GameClient/System/Anim2DDrawing.cpp` | `0x005BABA0`, `0x005BA9E0` |
| 165 | `game/GameEngine/Source/GameLogic/AI/BfmeAttackQueryCandidateE2B0.cpp` | `0x003EE2B0`, `0x003D6DC0` |
| 166 | `game/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadarViewBoxRva006C0FA0.cpp` | `0x00C49C80`, `0x006C0FA0` |
| 167 | `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewDrawablePostDraw.cpp` | `0x0073AD70`, `0x0073AED0` |
| 168 | `game/GameEngine/Source/GameClient/GUI/ProcessAnimateWindowReverseAnimate.cpp` | `0x00495970`, `0x00497270` |
| 169 | `game/GameEngine/Source/GameLogic/AI/AISkirmishPlayer_checkBridges.cpp` | `0x00168A10`, `0x003D96A0` |
| 170 | `game/GameEngine/Source/GameClient/MapPreviewImage.cpp` | `0x004508D0`, `0x004516E0` |
| 171 | `game/GameEngine/Source/GameLogic/Map/FootprintIterator001A1460.cpp` | `0x001A1460`, `0x001A12D0` |
| 172 | `game/GameEngine/Source/GameLogic/AI/PathfinderClearCellForDiameter.cpp` | `0x003DC810`, `0x003DC780` |
| 173 | `game/GameEngine/Source/GameLogic/AI/PathfinderDestinationWork.cpp` | `0x003F2DB0`, `0x003F2EC0` |
| 174 | `game/GameEngine/Source/GameLogic/AI/PathfindGetRadiusAndCenterE30.cpp` | `0x003DEE30`, `0x003E2140` |
| 175 | `game/GameEngine/Source/GameLogic/AI/PathfinderNewMap.cpp` | `0x003D80F0`, `0x00C1FB50` |
| 176 | `game/GameEngine/Source/GameClient/Input/Mouse_processMouseEvent.cpp` | `0x005A4230`, `0x005A46B0` |
| 177 | `game/GameEngine/Source/GameNetwork/NetPacket_FillBufferWithGameCommand.cpp` | `0x00676D00`, `0x00C45620` |

Frozen-census before:10/20 LINKS,5300B.
After:10/20 LINKS,5300B. No loss.
Staged current-provider preview: 20/20 UNKNOWN, 0/20 LINKS, 0/20 blocked. Unknown results authorize no LINKED claim.
No complete-image link, runtime or memory/crash-fix claim.
Unselected or failed private trials are not applied or counted. Original/control
and normal objects, CodeView, complete section/relocation graphs, reservations
and prior attempts are retained in this round diagnostics.
