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
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseScience(INI *ini, void *instance, void *store, const void *userData);
	static void parsePercentToReal(INI *ini, void *instance, void *store, const void *userData);
};

// Retail .rdata VA 0x010CB060: 3 entries plus the terminator (64 B).
extern const FieldParse SupplyCenterDockUpdateModuleDataFieldParse[] =
{
	{ "ValueMultiplier", INI::parseReal, 0, 0x10 },
	{ "BonusScience", INI::parseScience, 0, 0x14 },
	{ "BonusScienceMultiplier", INI::parsePercentToReal, 0, 0x18 },
	{ 0, 0, 0, 0 }
};

class SupplyCenterDockUpdateModuleData : public DockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void SupplyCenterDockUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	DockUpdateModuleData::buildFieldParse(parse);
	parse.add(SupplyCenterDockUpdateModuleDataFieldParse, 0);
}
