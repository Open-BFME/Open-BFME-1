struct BfmeMarkXB
{
	unsigned char m_bfmeOneXB;
	unsigned char m_bfmeTwoXB;
};

class BfmeItemXB
{
public:
	virtual void bfmeV0XB();
	virtual void bfmeV1XB();
	virtual void bfmeV2XB();
	virtual void bfmeV3XB();
	virtual void bfmeV4XB();
	virtual void bfmeV5XB();
	virtual void bfmeV6XB();
	virtual void bfmeV7XB();
	virtual void bfmeV8XB();
	virtual void bfmeV9XB();
	virtual void bfmeMarkedXB(BfmeMarkXB *mark);
};

class BfmeSinkXB
{
public:
	virtual void bfmeS0XB();
	virtual void bfmeS1XB();
	virtual void bfmeS2XB();
	virtual void bfmeTakeXB(BfmeItemXB *item);
};

class BfmeBaseXB
{
public:
	void bfmeAddXB(BfmeItemXB *item);
	void bfmeLinkXB(BfmeItemXB *item);
};

class BfmeHolderXB
{
public:
	void bfmeOnXB(BfmeItemXB *item);

	unsigned char m_bfmeHeadXB[0x284];
	BfmeSinkXB *m_bfmeSinkXB;
};

void BfmeHolderXB::bfmeOnXB(BfmeItemXB *item)
{
	BfmeMarkXB mark;
	unsigned char set = 1;

	mark.m_bfmeOneXB = set;
	mark.m_bfmeTwoXB = set;
	item->bfmeMarkedXB(&mark);

	BfmeBaseXB *base = (BfmeBaseXB *)((char *)this - 8);
	base->bfmeAddXB(item);
	base->bfmeLinkXB(item);

	if (m_bfmeSinkXB)
		m_bfmeSinkXB->bfmeTakeXB(item);
}
