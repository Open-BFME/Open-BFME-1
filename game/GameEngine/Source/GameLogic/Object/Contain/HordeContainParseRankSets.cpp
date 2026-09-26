// ?parse_002368c0@@YAXPAVINI@@PAX1PBX@Z
// FieldParse table VA 0x010AF710 maps two rank-set fields to this parser.
// Retail RVA 0x002368C0 has a 90-byte body.
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <set>

typedef int Int;

__declspec(dllimport) int __cdecl bfmeAtoi1027( char *text );

class INI
{
public:
	const char *getNextTokenOrNull( const char *seps );
	const char *getSeps( void ) const { return m_seps; }

	char m_unreconstructed_000[ 0x414 ];
	const char *m_seps;
};

typedef _STL::set<Int> BfmeRankSet;

void parse_002368c0( INI *ini, void *, void *store, const void * )
{
	for ( const char *token = ini->getNextTokenOrNull( ini->getSeps() ); token != 0;
		token = ini->getNextTokenOrNull( ini->getSeps() ) )
	{
		( (BfmeRankSet *)store )->insert( bfmeAtoi1027( (char *)token ) );
	}
}
