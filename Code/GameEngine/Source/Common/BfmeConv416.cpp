class BfmeSubARB
{
public:
	virtual void bfmeSpareARB0();
	virtual void bfmeSpareARB1();
	virtual void bfmeSpareARB2();
	virtual void bfmeSpareARB3();
	virtual void bfmeSpareARB4();
	virtual void bfmeSpareARB5();
	virtual void bfmeSpareARB6();
	virtual void bfmeSpareARB7();
	virtual void bfmeSpareARB8();
	virtual void bfmeSpareARB9();
	virtual void *bfmeTakeARB();
};

class BfmeGotARB
{
public:
	void bfmeDropARB(int what);
};

class BfmeThingARB
{
public:
	void bfmeGoARB();
	unsigned char m_bfmeHead[8];
	BfmeSubARB *m_bfmeSub;
	unsigned char m_bfmeGap[0x18];
	int m_bfmeOne;
	int m_bfmeTwo;
	int m_bfmeThree;
};

void BfmeThingARB::bfmeGoARB()
{
	m_bfmeOne = 0;
	m_bfmeTwo = 0;
	m_bfmeThree = 0;
	BfmeGotARB *got = (BfmeGotARB *)m_bfmeSub->bfmeTakeARB();
	if (got != 0)
		got->bfmeDropARB(4);
}
