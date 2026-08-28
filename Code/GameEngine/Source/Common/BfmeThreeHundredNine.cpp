class BfmeNodeRB
{
public:
	void bfmeTellRB(void *what);
	unsigned char m_bfmeHead[0x104];
	BfmeNodeRB *m_bfmeNext;
};

class BfmeHolderRB
{
public:
	virtual void bfmeSpareRB0();
	virtual void bfmeSpareRB1();
	virtual void bfmeSpareRB2();
	virtual void bfmeSpareRB3();
	virtual void bfmeSpareRB4();
	virtual void bfmeSpareRB5();
	virtual void bfmeSpareRB6();
	virtual void bfmeSpareRB7();
	virtual void bfmeSpareRB8();
	virtual void bfmeSpareRB9();
	virtual void bfmeSpareRBA();
	virtual void bfmeSpareRBB();
	virtual BfmeNodeRB *bfmeHeadRB();
	void bfmeTellAllRB(void *what);
};

void BfmeHolderRB::bfmeTellAllRB(void *what)
{
	for (BfmeNodeRB *at = bfmeHeadRB(); at != 0; at = at->m_bfmeNext)
		at->bfmeTellRB(what);
}
