struct BfmeElemCJG
{
	unsigned char m_bfmeHead[0xc];
	void *m_bfmeVal;
	unsigned char m_bfmeTail[0x14];
};

class BfmeThingCJG
{
public:
	void bfmeNotifyCJG();
	void bfmeGoCJG(void *what);
	unsigned char m_bfmeHead[0x2c];
	BfmeElemCJG *volatile m_bfmeBegin;
	BfmeElemCJG *m_bfmeEnd;
};

void BfmeThingCJG::bfmeGoCJG(void *what)
{
	if (m_bfmeEnd - m_bfmeBegin != 0)
		m_bfmeBegin->m_bfmeVal = what;
	bfmeNotifyCJG();
}
