// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseunicode /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
// stlport

typedef unsigned short WideChar;
typedef int Int;
typedef bool Bool;

#include "string_base.h"

extern "C" __declspec(dllimport) WideChar *__cdecl wcsrchr(
	const WideChar *text, WideChar c );

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString( const WideChar *text ) : StringBase<WideChar>( text ) {}
	UnicodeString( const UnicodeString &other )
		: StringBase<WideChar>( other ) {}
	~UnicodeString() throw() {}

	Int getLength() const
	{
		return m_data ? m_data->length : 0;
	}

	WideChar getCharAt( Int index ) const
	{
		return m_data ? m_data->data[index] : 0;
	}

	void concat( WideChar c )
	{
		StringBase<WideChar>::concat( &c, 1 );
	}

	void set( const UnicodeString &other )
	{
		StringBase<WideChar>::set( other );
	}
};

class LanguageFilter
{
protected:
	void unHaxor( UnicodeString &word );
};

WideChar ignoredChars[] = L"-_*'\"";

// ?unHaxor@LanguageFilter@@IAEXAAVUnicodeString@@@Z
void LanguageFilter::unHaxor( UnicodeString &word )
{
	Int len = word.getLength();
	UnicodeString newWord( L"" );
	for( Int i = 0; i < len; ++i )
	{
		WideChar c = word.getCharAt( i );
		if( ( c == L'p' ) || ( c == L'P' ) )
		{
			if( ( ( i + 1 ) < len ) &&
				( ( word.getCharAt( i + 1 ) == L'h' ) ||
				  ( word.getCharAt( i + 1 ) == L'H' ) ) )
			{
				newWord.concat( L'f' );
				++i;
			}
			else
			{
				newWord.concat( c );
			}
		}
		else if( c == L'1' )
			newWord.concat( L'l' );
		else if( c == L'3' )
			newWord.concat( L'e' );
		else if( c == L'4' )
			newWord.concat( L'a' );
		else if( c == L'5' )
			newWord.concat( L's' );
		else if( c == L'6' )
			newWord.concat( L'b' );
		else if( c == L'7' )
			newWord.concat( L't' );
		else if( c == L'0' )
			newWord.concat( L'o' );
		else if( c == L'@' )
			newWord.concat( L'a' );
		else if( c == L'$' )
			newWord.concat( L's' );
		else if( c == L'+' )
			newWord.concat( L't' );
		else if( wcsrchr( ignoredChars, c ) == 0 )
			newWord.concat( c );
	}
	word.set( newWord );
}
