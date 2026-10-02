// Open-BFME5 conversions.

class BfmeG1211
{
public:
	void bfmeStep1211C();
	int m_bfme00;
	int m_bfme04;
};

struct Rva00899560Pool;

extern Rva00899560Pool *g_rva01337810GcRoots;

class Rva8CD130State;
struct Rva8CD130Context;

extern "C" void bfmeStep1211A(int *a, void *b);
void rva8CD130NamedDispatch(Rva8CD130State *state, Rva8CD130Context *context);

void bfmeGo1211(int *a, void *b)
{
	BfmeG1211 *g;

	bfmeStep1211A(a, b);
	rva8CD130NamedDispatch((Rva8CD130State *)a, (Rva8CD130Context *)b);
	g = (BfmeG1211 *)g_rva01337810GcRoots;
	if (g->m_bfme04 && *a == 0)
		g->bfmeStep1211C();
}
