// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// BFME's SubsystemInterface, built against the native headers. The ZH-tree port
// in SubsystemInterface.cpp keeps ZH's behaviour (its dtor unregisters from
// TheSubsystemList); BFME's is empty — 0x009A1A40 is just "restore the vptr,
// then tail-jump to destroy m_name", which only comes out of an empty body and
// an out-of-line AsciiString dtor.
//
// The base vtable is at 0x01141640 and has nine slots. SubsystemLegend overrides
// 0/1/4/5 and inherits 2/3/6/7/8, which is how those five were ruled out of
// SubsystemLegend.cpp's membership.
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"
#include "subsystem_interface.h"
#include "subsystem_legend.h"
#include "Common/INI/INI.h"
#include "game_engine_subsystems.h"

SubsystemInterfaceList *TheSubsystemList;		// 0x0134C6C8

// ??1SubsystemInterface@@UAE@XZ
SubsystemInterface::~SubsystemInterface()
{
}

// ?getName@SubsystemInterface@@QAE?AVAsciiString@@XZ
AsciiString SubsystemInterface::getName(void)
{
	return m_name;
}

// ?loadIniFilesFromLegend@SubsystemInterface@@UAE_NXZ
// Vtable slot 2, inherited by every subsystem in the game. This is the whole
// point of SubsystemLegend: a subsystem looks itself up by name and loads the
// INI files and directories its "LoadSubsystem" block lists. The Bool it returns
// tells SubsystemInterfaceList::initSubsystem whether the legend supplied
// anything — if it did, the hard-coded paths GameEngine::init passed are skipped.
Bool SubsystemInterface::loadIniFilesFromLegend()
{
	if (!TheSubsystemLegend)
		return FALSE;

	// Declared before the lookup, not after: retail's xor bl,bl lands ahead of
	// the getName call, which only happens if the local is live by then.
	Bool loadedAny = FALSE;

	SubsystemLegendEntry *entry = TheSubsystemLegend->findEntry(getName());
	if (!entry)
		return FALSE;

	INI ini;

	// The xfer goes through a local rather than being written inline as the call
	// argument. That is what retail's register allocation says: it holds
	// TheSubsystemList->m_xfer in eax across both loops, which only happens when
	// the load is its own statement.
	for (AsciiString *f = entry->m_initFile.begin(); f != entry->m_initFile.end(); ++f)
	{
		Xfer *xfer = TheSubsystemList->m_xfer;
		loadedAny = TRUE;
		ini.loadFile(*f, INI_LOAD_OVERWRITE, xfer);
	}

	for (AsciiString *d = entry->m_initPath.begin(); d != entry->m_initPath.end(); ++d)
	{
		Xfer *xfer = TheSubsystemList->m_xfer;
		loadedAny = TRUE;
		ini.loadDirectory(*d, true, INI_LOAD_OVERWRITE, xfer, 0);
	}

	return loadedAny;
}

// ?initSubsystem@SubsystemInterfaceList@@QAEXPAVSubsystemInterface@@PAXPBD22PAVXfer@@VAsciiString@@@Z
// Name it, init it, then give the legend first refusal: if the subsystem's
// "LoadSubsystem" block supplied any files, the hard-coded paths GameEngine::init
// passed are skipped entirely. That precedence is the interesting part for anyone
// editing SubsystemLegend.ini.
void SubsystemInterfaceList::initSubsystem(SubsystemInterface *sys, void *slot, const char *path1,
										   const char *path2, const char *dirpath, Xfer *pXfer,
										   AsciiString name)
{
	sys->setName(name);
	sys->init();

	Bool loadedFromLegend = sys->loadIniFilesFromLegend();

	m_subsystems.push_back(std::make_pair(sys, slot));

	if (!loadedFromLegend)
	{
		INI ini;
		if (path1)
			ini.loadFile(path1, INI_LOAD_OVERWRITE, pXfer);
		if (path2)
			ini.loadFile(path2, INI_LOAD_OVERWRITE, pXfer);
		if (dirpath)
			ini.loadDirectory(dirpath, true, INI_LOAD_OVERWRITE, pXfer, 0);
	}
}

// ??$initSubsystem@VSubsystemLegend@@@@YAXAAPAVSubsystemLegend@@VAsciiString@@PAV0@PAVXfer@@PBD44@Z
// Force the SubsystemLegend instantiation retail carries at 0x00072DD0.
template void initSubsystem<SubsystemLegend>(SubsystemLegend *&, AsciiString, SubsystemLegend *,
											 Xfer *, const char *, const char *, const char *);

