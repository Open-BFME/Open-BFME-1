// ?parseHordeContainUnitTypePos@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.97 date=2026-09-03
// ?parseHordeContainUnitTypePos@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.97 date=2026-09-03
// ?parseHordeContainUnitTypePos@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.97 date=2026-09-03
// ?parseBannerCarrierPosition@@YAXPAVINI@@PAX1PBX@Z
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Oi /Ireference/shims/iniexception
// stlport
// Open-BFME5: HordeContain unit-slot position field parser, retail 0x0023E280.

typedef int Int;
typedef float Real;

extern "C" int __cdecl strcmp( const char *a, const char *b );

struct Coord2D
{
	Real x;
	Real y;
};

struct Coord2DTemp
{
	Coord2D value;
	Int unused;
};

class AsciiString
{
public:
	AsciiString( const char *s );
	void set( const char *s );

private:
	void *m_data;
};

#include "Common/INIException.h"

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

struct Gen_t_0023daa0_p4pod
{
	int a[ 1 ];
};

#include <vector>

class HordeContainUnitSlot;
typedef _STL::vector<HordeContainUnitSlot *> BfmeUnitSlotVector;

class HordeContainUnitSlot
{
public:
	HordeContainUnitSlot( void ) : m_unitType( "" )
	{
		m_pos.x = 0;
		m_pos.y = 0;
	}

	AsciiString m_unitType;
	Coord2D m_pos;
};

void parseHordeContainUnitTypePos( INI *ini, void *instance, void *store,
	const void *userData )
{
	HordeContainUnitSlot *slot = new HordeContainUnitSlot;

	const char *token = ini->getNextTokenOrNull( ini->getSepsColon() );
	if ( token == 0 || strcmp( token, "UnitType" ) != 0 )
		throw INIException( 3, "UnitType expected" );

	slot->m_unitType.set( ini->getNextToken( ini->getSepsColon() ) );

	token = ini->getNextTokenOrNull( ini->getSepsColon() );
	if ( token == 0 || strcmp( token, "Pos" ) != 0 )
		throw INIException( 3, "'Pos' expected" );

	{
		Coord2DTemp temp;
		INI::parseCoord2D( ini, 0, &temp.value, 0 );
		slot->m_pos.x = temp.value.x;
		slot->m_pos.y = temp.value.y;
	}

	( (BfmeUnitSlotVector *)store )->push_back(
		slot );
}
