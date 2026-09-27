// Retail 0x00248F00 is the field-parse builder that the module-data factory
// 0x00116140 hands to initFromINIMultiProc, and ModuleFactory::init registers
// that factory under "HordeGarrisonContain". It extends OpenContain's builder
// (ILT 0x00019772) with two tables. The module-data class name is not in the
// image, so the owner stays address-derived; the vocabulary is
// WideBuildFieldParse.cpp's.

class WideFieldParse
{
public:
	const char *m_token;
	void (*m_parse)();
	const void *m_userData;
	unsigned int m_offset;
};

class WideMulti
{
public:
	void add( const WideFieldParse *fields, unsigned int extraOffset );
};

class Gen00019772
{
public:
	static void buildFieldParse( WideMulti &p );
};

extern const WideFieldParse WideTbl00248F00A[];
extern const WideFieldParse WideTbl00248F00B[];

class Rva00248F00
{
public:
	static void buildFieldParse( WideMulti &p );
};

void Rva00248F00::buildFieldParse( WideMulti &p )
{
	Gen00019772::buildFieldParse( p );
	p.add( WideTbl00248F00A, 0 );
	p.add( WideTbl00248F00B, 0 );
}
