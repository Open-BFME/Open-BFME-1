// ?update@VictorySystem@@UAEXXZ
// partial score=0.94 date=2026-09-02
// cl: /DNDEBUG /MD /EHs-c-
// VictorySystem::update. Initialized flag at +0x100, grids at +0xF8/+0xFC,
// active-grid selector at +0x104, current player at +0x108.

struct FactionVictoryParameters;

class BfmeCellGrid
{
public:
	void _bfme_update(unsigned int playerIndex, FactionVictoryParameters *parameters);
};

class VictorySystem
{
public:
	virtual void init(void);
	virtual void update(void);

private:
	FactionVictoryParameters *_bfme_getFactionVictoryParametersForPlayer(unsigned int playerIndex);
	void _bfme_updateVictoryState(void);
	void _bfme_updateCellGrids(void);

	unsigned char m_unreconstructed_04[0xF8 - 4];
	BfmeCellGrid *m_cellGrids[2];
	bool m_initialized;
	unsigned char m_alignment[3];
	unsigned int m_activeGrid;
	unsigned int m_currentPlayer;
};

void VictorySystem::update(void)
{
	if (!m_initialized)
		return;

	unsigned int playerIndex;
	BfmeCellGrid *grid;
	switch (m_activeGrid)
	{
		case 0:
			grid = m_cellGrids[0];
			break;
		case 1:
			grid = m_cellGrids[1];
			break;
		default:
			grid = 0;
			break;
	}

	if (grid)
	{
		playerIndex = m_currentPlayer;
		grid->_bfme_update(playerIndex,
			_bfme_getFactionVictoryParametersForPlayer(playerIndex));
	}

	_bfme_updateVictoryState();
	_bfme_updateCellGrids();
}
