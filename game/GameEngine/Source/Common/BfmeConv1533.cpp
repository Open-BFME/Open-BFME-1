// Open-BFME5 conversions.

// Retail calls 0x00893990 directly: the matched S3ChildTeardown.cpp cleanup.
class Gen_00893990
{
public:
	void bfmeCleanup();
};

class BfmeNodeVOH
{
public:
	int m_bfme00;
	BfmeNodeVOH *m_bfme04;
};

extern void(__cdecl *g_bfmeFreeDWF)(void *p);

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

			((Gen_00893990 *)p)->bfmeCleanup();
			g_bfmeFreeDWF(p);
			m_bfme00 = nx;
		}
	}
}
