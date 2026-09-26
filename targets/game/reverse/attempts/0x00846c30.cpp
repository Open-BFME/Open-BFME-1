// ?bfmeRva00846C30CopyWideStream@@YA?AV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@PBG0V12@ABU__false_type@2@@Z
// partial score=0.95 date=2026-09-26
// cl: /O2 /Ob0 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <algorithm>
#include <iterator>

_STL::ostreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> >
bfmeRva00846C30CopyWideStream(const wchar_t *first, const wchar_t *last,
    _STL::ostreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > output,
    const _STL::__false_type &)
{
    return _STL::__copy(first, last, output,
        _STL::random_access_iterator_tag(), (int *)0);
}
