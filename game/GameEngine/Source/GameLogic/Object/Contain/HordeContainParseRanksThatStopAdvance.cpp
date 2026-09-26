// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: HordeContain RanksThatStopAdvance INI field parser, retail
// 0x00236930, 99 bytes.
//
// The FieldParse table at 0x010AF710 pairs the string "RanksThatStopAdvance"
// with ILT 0x00028BF0, which jumps to this body, and writes member offset
// 0x24C. The same table registers "SplitHorde" against the landed
// parseHordeContainSplitResult at 0x0023E420, so the table belongs to the
// HordeContain module data. INI member +0x414 is m_seps, the plain separator
// set, which Zero Hour orders ahead of m_sepsPercent, m_sepsColon and
// m_sepsQuote.
//
// The loop reads tokens until getNextTokenOrNull returns null and appends each
// one to an STLport list of Int. Each 12-byte node comes from the default node
// allocator at 0x0082E540, the same allocator the landed
// Rva0037F740ListPushBack body uses.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;

__declspec(dllimport) int __cdecl bfmeAtoi1027( char *text );

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextTokenOrNull( const char *seps );
	const char *getSeps( void ) const { return m_seps; }

	char m_unreconstructed_000[ 0x414 ];
	const char *m_seps;
};

typedef _STL::list<Int> BfmeRankList;

void parseHordeContainRanksThatStopAdvance( INI *ini, void *instance, void *store,
	const void *userData )
{
	for ( const char *token = ini->getNextTokenOrNull( ini->getSeps() ); token != 0;
		token = ini->getNextTokenOrNull( ini->getSeps() ) )
	{
		( (BfmeRankList *)store )->push_back( bfmeAtoi1027( (char *)token ) );
	}
}
