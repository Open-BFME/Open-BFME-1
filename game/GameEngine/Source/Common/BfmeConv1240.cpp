// Open-BFME5 conversions.

class BfmeE1240
{
public:
	virtual void bfmeV1240A();
	virtual void bfmeV1240B();
	int bfmeVal1240();
	float bfmeF1240();
	unsigned m_bfme04;
};

class BfmeA1240
{
public:
	int m_bfme00;
	int m_bfme04;
	BfmeE1240 **m_bfme08;
};

extern BfmeE1240 *g_bfmeResult1240;
extern const float g_bfmeK1240;

extern "C" int bfmeQuery1240(void);
extern "C" BfmeE1240 *bfmeMake1240(int a);
extern "C" BfmeE1240 *bfmeMakeF1240(float a);

void bfmeGo1240(BfmeA1240 *a)
{
	BfmeE1240 *e;
	BfmeE1240 *v;

	e = a->m_bfme08[a->m_bfme00 - 1];

	v = 0;
	if (bfmeQuery1240() == 7 && ((unsigned char)(~(e->m_bfme04 >> 15)) & 1))
		v = g_bfmeResult1240;

	if (!v) {
		if ((e->m_bfme04 & 0x3f) == 7 && !((unsigned char)(~(e->m_bfme04 >> 15)) & 1))
			v = bfmeMake1240(e->bfmeVal1240() - 1);
		else
			v = bfmeMakeF1240(e->bfmeF1240() - g_bfmeK1240);
	}

	e = a->m_bfme08[a->m_bfme00 - 1];
	if (!((unsigned char)(e->m_bfme04 >> 30) & 1))
		e->bfmeV1240B();
	--a->m_bfme00;
	a->m_bfme08[a->m_bfme00] = v;
	++a->m_bfme00;
	if (!((unsigned char)(v->m_bfme04 >> 30) & 1))
		v->bfmeV1240A();
}
