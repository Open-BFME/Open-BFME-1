struct BfmeResultCCH
{
	unsigned char m_bfmeHead[8];
	void *m_bfmeVal;
};

class BfmeSubCCH
{
public:
	BfmeResultCCH *bfmeGetCCH();
};

class BfmeThingCCH
{
public:
	int bfmeGoCCH(void *what);
	BfmeSubCCH *m_bfmeSub;
};

int bfmeCallCCH(void *value, void *what, int spare);

int BfmeThingCCH::bfmeGoCCH(void *what)
{
	BfmeSubCCH *sub = m_bfmeSub;
	if (sub == 0)
		return 0;
	void *value = sub->bfmeGetCCH()->m_bfmeVal;
	return bfmeCallCCH(value, what, 0);
}
