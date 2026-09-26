// cl: /DNDEBUG /MD /EHsc

// SpecialPowerModuleData::buildFieldParse, retail 0x002683D0, 745 bytes.
//
// Three module data factories name this body. The ones for SpecialPowerModule
// at 0x001195C0, ManTheWallsSpecialPower at 0x00121260 and SplitHordeSpecialPower
// at 0x001216A0 each push 0x002683D0 before they call INI::initFromINIMultiProc.
// The table it adds at 0x012B0A40 opens with SpecialPowerTemplate at member
// offset 8, UpdateModuleStartsAttack at 0xC and StartsPaused at 0xD.
//
// BFME grew the table past what the shipped image can hold as constants. Rows 0
// to 7 sit in .data whole. Row 8 keeps its token and its parser there and takes
// its name list and its member offset at run time. Rows 9 to 29 are written
// whole at run time, once, under bit 0 of the guard word at 0x012EFD4C.
//
// The name list row 8 hands INI::parseIndexList is the seven-name NONE..LEVEL
// list at 0x012A68B0 that game/GameEngine/Source/Common/BitFlagsParseToken.cpp
// already reads out of the image. It keeps an address-derived name here because
// no evidence spells the real one.
//
// Member offsets stay as numbers. The class layout runs past 0x20D and no
// witness names the fields that far out.

typedef unsigned int UnsignedInt;

class INI;

typedef void (*INIFieldParseProc)( INI *ini, void *instance, void *store, const void *userData );

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class MultiIniFieldParse
{
public:
	void add( const FieldParse *table, UnsignedInt offset );
};

class INI
{
public:
	static void parseSpecialPowerTemplate( INI *ini, void *instance, void *store, const void *userData );
	static void parseAudioEventRTS( INI *ini, void *instance, void *store, const void *userData );
	static void parseIndexList( INI *ini, void *instance, void *store, const void *userData );
	static void parseFXList( INI *ini, void *instance, void *store, const void *userData );
	static void parseAsciiString( INI *ini, void *instance, void *store, const void *userData );
	static void parseReal( INI *ini, void *instance, void *store, const void *userData );
	static void parseInt( INI *ini, void *instance, void *store, const void *userData );
	static void parseBool( INI *ini, void *instance, void *store, const void *userData );
};

void iniParseObjectFilter( INI *ini, void *instance, void *store, const void *userData );

// 0x00268340, the parser the SetModelCondition row points at, reached through
// the incremental-link thunk at 0x0000AC09.
class Rva00268340Contain
{
public:
	static void iniParseAnim( INI *ini, void *instance, void *store, const void *userData );
};

extern const char *const g_bfmeNames012A68B0[];		// 0x012A68B0, NONE..LEVEL

class SpecialPowerModuleData
{
public:
	static void buildFieldParse( MultiIniFieldParse &p );
};

static unsigned int s_onceSpecialPower;

static FieldParse s_specialPowerFieldParse[30] =
{
	{ "SpecialPowerTemplate",		INI::parseSpecialPowerTemplate,	0, 0x008 },
	{ "UpdateModuleStartsAttack",	INI::parseBool,					0, 0x00C },
	{ "StartsPaused",				INI::parseBool,					0, 0x00D },
	{ "InitiateSound",				INI::parseAudioEventRTS,		0, 0x010 },
	{ "InitiateSoundGroup",			INI::parseAudioEventRTS,		0, 0x080 },
	{ "InitiateSound2",				INI::parseAudioEventRTS,		0, 0x0F0 },
	{ "InitiateSoundGroup2",		INI::parseAudioEventRTS,		0, 0x160 },
	{ "ReEnableAntiCategory",		INI::parseBool,					0, 0x1EE },
	{ "AntiCategory",				INI::parseIndexList,			0, 0 },
};

