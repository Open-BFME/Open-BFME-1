// Parser-registration wrapper constructor at retail RVA 0x000872C0.

class AsciiString
{
};

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
	m_vftable = (void *)0x0107C7D0;
	m_table = table;
	m_parser = table->registerParser(*name, *label,
		(BfmeParserCallback)0x0041579E, this);
}
