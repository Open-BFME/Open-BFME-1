// ?rva001DF850@VictorySystem@@QAEXXZ
// partial score=0.97 date=2026-09-16
// cl: /O2 /Ob2 /G6
// 58/58 bytes; 15 non-relocation bytes differ. Duplicating the current-player
// assignment in both switch cases makes MSVC save ESI and EDI before the switch,
// matching the retail prologue and branch layout. The residue is register
// allocation (our grid/player are ESI/EDI, retail uses EDI/ESI), our player load
// precedes the null branch, and our receiver load follows the final argument.
// VictorySystem ownership is proven by its exact constructor layout and the
// matched bfmeParametersForPlayer call; the method name remains address-derived.
struct FactionVictoryParameters;

class BfmeCellGrid
{
public:
	void rva001B1AD0(int playerIndex, FactionVictoryParameters *parameters);
};

class VictorySystem
{
public:
	void rva001DF850(void);
	FactionVictoryParameters *bfmeParametersForPlayer(int playerIndex);

	unsigned char m_pad00[0xf8];
	BfmeCellGrid *m_cellGrids[2];
	int m_initialized;
	int m_activeGrid;
	int m_currentPlayer;
};

void VictorySystem::rva001DF850(void)
{
	int playerIndex;
	BfmeCellGrid *grid;

	switch (m_activeGrid)
	{
	case 0:
		playerIndex = m_currentPlayer;
		grid = m_cellGrids[0];
		break;

	case 1:
		playerIndex = m_currentPlayer;
		grid = m_cellGrids[1];
		break;

	default:
		return;
	}

	if (grid == 0)
		return;

	grid->rva001B1AD0(playerIndex, bfmeParametersForPlayer(playerIndex));
}
