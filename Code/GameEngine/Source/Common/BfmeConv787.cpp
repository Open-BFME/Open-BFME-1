class BfmeSubDVB
{
public:
	void bfmeOneDVB(void *a, void *b);
	void bfmeTwoDVB(void *a, void *b);
	void bfmeThreeDVB(void *a, void *b);
};

struct BfmeThingDVB
{
	void *bfmeGoDVBa(void *a, void *b);
	void *bfmeGoDVBb(void *a, void *b);
	void *bfmeGoDVBc(void *a, void *b);
	unsigned char m_bfmeHead[0x170];
	BfmeSubDVB m_bfmeSub;
};

void *BfmeThingDVB::bfmeGoDVBa(void *a, void *b)
{
	volatile int tmp = 0;
	m_bfmeSub.bfmeOneDVB(a, b);
	return a;
}

void *BfmeThingDVB::bfmeGoDVBb(void *a, void *b)
{
	volatile int tmp = 0;
	m_bfmeSub.bfmeTwoDVB(a, b);
	return a;
}

void *BfmeThingDVB::bfmeGoDVBc(void *a, void *b)
{
	volatile int tmp = 0;
	m_bfmeSub.bfmeThreeDVB(a, b);
	return a;
}
