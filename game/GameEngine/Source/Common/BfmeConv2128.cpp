struct BfmeNodeABB
{
	unsigned char m_bfmeHeadABB[0x14];
	void *m_bfme14ABB;
};

struct BfmeIterABB
{
	BfmeNodeABB *m_bfmeNodeABB;
};

class BfmeSubABB
{
public:
	void bfmeRangeABB(BfmeIterABB *first, BfmeIterABB *last);

	BfmeNodeABB *m_bfmeHeadABB;
};

BfmeNodeABB *__stdcall bfmeDiagABB(BfmeIterABB *it, const void *desc);

extern void *const g_bfmeDescABB;

class BfmeHostABB
{
public:
	void *bfmeFrontABB(BfmeIterABB last);

	unsigned char m_bfmeHeadHABB[4];
	BfmeSubABB m_bfme04ABB;
};

void *BfmeHostABB::bfmeFrontABB(BfmeIterABB last)
{
	BfmeIterABB first;

	m_bfme04ABB.bfmeRangeABB(&first, &last);

	BfmeNodeABB *n = first.m_bfmeNodeABB;

	if (n == m_bfme04ABB.m_bfmeHeadABB)
	{
		last.m_bfmeNodeABB = (BfmeNodeABB *)0xdead0003;
		n = bfmeDiagABB(&last, &g_bfmeDescABB);
	}

	return n->m_bfme14ABB;
}
