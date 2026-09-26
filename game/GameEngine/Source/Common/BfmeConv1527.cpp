// Open-BFME5 conversions.

void bfmeFreeNodeVOB(void *p, unsigned n);

extern void(__stdcall *g_bfmeFreeVOB)(void *p);

struct BfmeNodeVOB
{
	BfmeNodeVOB *m_bfme00;
	BfmeNodeVOB *m_bfme04;
	void *m_bfme08;
};

class BfmeOwnerVOB
{
public:
	void bfmeClearVOB();
	char m_bfmePad000[0x60c];
	int m_bfme60c;
	char m_bfmePad610[0x3b4];
	BfmeNodeVOB *m_bfme9c4;
};

void BfmeOwnerVOB::bfmeClearVOB()
{
	BfmeNodeVOB *p = m_bfme9c4->m_bfme00;

	if (p != m_bfme9c4)
	{
		void(__stdcall *f)(void *) = g_bfmeFreeVOB;

		do
		{
			f(p->m_bfme08);

			BfmeNodeVOB *nx = p->m_bfme00;
			BfmeNodeVOB *pv = p->m_bfme04;

			pv->m_bfme00 = nx;
			nx->m_bfme04 = pv;
			bfmeFreeNodeVOB(p, 0xc);
			p = nx;
		} while (p != m_bfme9c4);
	}
	m_bfme60c = 0;
}
