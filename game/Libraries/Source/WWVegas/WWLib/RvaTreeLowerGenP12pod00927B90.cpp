// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Retail 0x00927B90 is the non-const lower_bound half of the Gen_p12pod
// red-black tree whose const find twin sits at 0x00927790. The owning map
// is not identified, so the instantiation keeps this address token.

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

typedef _STL::pair<const Gen_p12pod, int> Rva00927B90Value;
typedef _STL::_Rb_tree<Gen_p12pod, Rva00927B90Value,
	_STL::_Select1st<Rva00927B90Value>, _STL::less<Gen_p12pod>,
	_STL::allocator<Rva00927B90Value> > Rva00927B90Tree;

template Rva00927B90Tree::iterator
Rva00927B90Tree::lower_bound( const Gen_p12pod & );
