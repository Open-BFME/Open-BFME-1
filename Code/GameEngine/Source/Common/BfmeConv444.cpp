class BfmeInnerBDC
{
public:
	void bfmeRunBDC();
};

struct BfmeSubBDC
{
	unsigned char m_bfmeHead[0x20];
	BfmeInnerBDC m_bfmeInner;
};

struct BfmeOwnerBDC
{
	unsigned char m_bfmeHead[0x204];
	BfmeSubBDC *m_bfmeSub;
};

class BfmeThingBDC
{
public:
	void bfmeGoBDC();
	unsigned char m_bfmeHead[8];
	BfmeOwnerBDC *m_bfmeOwner;
};

void BfmeThingBDC::bfmeGoBDC()
{
	m_bfmeOwner->m_bfmeSub->m_bfmeInner.bfmeRunBDC();
}
