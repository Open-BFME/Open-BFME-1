// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME7: INI field parser at 0x002D4AA0 (74 B): scans one percent-or-real
// token through INI::parsePercentToReal into a Real local and pushes it onto
// the vector<Real> the store argument points at.  Built with STLport
// exceptions off (inline push_back fast path with the placement copy and the
// out-of-line _M_insert_overflow slow path).  The parser name is
// address-derived.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef float Real;

class INI
{
public:
	static void parsePercentToReal( INI *ini, void *instance, void *store, const void *userData );
};

class Rva002D4AA0
{
public:
	static void parsePercentVectorEntry( INI *ini, void *instance, void *store, const void *userData );
};

// ?parsePercentVectorEntry@Rva002D4AA0@@SAXPAVINI@@PAX1PBX@Z
void Rva002D4AA0::parsePercentVectorEntry( INI *ini, void *, void *store, const void * )
{
	Real value;
	INI::parsePercentToReal( ini, 0, &value, 0 );
	((_STL::vector<Real> *)store)->push_back( value );
}
