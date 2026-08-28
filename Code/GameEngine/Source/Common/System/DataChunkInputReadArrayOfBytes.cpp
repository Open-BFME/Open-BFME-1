// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME: DataChunkInput::readArrayOfBytes, retail 0x00102870.
//
// BFME yields to the OS before reading a raw byte array.  The read then
// decrements dataLeft on every open parent chunk, matching the layout in the
// adjacent DataChunkInput bodies.

typedef int Int;
typedef bool Bool;

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

public:
	void readArrayOfBytes(char *ptr, Int len);
};

// ?readArrayOfBytes@DataChunkInput@@QAEXPADH@Z
void DataChunkInput::readArrayOfBytes(char *ptr, Int len)
{
	InputChunk *c;

	bfmeDataChunkYieldToOS();
	m_file->read(ptr, len);

	for (c = m_chunkStack; c; c = c->next)
		c->dataLeft -= len;
}
