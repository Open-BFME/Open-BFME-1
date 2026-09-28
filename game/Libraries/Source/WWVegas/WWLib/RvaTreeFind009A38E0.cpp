// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// The owning tree is unknown, so the comparator keeps this address token.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

class State;

typedef _STL::pair<const unsigned int, State *> Rva009A38E0Value;

struct Rva009A38E0Less
{
	bool operator()(const unsigned int &left, const unsigned int &right) const
	{
		return left < right;
	}
};

typedef _STL::_Rb_tree<unsigned int, Rva009A38E0Value,
	_STL::_Select1st<Rva009A38E0Value>, Rva009A38E0Less,
	_STL::allocator<Rva009A38E0Value> > Rva009A38E0Tree;

template Rva009A38E0Tree::iterator
Rva009A38E0Tree::find<unsigned int>(const unsigned int &);
