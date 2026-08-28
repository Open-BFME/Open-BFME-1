extern "C" unsigned char bfmeTextAIB[];

struct BfmeHeadAIB
{
	unsigned char m_bfmePad[4];
	void *m_bfmeOne;
	BfmeHeadAIB *m_bfmeTwo;
	BfmeHeadAIB *m_bfmeThree;
};

class BfmeListAIB
{
public:
	void bfmeDropAIB(void *what);
	BfmeHeadAIB *m_bfmeHead;
	int m_bfmeCount;
};

class BfmeSinkAIB
{
public:
	void bfmeSendAIB(BfmeListAIB *list, void *text);
};

void bfmeFlushAIB(BfmeSinkAIB *sink, void *spare, BfmeListAIB *list)
{
	if (list->m_bfmeCount != 0)
	{
		list->bfmeDropAIB(list->m_bfmeHead->m_bfmeOne);
		list->m_bfmeHead->m_bfmeTwo = list->m_bfmeHead;
		list->m_bfmeHead->m_bfmeOne = 0;
		list->m_bfmeHead->m_bfmeThree = list->m_bfmeHead;
		list->m_bfmeCount = 0;
	}
	sink->bfmeSendAIB(list, bfmeTextAIB);
}
