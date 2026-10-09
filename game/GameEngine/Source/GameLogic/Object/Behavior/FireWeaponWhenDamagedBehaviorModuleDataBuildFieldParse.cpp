// cl: /DNDEBUG /MD /EHsc

// FireWeaponWhenDamagedBehaviorModuleData::buildFieldParse, retail 0x00123180,
// 35 bytes.
//
// Its only reference is ILT 0x0002969A, which the module-data factory at
// 0x0012A170 hands INI::initFromINIMultiProc after constructing a
// FireWeaponWhenDamagedBehaviorModuleData (0x0012A100 through ILT 0x00012233).
// See identity_evidence/00123180-fireweaponwhendamaged-buildfieldparse.md.
//
// The body adds the table at 0x0108B330 at offset 0, then the upgrade-mux
// table at 0x010898A0 at offset 8. The keys are Zero Hour's
// FireWeaponWhenDamagedBehavior set at BFME offsets.

class INI;

struct FieldParse
{
	const char *token;
	void (*parse)(INI *ini, void *instance, void *store, const void *userData);
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
	static void parseWeaponTemplate(INI *ini, void *instance, void *store, const void *userData);
	static void parseDamageTypeFlags(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
};

// Retail 0x010898A0: UpgradeMuxData's field-parse table, added at the mux's +8.
extern const FieldParse g_bfmeBaseTableABF[];

class FireWeaponWhenDamagedBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &p);
};

// ?buildFieldParse@FireWeaponWhenDamagedBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z
void FireWeaponWhenDamagedBehaviorModuleData::buildFieldParse(MultiIniFieldParse &p)
{
	static const FieldParse dataFieldParse[] =
	{
		{ "StartsActive", INI::parseBool, 0, 0x70 },
		{ "ReactionWeaponPristine", INI::parseWeaponTemplate, 0, 0x7C },
		{ "ReactionWeaponDamaged", INI::parseWeaponTemplate, 0, 0x80 },
		{ "ReactionWeaponReallyDamaged", INI::parseWeaponTemplate, 0, 0x84 },
		{ "ReactionWeaponRubble", INI::parseWeaponTemplate, 0, 0x88 },
		{ "ContinuousWeaponPristine", INI::parseWeaponTemplate, 0, 0x8C },
		{ "ContinuousWeaponDamaged", INI::parseWeaponTemplate, 0, 0x90 },
		{ "ContinuousWeaponReallyDamaged", INI::parseWeaponTemplate, 0, 0x94 },
		{ "ContinuousWeaponRubble", INI::parseWeaponTemplate, 0, 0x98 },
		{ "DamageTypes", INI::parseDamageTypeFlags, 0, 0x74 },
		{ "DamageAmount", INI::parseReal, 0, 0x78 },
		{ 0, 0, 0, 0 }
	};

	p.add(dataFieldParse);
	p.add(g_bfmeBaseTableABF, 8);
}
