extern "C" unsigned char bfmeVftDUJa[];
extern "C" unsigned char bfmeVftDUJb[];
extern "C" unsigned char bfmeVftDUJc[];

struct BfmeThingDUJ
{
	void bfmeGoDUJ();
	void bfmeDtorDUJ();
	void *volatile m_bfmeVftA;
	unsigned char m_bfmeHead[0x6c];
	void *volatile m_bfmeVftB;
};

void BfmeThingDUJ::bfmeGoDUJ()
{
	m_bfmeVftA = bfmeVftDUJa;
	m_bfmeVftB = bfmeVftDUJb;
	m_bfmeVftB = bfmeVftDUJc;
	bfmeDtorDUJ();
}
