// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail 0x00437570, 672 bytes.  Zero Hour's GameTextManager::parseCSF with
// BFME's change: the caller (init, 0x004389E0 through ILT 0x0003EA77) reads the
// whole .csf into memory and passes the buffer, so every file->read becomes a
// copy out of that buffer and the StringInfo array is sized from the header
// here, and the list count is stored to m_textCount (+0x08) on success.  The
// wide scratch buffer lives at +0x280C (sizeof(GameTextManager) is 0x7840) and
// there is no speech field (StringInfo is 8 bytes, see GameText.cpp).
// Retail inlines AsciiString/UnicodeString operator=(const T *), so this TU
// spells them inline over the matched StringBase<T>::set(const T *, int).

#include <string.h>
#include <wchar.h>
#include "ascii_string.h"
#include "unicode_string.h"

typedef bool Bool;
typedef int Int;
typedef char Char;
typedef wchar_t WideChar;

#define MAX_UITEXT_LENGTH (10*1024)

void *operator new[]( unsigned int size );
void operator delete[]( void *block );

#define CSF_ID ( ('C'<<24) | ('S'<<16) | ('F'<<8) | (' ') )
#define CSF_LABEL ( ('L'<<24) | ('B'<<16) | ('L'<<8) | (' ') )
#define CSF_STRING ( ('S'<<24) | ('T'<<16) | ('R'<<8) | (' ') )
#define CSF_STRINGWITHWAVE ( ('S'<<24) | ('T'<<16) | ('R'<<8) | ('W') )

inline AsciiString &AsciiString::operator=( const char *str )
{
	((StringBase<char> *)this)->set( str, str ? strlen( str ) : 0 );
	return *this;
}

inline UnicodeString &UnicodeString::operator=( const wchar_t *str )
{
	((StringBase<unsigned short> *)this)->set( (const unsigned short *)str, str ? wcslen( str ) : 0 );
	return *this;
}

struct StringInfo
{
	AsciiString label;
	UnicodeString text;
};

struct CSFHeader
{
	Int id;
	Int version;
	Int num_labels;
	Int num_strings;
	Int skip;
	Int langid;
};

class GameTextManager
{
protected:
	Bool parseCSF( const Char *data );
	void stripSpaces( WideChar *string );

	void *m_vptr;
	unsigned m_unmodelled04;
	Int m_textCount;
	Char m_buffer[ MAX_UITEXT_LENGTH ];
	WideChar m_tbuffer[ MAX_UITEXT_LENGTH ];
	StringInfo *m_stringInfo;
};

// ?parseCSF@GameTextManager@@IAE_NPBD@Z
Bool GameTextManager::parseCSF( const Char *data )
{
	Int listCount = 0;

	if ( m_stringInfo != NULL )
		return false;

	if ( data == NULL )
		return false;

	const CSFHeader *header = (const CSFHeader *)data;
	const Char *ptr = data + sizeof( CSFHeader );

	if ( header->id != CSF_ID )
		return false;

	Int numLabels = header->num_labels;

	m_stringInfo = new StringInfo[ numLabels ];

	while ( numLabels-- )
	{
		const Int *label = (const Int *)ptr;
		ptr += 3 * sizeof( Int );

		if ( label[0] != CSF_LABEL )
			goto quit;

		if ( label[2] )
		{
			strncpy( m_buffer, ptr, label[2] );
			ptr += label[2];
		}
		m_buffer[ label[2] ] = 0;

		for ( Int num = 0; num < label[1]; num++ )
		{
			const Int *str = (const Int *)ptr;
			ptr += 2 * sizeof( Int );

			if ( str[0] != CSF_STRING && str[0] != CSF_STRINGWITHWAVE )
			{
				delete [] m_stringInfo;
				m_stringInfo = NULL;
				goto quit;
			}

			if ( str[1] )
			{
				// ZH's read length (bytes) survives as wcsncpy's character count.
				wcsncpy( m_tbuffer, (const WideChar *)ptr, str[1] * sizeof( WideChar ) );
				ptr += str[1] * sizeof( WideChar );
			}

			if ( num == 0 )
			{
				m_tbuffer[ str[1] ] = 0;

				{
					WideChar *p = m_tbuffer;
					while ( *p )
					{
						*p = ~*p;
						p++;
					}
				}

				stripSpaces( m_tbuffer );
				m_stringInfo[ listCount ].label = m_buffer;
				m_stringInfo[ listCount ].text = m_tbuffer;
			}

			if ( str[0] == CSF_STRINGWITHWAVE )
				ptr += *(const Int *)ptr + sizeof( Int );
		}

		listCount++;
	}

	m_textCount = listCount;

quit:
	return listCount > 0;
}
