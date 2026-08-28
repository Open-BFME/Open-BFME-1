extern "C" unsigned char bfmeRegZB[];

class BfmeSubZB
{
public:
	void bfmeDropZB(void *reg);
};

class BfmeThingZB
{
public:
	void bfmeResetZB();
	BfmeSubZB *m_bfmeSub;
	int m_bfmeOne;
	unsigned short m_bfmeTwo;
	unsigned short m_bfmeThree;
	unsigned int m_bfmeFlags;
};

void BfmeThingZB::bfmeResetZB()
{
	BfmeSubZB *sub = m_bfmeSub;
	if (sub != 0)
	{
		sub->bfmeDropZB(bfmeRegZB);
		m_bfmeSub = 0;
	}
	unsigned int flags = m_bfmeFlags;
	flags &= 0xfe000040;
	flags |= 0x40;
	m_bfmeOne = 0;
	m_bfmeThree = 0;
	m_bfmeTwo = 0;
	m_bfmeFlags = flags;
}
