extern "C" unsigned char bfmeVftDJD1[];
extern "C" unsigned char bfmeVftDJD2[];
extern "C" unsigned char bfmeVftDJD3[];
extern "C" unsigned char bfmeVftDJD4[];

struct BfmeBaseDJD
{
	void bfmeDtorDJD();
};

struct BfmeSub1DJD
{
	void *m_bfmeVft;
};

struct BfmeSub2DJD
{
	void *m_bfmeVft;
};

struct BfmeSub3DJD
{
	void *m_bfmeVft;
};

struct BfmeThingDJD
{
	void *m_bfmeVft;
	BfmeBaseDJD m_bfmeBase;
	unsigned char m_bfmeGap[0xf];
	BfmeSub3DJD m_bfme3;
	BfmeSub2DJD m_bfme2;
	BfmeSub1DJD m_bfme1;
};

void __fastcall bfmeGoDJD(BfmeThingDJD *p)
{
	BfmeSub1DJD *a = p ? &p->m_bfme1 : 0;
	a->m_bfmeVft = bfmeVftDJD1;
	BfmeSub2DJD *b = p ? &p->m_bfme2 : 0;
	b->m_bfmeVft = bfmeVftDJD2;
	BfmeSub3DJD *c = p ? &p->m_bfme3 : 0;
	c->m_bfmeVft = bfmeVftDJD3;
	p->m_bfmeVft = bfmeVftDJD4;
	p->m_bfmeBase.bfmeDtorDJD();
}
