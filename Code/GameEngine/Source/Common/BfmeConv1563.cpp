// Open-BFME5 conversions.

class BfmeCellVRB;

class BfmePartVRB
{
public:
	void bfmeCellRangeVRB(BfmeCellVRB **first, BfmeCellVRB **last, int x, int y, int radius);
};

class BfmeCellVRB
{
public:
	void bfmeTouchVRB(BfmePartVRB *owner, int index);
	char m_bfmePad00[0x68];
};

class BfmeShroudVRB
{
public:
	char bfmeUpdateVRB(int x, int y, int radius);
	BfmePartVRB *m_bfme00;
	int m_bfme04;
};

char BfmeShroudVRB::bfmeUpdateVRB(int x, int y, int radius)
{
	BfmeCellVRB *volatile first;
	BfmeCellVRB *last;
	unsigned int mask;
	int index;

	m_bfme00->bfmeCellRangeVRB((BfmeCellVRB **)&first, &last, x, y, radius);

	mask = m_bfme04;
	index = 0;
	if (mask != 0)
	{
		BfmeCellVRB *end = last;

		do
		{
			if ((mask & 1) != 0)
			{
				BfmeCellVRB *p;

				for (p = first; p != end; ++p)
					p->bfmeTouchVRB(m_bfme00, index);
			}

			mask >>= 1;
			++index;
		}
		while (mask != 0);
	}

	return 1;
}
