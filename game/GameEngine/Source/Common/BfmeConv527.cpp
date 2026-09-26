extern "C" unsigned char bfmeVftBTB[];

struct BfmeSubBTB
{
	void bfmeSetBTB(void *one, void *two);
	void bfmeCopyBTB(const BfmeSubBTB &that);
	unsigned char m_bfmeHead[4];
};

class BfmeThingBTB
{
public:
	BfmeThingBTB *bfmeInitBTB(void *one, void *two);
	BfmeThingBTB *bfmeCopyBTB(const BfmeThingBTB &that);
	void *m_bfmeVft;
	BfmeSubBTB m_bfmeSub;
};

BfmeThingBTB *BfmeThingBTB::bfmeInitBTB(void *one, void *two)
{
	m_bfmeVft = bfmeVftBTB;
	m_bfmeSub.bfmeSetBTB(one, two);
	return this;
}

// ?bfmeCopyBTB@BfmeThingBTB@@QAEPAV1@ABV1@@Z
BfmeThingBTB *BfmeThingBTB::bfmeCopyBTB(const BfmeThingBTB &that)
{
	m_bfmeVft = bfmeVftBTB;
	m_bfmeSub.bfmeCopyBTB(that.m_bfmeSub);
	return this;
}
