struct BfmeSrcBRC
{
	unsigned char m_bfmeHead[4];
	unsigned char m_bfmeRest[4];
};

struct BfmeSubBRC
{
	void bfmeSetBRC(void *what);
	unsigned char m_bfmeHead[4];
};

class BfmeThingBRC
{
public:
	BfmeThingBRC *bfmeGoBRC(BfmeSrcBRC *src);
	int m_bfmeZero;
	BfmeSubBRC m_bfmeSub;
};

BfmeThingBRC *BfmeThingBRC::bfmeGoBRC(BfmeSrcBRC *src)
{
	m_bfmeZero = 0;
	m_bfmeSub.bfmeSetBRC(src->m_bfmeRest);
	return this;
}
