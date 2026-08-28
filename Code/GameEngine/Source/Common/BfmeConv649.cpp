extern "C" unsigned char bfmeVftCUDa[];
extern "C" unsigned char bfmeVftCUDb[];

struct BfmeBaseCUD
{
	void bfmeDtorCUD();
};

struct BfmeSecondCUD
{
	void *m_bfmeVft;
};

struct BfmeThingCUD
{
	void *m_bfmeVftB;
	BfmeBaseCUD m_bfmeBase;
	unsigned char m_bfmeGap[0xc];
	BfmeSecondCUD m_bfmeSecond;
};

void __fastcall bfmeGoCUD(BfmeThingCUD *p)
{
	BfmeSecondCUD *s = p ? &p->m_bfmeSecond : 0;
	s->m_bfmeVft = bfmeVftCUDa;
	p->m_bfmeVftB = bfmeVftCUDb;
	p->m_bfmeBase.bfmeDtorCUD();
}
