struct BfmeBigAB
{
	int m_bfmeWords[6];
};

class BfmeThingAB
{
public:
	void bfmeBaseAB(void *one);
	BfmeThingAB *bfmeInitAB(void *one, const BfmeBigAB *two);
	unsigned char m_bfmeHead[0x10];
	BfmeBigAB m_bfmeBig;
};

BfmeThingAB *BfmeThingAB::bfmeInitAB(void *one, const BfmeBigAB *two)
{
	bfmeBaseAB(one);
	m_bfmeBig = *two;
	return this;
}
