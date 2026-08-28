class BfmeItemRY
{
public:
	void bfmeDoRY(void *one, void *two);
};

struct BfmeNodeRY
{
	BfmeNodeRY *m_bfmeNext;
	void *m_bfmeGap;
	BfmeItemRY *m_bfmeItem;
};

class BfmeListRY
{
public:
	void bfmeAllRY(void *one, void *two);
	unsigned char m_bfmeHead[4];
	BfmeNodeRY *m_bfmeEnd;
};

void BfmeListRY::bfmeAllRY(void *one, void *two)
{
	for (BfmeNodeRY *at = m_bfmeEnd->m_bfmeNext; at != m_bfmeEnd; at = at->m_bfmeNext)
		at->m_bfmeItem->bfmeDoRY(one, two);
}
