# Registered subsystem lifecycle slots

Retail image: `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`,
SHA-256 `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
All addresses are RVAs unless marked VA. pefile and capstone supplied the bytes
and instruction boundaries; existing semantic row names alone are not proof.

## Family enumeration and slot anchor

For each `via=new` row in `gameengine_init_subsystems.tsv`, disassemble the
registered constructor (first 500 bytes up to the first return), collect immediate
primary-vptr stores through ECX/ESI/EDI/EBP, and retain tables whose
slot 2 is the BFME `SubsystemInterface::loadIniFilesFromLegend` entry at
`009A1A50`. This bounded census recovers 39 registrations; it is not an exhaustive claim
about constructors whose table stores occur later or use another register. Most also share slot 3,
ILT `000436B2` -> `00067930`, the already-proven inherited
`SubsystemInterface::postProcessLoad`. Do not infer a derived owner when a
registration installs only SubsystemInterface's abstract table.

The unmodified Zero Hour
`GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h` declares
virtual destructor, init, postProcessLoad, reset, update, draw in that order.
BFME inserts its legend-loading virtual at slot 2: init stays at slot 1,
postProcessLoad becomes 3, reset 4, update 5. The base abstract table VA
`01141640` has purecall at 1/4/5 and the two independently reconstructed
legend/post-load entries at 2/3. The independently registered PlayerTemplateStore
table VA `01084BA0` agrees: slot 1 -> `000E41A0` (`init`), slot 4 -> `000E0BC0`
(`reset`), slot 5 -> `000E0BD0` (`update`), all with Zero Hour twins.
The registered WeaponStore table VA `010A13C8` further fixes reset at slot 4
through its substantial matched cleanup body `001E27D0` (89 bytes), while
PlayerList table VA `0108417C` fixes update at slot 5 through the matched
`000DF2D0` body (32 bytes). This note makes no new identification of slots 6 onward.

## MultiplayerSettings: init, update, reset

The owner is established by GameEngine's actual registration and constructor,
not by the deleting-destructor name in slot 0:

- At `00079594`, `GameEngine::init` allocates `0x88` bytes.
- At `000795AE`, it calls ILT `0002B0BC` -> constructor `0008EF80`.
- At `000795C5`, it pushes VA `0107655C`, the literal `TheMultiplayerSettings`.
- At `000795D3`, it passes global storage VA `012ED5FC`, and at `000795D8`
  calls ILT `00035B66` -> `initSubsystem<MultiplayerSettings>` at `000733D0`.
- The global's typed symbol is
  `?TheMultiplayerSettings@@3PAVMultiplayerSettings@@A`, independently bound to
  VA `012ED5FC` in `dir32_addresses.csv`. Zero Hour `MultiplayerSettings.h:145`
  declares `extern MultiplayerSettings *TheMultiplayerSettings`.
- Constructor instruction `0008EFA5` stores primary vtable VA `0107F954`.
  The constructor's 205-byte clean reconstruction in `INI/INIMultiplayer.cpp`
  independently matches the BFME 0x88-byte layout and field-parse owner.

| Slot | Pointer RVA | ILT RVA | Body RVA | Public virtual declaration |
|---|---|---|---|---|
| 1 | `00C7F958` | `0000ED40` | `0008F080` | `void init()` |
| 4 | `00C7F964` | `0002C89F` | `0008F0A0` | `void reset()` |
| 5 | `00C7F968` | `0001956A` | `0008F090` | `void update()` |

Each body is exactly `C3` followed by INT3 padding. Each stub VA occurs exactly
once as a whole-image dword, at its table entry above. These are distinct
class-specific overrides, not a shared no-op inferred to belong to this class.
The common slots 2/3 retain the family anchors above.

The lexical/type witness is unmodified Zero Hour
`GeneralsMD/Code/GameEngine/Include/Common/MultiplayerSettings.h:80-88`:
`class MultiplayerSettings : public SubsystemInterface` explicitly defines
public virtual empty `init()`, `update()`, and `reset()`. Inherited virtual
slots retain the base order, so the derived declaration order does not swap
reset and update. All three return void, accept no arguments and are non-const:
`?init@MultiplayerSettings@@UAEXXZ`, `?reset@MultiplayerSettings@@UAEXXZ`,
`?update@MultiplayerSettings@@UAEXXZ`.

The existing BFME header under `inputs/reference/shims/multiplayer` preserves
these same bodies while supplying the established BFME class layout. The new
TU includes that header and forces emission of the three inline overrides;
it does not duplicate the class or invent any field. Replace the three old
address-placeholder rows at unchanged one-byte extents and remove their
orphaned definitions.

## Mechanical constructor-table census

The labels here name registered globals, not newly inferred class identities.
Repeated abstract-base tables are included for reproducibility, not claimed
as distinct concrete classes. All listed tables carry slot 2 -> `009A1A50`.

| Global | Constructor RVA | Primary-store RVA | Table RVA |
|---|---|---|---|
| TheSubsystemLegend | `0x78ad0` | `0x78af4` | `0xc75f98` |
| TheWritableGlobalData | `0x84510` | `0x84543` | `0xc7c68c` |
| TheGlobalLanguageData | `0x439e70` | `0x439ea3` | `0xcf4124` |
| TheEva | `0x4271b0` | `0x4271ea` | `0xcf1fa8` |
| TheUpgradeCenter | `0x10a6a0` | `0x10a6b3` | `0xc88d24` |
| TheMultiplayerSettings | `0x8ef80` | `0x8efa5` | `0xc7f954` |
| TheTerrainTypes | `0xa71c0` | `0xa71c8` | `0xc80ee0` |
| TheTerrainRoads | `0x601430` | `0x601440` | `0xd14fd4` |
| TheGlobalWeatherSystem | `0x39b450` | `0x39b48c` | `0xcebd10` |
| TheSidesList | `0x19ea80` | `0x19eab1` | `0xc9c204` |
| TheCaveSystem | `0x3785e0` | `0x3785f1` | `0xcea230` |
| ThePlayerTemplateStore | `0xe3f50` | `0xe3f5a` | `0xc84ba0` |
| TheFXListStore | `0x42e020` | `0x42e049` | `0xcf35a4` |
| TheWeaponStore | `0x1e5290` | `0x1e529a` | `0xca13c8` |
| TheObjectCreationListStore | `0x1dad50` | `0x1dad75` | `0xc9f9dc` |
| TheLocomotorStore | `0x1b7d70` | `0x1b7d95` | `0xc9df10` |
| TheSpecialPowerStore | `0xeb9d0` | `0xeb9da` | `0xc85cc4` |
| TheDamageFXStore | `0x67c10` | `0x67c3c` | `0xc758f8` |
| TheArmorStore | `0x1b0bc0` | `0x1b0bec` | `0xc9c838` |
| TheBuildAssistant | `0xfda80` | `0xfdaa5` | `0xc860d8` |
| TheEmotionSystem | `0x37cc20` | `0x37cc2a` | `0xcea8d4` |
| TheLightPointSystem | `0x39c160` | `0x39c16a` | `0xcebdd4` |
| TheExperienceLevelSystem | `0x381480` | `0x3814b2` | `0xcea948` |
| TheLivingWorldManager | `0x6171d0` | `0x61720c` | `0xd16bfc` |
| TheAI | `0x14c170` | `0x14c1a2` | `0xc959a8` |
| TheAerialPathfinder | `0x76b60` | `0x76b84` | `0xc75ee8` |
| TheLivingWorldLogic | `0x3c2fc0` | `0x3c2ff2` | `0xcedbdc` |
| TheTaintManager | `0x880f00` | `0x880f3a` | `0xd32b54` |
| TheScriptEngine | `0x347e60` | `0x347e90` | `0xce7a30` |
| TheLuaScriptEngine | `0x2eb4a0` | `0x2eb4cb` | `0xccfac4` |
| TheTeamFactory | `0xf2250` | `0xf2280` | `0xc85f1c` |
| TheCrateSystem | `0x3799d0` | `0x3799da` | `0xcea34c` |
| ThePlayerList | `0xdfbd0` | `0xdfc08` | `0xc8417c` |
| TheMetaMap | `0x5b6a80` | `0x5b6a88` | `0xd0f024` |
| TheLivingWorldCampaignManager | `0x3b5100` | `0x3b5114` | `0xcecb78` |
| TheVictorySystem | `0x1e0160` | `0x1e0194` | `0xc9fd8c` |
| TheActionManager | `0xc3ff0` | `0xc3ff8` | `0xc83b90` |
| TheGameStateMap | `0x1129b0` | `0x1129bf` | `0xc89644` |
| TheGameState | `0x1111c0` | `0x111207` | `0xc893e0` |

## TerrainRoadCollection and FXListStore

These two independently registered classes use the same proven subsystem
slots 1/4/5. Their owner evidence, decoded from `GameEngine::init`, is:

| Global literal | Constructor call RVA / ILT / body | Literal push RVA / literal VA | Global push RVA / storage VA | initSubsystem call RVA / ILT / body |
|---|---|---|---|---|
| TheTerrainRoads | `00079640 / 00045FF7 / 00601430` | `00079657 / 01076534` | `00079665 / 012F7008` | `0007966A / 000148B2 / 00073550` |
| TheFXListStore | `00079923 / 00010208 / 0042E020` | `0007993A / 0107642C` | `00079948 / 012F144C` | `0007994D / 0001AC6C / 00073E50` |

Zero Hour explicitly declares `TerrainRoadCollection *TheTerrainRoads`
(`GameClient/TerrainRoads.h:231`) and `FXListStore *TheFXListStore`
(`GameClient/FXList.h:222`). The corresponding typed global symbols in
`dir32_addresses.csv` independently bind to VAs `012F7008` and `012F144C`.
Thus no class is inferred merely by stripping a `The` prefix.

TerrainRoadCollection's constructor stores VA `01114FD4` at instruction
`00601440`; FXListStore's stores VA `010F35A4` at `0042E049`. Both tables
retain the family slot-2 and slot-3 anchors. The lifecycle entries are:

| Owner | Slot | Pointer RVA | ILT RVA | Body RVA | Method |
|---|---|---|---|---|---|
| TerrainRoadCollection | 1 | `00D14FD8` | `000117F7` | `00601460` | init |
| TerrainRoadCollection | 4 | `00D14FE4` | `0002DC90` | `00601470` | reset |
| TerrainRoadCollection | 5 | `00D14FE8` | `000416FA` | `00601480` | update |
| FXListStore | 1 | `00CF35A8` | `00040D5E` | `0042DED0` | init |
| FXListStore | 4 | `00CF35B4` | `00024BF9` | `0042DEE0` | reset |
| FXListStore | 5 | `00CF35B8` | `00044DAF` | `0042DEF0` | update |

Each body is a complete one-byte RET (`C3`) followed by INT3 padding, and each
listed stub VA occurs exactly once as a little-endian dword in the whole
image, at the listed pointer. Their individual registered tables fix the
owners; no shared or inherited no-op is assigned to a concrete class.

The full lexical/type twins are unmodified Zero Hour
`GeneralsMD/Code/GameEngine/Include/GameClient/TerrainRoads.h:198-209` and
`GameClient/FXList.h:192-202`. Both classes publicly inherit SubsystemInterface
and explicitly define public inline `void init() {}`, `void reset() {}`, and
`void update() {}`. Although these declarations omit the repeated `virtual`
keyword, overriding a virtual retains virtual dispatch. Therefore all six
methods use `@@UAEXXZ` (public virtual void, non-const, no arguments), not
`@@QAEXXZ`. The source TUs include the upstream headers and force those exact
inline bodies to be emitted. All six existing address-placeholder rows retain
their original one-byte extents.

The name-regression checker falsely pairs removed address-named helper
`b_0042def0` with the first emission anchor `rva0042DED0Emission` in the new
FXListStore TU. They are different bodies: the old RVA `0042DEF0` becomes
`FXListStore::update`, while that anchor emits init at `0042DED0`. The exact
source-snapshot entry in name_corrections.json records this false pairing,
not a descriptive-to-opaque rename of a retail method.


## ActionManager lifecycle overrides

GameEngine::init allocates 8 bytes at `0007A25F` and calls constructor ILT
`0001C76F` at `0007A276`, resolving to `000C3FF0`. The registration sequence
pushes VA `01076130` (literal `TheActionManager`) at `0007A28A`, typed global
storage VA `012ED700` at `0007A298`, then calls ILT `00012E86` -> `000757E0`
at `0007A29D`. The unmodified ZH GameEngine.cpp registration likewise creates
ActionManager. The header declares `extern ActionManager *TheActionManager`.
Constructor `000C3FF0` calls SubsystemInterface constructor `009A1A30` at
`000C3FF3`, then installs VA `01083B90` at `000C3FF8`. This is a concrete
owner table, not an inherited callback assigned to an arbitrary subsystem.

| Slot | Pointer RVA | ILT RVA | Body RVA | ZH twin |
|---|---|---|---|---|
| 1 | `00C83B94` | `0002383F` | `000C4010` | ActionManager::init |
| 4 | `00C83BA0` | `00043EBE` | `000C4020` | ActionManager::reset |
| 5 | `00C83BA4` | `00043E64` | `000C4030` | ActionManager::update |

Whole-image bytewise scans find each absolute stub pointer exactly once, at
the listed slot. All three complete bodies are RET followed immediately by
INT3. The table shares common slots 2/3 (`009A1A50`/`00067930`) with the
mechanical census above; substantive independent lifecycle twins already
anchor slots 1/4/5. ZH `Common/ActionManager.h:69-71` explicitly defines all
three public non-const virtual void/no-argument empty overrides. Their ABI is
`?init@ActionManager@@UAEXXZ`, `?reset@ActionManager@@UAEXXZ`, and
`?update@ActionManager@@UAEXXZ`. These names are direct lexical twins, not
inferred from the empty bodies. The dedicated TU includes that header and
forces its inline definitions to emit using qualified-call anchors. Replace
the three address placeholders at unchanged one-byte extents and remove only
their orphan standalone TUs. No new pin, member, or shared header is needed.


## TerrainTypeCollection lifecycle overrides

GameEngine::init allocates `0x0C` bytes at `000795E0`, calls ILT `000484AF`
-> ctor `000A71C0` at `000795F7`, pushes VA `01076548` (TheTerrainTypes)
at `0007960E`, and passes typed global VA `012ED640` at `0007961C` to
registration ILT `000147EA` -> `00073490` at `00079621`. The ZH header
Common/TerrainTypes.h declares `extern TerrainTypeCollection *TheTerrainTypes`;
its GameEngine registration constructs exactly that class. Constructor
`000A71C0` calls SubsystemInterface `009A1A30` at `000A71C3` and installs
primary VA `01080EE0` at `000A71C8`, establishing the introducing owner.

| Slot | Pointer RVA | ILT RVA | Body RVA | Explicit ZH method |
|---|---|---|---|---|
| 1 | `00C80EE4` | `0002E672` | `000A71E0` | init |
| 4 | `00C80EF0` | `00002649` | `000A71F0` | reset |
| 5 | `00C80EF4` | `0001AD84` | `000A7200` | update |

Each absolute stub VA occurs exactly once in a bytewise whole-image pointer
scan, at the listed slot. All bodies are C3 then CC, proving their one-byte
extents. Common slots 2/3 and the already-established lifecycle alignment
agree with the census. The public section of ZH Common/TerrainTypes.h:225-227
explicitly defines these empty overrides. They are virtual by inheritance,
non-const, void, with no arguments, and therefore use
`?init@TerrainTypeCollection@@UAEXXZ`, `?reset@TerrainTypeCollection@@UAEXXZ`,
and `?update@TerrainTypeCollection@@UAEXXZ`. The new header-emission TU
replaces only these three address placeholders; unrelated shared-TU bodies
remain. No inferred data field or callee pin is introduced.
