// ?parseOclEntry@Rva00252010@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: two byte-twin INI field parsers (0x00251F70 and 0x00252010,
// 117 B each, different retail TUs).  The TransitionDamageFX subobject at
// store+4 is initialised from the instance (the 374-byte body at 0x00251CF0
// ledgered as the constructor; called here as a plain member so there is no
// placement-new null check)
// then the next quoted token must be "ocl" (imported _stricmp; else
// INIException(3 "'ocl' expected")) and INI::parseObjectCreationList reads
// the list with the store as both its store and user data.  Address-derived
// parser names.

typedef int Int;

extern "C" __declspec(dllimport) int __cdecl _stricmp( const char *a, const char *b );

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
	const char *getNextToken( const char *seps );
	static void parseObjectCreationList( INI *ini, void *instance, void *store, const void *userData );

	char m_unreconstructed[ 0x414 ];
	const char *m_seps;
	const char *m_sepsColon;
	const char *m_sepsQuote;
	const char *m_sepsPercent;
};

class TransitionDamageFX
{
public:
	void init( void *owner );
};

struct Rva00251F70Owner
{
	char m_unreconstructed[ 4 ];
	TransitionDamageFX m_fx;
};

class Rva00251F70
{
public:
	static void parseOclEntry( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseOclEntry@Rva00251F70@@SAXPAVINI@@PAX1PBX@Z
void Rva00251F70::parseOclEntry( INI *ini, void *instance, void *store, const void * )
{
	((Rva00251F70Owner *)store)->m_fx.init( instance );
	const char *token = ini->getNextToken( ini->m_sepsQuote );
	if( _stricmp( token, "ocl" ) != 0 )
		throw INIException( 3, "'ocl' expected" );
	INI::parseObjectCreationList( ini, instance, store, store );
}

class Rva00252010
{
public:
	static void parseOclEntry( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseOclEntry@Rva00252010@@SAXPAVINI@@PAX1PBX@Z
void Rva00252010::parseOclEntry( INI *ini, void *instance, void *store, const void * )
{
	((Rva00251F70Owner *)store)->m_fx.init( instance );
	const char *token = ini->getNextToken( ini->m_sepsQuote );
	if( _stricmp( token, "ocl" ) != 0 )
		throw INIException( 3, "'ocl' expected" );
	INI::parseObjectCreationList( ini, instance, store, store );
}
