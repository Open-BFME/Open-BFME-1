// cl: /O2 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Native STLport 4.5.3 locale assignment (src/locale_impl.cpp), retail
// 0x00832180. The pubimbue and ios_base::imbue REL32 displacements both land
// here (symbols.csv pins of ??4locale@_STL). The body releases this locale's
// implementation through vtable slot 2 (decr), takes a reference on the
// source's through slot 1 (incr), then stores it, exactly as STLport writes it.
#include <locale>

namespace _STL {

// The public header leaves the implementation opaque; only the reference
// counting virtuals are modeled (classic-locale builder: slots 1 and 2).
class _Locale_impl
{
public:
    virtual ~_Locale_impl();
    virtual void incr();
    virtual void decr();
};

const locale &locale::operator=(const locale &L) _STLP_NOTHROW
{
    if (this->_M_impl != L._M_impl) {
        this->_M_impl->decr();
        // _S_copy_impl(L._M_impl), inlined: incr and return the pointer.
        _Locale_impl *impl = L._M_impl;
        impl->incr();
        this->_M_impl = impl;
    }
    return *this;
}

} // namespace _STL
