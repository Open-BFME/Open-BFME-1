// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00667E20 is the unhinted insert_unique body for this 12-byte pair.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

struct Gen_t_00668440_m12pod
{
	int a[3];
};

typedef _STL::pair<const unsigned short, Gen_t_00668440_m12pod>
	RvaTreeInsertUniqueShortPod00667E20Pair;
typedef _STL::_Rb_tree<unsigned short,
	RvaTreeInsertUniqueShortPod00667E20Pair,
	_STL::_Select1st<RvaTreeInsertUniqueShortPod00667E20Pair>,
	_STL::less<unsigned short>,
	_STL::allocator<RvaTreeInsertUniqueShortPod00667E20Pair> >
	RvaTreeInsertUniqueShortPod00667E20Tree;

template _STL::pair<
	RvaTreeInsertUniqueShortPod00667E20Tree::iterator, bool>
RvaTreeInsertUniqueShortPod00667E20Tree::insert_unique(
	const RvaTreeInsertUniqueShortPod00667E20Pair &);
