// cl: /DNDEBUG /DWIN32 /MD /EHsc /Oi /Ireference/shims/iniexception
// stlport
// Open-BFME5: HordeContain split-result INI field parser, retail 0x0023E420.

typedef int Int;

extern "C" int __cdecl strcmp( const char *a, const char *b );
extern "C" __declspec(dllimport) int __cdecl atoi( const char * );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( void ) { m_data = 0; }
	void set( const char *s );

private:
	void *m_data;
};

#include "Common/INIException.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken( const char *seps );
	const char *getNextTokenOrNull( const char *seps );
	const char *getSepsColon( void ) const { return m_sepsColon; }

	char m_unreconstructed_000[ 0x41c ];
	const char *m_sepsColon;
};

class HordeContainSplitEntry;

struct Gen_t_0023da60_p4pod
{
	HordeContainSplitEntry *m_entry;
};

#include <vector>

typedef _STL::vector<Gen_t_0023da60_p4pod> BfmeSplitEntryVector;

class HordeContainSplitEntry
{
public:
	AsciiString m_splitResult;
	AsciiString m_unitType;
	Int m_rankNumber;
};

void parseHordeContainSplitResult( INI *ini, void *instance, void *store,
	const void *userData )
{
	HordeContainSplitEntry *entry = new HordeContainSplitEntry;

	Gen_t_0023da60_p4pod slot;
	slot.m_entry = entry;

	const char *token = ini->getNextTokenOrNull( ini->getSepsColon() );
	if ( token == 0 || strcmp( token, "SplitResult" ) != 0 )
		throw INIException( 3, "'Target' expected" );

	entry->m_splitResult.set( ini->getNextToken( ini->getSepsColon() ) );

	token = ini->getNextTokenOrNull( ini->getSepsColon() );
	if ( token == 0 || strcmp( token, "UnitType" ) != 0 )
		throw INIException( 3, "'Result' expected" );

	entry->m_unitType.set( ini->getNextToken( ini->getSepsColon() ) );

	token = ini->getNextTokenOrNull( ini->getSepsColon() );
	if ( token != 0 && strcmp( token, "RankNumber" ) == 0 )
		entry->m_rankNumber = atoi( ini->getNextToken( ini->getSepsColon() ) );
	else
		entry->m_rankNumber = 0;

	( (BfmeSplitEntryVector *)store )->push_back( slot );
}
