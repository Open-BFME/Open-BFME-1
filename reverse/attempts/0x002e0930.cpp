// ??0BfmeListBG@@QAE@PAX0@Z
// partial score=0.97 date=2026-09-09
// 47/47. Circular-list constructor: two parameter stores, a null of the node
// member, __new_alloc::allocate(0xc), the two self-links and the real node
// store. Marking BOTH parameter members volatile (not just the first) moves
// retail's `push 0xc` past the first store, leaving one residue: retail
// emits it after the second store too, ours still schedules it between the
// two stores. Body-vs-init-list assignment order made no difference.
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
	: m_bfmeFirstBG(first), m_bfmeSecondBG(second)
{
	m_bfmeNodeBG = 0;

	BfmeNodeBG *node = (BfmeNodeBG *)_STL::__new_alloc::allocate(0xc);

	node->m_bfmeNextBG = node;
	node->m_bfmePrevBG = node;
	m_bfmeNodeBG = node;
}
