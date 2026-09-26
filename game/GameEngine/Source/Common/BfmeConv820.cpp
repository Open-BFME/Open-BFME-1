// cl: /O1
struct BfmeRefEMI
{
	unsigned short m_bfmeCount;
};

struct BfmeVtblEMI
{
	void *m_bfmeF0;
	void (__cdecl *m_bfmeF1)(BfmeRefEMI *r);
};

extern BfmeVtblEMI *g_bfmeVtblEMI;
extern BfmeRefEMI *g_bfmeRefEMIa;
extern BfmeRefEMI *g_bfmeRefEMIb;

void bfmeGoEMIa()
{
	BfmeRefEMI *r = g_bfmeRefEMIa;
	if (--r->m_bfmeCount == 0)
		g_bfmeVtblEMI->m_bfmeF1(r);
}

void bfmeGoEMIb()
{
	BfmeRefEMI *r = g_bfmeRefEMIb;
	if (--r->m_bfmeCount == 0)
		g_bfmeVtblEMI->m_bfmeF1(r);
}
