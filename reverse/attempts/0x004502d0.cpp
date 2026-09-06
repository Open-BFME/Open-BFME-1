// ??0Gen004502D0@@QAE@PAXPAVDataChunkInput@@PAVBFMERetailAsciiString@@@Z
// partial score=0.90 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
//
// Fuzzy twin (r0.890) of PolygonTriggerDeleteTriggersThunk.cpp's landed
// naked lift at 0x0074A680 -- but that "twin" turned out to be a coincidence
// (the difflib match was only on the boilerplate EH prologue/epilogue); the
// real recipe came from tools/vtable_lookup.py 0x0107C7D0, which shows the
// vtable this body installs mid-construction is BfmeParserRegistrationVE's
// (Gen_000872C0_parserRegistrationCtor.cpp): `m_vftable=0x0107C7D0;
// m_table=table; m_parser=table->registerParser(name,label,callback,this);`
// is INLINED here verbatim (callee 0x0041579E is that ctor's own hardcoded
// callback), then this constructor finishes by re-installing ITS OWN vtable
// (0x010F5E78, cited nowhere else in the ledger) and one more field.
//
// The three explicit parameters, by stack offset: 1st -> stored verbatim at
// +0x0C; 2nd -> the DataChunkInput table; 3rd -> a nullable label override
// (falls back to a global AsciiString at 0x01336E50 when null). The
// registration's "name" argument is a fixed local BFMERetailAsciiString
// built from "MPPositionInfo" (reverse/string_xrefs.tsv confirms that
// literal is referenced from this RVA).
//
// IDENTITY IS NOT RECOVERED for the derived class, the default-label global
// or the callback at 0x0041579E.

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	__forceinline ~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer();
	char *m_data;
};

class UserParser;
struct DataChunkInfo;
class DataChunkInput;
typedef bool (*BfmeParserCallback)(DataChunkInput &, DataChunkInfo *, void *);

class DataChunkInput
{
public:
	UserParser *registerParser(const BFMERetailAsciiString &name,
		const BFMERetailAsciiString &label, BfmeParserCallback callback, void *userData);
};

extern BFMERetailAsciiString g_defaultLabelRva004502D0;	// 0x01336E50, address-derived

class Gen004502D0
{
public:
	Gen004502D0(void *extra, DataChunkInput *table, BFMERetailAsciiString *labelOverride);

	void *m_00;
	DataChunkInput *m_table;
	UserParser *m_parser;
	void *m_0c;
	int m_10;
};

// ??0Gen004502D0@@QAE@PAXPAVDataChunkInput@@PAVBFMERetailAsciiString@@@Z
Gen004502D0::Gen004502D0(void *extra, DataChunkInput *table, BFMERetailAsciiString *labelOverride)
{
	Gen004502D0 *self = this;
	BFMERetailAsciiString *label = labelOverride ? labelOverride : &g_defaultLabelRva004502D0;
	BFMERetailAsciiString name("MPPositionInfo");

	self->m_00 = (void *)0x0107C7D0;
	self->m_table = table;
	self->m_parser = table->registerParser(name, *label, (BfmeParserCallback)0x0041579E, self);

	self->m_0c = extra;
	self->m_00 = (void *)0x010F5E78;
	self->m_10 = 0;
}
