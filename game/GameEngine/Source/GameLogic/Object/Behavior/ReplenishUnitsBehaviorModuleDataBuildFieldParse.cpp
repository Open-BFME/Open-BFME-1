// cl: /DNDEBUG /MD /EHsc

// ReplenishUnitsBehaviorModuleData::buildFieldParse, retail 0x00204F30, 35 bytes.
//
// Its only reference is ILT 0x0002B1F7, which the module-data factory at
// 0x00117420 hands INI::initFromINIMultiProc after constructing a
// ReplenishUnitsBehaviorModuleData (0x00204ED0 through ILT 0x0003025B). See
// identity_evidence/00204f30-replenishunits-buildfieldparse.md.
//
// The body adds the table at 0x010A5D68 (the seven Replenish* keys) at offset 0,
// then the upgrade-mux table at 0x010898A0 at offset 8.

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
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
};

// ReplenishStatii's parser is the carved five-byte thunk at 0x00029B9A.
class Rva00029B9AThunk
{
public:
	static void parseFromINI(INI *ini, void *instance, void *store, const void *userData);
};

// Retail 0x010898A0: UpgradeMuxData's field-parse table, added at the mux's +8.
extern const FieldParse g_bfmeBaseTableABF[];

class ReplenishUnitsBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &p);
};

// ?buildFieldParse@ReplenishUnitsBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z
void ReplenishUnitsBehaviorModuleData::buildFieldParse(MultiIniFieldParse &p)
{
	static const FieldParse dataFieldParse[] =
	{
		{ "StartsActive", INI::parseBool, 0, 0x8C },
		{ "ReplenishDelay", INI::parseDurationUnsignedInt, 0, 0x88 },
		{ "ReplenishRadius", INI::parseReal, 0, 0x70 },
		{ "NoReplenishIfEnemyWithinRadius", INI::parseReal, 0, 0x74 },
		{ "ReplenishFXList", INI::parseFXList, 0, 0x78 },
		{ "ReplenishStatii", Rva00029B9AThunk::parseFromINI, 0, 0x7C },
		{ "ReplenishHordeMembersOnly", INI::parseBool, 0, 0x8D },
		{ 0, 0, 0, 0 }
	};

	p.add(dataFieldParse);
	p.add(g_bfmeBaseTableABF, 8);
}
