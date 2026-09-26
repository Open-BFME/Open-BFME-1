// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <algorithm>

int Rva00844F60FindTwoWideRanges(wchar_t needle, const wchar_t *first, const wchar_t *second, wchar_t sentinel)
{
    if (needle == sentinel)
        return -1;
    const wchar_t *found = _STL::find(first, first + 10, needle);
    if (found != first + 10)
        return (int)(found - first);
    found = _STL::find(second, second + 12, needle);
    if (found != second + 12)
        return 10 + (int)((second - found) / 2);
    return -2;
}
