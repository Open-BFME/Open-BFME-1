extern "C" unsigned char bfmeVftCUCa[];
extern "C" unsigned char bfmeVftCUCb[];

struct BfmeBaseCUC
{
	void bfmeDtorCUC();
};

struct BfmeSecondCUC
{
	void *m_bfmeVft;
};

struct BfmeThingCUC
{
	void *m_bfmeVftB;
	BfmeBaseCUC m_bfmeBase;
	unsigned char m_bfmeGap[0xc];
	BfmeSecondCUC m_bfmeSecond;
};

void __fastcall bfmeGoCUC(BfmeThingCUC *p)
{
	BfmeSecondCUC *s = p ? &p->m_bfmeSecond : 0;
	s->m_bfmeVft = bfmeVftCUCa;
	p->m_bfmeVftB = bfmeVftCUCb;
	p->m_bfmeBase.bfmeDtorCUC();
}
