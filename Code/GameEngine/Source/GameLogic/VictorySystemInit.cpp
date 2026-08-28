// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
// stlport

#include <vector>
#include "string_base.h"

class AsciiString
{
public:
	AsciiString( const char *text )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase( text );
	}

	AsciiString( const AsciiString &that )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that );
	}

	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

private:
	char *m_data;
};

struct FactionVictoryParameters
{
	FactionVictoryParameters( const AsciiString &name ) :
		m_name( name ),
		m_allyDeathScaleFactor( 0.0f ),
		m_enemyKillScaleFactor( 0.0f ),
		m_mapToCellVictoryRatio( 0.0f ),
		m_victoryThreshold( 0.0f ),
		m_majorUnitValue( 0.0f )
	{
	}

	AsciiString m_name;
	float m_allyDeathScaleFactor;
	float m_enemyKillScaleFactor;
	float m_mapToCellVictoryRatio;
	float m_victoryThreshold;
	float m_majorUnitValue;
};

class VictorySystem
{
public:
	virtual void init( void );

private:
	char m_opaque[0xe8];
	_STL::vector<FactionVictoryParameters> m_factionVictoryParameters;
};

void VictorySystem::init( void )
{
	FactionVictoryParameters parameters( AsciiString( "Default" ) );
	parameters.m_allyDeathScaleFactor = 1.0f;
	parameters.m_enemyKillScaleFactor = 1.0f;
	parameters.m_majorUnitValue = 10.0f;
	parameters.m_victoryThreshold = 500.0f;
	parameters.m_mapToCellVictoryRatio = 1.0f;
	m_factionVictoryParameters.push_back( parameters );
}
