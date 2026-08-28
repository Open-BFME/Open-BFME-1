class BfmeThingCVD
{
public:
	void bfmeApplyCVD();
	void bfmeGoCVD(void *what);
	unsigned char m_bfmeHead[0x1e8];
	int m_bfmeState;
	int m_bfmePrev;
};

void BfmeThingCVD::bfmeGoCVD(void *what)
{
	int v = m_bfmeState;
	if ((v | 0x10000) == 0x10004)
	{
		m_bfmeState = v ^ 0x10000;
		bfmeApplyCVD();
		return;
	}
	m_bfmePrev = v;
	m_bfmeState = 4;
	bfmeApplyCVD();
}
