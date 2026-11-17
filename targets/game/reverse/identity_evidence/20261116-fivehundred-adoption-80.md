# Canonical header adoptions: tasks 468-475 of 500

Immediate baseline: `b3bb281d8c40b2bfdd19ba5ffee7be25f93caf00`.
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

Combined ordinary gate: 264/264 functions
in 16 files; 395 DIR32 references; body guard OK.
Consumers preserve 8 rows / 4440B.
Native cleanup locator repairs: 0.

| Task | Source | Retained RVAs |
|---|---|---|
| 468 | `game/GameEngine/Source/GameLogic/Object/BfmeConv2025.cpp` | `0x001D0520` |
| 469 | `game/GameEngine/Source/GameLogic/Object/Object_rva001CEAD0_onVeterancyLevelChanged.cpp` | `0x001CEAD0` |
| 470 | `game/GameEngine/Source/GameLogic/System/ArmySummaryPlayerArmySync.cpp` | `0x00365DF0` |
| 471 | `game/GameEngine/Source/GameClient/DrawableHealthBar.cpp` | `0x0041CA50` |
| 472 | `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva00270DF0RebuildPath.cpp` | `0x00270DF0` |
| 473 | `game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/SupplyCenterProductionExitUpdateExitObjectViaDoor.cpp` | `0x002D2790` |
| 474 | `game/GameEngine/Source/GameLogic/AI/Rva001766F0State_update.cpp` | `0x001766F0` |
| 475 | `game/GameEngine/Source/GameLogic/Object/Contain/HordeContain/HordeMemberOrder00245420.cpp` | `0x00245420` |

Frozen-index before: 5/8 LINKS, 2782B.
After: 5/8 LINKS, 2782B; no loss.
Current-provider preview: 8/8 UNKNOWN; unknown proves no linked-byte gain.

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
- `game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/SupplyCenterProductionExitUpdateExitObjectViaDoor.cpp`: retained `W:\OpenBFME\Open-BFME-1\inputs\reference\CnC_Generals_Zero_Hour\GeneralsMD\Code\Libraries\Source\WWVegas\WWLib\always.h`.
