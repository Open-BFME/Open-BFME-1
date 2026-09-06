// ??0BfmeListBG@@QAE@PAX0@Z (identity unknown)
// partial score=0.96 date=2026-09-06
// 45/47. A circular-list constructor: two parameter stores, a null of the node
// member, __new_alloc::allocate(0xc), the two self-links and the real node
// store. Everything matches except that retail emits `push 0xc` AFTER both
// parameter stores while MSVC hoists it above them. Marking both parameter
// members volatile moves the push down by one store (three diffs to two);
// nothing moves it past the second. Member initialiser lists, a separate zero
// statement and volatile on the node member were also tried.
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
	void *m_bfmeSecondBG;
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
