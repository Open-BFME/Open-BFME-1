struct BfmeItemWB
{
	unsigned char m_bfmeHead[0x90];
};

class BfmeSubWB
{
public:
	void bfmeInitWB(BfmeItemWB *what);
};

class BfmeThingWB
{
public:
	void bfmeStepWB(void *what);
	void bfmeGoWB(void *what);
	unsigned char m_bfmeHead[8];
	BfmeItemWB m_bfmeItem;
	int m_bfmeFlags;
	BfmeSubWB m_bfmeSub;
};

void BfmeThingWB::bfmeGoWB(void *what)
{
	if ((m_bfmeFlags & 1) == 0)
	{
		m_bfmeSub.bfmeInitWB(&m_bfmeItem);
		m_bfmeFlags |= 1;
	}
	bfmeStepWB(what);
}
