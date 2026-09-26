// Open-BFME5 conversions.

void bfmeFreeNodeVOA(void *p, unsigned n);

extern void(__stdcall *g_bfmeFreeVOA)(void *p);

struct BfmeNodeVOA
{
	BfmeNodeVOA *m_bfme00;
	BfmeNodeVOA *m_bfme04;
	void *m_bfme08;
};

class BfmeOwnerVOA
{
public:
	void bfmeClearVOA();
	char m_bfmePad000[0x608];
	int m_bfme608;
	char m_bfmePad60c[0x3b4];
	BfmeNodeVOA *m_bfme9c0;
};

void BfmeOwnerVOA::bfmeClearVOA()
{
	BfmeNodeVOA *p = m_bfme9c0->m_bfme00;

	if (p != m_bfme9c0)
	{
		void(__stdcall *f)(void *) = g_bfmeFreeVOA;

		do
		{
			f(p->m_bfme08);

			BfmeNodeVOA *nx = p->m_bfme00;
			BfmeNodeVOA *pv = p->m_bfme04;

			pv->m_bfme00 = nx;
			nx->m_bfme04 = pv;
			bfmeFreeNodeVOA(p, 0xc);
			p = nx;
		} while (p != m_bfme9c0);
	}
	m_bfme608 = 0;
}
