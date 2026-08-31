// cl: /O2 /Ob2 /G6

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class Gen_001de260
{
public:
	Int bfmeAbove(const Real *samples, Int index) const;
};

class VictorySystem
{
public:
	Gen_001de260 *bfmeParametersForPlayer(Int playerIndex);
};

extern VictorySystem *TheVictorySystem;

class BfmeCell1670
{
public:
	void clear()
	{
		for (UnsignedInt index = 0; index < 16; ++index)
		{
			m_second[index] = 0.0f;
			m_first[index] = 0.0f;
		}
		m_secondMask = 0;
		m_firstMask = 0;
	}

	Real m_first[16];
	Real m_second[16];
	Int m_firstMask;
	Int m_secondMask;
};

class BfmeCellGrid
{
public:
	Int bfmeEvaluateCells() const;

private:
	Int m_width;
	Int m_height;
	UnsignedInt m_cellCount;
	Real m_cellSize;
	Real m_offset;
	BfmeCell1670 *m_cells;
	UnsignedInt *m_cellValues;
};

Int BfmeCellGrid::bfmeEvaluateCells() const
{
	Int affected = 0;
	for (UnsignedInt cellIndex = 0; cellIndex < m_cellCount; ++cellIndex)
	{
		m_cellValues[cellIndex] = 0;
		if (m_cells[cellIndex].m_firstMask != 0)
		{
			for (UnsignedInt playerIndex = 0; playerIndex < 16; ++playerIndex)
			{
				if ((m_cells[cellIndex].m_firstMask & (1 << playerIndex)) != 0)
				{
					Gen_001de260 *parameters =
						TheVictorySystem->bfmeParametersForPlayer((Int)playerIndex);
					if (parameters != 0 &&
						static_cast<unsigned char>(parameters->bfmeAbove(
							m_cells[cellIndex].m_first, (Int)playerIndex)) != 0)
					{
						m_cellValues[cellIndex] |= (1 << playerIndex);
						m_cells[cellIndex].clear();
						++affected;
					}
				}
			}
		}
	}
	return affected;
}
