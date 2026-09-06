// ?parseIntSetTokens@Rva002368C0@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME7: INI field parser at 0x002368C0 (90 B): every remaining token on
// the line (read with the plain separator set at INI+0x414) goes through the
// imported atoi and is inserted into the set<int> the store argument
// points at (STLport insert_unique on the red-black tree, its pair result
// returned through the hidden pointer).  Address-derived parser name.

#define _STLP_NO_EXCEPTIONS 1
#include <set>

extern "C" __declspec(dllimport) int __cdecl atoi( const char *text );

class INI
{
public:
	const char *getNextTokenOrNull( const char *seps );

	char m_unreconstructed[ 0x414 ];
	const char *m_seps;
};

class Rva002368C0
{
public:
	static void parseIntSetTokens( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseIntSetTokens@Rva002368C0@@SAXPAVINI@@PAX1PBX@Z
void Rva002368C0::parseIntSetTokens( INI *ini, void *, void *store, const void * )
{
	_STL::set<int> *values = (_STL::set<int> *)store;
	for( const char *token = ini->getNextTokenOrNull( ini->m_seps ); token; token = ini->getNextTokenOrNull( ini->m_seps ) )
	{
		int value = atoi( token );
		values->insert( value );
	}
}
