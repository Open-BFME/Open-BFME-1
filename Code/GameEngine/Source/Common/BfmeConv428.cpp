struct BfmeNodeAVC
{
	bool m_bfmeKind;
	unsigned char m_bfmePad[3];
	void *m_bfmeOne;
	BfmeNodeAVC *m_bfmeTwo;
	BfmeNodeAVC *m_bfmeThree;
};

void *bfmeAllocAVC(unsigned int bytes);

class BfmeThingAVC
{
public:
	BfmeThingAVC *bfmeInitAVC();
	BfmeNodeAVC *m_bfmeHead;
	int m_bfmeCount;
	unsigned char m_bfmeGap[4];
	int m_bfmeMore;
};

BfmeThingAVC *BfmeThingAVC::bfmeInitAVC()
{
	m_bfmeHead = 0;
	m_bfmeHead = (BfmeNodeAVC *)bfmeAllocAVC(0x20);
	m_bfmeCount = 0;
	m_bfmeHead->m_bfmeKind = false;
	m_bfmeHead->m_bfmeOne = 0;
	m_bfmeHead->m_bfmeTwo = m_bfmeHead;
	m_bfmeHead->m_bfmeThree = m_bfmeHead;
	m_bfmeMore = 0;
	return this;
}
