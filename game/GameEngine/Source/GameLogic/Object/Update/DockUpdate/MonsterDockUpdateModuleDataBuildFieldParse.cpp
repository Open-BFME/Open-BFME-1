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

extern const FieldParse MonsterDockUpdateModuleDataFieldParse[];

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
