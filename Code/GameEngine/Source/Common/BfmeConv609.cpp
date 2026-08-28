struct BfmeSubCIE
{
	void bfmeNotifyCIE();
	unsigned char m_bfmeHead[0x12c];
	unsigned int m_bfmeFlags;
};

class BfmeThingCIE
{
public:
	void bfmeGoCIE(void *one, void *two);
	unsigned char m_bfmeHead[8];
	BfmeSubCIE *m_bfmeSub;
	unsigned char m_bfmeGap[0xdc];
	bool m_bfmeFlag;
};

void BfmeThingCIE::bfmeGoCIE(void *one, void *two)
{
	BfmeSubCIE *sub = m_bfmeSub;
	if (sub->m_bfmeFlags & 0x200)
	{
		sub->m_bfmeFlags &= ~0x200u;
		sub->bfmeNotifyCIE();
	}
	m_bfmeFlag = false;
}
