// ??0BfmeParserRegDefaultVE_74A590@@QAE@PAX00@Z
// partial score=0.55 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// Fuzzy-twin of ?d_00088e20@@YAXXZ (BfmeParserRegDefaultVE family); see
// reverse/attempts/0x00088e20.cpp for the analysis and the blocker note
// (blocker=ehThisSpillTemp: retail emits a compiler-generated EH funclet
// this-pointer stack spill around the temp AsciiString construction that
// this reconstruction does not reproduce).
// IDENTITY IS NOT RECOVERED: class name is address-derived.

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

class BfmeParserRegistrationVE
{
public:
	BfmeParserRegistrationVE(DataChunkInput *table, void *name, void *label)
	{
		m_vftable = (void *)0x0107C7D0;
		m_table = table;
		m_parser = table->registerParser(name, label, (BfmeParserCallback)0x0041579E, this);
	}
protected:
	void *m_vftable;
	DataChunkInput *m_table;
	UserParser *m_parser;
};

class BfmeParserRegDefaultVE_74A590 : public BfmeParserRegistrationVE
{
public:
	BfmeParserRegDefaultVE_74A590(void *a, void *b, void *c);
private:
	void *m_third;
};

// ?d_0074a590@@YAXXZ
BfmeParserRegDefaultVE_74A590::BfmeParserRegDefaultVE_74A590(void *a, void *b, void *c)
	: BfmeParserRegistrationVE((DataChunkInput *)b,
		&BFMERetailAsciiString((const char *)0x01121ABC),
		c ? c : (void *)0x01336E50)
{
	m_third = a;
	m_vftable = (void *)0x01121B24;
}
