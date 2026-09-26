// cl: /DNDEBUG /MD /EHsc

// HeroDieModuleData::buildFieldParse, retail 0x00124920, 36 bytes.
//
// The HeroDie module data factory at 0x00124950 hands
// INI::initFromINIMultiProc this address, so this body is HeroDie's field parse
// builder.
//
// The body registers two tables. The first is DieMuxData::getFieldParse() at
// offset 8, which is the die-mux block every die module shares. The second is
// the table at 0x0108E504 at offset 0, one row that parses SpecialPowerTemplate
// into the member at +0x34.
//
// MSVC pushes the offset 8 before it calls getFieldParse, which is why the
// constant sits above the call in retail rather than beside the table pointer.
//
// The receiver is spelled WideMulti and its rows WideFieldParse because that is
// how targets/game/reverse/symbols.csv spells the add at 0x00850920 this body calls. The
// die-mux getter keeps the FieldParse spelling its own ledger row uses.

class INI;
struct FieldParse;

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
	static void parseSpecialPowerTemplate(INI *ini, void *instance, void *store, const void *userData);
};

class DieMuxData
{
public:
	static const FieldParse *getFieldParse();
};

class HeroDieModuleData
{
public:
	static void buildFieldParse(WideMulti &p);
};

static const WideFieldParse s_heroDieFieldParse[] =
{
	{ "SpecialPowerTemplate", INI::parseSpecialPowerTemplate, 0, 0x034 },
	{ 0, 0, 0, 0 }
};

// ?buildFieldParse@HeroDieModuleData@@SAXAAVWideMulti@@@Z
void HeroDieModuleData::buildFieldParse(WideMulti &p)
{
	p.add((const WideFieldParse *)DieMuxData::getFieldParse(), 8);
	p.add(s_heroDieFieldParse, 0);
}
