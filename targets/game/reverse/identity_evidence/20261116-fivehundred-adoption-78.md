# Canonical header adoptions: tasks 429-448 of 500

Immediate baseline: `069204ce811dc7bb89e251129613c3e60287e814`.
One distinct remaining class/header reconciliation in a source unit is one task. No new function
identity, authored coverage, full-image link or runtime/crash-fix claim.
Shared headers, compiler flags, pins, aliases, verifiers and baselines are unchanged.

## ABI and object evidence

The old Thing definition is a1-byte empty C++ facade used only as a pointer
view in the emitted code. It has no fields, bases, vfptr, virtual members or
static data; that size is not asserted to be the retail Thing object size.
The unchanged existing Thing header asserts its96-byte extent and field
offsets. Original nonvirtual function declarations/bodies retain their own
access visibility through the header's documented THING_TU_MEMBERS extension.
No data, friend declarations, conditional members or virtual slots are injected.
Every other complete native class record must preserve key, size, bases,
every field, vfptr, virtual slots, static data and virtual signatures exactly.
A changed containing or derived class therefore refuses the candidate.
Complete private and ordinary runtime inventories must be identical, including
every definition, byte, flag, relocation, weak contract and SafeSEH role.
No constructor, vtable or size-dependent emitted operation may change.
This completes a partial declaration; it is not a claim that the original
1-byte view was a correct complete object ABI, or that gameplay is validated.

Controls use one private physical compiler path and the original source context.
Separate ordinary native objects must retain every runtime section and relocation
role, including local offsets, EH actions and resolved SafeSEH targets. Additional
or changed callable COMDATs require existing matched ledger ownership and full
native RetailTruth bytes/targets; selected retail providers must remain. Refused
trials remain unapplied and uncounted. Cleanup locators use only the native
retail-state writer. All retained rows were reserved before experiments.

Combined ordinary gate: 276/276 functions
in 28 files; 370 DIR32 references; body guard OK.
Consumers preserve 20 rows / 2416B.
Native cleanup locator repairs: 0.

| Task | Source | Retained RVAs |
|---|---|---|
| 429 | `game/GameEngine/Source/Common/Rva001DCCA0Kind.cpp` | `0x001DCCA0` |
| 430 | `game/GameEngine/Source/Common/Rva001DCD30Kind.cpp` | `0x001DCD30` |
| 431 | `game/GameEngine/Source/Common/Thing/ThingIsAboveTerrainOrWater.cpp` | `0x000C3F00` |
| 432 | `game/GameEngine/Source/Common/Thing/Rva00259390CreateAtPosition.cpp` | `0x00259390` |
| 433 | `game/GameEngine/Source/Common/BfmeConv2053.cpp` | `0x001F7210` |
| 434 | `game/GameEngine/Source/Common/BfmeConv2091.cpp` | `0x000C7D10` |
| 435 | `game/GameEngine/Source/Common/Rva001CA9C0.cpp` | `0x001CA9C0` |
| 436 | `game/GameEngine/Source/GameLogic/AI/Rva0014C9E0Allow.cpp` | `0x0014C9E0` |
| 437 | `game/GameEngine/Source/Common/Gen_001dcc80.cpp` | `0x001DCC80` |
| 438 | `game/GameEngine/Source/GameLogic/Pathfinder/PathfindBuildActualPathE10f0.cpp` | `0x003E10F0` |
| 439 | `game/GameEngine/Source/Common/Rva000D4770InterfaceDispatch.cpp` | `0x000D4770` |
| 440 | `game/GameEngine/Source/GameLogic/Object/Body/Rva002157C0Refresh.cpp` | `0x002157C0` |
| 441 | `game/GameEngine/Source/GameLogic/Object/Update/AIUpdateTargetDispatch_Thunk.cpp` | `0x0027E170` |
| 442 | `game/GameEngine/Source/GameLogic/AI/AIGroup_add.cpp` | `0x001526C0` |
| 443 | `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdFollowPathState_update.cpp` | `0x002BDDC0` |
| 444 | `game/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetState_update_Bfme.cpp` | `0x00182EA0` |
| 445 | `game/GameEngine/Source/Common/BfmeOwnerTMDo.cpp` | `0x002140B0` |
| 446 | `game/GameEngine/Source/GameClient/Drawable_setIndicatorColor.cpp` | `0x004186E0` |
| 447 | `game/GameEngine/Source/GameLogic/Object/BfmeMeleeHordeTargetInvalid.cpp` | `0x00175820` |
| 448 | `game/GameEngine/Source/Common/Rva002DD5B0Can.cpp` | `0x002DD5B0` |

