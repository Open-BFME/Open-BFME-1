// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// The caller family and the retail template pin identify this body as the
// unsigned-short insert_unique member for the twelve-byte payload at 0x00668A90.
// The adjacent _M_insert body at 0x00668730 supplies the same tree ABI.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

struct Gen_t_00668a90_m12pod
{
	int m_body[3];
};

typedef _STL::pair<const unsigned short, Gen_t_00668a90_m12pod> Gen00668A90Pair;
typedef _STL::_Rb_tree<unsigned short,
	Gen00668A90Pair,
	_STL::_Select1st<Gen00668A90Pair>,
	_STL::less<unsigned short>,
	_STL::allocator<Gen00668A90Pair> > Gen00668A90Tree;

template _STL::pair<Gen00668A90Tree::iterator, bool>
Gen00668A90Tree::insert_unique(const Gen00668A90Pair &value);
