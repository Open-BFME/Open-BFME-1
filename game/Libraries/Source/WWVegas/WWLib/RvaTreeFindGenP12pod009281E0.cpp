// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Retail 0x009281E0 is a byte-identical second copy of the non-const
// Gen_p12pod tree find at 0x00927BF0 (callee 0x00927790). The ledger
// keeps one identity per address, so this copy lands under its own
// address-derived owner delegating to the same tree find.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

struct Gen_p12pod
{
	int a[3];
};

inline bool compare_tail(const Gen_p12pod &a, const Gen_p12pod &b)
{
	const int a1 = a.a[1];
	return b.a[1] > a1
		|| (!(b.a[1] < a1) && a.a[2] < b.a[2]);
}

inline bool operator<(const Gen_p12pod &a, const Gen_p12pod &b)
{
	const int a0 = a.a[0];
	return b.a[0] > a0 || (!(b.a[0] < a0) && compare_tail(a, b));
}

typedef _STL::pair<const Gen_p12pod, int> Rva009281E0Value;
typedef _STL::_Rb_tree<Gen_p12pod, Rva009281E0Value,
	_STL::_Select1st<Rva009281E0Value>, _STL::less<Gen_p12pod>,
	_STL::allocator<Rva009281E0Value> > Rva009281E0Tree;

class Rva009281E0Find
{
public:
	Rva009281E0Tree::iterator find(const Gen_p12pod &key);
	Rva009281E0Tree m_tree;
};

Rva009281E0Tree::iterator Rva009281E0Find::find(const Gen_p12pod &key)
{
	return m_tree.find(key);
}
