// ?parseBuffNuggetBone@Rva00773170@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.4 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc

// Open-BFME7: INI field parser at 0x00773170 (204 B). Bails if instance is
// null; reads a bone-name token (getNextTokenOrNull with the INI's own
// separators at +0x41c, discarded past the null check), a second token
// (the string later pushed into the member's vector), looks the second
// token up through the global function pointer g_lookup (VA 0x0135933C)
// against the literal "ExtraMesh" (VA 0x1123C5C) and bails unless it
// returns 0, then reads a third token and scans it as a Bool: false runs
// BuffNuggetFXNuggetMember::assign (thunk 0x00024C17, this at
// instance+0x28) before appending; true skips assign. The second token is
// then push_back'ed into the vector<AsciiString> the pinned thunk
// 0x00032317 already matches, at the same instance+0x28 member. Names and
// exact member semantics are address-derived; not yet byte-verified.

typedef int Int;
typedef bool Bool;

class INI
{
public:
	char m_pad[ 0x41c ];
	const char *m_seps;

	const char *getNextTokenOrNull( const char *seps );
	static Bool scanBool( const char *token );
};

typedef void *(__cdecl *LookupFn)( void *, void * );
extern LookupFn g_lookup;

class AsciiString
{
public:
	AsciiString( const char *s );
	~AsciiString();
};

class BuffNuggetFXNuggetMember
{
public:
	void assign( void *a, void *b );
	void pushBoneName( const AsciiString &name );
};

class Rva00773170Store
{
public:
	char m_pad[ 0x28 ];
	BuffNuggetFXNuggetMember m_member;			// +0x28
};

class Rva00773170
{
public:
	static void parseBuffNuggetBone( INI *ini, void *instance, void *, const void * );
};

// ?parseBuffNuggetBone@Rva00773170@@SAXPAVINI@@PAX1PBX@Z
void Rva00773170::parseBuffNuggetBone( INI *ini, void *instance, void *, const void * )
{
	Rva00773170Store *self = (Rva00773170Store *)instance;
	if( self == 0 )
		return;

	const char *boneToken = ini->getNextTokenOrNull( ini->m_seps );
	if( boneToken == 0 )
		return;

	const char *meshToken = ini->getNextTokenOrNull( ini->m_seps );
	if( meshToken == 0 )
		return;

	if( g_lookup( (void *)meshToken, (void *)"ExtraMesh" ) != 0 )
		return;

	const char *boolToken = ini->getNextTokenOrNull( ini->m_seps );
	if( boolToken == 0 )
		return;

	if( !INI::scanBool( boolToken ) )
	{
		self->m_member.assign( &self->m_member, &self->m_member );
	}

	self->m_member.pushBoneName( AsciiString( meshToken ) );
}
