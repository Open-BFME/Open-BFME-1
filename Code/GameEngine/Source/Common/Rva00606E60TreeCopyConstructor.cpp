// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Anonymous STLport red-black-tree copy constructor at retail 0x00606E60.
// The retail header node is 0x84 bytes; the mapped payload is therefore 0x70
// bytes and has a 0x74-byte pair with its int key.

#include <map>

struct Rva00606E60Value
{
	char m_body[ 0x70 ];

	Rva00606E60Value();
	Rva00606E60Value( const Rva00606E60Value &other );
	~Rva00606E60Value();
	Rva00606E60Value &operator=( const Rva00606E60Value &other );
};

typedef _STL::pair<const int, Rva00606E60Value> Rva00606E60Pair;
typedef _STL::_Rb_tree<int, Rva00606E60Pair,
	_STL::_Select1st<Rva00606E60Pair>, _STL::less<int>,
	_STL::allocator<Rva00606E60Pair> > Rva00606E60Tree;

template class _STL::_Rb_tree<int, Rva00606E60Pair,
	_STL::_Select1st<Rva00606E60Pair>, _STL::less<int>,
	_STL::allocator<Rva00606E60Pair> >;
