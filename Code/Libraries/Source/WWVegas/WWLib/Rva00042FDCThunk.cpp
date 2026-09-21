// cl: /O2 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport

// Retail RVA 0x00042FDC is a five-byte incremental-link jump to the matched
// STLport _Rb_tree::_M_erase body at 0x007612D0. The forwarding member keeps
// the caller's this pointer and node argument in their original ABI slots.

class Rva00042FDCThunk;

namespace _STL
{
template <class First, class Second>
struct pair
{
};

template <class Type>
struct _Select1st
{
};

template <class Type>
struct less
{
};

template <class Type>
class allocator
{
};

template <class Value>
struct _Rb_tree_node
{
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
	friend class ::Rva00042FDCThunk;

	private:
	void _M_erase(_Rb_tree_node<Value> *node);
};
}

typedef _STL::pair<const unsigned short, unsigned char> BfmeShortByteValue;
typedef _STL::_Rb_tree<unsigned short, BfmeShortByteValue,
	_STL::_Select1st<BfmeShortByteValue>, _STL::less<unsigned short>,
	_STL::allocator<BfmeShortByteValue> > BfmeShortByteTree;

class Rva00042FDCThunk : public BfmeShortByteTree
{
public:
	void forward(_STL::_Rb_tree_node<BfmeShortByteValue> *node);
};

void Rva00042FDCThunk::forward(
	_STL::_Rb_tree_node<BfmeShortByteValue> *node)
{
	_M_erase(node);
}
