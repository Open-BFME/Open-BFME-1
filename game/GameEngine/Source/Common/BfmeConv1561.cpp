// Open-BFME5 conversions.

class BfmeCellVRA;

// Retail's per-cell shroud update body lives on the shroud manager element:
// game/GameEngine/Source/Common/RTS/ShroudManagerImpl008FBA40.cpp
class ShroudManagerImpl008FBA40;

class ShroudManagerImpl008FBA40Element
{
public:
	void updatePlayerCells008FC300(ShroudManagerImpl008FBA40 *manager, int index);
};

class BfmePartVRA
{
public:
	void bfmeCellRangeVRA(BfmeCellVRA **first, BfmeCellVRA **last, int x, int y, int radius);
};

class BfmeCellVRA
{
public:
	char m_bfmePad00[0x68];
};

class BfmeShroudVRA
{
public:
	char bfmeUpdateVRA(int x, int y, int radius);
	BfmePartVRA *m_bfme00;
	int m_bfme04;
};

char BfmeShroudVRA::bfmeUpdateVRA(int x, int y, int radius)
{
	BfmeCellVRA *volatile first;
	BfmeCellVRA *last;
	unsigned int mask;
	int index;

	m_bfme00->bfmeCellRangeVRA((BfmeCellVRA **)&first, &last, x, y, radius);

	mask = m_bfme04;
	index = 0;
	if (mask != 0)
	{
		BfmeCellVRA *end = last;

		do
		{
			if ((mask & 1) != 0)
			{
				BfmeCellVRA *p;

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
