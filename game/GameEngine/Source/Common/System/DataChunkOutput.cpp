// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?openDataChunk@DataChunkOutput@@QAEXPADG@Z: game/GameEngine/Source/Common/System/DataChunk.cpp
// readable body of ?writeAsciiString@DataChunkOutput@@QAEXABVAsciiString@@@Z: game/GameEngine/Source/Common/System/DataChunk.cpp
// readable body of ?writeUnicodeString@DataChunkOutput@@QAEXVUnicodeString@@@Z: game/GameEngine/Source/Common/System/DataChunk.cpp

#include <stdio.h>

typedef int Int;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;

struct BfmeStringData
{
    UnsignedShort m_refCount;
    UnsignedShort m_numCharsAllocated;
    UnsignedShort m_len;
    UnsignedShort m_pad;
};

class AsciiString;
template <typename T>
class StringBase
{
    friend class AsciiString;
private:
    StringBase(const StringBase<T> &);
    StringBase(const T *);
    ~StringBase();
    void concat(const T *, int);
    BfmeStringData *m_data;
};

// The retail call sites inline these wrappers around the private char base.
class AsciiString : private StringBase<char>
{
public:
    AsciiString(const char *text) : StringBase<char>(text) {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}
    void concat(const char *text, int length) { StringBase<char>::concat(text, length); }
    Int getLength() const { return m_data ? m_data->m_len : 0; }
    const char *str() const { return m_data ? reinterpret_cast<const char *>(m_data + 1) : ""; }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	~UnicodeString();

	int getLength(void) const
	{
		return m_data ? *(const UnsignedShort *)((const char *)m_data + 4) : 0;
	}

	const WideChar *str(void) const
	{
		static const WideChar nullChar = 0;
		return m_data ? (const WideChar *)((const char *)m_data + 8) : &nullChar;
	}

private:
	void *m_data;
};

class GlobalData
{
public:
    AsciiString getPath_UserData() const;
};
extern GlobalData *TheGlobalData;

class Mapping;
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkTableOfContents
{
public:
    DataChunkTableOfContents()
        : m_list(0), m_listLength(0), m_nextID(1), m_headerOpened(false) {}
    ~DataChunkTableOfContents();
    unsigned int allocateID(const AsciiString &name);
private:
    Mapping *m_list;
    int m_listLength;
    unsigned int m_nextID;
    bool m_headerOpened;
};

class OutputStream;
class OutputChunk
{
public:
	virtual ~OutputChunk();
	OutputChunk *next;
	unsigned int id;
	int filepos;
};

// The retail stores agree with the reference writer layout through m_chunkStack (+0x18).
class DataChunkOutput
{
public:
    DataChunkOutput(OutputStream *output);
    void openDataChunk(char *name, unsigned short version);
    void writeAsciiString(const AsciiString &theString);
    void writeUnicodeString(UnicodeString theString);
private:
    OutputStream *m_pOut;
    FILE *m_tmp_file;
    DataChunkTableOfContents m_contents;
    OutputChunk *m_chunkStack;
};

// The reference temporary-file constructor agrees with retail getter 0x000106EA
// and its narrow-string concat/release calls; no named direct caller is recovered.
// ??0DataChunkOutput@@QAE@PAVOutputStream@@@Z
DataChunkOutput::DataChunkOutput(OutputStream *output) : m_pOut(output)
{
    AsciiString temporaryFileName = TheGlobalData->getPath_UserData();
    temporaryFileName.concat("_tmpChunk.dat", 13);
    m_tmp_file = fopen(temporaryFileName.str(), "wb");
    m_chunkStack = 0;
}

// ?openDataChunk@DataChunkOutput@@QAEXPADG@Z
void DataChunkOutput::openDataChunk( char *name, unsigned short version )
{
	unsigned int id;
	{
		// The retail build destroys this temporary before allocating the chunk.
		const AsciiString &chunkName = AsciiString( name );
		id = m_contents.allocateID( chunkName );
	}

	OutputChunk *chunk = new OutputChunk;
	chunk->next = m_chunkStack;
	m_chunkStack = chunk;
	chunk->id = id;

	fwrite( &id, sizeof( id ), 1, m_tmp_file );
	fwrite( &version, sizeof( version ), 1, m_tmp_file );
	chunk->filepos = ftell( m_tmp_file );

	int dummy = 0xffff;
	fwrite( &dummy, sizeof( dummy ), 1, m_tmp_file );
}

// ?writeAsciiString@DataChunkOutput@@QAEXABVAsciiString@@@Z
// The reference's three lines unchanged: the length as a halfword, then that
// many characters. fwrite is imported and its address is loaded once for the
// two calls.
void DataChunkOutput::writeAsciiString( const AsciiString& theString )
{
	UnsignedShort len = theString.getLength();
	fwrite( (const char *)&len, sizeof(UnsignedShort) , 1, m_tmp_file );
	fwrite( theString.str(), len , 1, m_tmp_file );
}

// ?writeUnicodeString@DataChunkOutput@@QAEXVUnicodeString@@@Z
// The same shape, counted in WideChars rather than bytes.
void DataChunkOutput::writeUnicodeString(UnicodeString theString)
{
	UnsignedShort len = theString.getLength();
	::fwrite((const char *)&len, sizeof(UnsignedShort), 1, m_tmp_file);
	::fwrite((const char *)theString.str(), len * sizeof(WideChar), 1, m_tmp_file);
}
