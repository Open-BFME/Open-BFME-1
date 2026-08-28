class BfmeThingCVB
{
public:
	void bfmeApplyCVB();
	void bfmeGoCVB(void *what);
	unsigned char m_bfmeHead[0x1e8];
	int m_bfmeState;
	int m_bfmePrev;
};

void BfmeThingCVB::bfmeGoCVB(void *what)
{
	int v = m_bfmeState;
	if ((v | 0x10000) == 0x10002)
	{
		m_bfmeState = v ^ 0x10000;
		bfmeApplyCVB();
		return;
	}
	m_bfmePrev = v;
	m_bfmeState = 2;
	bfmeApplyCVB();
}
