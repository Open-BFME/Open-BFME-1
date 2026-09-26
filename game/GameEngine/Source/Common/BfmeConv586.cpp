struct BfmeSrcCEC
{
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
};

class BfmeThingCEC
{
public:
	void bfmeBaseCEC(void *what);
	BfmeThingCEC *bfmeInitCEC(void *what, BfmeSrcCEC *src);
	unsigned char m_bfmeHead[4];
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
};

BfmeThingCEC *BfmeThingCEC::bfmeInitCEC(void *what, BfmeSrcCEC *src)
{
	bfmeBaseCEC(what);
	m_bfmeA = src->m_bfmeA;
	m_bfmeB = src->m_bfmeB;
	m_bfmeC = src->m_bfmeC;
	return this;
}
