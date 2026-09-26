// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: parseEmotionType (retail 0x0037AD00 72 B; a gap claimed through its
// exception literal).  The next token is converted through the cdecl name
// lookup at 0x004448AF and stored into the field the store argument points at;
// a missing token throws INIException(3 "Emotion type expected.").  Address-derived names.

typedef int Int;

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
};

Int __cdecl Rva0037AD00LookupEmotionType( const char *name );

class Rva0037AD00
{
public:
	static void parseEmotionType( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseEmotionType@Rva0037AD00@@SAXPAVINI@@PAX1PBX@Z
void Rva0037AD00::parseEmotionType( INI *ini, void *, void *store, const void * )
{
	const char *token = ini->getNextToken();
	if( token )
		*(Int *)store = Rva0037AD00LookupEmotionType( token );
	else
		throw INIException( 3, "Emotion type expected." );
}
