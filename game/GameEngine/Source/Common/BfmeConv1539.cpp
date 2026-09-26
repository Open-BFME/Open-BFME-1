// Open-BFME5 conversions.

void bfmeFreeVOL(void *p, unsigned n);

class BfmeItemVOL
{
public:
	virtual void bfmeDropVOL(int f);
};

struct BfmeNodeVOL
{
	BfmeNodeVOL *m_bfme00;
	BfmeNodeVOL *m_bfme04;
	BfmeItemVOL *m_bfme08;
};

class BfmeOwnerVOL
{
public:
	void bfmeClearVOL();
	char m_bfmePad000[0x2ac];
	BfmeNodeVOL *m_bfme2ac;
};

void BfmeOwnerVOL::bfmeClearVOL()
{
	BfmeNodeVOL *p = m_bfme2ac->m_bfme00;

	if (p != m_bfme2ac)
	{
		do
		{
			BfmeNodeVOL *nx = p->m_bfme00;
			BfmeNodeVOL *pv = p->m_bfme04;
			BfmeItemVOL *v = p->m_bfme08;

			pv->m_bfme00 = nx;
			nx->m_bfme04 = pv;
			bfmeFreeVOL(p, 0xc);
			p = nx;
			if (v != 0)
				v->bfmeDropVOL(1);
		} while (p != m_bfme2ac);
	}
}
