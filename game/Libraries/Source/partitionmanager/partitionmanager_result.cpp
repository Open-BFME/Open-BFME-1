// Open-BFME5 conversions.

struct BfmeElemVJX;

struct BfmeCmpVJX
{
	char m_bfme00;
};

void __cdecl bfmeSortAVJX(BfmeElemVJX *a, BfmeElemVJX *b, BfmeCmpVJX c);
void __cdecl bfmeSortBVJX(BfmeElemVJX *a, BfmeElemVJX *b, BfmeCmpVJX c);

struct BfmeRangeVJX
{
	BfmeElemVJX *m_bfme00;
	BfmeElemVJX *m_bfme04;
};

class BfmeThingVJX
{
public:
	void bfmeGoVJX(int mode);
	BfmeRangeVJX *m_bfme00;
};

void BfmeThingVJX::bfmeGoVJX(int mode)
{
	BfmeCmpVJX c;
	switch (mode)
	{
	case 2:
		c.m_bfme00 = 0;
		bfmeSortAVJX(m_bfme00->m_bfme00, m_bfme00->m_bfme04, c);
		break;
	case 1:
		c.m_bfme00 = 0;
		bfmeSortBVJX(m_bfme00->m_bfme00, m_bfme00->m_bfme04, c);
		break;
	}
}
