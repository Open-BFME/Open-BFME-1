class BfmeThingAUC;
struct Gen_t_00134aa0_m4pod;
namespace _STL {
 template<class T> struct _Identity;
 template<class T> struct less;
 template<class T> class allocator;
 template<class T> struct _Rb_tree_node;
 template<class K,class V,class E,class C,class A> class _Rb_tree {
  void _M_erase(_Rb_tree_node<V> *);
  friend class ::BfmeThingAUC;
 };
}

struct BfmeHeadAUC
{
	unsigned char m_bfmePad[4];
	void *m_bfmeOne;
	BfmeHeadAUC *m_bfmeTwo;
	BfmeHeadAUC *m_bfmeThree;
};

class BfmeThingAUC
{
public:
	void bfmeGoAUC();
	BfmeHeadAUC *m_bfmeHead;
	int m_bfmeCount;
	unsigned char m_bfmeGap[8];
	bool m_bfmeFlag;
};

void BfmeThingAUC::bfmeGoAUC()
{
	if (m_bfmeCount != 0)
	{
		reinterpret_cast<_STL::_Rb_tree<Gen_t_00134aa0_m4pod, Gen_t_00134aa0_m4pod, _STL::_Identity<Gen_t_00134aa0_m4pod>, _STL::less<Gen_t_00134aa0_m4pod>, _STL::allocator<Gen_t_00134aa0_m4pod> > *>(this)->_M_erase(reinterpret_cast<_STL::_Rb_tree_node<Gen_t_00134aa0_m4pod> *>(m_bfmeHead->m_bfmeOne));
		m_bfmeHead->m_bfmeTwo = m_bfmeHead;
		m_bfmeHead->m_bfmeOne = 0;
		m_bfmeHead->m_bfmeThree = m_bfmeHead;
		m_bfmeCount = 0;
	}
	m_bfmeFlag = true;
}
