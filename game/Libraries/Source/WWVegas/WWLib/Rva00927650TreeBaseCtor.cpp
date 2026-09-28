// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc
// stlport
// RVA 0x00927650: STLport tree base whose header allocation is 32 bytes.
// The value identity is unknown; sixteen bytes is proven by the node size.
#include <map>

struct Rva00927650Value
{
    int m_words[4];
};

template class _STL::_Rb_tree_base<Rva00927650Value,
    _STL::allocator<Rva00927650Value> >;
