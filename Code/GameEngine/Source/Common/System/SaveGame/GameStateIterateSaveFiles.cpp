// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep
// GameState::iterateSaveFiles, retail RVA 0x0010E8B0 (346 bytes).
// The save-list builder calls this callback iterator through ILT 0x00040403.
// _stricmp is a CRT DLL import: declaring a plain out-of-line stricmp changes
// both the call ABI encoding and MSVC's zero/IAT register allocation.

#include <windows.h>

typedef bool Bool;
typedef char Char;
typedef int Int;

extern "C" unsigned int __cdecl strlen( const char *text );

template <typename T> class StringBase
{
	friend class AsciiString;

	private:
	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &source );
	~StringBase();

	struct Header
	{
		int refCount;
		unsigned short length;
        unsigned short capacity;
		T data[ 1 ];
	};

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const AsciiString &source ) : StringBase<char>( source ) {}
	~AsciiString() {}

	const char *str() const
	{
		return m_data ? (const char *)( m_data->data ) : "";
	}

	void set( const char *text, Int length );
	void set( const char *text )
	{
		set( text, static_cast<Int>( strlen( text ) ) );
	}
};

typedef void (*IterateSaveFileCallback)( AsciiString filename, void *userData );

class GameState
{
public:
	AsciiString getSaveDirectory( void ) const;

	private:
	void iterateSaveFiles( IterateSaveFileCallback callback, void *userData );
};

extern "C" __declspec(dllimport) int __cdecl _stricmp( const char *left, const char *right );

void GameState::iterateSaveFiles( IterateSaveFileCallback callback, void *userData )
{
	if( !callback )
		return;

	char currentDirectory[ _MAX_PATH ];
	GetCurrentDirectory( _MAX_PATH, currentDirectory );
	SetCurrentDirectory( getSaveDirectory().str() );

	WIN32_FIND_DATA item;
	HANDLE hFile = FindFirstFile( "*", &item );
	if( hFile == INVALID_HANDLE_VALUE )
		return;

	while( TRUE )
	{
		if( !(item.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
		{
			Char *c = strrchr( item.cFileName, '.' );
			if( c && !_stricmp( c, ".sav" ) )
			{
				AsciiString filename;
				filename.set( item.cFileName );
				callback( filename, userData );
			}
		}

		if( FindNextFile( hFile, &item ) == 0 )
			break;
	}

	FindClose( hFile );
	SetCurrentDirectory( currentDirectory );
}
