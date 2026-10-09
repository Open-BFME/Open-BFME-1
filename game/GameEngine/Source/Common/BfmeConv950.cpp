// Open-BFME5 conversions.

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

struct BfmeNode950B
{
	char m_bfmeFlag;
	char m_bfmePad[3];
	int m_bfme04;
	BfmeNode950B *m_bfmeNext;
	BfmeNode950B *m_bfmePrev;
};

class BfmeList950B
{
public:
	BfmeList950B();
	BfmeNode950B *m_bfmeHead;
	int m_bfme04;
	char m_bfmePad[4];
	volatile int m_bfme0c;
	volatile char m_bfme10;
};

BfmeList950B::BfmeList950B()
{
	m_bfmeHead = 0;
	m_bfmeHead = (BfmeNode950B *)_STL::vectorSmallAllocate(0x14);
	m_bfme04 = 0;
	m_bfmeHead->m_bfmeFlag = 0;
	m_bfmeHead->m_bfme04 = 0;
	m_bfmeHead->m_bfmeNext = m_bfmeHead;
	m_bfmeHead->m_bfmePrev = m_bfmeHead;
	m_bfme0c = 0;
	m_bfme10 = 1;
}
