// cl: /DNDEBUG /MD /EHsc
// BFME2 GenericObjectCreationNugget::parseObject reconstruction.
//
// parseObject feeds MultiIniFieldParse::add two TU-local const tables: the common
// field table at retail .rdata VA 0x0109F320 (496 bytes: 30 fields plus the zero
// terminator) and the object field table at VA 0x0109F8A8 (256 bytes: 15 fields
// plus the terminator). Tokens, parsers, user data and offsets are read from the
// retail image; parsers retail reaches through incremental-link thunks are named
// by those thunks. The Disposition row's user data is the fifteen-name
// DebrisDisposition list retail keeps at .data VA 0x012AD164.

class INI;

typedef void (*INIFieldParseProc)(INI *, void *, void *, const void *);

#include "../../../Include/Common/FieldParse.h"

class MultiIniFieldParse
{
public:
	MultiIniFieldParse()
	{
		m_count = 0;
		for (int i = 0; i < 16; ++i)
		{
			m_extraOffset[i] = 0;
			m_fieldParse[i] = 0;
		}
	}

	void add(const FieldParse *, unsigned int = 0);

private:
	const FieldParse *m_fieldParse[16];
	unsigned int m_extraOffset[16];
	int m_count;
};

class INI
{
public:
	void initFromINIMulti(void *, const MultiIniFieldParse &);

	static void parseAsciiString(INI *, void *, void *, const void *);
	static void parseAsciiStringVector(INI *, void *, void *, const void *);
	static void parseInt(INI *, void *, void *, const void *);
	static void parseReal(INI *, void *, void *, const void *);
	static void parseBool(INI *, void *, void *, const void *);
	static void parseAngleReal(INI *, void *, void *, const void *);
	static void parseCoord3D(INI *, void *, void *, const void *);
	static void parseBitString32(INI *, void *, void *, const void *);
	static void parsePercentToReal(INI *, void *, void *, const void *);
};

class ObjectCreationNugget
{
};

class GenericObjectCreationNugget : public ObjectCreationNugget
{
public:
	GenericObjectCreationNugget();

	static void parseObject(INI *, void *, void *, const void *);

	char m_beforeNameAreObjects[0x114];
	bool m_nameAreObjects;
	char m_retailTail[0x33];
};

class ObjectCreationList
{
public:
	void addObjectCreationNugget(ObjectCreationNugget *);
};

// Retail .data VA 0x012AD164: the fifteen DebrisDisposition names that
// INI::parseBitString32 matches "Disposition" tokens against. Retail carries no
// NULL terminator here (the mutable 0.2f global parseExtraFriction scales by sits
// at 0x012AD1A0), and the upstream Zero Hour source spells the array the same way.
static const char *s_debrisDispositionNames[] =
{
	"LIKE_EXISTING",
	"ON_GROUND_ALIGNED",
	"SEND_IT_FLYING",
	"SEND_IT_UP",
	"SEND_IT_OUT",
	"RANDOM_FORCE",
	"FLOATING",
	"INHERIT_VELOCITY",
	"FORWARD_IMPACT",
	"REVERSE_IMPACT",
	"BUILDING_CHUNKS",
	"FADE_AND_DIE_ORNAMENT",
	"ANIMATED",
	"SET_ANGLE",
	"SPAWN_AROUND"
};

// ExtraFriction is the one non-INI parser in either table; the remaining three are
// incremental-link thunks retail's table entries point at.
void parseExtraFriction(INI *, void *, void *, const void *);
void j_00038708();
void j_000324de();
void j_00022be7();

