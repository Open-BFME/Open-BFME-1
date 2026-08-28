class BfmeSubBUD
{
public:
	void bfmeOneBUD();
};

class BfmeOwnerBUD
{
public:
	void bfmeTwoBUD();
	void bfmeThreeBUD();
	unsigned char m_bfmeHead[0x210];
	BfmeSubBUD *m_bfmeSub;
};

class BfmeThingBUD
{
public:
	void bfmeGoBUD();
	unsigned char m_bfmeHead[8];
	BfmeOwnerBUD *m_bfmeOwner;
};

void BfmeThingBUD::bfmeGoBUD()
{
	BfmeOwnerBUD *owner = m_bfmeOwner;
	BfmeSubBUD *sub = owner->m_bfmeSub;
	if (sub != 0)
		sub->bfmeOneBUD();
	owner->bfmeTwoBUD();
	owner->bfmeThreeBUD();
}
