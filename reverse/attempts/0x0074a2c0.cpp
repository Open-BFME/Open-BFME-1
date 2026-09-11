// ??0WorldHeightMapHeightMapDataParser@@QAE@PAXPAVDataChunkInput@@PBVBFMERetailAsciiString@@@Z
// partial score=0.97 date=2026-09-11
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

class WorldHeightMapHeightMapDataParser : public HeightMapDataParserBase
{
public:
	WorldHeightMapHeightMapDataParser(void *heightMap, DataChunkInput *input,
		const BFMERetailAsciiString *label);

private:
	void *m_heightMap;
};

WorldHeightMapHeightMapDataParser::WorldHeightMapHeightMapDataParser(
	void *heightMap, DataChunkInput *input,
	const BFMERetailAsciiString *label)
	: HeightMapDataParserBase(input,
		&BFMERetailAsciiString((const char *)0x010F5EF8),
		label ? label : (const BFMERetailAsciiString *)0x01336E50)
{
	m_heightMap = heightMap;
	m_vftable = (void *)0x01121AF0;
}
