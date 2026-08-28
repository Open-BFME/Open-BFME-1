struct BfmeGlobalCHE
{
	unsigned char m_bfmeHead[0x3c];
	unsigned int m_bfmeNow;
};

extern BfmeGlobalCHE *bfmeTheCHE;

class BfmeThingCHE
{
public:
	void bfmeUpdateCHE();
	int bfmeGoCHE();
	unsigned char m_bfmeHead[0x98];
	unsigned int m_bfmeNext;
	int m_bfmeCached;
};

int BfmeThingCHE::bfmeGoCHE()
{
	unsigned int now = bfmeTheCHE->m_bfmeNow;
	if (now >= m_bfmeNext)
	{
		m_bfmeNext = now + 0x19;
		bfmeUpdateCHE();
	}
	return m_bfmeCached;
}
