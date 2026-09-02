// ?bfmeAddYW@BfmeLinkYW@@QAEXPAV1@@Z
// partial score=0.58 date=2026-09-02
// cl: /O2 /Ob0

class BfmeLinkYW
{
public:
	BfmeLinkYW *m_bfmeUnknown;
	BfmeLinkYW *m_bfmeNext;

	void bfmeAddYW(BfmeLinkYW *node);
};

void BfmeLinkYW::bfmeAddYW(BfmeLinkYW *node)
{
	BfmeLinkYW *walk = this;
	BfmeLinkYW *next = walk->m_bfmeNext;
	if (next)
	{
		do
		{
			walk = next;
			next = walk->m_bfmeNext;
		} while (next);
	}

	walk->m_bfmeNext = node;
}
