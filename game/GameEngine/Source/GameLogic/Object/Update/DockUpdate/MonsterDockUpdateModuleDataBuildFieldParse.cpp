class INI;

typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

struct FieldParse
{
	const char *m_token;
	INIFieldParseProc m_parse;
	const void *m_userData;
	unsigned int m_offset;
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *fields, unsigned int extraOffset);
};

class DockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class INI
{
public:
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
};

void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);

// Retail .rdata VA 0x010CA9B0: two entries plus the terminator (48 B).
extern const FieldParse MonsterDockUpdateModuleDataFieldParse[] =
{
	{ "DockableObjectFilter", iniParseObjectFilter, 0, 0x10 },
	{ "DockedAnimationTime", INI::parseDurationUnsignedInt, 0, 0x14 },
	{ 0, 0, 0, 0 }
};

class MonsterDockUpdateModuleData : public DockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void MonsterDockUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	DockUpdateModuleData::buildFieldParse(parse);
	parse.add(MonsterDockUpdateModuleDataFieldParse, 0);
}
