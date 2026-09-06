// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: INI::parseStaticGameLODLevel (retail 0x0007BCF0 105 B; a gap
// claimed through its exception literal).  Zero Hour's body: the token is
// matched case-insensitively (imported _stricmp) against the six
// StaticGameLODNames and its index stored else INIException(3 "invalid
// GameLODLevel token %s -- expected LOW/MEDIUM/HIGH") is thrown; retail places
// the matching store after the throw block.

typedef int Int;

extern "C" __declspec(dllimport) int __cdecl _stricmp( const char *a, const char *b );

enum StaticGameLODLevel
{
	STATIC_GAME_LOD_COUNT = 6
};

extern const char *StaticGameLODNames[];

class INIException
{
public:
	INIException( Int code, const char *msg, ... );
	INIException( const INIException &other );

private:
	Int m_code;
	const char *m_msg;
};

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	static void parseStaticGameLODLevel( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseStaticGameLODLevel@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseStaticGameLODLevel( INI *ini, void *, void *store, const void * )
{
	const char *tok = ini->getNextToken();
	for( Int i = 0; i < STATIC_GAME_LOD_COUNT; i++ )
	{
		if( _stricmp( tok, StaticGameLODNames[ i ] ) == 0 )
		{
			*(StaticGameLODLevel *)store = (StaticGameLODLevel)i;
			return;
		}
	}
	throw INIException( 3, "invalid GameLODLevel token %s -- expected LOW/MEDIUM/HIGH", tok );
}
