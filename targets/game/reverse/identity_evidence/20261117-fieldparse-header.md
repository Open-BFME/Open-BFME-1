# One existing FieldParse definition;28 source reconciliations

Continuation tasks548-575 replace28 per-unit descriptor views with one existing
BFME1 descriptor contract. They add no authored function bytes and establish no
memory/leak, crash,64-bit, FPS or runtime improvement.

## Independent target facts

The matched128B field lookup at RVA00850880 (`INI_stl.cpp`) walks16B entries.
It tests token+0, returns callback+4, copies userData+8 and offset+12.
The complete728B dispatcher at00851910 (`INI_initFromINIMulti.cpp`) calls the
returned callback with four pointer words: INI, instance, instance+offset+extra,
and userData. Their independent names, extents, original code and normal gates
already exist. The three actual parser-provider units pass91/91 retained rows.

The existing local ini_inline/ini_noinline/ini_parser/ini_bfme headers already
describe that exact contract, including FieldParse::set. Their four definitions
and callback typedefs now include the single standalone Common/FieldParse.h.
Each extracted body is text-compared after whitespace/comments and Int->int
normalization; subsequent header line numbers are preserved. The small native
INI/INI.h view uses it too. This introduces no guessed class or member name.

## What the old views did and did not prove

The selected callers mostly pass descriptor pointers without reading fields.
Their old stand-ins use m_token/m_parse/m_userData/m_offset spellings, unsigned
offsets, or a void() callback placeholder. Those spellings are not target ABI
evidence. The canonical role/type reconciliation is explicit: struct,size16,
four4B slots at0/4/8/12, three pointer slots and a32-bit integer offset;
no bases, virtual state or static data. The canonical fields are the original
token/parse/userData/offset and the independently witnessed four-argument
callback. All OTHER complete original CodeView contracts remain identical.
The real canonical header is traced in a fresh private layout compilation.

## Verification and ownership

Before/after ordinary gates pass124/124 functions in31 source units, including
all28 consumers and the three parser providers:87 string literals,10 empty
string references,11 constants and136 DIR32 references. Baseline findings:0.
Every consumer ordinary object retains its ENTIRE runtime section inventory,
definitions, bytes, relocation offsets/kinds/targets, weak contracts and aliases.
No callable or datum addition/removal/retirement exemption is available.
All22,994 pre-change ordinary objects (398,714,527B) are preserved separately
for the complete post-header comparison; no hardlink can be overwritten by a
compiler. Shared headers require the normal full native commit gate. Its full
result and the post-gate object audit belong in the final continuation report.

Native claims cover each selected row and the shared FieldParse header work.
Normal hooks, sole-writer logs, current byte/data/alias checks and ordinary
publication remain required. No census index, verifier, baseline, callable pin,
import, source alias or generated source is edited.

## Reference context and remaining limits

Read-only BFME2 reference0630f0ef47d0a818bb2e97583b43cfb1ecd35491 and its
FieldParse-facing module/INI declarations were consulted. BFME1 target code
and existing BFME1 headers establish all addresses, roles and callback ABI;
no donor address, type layout, body or toolchain is imported. The local
standalone header resolves the observed missing ascii_string.h/INI-redefinition
prerequisites without importing the full INI object into descriptor-only users.

The first30 ordinary-header private trials produced no successful adoption;
the standalone contract produces28 complete private/ordinary matches. Two
refused trials are not counted. Full-image linking remains distinct from source
parity; follow-up44135612880 still measures its earlier30f455d61089 input.

| Task | Consumer | Retained rows |
|---|---|---|
| 548 | `game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/RepairDockUpdateModuleDataBuildFieldParse.cpp` | 1 |
| 549 | `game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/RailedTransportDockUpdateModuleDataBuildFieldParse.cpp` | 1 |
| 550 | `game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/SupplyWarehouseDockUpdateModuleDataBuildFieldParse.cpp` | 1 |
| 551 | `game/GameEngine/Source/Common/Rva0059EB90IniParse.cpp` | 1 |
| 552 | `game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/MonsterDockUpdateModuleDataBuildFieldParse.cpp` | 1 |
| 553 | `game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/SupplyCenterDockUpdateModuleDataBuildFieldParse.cpp` | 1 |
| 554 | `game/GameEngine/Source/GameLogic/Object/Die/RefundDieModuleDataBuildFieldParse.cpp` | 1 |
| 555 | `game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawParseLodOptions.cpp` | 1 |
| 556 | `game/GameEngine/Source/GameClient/GUI/BannerUIUnitCategory.cpp` | 1 |
| 557 | `game/GameEngine/Source/Common/INI/Rva0006AF00FunctionCurveParse.cpp` | 1 |
| 558 | `game/GameEngine/Source/GameLogic/Object/AttackNugget_parse_Thunk.cpp` | 1 |
| 559 | `game/GameEngine/Source/Common/Thing/ThingTemplate_parsePrerequisites_Thunk.cpp` | 1 |
| 560 | `game/GameEngine/Source/GameLogic/LivingWorld/ParseFlashRegionsEvent.cpp` | 1 |
| 561 | `game/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDamagedBehaviorModuleDataBuildFieldParse.cpp` | 1 |
| 562 | `game/GameEngine/Source/GameLogic/Object/Behavior/AutoHealBehaviorModuleDataBuildFieldParse.cpp` | 1 |
| 563 | `game/GameEngine/Source/Common/Rva0059B8F0NuggetParse.cpp` | 1 |
| 564 | `game/GameEngine/Source/GameLogic/Object/Update/RubbleRiseUpdateBuildFieldParse.cpp` | 1 |
| 565 | `game/GameEngine/Source/GameLogic/Object/ApplyRandomForceNugget_parse.cpp` | 1 |
| 566 | `game/GameEngine/Source/GameLogic/Object/Behavior/ReplenishUnitsBehaviorModuleDataBuildFieldParse.cpp` | 1 |
| 567 | `game/GameEngine/Source/Common/INI/Rva002284A0FieldParse.cpp` | 1 |
| 568 | `game/GameEngine/Source/GameLogic/AI/AI_parseSideInfo.cpp` | 1 |
| 569 | `game/GameEngine/Source/GameLogic/Object/GenericObjectCreationNuggetParseObject.cpp` | 1 |
| 570 | `game/GameEngine/Source/GameLogic/System/INILightPointLevel.cpp` | 1 |
| 571 | `game/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModuleData_buildFieldParse.cpp` | 1 |
| 572 | `game/GameEngine/Source/GameClient/Drawable/Behavior/Rva00608FE0ElementParse.cpp` | 2 |
| 573 | `game/GameEngine/Source/GameClient/Drawable/Behavior/Rva006077C0ParseSoundState.cpp` | 2 |
| 574 | `game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva0077D150ParseConditionState.cpp` | 2 |
| 575 | `game/GameEngine/Source/Common/INI/INIAudioSettings.cpp` | 3 |
