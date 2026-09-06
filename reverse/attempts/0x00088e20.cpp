// ??0BfmeParserRegDefaultVE_88E20@@QAE@PAX00@Z
// partial score=0.55 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// Family of small BfmeParserRegistrationVE-shaped wrapper constructors: build
// a display name from a fixed string literal, default the parent label to
// AsciiString::TheEmptyString (0x01336E50) when the caller passes null, call
// the shared registerParser thunk (0x00415BD1), then re-stamp the vtable for
// the derived slot. Base class mirrors Gen_000872C0_parserRegistrationCtor.cpp
// but is written inline here (implicit inline linkage, safe to redefine per
// TU) so the compiler folds the base construction into the derived ctor the
// way retail does -- a real base subobject also reproduces retail's partial-
// construction EH bookkeeping (this-pointer stack spill) that a flat, single
// class without inheritance did not emit.
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

class BfmeParserRegDefaultVE_88E20 : public BfmeParserRegistrationVE
{
public:
	BfmeParserRegDefaultVE_88E20(void *a, void *b, void *c);
private:
	void *m_third;
};

// ?d_00088e20@@YAXXZ (candidate real name unknown; installs vtable(s) 0x0107C7D0, 0x0107C804)
BfmeParserRegDefaultVE_88E20::BfmeParserRegDefaultVE_88E20(void *a, void *b, void *c)
	: BfmeParserRegistrationVE((DataChunkInput *)b,
		&BFMERetailAsciiString((const char *)0x0107C7C4),
		c ? c : (void *)0x01336E50)
{
	m_third = a;
	m_vftable = (void *)0x0107C804;
}
