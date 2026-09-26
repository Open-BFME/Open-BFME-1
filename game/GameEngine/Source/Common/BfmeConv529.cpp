struct BfmeInnerBUA
{
	void bfmeDoBUA(void *what);
	unsigned char m_bfmeHead[4];
};

struct BfmeSubBUA
{
	unsigned char m_bfmeHead[0x20];
	BfmeInnerBUA m_bfmeInner;
};

struct BfmeOwnerBUA
{
	unsigned char m_bfmeHead[0x204];
	BfmeSubBUA *m_bfmeSub;
};

void bfmeGoBUA(BfmeOwnerBUA *owner, void **what)
{
	if (owner != 0 && owner->m_bfmeSub != 0)
		owner->m_bfmeSub->m_bfmeInner.bfmeDoBUA(*what);
}
