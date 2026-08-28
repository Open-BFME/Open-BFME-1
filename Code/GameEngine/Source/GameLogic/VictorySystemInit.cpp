// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
// stlport

#include <vector>
#include "string_base.h"

extern "C" __declspec(dllimport) int __cdecl _memicmp( const void *left,
	const void *right, unsigned int count );

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

	int compareNoCase( const AsciiString &that ) const
	{
		const int length = that.m_data ? that.m_data->m_length : 0;
		const char *data = that.m_data ? (const char *)(that.m_data + 1) : "";
		return compareNoCase( data, length );
	}

private:
	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
	};

	int compareNoCase( const char *text, int length ) const
	{
		const int thisLength = m_data ? m_data->m_length : 0;
		const char *data = m_data ? (const char *)(m_data + 1) : "";
		int difference = _memicmp( data, text,
			thisLength < length ? thisLength : length );
		if( difference != 0 )
		{
			return difference;
		}
		return thisLength - length;
	}

	Header *m_data;
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
	FactionVictoryParameters *_bfme_findOrCreateFactionVictoryParameters(
		const AsciiString &name );

private:
	unsigned int _bfme_findFactionVictoryParametersIndex( const AsciiString &name );

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

FactionVictoryParameters *VictorySystem::_bfme_findOrCreateFactionVictoryParameters(
	const AsciiString &name )
{
	unsigned int index = _bfme_findFactionVictoryParametersIndex( name );
	if( index != 0x7fffffff )
	{
		return &m_factionVictoryParameters[index];
	}

	{
		FactionVictoryParameters parameters( name );
		m_factionVictoryParameters.push_back( parameters );
	}
	return &m_factionVictoryParameters.back();
}

unsigned int VictorySystem::_bfme_findFactionVictoryParametersIndex(
	const AsciiString &name )
{
	bool found = false;
	unsigned int result = 0x7fffffff;
	for( unsigned int index = 0;
		index < m_factionVictoryParameters.size() && !found;
		++index )
	{
		if( m_factionVictoryParameters[index].m_name.compareNoCase( name ) == 0 )
		{
			result = index;
			found = true;
		}
	}
	return result;
}
