# SubsystemDeleter<T>: the owned-subsystem destructor family

## The family

Sixty 89-byte destructors (`BigOwnedPointerDtors.cpp`) each delete the object
held through `*[this+4]` and null it. Each is called through an ILT by a
30-byte scalar-deleting destructor at A-0x30, whose one-slot vtable is
installed by an 18-byte constructor at A-0x50 that stores its argument at
`[this+4]`. The constructors store the address of a subsystem's global
pointer (`TheAI`, ...), which fixed the class argument T per family member;
earlier commits pinned the family as `SubsystemSlot<T>`.

## ILT evidence

Retail has no game RTTI. `tools/ilt_oracle.py` windows (frozen
`ilt_windows.tsv`) refute every `SubsystemSlot` spelling (e.g.
`check '??1?$SubsystemSlot@VActionManager@@@@UAE@XZ' 0x72060` is
CONTRADICTED). A dictionary search (about 105,000 identifiers from
`inputs/reference` plus `<prefix><Ptr|Holder|Slot|Deleter|...>` compounds;
template V/U/PAV and non-template prefix/suffix spellings; UAE/MAE/QAE) over
six family slots found exactly one scheme fitting all six: `SubsystemDeleter`.
Tested over the whole family with `ilt_oracle.Oracle.check`:

- `??1?$SubsystemDeleter@V<T>@@@@UAE@XZ` at the dtor's ILT: 59/60 fit
- `??_G?$SubsystemDeleter@V<T>@@@@UAEPAXI@Z` at the ??_G body: 59/60 fit
- `??0?$SubsystemDeleter@V<T>@@@@QAE@AAPAV<T>@@@Z` at the ctor body: 58/59 fit
  (`QAE@PAX@Z` and `QAE@PAPAV<T>@@@Z` fit 0/59)

176 of 179 independent windows fit; the sum of per-name false-fit
probabilities is 0.23, so a wrong scheme would be expected to fit under one
window, not 176. Each name carries T, so the same fits confirm the template
name and the 59 class names.

The three misses are all `ParticleSystemManager` (dtor 0x70620, ??_G 0x705F0,
ctor 0x705D0): its class argument is not `ParticleSystemManager`, and no
reference identifier fits. That member keeps its address-derived name.

## Per-class results

