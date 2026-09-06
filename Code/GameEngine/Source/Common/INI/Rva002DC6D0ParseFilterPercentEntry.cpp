// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME7: INI field parser at 0x002DC6D0 (174 B): an entry made of a
// 4-byte filter handle (constructor 0x003A0410 destructor 0x0039D550) and a
// Real is built on the stack the Real from INI::scanPercentToReal of the next
// token the filter through iniParseObjectFilter with the instance and the
// entry is pushed onto the vector the store argument points at (STLport
// exceptions off: inline push_back with the memberwise copy plus the
// out-of-line _M_insert_overflow at 0x002DC3D0).  Address-derived names.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef float Real;

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	static Real scanPercentToReal( const char *token );
};

void iniParseObjectFilter( INI *ini, void *instance, void *store, const void *userData );

struct Rva002DC6D0Filter
{
	Rva002DC6D0Filter();
	~Rva002DC6D0Filter();

	void *m_data;
};

struct Rva002DC6D0Entry
{
	Rva002DC6D0Filter m_filter;
	Real m_percent;
};

class Rva002DC6D0
{
public:
	static void parseFilterPercentEntry( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseFilterPercentEntry@Rva002DC6D0@@SAXPAVINI@@PAX1PBX@Z
void Rva002DC6D0::parseFilterPercentEntry( INI *ini, void *instance, void *store, const void * )
{
	Rva002DC6D0Entry entry;
	entry.m_percent = INI::scanPercentToReal( ini->getNextToken() );
	iniParseObjectFilter( ini, instance, &entry.m_filter, 0 );
	((_STL::vector<Rva002DC6D0Entry> *)store)->push_back( entry );
}
