// cl: /O2 /Ob0 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Focused narrow time_get date specialization with retail call boundaries.
#define private public
#include <locale>
#undef private

typedef _STL::istreambuf_iterator<char, _STL::char_traits<char> >
	BfmeNarrowDateIterator;

template <>
BfmeNarrowDateIterator
_STL::time_get<char, BfmeNarrowDateIterator>::do_get_date(
	BfmeNarrowDateIterator first, BfmeNarrowDateIterator last,
	_STL::ios_base &, _STL::ios_base::iostate &error, tm *value) const
{
	const _STL::_Time_Info &info = *reinterpret_cast<const _STL::_Time_Info *>(
		reinterpret_cast<const char *>(this) + 0x0C);
	const char *const *date_ptrs = reinterpret_cast<const char *const *>(
		reinterpret_cast<const char *>(this) + 0x1F8);
	const char *format = date_ptrs[0];
	const char *format_end = date_ptrs[1];
	const char *result = _STL::__get_formatted_time(
		first, last, format, format_end, info, error, value);
	if (result == format_end)
		error = _STL::ios_base::goodbit;
	else
	{
		error = _STL::ios_base::failbit;
		if (first.equal(last))
			error |= _STL::ios_base::eofbit;
	}
	return first;
}
