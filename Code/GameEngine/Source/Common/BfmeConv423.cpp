struct BfmeHeadAUD
{
	unsigned char m_bfmePad[4];
	void *m_bfmeOne;
	BfmeHeadAUD *m_bfmeTwo;
	BfmeHeadAUD *m_bfmeThree;
};

class BfmeListAUD
{
public:
	void bfmeDropAUD(void *what);
	BfmeHeadAUD *m_bfmeHead;
	int m_bfmeCount;
};

class BfmeThingAUD
{
public:
	void bfmeGoAUD();
	unsigned char m_bfmeHead[0x40];
	bool m_bfmeFlag;
	unsigned char m_bfmeGap[3];
	BfmeListAUD m_bfmeList;
};

void BfmeThingAUD::bfmeGoAUD()
{
	BfmeListAUD *list = &m_bfmeList;
	m_bfmeFlag = false;
	if (list->m_bfmeCount != 0)
	{
		list->bfmeDropAUD(list->m_bfmeHead->m_bfmeOne);
		list->m_bfmeHead->m_bfmeTwo = list->m_bfmeHead;
		list->m_bfmeHead->m_bfmeOne = 0;
		list->m_bfmeHead->m_bfmeThree = list->m_bfmeHead;
		list->m_bfmeCount = 0;
	}
}
