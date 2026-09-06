// ??0BfmeParserRegDefaultVE_450460@@QAE@PAX00@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// partial-turned-attempt: retrying the ehThisSpillTemp blocker recorded for
// this family (see reverse/attempts/0x00088e20.cpp, 0x00088f50.cpp) with a
// flat (no base class) layout: retail constructs the temp AsciiString,
// stores vtable/table/parser, calls registerParser, and only THEN
// explicitly calls the temp's destructor (releaseBuffer) -- i.e. the temp
// is a real local in a nested block in the constructor BODY, not a
// mem-initializer argument to a base-class constructor. IDENTITY IS NOT
// RECOVERED: class name is address-derived.

class UserParser;
class DataChunkInput;
typedef bool (*BfmeParserCallback)(DataChunkInput &, void *, void *);

class DataChunkInput
{
public:
	UserParser *registerParser(void *name, void *label, BfmeParserCallback callback, void *userData);
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *s);
	~BFMERetailAsciiString();
private:
	void *m_data;
};

class BfmeParserRegDefaultVE_450460
{
public:
	BfmeParserRegDefaultVE_450460(void *a, void *b, void *c);
private:
	void *m_vftable;
	DataChunkInput *m_table;
	UserParser *m_parser;
	void *m_third;
};

// ?d_00450460@@YAXXZ
BfmeParserRegDefaultVE_450460::BfmeParserRegDefaultVE_450460(void *a, void *b, void *c)
{
	void *label = c ? c : (void *)0x01336E50;
	{
		BFMERetailAsciiString name((const char *)0x010F5E30);
		m_vftable = (void *)0x0107C7D0;
		m_table = (DataChunkInput *)b;
		m_parser = m_table->registerParser(&name, label,
			(BfmeParserCallback)0x0041579E, this);
	}
	m_third = a;
	m_vftable = (void *)0x010F5E84;
}
