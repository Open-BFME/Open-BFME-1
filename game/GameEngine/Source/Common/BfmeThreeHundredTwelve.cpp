class BfmeMakerRE
{
public:
	virtual void bfmeSpareRE0();
	virtual void bfmeSpareRE1();
	virtual void bfmeSpareRE2();
	virtual void bfmeSpareRE3();
	virtual void bfmeSpareRE4();
	virtual void bfmeDoRE();
};

struct BfmeHolderRE
{
	unsigned char m_bfmeHead[0x2a0];
	BfmeMakerRE *m_bfmeMaker;
};

BfmeMakerRE *bfmeMakeRE();

class BfmeThingRE
{
public:
	void bfmeRunRE();
	unsigned char m_bfmeHead[4];
	BfmeHolderRE *m_bfmeHolder;
};

void BfmeThingRE::bfmeRunRE()
{
	BfmeHolderRE *holder = m_bfmeHolder;
	if (holder->m_bfmeMaker == 0)
		holder->m_bfmeMaker = bfmeMakeRE();
	m_bfmeHolder->m_bfmeMaker->bfmeDoRE();
}
