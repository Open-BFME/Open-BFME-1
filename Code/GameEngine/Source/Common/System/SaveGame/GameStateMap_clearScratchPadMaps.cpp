// ?clearScratchPadMaps@GameStateMap@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep

#include <windows.h>
#include <string.h>

typedef bool Bool;
typedef char Char;
typedef int Int;

// BFME retail AsciiString is the one-pointer value type backed by an
// eight-byte StringBase header: ref_count, length, capacity, then data.
class AsciiString
{
public:
	AsciiString() : m_text( 0 ) {}
	~AsciiString();

	const char *str() const
	{
		return m_text ? reinterpret_cast<const char *>( m_text + 8 ) : "";
	}

	Bool isEmpty() const
	{
		return m_text == 0 || *reinterpret_cast<const unsigned short *>( m_text + 4 ) == 0;
	}

	void clear();
	void set( const char *text, Int length );

private:
	char *m_text;
};

class GameState
{
public:
	AsciiString getSaveDirectory() const;
};

extern GameState *TheGameState;

class GameStateMap
{
public:
	void clearScratchPadMaps( void );
};

extern "C" unsigned int __cdecl strlen( const char *str );
#pragma intrinsic( strlen )

void GameStateMap::clearScratchPadMaps( void )
{
	char currentDirectory[ _MAX_PATH ];
	GetCurrentDirectory( _MAX_PATH, currentDirectory );

	SetCurrentDirectory( TheGameState->getSaveDirectory().str() );

	AsciiString fileToDelete;
	WIN32_FIND_DATA item;
	Bool done = FALSE;
	HANDLE hFile = FindFirstFile( "*", &item );
	if( hFile == INVALID_HANDLE_VALUE )
		return;

	while( done == FALSE )
	{
		fileToDelete.clear();

		if( !(item.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
		{
			Char *c = strrchr( item.cFileName, '.' );
			if( c && (stricmp( c, ".map" ) == 0 || stricmp( c, ".wak" ) == 0) )
				fileToDelete.set( item.cFileName, static_cast<Int>( strlen( item.cFileName ) ) );
		}

		if( FindNextFile( hFile, &item ) == 0 )
			done = TRUE;

		if( fileToDelete.isEmpty() == FALSE )
			DeleteFile( fileToDelete.str() );
	}

	FindClose( hFile );
	SetCurrentDirectory( currentDirectory );
}
