struct BfmeSubCCC
{
	void bfmeNotifyCCC();
	unsigned char m_bfmeHead[0x114];
	unsigned int m_bfmeFlags;
};

struct BfmeOwnerCCC
{
	unsigned char m_bfmeHead[0x10];
	BfmeSubCCC *m_bfmeMid;
};

class BfmeThingCCC
{
public:
	void bfmeGoCCC(void *spare);
	unsigned char m_bfmeHead[0x1c];
	BfmeOwnerCCC *m_bfmeOwner;
};

void BfmeThingCCC::bfmeGoCCC(void *spare)
{
	BfmeSubCCC *sub = m_bfmeOwner->m_bfmeMid;
	if (sub->m_bfmeFlags & 0x20000000u)
	{
		sub->m_bfmeFlags &= ~0x20000000u;
		sub->bfmeNotifyCCC();
	}
}
