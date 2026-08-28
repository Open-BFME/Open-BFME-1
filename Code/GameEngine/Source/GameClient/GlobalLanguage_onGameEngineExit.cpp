// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

#include <list>

typedef int Bool;
typedef unsigned long DWORD;
typedef void *HANDLE;
typedef void *HMODULE;
typedef const char *LPCSTR;
typedef char *LPSTR;

#define NULL 0
#define MAX_PATH 260
#define INVALID_HANDLE_VALUE ((HANDLE)-1)

extern "C" __declspec(dllimport) HMODULE __stdcall LoadLibraryA( LPCSTR );
extern "C" __declspec(dllimport) void * __stdcall GetProcAddress( HMODULE, LPCSTR );
extern "C" __declspec(dllimport) Bool __stdcall FreeLibrary( HMODULE );
extern "C" __declspec(dllimport) DWORD __stdcall GetTempPathA( DWORD, LPSTR );
extern "C" __declspec(dllimport) HANDLE __stdcall FindFirstFileA( LPCSTR, void * );
extern "C" __declspec(dllimport) Bool __stdcall FindNextFileA( HANDLE, void * );
extern "C" __declspec(dllimport) Bool __stdcall FindClose( HANDLE );
extern "C" __declspec(dllimport) Bool __stdcall DeleteFileA( LPCSTR );
extern "C" __declspec(dllimport) Bool __stdcall RemoveDirectoryA( LPCSTR );

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	void set( const StringBase<T> &source );

private:
	StringBase() {}
	StringBase( const T *text );
	void releaseBuffer();
	char *m_data;
};

struct BfmeStringView
{
	char *m_data;
};

class AsciiString
{
public:
	AsciiString() { m_string.m_data = NULL; }
	AsciiString( const char *text ) : m_string( text ) {}
	~AsciiString() { m_string.releaseBuffer(); }

	const char *str() const
	{
		static const char TheNullChr = 0;
		char *data = ((const BfmeStringView *)this)->m_data;
		return data ? data + 8 : &TheNullChr;
	}

	Bool isEmpty() const
	{
		return m_string.m_data == NULL || *(unsigned short *)(m_string.m_data + 4) == 0;
	}

	Bool isNotEmpty() const { return !isEmpty(); }

	__forceinline void clear()
	{
		m_string.set( *(const StringBase<char> *)0x01336E50 );
	}

	void format( AsciiString format, ... );

private:
	StringBase<char> m_string;
};

struct BfmeFontEntry
{
	void *unmodelled;
	AsciiString value;
};

struct BfmeFindData
{
	unsigned char header[ 44 ];
	char fileName[ MAX_PATH ];
	char alternateFileName[ 14 ];
	unsigned short padding;
};

class GlobalLanguage
{
public:
	void onGameEngineExit();

private:
	typedef std::list<BfmeFontEntry> StringList;
	typedef StringList::iterator StringListIt;
	unsigned char m_unmodelled00[ 0x134 ];
	StringList m_localFonts;
};

void GlobalLanguage::onGameEngineExit()
{
	if( m_localFonts.size() )
	{
		HMODULE library = LoadLibraryA( "GDI32.DLL" );
		if( library )
		{
			typedef Bool (__stdcall *RemoveFontResourceExProc)( LPCSTR, DWORD, void * );
			RemoveFontResourceExProc removeFontResourceEx =
				(RemoveFontResourceExProc)GetProcAddress( library, "RemoveFontResourceExA" );
			if( removeFontResourceEx )
			{
				for( StringListIt it = m_localFonts.begin(); it != m_localFonts.end(); ++it )
				{
					if( !it->value.isEmpty() )
					{
						removeFontResourceEx( it->value.str(), 0x30, NULL );
						it->value.clear();
					}
				}
			}
			FreeLibrary( library );
		}
		m_localFonts.clear();
	}

	char tempPath[ MAX_PATH ];
	if( GetTempPathA( MAX_PATH, tempPath ) )
	{
		AsciiString fontDirectory;
		fontDirectory.format( "%s\\%s", tempPath, *(const char **)0x012B53A8 );

		AsciiString searchPath;
		searchPath.format( "%s\\lrf*.*", fontDirectory.str() );

		BfmeFindData findData;
		HANDLE findHandle = FindFirstFileA( searchPath.str(), &findData );
		while( findHandle != INVALID_HANDLE_VALUE )
		{
			AsciiString fontPath;
			fontPath.format( "%s\\%s", fontDirectory.str(), findData.fileName );
			DeleteFileA( fontPath.str() );

			if( !FindNextFileA( findHandle, &findData ) )
			{
				FindClose( findHandle );
				findHandle = INVALID_HANDLE_VALUE;
			}
		}

		RemoveDirectoryA( fontDirectory.str() );
	}
}
