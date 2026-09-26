struct FieldParse
{
	const char *m_token;
	void (*m_parse)();
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

extern const FieldParse SupplyCenterDockUpdateModuleDataFieldParse[];

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
