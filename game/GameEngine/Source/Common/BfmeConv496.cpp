class BfmeOuterBNE
{
public:
	void bfmeDoBNE();
};

class BfmeThingBNE
{
public:
	int bfmeGoBNE();
	unsigned char m_bfmeHead[0x10];
	int m_bfmeCount;
};

int BfmeThingBNE::bfmeGoBNE()
{
	int left = m_bfmeCount;
	if (left > 0)
	{
		--left;
		m_bfmeCount = left;
		if (left == 0)
			((BfmeOuterBNE *)((char *)this - 0x10))->bfmeDoBNE();
	}
	return 1;
}
