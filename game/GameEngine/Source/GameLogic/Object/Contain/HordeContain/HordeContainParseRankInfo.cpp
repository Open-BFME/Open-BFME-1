// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/iniexception
// stlport
// HordeContainModuleData::parseRankInfo, the "RankInfo" FieldParse callback:
// the HordeContain field table at VA 0x010AF710 pairs RankInfo (row VA
// 0x010AF720) with this body. EA's evidence names it (chain+direct, strong)
// and places it in HordeContain.cpp; ilt_oracle CONFIRMS the public static
// decoration at its ILT 0x00049BE8.

#include "../../../../../Include/Common/ScalarTypes.h"



#include "ascii_string.h"
#include "Common/INIException.h"
#include <string.h>
#include <stdlib.h>
#include <new>
#include <vector>

#define __PRERTS_H__
#include "../WWMath/coord.h"
#undef __PRERTS_H__

class INI
{
public:
	const char *getNextToken( const char *seps );
	const char *getNextTokenOrNull( const char *seps );
	const char *getSepsColon( void ) const { return m_sepsColon; }
	static void parseCoord2D( INI *ini, void *instance, void *store, const void *userData );
	static void parseReal( INI *ini, void *instance, void *store, const void *userData );

	char m_unreconstructed_000[ 0x41c ];
	const char *m_sepsColon;
};

struct Rva00244B10ConditionBits
{
	unsigned int m_bits;

	Rva00244B10ConditionBits() : m_bits( 0 ) {}
	void clear() { m_bits = 0; }
};

// ilt_oracle confirms the push_back below at ILT 0x00046907 (the only callers
// are this body's two calls) as vector<HordeContainModuleData::HordeRankInfo *>.
class HordeContainModuleData
{
public:
	static void parseRankInfo( INI *ini, void *instance, void *store, const void *userData );

	class HordeRankInfo
	{
	public:
		HordeRankInfo()
		{
			m_rankNumber = 0;
			m_hasWeaponCondition = false;
			m_grantedWeaponCondition.clear();
			m_revokedWeaponCondition.clear();
		}

		Int m_rankNumber;
		AsciiString m_unitType;
		_STL::vector<Coord3D> m_positions;
		Rva00244B10ConditionBits m_grantedWeaponCondition;
		Rva00244B10ConditionBits m_revokedWeaponCondition;
		Bool m_hasWeaponCondition;
	};
};

// The weapon-condition list parser. The ledger declares three parameters;
// retail calls it as a FieldParse (ini, 0, store, 0), four cdecl arguments.
class Gen008509C0;
class Gen00049A2B;
void __cdecl Rva001EB560( Gen008509C0 *, Int, Gen00049A2B * );
typedef void ( __cdecl *Rva001EB560FieldParse )( INI *, void *, void *, const void * );

extern Real normalizeAngle( Real angle );

#define TWO_PI 6.28318530718f

// Reads RankNumber, UnitType, then Position [Z] / Facing entries and an
// optional Granted/RevokedWeaponCondition, and appends the rank to the vector
// at store.
void HordeContainModuleData::parseRankInfo( INI *ini, void *instance, void *store, const void *userData )
{
	HordeContainModuleData::HordeRankInfo *info = new HordeContainModuleData::HordeRankInfo;

	const char *token = ini->getNextTokenOrNull( ini->getSepsColon() );
	if ( token == 0 || strcmp( token, "RankNumber" ) != 0 )
		throw INIException( 3, "RankNumber expected" );
	info->m_rankNumber = atoi( ini->getNextToken( ini->getSepsColon() ) );

	token = ini->getNextTokenOrNull( ini->getSepsColon() );
	if ( token == 0 || strcmp( token, "UnitType" ) != 0 )
		throw INIException( 3, "UnitType expected" );
	info->m_unitType = ini->getNextToken( ini->getSepsColon() );

	token = ini->getNextTokenOrNull( ini->getSepsColon() );
	while ( token != 0 )
	{
		if ( strcmp( token, "Position" ) == 0 )
		{
			Coord2D position;
			INI::parseCoord2D( ini, 0, &position, 0 );
			Coord3D position3D;
			position3D.x = position.x;
			position3D.y = position.y;
			position3D.z = 0;
			info->m_positions.push_back( position3D );
			token = ini->getNextTokenOrNull( ini->getSepsColon() );
			if ( token == 0 )
				break;
			if ( strcmp( token, "Z" ) == 0 )
				token = ini->getNextTokenOrNull( ini->getSepsColon() );
		}
		else if ( strcmp( token, "Facing" ) == 0 )
		{
			Real facing;
			INI::parseReal( ini, 0, &facing, 0 );
			facing *= 1.0f / 360.0f;
			facing *= TWO_PI;
			Int last = info->m_positions.size() - 1;
			info->m_positions[ last ].z = normalizeAngle( facing );
			token = ini->getNextTokenOrNull( ini->getSepsColon() );
		}
		else if ( strcmp( token, "GrantedWeaponCondition" ) == 0 )
		{
			info->m_hasWeaponCondition = true;
			( (Rva001EB560FieldParse)Rva001EB560 )( ini, 0, &info->m_grantedWeaponCondition, 0 );
			break;
		}
		else if ( strcmp( token, "RevokedWeaponCondition" ) == 0 )
		{
			info->m_hasWeaponCondition = true;
			( (Rva001EB560FieldParse)Rva001EB560 )( ini, 0, &info->m_revokedWeaponCondition, 0 );
			break;
		}
		else
		{
			throw INIException( 3, "'Position' expected" );
		}
	}
	( (_STL::vector<HordeContainModuleData::HordeRankInfo *> *)store )->push_back( info );
}
