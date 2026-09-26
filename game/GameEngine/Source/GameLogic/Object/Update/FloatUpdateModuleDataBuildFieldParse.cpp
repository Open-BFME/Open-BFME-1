// cl: /DNDEBUG /MD /EHsc

// FloatUpdateModuleData::buildFieldParse, retail 0x00294F70, 17 bytes.
//
// The FloatUpdate module data factory at 0x00118580 hands
// INI::initFromINIMultiProc this address, so this body is FloatUpdate's field
// parse builder. FloatUpdateModuleData's constructor sits directly before it at
// 0x00294F60 and is already matched, which puts both in the same class.
//
// The body pushes one table and the offset 0 and calls
// MultiIniFieldParse::add. The table at 0x010BF35C holds one row, "Enabled"
// parsed by INI::parseBool into the member at +0x08, then a null row.
//
// The receiver is spelled WideMulti and its rows WideFieldParse because that is
// how targets/game/reverse/symbols.csv spells the add at 0x00850920 this body calls. The
// table is written out here rather than declared external, the way
// Rva0022A450Parse.cpp writes its own, because the operand is a relocation and
// the byte check masks it.

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
};

class FloatUpdateModuleData
{
public:
	static void buildFieldParse(WideMulti &p);
};

static const WideFieldParse s_floatUpdateFieldParse[] =
{
	{ "Enabled", INI::parseBool, 0, 0x08 },
	{ 0, 0, 0, 0 }
};

// ?buildFieldParse@FloatUpdateModuleData@@SAXAAVWideMulti@@@Z
void FloatUpdateModuleData::buildFieldParse(WideMulti &p)
{
	p.add(s_floatUpdateFieldParse, 0);
}
