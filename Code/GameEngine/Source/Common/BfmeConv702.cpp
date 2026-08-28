class BfmeItemDHF
{
public:
	virtual void bfmeSpareDHF0();
	virtual void bfmeRunDHF();
};

struct BfmeNodeDHF
{
	BfmeNodeDHF *m_bfmeNext;
	unsigned char m_bfmeGap[4];
	BfmeItemDHF *m_bfmeItem;
};

class BfmeThingDHF
{
public:
	void bfmeGoDHF();
	unsigned char m_bfmeHead[0xc];
	BfmeNodeDHF *m_bfmeList;
};

void BfmeThingDHF::bfmeGoDHF()
{
	for (BfmeNodeDHF *n = m_bfmeList->m_bfmeNext; n != m_bfmeList; n = n->m_bfmeNext)
		n->m_bfmeItem->bfmeRunDHF();
}
