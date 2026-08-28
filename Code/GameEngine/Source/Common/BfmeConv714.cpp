extern "C" unsigned char bfmeVftDJC1[];
extern "C" unsigned char bfmeVftDJC2[];
extern "C" unsigned char bfmeVftDJC3[];
extern "C" unsigned char bfmeVftDJC4[];

struct BfmeBaseDJC
{
	void bfmeDtorDJC();
};

struct BfmeSub1DJC
{
	void *m_bfmeVft;
};

struct BfmeSub2DJC
{
	void *m_bfmeVft;
};

struct BfmeSub3DJC
{
	void *m_bfmeVft;
};

struct BfmeThingDJC
{
	void *m_bfmeVft;
	BfmeBaseDJC m_bfmeBase;
	unsigned char m_bfmeGap[0xf];
	BfmeSub3DJC m_bfme3;
	BfmeSub2DJC m_bfme2;
	BfmeSub1DJC m_bfme1;
};

void __fastcall bfmeGoDJC(BfmeThingDJC *p)
{
	BfmeSub1DJC *a = p ? &p->m_bfme1 : 0;
	a->m_bfmeVft = bfmeVftDJC1;
	BfmeSub2DJC *b = p ? &p->m_bfme2 : 0;
	b->m_bfmeVft = bfmeVftDJC2;
	BfmeSub3DJC *c = p ? &p->m_bfme3 : 0;
	c->m_bfmeVft = bfmeVftDJC3;
	p->m_bfmeVft = bfmeVftDJC4;
	p->m_bfmeBase.bfmeDtorDJC();
}
