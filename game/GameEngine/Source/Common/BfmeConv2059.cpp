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

// The map lookup is reached through ILT 0x00018C5A (body 0x006109B0), which the
// ledger defines as ?j_00018c5a@@YAXXZ; the call names it through a member pointer.
extern void j_00018c5a(void);

void *BfmeOwnerGH::bfmeFindGH(void *k)
{
	if (k == 0)
	{
		return 0;
	}
	else
	{
		BfmeNodeGH *n;

		union { void (*raw)(void); void (BfmeMapGH::*member)(BfmeNodeGH **, void **); } call;
		call.raw = j_00018c5a;
		(m_bfmeMapGH.*call.member)(&n, &k);

		if (n == m_bfmeMapGH.m_bfmeEndGH)
			return 0;

		return n->m_bfmeValueGH;
	}
}
