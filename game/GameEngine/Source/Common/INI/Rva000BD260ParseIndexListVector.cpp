// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME7: INI field parser at 0x000BD260 (107 B): every remaining token
// is resolved through INI::scanIndexList against the name table the userData
// argument points at and pushed onto the vector<Int> the store argument
// points at.  STLport exceptions off: inline push_back fast path with the
// placement copy plus the out-of-line _M_insert_overflow.  Address-derived
// parser name.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;

class INI
{
public:
	const char *getNextTokenOrNull( const char *seps = 0 );
	static Int scanIndexList( const char *token, const char *const *nameList );
};

class Rva000BD260
{
public:
	static void parseIndexListVector( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseIndexListVector@Rva000BD260@@SAXPAVINI@@PAX1PBX@Z
void Rva000BD260::parseIndexListVector( INI *ini, void *, void *store, const void *userData )
{
	_STL::vector<Int> *values = (_STL::vector<Int> *)store;
	for( const char *token = ini->getNextTokenOrNull(); token; token = ini->getNextTokenOrNull() )
	{
		Int value = INI::scanIndexList( token, (const char *const *)userData );
		values->push_back( value );
	}
}
