// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct FactionVictoryParameters
{
	unsigned char m_storage[24];
};

class FactionVictoryParametersVector
{
public:
	unsigned int size( void ) const { return (unsigned int)(m_end - m_begin); }
	FactionVictoryParameters &operator[]( unsigned int index ) { return m_begin[index]; }

private:
	FactionVictoryParameters *m_begin;
	FactionVictoryParameters *m_end;
	FactionVictoryParameters *m_storageEnd;
};

class VictorySystem
{
public:
	FactionVictoryParameters *bfmeParametersForPlayer( int playerIndex );

private:
	unsigned char m_unreconstructed_00[0x24];
	int m_playerParameterIndex[(0xec - 0x24) / 4];
	FactionVictoryParametersVector m_parameters;
};

FactionVictoryParameters *VictorySystem::bfmeParametersForPlayer( int playerIndex )
{
	unsigned int parameterIndex =
		(unsigned int)m_playerParameterIndex[playerIndex] & 0x7fffffff;
	if( parameterIndex < m_parameters.size() )
	{
		return &m_parameters[parameterIndex];
	}
	return 0;
}
