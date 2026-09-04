// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /G6

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

struct FactionVictoryParameters
{
	unsigned char m_name[4];
	Real m_allyDeathScaleFactor;
	Real m_enemyKillScaleFactor;
	Real m_mapToCellVictoryRatio;
	Real m_victoryThreshold;
	Real m_majorUnitValue;
};

class FactionVictoryParametersVector
{
public:
	UnsignedInt size( void ) const
	{
		return (UnsignedInt)(m_end - m_begin);
	}

	FactionVictoryParameters &operator[]( UnsignedInt index )
	{
		return m_begin[index];
	}

private:
	FactionVictoryParameters *m_begin;
	FactionVictoryParameters *m_end;
	FactionVictoryParameters *m_storageEnd;
};

class VictorySystem
{
public:
	unsigned char m_unreconstructed_00[0x24];
	Int m_playerParameterIndex[(0xec - 0x24) / 4];
	FactionVictoryParametersVector m_parameters;

	FactionVictoryParameters *bfmeParametersForPlayer( Int playerIndex )
	{
		UnsignedInt parameterIndex =
			(UnsignedInt)m_playerParameterIndex[playerIndex] & 0x7fffffff;
		if( parameterIndex < m_parameters.size() )
		{
			return &m_parameters[parameterIndex];
		}
		return 0;
	}
};

extern VictorySystem *TheVictorySystem;

class BfmeCell
{
public:
	Int bfmeEvaluate( bool useCellRatio );

private:
	Real m_first[16];
	Real m_second[16];
	UnsignedInt m_firstMask;
	UnsignedInt m_secondMask;
};

Int BfmeCell::bfmeEvaluate( bool useCellRatio )
{
	Int result = 0;
	if( useCellRatio )
	{
		for( UnsignedInt playerIndex = 0; playerIndex < 16; ++playerIndex )
		{
			FactionVictoryParameters *parameters =
				TheVictorySystem->bfmeParametersForPlayer( playerIndex );
			if( m_first[playerIndex] * parameters->m_enemyKillScaleFactor -
				m_second[playerIndex] * parameters->m_allyDeathScaleFactor >
				parameters->m_victoryThreshold *
				parameters->m_mapToCellVictoryRatio )
			{
				result |= 1 << playerIndex;
			}
		}
	}
	else
	{
		for( UnsignedInt playerIndex = 0; playerIndex < 16; ++playerIndex )
		{
			FactionVictoryParameters *parameters =
				TheVictorySystem->bfmeParametersForPlayer( playerIndex );
			if( m_first[playerIndex] * parameters->m_enemyKillScaleFactor -
				m_second[playerIndex] * parameters->m_allyDeathScaleFactor >
				parameters->m_victoryThreshold )
			{
				result |= 1 << playerIndex;
			}
		}
	}
	return result;
}
