// Open-BFME5 conversions.

class BfmeE1239
{
public:
	virtual void bfmeV1239A();
	virtual void bfmeV1239B();
	int bfmeVal1239();
	float bfmeF1239();
	unsigned m_bfme04;
};

class BfmeA1239
{
public:
	int m_bfme00;
	int m_bfme04;
	BfmeE1239 **m_bfme08;
};

extern BfmeE1239 *g_bfmeResult1239;
extern const float g_bfmeK1239;

extern "C" int bfmeQuery1239(void);
extern "C" BfmeE1239 *bfmeMake1239(int a);
extern "C" BfmeE1239 *bfmeMakeF1239(float a);

void bfmeGo1239(BfmeA1239 *a)
{
	BfmeE1239 *e;
	BfmeE1239 *v;

	e = a->m_bfme08[a->m_bfme00 - 1];

	v = 0;
	if (bfmeQuery1239() == 7 && ((unsigned char)(~(e->m_bfme04 >> 15)) & 1))
		v = g_bfmeResult1239;

	if (!v) {
		if ((e->m_bfme04 & 0x3f) == 7 && !((unsigned char)(~(e->m_bfme04 >> 15)) & 1))
			v = bfmeMake1239(e->bfmeVal1239() + 1);
		else
			v = bfmeMakeF1239(e->bfmeF1239() + g_bfmeK1239);
	}

	e = a->m_bfme08[a->m_bfme00 - 1];
	if (!((unsigned char)(e->m_bfme04 >> 30) & 1))
		e->bfmeV1239B();
	--a->m_bfme00;
	a->m_bfme08[a->m_bfme00] = v;
	++a->m_bfme00;
	if (!((unsigned char)(v->m_bfme04 >> 30) & 1))
		v->bfmeV1239A();
}
