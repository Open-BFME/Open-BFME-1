// ?d_009a3ff0@@YAXXZ
// partial score=0.9 date=2026-09-26
// stlport
// This wrapper forwards the iterator result of the state-id tree lookup.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

class State;
typedef _STL::pair<const unsigned int, State *> Rva009A3FF0Pair;
typedef _STL::_Rb_tree<unsigned int, Rva009A3FF0Pair,
	_STL::_Select1st<Rva009A3FF0Pair>, _STL::less<unsigned int>,
	_STL::allocator<Rva009A3FF0Pair> > Rva009A3FF0TreeBase;

class Rva009A3FF0Tree : public Rva009A3FF0TreeBase
{
public:
	iterator findAt9A3FF0(const unsigned int &id);
};

Rva009A3FF0Tree::iterator Rva009A3FF0Tree::findAt9A3FF0(const unsigned int &id)
{
	return find(id);
}
