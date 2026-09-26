// cl: /DNDEBUG /MD /EHsc

// DevastateSpecialPowerModuleData::buildFieldParse, retail 0x0025A790, 30 bytes.
//
// The DevastateSpecialPower module data factory at 0x00121590 hands
// INI::initFromINIMultiProc this address, so this body is that module's field
// parse builder. The factory allocates 0x220 bytes and the table below reaches
// +0x21C, which agrees.
//
// The body calls a base class builder through ILT 0x0002AF8B and then registers
// the table at 0x010B45A8 at offset 0. targets/game/reverse/symbols.csv already carries the
// address-derived name ?buildFieldParse@Gen0002AF8B@@SAXAAVWideMulti@@@Z for
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
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
	static void parsePercentToReal(INI *ini, void *instance, void *store, const void *userData);
};

// The base class this module data derives from. Its builder is reached through
// ILT 0x0002AF8B and its own name is not recovered.
class Gen0002AF8B
{
public:
	static void buildFieldParse(WideMulti &p);
};

class DevastateSpecialPowerModuleData
{
public:
	static void buildFieldParse(WideMulti &p);
};

static const WideFieldParse s_devastateFieldParse[] =
{
	{ "Radius",              INI::parseReal,          0, 0x210 },
	{ "FX",                  INI::parseFXList,        0, 0x214 },
	{ "TreeValueMultiplier", INI::parsePercentToReal, 0, 0x218 },
	{ "TreeValueTotalCap",   INI::parseReal,          0, 0x21C },
	{ 0, 0, 0, 0 }
};

// ?buildFieldParse@DevastateSpecialPowerModuleData@@SAXAAVWideMulti@@@Z
void DevastateSpecialPowerModuleData::buildFieldParse(WideMulti &p)
{
	Gen0002AF8B::buildFieldParse(p);
	p.add(s_devastateFieldParse, 0);
}
