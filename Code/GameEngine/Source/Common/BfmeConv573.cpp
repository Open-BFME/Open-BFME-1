struct BfmeSubCCB
{
	void bfmeNotifyCCB();
	unsigned char m_bfmeHead[0x12c];
	unsigned int m_bfmeFlags;
};

struct BfmeOwnerCCB
{
	unsigned char m_bfmeHead[0x10];
	BfmeSubCCB *m_bfmeMid;
};

class BfmeThingCCB
{
public:
	void bfmeGoCCB(void *spare);
	unsigned char m_bfmeHead[0x1c];
	BfmeOwnerCCB *m_bfmeOwner;
};

void BfmeThingCCB::bfmeGoCCB(void *spare)
{
	BfmeSubCCB *sub = m_bfmeOwner->m_bfmeMid;
	if (sub->m_bfmeFlags & 0x400000u)
	{
		sub->m_bfmeFlags &= ~0x400000u;
		sub->bfmeNotifyCCB();
	}
}
