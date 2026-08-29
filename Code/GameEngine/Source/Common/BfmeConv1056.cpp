// Open-BFME5 conversions.

struct BfmeVt1056
{
	char m_bfmePad[0x104];
	void (__stdcall *m_bfmeFn)(void *o, int a, int b);
};

struct BfmeE1056
{
	BfmeVt1056 *m_bfmeVt;
};

extern BfmeE1056 *g_bfmeE1056;
extern char g_bfmeFlag1056;

void bfmeGo1056E(void)
{
	g_bfmeFlag1056 = 1;

	BfmeE1056 *p = g_bfmeE1056;

	p->m_bfmeVt->m_bfmeFn(p, 0, 0);
	g_bfmeE1056->m_bfmeVt->m_bfmeFn(g_bfmeE1056, 1, 0);
}
