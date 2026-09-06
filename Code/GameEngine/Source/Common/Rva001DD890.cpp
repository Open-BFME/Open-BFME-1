// cl: /DNDEBUG /MD /EHsc

struct BfmePartBMC492
{
	unsigned char m_bfmeHead[4];
};

class BfmeSubBMC492
{
public:
	unsigned char bfmeCheckBMC(BfmePartBMC492 *one, BfmePartBMC492 *two);
	unsigned char m_bfmeHead[4];
};

struct BfmeOwnerBMC492
{
	unsigned char m_bfmeHead[0x90];
	BfmeSubBMC492 m_bfmeSub;
};

class BfmeThingBMC492
{
public:
	bool bfmeCheckBMC(BfmeOwnerBMC492 *owner);
	unsigned char m_bfmeHead[8];
	BfmePartBMC492 m_bfmeA;
	unsigned char m_bfmeGap[8];
	BfmePartBMC492 m_bfmeB;
};

// ?bfmeCheckBMC@BfmeThingBMC492@@QAE_NPAUBfmeOwnerBMC492@@@Z
bool BfmeThingBMC492::bfmeCheckBMC(BfmeOwnerBMC492 *owner)
{
	return !owner->m_bfmeSub.bfmeCheckBMC(&m_bfmeA, &m_bfmeB);
}
