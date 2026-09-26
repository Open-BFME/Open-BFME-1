// cl: /O2 /Ob0 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <algorithm>
#include <iterator>
extern _STL::ostreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> >
bfmeRva0083A2D0CopyWide(const wchar_t *, const wchar_t *,
    _STL::ostreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> >,
    const _STL::random_access_iterator_tag &, int *);


_STL::ostreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> >
bfmeRva00846C30CopyWideStream(const wchar_t *first, const wchar_t *last,
    _STL::ostreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > output,
    const _STL::__false_type &)
{
    return bfmeRva0083A2D0CopyWide(first, last, output,
        _STL::random_access_iterator_tag(), (int *)0);
}
