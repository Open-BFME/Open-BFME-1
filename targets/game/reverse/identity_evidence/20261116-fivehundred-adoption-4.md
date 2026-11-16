# Canonical header adoptions: tasks 12-31 of 500

Immediate baseline: `2a7328eb5728f56cea0145d5d6959ed489a514cb`.
One independently verified existing source unit is one task. No new function
identity, authored coverage, full-image link or runtime/crash-fix claim.
Shared headers, pins, aliases, verifiers and baselines are unchanged. Consumers add only the existing WWLib include root; optimization and defines are unchanged.

## ABI and object evidence

The existing WWMath/vector3.h defines a12B class, no bases or virtual state,
with float X/Y/Z at0/4/8. Native class_contract sampled60 views:59 compiled;
retail member accesses and the compiled ZH vector3.h support those widths,
offsets and names. Each old/new source independently satisfies that exact
CodeView layout. No new field name, return ABI or original-source claim.

Controls use one private physical compiler path and the original source context.
Separate ordinary native objects must retain every runtime section and relocation
role, including local offsets, EH actions and resolved SafeSEH targets. Additional
or changed callable COMDATs require existing matched ledger ownership and full
native RetailTruth bytes/targets; correct providers may not disappear. Refused
trials remain unapplied and uncounted. Cleanup locators use only the native
retail-state writer. All retained rows were reserved before experiments.

Combined ordinary gate: 238/238 functions
in 27 files; 387 DIR32 references; body guard OK.
Consumers preserve 20 rows / 3645B.
Native cleanup locator repairs: 0.

| Task | Source | Retained RVAs |
|---|---|---|
| 12 | `game/GameEngine/Source/Common/Rva00412FC0SetVec.cpp` | `0x00412FC0` |
| 13 | `game/GameEngine/Source/Common/BfmeConv2098.cpp` | `0x006FCF60` |
| 14 | `game/GameEngine/Source/Common/BfmeConv1963.cpp` | `0x0073DFD0` |
| 15 | `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeInit.cpp` | `0x006D8920` |
| 16 | `game/GameEngine/Source/Common/BfmeThingVGXCopyCtor.cpp` | `0x00975090` |
| 17 | `game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowVisibleBounds.cpp` | `0x007C0EA0` |
| 18 | `game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowVisibleBoundsPredicate.cpp` | `0x007C0F60` |
| 19 | `game/GameEngineDevice/Source/W3DDevice/GameClient/BFMECameraCullBox_Cull_Box.cpp` | `0x009330C0` |
| 20 | `game/GameEngineDevice/Source/W3DDevice/GameClient/ScreenFilterRva007DCA80PreRender.cpp` | `0x007DB890` |
| 21 | `game/Libraries/Source/WWVegas/WW3D2/PointGroupClassPrepareShader.cpp` | `0x00912E60` |
| 22 | `game/Libraries/Source/WWVegas/WW3D2/StreakRendererCopyCtor.cpp` | `0x0095FE50` |
| 23 | `game/GameEngine/Source/GameClient/DrawableBFMERecordTransform.cpp` | `0x001C0BE0` |
| 24 | `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewCalcDeltaScrollThunk.cpp` | `0x0073B6B0` |
| 25 | `game/GameEngineDevice/Source/W3DDevice/GameClient/Rva006FD180MouseWorldToScreen.cpp` | `0x006FD180` |
| 26 | `game/GameEngine/Source/Common/BfmeViewETHApply.cpp` | `0x0073B8E0` |
| 27 | `game/Libraries/Source/WWVegas/WW3D2/Rva0090F950PackColor.cpp` | `0x0090F950` |
| 28 | `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBuffer_addBridge_Thunk.cpp` | `0x006DA0B0` |
| 29 | `game/Libraries/Source/WWVegas/WW3D2/RenderList_ApplyClearFlush.cpp` | `0x0079DE40` |
| 30 | `game/Libraries/Source/WWVegas/WW3D2/SegLineRendererClassCopyCtorThunk.cpp` | `0x00960990` |
| 31 | `game/Libraries/Source/WWVegas/WWMath/VehicleCurveArc_Add_Thunk.cpp` | `0x009347C0` |

Frozen-index before: 17/20 LINKS, 3064B.
After: 17/20 LINKS, 3064B; no loss.
Current-provider preview: 20/20 UNKNOWN; unknown proves no linked-byte gain.

BFME2 reference7209b9e7397e3ed356627a8110e4b7aab234f6e8 remains read-only.
Its Code/ maps to game/; no donor RVAs, compiler settings or private buffer
representations are copied. BFME1 native providers and settled headers determine
the target ABI. The earlier DXERR route prerequisite is unchanged and not retried.
New full census43852286500 was requested against fe40b725e8, the preceding
200-task completion. Its result is recorded separately when available.

## Include resolution

The initial trial failed because WWMath/vector3.h could not find always.h.
The corrected consumer //cl flags add /Igame/Libraries/Source/WWVegas/WWLib.
Private controls use the old flags; private candidates and ordinary native
builds use the new include root. Include tracing must resolve vector3.h and
WWLib/always.h to these BFME1 files before publication. No donor flag set is copied.

## Incoming-change reconciliation

Before publication,17658e39a3 added dllimport/forceinline suppression of the
helper-only Ortho particle constructor and advanced the BFME2 reference to
aa505f34c898e6fb7c9a1f1632e75ce232f4829a. This batch was rebased on it.
The reviewed string_base.h, Vector3.h, Coord3D.h and BFME2 ascii shim blobs
are unchanged between7209b9e739 and aa505f34c8; their earlier source evidence
remains applicable. The new reference checkout is read-only.

The ordinary gate was repeated for the20 consumers, seven native providers
and the incoming Ortho destructor:239/239 functions across28 source files,
387 DIR32 references, body guard OK. The final complete ordinary runtime
graphs, owned rows and source/header hashes were independently re-audited;
all20 remain proven. No incoming change is counted as one of these tasks.

Further incoming commits1a8cb3e09ee..23fbabab715 apply the same constructor-suppression repair to four other particle helpers. They do not overlap these consumers or their headers. After rebasing, the joint ordinary gate passes243/243 functions across32 files; final complete runtime graphs and all20 owned rows still pass.
