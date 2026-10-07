struct BfmeHeadAVA
// Open-BFME7: retail 0x00449880 (58 bytes) is the twin of BfmeConv426.cpp bfmeGoAVA on a
// thing whose list sits at +0x77c instead of +0x20c; its erase helper is a distinct tree specialization (443DF0, not644050).
{
	unsigned char m_bfmePad[4];
	void *m_bfmeOne;
	BfmeHeadAVA *m_bfmeTwo;
	BfmeHeadAVA *m_bfmeThree;
};

// Retail calls ILT 0x16176 -> 0x00443DF0, the matched _Rb_tree::_M_erase
// specialization over Gen_t_00443df0_k4/p4pod (callees.py).
class BfmeThingAVA00449880;
struct Gen_t_00443df0_k4;
struct Gen_t_00443df0_p4pod;

namespace _STL
{
template <class A, class B> struct pair;
template <class T> struct _Select1st;
template <class T> struct less;
template <class T> class allocator;
template <class V> struct _Rb_tree_node;

template <class K, class V, class KoV, class C, class A>
class _Rb_tree
{
	friend class ::BfmeThingAVA00449880;
	void _M_erase(_Rb_tree_node<V> *node);
};
}

typedef _STL::pair<const Gen_t_00443df0_k4, Gen_t_00443df0_p4pod> BfmeValueAVA;
typedef _STL::_Rb_tree<Gen_t_00443df0_k4, BfmeValueAVA, _STL::_Select1st<BfmeValueAVA>,
	_STL::less<Gen_t_00443df0_k4>, _STL::allocator<BfmeValueAVA> > BfmeTreeAVA;

class BfmeListAVA00443DF0
{
public:
	BfmeHeadAVA *m_bfmeHead;
	int m_bfmeCount;
};

class BfmeThingAVA00449880
{
public:
	void bfmeGoAVA();
	unsigned char m_bfmeHead[0x77c];
	BfmeListAVA00443DF0 m_bfmeList;
};

void BfmeThingAVA00449880::bfmeGoAVA()
{
	BfmeListAVA00443DF0 *list = &m_bfmeList;
	if (list->m_bfmeCount != 0)
	{
		((BfmeTreeAVA *)list)->_M_erase(
			(_STL::_Rb_tree_node<BfmeValueAVA> *)list->m_bfmeHead->m_bfmeOne);
		list->m_bfmeHead->m_bfmeTwo = list->m_bfmeHead;
		list->m_bfmeHead->m_bfmeOne = 0;
		list->m_bfmeHead->m_bfmeThree = list->m_bfmeHead;
		list->m_bfmeCount = 0;
	}
}
