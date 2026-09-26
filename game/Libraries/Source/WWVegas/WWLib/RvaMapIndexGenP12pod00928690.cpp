// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Retail 0x00928690 calls the Gen_p12pod lower-bound helper at 0x00927680,
// inserts through the tree helper at 0x009282C0, and returns the mapped field
// at node offset 0x1C.  Those calls identify map<Gen_p12pod, int>::operator[].
// The cached fields and negated less-than tests preserve the retail branch
// order when MSVC 7.1 inlines the three-field key comparison.

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

typedef _STL::map<Gen_p12pod, int, _STL::less<Gen_p12pod>,
	_STL::allocator<_STL::pair<const Gen_p12pod, int> > > Rva00928690Map;

template int &Rva00928690Map::operator[](const Gen_p12pod &);
