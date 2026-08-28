class BfmeInnerWC
{
public:
	void bfmeTailWC(int what);
};

struct BfmeOwnerWC
{
	unsigned char m_bfmeHead[0x10];
	BfmeInnerWC *m_bfmeInner;
};

class BfmeSubWC
{
public:
	virtual void bfmeReleaseWC(int what);
};

class BfmeThingWC
{
public:
	void bfmeGoWC(int what);
	unsigned char m_bfmeHead[0x1c];
	BfmeOwnerWC *m_bfmeOwner;
	unsigned char m_bfmeGap[4];
	BfmeSubWC *m_bfmeSub;
};

void BfmeThingWC::bfmeGoWC(int what)
{
	BfmeSubWC *sub = m_bfmeSub;
	if (sub != 0)
		sub->bfmeReleaseWC(1);
	m_bfmeSub = 0;
	BfmeInnerWC *inner = m_bfmeOwner->m_bfmeInner;
	if (inner != 0)
		inner->bfmeTailWC(1);
}
