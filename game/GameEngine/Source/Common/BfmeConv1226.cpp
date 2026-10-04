// Open-BFME5 conversions.

class BfmeE1226
{
public:
	int m_bfme00;
	void *m_bfme04;
};

struct BfmeP1226
{
	int m_bfme00;
	BfmeE1226 **m_bfme04;
};

class BfmeR1226
{
public:
	void bfmeLine1226(char *a);
};

// Retail 0x008CCED0 is the gen-asm dump body ?d_008cced0@@YAXXZ (owned by
// game/gen_asm/d_008cb600.asm); the bfmeAdd1226@BfmeR1226 spelling was a pin
// for that address, not a definition.  The callee is thiscall with two stack
// arguments, so route it through a member pointer (same convention as
// Rva003855F0Transition.cpp); the self type must be complete or the compiler
// emits a runtime adjustor.
extern void d_008cced0();

struct Rva008CCED0Self { int m_pad; };

// The global stack object itself carries the defining name; the methods keep
// their own pinned class spelling, so the access goes through a cast.
struct Rva008AE770Stack;
extern Rva008AE770Stack Rva008AE770TheStack;
extern char g_bfmeStr1226[];

class BfmeA1226
{
public:
	void bfmeDump1226(void *a, int k);
	int m_bfme00;
	BfmeP1226 *m_bfme04;
};

void BfmeA1226::bfmeDump1226(void *a, int k)
{
	int i;
	BfmeE1226 *e;

	for (i = 0; i < m_bfme04[k].m_bfme00; ++i) {
		e = m_bfme04[k].m_bfme04[i];
		if (e->m_bfme00 == 1) {
			BfmeR1226 *stack = (BfmeR1226 *)&Rva008AE770TheStack;
			union { void (*raw)(); void (Rva008CCED0Self::*member)(void *, void *, int); } add;
			add.raw = d_008cced0;
			((Rva008CCED0Self *)stack->*add.member)(e->m_bfme04, a, -1);
			stack->bfmeLine1226(g_bfmeStr1226);
		}
	}
}
