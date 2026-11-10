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

// The global's identity IS named: GameEngine::init pushes the literal
// "TheLivingWorldManager" (0x010762FC) immediately before pushing 0x012F706C,
// and EA's own definition lives in
// game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldManager.cpp as
// `LivingWorldManager *TheLivingWorldManager`.  The class is not named -- the
// subsystem is BFME-only, so Zero Hour cannot supply the type and no ledger row
// carries it -- so this TU keeps its local view RetailLivingWorldManager and
// casts the canonical global at the use.
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

static inline RetailLivingWorldManager *retailLivingWorldManager( void )
{
	return reinterpret_cast< RetailLivingWorldManager * >( TheLivingWorldManager );
}

// Retail .rdata VA 0x01116000: the 71-entry table and its null terminator;
// tokens, parsers and offsets read from the image. Three sound fields and
// EyeTower bind through ILT thunks (0x00018E7B, 0x00030152).
extern "C" void __identifier("?j_00018e7b@@YAXXZ")(INI *, void *, void *, const void *);
extern "C" void __identifier("?j_00030152@@YAXXZ")(INI *, void *, void *, const void *);
const FieldParse LivingWorldMapInfo::m_fieldParseTable[] =
{
	{ "MapObject", INI::parseAsciiString, 0, 0x0 },
	{ "CloudBorderSubObject", INI::parseAsciiString, 0, 0x11C },
	{ "TextLayerSubObject", INI::parseAsciiString, 0, 0x120 },
	{ "Center", INI::parseCoord2D, 0, 0x4 },
	{ "Extent", INI::parseCoord2D, 0, 0xC },
	{ "EmbersPartSys", INI::parseAsciiString, 0, 0x20 },
	{ "CloudPos", INI::parseCoord3D, 0, 0x14 },
	{ "Ambient", INI::parseRGBColor, 0, 0x24 },
	{ "SunDir", INI::parseCoord2D, 0, 0x30 },
	{ "SunRGB", INI::parseRGBColor, 0, 0x38 },
	{ "Accent1Dir", INI::parseCoord2D, 0, 0x44 },
	{ "Accent1RGB", INI::parseRGBColor, 0, 0x4C },
	{ "Accent2Dir", INI::parseCoord2D, 0, 0x58 },
	{ "Accent2RGB", INI::parseRGBColor, 0, 0x60 },
	{ "GondorBanner", INI::parseAsciiString, 0, 0x6C },
	{ "RohanBanner", INI::parseAsciiString, 0, 0x70 },
	{ "MordorBanner", INI::parseAsciiString, 0, 0x74 },
	{ "IsengardBanner", INI::parseAsciiString, 0, 0x78 },
	{ "NeutralBanner", INI::parseAsciiString, 0, 0x7C },
	{ "GondorAnts", INI::parseAsciiString, 0, 0x80 },
	{ "RohanAnts", INI::parseAsciiString, 0, 0x84 },
	{ "MordorAnts", INI::parseAsciiString, 0, 0x88 },
	{ "IsengardAnts", INI::parseAsciiString, 0, 0x8C },
	{ "NeutralAnts", INI::parseAsciiString, 0, 0x90 },
	{ "BattleMarker", INI::parseAsciiString, 0, 0x94 },
	{ "PalantirMarker", INI::parseAsciiString, 0, 0x98 },
	{ "BattleMarkerCreatedSound", __identifier("?j_00018e7b@@YAXXZ"), 0, 0xE8 },
	{ "EnterMapSound", __identifier("?j_00018e7b@@YAXXZ"), 0, 0xEC },
	{ "BannerScaleSpeed", INI::parseReal, 0, 0x9C },
	{ "BannerMaxScale", INI::parseReal, 0, 0xA0 },
	{ "BannerTiltAngle", INI::parseReal, 0, 0xA4 },
	{ "BannerHeight", INI::parseReal, 0, 0xA8 },
	{ "ArmyHeight", INI::parseReal, 0, 0xAC },
	{ "BeaconHeight", INI::parseReal, 0, 0xB0 },
	{ "AnimRays", INI::parseAsciiString, 0, 0xB4 },
	{ "AnimRaysPartSys", INI::parseAsciiString, 0, 0xB8 },
	{ "AnimRaysPartSysOffset", INI::parseCoord3D, 0, 0xBC },
	{ "AnimRaysColor", INI::parseRGBColor, 0, 0xC8 },
	{ "AnimRaysColorScale", INI::parseReal, 0, 0xD4 },
	{ "AnimRaysEffectShells", INI::parseInt, 0, 0xD8 },
	{ "AnimRaysEffectDiameter", INI::parseInt, 0, 0xDC },
	{ "AnimRaysEffectLifetime", INI::parseInt, 0, 0xE0 },
	{ "AnimRaysCreateSound", __identifier("?j_00018e7b@@YAXXZ"), 0, 0xE4 },
	{ "AnimCloud", INI::parseAsciiString, 0, 0xF0 },
	{ "AnimCloudPartSys", INI::parseAsciiString, 0, 0xF4 },
	{ "NumAnimClouds", INI::parseInt, 0, 0xF8 },
	{ "AnimCloudLifetime", INI::parseInt, 0, 0x114 },
	{ "AnimCloudRegionMin", INI::parseCoord3D, 0, 0xFC },
	{ "AnimCloudRegionMax", INI::parseCoord3D, 0, 0x108 },
	{ "MordorCloud", INI::parseAsciiString, 0, 0x118 },
	{ "CloudGrowthPos", INI::parseCoord3D, 0, 0x124 },
	{ "CloudGrowthRate", INI::parseInt, 0, 0x130 },
	{ "CloudInitialSize", INI::parseReal, 0, 0x134 },
	{ "CloudGrowthSize", INI::parseReal, 0, 0x13C },
	{ "CloudInitialOpacity", INI::parseReal, 0, 0x138 },
	{ "CameraBoundX", INI::parseReal, 0, 0x144 },
	{ "CameraBoundY", INI::parseReal, 0, 0x148 },
	{ "ShadowColor", INI::parseRGBColor, 0, 0x14C },
	{ "EnableMapShadows", INI::parseBool, 0, 0x158 },
	{ "ArmySelectedIconObject", INI::parseAsciiString, 0, 0x15C },
	{ "ArmyHilightedIconObject", INI::parseAsciiString, 0, 0x160 },
	{ "ArmySelectedFadeInStart", INI::parseInt, 0, 0x164 },
	{ "ArmySelectedFadeInEnd", INI::parseInt, 0, 0x168 },
	{ "ArmySelectedFadeOutStart", INI::parseInt, 0, 0x16C },
	{ "ArmySelectedFadeOutEnd", INI::parseInt, 0, 0x170 },
	{ "ArmyHilightedFadeInTime", INI::parseInt, 0, 0x174 },
	{ "ArmyHilightedFadeOutTime", INI::parseInt, 0, 0x178 },
	{ "ArmySoldierLarge", INI::parseAsciiString, 0, 0x17C },
	{ "ArmySoldierMedium", INI::parseAsciiString, 0, 0x180 },
	{ "ArmySoldierSmall", INI::parseAsciiString, 0, 0x184 },
	{ "EyeTower", __identifier("?j_00030152@@YAXXZ"), 0, 0x0 },
	{ 0, 0, 0, 0 }
};

void parseLivingWorldMapInfo( INI *ini )
{
	if( TheLivingWorldManager )
	{
		ini->initFromINI( &retailLivingWorldManager()->m_mapInfo,
											LivingWorldMapInfo::m_fieldParseTable );
		retailLivingWorldManager()->m_mapInfo.m_isLoaded = TRUE;
	}
}
