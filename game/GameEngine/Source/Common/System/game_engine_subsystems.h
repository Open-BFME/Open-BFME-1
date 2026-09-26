#pragma once
#include "subsystem_interface.h"

// The subsystems GameEngine::init (0x00079060) registers through initSubsystem<T>.
//
// Only classes whose NAME is proven from the binary appear here. The proof is the
// constructor at each registration site: init news the object and calls its ctor,
// and for these five that ctor already carries a decorated name in the ledger, so
// the template instantiation's own mangled name follows from it. Byte-verifying
// the instantiation does NOT prove the name -- a stub emits identical code
// whatever it is called -- which is exactly why the unproven ones are absent.
//
// Deliberately NOT listed, and why:
//   TheScienceStore / TheRankInfoStore / ThePlayerAITypeSet -- their registration
//     calls ??0SubsystemInterface@@QAE@XZ directly, i.e. no class-specific ctor
//     is emitted, so nothing in the binary names them.
//   TheTerrainTypes -- its ctor address resolves to ??0W3DPropDrawModuleData@@,
//     an ICF-folded trivial ctor shared with an unrelated class. Not evidence.
//   TheGameText / TheAudio / TheCDManager / TheFunctionLexicon / TheModuleFactory /
//     TheMessageStream / TheFXParticleSystemManager -- built by a factory call
//     rather than new+ctor, so there is no ctor to read a name from.
//   TheWritableGlobalData, TheGlobalLanguageData, TheMultiplayerSettings,
//     TheGlobalWeatherSystem, TheFXListStore -- have their own ctor, but it is
//     unclaimed and their vtables contain no class-specific named slot, so
//     nothing names them yet.
//   TheCaveSystem -- its ctor sits between ?getTunnelTrackerForCaveIndex@CaveSystem@@
//     and ?registerNewCave@CaveSystem@@ in the same TU, which is suggestive but
//     is only TU locality; its vtable slots are all unclaimed. Left out until
//     something binds the ctor to the class directly.
//
// The stubs are abstract on purpose: initSubsystem<T> only forms a T* and
// converts it to SubsystemInterface*, so it never instantiates T.
class UpgradeCenter            : public SubsystemInterface {};   // TheUpgradeCenter,           ctor 0x0010A6A0
class TerrainRoadCollection    : public SubsystemInterface {};   // TheTerrainRoads,            ctor 0x00601430
class SidesList                : public SubsystemInterface {};   // TheSidesList,               ctor 0x0019EA80
class WeaponStore              : public SubsystemInterface {};   // TheWeaponStore,             ctor 0x001E5290
class ObjectCreationListStore  : public SubsystemInterface {};   // TheObjectCreationListStore, ctor 0x001DAD50
// ThePlayerTemplateStore, ctor 0x000E3F50: proven by the vtable that ctor installs
// (0x01084BA0), whose slot 1 is ?init@PlayerTemplateStore@@UAEXXZ -- a
// class-specific virtual. Slot 0 is an ICF-folded ??_GFileSystem@@ and is NOT
// evidence; slot 1 is.
class PlayerTemplateStore : public SubsystemInterface {};
// TheArmorStore, ctor at its registration site: the class name is proven the
// strongest way available -- game/GameEngine/Source/GameLogic/Object/Armor.cpp
// owns a byte-verified ?findArmorTemplate@ArmorStore@@ row, so the name is not
// an inference at all.
//
// Note these declarations are deliberately minimal and are NOT the ported class.
// initSubsystem<T> only forms a T* and converts it to SubsystemInterface*, so
// all it needs is the name and the base; the real ArmorStore, with its
// hash_map of templates, lives in Armor.cpp against the ZH header tree. They are
// separate on purpose -- this header is the registration manifest, not a port.
class ArmorStore : public SubsystemInterface {};

// Proven the same two ways as the entries above -- a ctor already decorated with
// the class name, or a class-specific virtual in the vtable that ctor installs.
class DamageFXStore : public SubsystemInterface {};	// 0x00074210, ctor ??0DamageFXStore@@QAE@XZ
class AI : public SubsystemInterface {};	// 0x00074990, vtable slot 3 = ?crc@AI@@UAEXPAVXfer@@@Z
class TeamFactory : public SubsystemInterface {};	// 0x00074F90, ctor ??0TeamFactory@@QAE@XZ
class CrateSystem : public SubsystemInterface {};	// 0x00075050, ctor ??0CrateSystem@@QAE@XZ
class PlayerList : public SubsystemInterface {};	// 0x00075110, ctor ??0PlayerList@@QAE@XZ
class GameState : public SubsystemInterface {};	// 0x00075960, ctor ??0GameState@@QAE@XZ

