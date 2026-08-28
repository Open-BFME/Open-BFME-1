struct BfmeHeadAUC
{
	unsigned char m_bfmePad[4];
	void *m_bfmeOne;
	BfmeHeadAUC *m_bfmeTwo;
	BfmeHeadAUC *m_bfmeThree;
};

class BfmeThingAUC
{
public:
	void bfmeDropAUC(void *what);
	void bfmeGoAUC();
	BfmeHeadAUC *m_bfmeHead;
	int m_bfmeCount;
	unsigned char m_bfmeGap[8];
	bool m_bfmeFlag;
};

void BfmeThingAUC::bfmeGoAUC()
{
	if (m_bfmeCount != 0)
	{
		bfmeDropAUC(m_bfmeHead->m_bfmeOne);
		m_bfmeHead->m_bfmeTwo = m_bfmeHead;
		m_bfmeHead->m_bfmeOne = 0;
		m_bfmeHead->m_bfmeThree = m_bfmeHead;
		m_bfmeCount = 0;
	}
	m_bfmeFlag = true;
}
