extern "C" unsigned char bfmeTextBME[];

struct BfmeSubBME
{
	void bfmeSetBME(void *text);
	unsigned char m_bfmeHead[4];
};

class BfmeThingBME
{
public:
	BfmeThingBME *bfmeInitBME();
	int m_bfmeZero;
	BfmeSubBME m_bfmeSub;
};

BfmeThingBME *BfmeThingBME::bfmeInitBME()
{
	m_bfmeZero = 0;
	m_bfmeSub.bfmeSetBME(bfmeTextBME);
	return this;
}
