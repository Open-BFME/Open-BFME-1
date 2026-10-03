// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/stlp_nodealloc
// stlport
#include <deque>
class Rva0090E330 {
public:
    void *method(unsigned count, const void *hint) const;
};
void *Rva0090E330::method(unsigned count, const void *hint) const
{
    return _STL::allocator<unsigned>().allocate(count, hint);
}