static const FieldParse s_commonFieldParse[] =
{
	{ "PutInContainer", INI::parseAsciiString, 0, 0x10 },
	{ "ParticleSystem", INI::parseAsciiString, 0, 0x24 },
	{ "Count", INI::parseInt, 0, 0x28 },
	{ "OrientInForceDirection", INI::parseBool, 0, 0x116 },
	{ "ExtraBounciness", INI::parseReal, 0, 0x2C },
	{ "ExtraFriction", parseExtraFriction, 0, 0x30 },
	{ "Offset", INI::parseCoord3D, 0, 0x34 },
	{ "Disposition", INI::parseBitString32, s_debrisDispositionNames, 0x40 },
	{ "DispositionIntensity", (INIFieldParseProc)j_00038708, 0, 0x44 },
	{ "DispositionAngle", INI::parseAngleReal, 0, 0x48 },
	{ "VelocityScale", INI::parseReal, 0, 0x4C },
	{ "MinForceMagnitude", INI::parseReal, 0, 0x50 },
	{ "MaxForceMagnitude", INI::parseReal, 0, 0x54 },
	{ "MinForcePitch", INI::parseAngleReal, 0, 0x58 },
	{ "MaxForcePitch", INI::parseAngleReal, 0, 0x5C },
	{ "MinLifetime", (INIFieldParseProc)j_000324de, 0, 0x60 },
	{ "MaxLifetime", (INIFieldParseProc)j_000324de, 0, 0x64 },
	{ "SpreadFormation", INI::parseBool, 0, 0x117 },
	{ "MinDistanceAFormation", INI::parseReal, 0, 0x84 },
	{ "MinDistanceBFormation", INI::parseReal, 0, 0x88 },
	{ "MaxDistanceFormation", INI::parseReal, 0, 0x8C },
	{ "FadeIn", INI::parseBool, 0, 0x118 },
	{ "FadeOut", INI::parseBool, 0, 0x119 },
	{ "FadeTime", (INIFieldParseProc)j_000324de, 0, 0x7C },
	{ "FadeSound", INI::parseAsciiString, 0, 0x80 },
	{ "PreserveLayer", INI::parseBool, 0, 0x10A },
	{ "IgnoreAllObjects", INI::parseBool, 0, 0x10B },
	{ "IgnoreEnemyUnits", INI::parseBool, 0, 0x10D },
	{ "IgnoreAllyUnits", INI::parseBool, 0, 0x10C },
	{ "StartingConditions", (INIFieldParseProc)j_00022be7, 0, 0x120 },
	{ 0, 0, 0, 0 }
};

static const FieldParse s_objectFieldParse[] =
{
	{ "ContainInsideSourceObject", INI::parseBool, 0, 0x109 },
	{ "ObjectNames", INI::parseAsciiStringVector, 0, 0x4 },
	{ "ObjectCount", INI::parseInt, 0, 0x90 },
	{ "InheritsVeterancy", INI::parseBool, 0, 0x11A },
	{ "VeterancyLevel", INI::parseInt, 0, 0x11C },
	{ "SkipIfSignificantlyAirborne", INI::parseBool, 0, 0x11B },
	{ "InvulnerableTime", (INIFieldParseProc)j_000324de, 0, 0x70 },
	{ "StartingBusyTime", (INIFieldParseProc)j_000324de, 0, 0x110 },
	{ "MinHealth", INI::parsePercentToReal, 0, 0x74 },
	{ "MaxHealth", INI::parsePercentToReal, 0, 0x78 },
	{ "RequiresLivePlayer", INI::parseBool, 0, 0x104 },
	{ "IgnoreCommandPointLimit", INI::parseBool, 0, 0x105 },
	{ "InheritAttributesFromSource", INI::parseBool, 0, 0x106 },
	{ "UseJustBuiltFlag", INI::parseBool, 0, 0x108 },
	{ "InheritScriptingName", INI::parseBool, 0, 0x107 },
	{ 0, 0, 0, 0 }
};

void GenericObjectCreationNugget::parseObject(INI *ini, void *instance,
	void *, const void *)
{
	MultiIniFieldParse fields;
	fields.add(s_commonFieldParse);
	fields.add(s_objectFieldParse);

	GenericObjectCreationNugget *nugget = new GenericObjectCreationNugget;
	nugget->m_nameAreObjects = true;

	ini->initFromINIMulti(nugget, fields);
	((ObjectCreationList *)instance)->addObjectCreationNugget(nugget);
}
