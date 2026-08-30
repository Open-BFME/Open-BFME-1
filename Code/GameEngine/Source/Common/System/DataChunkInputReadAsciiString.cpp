// cl: /DNDEBUG /MD /EHsc
// Open-BFME: DataChunkInput::readAsciiString, retail 0x00103450.
//
// BFME yields to the OS before reading the length.  Its AsciiString call sites
// use the out-of-line StringBase<char> buffer helper and copy constructor;
// those choices are distinct from the inline Zero Hour header implementation.

typedef int Int;
typedef unsigned short UnsignedShort;

extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long);

class GameEngine;
extern GameEngine *TheGameEngine;

// BFME retail GameEngine vtable: serviceWindowsOS is slot 16 (+0x40).
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

static void bfmeDataChunkYieldToOS(void)
{
	::Sleep(0);
	if (TheGameEngine)
		reinterpret_cast<BFME_GameEngineServiceWindowsOS *>(TheGameEngine)->serviceWindowsOS();
}

// The retail body uses the shared StringBase<char> implementations at
// 0x00887B60 and 0x00887BE0, while the returned type keeps the AsciiString
// ABI name at the DataChunkInput boundary.
template <typename T>
class StringBase
{
public:
	StringBase(void) : m_data(0) {}
	StringBase(const StringBase &other);
	T *getBufferForRead(Int len);

private:
	void *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(void) : StringBase<char>() {}
	AsciiString(const AsciiString &other);
	~AsciiString();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MapReaderWriterInfo.h
class ChunkInputStream
{
public:
	virtual Int read(void *pData, Int numBytes);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class InputChunk
{
public:
	virtual ~InputChunk();

	InputChunk *next;
	char m_pad08[0x10];
	Int dataLeft;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkTableOfContents
{
	char m_data[0x10];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include/Common/DataChunk.h
class UserParser;
class DataChunkInput
{
protected:
	ChunkInputStream *m_file;
	DataChunkTableOfContents m_contents;
	Int m_fileposOfFirstChunk;
	UserParser *m_parserList;
	InputChunk *m_chunkStack;

	void decrementDataLeft(Int size)
	{
		InputChunk *c;

		c = m_chunkStack;
		while (c) {
			c->dataLeft -= size;
			c = c->next;
		}
	}

public:
	AsciiString readAsciiString(void);
};

// ?readAsciiString@DataChunkInput@@QAE?AVAsciiString@@XZ
AsciiString DataChunkInput::readAsciiString(void)
{
	UnsignedShort len;

	bfmeDataChunkYieldToOS();
	m_file->read(&len, sizeof(UnsignedShort));
	decrementDataLeft(sizeof(UnsignedShort));

	AsciiString theString;
	if (len > 0) {
		char *str = theString.getBufferForRead(len);
		m_file->read(str, len);
		decrementDataLeft(len);

		str[len] = '\0';
	}

	return theString;
}
