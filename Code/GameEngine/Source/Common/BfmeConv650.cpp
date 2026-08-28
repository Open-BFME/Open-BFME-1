extern "C" unsigned char bfmeVftCUEa[];
extern "C" unsigned char bfmeVftCUEb[];

struct BfmeBaseCUE
{
	void bfmeDtorCUE();
};

struct BfmeSecondCUE
{
	void *m_bfmeVft;
};

struct BfmeThingCUE
{
	void *m_bfmeVftB;
	BfmeBaseCUE m_bfmeBase;
	unsigned char m_bfmeGap[0xc];
	BfmeSecondCUE m_bfmeSecond;
};

void __fastcall bfmeGoCUE(BfmeThingCUE *p)
{
	BfmeSecondCUE *s = p ? &p->m_bfmeSecond : 0;
	s->m_bfmeVft = bfmeVftCUEa;
	p->m_bfmeVftB = bfmeVftCUEb;
	p->m_bfmeBase.bfmeDtorCUE();
}
