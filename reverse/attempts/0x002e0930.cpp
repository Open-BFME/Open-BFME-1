// ?d_002e0930@@YAXXZ
// partial score=0.99 date=2026-09-10
// Exact 47-byte circular-list constructor. The compiler barrier preserves
// retail's store, push, zero, allocate order, but no source caller or owner
// proves the class name behind this placeholder.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

namespace _STL
{

class __new_alloc
{
public:
	static void *allocate(unsigned int size);
};

}

class BfmeNodeBG
{
public:
	BfmeNodeBG *m_bfmeNextBG;
	BfmeNodeBG *m_bfmePrevBG;
	void *m_bfmeValueBG;
};

class BfmeListBG
{
public:
	BfmeListBG(void *first, void *second);

	void *volatile m_bfmeFirstBG;
	void *volatile m_bfmeSecondBG;
	BfmeNodeBG *m_bfmeNodeBG;
};

BfmeListBG::BfmeListBG(void *first, void *second)
{
	m_bfmeFirstBG = first;
	m_bfmeSecondBG = second;
	_ReadWriteBarrier();
	m_bfmeNodeBG = 0;

	BfmeNodeBG *node = (BfmeNodeBG *)_STL::__new_alloc::allocate(0xc);

	node->m_bfmeNextBG = node;
	node->m_bfmePrevBG = node;
	m_bfmeNodeBG = node;
}
