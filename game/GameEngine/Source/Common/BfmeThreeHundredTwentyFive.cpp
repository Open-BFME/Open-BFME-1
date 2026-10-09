struct BfmeLinkRW
{
	BfmeLinkRW *m_bfmeNext;
	BfmeLinkRW *m_bfmePrev;
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

class BfmeListRW
{
public:
	void bfmePushRW(void *what);
	unsigned char m_bfmeHead[0xc];
	BfmeLinkRW **m_bfmeRoot;
};

void BfmeListRW::bfmePushRW(void *what)
{
	BfmeLinkRW *end = *m_bfmeRoot;
	BfmeLinkRW *link = (BfmeLinkRW *)_STL::vectorSmallAllocate(0xc);
	void **slot = &link->m_bfmeWhat;
	if (slot != 0)
		*slot = what;
	BfmeLinkRW *last = end->m_bfmePrev;
	link->m_bfmeNext = end;
	link->m_bfmePrev = last;
	last->m_bfmeNext = link;
	end->m_bfmePrev = link;
}
