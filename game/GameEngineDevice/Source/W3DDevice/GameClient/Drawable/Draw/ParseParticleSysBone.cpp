// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: the ParticleSysBone INI field parser, retail 0x0076E7B0, 23 bytes.
//
// The animation-state FieldParse table at 0x012BB650 pairs the string
// "ParticleSysBone" with this body, and the same table pairs "Animation" with
// the landed parseAnimation at 0x00B74FD0. Zero Hour spells the callback
// parseParticleSysBone in W3DModelDraw.cpp, where it appends to
// ModelConditionInfo::m_particleSysBones.
//
// BFME moved the work into the shared function at 0x0076E4F0, which the ledger
// pins as bfmeCallEMA. This body only forwards, handing that function the INI
// reader, the state block and the list at offset 0x50 of the state block.
// bfmeCallEMA is Zero Hour's parseParticleSysBone body (bone name, toLower,
// particle system template, push_back) plus BFME's optional FollowBone or
// HouseColor, FXTrigger, Persist and PersistID keywords.
#include "string_base.h"
#include "ascii_string.h"
#include <string.h>
#pragma intrinsic(strcmp)

// class-gate: allow INI canonical INI.h returns int from scanBool, retail's pinned symbol returns bool
class INI
{
public:
	AsciiString getNextAsciiString();
	const char *getNextToken( const char *seps );
	const char *getNextTokenOrNull( const char *seps );
	static bool scanBool( const char *token );
	static int scanInt( const char *token );
	static int scanIndexList( const char *token, const char *const *names );
	static void parseParticleSystemTemplate( INI *ini, void *instance, void *store, const void *userData );

	char m_unreconstructed[ 0x41c ];
	const char *m_seps;
};

// The list element the FXEvent parser (0x007764E0) also pushes; its _Construct
// is pinned at ILT 0x00028524.
struct Rva0076CEE0Element {
	AsciiString at00;
	bool at04;
	int at08, at0c, at10, at14, at18, at1c;
	bool at20;
	Rva0076CEE0Element() : at04( false ), at08( 0 ), at0c( 0 ), at10( 0 ), at14( 0 ), at1c( 0 ), at20( false ) {}
};
namespace _STL {
template<class T, class U> void __cdecl _Construct( T *, const U & );
inline void _Construct( Rva0076CEE0Element *destination, const Rva0076CEE0Element &value ) {
	_Construct<Rva0076CEE0Element, Rva0076CEE0Element>( destination, value );
}
}
#include <list>

extern const char *const g_rva012BB55C[];	// NONE CATAPULT_ROCK TREBUCHET_ROCK
extern const char *const g_rva012BB548[];	// NONE HOLD KILL SPAWN

struct BfmeThingEMA;
struct BfmeSubEMA;

static const char *nextToken( INI *ini ) { const char *seps = ini->m_seps; return ini->getNextTokenOrNull( seps ); }
static const char *requiredToken( INI *ini ) { const char *seps = ini->m_seps; return ini->getNextToken( seps ); }

void __cdecl bfmeCallEMA( void *a, BfmeThingEMA *b, BfmeSubEMA *s )
{
	// The volatile read loads the INI pointer in the prologue, ahead of the
	// element-ctor stores, as retail does.
	INI *ini = *(INI *volatile *)&a;
	Rva0076CEE0Element info;
	info.at18 = 0;
	info.at00 = ini->getNextAsciiString();
	info.at00.toLower();
	INI::parseParticleSystemTemplate( ini, b, &info.at1c, 0 );
	info.at04 = false;
	info.at20 = false;

	const char *token = nextToken( ini );
	if( token )
	{
		if( strcmp( token, "FollowBone" ) == 0 )
			info.at04 = INI::scanBool( requiredToken( ini ) );
		else if( strcmp( token, "HouseColor" ) == 0 )
			info.at20 = INI::scanBool( requiredToken( ini ) );
	}

	token = nextToken( ini );
	if( token && strcmp( token, "FXTrigger" ) == 0 )
	{
		token = requiredToken( ini );
		info.at08 = INI::scanIndexList( token, g_rva012BB55C );
	}
	else
		info.at08 = 0;

	token = nextToken( ini );
	if( token && strcmp( token, "Persist" ) == 0 )
	{
		token = requiredToken( ini );
		info.at10 = INI::scanIndexList( token, g_rva012BB548 );
	}
	else
		info.at10 = 0;

	token = nextToken( ini );
	if( token && strcmp( token, "PersistID" ) == 0 )
		info.at0c = INI::scanInt( requiredToken( ini ) );
	else
		info.at0c = 0;

	( (_STL::list<Rva0076CEE0Element> *)s )->push_back( info );
}

void parseParticleSysBone( INI *ini, void *instance, void *store, const void *userData )
{
	bfmeCallEMA( ini, (BfmeThingEMA *)instance, (BfmeSubEMA *)( (char *)instance + 0x50 ) );
}
