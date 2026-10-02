struct BfmeLinkRW
{
	BfmeLinkRW *m_bfmeNext;
	BfmeLinkRW *m_bfmePrev;
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
	BfmeLinkRW *link = (BfmeLinkRW *)_STL::__new_alloc::allocate(0xc);
	void **slot = &link->m_bfmeWhat;
	if (slot != 0)
		*slot = what;
	BfmeLinkRW *last = end->m_bfmePrev;
	link->m_bfmeNext = end;
	link->m_bfmePrev = last;
	last->m_bfmeNext = link;
	end->m_bfmePrev = link;
}
