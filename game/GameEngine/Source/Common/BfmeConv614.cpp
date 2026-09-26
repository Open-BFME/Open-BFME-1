struct BfmeElemCJF
{
	unsigned char m_bfmeHead[8];
	void *m_bfmeVal;
	unsigned char m_bfmeTail[0x18];
};

class BfmeThingCJF
{
public:
	void bfmeNotifyCJF();
	void bfmeGoCJF(void *what);
	unsigned char m_bfmeHead[0x2c];
	BfmeElemCJF *volatile m_bfmeBegin;
	BfmeElemCJF *m_bfmeEnd;
};

void BfmeThingCJF::bfmeGoCJF(void *what)
{
	if (m_bfmeEnd - m_bfmeBegin != 0)
		m_bfmeBegin->m_bfmeVal = what;
	bfmeNotifyCJF();
}
