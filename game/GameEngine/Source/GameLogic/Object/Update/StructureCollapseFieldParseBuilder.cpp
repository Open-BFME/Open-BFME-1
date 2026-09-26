// cl: /DNDEBUG /MD /EHsc
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *fields, unsigned int offset = 0);
};

class DieMuxData
{
public:
	static const FieldParse *getFieldParse();
};

// Registration and field keys establish the StructureCollapse role; the original class spelling is unknown.
class Rva002AEDF0ModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

extern const FieldParse g_structureCollapseFieldParse[];

void Rva002AEDF0ModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_structureCollapseFieldParse);
	parse.add(DieMuxData::getFieldParse(), 8);
}
