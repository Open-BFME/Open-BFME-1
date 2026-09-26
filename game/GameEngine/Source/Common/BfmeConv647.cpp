extern "C" unsigned char bfmeVftCUBa[];
extern "C" unsigned char bfmeVftCUBb[];

struct BfmeBaseCUB
{
	void bfmeDtorCUB();
};

struct BfmeSecondCUB
{
	void *m_bfmeVft;
};

struct BfmeThingCUB
{
	void *m_bfmeVftB;
	BfmeBaseCUB m_bfmeBase;
	unsigned char m_bfmeGap[0xc];
	BfmeSecondCUB m_bfmeSecond;
};

void __fastcall bfmeGoCUB(BfmeThingCUB *p)
{
	BfmeSecondCUB *s = p ? &p->m_bfmeSecond : 0;
	s->m_bfmeVft = bfmeVftCUBa;
	p->m_bfmeVftB = bfmeVftCUBb;
	p->m_bfmeBase.bfmeDtorCUB();
}
