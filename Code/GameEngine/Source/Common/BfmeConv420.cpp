void *bfmeMakeASB(int one, int two);

class BfmeThingASB
{
public:
	BfmeThingASB *bfmeInitASB();
	int m_bfmeZero;
	unsigned char m_bfmeGap[4];
	void *m_bfmeGot;
	unsigned int m_bfmeScale;
	int m_bfmeCount;
	bool m_bfmeFlag;
};

BfmeThingASB *BfmeThingASB::bfmeInitASB()
{
	m_bfmeZero = 0;
	m_bfmeGot = bfmeMakeASB(0, 0);
	m_bfmeScale = 0x3f800000;
	m_bfmeCount = 0;
	m_bfmeFlag = false;
	return this;
}
