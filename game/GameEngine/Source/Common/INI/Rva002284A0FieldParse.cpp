// cl: /DNDEBUG /MD /EHsc
class INI;

typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parsePercentToReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseAudioEventRTS(INI *ini, void *instance, void *store, const void *userData);
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseAsciiStringVectorAppend(INI *ini, void *instance, void *store, const void *userData);
};

class TransportContain
{
public:
	static void parseBoneSpecificConditionState(INI *ini, void *instance, const void *userData);
};

void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);
void rva002274a0ParsePassengerBone(INI *ini, void *instance, void *store, const void *userData);
void parseObjectStatusOfContained(INI *ini, void *instance, void *store, const void *userData);

class MultiIniFieldParse
{
public:
	void add(const FieldParse *fields, unsigned int offset = 0);
};

class DieMuxData
{
public:
	static const FieldParse *getFieldParse();
};

// The containment field table is proven; this builder's original owner and spelling remain unknown.
class Rva002284A0FieldParseBuilder
{
public:
	static void build(MultiIniFieldParse &parse);
};

// Retail .rdata VA 0x010AC600: 24 entries plus the terminator (400 B).
extern const FieldParse g_rva002284A0FieldParse[] =
{
	{ "ContainMax", INI::parseInt, 0, 0x140 },
	{ "EnterSound", INI::parseAudioEventRTS, 0, 0x34 },
	{ "ExitSound", INI::parseAudioEventRTS, 0, 0xA4 },
	{ "DamagePercentToUnits", INI::parsePercentToReal, 0, 0x13C },
	{ "PassengerFilter", iniParseObjectFilter, 0, 0x114 },
	{ "ManualPickUpFilter", iniParseObjectFilter, 0, 0x118 },
	{ "PassengersTestCollisionHeight", INI::parseReal, 0, 0x138 },
	{ "PassengersInTurret", INI::parseBool, 0, 0x155 },
	{ "NumberOfExitPaths", INI::parseInt, 0, 0x144 },
	{ "DoorOpenTime", INI::parseDurationUnsignedInt, 0, 0x148 },
	{ "AllowOwnPlayerInsideOverride", INI::parseBool, 0, 0x14C },
	{ "AllowAlliesInside", INI::parseBool, 0, 0x14D },
	{ "AllowEnemiesInside", INI::parseBool, 0, 0x14E },
	{ "AllowNeutralInside", INI::parseBool, 0, 0x14F },
	{ "ShowPips", INI::parseBool, 0, 0x150 },
	{ "CollidePickup", INI::parseBool, 0, 0x151 },
	{ "PassengerBonePrefix", rva002274a0ParsePassengerBone, 0, 0x0 },
	{ "BoneSpecificConditionState", (INIFieldParseProc)TransportContain::parseBoneSpecificConditionState, 0, 0x0 },
	{ "EjectPassengersOnDeath", INI::parseBool, 0, 0x152 },
	{ "KillPassengersOnDeath", INI::parseBool, 0, 0x153 },
	{ "Enabled", INI::parseBool, 0, 0x154 },
	{ "ObjectStatusOfContained", parseObjectStatusOfContained, 0, 0x12C },
	{ "ModifierToGiveOnExit", INI::parseAsciiStringVectorAppend, 0, 0x158 },
	{ "ModifierRequiredTime", INI::parseDurationUnsignedInt, 0, 0x164 },
	{ 0, 0, 0, 0 }
};

void Rva002284A0FieldParseBuilder::build(MultiIniFieldParse &parse)
{
	parse.add(g_rva002284A0FieldParse);
	parse.add(DieMuxData::getFieldParse(), 8);
}
