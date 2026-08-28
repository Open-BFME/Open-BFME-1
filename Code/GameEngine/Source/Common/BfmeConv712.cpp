extern "C" unsigned char bfmeVftDJA1[];
extern "C" unsigned char bfmeVftDJA2[];
extern "C" unsigned char bfmeVftDJA3[];
extern "C" unsigned char bfmeVftDJA4[];

struct BfmeBaseDJA
{
	void bfmeDtorDJA();
};

struct BfmeSub1DJA
{
	void *m_bfmeVft;
};

struct BfmeSub2DJA
{
	void *m_bfmeVft;
};

struct BfmeSub3DJA
{
	void *m_bfmeVft;
};

struct BfmeThingDJA
{
	void *m_bfmeVft;
	BfmeBaseDJA m_bfmeBase;
	unsigned char m_bfmeGap[0xf];
	BfmeSub3DJA m_bfme3;
	BfmeSub2DJA m_bfme2;
	BfmeSub1DJA m_bfme1;
};

void __fastcall bfmeGoDJA(BfmeThingDJA *p)
{
	BfmeSub1DJA *a = p ? &p->m_bfme1 : 0;
	a->m_bfmeVft = bfmeVftDJA1;
	BfmeSub2DJA *b = p ? &p->m_bfme2 : 0;
	b->m_bfmeVft = bfmeVftDJA2;
	BfmeSub3DJA *c = p ? &p->m_bfme3 : 0;
	c->m_bfmeVft = bfmeVftDJA3;
	p->m_bfmeVft = bfmeVftDJA4;
	p->m_bfmeBase.bfmeDtorDJA();
}
