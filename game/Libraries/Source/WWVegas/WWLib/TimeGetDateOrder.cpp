// cl: /O2 /Ob0 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// The vtable at VA 0x0112EB44 sits behind an RTTI complete object locator
// spelling the narrow time_get, and 0x0112EB70 spells the wide one.  Slots 3
// to 6 already hold do_get_date, do_get_weekday, do_get_monthname and
// do_get_year, so slot 1 is do_date_order and slot 2 is do_get_time, in the
// order inputs/vendor/stlport/stl/_time_facets.h declares them.  STLport defines
// do_date_order inline as a plain `return no_order`, which is the three bytes
// retail runs.

#include <locale>

typedef _STL::istreambuf_iterator<char, _STL::char_traits<char> >
	BfmeNarrowDateOrderIterator;
typedef _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> >
	BfmeWideDateOrderIterator;

template class _STL::time_get<char, BfmeNarrowDateOrderIterator>;
template class _STL::time_get<wchar_t, BfmeWideDateOrderIterator>;
