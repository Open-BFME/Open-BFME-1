// cl: /O1
struct BfmeRefEMI
{
	unsigned short m_bfmeCount;
};

// TU-local view of the Apt allocator-hook pair table owned by Apt.cpp; the
// global itself is declared under its canonical spelling so it links.
struct BfmeStringPool3AF0
{
	void *m_bfmeF0;
	void (__cdecl *m_bfmeF1)(BfmeRefEMI *r);
};

extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
extern BfmeRefEMI *g_bfmeRefEMIa;
extern BfmeRefEMI *g_bfmeRefEMIb;

void bfmeGoEMIa()
{
	BfmeRefEMI *r = g_bfmeRefEMIa;
	if (--r->m_bfmeCount == 0)
		g_rva01337A30AllocPair->m_bfmeF1(r);
}

void bfmeGoEMIb()
{
	BfmeRefEMI *r = g_bfmeRefEMIb;
	if (--r->m_bfmeCount == 0)
		g_rva01337A30AllocPair->m_bfmeF1(r);
}
