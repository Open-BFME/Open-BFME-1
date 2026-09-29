// cl: /Igame/Libraries/Source/WWVegas/WWLib
// Parser-registration wrapper constructor at retail RVA 0x000872C0.

#include "ascii_string.h"

class UserParser
{
};

class DataChunkInput;
struct DataChunkInfo;
typedef bool (*BfmeParserCallback)(DataChunkInput &, DataChunkInfo *, void *);

class DataChunkInput
{
public:
	UserParser *registerParser(const AsciiString &name,
		const AsciiString &label, BfmeParserCallback callback, void *userData);
};

// Retail vtable 0x0107C7D0, pinned as _bfmeVftVE.
extern "C" int _bfmeVftVE[];
void j_0001579e();

class BfmeParserRegistrationVE
{
public:
	BfmeParserRegistrationVE(DataChunkInput *table, AsciiString *name,
		AsciiString *label);

private:
	void *m_vftable;
	DataChunkInput *m_table;
	UserParser *m_parser;
};

BfmeParserRegistrationVE::BfmeParserRegistrationVE(
	DataChunkInput *table, AsciiString *name, AsciiString *label)
{
	m_vftable = _bfmeVftVE;
	m_table = table;
	m_parser = table->registerParser(*name, *label,
		(BfmeParserCallback)j_0001579e, this);
}
