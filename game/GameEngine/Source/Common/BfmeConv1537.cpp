// Open-BFME5 conversions.

void bfmeFreeVOK(void *p, unsigned n);

class BfmeItemVOK
{
public:
	virtual void bfmeDropVOK(int f);
};

struct BfmeNodeVOK
{
	BfmeNodeVOK *m_bfme00;
	BfmeNodeVOK *m_bfme04;
	BfmeItemVOK *m_bfme08;
};

class BfmeOwnerVOK
{
public:
	void bfmeClearVOK();
	char m_bfmePad0000[0x1298];
	BfmeNodeVOK *m_bfme1298;
};

void BfmeOwnerVOK::bfmeClearVOK()
{
	BfmeNodeVOK *p = m_bfme1298->m_bfme00;

	if (p != m_bfme1298)
	{
		do
		{
			BfmeNodeVOK *nx = p->m_bfme00;
			BfmeNodeVOK *pv = p->m_bfme04;
			BfmeItemVOK *v = p->m_bfme08;

			pv->m_bfme00 = nx;
			nx->m_bfme04 = pv;
			bfmeFreeVOK(p, 0xc);
			p = nx;
			if (v != 0)
				v->bfmeDropVOK(1);
		} while (p != m_bfme1298);
	}
}
