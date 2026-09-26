// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Retail 0x00927790 is the find half of the same Gen_p12pod red-black tree
// whose lower-bound helper and map operator[] are identified at 0x00927680
// and 0x00928690.  The body reads only the three key fields at node offsets
// +0x10, +0x14 and +0x18, then returns the tree header on a miss.

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

typedef _STL::pair<const Gen_p12pod, int> Rva00927790Value;
typedef _STL::_Rb_tree<Gen_p12pod, Rva00927790Value,
	_STL::_Select1st<Rva00927790Value>, _STL::less<Gen_p12pod>,
	_STL::allocator<Rva00927790Value> > Rva00927790Tree;

// retail 0x00927790
template _STL::_Rb_tree_node<Rva00927790Value> *
Rva00927790Tree::_M_find<Gen_p12pod>( const Gen_p12pod & ) const;
