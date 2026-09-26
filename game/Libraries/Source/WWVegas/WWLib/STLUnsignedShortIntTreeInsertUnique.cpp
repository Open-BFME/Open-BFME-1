// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

typedef _STL::pair<const unsigned short, int> UnsignedShortIntPair;
typedef _STL::_Rb_tree<unsigned short,
	UnsignedShortIntPair,
	_STL::_Select1st<UnsignedShortIntPair>,
	_STL::less<unsigned short>,
	_STL::allocator<UnsignedShortIntPair> > UnsignedShortIntTree;

template _STL::pair<UnsignedShortIntTree::iterator, bool>
UnsignedShortIntTree::insert_unique(const UnsignedShortIntPair &);
