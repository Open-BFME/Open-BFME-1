class BfmeThingBMA
{
public:
	void bfmeBaseBMA(void *one);
	BfmeThingBMA *bfmeGoBMA(void *one, void *two);
	unsigned char m_bfmeHead[4];
	void *m_bfmeTwo;
};

BfmeThingBMA *BfmeThingBMA::bfmeGoBMA(void *one, void *two)
{
	bfmeBaseBMA(one);
	m_bfmeTwo = two;
	return this;
}
