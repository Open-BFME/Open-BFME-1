extern "C" unsigned char bfmeVftCUAa[];
extern "C" unsigned char bfmeVftCUAb[];

struct BfmeBaseCUA
{
	void bfmeDtorCUA();
};

struct BfmeSecondCUA
{
	void *m_bfmeVft;
};

struct BfmeThingCUA
{
	void *m_bfmeVftB;
	BfmeBaseCUA m_bfmeBase;
	unsigned char m_bfmeGap[0xc];
	BfmeSecondCUA m_bfmeSecond;
};

void __fastcall bfmeGoCUA(BfmeThingCUA *p)
{
	BfmeSecondCUA *s = p ? &p->m_bfmeSecond : 0;
	s->m_bfmeVft = bfmeVftCUAa;
	p->m_bfmeVftB = bfmeVftCUAb;
	p->m_bfmeBase.bfmeDtorCUA();
}
