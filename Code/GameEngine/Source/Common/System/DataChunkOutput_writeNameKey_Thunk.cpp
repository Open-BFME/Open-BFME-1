// cl: /DNDEBUG /MD /EHsc

extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(const void *, unsigned int,
	unsigned int, void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &);
	~AsciiString();
};

enum NameKeyType { NameKeyType_dummy = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	AsciiString keyToName(NameKeyType);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkTableOfContents
{
public:
	unsigned int allocateID(const AsciiString &);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkOutput
{
public:
	void writeNameKey(NameKeyType);

private:
	unsigned char m_unreconstructed_00[4];
	void *m_tmp_file;
	DataChunkTableOfContents m_contents;
};

// ?writeNameKey@DataChunkOutput@@QAEXW4NameKeyType@@@Z
void DataChunkOutput::writeNameKey(NameKeyType key)
{
	AsciiString kname = TheNameKeyGenerator->keyToName(key);
	int keyAndType = m_contents.allocateID(kname);
	keyAndType <<= 8;
	keyAndType |= 3;
	fwrite((const void *)&keyAndType, sizeof(int), 1, m_tmp_file);
}
