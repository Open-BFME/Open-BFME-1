class BfmeR1094;

class BfmeK1094
{
public:
	BfmeR1094 *bfmeCur1094();
	void bfmeApplyABG(void *a, void *b);
};

struct BfmeNodeABG
{
	BfmeNodeABG *m_bfmeNextABG;
	BfmeNodeABG *m_bfmePrevABG;
	BfmeK1094 *m_bfme08ABG;
};

class BfmeHostABG
{
public:
	void bfmeVisitABG(void *a, void *b);

	unsigned char m_bfmeHeadABG[4];
	BfmeNodeABG *m_bfme04ABG;
};

void BfmeHostABG::bfmeVisitABG(void *a, void *b)
{
	for (BfmeNodeABG *n = m_bfme04ABG->m_bfmeNextABG; n != m_bfme04ABG; n = n->m_bfmeNextABG)
	{
		BfmeK1094 *it = n->m_bfme08ABG;

		if (it->bfmeCur1094() != 0)
		{
			it->bfmeApplyABG(a, b);
			return;
		}
	}
}
