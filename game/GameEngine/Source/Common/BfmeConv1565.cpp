// Open-BFME5 conversions.

class PartitionCell;

class PartitionManager
{
public:
	void getCellRange(PartitionCell **first, PartitionCell **last, int x, int y, int radius);
};

// Retail 0x008FC1F0 is owned by ShroudManagerImpl008FBA40.cpp.
class ShroudManagerImpl008FBA40Element
{
public:
	void adjustPlayerCounter008FC1F0(int index, int a, int b);
};

class BfmeCellVRC
{
public:
	char m_bfmePad00[0x68];
};

class BfmeShroudVRC
{
public:
	char bfmeUpdateVRC(int x, int y, int radius);
	PartitionManager *m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
};

char BfmeShroudVRC::bfmeUpdateVRC(int x, int y, int radius)
{
	BfmeCellVRC *volatile first;
	BfmeCellVRC *last;
	unsigned int mask;
	int index;

	m_bfme00->getCellRange((PartitionCell **)&first, (PartitionCell **)&last, x, y, radius);

	mask = m_bfme04;
	index = 0;
	if (mask != 0)
	{
		BfmeCellVRC *end = last;

		do
		{
			if ((mask & 1) != 0)
			{
				BfmeCellVRC *p;

				for (p = first; p != end; ++p)
					reinterpret_cast<ShroudManagerImpl008FBA40Element *>(p)->adjustPlayerCounter008FC1F0(
						index, m_bfme08, m_bfme0c);
			}

			mask >>= 1;
			++index;
		}
		while (mask != 0);
	}

	return 1;
}
