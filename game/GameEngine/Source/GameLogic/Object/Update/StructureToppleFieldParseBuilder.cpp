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

// Registration and field keys establish the StructureTopple role; the original class spelling is unknown.
class Rva002B0A40ModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

extern const FieldParse g_structureToppleFieldParse[];

void Rva002B0A40ModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_structureToppleFieldParse);
	parse.add(DieMuxData::getFieldParse(), 8);
}
