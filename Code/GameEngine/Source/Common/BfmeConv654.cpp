class BfmeThingCVC
{
public:
	void bfmeApplyCVC();
	void bfmeGoCVC(void *what);
	unsigned char m_bfmeHead[0x1e8];
	int m_bfmeState;
	int m_bfmePrev;
};

void BfmeThingCVC::bfmeGoCVC(void *what)
{
	int v = m_bfmeState;
	if ((v | 0x10000) == 0x10008)
	{
		m_bfmeState = v ^ 0x10000;
		bfmeApplyCVC();
		return;
	}
	m_bfmePrev = v;
	m_bfmeState = 8;
	bfmeApplyCVC();
}
