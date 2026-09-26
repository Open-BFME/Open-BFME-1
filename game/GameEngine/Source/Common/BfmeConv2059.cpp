class BfmeNodeGH
{
public:
	unsigned char m_bfmeHeadGH[0x14];
	void *m_bfmeValueGH;
};

class BfmeMapGH
{
public:
	void bfmeLookupGH(BfmeNodeGH **out, void **key);

	BfmeNodeGH *m_bfmeEndGH;
};

class BfmeOwnerGH
{
public:
	void *bfmeFindGH(void *k);

	unsigned char m_bfmeGapGH[0x27c];
	BfmeMapGH m_bfmeMapGH;
};

void *BfmeOwnerGH::bfmeFindGH(void *k)
{
	if (k == 0)
	{
		return 0;
	}
	else
	{
		BfmeNodeGH *n;

		m_bfmeMapGH.bfmeLookupGH(&n, &k);

		if (n == m_bfmeMapGH.m_bfmeEndGH)
			return 0;

		return n->m_bfmeValueGH;
	}
}
