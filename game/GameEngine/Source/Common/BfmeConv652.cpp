class BfmeThingCVA
{
public:
	void bfmeApplyCVA();
	void bfmeGoCVA(void *what);
	unsigned char m_bfmeHead[0x1e8];
	int m_bfmeState;
	int m_bfmePrev;
};

void BfmeThingCVA::bfmeGoCVA(void *what)
{
	int v = m_bfmeState;
	if ((v | 0x10000) == 0x10001)
	{
		m_bfmeState = v ^ 0x10000;
		bfmeApplyCVA();
		return;
	}
	m_bfmePrev = v;
	m_bfmeState = 1;
	bfmeApplyCVA();
}
