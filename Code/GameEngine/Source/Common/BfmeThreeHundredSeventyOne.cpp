struct BfmeHeadXA
{
	unsigned char m_bfmePad[4];
	void *m_bfmeOne;
	BfmeHeadXA *m_bfmeTwo;
	BfmeHeadXA *m_bfmeThree;
};

class BfmeListXA
{
public:
	void bfmeDropXA(void *what);
	BfmeHeadXA *m_bfmeHead;
	int m_bfmeCount;
};

class BfmeThingXA
{
public:
	void bfmeClearXA();
	unsigned char m_bfmeHead[0x550];
	BfmeListXA m_bfmeList;
};

void BfmeThingXA::bfmeClearXA()
{
	BfmeListXA *list = &m_bfmeList;
	if (list->m_bfmeCount != 0)
	{
		list->bfmeDropXA(list->m_bfmeHead->m_bfmeOne);
		list->m_bfmeHead->m_bfmeTwo = list->m_bfmeHead;
		list->m_bfmeHead->m_bfmeOne = 0;
		list->m_bfmeHead->m_bfmeThree = list->m_bfmeHead;
		list->m_bfmeCount = 0;
	}
}
