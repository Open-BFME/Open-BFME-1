// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?init@GameTextManager@@UAEXXZ: game/GameEngine/Source/GameClient/GameText.cpp
//
// Retail 0x004389E0, 697 bytes through the RET at +0x2B8. This is Zero Hour's
// GameTextManager::init with BFME's file workflow, the same changes as the
// matched initMapStringFile and parseStringFile siblings. The string file
// (g_strFile, "data\\lotr.str") is opened, converted to a RAM file, counted,
// rewound and parsed through ILT 0x00035175 (deinit on failure). When it yields
// no strings, the CSF file named by g_csfFile ("Lang\\%s\\Lotr.csf") is read whole
// and handed to parseCSF. The lookup table is then built and sorted with
// STLport's sort (__final_insertion_sort inlined here). The window title is
// set from fetch("GUI:FullGameName").
#include "ascii_string.h"
#include "unicode_string.h"

// Retail allocates and frees the arrays through operator new[]/delete[].
void *operator new[]( unsigned int size );
void operator delete[]( void *p );

#include "../../Include/Common/ScalarTypes.h"


typedef wchar_t WideChar;

#define MAX_UITEXT_LENGTH (10*1024)

__forceinline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->releaseBuffer();
}

class File
{
public:
	virtual ~File();
	virtual Bool open( const char *, Int = 0 );
	virtual void close();
	virtual Int read( void *, Int );
	virtual Int write( const void *, Int );
	virtual Int seek( Int pos, Int mode );
	virtual void nextLine( char *, Int );
	virtual Bool scanInt( Int & );
	virtual Bool scanReal( float & );
	virtual Bool scanString( AsciiString & );
	virtual Bool print( const char *, ... );
	virtual Int size();
	virtual Int position();
	virtual char *readEntireAndClose();
	virtual File *convertToRAMFile();

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
// Zero Hour's WinMain.cpp globals g_strFile and g_csfFile. No data row owns
// these words yet, so they keep address names.
extern const Char *g_Va012A6508;		// g_strFile: "data\\lotr.str"
extern const Char *g_Va012A650C;		// g_csfFile: "Lang\\%s\\Lotr.csf"
extern void *ApplicationHWnd;
extern "C" __declspec(dllimport) int __stdcall SetWindowTextW( void *hWnd, const wchar_t *lpString );

AsciiString GetRegistryLanguage();

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
struct GameTextStringLookUp;
struct GameTextStringCompare
{
};
struct BfmePairCXD;

void Gen004388C0( Q3SortElem8 *first, Q3SortElem8 *last, Q3SortElem8 *value, Int depthLimit, Q3SortCompare comp );
void GameTextInsertionSort00437E90( GameTextStringLookUp *first, GameTextStringLookUp *last, GameTextStringCompare comp );
void bfmeGoCXD( BfmePairCXD *first, BfmePairCXD *last, void *comp );

// STLport's inline sort(), __lg() and __final_insertion_sort() around them.
inline Int bfmeSortDepth( Int n )
{
	Int k;
	for( k = 0; n != 1; n >>= 1 )
		++k;
	return k;
}

inline void bfmeFinalInsertionSort( StringLookUp *first, StringLookUp *last, const Q3SortCompare &comp )
{
	if( last - first > 16 )
	{
		GameTextInsertionSort00437E90( (GameTextStringLookUp *)first, (GameTextStringLookUp *)( first + 16 ), *(GameTextStringCompare *)&comp );
		bfmeGoCXD( (BfmePairCXD *)( first + 16 ), (BfmePairCXD *)last, *(void **)&comp );
	}
	else
	{
		GameTextInsertionSort00437E90( (GameTextStringLookUp *)first, (GameTextStringLookUp *)last, *(GameTextStringCompare *)&comp );
	}
}

inline void sortStringLookUp( StringLookUp *first, StringLookUp *last, const Q3SortCompare &comp )
{
	if( first != last )
	{
		Gen004388C0( (Q3SortElem8 *)first, (Q3SortElem8 *)last, (Q3SortElem8 *)0, bfmeSortDepth( last - first ) * 2, comp );
		bfmeFinalInsertionSort( first, last, comp );
	}
}

class GameTextManager
{
public:
	virtual ~GameTextManager();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	// MSVC lays out these overloads in reverse declaration order: fetch(const Char *) is +0x28.
	virtual UnicodeString fetch( AsciiString label, Bool *exists = NULL );
	virtual UnicodeString fetch( const Char *label, Bool *exists = NULL );
	virtual void slot30();
	virtual void deinit();

protected:
	Bool getStringCount( File *file, Int &textCount );
	Bool parseStringFile( File *file );
	Bool parseCSF( const Char *buffer );

	Int m_subsystemBase;
	Int m_textCount;							// +0x08
	Char m_buffer[ MAX_UITEXT_LENGTH ];
	WideChar m_tbuffer[ MAX_UITEXT_LENGTH ];
	StringInfo *m_stringInfo;					// +0x780C
	StringLookUp *m_stringLUT;					// +0x7810
	Bool m_initialized;							// +0x7814
	void *m_noStringList;
	Int m_useStringFile;						// +0x781C
};

// ?init@GameTextManager@@UAEXXZ
void GameTextManager::init( void )
{
	AsciiString csfFile;
	csfFile.format( AsciiString( g_Va012A650C ), GetRegistryLanguage().str() );

	if( m_initialized )
		return;

	m_initialized = true;
	m_textCount = 0;

	if( m_useStringFile )
	{
		File *file = TheFileSystem->openFile( g_Va012A6508, 0x21 );
		if( file )
		{
			file->deleteOnClose();
			File *ramFile = file->convertToRAMFile();
			if( ramFile )
			{
				ramFile->deleteOnClose();
				getStringCount( ramFile, m_textCount );
				if( m_textCount > 0 )
				{
					m_stringInfo = new StringInfo[ m_textCount ];
					ramFile->seek( 0, 0 );
					if( parseStringFile( ramFile ) == false )
					{
						deinit();
						return;
					}
				}
				ramFile->close();
			}
		}
	}

	if( m_textCount == 0 )
	{
		File *file = TheFileSystem->openFile( csfFile.str(), 0 );
		if( file )
		{
			file->deleteOnClose();
			char *buffer = file->readEntireAndClose();
			if( buffer )
			{
				parseCSF( buffer );
				delete [] buffer;
			}
		}
	}

	m_stringLUT = new StringLookUp[ m_textCount ];

	StringLookUp *lut = m_stringLUT;
	StringInfo *info = m_stringInfo;
	for( Int i = 0; i < m_textCount; i++ )
	{
		lut->info = info;
		lut->label = &info->label;
		lut++;
		info++;
	}

	sortStringLookUp( m_stringLUT, m_stringLUT + m_textCount, Q3SortCompare() );

	UnicodeString ourName = fetch( "GUI:FullGameName" );
	if( ApplicationHWnd )
		SetWindowTextW( ApplicationHWnd, ourName.str() );
}
