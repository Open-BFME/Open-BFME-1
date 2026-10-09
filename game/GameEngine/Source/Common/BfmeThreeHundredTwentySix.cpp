struct BfmeLinkRX
{
	BfmeLinkRX *m_bfmeNext;
	BfmeLinkRX *m_bfmePrev;
	unsigned short m_bfmeWhat;
};

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

class BfmeListRX
{
public:
	void bfmePushRX(unsigned short *what);
	BfmeLinkRX *m_bfmeEnd;
};

void BfmeListRX::bfmePushRX(unsigned short *what)
{
	BfmeLinkRX *end = m_bfmeEnd;
	BfmeLinkRX *link = (BfmeLinkRX *)_STL::vectorSmallAllocate(0xc);
	unsigned short *slot = &link->m_bfmeWhat;
	if (slot != 0)
		*slot = *what;
	BfmeLinkRX *last = end->m_bfmePrev;
	link->m_bfmeNext = end;
	link->m_bfmePrev = last;
	last->m_bfmeNext = link;
	end->m_bfmePrev = link;
}
