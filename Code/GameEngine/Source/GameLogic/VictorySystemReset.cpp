// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
// stlport

class BfmeCellGrid
{
public:
	void _bfme_reset( void );
	~BfmeCellGrid();
};

class VictorySystem
{
public:
	virtual void reset( void );

private:
	char m_opaque04[0x0c];
	unsigned int m_field10;
	char m_opaque14[0x50];
	volatile unsigned int m_values64[16];
	volatile unsigned int m_valuesA4[16];
	unsigned int m_fieldE4;
	unsigned int m_fieldE8;
	char m_opaqueEC[0x0c];
	BfmeCellGrid *m_cellGrids[2];
	bool m_initialized;
	char m_alignment[3];
	unsigned int m_activeGrid;
	unsigned int m_currentPlayer;
};

void VictorySystem::reset( void )
{
	VictorySystem *self = this;
	BfmeCellGrid **grid = self->m_cellGrids;
	for( unsigned int index = 0; index < 2; ++index )
	{
		if( *grid )
		{
			(*grid)->_bfme_reset();
			delete *grid;
			*grid = 0;
		}
		++grid;
	}

	self->m_activeGrid = 2;
	self->m_currentPlayer = 0;
	self->m_field10 = 0;
	volatile unsigned int *valuesA4 = self->m_valuesA4;
	unsigned int *fieldE8 = &self->m_fieldE8;
	unsigned int *fieldE4 = &self->m_fieldE4;
	for( unsigned int index = 0; index < 16; ++index )
	{
		valuesA4[index] = 0;
		valuesA4[index - 16] = 0;
	}
	*fieldE8 = 0;
	*fieldE4 = 0;
	self->m_initialized = false;
}
