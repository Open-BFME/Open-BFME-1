extern "C" unsigned char bfmeVftBTB[];

struct BfmeSubBTB
{
	void bfmeSetBTB(void *one, void *two);
	unsigned char m_bfmeHead[4];
};

class BfmeThingBTB
{
public:
	BfmeThingBTB *bfmeInitBTB(void *one, void *two);
	void *m_bfmeVft;
	BfmeSubBTB m_bfmeSub;
};

BfmeThingBTB *BfmeThingBTB::bfmeInitBTB(void *one, void *two)
{
	m_bfmeVft = bfmeVftBTB;
	m_bfmeSub.bfmeSetBTB(one, two);
	return this;
}
