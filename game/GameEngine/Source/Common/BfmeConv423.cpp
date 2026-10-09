class BfmeThingAUD;
struct Gen_t_00234730_m4pod;
namespace _STL {
 template<class T> struct _Identity;
 template<class T> struct less;
 template<class T> class allocator;
 template<class T> struct _Rb_tree_node;
 template<class K,class V,class E,class C,class A> class _Rb_tree {
  void _M_erase(_Rb_tree_node<V> *);
  friend class ::BfmeThingAUD;
 };
}

struct BfmeHeadAUD
{
	unsigned char m_bfmePad[4];
	void *m_bfmeOne;
	BfmeHeadAUD *m_bfmeTwo;
	BfmeHeadAUD *m_bfmeThree;
};

class BfmeListAUD
{
public:
	BfmeHeadAUD *m_bfmeHead;
	int m_bfmeCount;
};

class BfmeThingAUD
{
public:
	void bfmeGoAUD();
	unsigned char m_bfmeHead[0x40];
	bool m_bfmeFlag;
	unsigned char m_bfmeGap[3];
	BfmeListAUD m_bfmeList;
};

void BfmeThingAUD::bfmeGoAUD()
{
	BfmeListAUD *list = &m_bfmeList;
	m_bfmeFlag = false;
	if (list->m_bfmeCount != 0)
	{
		reinterpret_cast<_STL::_Rb_tree<Gen_t_00234730_m4pod, Gen_t_00234730_m4pod, _STL::_Identity<Gen_t_00234730_m4pod>, _STL::less<Gen_t_00234730_m4pod>, _STL::allocator<Gen_t_00234730_m4pod> > *>(list)->_M_erase(reinterpret_cast<_STL::_Rb_tree_node<Gen_t_00234730_m4pod> *>(list->m_bfmeHead->m_bfmeOne));
		list->m_bfmeHead->m_bfmeTwo = list->m_bfmeHead;
		list->m_bfmeHead->m_bfmeOne = 0;
		list->m_bfmeHead->m_bfmeThree = list->m_bfmeHead;
		list->m_bfmeCount = 0;
	}
}
