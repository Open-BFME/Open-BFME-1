// Open-BFME5 conversions.

class BfmeNodeVOH
{
public:
	void bfmeCleanupVOH();
	int m_bfme00;
	BfmeNodeVOH *m_bfme04;
};

extern void(__cdecl *g_bfmeFreeVOH)(void *p);

class BfmeListVOH
{
public:
	void bfmeClearVOH();
	BfmeNodeVOH *m_bfme00;
};

void BfmeListVOH::bfmeClearVOH()
{
	while (m_bfme00 != 0)
	{
		BfmeNodeVOH *p = m_bfme00;

		if (p != 0)
		{
			BfmeNodeVOH *nx = p->m_bfme04;

			p->bfmeCleanupVOH();
			g_bfmeFreeVOH(p);
			m_bfme00 = nx;
		}
	}
}
