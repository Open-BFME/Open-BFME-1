struct BfmeHeadAVA
// Open-BFME7: retail 0x00449880 (58 bytes) is the twin of BfmeConv426.cpp bfmeGoAVA on a
// thing whose list sits at +0x77c instead of +0x20c; the list class is shared.
{
	unsigned char m_bfmePad[4];
	void *m_bfmeOne;
	BfmeHeadAVA *m_bfmeTwo;
	BfmeHeadAVA *m_bfmeThree;
};

class BfmeListAVA
{
public:
	void bfmeDropAVA(void *what);
	BfmeHeadAVA *m_bfmeHead;
	int m_bfmeCount;
};

class BfmeThingAVA00449880
{
public:
	void bfmeGoAVA();
	unsigned char m_bfmeHead[0x77c];
	BfmeListAVA m_bfmeList;
};

void BfmeThingAVA00449880::bfmeGoAVA()
{
	BfmeListAVA *list = &m_bfmeList;
	if (list->m_bfmeCount != 0)
	{
		list->bfmeDropAVA(list->m_bfmeHead->m_bfmeOne);
		list->m_bfmeHead->m_bfmeTwo = list->m_bfmeHead;
		list->m_bfmeHead->m_bfmeOne = 0;
		list->m_bfmeHead->m_bfmeThree = list->m_bfmeHead;
		list->m_bfmeCount = 0;
	}
}
