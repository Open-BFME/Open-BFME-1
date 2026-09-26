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

// The containment field table is proven; this builder's original owner and spelling remain unknown.
class Rva002284A0FieldParseBuilder
{
public:
	static void build(MultiIniFieldParse &parse);
};

extern const FieldParse g_rva002284A0FieldParse[];

void Rva002284A0FieldParseBuilder::build(MultiIniFieldParse &parse)
{
	parse.add(g_rva002284A0FieldParse);
	parse.add(DieMuxData::getFieldParse(), 8);
}
