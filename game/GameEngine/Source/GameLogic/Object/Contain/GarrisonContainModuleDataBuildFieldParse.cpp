// cl: /DNDEBUG /MD /EHsc

// GarrisonContainModuleData::buildFieldParse, retail 0x00125440, 30 bytes.
//
// The GarrisonContain module data factory at 0x00125470 hands
// INI::initFromINIMultiProc this address, so this body is GarrisonContain's
// field parse builder. The table it registers names
// GarrisonContainModuleData::parseInitialRoster as one of its parsers, which
// says the same thing a second way.
//
// The body calls a base class builder through ILT 0x00019772 and then registers
// the table at 0x0108E660 at offset 0. targets/game/reverse/symbols.csv already carries the
// address-derived name ?buildFieldParse@Gen00019772@@SAXAAVWideMulti@@@Z for
// that thunk, so the base is called by that name rather than a guessed one.
//
// The receiver is spelled WideMulti and its rows WideFieldParse because that is
// how targets/game/reverse/symbols.csv spells the add at 0x00850920 this body calls.

class INI;

class WideFieldParse
{
public:
	const char *m_token;
	void (*m_parse)(INI *, void *, void *, const void *);
	const void *m_userData;
	unsigned int m_offset;
};

class WideMulti
{
public:
	void add(const WideFieldParse *fields, unsigned int extraOffset);
};

class INI
{
public:
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseDurationReal(INI *ini, void *instance, void *store, const void *userData);
};

// The base class this module data derives from. Its builder is reached through
// ILT 0x00019772 and its own name is not recovered.
class Gen00019772
{
public:
	static void buildFieldParse(WideMulti &p);
};

class GarrisonContainModuleData
{
public:
	static void buildFieldParse(WideMulti &p);
	static void parseInitialRoster(INI *ini, void *instance, void *store, const void *userData);
};

static const WideFieldParse s_garrisonContainFieldParse[] =
{
	{ "MobileGarrison",               INI::parseBool,                             0, 0x170 },
	{ "HealObjects",                  INI::parseBool,                             0, 0x168 },
	{ "TimeForFullHeal",              INI::parseDurationReal,                     0, 0x16C },
	{ "InitialRoster",                GarrisonContainModuleData::parseInitialRoster, 0, 0x000 },
	{ "ImmuneToClearBuildingAttacks", INI::parseBool,                             0, 0x171 },
	{ 0, 0, 0, 0 }
};

// ?buildFieldParse@GarrisonContainModuleData@@SAXAAVWideMulti@@@Z
void GarrisonContainModuleData::buildFieldParse(WideMulti &p)
{
	Gen00019772::buildFieldParse(p);
	p.add(s_garrisonContainFieldParse, 0);
}
