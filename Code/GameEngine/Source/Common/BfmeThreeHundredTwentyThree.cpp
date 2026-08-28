struct BfmeLinkRU
{
	BfmeLinkRU *m_bfmeNext;
	BfmeLinkRU *m_bfmePrev;
	void *m_bfmeWhat;
};

void *bfmeAllocRU(unsigned int bytes);

class BfmeListRU
{
public:
	BfmeListRU *bfmeInitRU();
	bool m_bfmeOne;
	bool m_bfmeTwo;
	unsigned char m_bfmeGap[2];
	BfmeLinkRU *m_bfmeHead;
	int m_bfmeCount;
};

BfmeListRU *BfmeListRU::bfmeInitRU()
{
	m_bfmeHead = 0;
	BfmeLinkRU *link = (BfmeLinkRU *)bfmeAllocRU(0xc);
	link->m_bfmeNext = link;
	link->m_bfmePrev = link;
	m_bfmeHead = link;
	m_bfmeCount = -1;
	m_bfmeTwo = false;
	m_bfmeOne = false;
	return this;
}
