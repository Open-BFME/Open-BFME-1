// Open-BFME5 conversions.

class BfmeE1214
{
public:
	virtual void bfmeV1214();
	unsigned m_bfme04;
};

class BfmeA1214
{
public:
	int m_bfme00;
	int m_bfme04;
	BfmeE1214 **m_bfme08;
	char m_bfmePad0c[0x60 - 0x0c];
	BfmeE1214 **m_bfme60;
};

class BfmeG1214
{
public:
	void bfmeStep1214C();
	int m_bfme00;
	int m_bfme04;
};

struct Rva00899560Pool;

extern Rva00899560Pool *g_rva01337810GcRoots;

class Rva8CD130State;
struct Rva8CD130Context;

extern "C" void bfmeStep1214A(BfmeA1214 *a, const unsigned char **b);
void rva8CD130NamedDispatch(Rva8CD130State *state, Rva8CD130Context *context);

void bfmeGo1214(BfmeA1214 *a, const unsigned char **b)
{
	const unsigned char *p;
	unsigned char c;
	BfmeE1214 *e;
	BfmeG1214 *g;

	p = *b;
	c = *p;
	*b = p + 1;
	e = a->m_bfme60[c];
	a->m_bfme08[a->m_bfme00] = e;
	++a->m_bfme00;
	if (!((unsigned char)(e->m_bfme04 >> 30) & 1))
		e->bfmeV1214();
	bfmeStep1214A(a, b);
	rva8CD130NamedDispatch((Rva8CD130State *)a, (Rva8CD130Context *)b);
	g = (BfmeG1214 *)g_rva01337810GcRoots;
	if (g->m_bfme04 && a->m_bfme00 == 0)
		g->bfmeStep1214C();
}
