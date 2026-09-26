// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc
// stlport
// RVA 0x009C9490: STLport tree base whose header allocation is 24 bytes.
// The value identity is unknown; eight bytes is proven by the node size.
#include <map>

struct Rva009C9490Value
{
    int m_words[2];
};

template class _STL::_Rb_tree_base<Rva009C9490Value,
    _STL::allocator<Rva009C9490Value> >;
