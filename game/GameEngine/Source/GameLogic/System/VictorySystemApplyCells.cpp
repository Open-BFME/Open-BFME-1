// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /G6

typedef int Int;
typedef unsigned int UnsignedInt;

struct BfmeVec1268
{
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
};

class BfmeCell
{
public:
	Int bfmeEvaluate(bool useCellRatio);
};

class BfmeCellGrid
{
public:
	Int bfmeEvaluateCells() const;
};

class BfmeA1268
{
public:
	void bfmeCell1268(UnsignedInt i, BfmeVec1268 *out);

	char m_pad00[8];
	UnsignedInt m_cellCount;
	char m_pad0c[0x18 - 0x0c];
	UnsignedInt *m_cellValues;
};

class VictorySystem
{
public:
	void bfmeApplyWinningCells(void);
	void bfmeNotifyCell(UnsignedInt playerIndex, BfmeVec1268 *pos);

private:

	char m_pad00[0x64];
	BfmeCell m_rootCell;
	char m_pad65[0xf8 - 0x65];
	BfmeA1268 *m_grids[2];
};

void VictorySystem::bfmeApplyWinningCells(void)
{
	if (m_rootCell.bfmeEvaluate(false) == 0)
		return;

	UnsignedInt best = 0x7fffffff;
	union {
		UnsignedInt counts[2];
		BfmeVec1268 vec;
	} u;
	UnsignedInt index;
	for (index = 0; index < 2; ++index)
	{
		u.counts[index] = (UnsignedInt)((BfmeCellGrid *)m_grids[index])->bfmeEvaluateCells();
		if (u.counts[index] != 0)
		{
			if (best == 0x7fffffff || u.counts[index] > u.counts[best])
				best = index;
		}
	}

	if (best == 0x7fffffff)
		return;

	UnsignedInt *values = m_grids[best]->m_cellValues;
	UnsignedInt cellIndex;
	for (cellIndex = 0; cellIndex < m_grids[best]->m_cellCount; ++cellIndex, ++values)
	{
		if (*values != 0)
		{
			m_grids[best]->bfmeCell1268(cellIndex, &u.vec);
			UnsignedInt playerIndex;
			for (playerIndex = 0; playerIndex < 16; ++playerIndex)
			{
				if ((*values & (1u << playerIndex)) != 0)
					bfmeNotifyCell(playerIndex, &u.vec);
			}
		}
	}
}