| T | dtor | ??1 at ILT | ??_G | ??0 |
|---|---|---|---|---|
| AI | 0x71220 | fit 0x13A48 | fit 0x711F0 | fit 0x711D0 |
| ActionManager | 0x72060 | fit 0x37542 | fit 0x72030 | fit 0x72010 |
| AerialPathfinder | 0x712E0 | fit 0x54F7 | fit 0x712B0 | fit 0x71290 |
| AptPlayer | 0x70FE0 | fit 0x444B8 | fit 0x70FB0 | fit 0x70F90 |
| ArmorStore | 0x70B60 | fit 0x172CE | fit 0x70B30 | fit 0x70B10 |
| AttributeModifierStore | 0x71520 | fit 0x20941 | fit 0x714F0 | fit 0x714D0 |
| AudioManager | 0x6F960 | fit 0x223BD | fit 0x6F930 | fit 0x6F910 |
| BuildAssistant | 0x70C20 | fit 0x1B7DE | fit 0x70BF0 | fit 0x70BD0 |
| CDManagerInterface | 0x6FEA0 | fit 0x220E3 | fit 0x6FE70 | fit 0x6FE50 |
| CaveSystem | 0x70320 | fit 0x401A1 | fit 0x702F0 | fit 0x702D0 |
| CrateSystem | 0x718E0 | fit 0x3C52E | fit 0x718B0 | fit 0x71890 |
| DamageFXStore | 0x70AA0 | fit 0x294F1 | fit 0x70A70 | fit 0x70A50 |
| EmotionSystem | 0x70CE0 | fit 0x1B2C0 | fit 0x70CB0 | fit 0x70C90 |
| Eva | 0x6FA20 | fit 0x3B51B | fit 0x6F9F0 | fit 0x6F9D0 |
| ExperienceLevelSystem | 0x70F20 | fit 0x83C3 | fit 0x70EF0 | fit 0x70ED0 |
| FXListStore | 0x706E0 | fit 0x27728 | fit 0x706B0 | fit 0x70690 |
| FunctionLexicon | 0x70020 | fit 0x292AD | fit 0x6FFF0 | fit 0x6FFD0 |
| GameClient | 0x71160 | fit 0x4473D | fit 0x71130 | fit 0x71110 |
| GameLogic | 0x71A60 | fit 0x410B | fit 0x71A30 | fit 0x71A10 |
| GameResultsInterface | 0x722A0 | fit 0x44BD9 | fit 0x72270 | fit 0x72250 |
| GameState | 0x721E0 | fit 0x32F56 | fit 0x721B0 | fit 0x72190 |
| GameStateMap | 0x72120 | fit 0x2062B | fit 0x720F0 | fit 0x720D0 |
| GameTextInterface | 0x6F8A0 | fit 0x1C274 | fit 0x6F870 | fit 0x6F850 |
| GlobalData | 0x6F720 | fit 0x3B96C | fit 0x6F6F0 | fit 0x6F6D0 |
| GlobalLanguage | 0x6F7E0 | fit 0x268AA | fit 0x6F7B0 | fit 0x6F790 |
| GlobalWeatherSystem | 0x6FF60 | fit 0x31D72 | fit 0x6FF30 | fit 0x6FF10 |
| HouseColorSystem | 0x71E20 | fit 0x46673 | fit 0x71DF0 | fit 0x71DD0 |
| LightPointSystem | 0x70E60 | fit 0xB9EC | fit 0x70E30 | fit 0x70E10 |
| LivingWorldCampaignManager | 0x71EE0 | fit 0x436F8 | fit 0x71EB0 | fit 0x71E90 |
| LivingWorldLogic | 0x713A0 | fit 0xF240 | fit 0x71370 | fit 0x71350 |
| LivingWorldManager | 0x710A0 | fit 0x34E96 | fit 0x71070 | fit 0x71050 |
| LocomotorStore | 0x70920 | fit 0x2F077 | fit 0x708F0 | fit 0x708D0 |
| LuaScriptEngine | 0x71760 | fit 0x40683 | fit 0x71730 | fit 0x71710 |
| MessageStream | 0x701A0 | fit 0x31C46 | fit 0x70170 | fit 0x70150 |
| MetaMap | 0x71D60 | fit 0x1C4C7 | fit 0x71D30 | fit 0x71D10 |
| ModuleFactory | 0x700E0 | fit 0x3A6D4 | fit 0x700B0 | fit 0x70090 |
| MultiplayerSettings | 0x6FC60 | fit 0x2C543 | fit 0x6FC30 | fit 0x6FC10 |
| ObjectCreationListStore | 0x70860 | fit 0x3817C | fit 0x70830 | fit 0x70810 |
| ParticleSystemManager | 0x70620 | MISS 0x2D7BD | MISS 0x705F0 | MISS 0x705D0 |
| PlayerAITypeSet | 0x704A0 | fit 0x42C21 | fit 0x70470 | fit 0x70450 |
| PlayerList | 0x719A0 | fit 0x309B3 | fit 0x71970 | fit 0x71950 |
| PlayerTemplateStore | 0x70560 | fit 0x41E39 | fit 0x70530 | fit 0x70510 |
| Radar | 0x71BE0 | fit 0x27C87 | fit 0x71BB0 | - |
| RankInfoStore | 0x703E0 | fit 0x2325E | fit 0x703B0 | fit 0x70390 |
| RecorderClass | 0x71B20 | fit 0x25045 | fit 0x71AF0 | fit 0x71AD0 |
| ScienceStore | 0x6FAE0 | fit 0x1B18A | fit 0x6FAB0 | fit 0x6FA90 |
| ScriptEngine | 0x716A0 | fit 0x43BEE | fit 0x71670 | fit 0x71650 |
| SidesList | 0x70260 | fit 0x467FE | fit 0x70230 | fit 0x70210 |
| SpecialPowerStore | 0x709E0 | fit 0x248C0 | fit 0x709B0 | fit 0x70990 |
| SplineService | 0x71460 | fit 0x39BDF | fit 0x71430 | fit 0x71410 |
| SubsystemLegend | 0x6F660 | fit 0x2BDF | fit 0x6F630 | fit 0x6F610 |
| TaintManager | 0x715E0 | fit 0x9A5C | fit 0x715B0 | fit 0x71590 |
| TeamFactory | 0x71820 | fit 0x2DDDF | fit 0x717F0 | fit 0x717D0 |
| TerrainRoadCollection | 0x6FDE0 | fit 0x45C50 | fit 0x6FDB0 | fit 0x6FD90 |
| TerrainTypeCollection | 0x6FD20 | fit 0x2C520 | fit 0x6FCF0 | fit 0x6FCD0 |
| ThingFactory | 0x70DA0 | fit 0x25E5A | fit 0x70D70 | fit 0x70D50 |
| UpgradeCenter | 0x6FBA0 | fit 0x111D | fit 0x6FB70 | fit 0x6FB50 |
| VictoryConditionsInterface | 0x71CA0 | fit 0x315D9 | fit 0x71C70 | fit 0x71C50 |
| VictorySystem | 0x71FA0 | fit 0xD1AC | fit 0x71F70 | fit 0x71F50 |
| WeaponStore | 0x707A0 | fit 0x307B5 | fit 0x70770 | fit 0x70750 |

## ParticleSystemManager stays unresolved

The three `ParticleSystemManager` rows keep their existing names and pins
(`??_G?$SubsystemSlot@VParticleSystemManager@@@@UAEPAXI@Z` at 0x705F0, its
constructor at 0x705D0 and the address-derived destructor at 0x70620): ILT
contradicts every spelling tried for them, including
`SubsystemDeleter<ParticleSystemManager>`, so the holder's real class argument
is unresolved. `initSubsystem<ParticleSystemManager>` is an explicit
specialization in `game/Libraries/Source/subsystem/SubsystemInterface.cpp`
that keeps that holder; every other subsystem uses `SubsystemDeleter<T>` from
`subsystem_interface.h`.

Radar's constructor at 0x71B90 has no SubsystemSlot row (it is
`??0Rva00071B90Holder@@QAE@PAX@Z`) and was not tested; it is left as is.
