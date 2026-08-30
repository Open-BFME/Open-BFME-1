// Open-BFME5 conversions.

class BfmeE1215
{
public:
	virtual void bfmeV1215A();
	virtual void bfmeV1215B();
	unsigned m_bfme04;
};

class BfmeA1215
{
public:
	int m_bfme00;
	int m_bfme04;
	BfmeE1215 **m_bfme08;
	char m_bfmePad0c[0x60 - 0x0c];
	BfmeE1215 **m_bfme60;
};

class BfmeG1215
{
public:
	void bfmeStep1215C();
	int m_bfme00;
	int m_bfme04;
};

extern BfmeG1215 *g_bfme1215;

extern "C" void bfmeStep1215A(BfmeA1215 *a, const unsigned char **b);

void bfmeGo1215(BfmeA1215 *a, const unsigned char **b)
{
	const unsigned char *p;
	unsigned char c;
	BfmeE1215 *e;
	BfmeG1215 *g;

	p = *b;
	c = *p;
	*b = p + 1;
	e = a->m_bfme60[c];
	a->m_bfme08[a->m_bfme00] = e;
	++a->m_bfme00;
	if (!((unsigned char)(e->m_bfme04 >> 30) & 1))
		e->bfmeV1215A();
	bfmeStep1215A(a, b);
	e = a->m_bfme08[a->m_bfme00 - 1];
	if (!((unsigned char)(e->m_bfme04 >> 30) & 1))
		e->bfmeV1215B();
	--a->m_bfme00;
	g = g_bfme1215;
	if (g->m_bfme04 && a->m_bfme00 == 0)
		g->bfmeStep1215C();
}
