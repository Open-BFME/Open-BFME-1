class BfmeItemDHG
{
public:
	virtual void bfmeSpareDHG0();
	virtual void bfmeSpareDHG1();
	virtual void bfmeSpareDHG2();
	virtual void bfmeSpareDHG3();
	virtual void bfmeSpareDHG4();
	virtual void bfmeSpareDHG5();
	virtual void bfmeSpareDHG6();
	virtual void bfmeSpareDHG7();
	virtual void bfmeSpareDHG8();
	virtual void bfmeSpareDHG9();
	virtual void bfmeSpareDHG10();
	virtual void bfmeSpareDHG11();
	virtual void bfmeSpareDHG12();
	virtual void bfmeSpareDHG13();
	virtual void bfmeSpareDHG14();
	virtual void bfmeSpareDHG15();
	virtual void bfmeSpareDHG16();
	virtual void bfmeSpareDHG17();
	virtual void bfmeRunDHG();
};

struct BfmeNodeDHG
{
	BfmeNodeDHG *m_bfmeNext;
	unsigned char m_bfmeGap[4];
	BfmeItemDHG *m_bfmeItem;
};

class BfmeThingDHG
{
public:
	void bfmeGoDHG();
	unsigned char m_bfmeHead[0x18];
	BfmeNodeDHG *m_bfmeList;
};

void BfmeThingDHG::bfmeGoDHG()
{
	for (BfmeNodeDHG *n = m_bfmeList->m_bfmeNext; n != m_bfmeList; n = n->m_bfmeNext)
		n->m_bfmeItem->bfmeRunDHG();
}
