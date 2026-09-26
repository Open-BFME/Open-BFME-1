// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: INI field parser at 0x002542F0 (151 B): the token becomes an
// Rva002542F0String pushed onto the list<Rva002542F0String> member at instance+0x34.
// STLport exceptions off (inline push_back: node from the static-lib node
// allocator then the placement copy under the EH state the string copy
// constructor still gets) with the allocator reached directly.
// The string class carries an address-derived name so its out-of-line copy
// constructor pins to the 0x00887B60 body without colliding with the
// AsciiString name (whose thunk pin points at a different-size copy).

#define _STLP_NO_EXCEPTIONS 1
#include <list>

class Rva002542F0String
{
public:
	Rva002542F0String( const char *text );
	Rva002542F0String( const Rva002542F0String &other );
	~Rva002542F0String() { releaseBuffer(); }

private:
	void releaseBuffer( void );
	void *m_data;
};

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
};

struct Rva002542F0Owner
{
	char m_unreconstructed[ 0x34 ];
	_STL::list<Rva002542F0String> m_names;
};

class Rva002542F0
{
public:
	static void parseStringListEntry( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseStringListEntry@Rva002542F0@@SAXPAVINI@@PAX1PBX@Z
void Rva002542F0::parseStringListEntry( INI *ini, void *instance, void *, const void * )
{
	Rva002542F0String name( ini->getNextToken() );
	((Rva002542F0Owner *)instance)->m_names.push_back( name );
}
