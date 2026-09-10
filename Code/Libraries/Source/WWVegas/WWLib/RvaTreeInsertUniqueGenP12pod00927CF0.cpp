// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// The direct caller at 0x009282C0 and the pinned _M_insert at 0x00927C30
// identify this body as the no-hint Gen_p12pod map insertion.

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

typedef _STL::pair<const Gen_p12pod, int> GenP12Pair;
typedef _STL::_Rb_tree<Gen_p12pod, GenP12Pair,
	_STL::_Select1st<GenP12Pair>, _STL::less<Gen_p12pod>,
	_STL::allocator<GenP12Pair> > GenP12Tree;

template _STL::pair<GenP12Tree::iterator, bool>
GenP12Tree::insert_unique(const GenP12Pair &value);
