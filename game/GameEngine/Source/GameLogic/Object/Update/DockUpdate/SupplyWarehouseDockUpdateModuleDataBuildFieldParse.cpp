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

extern const FieldParse SupplyWarehouseDockUpdateModuleDataFieldParse[];

class SupplyWarehouseDockUpdateModuleData : public DockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void SupplyWarehouseDockUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	DockUpdateModuleData::buildFieldParse(parse);
	parse.add(SupplyWarehouseDockUpdateModuleDataFieldParse, 0);
}
