// stlport
#include <stl/_alloc.h>

class BfmeThingCFB
{
public:
	void bfmeGoCFB();
	unsigned char m_bfmeHead[4];
	char *m_bfmePtr;
	unsigned char m_bfmeGap[4];
	char *m_bfmeEnd;
};

void __cdecl operator delete(void *ptr);

void BfmeThingCFB::bfmeGoCFB()
{
	char *ptr = m_bfmePtr;
	unsigned int size = m_bfmeEnd - ptr;
	if (ptr != 0)
	{
		if (size > 0x80)
			::operator delete(ptr);
		else
			_STL::__node_alloc<true, 0>::deallocate(ptr, size);
	}
}
