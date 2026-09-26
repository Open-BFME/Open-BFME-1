// Open-BFME5 conversions.

class BfmeCellVRC;

class BfmePartVRC
{
public:
	void bfmeCellRangeVRC(BfmeCellVRC **first, BfmeCellVRC **last, int x, int y, int radius);
};

class BfmeCellVRC
{
public:
	void bfmeAdjustVRC(int index, int a, int b);
	char m_bfmePad00[0x68];
};

class BfmeShroudVRC
{
public:
	char bfmeUpdateVRC(int x, int y, int radius);
	BfmePartVRC *m_bfme00;
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

	m_bfme00->bfmeCellRangeVRC((BfmeCellVRC **)&first, &last, x, y, radius);

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
					p->bfmeAdjustVRC(index, m_bfme08, m_bfme0c);
			}

			mask >>= 1;
			++index;
		}
		while (mask != 0);
	}

	return 1;
}
