extern "C" unsigned char bfmeVftASAa[];
extern "C" unsigned char bfmeVftASAb[];
extern "C" unsigned char bfmeVftASAc[];

class BfmeThingASA
{
public:
	void bfmeBaseASA(void *one);
	BfmeThingASA *bfmeInitASA(void *one);
	void *volatile m_bfmeVftA;
	unsigned char m_bfmeGap[0x20];
	void *volatile m_bfmeVftB;
	volatile int m_bfmeZero;
};

BfmeThingASA *BfmeThingASA::bfmeInitASA(void *one)
{
	bfmeBaseASA(one);
	m_bfmeVftB = bfmeVftASAa;
	m_bfmeZero = 0;
	m_bfmeVftA = bfmeVftASAb;
	m_bfmeVftB = bfmeVftASAc;
	return this;
}
