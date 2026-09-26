// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <algorithm>

wchar_t *Rva00844F20FindWide(wchar_t *first, wchar_t *last, const wchar_t &value)
{
    return _STL::find(first, last, value);
}
