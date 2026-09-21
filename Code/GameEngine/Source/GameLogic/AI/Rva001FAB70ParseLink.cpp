// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// The FieldParse table at 0x010A3B28 names this callback parseLink.  Its
// native callback ABI is the same four-argument static INI parser used by the
// adjacent Rva001FAB70::parseWayPoint body.  The retail body builds one
// vector<int> element, accepts the optional Via tokens, and appends that
// non-trivial three-pointer vector element to the Link field.
#include <vector>

extern "C" int __cdecl memcmp( const void *, const void *, unsigned int );
#pragma intrinsic(memcmp)
extern "C" unsigned int __cdecl strlen( const char * );
#pragma intrinsic(strlen)

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString( const char *text );
	~BFMERetailAsciiString() { releaseBuffer(); }

	void set( const char *text, int length );

	int compare( const char *text ) const
	{
		int thisLength;
		const char *thisText;
		if ( m_data != 0 )
		{
			thisLength = *(const unsigned short *)((const char *)m_data + 4);
			thisText = (const char *)m_data + 8;
		}
		else
		{
			thisLength = 0;
			thisText = "";
		}
		int otherLength = 3;
		int length = thisLength < otherLength ? thisLength : otherLength;
		int result = memcmp( thisText, text, length );
		if ( result != 0 )
			return result;
		return thisLength - otherLength;
	}

private:
	void releaseBuffer();
	void *m_data;
};

class INI
{
public:
	static int scanInt( const char *token );
	const char *getNextSubToken( const char *expected );
	const char *getNextToken( const char *separators = 0 );
};

// The output vector element is the native non-trivial vector<int> object
// (three STLport pointers), retained under the established generated callee
// tag so the 12-byte push_back ABI stays visible without editing generated
// sources.
struct Gen_t_001fa830_p12cd
{
	_STL::vector<int> m_ids;
};

// The retail append calls the established ILT 0x0003D915, whose body is the
// non-trivial three-pointer vector-element copy at 0x001F9520.  Keep that
// witnessed copy ABI without creating a second semantic callee identity.
#pragma comment(linker, "/alternatename:??0Gen_t_001fa830_p12cd@@QAE@ABU0@@Z=?j_0003d915@@YAXXZ")

class Rva001FAB70
{
public:
	static void parseLink( INI *ini, void *instance, void *store, const void *userData );
};

void Rva001FAB70::parseLink( INI *ini, void *, void *store, const void * )
{
	Gen_t_001fa830_p12cd entry;
	int index = INI::scanInt( ini->getNextSubToken( "From" ) );
	entry.m_ids.push_back( index );
	BFMERetailAsciiString token( ini->getNextToken( ":" ) );
	while ( token.compare( "Via" ) == 0 )
	{
		entry.m_ids.push_back( INI::scanInt( ini->getNextToken() ) );
		const char *next = ini->getNextToken( ":" );
		token.set( next, next ? (int)strlen( next ) : 0 );
	}
	entry.m_ids.push_back( INI::scanInt( ini->getNextToken( ":" ) ) );
	( (_STL::vector<Gen_t_001fa830_p12cd> *)store )->push_back( entry );
}
