// ?parseOclEntry@Rva00251F70@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.91 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// One retail TU holds four bodies: the shared helper at 0x00251CF0 and the
// three field parsers 0x00251ED0 (token "fxlist"), 0x00251F70 ("ocl") and
// 0x00252010 ("psys").  Their literals sit in one contiguous pool at
// 0x010B24CC..0x010B2523, in the order "bone" / "'fxlist' expected" /
// "fxlist" / "'ocl' expected" / "ocl" / "'psys' expected" / "psys", which is
// what proves the single translation unit.
//
// This body compiles to 114 bytes against retail's 117.  The whole remaining
// difference is one instruction: retail cleans the call to 0x00251CF0 in the
// CALLER (add esp,4 scheduled after mov eax,[esi+0x41C]) whereas a thiscall
// member call cleans in the callee.  Retail also loads esi (ini) in the
// prologue rather than after that call.
//
// WHY.  0x00251CF0 is not a constructor with an inexpressible convention.  It
// is a FILE-STATIC helper, and MSVC 7.1 gives static callees a private
// register convention.  That needs no LTCG and is measured here: a static
// three-argument helper defined in this TU compiles the call site to
// "push <arg>; call; mov eax,[reg+0x41C]; add esp,4" - retail's exact shape,
// deferred cleanup included.  Which value lands in which register is chosen by
// the CALLEE's own allocation, so the shape can only be finished by converting
// 0x00251CF0 itself into this TU as a real static C++ function.  Its retail
// prologue (mov eax,[esi+0x41C] ... mov edi,ecx ... mov ecx,esi) says the
// convention is ecx = &store->m_fx, esi = ini, and one caller-cleaned stack
// argument = instance.  The current ledger row for 0x00251CF0 is an __emit
// thunk in its own file, and a naked body gets no private convention, so that
// row has to be repointed at the same time.
//
// RULED OUT, each measured with tools/probe.py: __fastcall varargs on a member
// (118 B, pushes this through eax) and on a free function (118 B, the same);
// an ellipsis thiscall member (pushes this); __asm at the call site (forces a
// push-ebp frame, 121 B); local-definition-order and hoisted-separator
// variants for the esi load (no effect, still 114 B).  A fake TU-local stub
// would make the bytes match while sending the call somewhere that is not
// retail, so it is not a landing.
//
// Address-derived parser names; the identity pins live in the ledger.

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
	static void parseParticleSystemTemplate( INI *ini, void *instance, void *store, const void *userData );

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
