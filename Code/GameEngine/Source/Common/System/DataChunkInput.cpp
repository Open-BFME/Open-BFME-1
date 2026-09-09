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
typedef unsigned short DataChunkVersionType;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

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
	// ?set@?$StringBase@D@@QAEXABV1@@Z aliases the retail
	// ?set@UnicodeString@@QAEXABV1@@Z pin (see symbols.csv) -- both types
	// share this StringBase<char> implementation.
	void set(const StringBase &other);

protected:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : public StringBase<char>
{
public:
	AsciiString(void) : StringBase<char>() {}
	// Retail's AsciiString adds no members to StringBase<char>: a copy of one
	// encodes the base copy ctor at 0x00887B60 directly, so the delegation has
	// to be visible here.
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString();

	AsciiString &operator=(const AsciiString &other)
	{
		set(other);
		return *this;
	}

	const char *str() const
	{
		static const char empty = 0;
		return m_data ? static_cast<const char *>(m_data) + 8 : &empty;
	}

	// parse()'s scope/label matches inline this compare (repe cmpsb) rather
	// than calling out -- there is no separate call target for it in the
	// retail body.
	int compare(const AsciiString &that) const
	{
		int thatLen = that.m_data ? *reinterpret_cast<const UnsignedShort *>(static_cast<const char *>(that.m_data) + 4) : 0;
		const char *thatData = that.m_data ? static_cast<const char *>(that.m_data) + 8 : "";
		int thisLen = m_data ? *reinterpret_cast<const UnsignedShort *>(static_cast<const char *>(m_data) + 4) : 0;
		const char *thisData = m_data ? static_cast<const char *>(m_data) + 8 : "";
		int n = thisLen < thatLen ? thisLen : thatLen;
		int c = memcmp(thisData, thatData, n);
		if (c != 0)
			return c;
		return thisLen - thatLen;
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
// parse()'s inlined closeDataChunk() proves the next two slots: tell() at
// +0x04, absoluteSeek() at +0x08. atEndOfFile() proves eof() at +0x0C.
class ChunkInputStream
{
public:
	virtual Int read(void *pData, Int numBytes);
	virtual Int tell(void);
	virtual void absoluteSeek(Int pos);
	virtual Bool eof(void);
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

class DataChunkInput;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
struct DataChunkInfo
{
	AsciiString label;
	AsciiString parentLabel;
	DataChunkVersionType version;
	Int dataSize;
};

typedef Bool (*DataChunkParserPtr)(DataChunkInput &file, DataChunkInfo *info, void *userData);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
// DataChunkInput::registerParser (0x00103840) proves the extra intrusive
// previous-link at +0x08 ahead of the parser field at +0x0C, which parse()'s
// direct field call (call dword ptr [ecx+0x0C]) also requires.
struct UserParser
{
	virtual ~UserParser();
	UserParser *next;					// this+0x04
	UserParser **previous;					// this+0x08
	DataChunkParserPtr parser;				// this+0x0C
	AsciiString label;					// this+0x10
	AsciiString parentLabel;				// this+0x14
	void *userData;						// this+0x18
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
	Bool isOpenedForRead(void) { return m_headerOpened; }

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

	// parse() has no separate call target for closeDataChunk -- MSVC inlines
	// this whole body (the deleting destructor call at the end is the only
	// call still visible), so it is modelled here rather than as its own row.
	void closeDataChunk(void)
	{
		if (m_chunkStack == 0) {
			return;
		}

		if (m_chunkStack->dataLeft > 0) {
			m_file->absoluteSeek(m_file->tell() + m_chunkStack->dataLeft);
			decrementDataLeft(m_chunkStack->dataLeft);
		}

		InputChunk *c = m_chunkStack;
		m_chunkStack = m_chunkStack->next;
		delete c;
	}

public:
	~DataChunkInput();
	void readArrayOfBytes(char *ptr, Int len);
	AsciiString readAsciiString(void);
	NameKeyType readNameKey(void);

	AsciiString openDataChunk(DataChunkVersionType *ver);
	// parse()'s call site has no separate call target for this either -- it
	// is the same 12-byte body as the standalone matched row at 0x00102740,
	// inlined here because the caller is visibly small too.
	UnsignedInt getChunkDataSize(void)
	{
		if (m_chunkStack == 0) {
			return 0;
		}
		return m_chunkStack->dataSize;
	}
	Bool atEndOfFile(void) { return m_file->eof(); }

	Bool parse(void *userData);
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

// ?parse@DataChunkInput@@QAE_NPAX@Z
Bool DataChunkInput::parse(void *userData)
{
	AsciiString label;
	AsciiString parentLabel;
	DataChunkVersionType ver;
	UserParser *parser;
	Bool scopeOK;
	DataChunkInfo info;

	// If the header wasn't a chunk table of contents, we can't parse.
	if (!m_contents.isOpenedForRead()) {
		return false;
	}

	// if we are inside a data chunk right now, get its name
	if (m_chunkStack)
		parentLabel = m_contents.getName(m_chunkStack->id);

	while (atEndOfFile() == false)
	{
		if (m_chunkStack) { // If we are parsing chunks in a chunk, check current length.
			if (m_chunkStack->dataLeft < 4) {
				break;
			}
		}
		// open the chunk
		label = openDataChunk(&ver);
		if (atEndOfFile()) { // FILE * returns eof after you read past end of file, so check.
			break;
		}

		// find a registered parser for this chunk
		for (parser = m_parserList; parser; parser = parser->next)
		{
			// chunk labels must match
			if (parser->label.compare(label) == 0)
			{
				// make sure parent name (scope) also matches
				scopeOK = true;

				if (parentLabel.compare(parser->parentLabel) != 0)
					scopeOK = false;

				if (scopeOK)
				{
					// fill out the chunk info and call the user parser
					info.label = label;
					info.parentLabel = parentLabel;
					info.version = ver;
					info.dataSize = getChunkDataSize();

					// BFME: a parser registered with its own userData
					// (registerParser's 4th argument) takes priority over
					// parse()'s own userData argument.
					if (parser->parser(*this, &info, parser->userData ? parser->userData : userData) == false)
						return false;
					break;
				}
			}
		}

		// close chunk (and skip to end if need be)
		closeDataChunk();
	}

	return true;
}
