class BfmeSubBVD
{
public:
	int bfmeKindBVD();
};

struct BfmeMidBVD
{
	unsigned char m_bfmeHead[0x204];
	BfmeSubBVD *m_bfmeSub;
};

struct BfmeOwnerBVD
{
	unsigned char m_bfmeHead[0x10];
	BfmeMidBVD *m_bfmeMid;
};

struct BfmeThingBVD
{
	unsigned char m_bfmeHead[0x1c];
	BfmeOwnerBVD *m_bfmeOwner;
};

bool bfmeGoBVD(BfmeThingBVD *what)
{
	BfmeSubBVD *sub = what->m_bfmeOwner->m_bfmeMid->m_bfmeSub;
	if (!sub)
		return false;
	if (sub->bfmeKindBVD() == 0x2f)
		return true;
	return false;
}
