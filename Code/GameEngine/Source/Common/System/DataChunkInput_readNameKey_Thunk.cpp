// cl: /DNDEBUG /MD /EHsc
// readable body of ?readNameKey@DataChunkInput@@QAE?AW4NameKeyType@@XZ: Code/GameEngine/Source/Common/System/DataChunk.cpp
// Open-BFME5: convert DataChunkInput::readNameKey to clean C++.

typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class AsciiString
{
	void *m_data;

public:
	const char *str() const
	{
		static const char empty = 0;
		return m_data ? static_cast<const char *>(m_data) + 8 : &empty;
	}
	~AsciiString();
};

class DataChunkTableOfContents
{
	void *m_list;
	Int m_listLength;
	unsigned int m_nextID;
	int m_headerOpened;

public:
	AsciiString getName(unsigned int id);
};

class ChunkInputStream
{
public:
	virtual Int read(void *pData, Int numBytes) = 0;
};

struct InputChunk
{
	void *vtable;
	InputChunk *next;
	unsigned int id;
	unsigned short version;
	unsigned short padding;
	Int chunkStart;
	Int dataSize;
	Int dataLeft;
};

class DataChunkInput
{
	ChunkInputStream *m_file;
	DataChunkTableOfContents m_contents;
	Int m_fileposOfFirstChunk;
	void *m_parserList;
	InputChunk *m_chunkStack;

	void decrementDataLeft(Int size)
	{
		InputChunk *c = m_chunkStack;
		while (c)
		{
			c->dataLeft -= size;
			c = c->next;
		}
	}

	Int readInt(void)
	{
		Int i;
		m_file->read(&i, sizeof(Int));
		decrementDataLeft(sizeof(Int));
		return i;
	}

public:
	NameKeyType readNameKey(void);
};

class BFME_GameEngineServiceWindowsOS
{
public:
	virtual void _bfme_ge_slot00() = 0;
	virtual void _bfme_ge_slot01() = 0;
	virtual void _bfme_ge_slot02() = 0;
	virtual void _bfme_ge_slot03() = 0;
	virtual void _bfme_ge_slot04() = 0;
	virtual void _bfme_ge_slot05() = 0;
	virtual void _bfme_ge_slot06() = 0;
	virtual void _bfme_ge_slot07() = 0;
	virtual void _bfme_ge_slot08() = 0;
	virtual void _bfme_ge_slot09() = 0;
	virtual void _bfme_ge_slot10() = 0;
	virtual void _bfme_ge_slot11() = 0;
	virtual void _bfme_ge_slot12() = 0;
	virtual void _bfme_ge_slot13() = 0;
	virtual void _bfme_ge_slot14() = 0;
	virtual void _bfme_ge_slot15() = 0;
	virtual void serviceWindowsOS() = 0;
};

class GameEngine;
extern GameEngine *TheGameEngine;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);

static inline void bfmeDataChunkYieldToOS(void)
{
	::Sleep(0);
	if (TheGameEngine)
		reinterpret_cast<BFME_GameEngineServiceWindowsOS *>(TheGameEngine)->serviceWindowsOS();
}

NameKeyType DataChunkInput::readNameKey(void)
{
	bfmeDataChunkYieldToOS();
	Int keyAndType = readInt();
	keyAndType >>= 8;

	AsciiString kname = m_contents.getName(keyAndType);
	NameKeyType k = TheNameKeyGenerator->nameToKey(kname.str());
	return k;
}
