// cl: /O2 /Ob0 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail inlines the small month-name wrapper but keeps __match and the two
// iterator refreshes out of line. This focused specialization spells out that
// boundary; exposing iterator state only within this TU preserves the real
// method calls without changing the vendored STLport header.
#define private public
#include <locale>
#undef private

typedef _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> >
	BfmeWideTimeIterator;

template <>
BfmeWideTimeIterator
_STL::time_get<wchar_t, BfmeWideTimeIterator>::do_get_monthname(
		BfmeWideTimeIterator first, BfmeWideTimeIterator last,
		_STL::ios_base &, _STL::ios_base::iostate &error, tm *value) const
{
	const _STL::_Time_Info &info = *reinterpret_cast<const _STL::_Time_Info *>(
		reinterpret_cast<const char *>(this) + 0x0C);
	_STL::string *monthNamesEnd;
	const _STL::string *match = _STL::__match(first, last,
		const_cast<_STL::string *>(info._M_monthname),
		monthNamesEnd = const_cast<_STL::string *>(info._M_monthname) + 24,
		(long *)0);
	value->tm_mon = (int)(match - info._M_monthname) % 12;

	if (match != monthNamesEnd)
	{
		error = _STL::ios_base::goodbit;
	}
	else
	{
		error = _STL::ios_base::failbit;
		if (first._M_buf)
			first._M_getc();
		if (last._M_buf)
			last._M_getc();
		if (first._M_eof == last._M_eof)
			error |= _STL::ios_base::eofbit;
	}

	return first;
}
