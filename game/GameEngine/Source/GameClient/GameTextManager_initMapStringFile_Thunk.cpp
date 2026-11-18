// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?initMapStringFile@GameTextManager@@UAEXABVAsciiString@@@Z: game/GameEngine/Source/GameClient/GameText.cpp
//
// Retail 0x00438D50, 432 bytes through RET 4. Zero Hour's initMapStringFile with
// BFME's changes: the old map arrays are freed first, and this function opens the
// file itself (deleteOnClose), counts the strings, rewinds and hands the File* to
// parseMapStringFile (ILT 0x0001D7E1, matched in
// GameTextManager_parseMapStringFile.cpp), then sorts the lookup table with
// STLport sort, whose introsort loop and final insertion sort are matched
// out-of-line bodies (ILTs 0x000323F3 and 0x00007F4F). Layout as the matched
// GameText siblings: m_mapStringInfo +0x7828, m_mapStringLUT +0x782C,
// m_mapTextCount +0x7830, StringInfo is 8 bytes.

// Retail allocates and frees the arrays through operator new[]/delete[].
void *operator new[]( unsigned int size );
void operator delete[]( void *p );

#include "ascii_string.h"
#include "unicode_string.h"

#include "../../Include/Common/ScalarTypes.h"


typedef wchar_t WideChar;

#define MAX_UITEXT_LENGTH (10*1024)

class File
{
public:
	virtual ~File();
	virtual Bool open( const char *, Int = 0 );
	virtual void close();
	virtual Int read( void *, Int );
	virtual Int write( const void *, Int );
	virtual Int seek( Int pos, Int mode );

	void deleteOnClose() { m_deleteOnClose = true; }

private:
	AsciiString m_nameStr;
	Int m_access;
	Bool m_open;
	Bool m_deleteOnClose;		// +0x0D
};

class FileSystem
{
public:
	File *openFile( const Char *filename, Int access );
};

extern FileSystem *TheFileSystem;

struct StringInfo
{
	StringInfo();
	~StringInfo();

	AsciiString label;
	UnicodeString text;
};

struct StringLookUp
{
	AsciiString *label;
	StringInfo *info;
};

// STLport sort's out-of-line pieces for the lookup table (GameText sort TUs).
struct Q3SortElem8;
struct Q3SortCompare
{
};

void Gen004388C0( Q3SortElem8 *first, Q3SortElem8 *last, Q3SortElem8 *value, Int depthLimit, Q3SortCompare comp );
void Gen00438270( Q3SortElem8 *first, Q3SortElem8 *last, Q3SortCompare comp );

// STLport's inline sort() and __lg() around them.
inline Int bfmeSortDepth( Int n )
{
	Int k;
	for( k = 0; n != 1; n >>= 1 )
		++k;
	return k;
}

inline void bfmeSortLookUp( StringLookUp *first, StringLookUp *last, Q3SortCompare comp )
{
	if( first != last )
	{
		Gen004388C0( (Q3SortElem8 *)first, (Q3SortElem8 *)last, (Q3SortElem8 *)0, bfmeSortDepth( last - first ) * 2, comp );
		Gen00438270( (Q3SortElem8 *)first, (Q3SortElem8 *)last, comp );
	}
}

class GameTextManager
{
public:
	virtual void initMapStringFile( const AsciiString &filename );

protected:
	Bool getStringCount( File *file, Int &textCount );
	Bool parseMapStringFile( File *file );

	Int m_subsystemBase;
	Int m_textCount;
	Char m_buffer[ MAX_UITEXT_LENGTH ];
	WideChar m_tbuffer[ MAX_UITEXT_LENGTH ];
	char m_unmodelled780C[ 0x1C ];
	StringInfo *m_mapStringInfo;		// +0x7828
	StringLookUp *m_mapStringLUT;		// +0x782C
	Int m_mapTextCount;					// +0x7830
};

// ?initMapStringFile@GameTextManager@@UAEXABVAsciiString@@@Z
void GameTextManager::initMapStringFile( const AsciiString &filename )
{
	m_mapTextCount = 0;

	if( m_mapStringLUT )
	{
		delete [] m_mapStringLUT;
		m_mapStringLUT = NULL;
	}

	if( m_mapStringInfo )
	{
		delete [] m_mapStringInfo;
		m_mapStringInfo = NULL;
	}

	File *file = TheFileSystem->openFile( filename.str(), 0x21 );
	if( file == NULL )
		return;

	file->deleteOnClose();
	getStringCount( file, m_mapTextCount );
	if( m_mapTextCount > 0 )
	{
		file->seek( 0, 0 );
		m_mapStringInfo = new StringInfo[ m_mapTextCount ];
		parseMapStringFile( file );
		m_mapStringLUT = new StringLookUp[ m_mapTextCount ];

		StringLookUp *lut = m_mapStringLUT;
		StringInfo *info = m_mapStringInfo;
		for( Int i = 0; i < m_mapTextCount; i++ )
		{
			lut->info = info;
			lut->label = &info->label;
			lut++;
			info++;
		}

		bfmeSortLookUp( m_mapStringLUT, m_mapStringLUT + m_mapTextCount, Q3SortCompare() );
	}

	file->close();
}