// The other instantiations GameEngine::init carries, one per subsystem, laid out
// consecutively from 0x00072DD0 at 192 bytes apiece.
template void initSubsystem<UpgradeCenter>(UpgradeCenter *&, AsciiString, UpgradeCenter *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<TerrainRoadCollection>(TerrainRoadCollection *&, AsciiString, TerrainRoadCollection *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<SidesList>(SidesList *&, AsciiString, SidesList *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<WeaponStore>(WeaponStore *&, AsciiString, WeaponStore *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<ObjectCreationListStore>(ObjectCreationListStore *&, AsciiString, ObjectCreationListStore *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<PlayerTemplateStore>(PlayerTemplateStore *&, AsciiString, PlayerTemplateStore *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<ArmorStore>(ArmorStore *&, AsciiString, ArmorStore *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<DamageFXStore>(DamageFXStore *&, AsciiString, DamageFXStore *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<AI>(AI *&, AsciiString, AI *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<TeamFactory>(TeamFactory *&, AsciiString, TeamFactory *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<CrateSystem>(CrateSystem *&, AsciiString, CrateSystem *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<PlayerList>(PlayerList *&, AsciiString, PlayerList *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<GameState>(GameState *&, AsciiString, GameState *, Xfer *, const char *, const char *, const char *);

// Named from the global each GameEngine::init registration site passes by
// reference -- see game_engine_subsystems.h for why that is proof.
template void initSubsystem<GlobalData>(GlobalData *&, AsciiString, GlobalData *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<AudioManager>(AudioManager *&, AsciiString, AudioManager *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<MultiplayerSettings>(MultiplayerSettings *&, AsciiString, MultiplayerSettings *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<FunctionLexicon>(FunctionLexicon *&, AsciiString, FunctionLexicon *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<MessageStream>(MessageStream *&, AsciiString, MessageStream *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<ParticleSystemManager>(ParticleSystemManager *&, AsciiString, ParticleSystemManager *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<FXListStore>(FXListStore *&, AsciiString, FXListStore *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<LocomotorStore>(LocomotorStore *&, AsciiString, LocomotorStore *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<SpecialPowerStore>(SpecialPowerStore *&, AsciiString, SpecialPowerStore *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<ThingFactory>(ThingFactory *&, AsciiString, ThingFactory *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<ScriptEngine>(ScriptEngine *&, AsciiString, ScriptEngine *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<GameLogic>(GameLogic *&, AsciiString, GameLogic *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<RecorderClass>(RecorderClass *&, AsciiString, RecorderClass *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<ActionManager>(ActionManager *&, AsciiString, ActionManager *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<ScienceStore>(ScienceStore *&, AsciiString, ScienceStore *, Xfer *, const char *, const char *, const char *);

// Named by tools/dump_subsystems.py -- see game_engine_subsystems.h.
template void initSubsystem<Eva>(Eva *&, AsciiString, Eva *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<TerrainTypeCollection>(TerrainTypeCollection *&, AsciiString, TerrainTypeCollection *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<ModuleFactory>(ModuleFactory *&, AsciiString, ModuleFactory *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<RankInfoStore>(RankInfoStore *&, AsciiString, RankInfoStore *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<MetaMap>(MetaMap *&, AsciiString, MetaMap *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<GameResultsInterface>(GameResultsInterface *&, AsciiString, GameResultsInterface *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<GameTextInterface>(GameTextInterface *&, AsciiString, GameTextInterface *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<CDManagerInterface>(CDManagerInterface *&, AsciiString, CDManagerInterface *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<BuildAssistant>(BuildAssistant *&, AsciiString, BuildAssistant *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<GameStateMap>(GameStateMap *&, AsciiString, GameStateMap *, Xfer *, const char *, const char *, const char *);

template void initSubsystem<GlobalLanguage>(GlobalLanguage *&, AsciiString, GlobalLanguage *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<CaveSystem>(CaveSystem *&, AsciiString, CaveSystem *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<GameClient>(GameClient *&, AsciiString, GameClient *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<VictoryConditionsInterface>(VictoryConditionsInterface *&, AsciiString, VictoryConditionsInterface *, Xfer *, const char *, const char *, const char *);

// Convention-named from the registration-site "TheXxx" literal, not from a
// decorated symbol -- see the block at the end of game_engine_subsystems.h for
// what that is worth and why the two stronger routes produce nothing here.
// TheRadar is excluded: 167 bytes where these are all 154.
template void initSubsystem<GlobalWeatherSystem>(GlobalWeatherSystem *&, AsciiString, GlobalWeatherSystem *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<PlayerAITypeSet>(PlayerAITypeSet *&, AsciiString, PlayerAITypeSet *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<EmotionSystem>(EmotionSystem *&, AsciiString, EmotionSystem *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<LightPointSystem>(LightPointSystem *&, AsciiString, LightPointSystem *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<ExperienceLevelSystem>(ExperienceLevelSystem *&, AsciiString, ExperienceLevelSystem *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<AptPlayer>(AptPlayer *&, AsciiString, AptPlayer *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<LivingWorldManager>(LivingWorldManager *&, AsciiString, LivingWorldManager *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<AerialPathfinder>(AerialPathfinder *&, AsciiString, AerialPathfinder *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<LivingWorldLogic>(LivingWorldLogic *&, AsciiString, LivingWorldLogic *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<SplineService>(SplineService *&, AsciiString, SplineService *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<AttributeModifierStore>(AttributeModifierStore *&, AsciiString, AttributeModifierStore *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<TaintManager>(TaintManager *&, AsciiString, TaintManager *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<LuaScriptEngine>(LuaScriptEngine *&, AsciiString, LuaScriptEngine *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<HouseColorSystem>(HouseColorSystem *&, AsciiString, HouseColorSystem *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<LivingWorldCampaignManager>(LivingWorldCampaignManager *&, AsciiString, LivingWorldCampaignManager *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<VictorySystem>(VictorySystem *&, AsciiString, VictorySystem *, Xfer *, const char *, const char *, const char *);
