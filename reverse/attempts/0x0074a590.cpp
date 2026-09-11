// ?d_0074a590@@YAXXZ
// partial score=0.85 date=2026-09-11
// ?d_0074a590@@YAXXZ [retail body 0x0074A590]
// experiment: apply the 0x0074A2C0 inheritance-based template
// cl: /DNDEBUG /MD /EHsc

class UserParser;
class DataChunkInput;
typedef bool (*HeightMapParserCallback)(DataChunkInput &, void *, void *);

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString();

private:
	void *m_data;
};

class DataChunkInput
{
public:
	UserParser *registerParser(const BFMERetailAsciiString &name,
		const BFMERetailAsciiString &label, HeightMapParserCallback callback,
		void *userData);
};

class HeightMapDataParserBase
{
public:
	HeightMapDataParserBase(DataChunkInput *input,
		const BFMERetailAsciiString *name,
		const BFMERetailAsciiString *label)
	{
		m_vftable = (void *)0x0107C7D0;
		m_input = input;
		m_parser = input->registerParser(*name, *label,
			(HeightMapParserCallback)0x0041579E, this);
	}
	~HeightMapDataParserBase();

protected:
	void *m_vftable;
	DataChunkInput *m_input;
	UserParser *m_parser;
};

class Rva0074A590Parser : public HeightMapDataParserBase
{
public:
	Rva0074A590Parser(void *heightMap, DataChunkInput *input,
		const BFMERetailAsciiString *label);

private:
	void *m_heightMap;
};

Rva0074A590Parser::Rva0074A590Parser(
	void *heightMap, DataChunkInput *input,
	const BFMERetailAsciiString *label)
	: HeightMapDataParserBase(input,
		&BFMERetailAsciiString((const char *)0x01121ABC),
		label ? label : (const BFMERetailAsciiString *)0x01336E50)
{
	m_heightMap = heightMap;
	m_vftable = (void *)0x01121B24;
}