// The next block is named a third way, which needed no new byte-matching at all.
// initSubsystem<T> takes its subsystem by REFERENCE -- T*& -- so the pointer the
// registration site passes as the first argument has to be declared exactly T*;
// a reference will not bind through a conversion. Each site in GameEngine::init
// pushes the address of one global, those addresses are already proven by the
// DIR32 relocations of matched functions that read the same globals, and the
// global's own declared type is therefore the template argument.
//
// The method self-checks: of the 14 registrations already claimed above, every
// one whose global resolves agrees with the name it was given, with no
// contradictions.
//
// Each class below additionally has at least one byte-verified ledger row
// carrying its decorated name, so the name is not resting on the global alone.
// Two candidates are deliberately absent -- TheGameText's GameTextInterface at
// 0x00073010 and TheGameClient's GameClient at 0x000748D0 -- because neither
// class appears in any ledger row, which would leave our own header as the only
// authority for the name.

class GlobalData : public SubsystemInterface {};	// 0x00072E90, TheWritableGlobalData; name from ?getPath_UserData@GlobalData@@QBE?AVAsciiString@@XZ
class AudioManager : public SubsystemInterface {};	// 0x000730D0, TheAudio; name from ?releaseAudioEventRTS@AudioManager@@UAEXPAVAudioEven
class MultiplayerSettings : public SubsystemInterface {};	// 0x000733D0, TheMultiplayerSettings; name from ?getColor@MultiplayerSettings@@QAEPAVMultiplayerColo
class FunctionLexicon : public SubsystemInterface {};	// 0x00073790, TheFunctionLexicon; name from ?gameWinDrawFunc@FunctionLexicon@@QAEP6AXPAVGameWind
class MessageStream : public SubsystemInterface {};	// 0x00073910, TheMessageStream; name from ??0TranslatorData@MessageStream@@QAE@XZ
class ParticleSystemManager : public SubsystemInterface {};	// 0x00073D90, TheParticleSystemManager; name from ?findTemplate@ParticleSystemManager@@QBEPAVParticleS
class FXListStore : public SubsystemInterface {};	// 0x00073E50, TheFXListStore; name from ?findFXList@FXListStore@@QBEPBVFXList@@PBD@Z
class LocomotorStore : public SubsystemInterface {};	// 0x00074090, TheLocomotorStore; name from ?findLocomotorTemplate@LocomotorStore@@QAEPAVLocomot
class SpecialPowerStore : public SubsystemInterface {};	// 0x00074150, TheSpecialPowerStore; name from ?findSpecialPowerTemplateByID@SpecialPowerStore@@QAE
class ThingFactory : public SubsystemInterface {};	// 0x00074510, TheThingFactory; name from ?findByTemplateID@ThingFactory@@QAEPBVThingTemplate@
class ScriptEngine : public SubsystemInterface {};	// 0x00074E10, TheScriptEngine; name from ?doFreezeTime@ScriptEngine@@QAEXXZ
class GameLogic : public SubsystemInterface {};	// 0x000751D0, TheGameLogic; name from ?createGhostObjectManager@GameLogic@@EAEPAVGhostObje
class RecorderClass : public SubsystemInterface {};	// 0x00075290, TheRecorder; name from ?appendNextCommand@RecorderClass@@IAEXXZ
// TheRadar / Radar at 0x00075350 is left out: the global names it the same way,
// but its body is 167 bytes where every other instantiation is 154, so the
// T*-to-SubsystemInterface* conversion there is not the trivial one a
// single-inheritance stub emits. Whatever Radar really derives from has to be
// recovered before the instantiation can be reproduced.
class ActionManager : public SubsystemInterface {};	// 0x000757E0, TheActionManager; name from ?canOverrideSpecialPowerDestination@ActionManager@@Q

// ScienceStore, 0x00073250. The manifest used to exclude this one because its
// registration constructs through ??0SubsystemInterface@@ directly, so no
// class-specific ctor is emitted there. Three things now settle it without one:
// the site passes the literal "TheScienceStore" as the subsystem name, its first
// argument is 0x012ED7AC, and Science.cpp binds ?TheScienceStore@@3PAVScienceStore@@A
// to exactly that address from byte-verified rows -- including
// friend_parseScienceDefinition, which the INI block table registers for the
// "Science" keyword and which reads 0x012ED7AC as a store with m_sciences at +0x08.
// The class name itself is carried by a dozen byte-verified @ScienceStore@@ rows.
//
// This also decides the 0x012ED7AC collision noted in the DIR32 whitelist: the
// address is TheScienceStore, and ControlBar.cpp's commandButtonTooltip is the
// row referencing the wrong global.
class ScienceStore : public SubsystemInterface {};

