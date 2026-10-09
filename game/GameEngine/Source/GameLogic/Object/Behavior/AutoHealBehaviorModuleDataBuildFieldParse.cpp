// cl: /DNDEBUG /MD /EHsc

// AutoHealBehaviorModuleData::buildFieldParse, retail 0x001298A0, 35 bytes.
//
// Its only reference is ILT 0x0003AF21, which the matched
// AutoHealBehavior::friend_newModuleData (0x00129E40) hands
// INI::initFromINIMultiProc after constructing an AutoHealBehaviorModuleData
// (0x00129D50 through ILT 0x0001528A). See
// identity_evidence/001298a0-autoheal-buildfieldparse.md.
//
// The body adds the table at 0x0108EE60 (the thirteen AutoHeal keys) at offset
// 0, then the upgrade-mux table at 0x010898A0 at offset 8.

class INI;

typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class MultiIniFieldParse
{
public:
	void add(const FieldParse *fields, unsigned int extraOffset = 0);
};

class INI
{
public:
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
};

// KindOf parses through the five-byte tail thunk 0x0002032E into
// BitFlags<116>::parseFromINI; the thunk has no signature of its own.
void Rva0002032EBitFlagsParseThunk();

// Retail 0x010898A0: UpgradeMuxData's field-parse table, added at the mux's +8.
extern const FieldParse g_bfmeBaseTableABF[];

class AutoHealBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &p);
};

// ?buildFieldParse@AutoHealBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z
void AutoHealBehaviorModuleData::buildFieldParse(MultiIniFieldParse &p)
{
	static const FieldParse dataFieldParse[] =
	{
		{ "StartsActive", INI::parseBool, 0, 0x70 },
		{ "ButtonTriggered", INI::parseBool, 0, 0x71 },
		{ "SingleBurst", INI::parseBool, 0, 0x72 },
		{ "HealingAmount", INI::parseInt, 0, 0x74 },
		{ "HealingDelay", INI::parseDurationUnsignedInt, 0, 0x78 },
		{ "Radius", INI::parseInt, 0, 0x80 },
		{ "KindOf", (INIFieldParseProc)Rva0002032EBitFlagsParseThunk, 0, 0x88 },
		{ "UnitHealPulseFX", INI::parseFXList, 0, 0xA4 },
		{ "StartHealingDelay", INI::parseDurationUnsignedInt, 0, 0x7C },
		{ "AffectsWholePlayer", INI::parseBool, 0, 0x84 },
		{ "HealOnlyIfNotUnderAttack", INI::parseBool, 0, 0x85 },
		{ "HealOnlyIfNotInCombat", INI::parseBool, 0, 0x86 },
		{ "HealOnlyOthers", INI::parseBool, 0, 0xA0 },
		{ 0, 0, 0, 0 }
	};

	p.add(dataFieldParse);
	p.add(g_bfmeBaseTableABF, 8);
}
