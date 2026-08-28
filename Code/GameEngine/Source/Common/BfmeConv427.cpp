extern "C" unsigned char bfmeVftAWA[];

class BfmeThingAWA
{
public:
	void bfmeBaseAWA(void *one, void *two);
	BfmeThingAWA *bfmeInitAWA(void *one, void *two);
	void *m_bfmeVft;
	unsigned char m_bfmeGap[0xc];
	int m_bfmeZero;
	int m_bfmeCount;
};

BfmeThingAWA *BfmeThingAWA::bfmeInitAWA(void *one, void *two)
{
	bfmeBaseAWA(one, two);
	m_bfmeVft = bfmeVftAWA;
	m_bfmeCount = 0xa;
	m_bfmeZero = 0;
	return this;
}
