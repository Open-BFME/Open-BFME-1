// Open-BFME5 conversions.

class BfmeG1212
{
public:
	void bfmeStep1212C();
	int m_bfme00;
	int m_bfme04;
};

// The global at VA 0x01337810 is defined once in game/Libraries/Source/Apt/Apt.cpp
// as `struct Rva00899560Pool *g_rva01337810GcRoots`; this TU views it through
// its own local class, so the reference carries the canonical mangled name.
struct Rva00899560Pool;
extern Rva00899560Pool *g_rva01337810GcRoots;

static BfmeG1212 *localBfme1212()
{
	return (BfmeG1212 *)g_rva01337810GcRoots;
}

class Rva8CD130State;
struct Rva8CD130Context;

extern "C" void bfmeStep1212A(int *a, void *b);
void rva8CD130NamedDispatch(Rva8CD130State *state, Rva8CD130Context *context);

void bfmeGo1212(int *a, void *b)
{
	BfmeG1212 *g;

	bfmeStep1212A(a, b);
	rva8CD130NamedDispatch((Rva8CD130State *)a, (Rva8CD130Context *)b);
	g = localBfme1212();
	if (g->m_bfme04 && *a == 0)
		g->bfmeStep1212C();
}
