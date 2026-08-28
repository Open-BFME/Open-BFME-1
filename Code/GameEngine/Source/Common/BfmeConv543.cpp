class BfmeThingBWB
{
public:
	void bfmeBaseBWB(void *what);
	BfmeThingBWB *bfmeInitBWB(void *what, int value);
	unsigned char m_bfmeHead[4];
	int m_bfmeNum;
	int m_bfmeA;
	int m_bfmeB;
};

BfmeThingBWB *BfmeThingBWB::bfmeInitBWB(void *what, int value)
{
	bfmeBaseBWB(what);
	m_bfmeA = value;
	m_bfmeB = value;
	m_bfmeNum = 1;
	return this;
}
