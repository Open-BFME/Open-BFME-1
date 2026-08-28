class BfmeSubDBD
{
public:
	void bfmeTailDBD(void *a);
};

class BfmeThingDBD
{
public:
	void bfmeGoDBD(void *a);
	unsigned char m_bfmeHead[0x1bc];
	BfmeSubDBD m_bfmeSub;
};

void BfmeThingDBD::bfmeGoDBD(void *a)
{
	if (a == 0)
		return;
	m_bfmeSub.bfmeTailDBD(a);
}
