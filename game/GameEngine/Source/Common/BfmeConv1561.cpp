// Open-BFME5 conversions.

class PartitionCell
{
public:
	char m_bfmePad00[0x68];
};

// Retail's per-cell shroud update body lives on the shroud manager element:
// game/GameEngine/Source/Common/RTS/ShroudManagerImpl008FBA40.cpp
class ShroudManagerImpl008FBA40;

class ShroudManagerImpl008FBA40Element
{
public:
	void updatePlayerCells008FC300(ShroudManagerImpl008FBA40 *manager, int index);
};

class PartitionManager
{
public:
	void getCellRange(PartitionCell **first, PartitionCell **last, int x1, int x2, int y);
};

class BfmeShroudVRA
{
public:
	char bfmeUpdateVRA(int x, int y, int radius);
	PartitionManager *m_bfme00;
	int m_bfme04;
};

char BfmeShroudVRA::bfmeUpdateVRA(int x, int y, int radius)
{
	PartitionCell *volatile first;
	PartitionCell *last;
	unsigned int mask;
	int index;

	m_bfme00->getCellRange((PartitionCell **)&first, &last, x, y, radius);

	mask = m_bfme04;
	index = 0;
	if (mask != 0)
	{
		PartitionCell *end = last;

		do
		{
			if ((mask & 1) != 0)
			{
				PartitionCell *p;

				for (p = first; p != end; ++p)
					reinterpret_cast<ShroudManagerImpl008FBA40Element *>(p)
					->updatePlayerCells008FC300(
						reinterpret_cast<ShroudManagerImpl008FBA40 *>(m_bfme00),
						index);
			}

			mask >>= 1;
			++index;
		}
		while (mask != 0);
	}

	return 1;
}
