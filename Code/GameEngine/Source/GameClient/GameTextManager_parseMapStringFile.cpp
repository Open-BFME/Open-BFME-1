// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// Retail 0x00436C40, 660 bytes through the int3 run at +0x294; Ghidra split it
// at the null-file exit (+0x55).  GameTextManager::initMapStringFile (0x00438D50)
// opens the map string file and passes the File* in through ILT 0x0001D7E1.
// This is Zero Hour's parseMapStringFile with BFME's changes: the caller owns
// the file, the quote scratch buffers are locals, the wide buffer lives at
// +0x280C (sizeof(GameTextManager) is 0x7840) and there is no speech field.
// Retail inlines readLine, AsciiString::str() and operator=(const char *), so
// this TU spells them inline; the helpers are the matched GameText.cpp bodies.

#include <string.h>
#include "ascii_string.h"
#include "unicode_string.h"

typedef bool Bool;
typedef int Int;
typedef char Char;
typedef wchar_t WideChar;

#define MAX_UITEXT_LENGTH (10*1024)

extern "C" __declspec(dllimport) int __cdecl _stricmp( const char *a, const char *b );

inline UnicodeString::UnicodeString( const wchar_t *str )
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase( (const unsigned short *)str );
}

inline UnicodeString &UnicodeString::operator=( const UnicodeString &that )
{
	((StringBase<unsigned short> *)this)->set( *(const StringBase<unsigned short> *)&that );
	return *this;
}

inline AsciiString &AsciiString::operator=( const char *str )
{
	((StringBase<char> *)this)->set( str, str ? strlen( str ) : 0 );
	return *this;
}

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
};

class LanguageFilter
{
public:
	void filterLine( UnicodeString &line );
};

extern LanguageFilter *TheLanguageFilter;

struct StringInfo
{
	AsciiString label;
	UnicodeString text;
};

static inline const char *labelText( const AsciiString &label )
{
	const char *text = *(const char * const *)&label;
	return text ? text + 8 : "";
}

class GameTextManager
{
protected:
	Bool parseMapStringFile( File *file );

	void stripSpaces( WideChar *string );
	void removeLeadingAndTrailing( Char *buffer );
	void readToEndOfQuote( File *file, Char *in, Char *out, Char *wavefile, Int maxBufLen );
	void translateCopy( WideChar *outbuf, Char *inbuf );

	Bool readLine( char *buffer, Int max, File *file )
	{
		Int ok = 0;
		while( max && file->read( buffer, 1 ) == 1 )
		{
			ok = 1;
			if( *buffer == '\n' )
				break;
			buffer++;
			max--;
		}
		*buffer = 0;
		return ok != 0;
	}

	void *m_vptr;
	Int m_textCount;
	Int m_unmodelled08;
	Char m_buffer[ MAX_UITEXT_LENGTH ];
	WideChar m_tbuffer[ MAX_UITEXT_LENGTH ];
	char m_unmodelled780C[ 0x1C ];
	StringInfo *m_mapStringInfo;
};

Bool GameTextManager::parseMapStringFile( File *file )
{
	Int listCount = 0;
	Int ok = 1;
	Char buffer2[ MAX_UITEXT_LENGTH ];
	Char buffer3[ MAX_UITEXT_LENGTH ];

	if( file == 0 )
		return false;

	while( ok )
	{
		if( !readLine( m_buffer, MAX_UITEXT_LENGTH, file ) )
			break;

		removeLeadingAndTrailing( m_buffer );

		if( ( *(unsigned short *)m_buffer == 0x2F2F ) || !m_buffer[ 0 ] )
			continue;

		for( Int i = 0; i < listCount; i++ )
		{
			StringInfo *info = &m_mapStringInfo[ i ];
			if( !_stricmp( labelText( info->label ), m_buffer ) )
			{
			}
		}

		m_mapStringInfo[ listCount ].label = m_buffer;

		Bool readString = false;
		while( ok )
		{
			if( !readLine( m_buffer, sizeof( m_buffer ) - 1, file ) )
			{
				ok = 0;
				goto quit;
			}

			removeLeadingAndTrailing( m_buffer );

			if( m_buffer[ 0 ] == '"' )
			{
				Int len = strlen( m_buffer );
				m_buffer[ len ] = '\n';
				m_buffer[ len + 1 ] = 0;
				readToEndOfQuote( file, &m_buffer[ 1 ], buffer2, buffer3, MAX_UITEXT_LENGTH );

				if( !readString )
				{
					translateCopy( m_tbuffer, buffer2 );
					stripSpaces( m_tbuffer );

					UnicodeString text = UnicodeString( m_tbuffer );
					if( TheLanguageFilter )
						TheLanguageFilter->filterLine( text );

					m_mapStringInfo[ listCount ].text = text;
					readString = true;
				}
			}
			else if( !_stricmp( m_buffer, "END" ) )
			{
				break;
			}
		}

		listCount++;
	}

quit:
	return ok;
}
