extern "C" unsigned char bfmeVftDJF1[];
extern "C" unsigned char bfmeVftDJF2[];
extern "C" unsigned char bfmeVftDJF3[];
extern "C" unsigned char bfmeVftDJF4[];

struct BfmeBaseDJF
{
	void bfmeDtorDJF();
};

struct BfmeSub1DJF
{
	void *m_bfmeVft;
};

struct BfmeSub2DJF
{
	void *m_bfmeVft;
};

struct BfmeSub3DJF
{
	void *m_bfmeVft;
};

struct BfmeThingDJF
{
	void *m_bfmeVft;
	BfmeBaseDJF m_bfmeBase;
	unsigned char m_bfmeGap[0xf];
	BfmeSub3DJF m_bfme3;
	BfmeSub2DJF m_bfme2;
	BfmeSub1DJF m_bfme1;
};

void __fastcall bfmeGoDJF(BfmeThingDJF *p)
{
	BfmeSub1DJF *a = p ? &p->m_bfme1 : 0;
	a->m_bfmeVft = bfmeVftDJF1;
	BfmeSub2DJF *b = p ? &p->m_bfme2 : 0;
	b->m_bfmeVft = bfmeVftDJF2;
	BfmeSub3DJF *c = p ? &p->m_bfme3 : 0;
	c->m_bfmeVft = bfmeVftDJF3;
	p->m_bfmeVft = bfmeVftDJF4;
	p->m_bfmeBase.bfmeDtorDJF();
}
