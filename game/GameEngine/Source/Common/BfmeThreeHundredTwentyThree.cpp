struct BfmeLinkRU
{
	BfmeLinkRU *m_bfmeNext;
	BfmeLinkRU *m_bfmePrev;
	void *m_bfmeWhat;
};

// Retail's callee at 0x0082E540 is the STLport node allocator's public
// allocate entry, defined by
// game/Libraries/Source/WWVegas/WWLib/STL_new_alloc_allocateThunk.cpp.
// Spelled with the defining name so this TU links.
namespace _STL
{

class __new_alloc
{
public:
	static void *allocate(unsigned int n);
};

}

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
	BfmeLinkRU *link = (BfmeLinkRU *)_STL::__new_alloc::allocate(0xc);
	link->m_bfmeNext = link;
	link->m_bfmePrev = link;
	m_bfmeHead = link;
	m_bfmeCount = -1;
	m_bfmeTwo = false;
	m_bfmeOne = false;
	return this;
}
