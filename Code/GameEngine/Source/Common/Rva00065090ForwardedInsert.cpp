// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// Open-BFME5: one-argument member forwarding to the retail STLport tree.
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

struct Rva00065050Target;
typedef Rva00065050Target *Rva00065050Key;
typedef _STL::_Rb_tree<Rva00065050Key, Rva00065050Key,
	_STL::_Identity<Rva00065050Key>, _STL::less<Rva00065050Key>,
	_STL::allocator<Rva00065050Key> > Rva00065090Tree;

class GenForwardedArg
{
	int m_x;
};

class Gen0001581B : public Rva00065090Tree
{
public:
	void take(GenForwardedArg *arg);
};

void Gen0001581B::take(GenForwardedArg *arg)
{
	insert_unique(*reinterpret_cast<Rva00065050Key const *>(arg));
}
