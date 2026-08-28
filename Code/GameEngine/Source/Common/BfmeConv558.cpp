class BfmeSubBZC
{
public:
	void bfmeSetBZC(int value);
	unsigned char m_bfmeHead[8];
};

struct BfmeSrcBZC
{
	int m_bfmeVal;
};

class BfmeThingBZC
{
public:
	void bfmeGoBZC(BfmeSrcBZC *src, int value);
	unsigned char m_bfmeHead[0x1c];
	BfmeSubBZC m_bfmeSub;
	int m_bfmeA;
	int m_bfmeB;
};

void BfmeThingBZC::bfmeGoBZC(BfmeSrcBZC *src, int value)
{
	m_bfmeSub.bfmeSetBZC(src->m_bfmeVal);
	m_bfmeA = 0;
	m_bfmeB = value;
}
