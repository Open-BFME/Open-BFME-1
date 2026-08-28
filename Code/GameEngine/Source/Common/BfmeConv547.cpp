class BfmeRetBWF
{
};

class BfmeCalcBWF
{
public:
	void bfmeCalcBWF(BfmeRetBWF *one, int value, BfmeRetBWF *two);
};

struct BfmeOwnerBWF
{
	unsigned char m_bfmeHead[0x60];
	BfmeCalcBWF m_bfmeSub;
};

struct BfmeThingBWF
{
	BfmeRetBWF *bfmeGoBWF();
	unsigned char m_bfmeHead[8];
	BfmeRetBWF m_bfmeOne;
	unsigned char m_bfmeGap[0xf];
	BfmeOwnerBWF *m_bfmeOwner;
	int m_bfmeArg;
	unsigned char m_bfmeGap2[0x28];
	BfmeRetBWF m_bfmeTwo;
};

BfmeRetBWF *BfmeThingBWF::bfmeGoBWF()
{
	if (m_bfmeOwner != 0)
	{
		m_bfmeOwner->m_bfmeSub.bfmeCalcBWF(&m_bfmeOne, m_bfmeArg, &m_bfmeTwo);
		return &m_bfmeTwo;
	}
	return &m_bfmeOne;
}
