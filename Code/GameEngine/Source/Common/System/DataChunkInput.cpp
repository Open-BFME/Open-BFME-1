// cl: /DNDEBUG /MD /EHsc
// readable body of ??1DataChunkInput@@QAE@XZ: Code/GameEngine/Source/Common/System/DataChunk.cpp
// readable body of ?readArrayOfBytes@DataChunkInput@@QAEXPADH@Z: Code/GameEngine/Source/Common/System/DataChunk.cpp
// readable body of ?readAsciiString@DataChunkInput@@QAE?AVAsciiString@@XZ: Code/GameEngine/Source/Common/System/DataChunk.cpp
// readable body of ?readNameKey@DataChunkInput@@QAE?AW4NameKeyType@@XZ: Code/GameEngine/Source/Common/System/DataChunk.cpp

// DataChunkInput's teardown and its three readers:
//
//   ~DataChunkInput  0x00102910   the chunk stack, the parser list and the
//                                 table's mapping list, each freed through the
//                                 node's virtual deleting destructor
//   readArrayOfBytes 0x00102870   raw bytes
//   readAsciiString  0x00103450   a counted string
//   readNameKey      0x00103390   an id looked up in the table, then interned
//
// The destructor is the layout evidence the readers rely on: the chunk stack
// is at +0x1c, the parser list at +0x18 and the table of contents starts at
// +0x04. Both facts used to be asserted four times over -- one file spelled
// the table as char[0x10], another as four fields, a third as four differently
// typed fields -- and the InputChunk fields the readers decrement were named
// in one file and padded over in two.
//
// The yield is BFME's, not Zero Hour's: every read gives the OS a slice and
// pumps the engine's window messages first, through slot 16 of the GameEngine
// vtable.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);

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

// BFME yields to the OS before every read.
static void bfmeDataChunkYieldToOS(void)
{
	::Sleep(0);
	if (TheGameEngine)
		reinterpret_cast<BFME_GameEngineServiceWindowsOS *>(TheGameEngine)->serviceWindowsOS();
}

// The retail bodies use the shared StringBase<char> implementations at
// 0x00887B60 and 0x00887BE0, while the returned type keeps the AsciiString
// ABI name at the DataChunkInput boundary.
template <typename T>
class StringBase
{
public:
	StringBase(void) : m_data(0) {}
	StringBase(const StringBase &other);
	T *getBufferForRead(Int len);

protected:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : public StringBase<char>
{
public:
	AsciiString(void) : StringBase<char>() {}
	AsciiString(const AsciiString &other);
	~AsciiString();

	const char *str() const
	{
		static const char empty = 0;
		return m_data ? static_cast<const char *>(m_data) + 8 : &empty;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

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
	virtual ~InputChunk();					// vptr this+0x00

	InputChunk *next;					// this+0x04
	UnsignedInt id;						// this+0x08
	UnsignedShort version;					// this+0x0C
	UnsignedShort padding;
	Int chunkStart;						// this+0x10
	Int dataSize;						// this+0x14
	Int dataLeft;						// this+0x18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
struct UserParser
{
	virtual ~UserParser();
	UserParser *next;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
struct Mapping
{
	virtual ~Mapping();
	Mapping *next;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkTableOfContents
{
public:
	AsciiString getName(UnsignedInt id);

	~DataChunkTableOfContents()
	{
		Mapping *mapping = m_list;
		while (mapping != 0) {
			Mapping *next = mapping->next;
			delete mapping;
			mapping = next;
		}
	}

	Mapping *m_list;					// this+0x00
	Int m_listLength;
	UnsignedInt m_nextID;
	Bool m_headerOpened;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkInput
{
protected:
	ChunkInputStream *m_file;				// this+0x00
	DataChunkTableOfContents m_contents;			// this+0x04
	Int m_fileposOfFirstChunk;				// this+0x14
	UserParser *m_parserList;				// this+0x18
	InputChunk *m_chunkStack;				// this+0x1C

	void decrementDataLeft(Int size)
	{
		InputChunk *c;

		c = m_chunkStack;
		while (c) {
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
	~DataChunkInput();
	void readArrayOfBytes(char *ptr, Int len);
	AsciiString readAsciiString(void);
	NameKeyType readNameKey(void);
};

// ??1DataChunkInput@@QAE@XZ
DataChunkInput::~DataChunkInput()
{
	InputChunk *chunk = m_chunkStack;
	while (chunk != 0) {
		InputChunk *next = chunk->next;
		delete chunk;
		chunk = next;
	}
	m_chunkStack = 0;

	UserParser *parser = m_parserList;
	while (parser != 0) {
		UserParser *next = parser->next;
		delete parser;
		parser = next;
	}
}

// ?readArrayOfBytes@DataChunkInput@@QAEXPADH@Z
void DataChunkInput::readArrayOfBytes(char *ptr, Int len)
{
	InputChunk *c;

	bfmeDataChunkYieldToOS();
	m_file->read(ptr, len);

	for (c = m_chunkStack; c; c = c->next)
		c->dataLeft -= len;
}

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

// ?readNameKey@DataChunkInput@@QAE?AW4NameKeyType@@XZ
NameKeyType DataChunkInput::readNameKey(void)
{
	bfmeDataChunkYieldToOS();
	Int keyAndType = readInt();
	keyAndType >>= 8;

	AsciiString kname = m_contents.getName(keyAndType);
	NameKeyType k = TheNameKeyGenerator->nameToKey(kname.str());
	return k;
}
