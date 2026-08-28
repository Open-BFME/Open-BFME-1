extern "C" unsigned char bfmeVftDJE1[];
extern "C" unsigned char bfmeVftDJE2[];
extern "C" unsigned char bfmeVftDJE3[];
extern "C" unsigned char bfmeVftDJE4[];

struct BfmeBaseDJE
{
	void bfmeDtorDJE();
};

struct BfmeSub1DJE
{
	void *m_bfmeVft;
};

struct BfmeSub2DJE
{
	void *m_bfmeVft;
};

struct BfmeSub3DJE
{
	void *m_bfmeVft;
};

struct BfmeThingDJE
{
	void *m_bfmeVft;
	BfmeBaseDJE m_bfmeBase;
	unsigned char m_bfmeGap[0xf];
	BfmeSub3DJE m_bfme3;
	BfmeSub2DJE m_bfme2;
	BfmeSub1DJE m_bfme1;
};

void __fastcall bfmeGoDJE(BfmeThingDJE *p)
{
	BfmeSub1DJE *a = p ? &p->m_bfme1 : 0;
	a->m_bfmeVft = bfmeVftDJE1;
	BfmeSub2DJE *b = p ? &p->m_bfme2 : 0;
	b->m_bfmeVft = bfmeVftDJE2;
	BfmeSub3DJE *c = p ? &p->m_bfme3 : 0;
	c->m_bfmeVft = bfmeVftDJE3;
	p->m_bfmeVft = bfmeVftDJE4;
	p->m_bfmeBase.bfmeDtorDJE();
}
