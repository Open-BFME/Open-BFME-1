class BfmeFoundAKB
{
public:
	virtual void bfmeSpareAKB0();
	virtual bool bfmeTestAKB();
};

class BfmeSubAKB
{
public:
	BfmeFoundAKB *bfmeFindAKB(int what);
};

class BfmeThingAKB
{
public:
	bool bfmeFirstAKB(int *what);
	bool bfmeAskAKB(int *what);
	unsigned char m_bfmeHead[8];
	BfmeSubAKB *m_bfmeSub;
};

bool BfmeThingAKB::bfmeAskAKB(int *what)
{
	if (!bfmeFirstAKB(what))
		return false;
	BfmeFoundAKB *found = m_bfmeSub->bfmeFindAKB(0x2e);
	if (found != 0 && !found->bfmeTestAKB())
		return *what == 0x1b;
	return true;
}
