class BfmeItemDHE
{
public:
	virtual void bfmeRunDHE();
};

struct BfmeNodeDHE
{
	BfmeNodeDHE *m_bfmeNext;
	unsigned char m_bfmeGap[4];
	BfmeItemDHE *m_bfmeItem;
};

class BfmeThingDHE
{
public:
	void bfmeGoDHE();
	unsigned char m_bfmeHead[0xc];
	BfmeNodeDHE *m_bfmeList;
};

void BfmeThingDHE::bfmeGoDHE()
{
	for (BfmeNodeDHE *n = m_bfmeList->m_bfmeNext; n != m_bfmeList; n = n->m_bfmeNext)
		n->m_bfmeItem->bfmeRunDHE();
}
