// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// readable body of ?findStaticLODLevel@GameLODManager@@QAE?AW4StaticGameLODLevel@@XZ: Code/GameEngine/Source/Common/GameLOD.cpp

// Open-BFME5: lift the GameLODManager::findStaticLODLevel MASM dump to clean C++.
//
// BFME rewrote this one. Zero Hour's version benchmarks the hardware against
// m_lodPresets; BFME's looks "StaticGameLOD" up in the preferences map and only
// falls back to the cached ideal level when the key is absent.
//
// Skeleton follows CustomMatchPreferences::getLastLadderAddr: the map at this+4
// with its header node doubling as the end sentinel. The key lives in an inner
// scope because retail destroys it immediately after the lookup, and the map
// pointer is assigned inside that scope because retail holds plain `this` in esi
// across the constructor and only then does `add esi,4`.
//
// Real AsciiString rather than a stand-in, per the by-value-temporary rule in
// docs/lessons.md.
//
// The lever for the last four bytes is find() being non-throwing under /EHsc.
// Retail stashes the argument temporary with `mov [esp+0xC],esp` -- reusing the
// dead key slot -- which is /EHsc bookkeeping, yet retail carries no SEH frame.
// Both hold at once only if nothing can throw across the key's lifetime: mark
// find() throw() and the frame the key would otherwise need disappears while the
// stash stays. /EHs-c- drops the stash instead and lands four bytes short, which
// is the residue logged against the sibling OptionPreferences accessor.
#include "PreRTS.h"
#include "Common/AsciiString.h"

enum StaticGameLODLevel
{
	STATIC_GAME_LOD_UNKNOWN = -1,
	STATIC_GAME_LOD_LOW = 0
};

struct CustomMapNodeShim
{
	unsigned char m_unreconstructed_00[0x14];
	AsciiString m_value;							///< retail node+0x14
};

struct CustomPreferenceMapShim
{
	CustomMapNodeShim *m_header;					///< doubles as the end sentinel
	CustomMapNodeShim *find(const AsciiString &key) throw();	///< ILT thunk at 0x0000AEAC
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameLOD.h
class GameLODManager
{
public:
	StaticGameLODLevel findStaticLODLevel(void);
	int getStaticGameLODIndex(AsciiString name);	///< body at 0x000245A0

	unsigned char m_unreconstructed_00[0x16C0];
	StaticGameLODLevel m_idealDetailLevel;			///< retail this+0x16C0
};

extern GameLODManager *TheGameLODManager;			///< retail [0x012ED5AC]

// ?findStaticLODLevel@GameLODManager@@QAE?AW4StaticGameLODLevel@@XZ
StaticGameLODLevel GameLODManager::findStaticLODLevel(void)
{
	CustomPreferenceMapShim *map;
	CustomMapNodeShim *node;

	{
		AsciiString key("StaticGameLOD");

		map = (CustomPreferenceMapShim *)((unsigned char *)this + 4);
		node = map->find(key);
	}

	if (node == map->m_header)
	{
		// No preference recorded: report the cached ideal level, or unknown when
		// the manager global has not been created yet.
		if (TheGameLODManager != 0)
		{
			return TheGameLODManager->m_idealDetailLevel;
		}

		return STATIC_GAME_LOD_UNKNOWN;
	}

	return (StaticGameLODLevel)TheGameLODManager->getStaticGameLODIndex(node->m_value);
}