// ?buildFieldParse@SpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
/*static*/ void SpecialPowerModuleData::buildFieldParse( MultiIniFieldParse &p )
{
	if ((s_onceSpecialPower & 1) == 0)
	{
		s_onceSpecialPower |= 1;

		s_specialPowerFieldParse[8].userData = g_bfmeNames012A68B0;
		s_specialPowerFieldParse[8].offset = 0x1E8;

		s_specialPowerFieldParse[9].token = "AntiFX";
		s_specialPowerFieldParse[9].parse = INI::parseFXList;
		s_specialPowerFieldParse[9].userData = 0;
		s_specialPowerFieldParse[9].offset = 0x1F8;

		s_specialPowerFieldParse[10].token = "AttributeModifier";
		s_specialPowerFieldParse[10].parse = INI::parseAsciiString;
		s_specialPowerFieldParse[10].userData = 0;
		s_specialPowerFieldParse[10].offset = 0x1D0;

		s_specialPowerFieldParse[11].token = "AttributeModifierRange";
		s_specialPowerFieldParse[11].parse = INI::parseReal;
		s_specialPowerFieldParse[11].userData = 0;
		s_specialPowerFieldParse[11].offset = 0x1D4;

		s_specialPowerFieldParse[12].token = "AttributeModifierAffectsSelf";
		s_specialPowerFieldParse[12].parse = INI::parseBool;
		s_specialPowerFieldParse[12].userData = 0;
		s_specialPowerFieldParse[12].offset = 0x1D8;

		s_specialPowerFieldParse[13].token = "AttributeModifierAffects";
		s_specialPowerFieldParse[13].parse = iniParseObjectFilter;
		s_specialPowerFieldParse[13].userData = 0;
		s_specialPowerFieldParse[13].offset = 0x1DC;

		s_specialPowerFieldParse[14].token = "AttributeModifierFX";
		s_specialPowerFieldParse[14].parse = INI::parseFXList;
		s_specialPowerFieldParse[14].userData = 0;
		s_specialPowerFieldParse[14].offset = 0x1E0;

		s_specialPowerFieldParse[15].token = "AttributeModifierWeatherBased";
		s_specialPowerFieldParse[15].parse = INI::parseBool;
		s_specialPowerFieldParse[15].userData = 0;
		s_specialPowerFieldParse[15].offset = 0x1E4;

		s_specialPowerFieldParse[16].token = "TargetEnemy";
		s_specialPowerFieldParse[16].parse = INI::parseBool;
		s_specialPowerFieldParse[16].userData = 0;
		s_specialPowerFieldParse[16].offset = 0x1EC;

		s_specialPowerFieldParse[17].token = "TargetAllSides";
		s_specialPowerFieldParse[17].parse = INI::parseBool;
		s_specialPowerFieldParse[17].userData = 0;
		s_specialPowerFieldParse[17].offset = 0x1ED;

		s_specialPowerFieldParse[18].token = "InitiateFX";
		s_specialPowerFieldParse[18].parse = INI::parseFXList;
		s_specialPowerFieldParse[18].userData = 0;
		s_specialPowerFieldParse[18].offset = 0x1F0;

		s_specialPowerFieldParse[19].token = "TriggerFX";
		s_specialPowerFieldParse[19].parse = INI::parseFXList;
		s_specialPowerFieldParse[19].userData = 0;
		s_specialPowerFieldParse[19].offset = 0x1F4;

		s_specialPowerFieldParse[20].token = "SetModelCondition";
		s_specialPowerFieldParse[20].parse = Rva00268340Contain::iniParseAnim;
		s_specialPowerFieldParse[20].userData = 0;
		s_specialPowerFieldParse[20].offset = 0x1FC;

		s_specialPowerFieldParse[21].token = "SetModelConditionTime";
		s_specialPowerFieldParse[21].parse = INI::parseReal;
		s_specialPowerFieldParse[21].userData = 0;
		s_specialPowerFieldParse[21].offset = 0x200;

		s_specialPowerFieldParse[22].token = "GiveLevels";
		s_specialPowerFieldParse[22].parse = INI::parseInt;
		s_specialPowerFieldParse[22].userData = 0;
		s_specialPowerFieldParse[22].offset = 0x204;

		s_specialPowerFieldParse[23].token = "DisableDuringAnimDuration";
		s_specialPowerFieldParse[23].parse = INI::parseBool;
		s_specialPowerFieldParse[23].userData = 0;
		s_specialPowerFieldParse[23].offset = 0x208;

		s_specialPowerFieldParse[24].token = "IdleWhenStartingPower";
		s_specialPowerFieldParse[24].parse = INI::parseBool;
		s_specialPowerFieldParse[24].userData = 0;
		s_specialPowerFieldParse[24].offset = 0x209;

		s_specialPowerFieldParse[25].token = "AffectGood";
		s_specialPowerFieldParse[25].parse = INI::parseBool;
		s_specialPowerFieldParse[25].userData = 0;
		s_specialPowerFieldParse[25].offset = 0x20A;

		s_specialPowerFieldParse[26].token = "AffectEvil";
		s_specialPowerFieldParse[26].parse = INI::parseBool;
		s_specialPowerFieldParse[26].userData = 0;
		s_specialPowerFieldParse[26].offset = 0x20B;

		s_specialPowerFieldParse[27].token = "AffectAllies";
		s_specialPowerFieldParse[27].parse = INI::parseBool;
		s_specialPowerFieldParse[27].userData = 0;
		s_specialPowerFieldParse[27].offset = 0x20C;

		s_specialPowerFieldParse[28].token = "AvailableAtStart";
		s_specialPowerFieldParse[28].parse = INI::parseBool;
		s_specialPowerFieldParse[28].userData = 0;
		s_specialPowerFieldParse[28].offset = 0x20D;

		s_specialPowerFieldParse[29].token = 0;
		s_specialPowerFieldParse[29].parse = 0;
		s_specialPowerFieldParse[29].userData = 0;
		s_specialPowerFieldParse[29].offset = 0;
	}

	p.add( s_specialPowerFieldParse, 0 );
}
