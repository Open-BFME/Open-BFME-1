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
