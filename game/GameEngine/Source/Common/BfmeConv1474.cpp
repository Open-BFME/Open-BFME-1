// Open-BFME5 conversions.

class BfmeNodeVMU
{
public:
	void bfmeCleanupVMU();
	int m_bfme00;
	BfmeNodeVMU *m_bfme04;
};

extern void(__cdecl *g_bfmeFreeVMU)(void *p);

class BfmeListVMU
{
public:
	void bfmeEraseVMU(BfmeNodeVMU **it);
	BfmeNodeVMU *m_bfme00;
};

void BfmeListVMU::bfmeEraseVMU(BfmeNodeVMU **it)
{
	BfmeNodeVMU *t = *it;
	BfmeNodeVMU *p = m_bfme00;
	BfmeNodeVMU *q;
	BfmeNodeVMU *n;

	if (t == p)
	{
		if (p != 0)
		{
			n = p->m_bfme04;
			p->bfmeCleanupVMU();
			g_bfmeFreeVMU(p);
			m_bfme00 = n;
		}
		return;
	}
	q = m_bfme00;
	while (q != 0)
	{
		if (q->m_bfme04 == t)
			break;
		q = q->m_bfme04;
	}
	n = q->m_bfme04;
	if (n != 0)
	{
		q->m_bfme04 = n->m_bfme04;
		n->bfmeCleanupVMU();
		g_bfmeFreeVMU(n);
	}
}
