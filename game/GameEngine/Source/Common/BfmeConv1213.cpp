// Open-BFME5 conversions.

class BfmeE1213
{
public:
	virtual void bfmeV1213();
	unsigned m_bfme04;
};

class BfmeA1213
{
public:
	int m_bfme00;
	int m_bfme04;
	BfmeE1213 **m_bfme08;
	char m_bfmePad0c[0x60 - 0x0c];
	BfmeE1213 **m_bfme60;
};

class BfmeG1213
{
public:
	void bfmeStep1213C();
	int m_bfme00;
	int m_bfme04;
};

extern BfmeG1213 *g_bfme1213;

extern "C" void bfmeStep1213A(BfmeA1213 *a, const unsigned char **b);
extern "C" void bfmeStep1213B(BfmeA1213 *a, const unsigned char **b);

void bfmeGo1213(BfmeA1213 *a, const unsigned char **b)
{
	const unsigned char *p;
	unsigned char c;
	BfmeE1213 *e;
	BfmeG1213 *g;

	p = *b;
	c = *p;
	*b = p + 1;
	e = a->m_bfme60[c];
	a->m_bfme08[a->m_bfme00] = e;
	++a->m_bfme00;
	if (!((unsigned char)(e->m_bfme04 >> 30) & 1))
		e->bfmeV1213();
	bfmeStep1213A(a, b);
	bfmeStep1213B(a, b);
	g = g_bfme1213;
	if (g->m_bfme04 && a->m_bfme00 == 0)
		g->bfmeStep1213C();
}
