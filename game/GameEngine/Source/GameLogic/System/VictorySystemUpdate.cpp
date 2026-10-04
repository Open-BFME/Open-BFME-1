// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// VictorySystem::update (vtable 0x0109FD8C slot 5; GameLogic update caller at
// 0x0038DC4D). Retail inlines the active-grid pass whose standalone copy is
// 0x001DF850, so that pass is defined here ahead of update.
//
// This TU owns the landed 0x001DE880 parameter lookup. Keeping its body
// visible lets VC7.1 see that it writes no memory. Both per-case grid calls read
// +0x108 once, cross-jump into one call block, and keep retail's EBX/EDI saves
// ahead of the switch. Declared only, the two calls stay separate.

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

class BfmeCellGrid
{
public:
	void rva001B1AD0( int playerIndex, void *parameters );
};

class VictorySystem
{
public:
	virtual void init( void );
	virtual void update( void );

	FactionVictoryParameters *bfmeParametersForPlayer( int playerIndex );
	void bfmeApplyWinningCells( void );
	void bfmeDecayAllCells( void );
	void rva001DF850( void );

private:
	unsigned char m_unreconstructed_04[0x24 - 4];
	int m_playerParameterIndex[(0xec - 0x24) / 4];
	FactionVictoryParametersVector m_parameters;
	BfmeCellGrid *m_cellGrids[2];
	bool m_initialized;
	unsigned char m_pad101[3];
	unsigned int m_activeGrid;
	int m_currentPlayer;
};

inline FactionVictoryParameters *VictorySystem::bfmeParametersForPlayer( int playerIndex )
{
	unsigned int parameterIndex =
		(unsigned int)m_playerParameterIndex[playerIndex] & 0x7fffffff;
	if( parameterIndex < m_parameters.size() )
	{
		return &m_parameters[parameterIndex];
	}
	return 0;
}

void VictorySystem::rva001DF850( void )
{
	switch( m_activeGrid )
	{
		case 0:
			if( !m_cellGrids[0] )
				return;
			m_cellGrids[0]->rva001B1AD0( m_currentPlayer, bfmeParametersForPlayer( m_currentPlayer ) );
			break;
		case 1:
			if( !m_cellGrids[1] )
				return;
			m_cellGrids[1]->rva001B1AD0( m_currentPlayer, bfmeParametersForPlayer( m_currentPlayer ) );
			break;
	}
}

void VictorySystem::update( void )
{
	if( !m_initialized )
		return;

	rva001DF850();
	bfmeApplyWinningCells();
	bfmeDecayAllCells();
}
