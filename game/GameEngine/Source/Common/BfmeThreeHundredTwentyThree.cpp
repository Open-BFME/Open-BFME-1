struct BfmeLinkRU
{
	BfmeLinkRU *m_bfmeNext;
	BfmeLinkRU *m_bfmePrev;
	void *m_bfmeWhat;
};

// Retail 0x0082E540 is the private node pool allocation member.
namespace _STL
{

// Retail 0x0082E540 is the matched node pool refill/mutex body.
static __forceinline void *vectorSmallAllocate(unsigned int bytes);
template <bool Threads, int Instance>
class __node_alloc
{
	static void *__cdecl _M_allocate(unsigned int bytes);
	friend void *vectorSmallAllocate(unsigned int bytes);
};
static __forceinline void *vectorSmallAllocate(unsigned int bytes)
{
	return __node_alloc<true, 0>::_M_allocate(bytes);
}

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
	BfmeLinkRU *link = (BfmeLinkRU *)_STL::vectorSmallAllocate(0xc);
	link->m_bfmeNext = link;
	link->m_bfmePrev = link;
	m_bfmeHead = link;
	m_bfmeCount = -1;
	m_bfmeTwo = false;
	m_bfmeOne = false;
	return this;
}
