// cl: /O2 /GR- /EHsc- /DNDEBUG /DWIN32 /D_WINDOWS /MD /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// BfmeOtherDCE only ever receives the INI* receiver of INI::initFromINI, so the
// call below goes through the real header rather than a stand-in member whose
// name nothing defines.
#include "PreRTS.h"
#include "Common/INI.h"

// Retail .rdata 0x010EA6A8, 464 bytes: the 28-entry field-parse table that
// bfmeGoDCE hands to INI::initFromINI, plus the zero terminator. Tokens,
// parsers and offsets are read from the image; parsers retail reaches through
// incremental-link thunks are named by those thunks. The owning record is not
// recovered, so the table keeps the alias this caller already spells.
void j_000019ec();
void j_00004b47();
void j_000220d9();
void j_00022be7();
void j_00025a90();
void j_000324de();
void j_0003908b();
void j_0003a7a6();
void j_0004a33b();
extern "C" const FieldParse bfmeInfoDCE[] =
{
	{ "CopyFrom",	(INIFieldParseProc)j_00025a90,	0,	0x0 },
	{ "Type",	(INIFieldParseProc)j_000019ec,	0,	0x4 },
	{ "IgnoreIfUnitIdle",	INI::parseBool,	0,	0x8 },
	{ "IgnoreIfUnitBusy",	INI::parseBool,	0,	0x9 },
	{ "Duration",	(INIFieldParseProc)j_000324de,	0,	0xC },
	{ "InactiveDuration",	(INIFieldParseProc)j_000324de,	0,	0x10 },
	{ "InactiveDurationSameObject",	(INIFieldParseProc)j_000324de,	0,	0x14 },
	{ "InactiveDurationSameType",	(INIFieldParseProc)j_000324de,	0,	0x18 },
	{ "OnlyIfEnemyThreatAbove",	(INIFieldParseProc)j_0004a33b,	0,	0x1C },
	{ "OnlyIfEnemyThreatBelow",	(INIFieldParseProc)j_0003a7a6,	0,	0x1C },
	{ "OnlyIfFriendThreatAbove",	(INIFieldParseProc)j_0004a33b,	0,	0x24 },
	{ "OnlyIfFriendThreatBelow",	(INIFieldParseProc)j_0003a7a6,	0,	0x24 },
	{ "IgnoreIfAI",	INI::parseBool,	0,	0x2C },
	{ "IgnoreIfHuman",	INI::parseBool,	0,	0x2D },
	{ "StartFXList",	(INIFieldParseProc)j_00004b47,	0,	0x30 },
	{ "UpdateFXList",	(INIFieldParseProc)j_00004b47,	0,	0x34 },
	{ "EndFXList",	(INIFieldParseProc)j_00004b47,	0,	0x38 },
	{ "AttributeModifier",	INI::parseAsciiString,	0,	0x3C },
	{ "AttributeStartDelay",	(INIFieldParseProc)j_000324de,	0,	0x40 },
	{ "AttributeModifierWhileEmotionActive",	INI::parseBool,	0,	0x44 },
	{ "AttributeDuration",	(INIFieldParseProc)j_000324de,	0,	0x48 },
	{ "AIState",	(INIFieldParseProc)j_000220d9,	0,	0x4C },
	{ "AILockDuration",	(INIFieldParseProc)j_000324de,	0,	0x50 },
	{ "ModelConditions",	(INIFieldParseProc)j_0003908b,	0,	0x54 },
	{ "ModelConditionsClear",	(INIFieldParseProc)j_0003908b,	0,	0xA4 },
	{ "ModelConditionsSetOnExit",	(INIFieldParseProc)j_00022be7,	0,	0xCC },
	{ "ModelConditionsClearOnExit",	(INIFieldParseProc)j_00022be7,	0,	0x7C },
	{ "LuaEvent",	INI::parseAsciiString,	0,	0xF4 },
	{ 0,	0,	0,	0 }
};

class BfmeThingDCE;

class BfmeOtherDCE;

class BfmeThingDCE
{
public:
	void bfmeGoDCE(BfmeOtherDCE *other);
};

void BfmeThingDCE::bfmeGoDCE(BfmeOtherDCE *other)
{
	reinterpret_cast<INI *>(other)->initFromINI(this, bfmeInfoDCE);
}
