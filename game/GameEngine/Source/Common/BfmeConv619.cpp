struct BfmeMidCLC
{
	void bfmeNotifyCLC();
	unsigned char m_bfmeHead[0x118];
	unsigned int m_bfmeFlags;
};

struct BfmeOwnerCLC
{
	unsigned char m_bfmeHead[0x10];
	BfmeMidCLC *m_bfmeMid;
};

class BfmeThingCLC
{
public:
	void bfmeThenCLC(void *what);
	void bfmeGoCLC(void *what);
	unsigned char m_bfmeHead[0x1c];
	BfmeOwnerCLC *m_bfmeOwner;
};

void BfmeThingCLC::bfmeGoCLC(void *what)
{
	BfmeMidCLC *mid = m_bfmeOwner->m_bfmeMid;
	if (mid->m_bfmeFlags & 0x1000)
	{
		mid->m_bfmeFlags &= ~0x1000u;
		mid->bfmeNotifyCLC();
	}
	bfmeThenCLC(what);
}
