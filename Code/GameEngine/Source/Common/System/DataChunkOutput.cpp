// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?openDataChunk@DataChunkOutput@@QAEXPADG@Z: Code/GameEngine/Source/Common/System/DataChunk.cpp
// readable body of ?writeAsciiString@DataChunkOutput@@QAEXABVAsciiString@@@Z: Code/GameEngine/Source/Common/System/DataChunk.cpp
// readable body of ?writeUnicodeString@DataChunkOutput@@QAEXVUnicodeString@@@Z: Code/GameEngine/Source/Common/System/DataChunk.cpp

// DataChunkOutput's writing half: opening a chunk (0x00102B60) and the two
// string writers, AsciiString at 0x00102C80 and UnicodeString at 0x00102D00.
//
// All three write through the temporary file at this+0x04, which is what ties
// them together and what fixes the layout below: the three used to declare
// that field three ways -- once as the real FILE * behind m_contents and
// m_chunkStack, twice as a bare void * behind four bytes of padding -- and
// nothing checked that the offset agreed.

#include <stdio.h>

typedef int Int;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;

struct BfmeStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;					// this+0x04
	UnsignedShort m_pad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *text );
	~AsciiString();

	// Both accessors inline, which is where the offsets come from: the halfword
	// length at the buffer's +4 and the characters from +8, with an empty
	// string standing in for a null buffer.
	Int getLength(void) const { return m_data ? m_data->m_len : 0; }
	const char *str(void) const { return m_data ? (const char *)(m_data + 1) : ""; }

private:
	BfmeStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkTableOfContents
{
public:
	unsigned int allocateID( const AsciiString &name );

private:
	void *m_list;
	int m_listLength;
	unsigned int m_nextID;
	bool m_headerOpened;
	char m_pad[ 3 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class OutputChunk
{
public:
	virtual ~OutputChunk();
	OutputChunk *next;
	unsigned int id;
	int filepos;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkOutput
{
public:
	void openDataChunk( char *name, unsigned short version );
	void writeAsciiString( const AsciiString &theString );
	void writeUnicodeString( UnicodeString theString );

private:
	void *m_output;						// this+0x00
	FILE *m_tmpFile;					// this+0x04
	DataChunkTableOfContents m_contents;			// this+0x08
	OutputChunk *m_chunkStack;				// this+0x18
};

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

	fwrite( &id, sizeof( id ), 1, m_tmpFile );
	fwrite( &version, sizeof( version ), 1, m_tmpFile );
	chunk->filepos = ftell( m_tmpFile );

	int dummy = 0xffff;
	fwrite( &dummy, sizeof( dummy ), 1, m_tmpFile );
}

// ?writeAsciiString@DataChunkOutput@@QAEXABVAsciiString@@@Z
// The reference's three lines unchanged: the length as a halfword, then that
// many characters. fwrite is imported and its address is loaded once for the
// two calls.
void DataChunkOutput::writeAsciiString( const AsciiString& theString )
{
	UnsignedShort len = theString.getLength();
	fwrite( (const char *)&len, sizeof(UnsignedShort) , 1, m_tmpFile );
	fwrite( theString.str(), len , 1, m_tmpFile );
}

// ?writeUnicodeString@DataChunkOutput@@QAEXVUnicodeString@@@Z
// The same shape, counted in WideChars rather than bytes.
void DataChunkOutput::writeUnicodeString(UnicodeString theString)
{
	UnsignedShort len = theString.getLength();
	::fwrite((const char *)&len, sizeof(UnsignedShort), 1, m_tmpFile);
	::fwrite((const char *)theString.str(), len * sizeof(WideChar), 1, m_tmpFile);
}
