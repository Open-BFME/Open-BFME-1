// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?openDataChunk@DataChunkOutput@@QAEXPADG@Z: Code/GameEngine/Source/Common/System/DataChunk.cpp
#include <stdio.h>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *text );
	~AsciiString();

private:
	char *m_data;
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

private:
	void *m_output;
	FILE *m_tmpFile;
	DataChunkTableOfContents m_contents;
	OutputChunk *m_chunkStack;
};

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
