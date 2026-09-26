// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Four INI field parsers -- the functions that read one .ini field and store it.
// These are the modding interface: every stat in an .ini file arrives through a
// function of this shape, INI::parseX(INI *, void *instance, void *store,
// const void *userData).
//
// They were four files, and their accounts of INI contradicted each other on
// something a reader would want to trust. parseNonNegativeReal reads the token
// separators straight out of the object at +0x414. bfmeParseUpgradeWithDelay
// reads them through getSeparators(), which returns the member at +0x41C. Both
// bodies byte-verify, so both loads are real: BFME's INI carries TWO separator
// pointers, eight bytes apart, and neither file on its own could say so. The
// merged declaration states both and names the gap between them.
//
// parseStaticGameLODLevel's file declared INI with no members at all, which is
// how a third account of the same class could sit beside the other two without
// anything noticing.

typedef int Int;
typedef float Real;

extern "C" __declspec(dllimport) char *__cdecl strtok( char *s, const char *delim );
extern "C" __declspec(dllimport) int __cdecl _stricmp( const char *a, const char *b );
extern "C" __declspec(dllimport) double __cdecl ceil( double value );
extern "C" int __cdecl strcmp( const char *left, const char *right );

enum StaticGameLODLevel
{
	STATIC_GAME_LOD_COUNT = 6
};

extern const char *StaticGameLODNames[];
extern const Real BfmeZeroRange;

class INIException
{
public:
	INIException( Int code, const char *msg, ... );
	INIException( const INIException &other );

private:
	Int m_code;
	const char *m_msg;
};

#include "ascii_string.h"

class UpgradeTemplate;

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade( const AsciiString &name ) const;
};

extern UpgradeCenter *TheUpgradeCenter;

struct UpgradeWithDelay
{
	const UpgradeTemplate *m_upgrade;
	unsigned int m_delay;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	const char *getNextTokenOrNull( const char *seps );
	const char *getNextTokenOrNull( void )
	{
		return getNextTokenOrNull( getSeparators() );
	}
	const char *getSeparators( void ) const { return m_separators; }

	static Real scanReal( const char *token );
	static unsigned int scanUnsignedInt( const char *token );

	static void parseNonNegativeReal( INI *ini, void *instance, void *store, const void *userData );
	static void parseNonPositiveReal( INI *ini, void *instance, void *store, const void *userData );
	static void parseStaticGameLODLevel( INI *ini, void *instance, void *store, const void *userData );
	static void bfmeParseUpgradeWithDelay( INI *ini, void *instance, void *store, const void *userData );

	unsigned char m_unreconstructed[ 0x414 ];
	const char *m_seps;					// +0x414, read directly by the real parsers
	unsigned char m_unreconstructed418[ 0x41C - 0x418 ];
	const char *m_separators;				// +0x41C, what getSeparators() returns
};

// Open-BFME7: two INI real parsers claimed from the gap after
// parsePositiveNonZeroReal (retail 0x00852C10 and 0x00852CA0 144 B each).
// Both read the next token with BFME's inline getNextToken (imported strtok on
// the separator set at +0x414 and INIException(3 "Expected additional data
// after '%s'" seps) when the line is exhausted) scan it with INI::scanReal
// store it and then throw INIException(3 msg (double)value) when the sign is
// wrong: Zero Hour's parseNonNegativeReal rejects values below zero and the
// BFME-only parseNonPositiveReal rejects values above zero.

// ?parseNonNegativeReal@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseNonNegativeReal( INI *ini, void *, void *store, const void * )
{
	const char *seps = ini->m_seps;
	const char *token = strtok( 0, seps );
	if( !token )
		throw INIException( 3, "Expected additional data after '%s'", seps );
	Real value = INI::scanReal( token );
	*(Real *)store = value;
	if( value < BfmeZeroRange )
		throw INIException( 3, "invalid Real value %1.7f -- expected >= 0", value );
}

// ?parseNonPositiveReal@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseNonPositiveReal( INI *ini, void *, void *store, const void * )
{
	const char *seps = ini->m_seps;
	const char *token = strtok( 0, seps );
	if( !token )
		throw INIException( 3, "Expected additional data after '%s'", seps );
	Real value = INI::scanReal( token );
	*(Real *)store = value;
	if( value > BfmeZeroRange )
		throw INIException( 3, "invalid Real value %1.7f -- expected <= 0", value );
}

// Open-BFME7: INI::parseStaticGameLODLevel (retail 0x0007BCF0 105 B; a gap
// claimed through its exception literal).  Zero Hour's body: the token is
// matched case-insensitively (imported _stricmp) against the six
// StaticGameLODNames and its index stored else INIException(3 "invalid
// GameLODLevel token %s -- expected LOW/MEDIUM/HIGH") is thrown; retail places
// the matching store after the throw block.

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

// ?bfmeParseUpgradeWithDelay@INI@@SAXPAV1@PAX1PBX@Z
void INI::bfmeParseUpgradeWithDelay( INI *ini, void *, void *store,
	const void * )
{
	const char *name = ini->getNextToken( 0 );
	if( TheUpgradeCenter == 0 )
		return;

	UpgradeWithDelay *value = static_cast<UpgradeWithDelay *>( store );
	{
		AsciiString key( name );
		value->m_upgrade = TheUpgradeCenter->findUpgrade( key );
	}

	const char *option = ini->getNextTokenOrNull();
	if( option != 0 && strcmp( option, "Delay" ) == 0 )
	{
		const char *delay = ini->getNextToken( 0 );
		if( delay != 0 )
		{
			unsigned int rawDelay = scanUnsignedInt( delay );
			value->m_delay = static_cast<unsigned short>(
				ceil( static_cast<double>( rawDelay * 0.005f ) ) );
		}
	}
}
