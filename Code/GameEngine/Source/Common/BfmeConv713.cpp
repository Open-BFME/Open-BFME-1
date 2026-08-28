extern "C" unsigned char bfmeVftDJB1[];
extern "C" unsigned char bfmeVftDJB2[];
extern "C" unsigned char bfmeVftDJB3[];
extern "C" unsigned char bfmeVftDJB4[];

struct BfmeBaseDJB
{
	void bfmeDtorDJB();
};

struct BfmeSub1DJB
{
	void *m_bfmeVft;
};

struct BfmeSub2DJB
{
	void *m_bfmeVft;
};

struct BfmeSub3DJB
{
	void *m_bfmeVft;
};

struct BfmeThingDJB
{
	void *m_bfmeVft;
	BfmeBaseDJB m_bfmeBase;
	unsigned char m_bfmeGap[0xf];
	BfmeSub3DJB m_bfme3;
	BfmeSub2DJB m_bfme2;
	BfmeSub1DJB m_bfme1;
};

void __fastcall bfmeGoDJB(BfmeThingDJB *p)
{
	BfmeSub1DJB *a = p ? &p->m_bfme1 : 0;
	a->m_bfmeVft = bfmeVftDJB1;
	BfmeSub2DJB *b = p ? &p->m_bfme2 : 0;
	b->m_bfmeVft = bfmeVftDJB2;
	BfmeSub3DJB *c = p ? &p->m_bfme3 : 0;
	c->m_bfmeVft = bfmeVftDJB3;
	p->m_bfmeVft = bfmeVftDJB4;
	p->m_bfmeBase.bfmeDtorDJB();
}
