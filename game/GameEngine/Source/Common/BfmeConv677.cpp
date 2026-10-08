// cl: /O2 /GR- /EHsc- /DNDEBUG /DWIN32 /D_WINDOWS /MD /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// BfmeOtherDCG only ever receives the INI* receiver of INI::initFromINI, so the
// call below goes through the real header rather than a stand-in member whose
// name nothing defines.
#include "PreRTS.h"
#include "Common/INI.h"

// Retail .rdata 0x01116D70, 464 bytes: the 28-entry field-parse table that
// bfmeGoDCG hands to INI::initFromINI, plus the zero terminator. Tokens,
// parsers and offsets are read from the image; parsers retail reaches through
// incremental-link thunks are named by those thunks. The owning record is not
// recovered, so the table keeps the alias this caller already spells.
void j_0002245d();
void j_00029be0();
void j_00031b1a();
void j_0003da78();
extern "C" const FieldParse bfmeInfoDCG[] =
{
	{ "MapName",	INI::parseAsciiString,	0,	0x8 },
	{ "DisplayName",	INI::parseAsciiString,	0,	0x10 },
	{ "ConqueredNotice",	INI::parseAsciiString,	0,	0xC },
	{ "MovieNameFirstTime",	INI::parseAsciiString,	0,	0x14 },
	{ "MovieNameRepeat",	INI::parseAsciiString,	0,	0x18 },
	{ "SkirmishStillImage",	INI::parseAsciiString,	0,	0x1C },
	{ "SkirmishVoiceTrack",	INI::parseAsciiString,	0,	0x20 },
	{ "SkirmishMusicTrack",	INI::parseAsciiString,	0,	0x24 },
	{ "SubObject",	INI::parseAsciiString,	0,	0x28 },
	{ "RegionBonus",	(INIFieldParseProc)j_00031b1a,	0,	0x2C },
	{ "SkirmishOpponent",	(INIFieldParseProc)j_0003da78,	0,	0x0 },
	{ "ConnectsTo",	(INIFieldParseProc)j_0002245d,	0,	0x0 },
	{ "OnWinActSubroutine",	INI::parseAsciiString,	0,	0x3C },
	{ "RegionPortrait",	INI::parseAsciiString,	0,	0x40 },
	{ "ArmyPlacementPos",	(INIFieldParseProc)j_00029be0,	0,	0x44 },
	{ "UnpackCamps",	INI::parseBool,	0,	0x50 },
	{ "MissionObjectiveTag",	INI::parseAsciiStringVectorAppend,	0,	0x54 },
	{ "BonusMissionObjectiveTag",	INI::parseAsciiStringVectorAppend,	0,	0x60 },
	{ "CustomCenterPoint",	INI::parseBool,	0,	0x74 },
	{ "CenterPoint",	INI::parseCoord2D,	0,	0x6C },
	{ "ArmyBonus",	INI::parseInt,	0,	0x78 },
	{ "LegendaryBonus",	INI::parseInt,	0,	0x80 },
	{ "ResourceBonus",	INI::parseInt,	0,	0x7C },
	{ "EndOfCampaign",	INI::parseBool,	0,	0x84 },
	{ "DisplayActNum",	INI::parseInt,	0,	0x88 },
	{ "CustomUIPopupPoint",	INI::parseBool,	0,	0x8C },
	{ "UIPopupPoint",	INI::parseCoord2D,	0,	0x90 },
	{ "DifficultyText",	INI::parseAsciiString,	0,	0x98 },
	{ 0,	0,	0,	0 }
};

class BfmeThingDCG;

class BfmeOtherDCG;

class BfmeThingDCG
{
public:
	void bfmeGoDCG(BfmeOtherDCG *other);
};

void BfmeThingDCG::bfmeGoDCG(BfmeOtherDCG *other)
{
	reinterpret_cast<INI *>(other)->initFromINI(this, bfmeInfoDCG);
}
