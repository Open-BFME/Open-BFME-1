// Open-BFME5 conversions.

// Node cleanup is the matched ?bfmeCleanup@Gen_00893990@@QAEXXZ (0x00893990,
// S3ChildTeardown.cpp), per callees.py on this body.
class Gen_00893990
{
public:
	void bfmeCleanup(void);
};

class BfmeNodeVMU
{
public:
	int m_bfme00;
	BfmeNodeVMU *m_bfme04;
};

extern void(__cdecl *g_bfmeFreeDWF)(void *p);

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
			reinterpret_cast<Gen_00893990 *>(p)->bfmeCleanup();
			g_bfmeFreeDWF(p);
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
		reinterpret_cast<Gen_00893990 *>(n)->bfmeCleanup();
		g_bfmeFreeDWF(n);
	}
}
