struct BfmeSubCCA
{
	void bfmeNotifyCCA();
	unsigned char m_bfmeHead[0x12c];
	unsigned int m_bfmeFlags;
};

struct BfmeOwnerCCA
{
	unsigned char m_bfmeHead[0x10];
	BfmeSubCCA *m_bfmeMid;
};

class BfmeThingCCA
{
public:
	void bfmeGoCCA(void *spare);
	unsigned char m_bfmeHead[0x1c];
	BfmeOwnerCCA *m_bfmeOwner;
};

void BfmeThingCCA::bfmeGoCCA(void *spare)
{
	BfmeSubCCA *sub = m_bfmeOwner->m_bfmeMid;
	if (sub->m_bfmeFlags & 0x200000u)
	{
		sub->m_bfmeFlags &= ~0x200000u;
		sub->bfmeNotifyCCA();
	}
}
