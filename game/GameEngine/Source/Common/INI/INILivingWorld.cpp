// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The LivingWorldMapInfo block -- BFME's campaign-map description, 71 INI fields
// (docs/ini_schema.md). Zero Hour has no Living World at all.
//
// The global is named: GameEngine::init passes the literal "TheLivingWorldManager"
// immediately before pushing 0x012F706C (tools/dump_subsystems.py). Its class is
// not named -- the subsystem is BFME-only, so Zero Hour cannot supply the type
// and no ledger row carries it -- so it is reached through a local view here,
// the same way GameLOD.cpp reaches GameLODManager.
#include "PreRTS.h"
#include "Common/INI.h"

struct LivingWorldMapInfo
{
	char m_fields000[ 0x140 ];			// INI fields, 0x000 through 0x13f
	// Not an INI field: the table writes 0x13c and 0x144 but nothing writes here.
	// The parser sets it after initFromINI, which is what makes it a "this map
	// info has been loaded" flag rather than a setting.
	Bool m_isLoaded;					// 0x140
	char m_fields141[ 0x188 - 0x141 ];	// more INI fields, out to 0x184

	static const FieldParse m_fieldParseTable[];
};

struct RetailLivingWorldManager
{
	char m_unknown000[ 0x0c ];
	LivingWorldMapInfo m_mapInfo;		// 0x0c
};

extern RetailLivingWorldManager *TheLivingWorldManager;

void parseLivingWorldMapInfo( INI *ini )
{
	if( TheLivingWorldManager )
	{
		ini->initFromINI( &TheLivingWorldManager->m_mapInfo,
											LivingWorldMapInfo::m_fieldParseTable );
		TheLivingWorldManager->m_mapInfo.m_isLoaded = TRUE;
	}
}
