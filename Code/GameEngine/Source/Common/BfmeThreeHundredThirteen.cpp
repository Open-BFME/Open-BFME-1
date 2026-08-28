class BfmeMakerRG
{
public:
	virtual void bfmeSpareRG0();
	virtual void bfmeSpareRG1();
	virtual void bfmeSpareRG2();
	virtual void bfmeSpareRG3();
	virtual void bfmeSpareRG4();
	virtual void bfmeSpareRG5();
	virtual void bfmeDoRG();
};

struct BfmeHolderRG
{
	unsigned char m_bfmeHead[0x2a0];
	BfmeMakerRG *m_bfmeMaker;
};

BfmeMakerRG *bfmeMakeRG();

class BfmeThingRG
{
public:
	void bfmeRunRG();
	unsigned char m_bfmeHead[4];
	BfmeHolderRG *m_bfmeHolder;
};

void BfmeThingRG::bfmeRunRG()
{
	BfmeHolderRG *holder = m_bfmeHolder;
	if (holder->m_bfmeMaker == 0)
		holder->m_bfmeMaker = bfmeMakeRG();
	m_bfmeHolder->m_bfmeMaker->bfmeDoRG();
}
