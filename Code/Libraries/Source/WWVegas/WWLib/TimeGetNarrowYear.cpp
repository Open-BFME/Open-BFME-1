// cl: /O2 /Ob0 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Focused narrow time_get year specialization with retail call boundaries.
#define private public
#include <locale>
#undef private

typedef _STL::istreambuf_iterator<char, _STL::char_traits<char> >
	BfmeNarrowYearIterator;

template <>
BfmeNarrowYearIterator
_STL::time_get<char, BfmeNarrowYearIterator>::do_get_year(
	BfmeNarrowYearIterator first, BfmeNarrowYearIterator last,
	_STL::ios_base &, _STL::ios_base::iostate &error, tm *value) const
{
	if (first.equal(last))
	{
		error = _STL::ios_base::failbit | _STL::ios_base::eofbit;
		return first;
	}
	bool ok = _STL::__get_decimal_integer(first, last, value->tm_year);
	value->tm_year -= 1900;
	error = ok ? _STL::ios_base::goodbit : _STL::ios_base::failbit;
	if (first.equal(last))
		error |= _STL::ios_base::eofbit;
	return first;
}
