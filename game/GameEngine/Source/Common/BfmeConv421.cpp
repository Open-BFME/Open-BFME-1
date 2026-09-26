extern "C" unsigned char bfmeVftASCa[];
extern "C" unsigned char bfmeVftASCb[];
extern "C" unsigned char bfmeVftASCc[];

class BfmeThingASC
{
public:
	void bfmeBaseASC(void *one);
	BfmeThingASC *bfmeInitASC(void *one);
	void *volatile m_bfmeVftA;
	unsigned char m_bfmeGap[0x6c];
	void *volatile m_bfmeVftB;
	volatile int m_bfmeZero;
};

BfmeThingASC *BfmeThingASC::bfmeInitASC(void *one)
{
	bfmeBaseASC(one);
	m_bfmeVftB = bfmeVftASCa;
	m_bfmeZero = 0;
	m_bfmeVftA = bfmeVftASCb;
	m_bfmeVftB = bfmeVftASCc;
	return this;
}
