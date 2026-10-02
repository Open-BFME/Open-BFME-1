// Open-BFME5 conversions.

class BfmeG1212
{
public:
	void bfmeStep1212C();
	int m_bfme00;
	int m_bfme04;
};

extern BfmeG1212 *g_bfme1212;

class Rva8CD130State;
struct Rva8CD130Context;

extern "C" void bfmeStep1212A(int *a, void *b);
void rva8CD130NamedDispatch(Rva8CD130State *state, Rva8CD130Context *context);

void bfmeGo1212(int *a, void *b)
{
	BfmeG1212 *g;

	bfmeStep1212A(a, b);
	rva8CD130NamedDispatch((Rva8CD130State *)a, (Rva8CD130Context *)b);
	g = g_bfme1212;
	if (g->m_bfme04 && *a == 0)
		g->bfmeStep1212C();
}
