// ?reset@VictorySystem@@UAEXXZ
// partial score=0.94 date=2026-08-28
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

class BfmeCellGrid
{
public:
	void _bfme_reset( void );
	~BfmeCellGrid();
};

class VictorySystem
{
public:
	virtual void init( void );
	virtual void reset( void );
	FactionVictoryParameters *_bfme_findOrCreateFactionVictoryParameters(
		const AsciiString &name );

private:
	unsigned int _bfme_findFactionVictoryParametersIndex( const AsciiString &name );

	char m_opaque04[0x0c];
	unsigned int m_field10;
	char m_opaque14[0x50];
	unsigned int m_values64[16];
	unsigned int m_valuesA4[16];
	unsigned int m_fieldE4;
	unsigned int m_fieldE8;
	_STL::vector<FactionVictoryParameters> m_factionVictoryParameters;
	BfmeCellGrid *m_cellGrids[2];
	bool m_initialized;
	char m_alignment[3];
	unsigned int m_activeGrid;
	unsigned int m_currentPlayer;
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

void VictorySystem::reset( void )
{
	for( unsigned int index = 0; index < 2; ++index )
	{
		if( m_cellGrids[index] )
		{
			m_cellGrids[index]->_bfme_reset();
			delete m_cellGrids[index];
			m_cellGrids[index] = 0;
		}
	}

	m_activeGrid = 2;
	m_currentPlayer = 0;
	m_field10 = 0;
	for( unsigned int index = 0; index < 16; ++index )
	{
		m_valuesA4[index] = 0;
		m_values64[index] = 0;
	}
	m_fieldE8 = 0;
	m_fieldE4 = 0;
	m_initialized = false;
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
