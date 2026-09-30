// cl: /O2 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00654CE0 is the pointer/false-tag range-initialization adapter.
// Its unused tag argument is reused for the forward-iterator temporary before
// tail-calling ILT 0x0002648B. The callee specialization also matches its 97B
// body at 0x004FA6F0; defining it avoids VC7.1's C1001 on an external-only
// specialization declaration, while noinline preserves the retail tail call.
#include <string>

namespace _STL {
template<> template<> __declspec(noinline)
void basic_string<char,char_traits<char>,allocator<char> >::_M_range_initialize<char *>(
    char *first,char *last,const forward_iterator_tag &) {
    difference_type count=last-first;
    _M_allocate_block(count+1);
    _M_finish=uninitialized_copy(first,last,_M_start);
    *_M_finish=0;
}

template<> template<>
void basic_string<char,char_traits<char>,allocator<char> >::_M_initialize_dispatch<char *>(
    char *first,char *last,const __false_type &) {
    _M_range_initialize(first,last,forward_iterator_tag());
}
}
