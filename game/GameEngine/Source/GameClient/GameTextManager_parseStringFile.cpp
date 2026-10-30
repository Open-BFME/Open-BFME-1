// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail 0x00436960, 587 bytes through RET 4 at +0x248; the generator split it
// at the null-file exit (+0x32). GameTextManager::init (gen dump 0x004389E0)
// allocates m_stringInfo at +0x780C, then passes the File* in through ILT
// 0x00035175 (ilt_oracle CONFIRMED this decoration) and calls deinit on failure.
// Zero Hour's parseStringFile with BFME's changes, the same ones as its matched
// sibling GameTextManager_parseMapStringFile.cpp: the caller owns the file, the
// quote scratch buffers are locals, and there is no speech field. Unlike the
// map file, the text is assigned straight from the wide buffer, with no
// language filter, and the duplicate-label scan uses Zero Hour's inline
// AsciiString::str() (the map body's private labelText view left a register
// assignment here that retail does not have).

#include <string.h>
#include "ascii_string.h"
#include "unicode_string.h"

typedef bool Bool;
typedef int Int;
typedef char Char;
typedef wchar_t WideChar;

#define MAX_UITEXT_LENGTH (10*1024)

extern "C" __declspec(dllimport) int __cdecl _strcmpi( const char *a, const char *b );

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

// UnicodeString::operator=( const wchar_t * ), expanded in place.  A local
// inline definition of the member would emit a COMDAT next to the strong
// retail body in unicode_string.cpp (0x00083D20).
static __forceinline void assignWide( UnicodeString &string, const wchar_t *str )
{
	((StringBase<unsigned short> *)&string)->set( (const unsigned short *)str, str ? wcslen( str ) : 0 );
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

static inline Bool readLine( char *buffer, Int max, File *file )
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

struct StringInfo
{
	AsciiString label;
	UnicodeString text;
};

class GameTextManager
{
protected:
	Bool parseStringFile( File *file );

	void stripSpaces( WideChar *string );
	void removeLeadingAndTrailing( Char *buffer );
	void readToEndOfQuote( File *file, Char *in, Char *out, Char *wavefile, Int maxBufLen );
	void translateCopy( WideChar *outbuf, Char *inbuf );

	void *m_vptr;
	Int m_textCount;
	Int m_unmodelled08;
	Char m_buffer[ MAX_UITEXT_LENGTH ];
	WideChar m_tbuffer[ MAX_UITEXT_LENGTH ];
	StringInfo *m_stringInfo;		// +0x780C
};

Bool GameTextManager::parseStringFile( File *file )
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
			if( !_strcmpi( m_stringInfo[ i ].label.str(), m_buffer ) )
			{
			}
		}

		m_stringInfo[ listCount ].label = m_buffer;

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

					assignWide( m_stringInfo[ listCount ].text, m_tbuffer );
					readString = true;
				}
			}
			else if( !_strcmpi( m_buffer, "END" ) )
			{
				break;
			}
		}

		listCount++;
	}

quit:
	return ok;
}
