// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /Iinputs/reference/shims/sweep /Iinputs/reference/shims/win32localfilesystem_wide /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

// RtsPoolGlueDeletes.cpp ------------------------------------------------
//
// Retail folds every class's pool-glue `operator delete(void *, MagicEnum)`
// onto one 12-byte body at 0x007EFFF0 that calls the CRT free import thunk,
// not ::operator delete (0x00881EB0). Player.cpp's own copy of these eleven
// bodies is a different function because the shipped header spells the glue
// `::operator delete(p)`, and Player.cpp cannot carry the TU-scoped override
// while other rows in it are still red. This TU carries it instead: it opens
// the same headers Player.cpp does with the override in force and forces each
// of the eleven inline bodies to be emitted by taking its address.
// The override below has to be in place before PreRTS.h pulls in Upgrade.h, so
// open GameMemory.h (which defines the macro) by hand first; PreRTS.h then
// re-includes these eight as no-ops.
#include "Lib/Basetype.h"
#include "Common/STLTypedefs.h"
#include "Common/Errors.h"
#include "Common/Debug.h"
#include "Common/AsciiString.h"
#include "Common/SubsystemInterface.h"
#include "Common/GameCommon.h"
#include "Common/GameMemory.h"
#pragma push_macro("MEMORY_POOL_GLUE_WITHOUT_GCMP")
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
// Retail's pool-glue placement operator delete frees through the CRT import;
// the shipped header spells it ::operator delete(p). TU-scoped so no header
// changes -- same lever as Common/RTS/Team.cpp. The plain one-argument
// operator delete keeps ::operator delete, which is what ??_G... calls.
extern "C" void free(void *);
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ \
		DEBUG_ASSERTCRASH(s == sizeof(ARGCLASS), ("The wrong operator new is being called; ensure all objects in the hierarchy have MemoryPoolGlue set up correctly")); \
		return MP_GLUE_ALLOCATE(ARGCLASS); \
	} \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ \
		free(p); \
	} \
protected: \
	inline void *operator new(size_t s) \
	{ \
		DEBUG_ASSERTCRASH(s == sizeof(ARGCLASS), ("The wrong operator new is being called; ensure all objects in the hierarchy have MemoryPoolGlue set up correctly")); \
		return ::operator new(s); \
	} \
	inline void operator delete(void *p) \
	{ \
		::operator delete(p); \
	} \
private: \
	virtual MemoryPool *getObjectMemoryPool() \
	{ \
		return ARGCLASS::getClassMemoryPool(); \
	} \
public:
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#define DEFINE_SCIENCE_AVAILABILITY_NAMES

#include "Common/ActionManager.h"
#include "Common/BuildAssistant.h"
#include "Common/CRCDebug.h"
#include "Common/DisabledTypes.h"
#include "Common/GameState.h"
#include "Common/GlobalData.h"
#include "Common/MessageStream.h"
#include "Common/MiscAudio.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/PlayerTemplate.h"
#include "Common/ProductionPrerequisite.h"
#include "Common/Radar.h"
#include "Common/ResourceGatheringManager.h"
#include "Common/Team.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/TunnelTracker.h"
#include "Common/Upgrade.h"
#include "Common/WellKnownKeys.h"
#include "Common/Xfer.h"
#include "Common/BitFlagsIO.h"
#include "Common/SpecialPower.h"

#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameClient/Eva.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameText.h"

#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/AISkirmishPlayer.h"
#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/Object.h"
#include "GameLogic/Scripts.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/SidesList.h"
#include "GameLogic/TerrainLogic.h"
#include "GameLogic/Squad.h"
#include "GameLogic/RankInfo.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/AutoDepositUpdate.h"
#include "GameLogic/Module/StealthUpdate.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/Module/SupplyTruckAIUpdate.h"
#include "GameLogic/Module/BattlePlanUpdate.h"
#include "GameLogic/Module/ProductionUpdate.h"
#include "GameLogic/VictoryConditions.h"
#include "GameLogic/Locomotor.h"
#include "Win32Device/Common/Win32LocalFile.h"

#include "GameNetwork/GameInfo.h"
#pragma pop_macro("MEMORY_POOL_GLUE_WITHOUT_GCMP")

// Taking the address of the placement delete is what forces MSVC to emit the
// inline body; the pointers themselves are constant-initialised data.
#define EMIT_POOL_GLUE_DELETE(cls) \
	void (*bfme_pool_glue_delete_##cls)(void *, cls::cls##MagicEnum) = &cls::operator delete;

EMIT_POOL_GLUE_DELETE( AIPlayer )
EMIT_POOL_GLUE_DELETE( AISkirmishPlayer )
EMIT_POOL_GLUE_DELETE( BattlePlanBonuses )
EMIT_POOL_GLUE_DELETE( BuildListInfo )
EMIT_POOL_GLUE_DELETE( KindOfPercentProductionChange )
EMIT_POOL_GLUE_DELETE( PlayerRelationMap )
EMIT_POOL_GLUE_DELETE( ResourceGatheringManager )
EMIT_POOL_GLUE_DELETE( Squad )
EMIT_POOL_GLUE_DELETE( TeamRelationMap )
EMIT_POOL_GLUE_DELETE( TunnelTracker )
EMIT_POOL_GLUE_DELETE( Upgrade )

// PartitionManager.cpp's two, reachable from the same include set.
EMIT_POOL_GLUE_DELETE( PartitionData )
EMIT_POOL_GLUE_DELETE( SimpleObjectIterator )

// Weapon.cpp's three and ThingFactory.cpp's one: same folded 12-byte body at
// 0x007EFFF0, and both owning TUs are pure C++ that cannot carry the override.
EMIT_POOL_GLUE_DELETE( Weapon )
EMIT_POOL_GLUE_DELETE( WeaponBonusSet )
EMIT_POOL_GLUE_DELETE( WeaponTemplate )
EMIT_POOL_GLUE_DELETE( ThingTemplate )
EMIT_POOL_GLUE_DELETE( ProductionEntry )

// TerrainLogic.cpp's two: Waypoint's own copy was one displacement wrong and
// Bridge's was not emitted there at all (nothing in that TU takes its address).
EMIT_POOL_GLUE_DELETE( Waypoint )
EMIT_POOL_GLUE_DELETE( Bridge )

// Nine more rows off the same folded body, every class already open in the
// include set above: their own TUs each still carry unrelated red rows, so the
// glue delete is verified here instead of waiting on them.
EMIT_POOL_GLUE_DELETE( EvaCheckInfo )
EMIT_POOL_GLUE_DELETE( RadarObject )
EMIT_POOL_GLUE_DELETE( UpgradeTemplate )
EMIT_POOL_GLUE_DELETE( Object )
EMIT_POOL_GLUE_DELETE( Path )
EMIT_POOL_GLUE_DELETE( PathNode )
EMIT_POOL_GLUE_DELETE( TeamInQueue )
EMIT_POOL_GLUE_DELETE( WorkOrder )
EMIT_POOL_GLUE_DELETE( Locomotor )
EMIT_POOL_GLUE_DELETE( LocomotorTemplate )
EMIT_POOL_GLUE_DELETE( Win32LocalFile )