// ---------------------------------------------------------------------------
// tools/dump_subsystems.py reopened the ten below, which the exclusions above
// were written before it existed.
//
// Every GameEngine::init registration site passes the subsystem's own name as a
// string literal immediately before the address of the global it initialises:
//
//     push 0x1076494          ; "TheRankInfoStore"
//     call AsciiString::AsciiString
//     push 0x12f1014          ; &TheRankInfoStore
//     call initSubsystem<T>
//
// That names the VARIABLE from the binary, with no ctor needed -- which is what
// the "built by a factory call, so there is no ctor to read a name from" and
// "calls ??0SubsystemInterface@@ directly" exclusions above were blocked on.
// It does not by itself name the TYPE, and the two differ often enough to be
// dangerous: TheTerrainTypes is a TerrainTypeCollection*, TheCDManager a
// CDManagerInterface*, TheGameResultsQueue a GameResultsInterface*. Chopping
// "The" would have been wrong three times in ten.
//
// So the type comes from a second source, and there are two tiers of it:
//
//   (a) a byte-verified ledger row carries the class name. Same standard as the
//       block above.
//   (b) no ledger row does, and Zero Hour's header declares the global with the
//       type. Weaker, but it is an outside authority rather than this file --
//       the objection that kept TheGameText out was precisely that our own
//       header would otherwise be the only one asserting the name.
//
class Eva : public SubsystemInterface {};	// 0x00073190, TheEva; (a) ?parseEvaMessageFromIni@Eva@@SAXPAVINI@@PAX1PBX@Z
class TerrainTypeCollection : public SubsystemInterface {};	// 0x00073490, TheTerrainTypes; (a) ?newTerrain@TerrainTypeCollection@@
class ModuleFactory : public SubsystemInterface {};	// 0x00073850, TheModuleFactory; (a) 14 rows incl ??0ModuleTemplate@ModuleFactory@@QAE@XZ
class RankInfoStore : public SubsystemInterface {};	// 0x00073B50, TheRankInfoStore; (a) ?getRankInfo@RankInfoStore@@QBEPBVRankInfo@@H@Z
class MetaMap : public SubsystemInterface {};	// 0x000754E0, TheMetaMap; (a) ?findGameMessageMetaType@MetaMap@@IAE?AW4Type@GameMessage@@PBD@Z
class GameResultsInterface : public SubsystemInterface {};	// 0x00075A20, TheGameResultsQueue; (a) ?createNewGameResultsInterface@GameResultsInterface@@SAPAV1@XZ

class GameTextInterface : public SubsystemInterface {};	// 0x00073010, TheGameText; (b) ZH: extern GameTextInterface *TheGameText
class CDManagerInterface : public SubsystemInterface {};	// 0x00073610, TheCDManager; (b) ZH: extern CDManagerInterface *TheCDManager
class BuildAssistant : public SubsystemInterface {};	// 0x00074390, TheBuildAssistant; (b) ZH: extern BuildAssistant *TheBuildAssistant
class GameStateMap : public SubsystemInterface {};	// 0x000758A0, TheGameStateMap; (b) ZH: extern GameStateMap *TheGameStateMap

// Still out, and now for one reason only -- no second source for the TYPE.
// TheVictorySystem, TheLivingWorldManager, TheAerialPathfinder, TheTaintManager,
// ThePlayerAITypeSet and TheExperienceLevelSystem are all BFME-only, so Zero
// Hour cannot supply tier (b), and no ledger row carries a matching class name.
// The variable names read like the class names, but that is the guess that
// TerrainTypeCollection, CDManagerInterface and GameResultsInterface each show
// to be unsafe. TheRadar stays out for the separate reason given above: 167
// bytes where every other instantiation is 154.

