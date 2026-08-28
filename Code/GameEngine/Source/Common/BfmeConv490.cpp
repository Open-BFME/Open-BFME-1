struct BfmePartBMC
{
	unsigned char m_bfmeHead[4];
};

class BfmeSubBMC
{
public:
	void bfmeDoBMC(BfmePartBMC *one, BfmePartBMC *two);
	unsigned char m_bfmeHead[4];
};

struct BfmeOwnerBMC
{
	unsigned char m_bfmeHead[0x90];
	BfmeSubBMC m_bfmeSub;
};

class BfmeThingBMC
{
public:
	void bfmeGoBMC(BfmeOwnerBMC *owner);
	unsigned char m_bfmeHead[8];
	BfmePartBMC m_bfmeA;
	unsigned char m_bfmeGap[8];
	BfmePartBMC m_bfmeB;
};

void BfmeThingBMC::bfmeGoBMC(BfmeOwnerBMC *owner)
{
	owner->m_bfmeSub.bfmeDoBMC(&m_bfmeA, &m_bfmeB);
}
