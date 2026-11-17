// Open-BFME5 conversions.

struct BfmeNode1016
{
	char m_bfmePad[4];
	int m_bfmeCount;
	BfmeNode1016 *m_bfmeNext;
	BfmeNode1016 *m_bfmePrev;
};

class BfmeList1016
{
public:
	BfmeNode1016 *m_bfmeHead;
	int m_bfmeSize;
};

// Retail 0x008FF960 is the ledger row ?_M_erase@?$_Rb_tree@HU?$pair@$$CBHUGen_t_008ff960_p12cd@@@...
// (gen-tgrid tree_int_p12cd); spell the receiver as that tree so the call
// resolves to it. Only the member's mangling matters here.
struct Gen_t_008ff960_p12cd;
namespace _STL
{
	template<class A, class B> struct pair;
	template<class T> struct _Select1st;
	template<class T> struct less;
	template<class T> class allocator;
	template<class T> struct _Rb_tree_node;
	template<class K, class V, class KoV, class C, class A> class _Rb_tree
	{
	public:
		typedef pair<const int, Gen_t_008ff960_p12cd> value_type;
		void bfmeEraseCall(_Rb_tree_node<value_type> *node) { _M_erase(node); }
	private:
		void _M_erase(_Rb_tree_node<value_type> *node);
	};
}
typedef _STL::_Rb_tree<int, _STL::pair<const int, Gen_t_008ff960_p12cd>,
	_STL::_Select1st<_STL::pair<const int, Gen_t_008ff960_p12cd> >, _STL::less<int>,
	_STL::allocator<_STL::pair<const int, Gen_t_008ff960_p12cd> > > BfmeTree1016;

BfmeList1016 g_bfmeList1016;

void bfmeGo1016T(void)
{
	if (g_bfmeList1016.m_bfmeSize != 0) {
		((BfmeTree1016 *)&g_bfmeList1016)->bfmeEraseCall((_STL::_Rb_tree_node<BfmeTree1016::value_type> *)g_bfmeList1016.m_bfmeHead->m_bfmeCount);
		g_bfmeList1016.m_bfmeHead->m_bfmeNext = g_bfmeList1016.m_bfmeHead;
		g_bfmeList1016.m_bfmeHead->m_bfmeCount = 0;
		g_bfmeList1016.m_bfmeHead->m_bfmePrev = g_bfmeList1016.m_bfmeHead;
		g_bfmeList1016.m_bfmeSize = 0;
	}
}
