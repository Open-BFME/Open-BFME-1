// cl: /DNDEBUG /DWIN32 /MD /EHsc /Oi /Iinputs/reference/shims/iniexception
// stlport
// Open-BFME5: HordeContain BannerCarrierPosition INI field parser, retail
// 0x0023E280. The HordeContain FieldParse table at 0x010AF710 pairs the
// 'BannerCarrierPosition' key with ILT 0x00028EF2, which jumps here; the same
// table pairs 'SplitHorde' with parseHordeContainSplitResult (0x0023E420).
//
// The entry takes a 'UnitType' name and a 'Pos' Coord2D. Retail packs the
// 'UnitType expected' exception temporary onto the Coord2D slot and gives the
// 'Pos' exception its own slot, which is what the guard-then-success-block
// spelling below produces: the Coord2D lives only in the success block that
// returns, and the 'Pos' throw sits after it.
// Full body extent is 328 bytes: the former 327-byte generated claim omitted
// the last byte of the final _CxxThrowException call displacement.

typedef float Real;

extern "C" int __cdecl strcmp( const char *a, const char *b );

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *s );
	void set( const char *s );

private:
	void *m_data;
};

#include "Common/INIException.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken( const char *seps );
	const char *getNextTokenOrNull( const char *seps );
	const char *getSepsColon( void ) const { return m_sepsColon; }
	static void parseCoord2D( INI *ini, void *instance, void *store, const void *userData );

	char m_unreconstructed_000[ 0x41c ];
	const char *m_sepsColon;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord2D
{
	Real x;
	Real y;
};

class BannerCarrierPosition;

struct Gen_t_0023daa0_p4pod
{
	BannerCarrierPosition *m_entry;
};

#include <vector>

typedef _STL::vector<Gen_t_0023daa0_p4pod> BfmeBannerCarrierPositionVector;

class BannerCarrierPosition
{
public:
	BannerCarrierPosition( void ) : m_unitType( "" )
	{
		m_pos.x = 0;
		m_pos.y = 0;
	}

	AsciiString m_unitType;
	Coord2D m_pos;
};

void parseBannerCarrierPosition( INI *ini, void *instance, void *store,
	const void *userData )
{
	Gen_t_0023daa0_p4pod slot;
	slot.m_entry = new BannerCarrierPosition;

	const char *token = ini->getNextTokenOrNull( ini->getSepsColon() );
	if ( token == 0 || strcmp( token, "UnitType" ) != 0 )
		throw INIException( 3, "UnitType expected" );

	slot.m_entry->m_unitType.set( ini->getNextToken( ini->getSepsColon() ) );

	token = ini->getNextTokenOrNull( ini->getSepsColon() );
	if ( token != 0 && strcmp( token, "Pos" ) == 0 )
	{
		Coord2D pos;
		INI::parseCoord2D( ini, 0, &pos, 0 );
		slot.m_entry->m_pos = pos;
		( (BfmeBannerCarrierPositionVector *)store )->push_back( slot );
		return;
	}
	throw INIException( 3, "'Pos' expected" );
}
