class BfmeThingBWA
{
public:
	void bfmeBaseBWA(void *what);
	BfmeThingBWA *bfmeInitBWA(void *what, bool flag);
	unsigned char m_bfmeHead[4];
	int m_bfmeNum;
	bool m_bfmeA;
	bool m_bfmeB;
};

BfmeThingBWA *BfmeThingBWA::bfmeInitBWA(void *what, bool flag)
{
	bfmeBaseBWA(what);
	m_bfmeA = flag;
	m_bfmeB = flag;
	m_bfmeNum = 0;
	return this;
}
