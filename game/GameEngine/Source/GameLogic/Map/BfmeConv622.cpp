struct BfmeItemCMC
{
	void bfmeInitCMC(void *what);
	unsigned char m_bfmeHead[0x18];
};

class BfmeThingCMC
{
public:
	int bfmeAddCMC(void *what);
	unsigned char m_bfmeHead[0x28];
	int m_bfmeCount;
	BfmeItemCMC m_bfmeItems[0x20];
};

int BfmeThingCMC::bfmeAddCMC(void *what)
{
	int n = m_bfmeCount;
	if (n < 0x20)
	{
		m_bfmeCount = n + 1;
		m_bfmeItems[n].bfmeInitCMC(what);
		return n;
	}
	return -1;
}
