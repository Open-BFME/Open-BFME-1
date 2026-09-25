// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// VictorySystem::update (vtable 0x0109FD8C slot 5; GameLogic update caller at
// 0x0038DC4D). Retail inlines the active-grid pass whose standalone copy is
// 0x001DF850, so that pass is defined here ahead of update.
//
// The parameter lookup below is the landed 0x001DE880 body
// (VictorySystemParametersForPlayer.cpp), repeated so VC7.1 can see that it
// writes no memory. With it visible, both per-case grid calls read
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
	BfmeCellGrid *m_gridF8[2];
	bool m_byte100;
	unsigned char m_pad101[3];
	unsigned int m_dword104;
	int m_dword108;
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

// ?rva001DF850@VictorySystem@@QAEXXZ present-unmatched
void VictorySystem::rva001DF850( void )
{
	switch( m_dword104 )
	{
		case 0:
			if( m_gridF8[0] )
				m_gridF8[0]->rva001B1AD0( m_dword108, bfmeParametersForPlayer( m_dword108 ) );
			break;
		case 1:
			if( m_gridF8[1] )
				m_gridF8[1]->rva001B1AD0( m_dword108, bfmeParametersForPlayer( m_dword108 ) );
			break;
	}
}

void VictorySystem::update( void )
{
	if( !m_byte100 )
		return;

	rva001DF850();
	bfmeApplyWinningCells();
	bfmeDecayAllCells();
}
