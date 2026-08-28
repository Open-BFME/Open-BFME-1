extern "C" unsigned char bfmeVftCUFa[];
extern "C" unsigned char bfmeVftCUFb[];

struct BfmeBaseCUF
{
	void bfmeDtorCUF();
};

struct BfmeSecondCUF
{
	void *m_bfmeVft;
};

struct BfmeThingCUF
{
	void *m_bfmeVftB;
	BfmeBaseCUF m_bfmeBase;
	unsigned char m_bfmeGap[0xc];
	BfmeSecondCUF m_bfmeSecond;
};

void __fastcall bfmeGoCUF(BfmeThingCUF *p)
{
	BfmeSecondCUF *s = p ? &p->m_bfmeSecond : 0;
	s->m_bfmeVft = bfmeVftCUFa;
	p->m_bfmeVftB = bfmeVftCUFb;
	p->m_bfmeBase.bfmeDtorCUF();
}
