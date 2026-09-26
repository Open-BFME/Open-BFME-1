// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class BfmeCellGrid
{
public:
	void bfmeDecayCells( float firstScale, float secondScale );
};

class BfmeCell
{
public:
	void bfmeDecay( float firstScale, float secondScale );
};

class VictorySystem
{
public:
	void bfmeDecayAllCells( void );

private:
	unsigned char m_unreconstructed_00[0x14];
	float m_firstScale;
	float m_secondScale;
	unsigned char m_unreconstructed_1c[0x64 - 0x1c];
	BfmeCell m_rootCell;
	unsigned char m_unreconstructed_65[0xf8 - 0x65];
	BfmeCellGrid *m_grids[2];
};

void VictorySystem::bfmeDecayAllCells( void )
{
	BfmeCellGrid **grid = m_grids;
	int count = 2;
	do
	{
		if( *grid != 0 )
		{
			(*grid)->bfmeDecayCells( m_firstScale, m_secondScale );
		}
		++grid;
	}
	while( --count != 0 );

	m_rootCell.bfmeDecay( m_firstScale, m_secondScale );
}