Frozen-index before: 17/20 LINKS, 1758B.
After: 17/20 LINKS, 1758B; no loss.
Current-provider preview: 20/20 UNKNOWN; unknown proves no linked-byte gain.

BFME2 reference0630f0ef47d0a818bb2e97583b43cfb1ecd35491 remains read-only.
Its Code/ maps to game/; no donor RVAs, compiler settings or private buffer
representations are copied. BFME1 native providers and settled headers determine
the target ABI. The earlier DXERR route prerequisite is unchanged and not retried.
Full census43852286500 measured fe40b725e8, the preceding 200-task completion.
Its 3,094,682 LINKED bytes and the unchanged follow-up43870552474 are recorded
separately; neither result measures this later cohort.

## Unselected retail-copy retirement

0 redundant retail COMDAT copies are retired only with a complete current native provider inventory.
The retiring consumer is not the selected object; its current copy matches the
control digest. The actual selected object has current input receipts, the same
digest, an existing matched identity and full native RetailTruth proof. Unknown
definers, stale names, unmeasured names, MAP exceptions and selected-copy removal
are refused. The complete private cohort and the final ordinary-object cohort
must retain the exact selected object/digest and its complete file hash.
Existing verifiers, row ownership/extents, pins and baselines remain unchanged. Native EH locator metadata is reported separately. This proves
provider preservation in the current native index; it is not a new full census.

## Progressive source units

A file may have a prior independently verified repair of another type.
This cohort selects only a remaining local class definition and never repeats
an already completed source/family. Every owned row is reread from the current
ledger, reserved again, and verified against the immediate committed baseline.

## Family reference and native contract inspection

Read-only BFME2 revision `0630f0ef47d0a818bb2e97583b43cfb1ecd35491`; 1443 matching header/provider/consumer files.
Inspection baseline `b8f0b633f8d3e68380fb37790958d03c67b02f1f`; identical canonical header SHA256 `048b53316d897a6606d6e540966f59cb0849e18b301b3f1019c8e9e10f6c2151`.
No donor implementation or layout is copied. Reviewed declaration/caller paths:
- `Code/GameEngine/Include/Common/Module.h` SHA256 `55326bed1265f4a3913d82f24018aff0d7e96d206a45848b0b6e11120088d47e`
- `Code/GameEngine/Include/Common/FXListDie.h` SHA256 `2a4cf5a0fddfa84fcac8ed07a78b3c9fb442150743b77aa4b98f041ab68bdfae`
- `Code/GameEngine/Source/Common/Thing/thing.h` SHA256 `86a0a1dd359f1f58a6a4902966cf589937e9060889b4970b4f79e94c389a6a41`
- `Code/GameEngine/Include/Common/BaseUpgrade.h` SHA256 `f31d153d3b72ffe91547d96e64601da513838f083289ffb4683d654b28eae6b1`
- `Code/GameEngine/Include/Common/Rva00252B68.h` SHA256 `23508f3d29c535d26ee76095dd9f26aec6a27c021a84ffca682c427785752de8`
- `Code/GameEngine/Include/GameClient/Drawable.h` SHA256 `077adb4775d47d5204fdee7aa0e116f133f3bc92ddb41670541122db7bf39866`

Native class_contract inspection (bounded sample; unresolved entries are retained,
not represented as settled global ABI facts). This cohort requires the stricter
per-source pointer-view completion above, all other concrete contracts unchanged, and complete runtime identity:

```text
Thing: class (bytes), sizeof 1 (majority), bases [] (majority); 12 views, 0 uncompiled, zh CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
  QUEUE field@0x0: {'4:P': 1, '4:VPTR': 1}
  QUEUE slot0: {'__vecDelDtor(uint)': 1} beyond the retail vftable's 0 slots
```

## Ordinary source include context

The final ordinary source and the saved original source were independently
compiled with include tracing. Optimization, defines and STLport are retained.
Any added roots must exactly match their recorded local-directory additions.
The new primary header must resolve to its exact local path.
Any existing always.h resolution must retain the same complete path set.
This adopts the named primary class; it does not claim a wholesale WWLib
migration. Complete ordinary runtime and concrete class checks remain required.