// A later fix to tools/dump_subsystems.py raised the site count from 43 to 60:
// it had been reading uninitialised globals as string literals, because .data's
// virtual size runs past its raw size and the zero-fill tail decodes as whatever
// section follows. TheHouseColorSystem's global came back as "CloneImage" and
// its whole site was dropped. These four are from that recovered set, same two
// tiers of type evidence as above.
//
// Note VictoryConditionsInterface: chopping "The" off TheVictoryConditions gives
// VictoryConditions, which is not the class. That is the fourth time in this
// file the shortcut would have been wrong.
class GlobalLanguage : public SubsystemInterface {};	// 0x00072F50, TheGlobalLanguageData; (a) ?parseFontDesc@GlobalLanguage@@SAXPAVINI@@PAX1PBX@Z
class CaveSystem : public SubsystemInterface {};	// 0x00073A90, TheCaveSystem; (a) ?getTunnelTrackerForCaveIndex@CaveSystem@@QAEPAVTunnelTracker@@H@Z
class GameClient : public SubsystemInterface {};	// 0x000748D0, TheGameClient; (b) ZH: extern GameClient *TheGameClient
class VictoryConditionsInterface : public SubsystemInterface {};	// 0x00075420, TheVictoryConditions; (b) ZH: extern VictoryConditionsInterface *TheVictoryConditions

// ---------------------------------------------------------------------------
// CONVENTION-NAMED. Weaker than everything above -- read this before trusting a
// name in this block.
//
// These sixteen are named from the "TheXxx" string literal their registration
// site passes, with the class taken as Xxx. That literal names the GLOBAL. The
// class name follows only by convention, and this file already records four
// times the convention is wrong:
//
//     TheTerrainTypes       -> TerrainTypeCollection
//     TheCDManager          -> CDManagerInterface
//     TheGameResultsQueue   -> GameResultsInterface
//     TheVictoryConditions  -> VictoryConditionsInterface
//
// So treat roughly one name in four here as likely wrong. They are claimed
// anyway, by explicit decision, because the BYTES are verified either way --
// initSubsystem<T> emits identical code whatever T is called, so a wrong name
// costs a wrong label on a correct match and nothing else. Every row carries
// "convention-named" in its functions.csv note so the block stays reversible.
//
// Both stronger routes were checked for all sixteen and neither produces
// anything -- see tools/name_subsystem.py, which does this mechanically:
//   (a) no registration constructor is in the ledger under a decorated name.
//       TheEmotionSystem's resolves to ??0SupplyCenterProductionExitUpdate-
//       ModuleData@@, an ICF-folded trivial constructor, which is the same
//       non-evidence already recorded for TheTerrainTypes.
//   (b) no vtable these constructors install has a class-specific named slot.
//       The only named slots are loadIniFilesFromLegend (in 44 other vtables)
//       and ??_GSubsystemInterface (in 5), both inherited or ICF-folded.
//
// Six of them are worse than merely unproven. TheScienceStore, TheRankInfoStore,
// ThePlayerAITypeSet, TheSplineService, TheAttributeModifierStore and
// TheHouseColorSystem share BOTH constructor 0x009A1A30 and vtable 0x00D41640 --
// they are plain SubsystemInterfaces with no overrides at all. No byte in the
// image distinguishes them from each other, so route (b) can never name them,
// however much else gets decompiled.
//
// TheRadar is deliberately NOT here even though Zero Hour supplies a real
// `extern Radar *TheRadar;`, which would be tier (b) evidence. Its instantiation
// is 167 bytes where the other 59 are all 154, so it is not the same template
// shape and claiming it at 154 would be a false match, not just a false name.
class GlobalWeatherSystem        : public SubsystemInterface {};	// 0x000736D0
class PlayerAITypeSet            : public SubsystemInterface {};	// 0x00073C10  (shares ctor+vtable)
class EmotionSystem              : public SubsystemInterface {};	// 0x00074450
class LightPointSystem           : public SubsystemInterface {};	// 0x000745D0
class ExperienceLevelSystem      : public SubsystemInterface {};	// 0x00074690
class AptPlayer                  : public SubsystemInterface {};	// 0x00074750  (factory-built)
class LivingWorldManager         : public SubsystemInterface {};	// 0x00074810
class AerialPathfinder           : public SubsystemInterface {};	// 0x00074A50
class LivingWorldLogic           : public SubsystemInterface {};	// 0x00074B10
class SplineService              : public SubsystemInterface {};	// 0x00074BD0  (shares ctor+vtable)
class AttributeModifierStore     : public SubsystemInterface {};	// 0x00074C90  (shares ctor+vtable)
class TaintManager               : public SubsystemInterface {};	// 0x00074D50
class LuaScriptEngine            : public SubsystemInterface {};	// 0x00074ED0
class HouseColorSystem           : public SubsystemInterface {};	// 0x000755A0  (shares ctor+vtable)
class LivingWorldCampaignManager : public SubsystemInterface {};	// 0x00075660
class VictorySystem              : public SubsystemInterface {};	// 0x00075720
