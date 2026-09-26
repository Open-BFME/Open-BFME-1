// cl: /O2 /Ob0 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Focused wide time_get weekday specialization with retail call boundaries.
#define private public
#include <locale>
#undef private

typedef _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> >
	BfmeWideWeekdayIterator;

template <>
BfmeWideWeekdayIterator
_STL::time_get<wchar_t, BfmeWideWeekdayIterator>::do_get_weekday(
	BfmeWideWeekdayIterator first, BfmeWideWeekdayIterator last,
	_STL::ios_base &, _STL::ios_base::iostate &error, tm *value) const
{
	const _STL::_Time_Info &info = *reinterpret_cast<const _STL::_Time_Info *>(
		reinterpret_cast<const char *>(this) + 0x0C);
	_STL::string *dayNamesEnd;
	const _STL::string *match = _STL::__match(first, last,
		const_cast<_STL::string *>(info._M_dayname),
		dayNamesEnd = const_cast<_STL::string *>(info._M_dayname) + 14,
		(long *)0);
	value->tm_wday = (int)(match - info._M_dayname) % 7;
	if (match != dayNamesEnd)
		error = _STL::ios_base::goodbit;
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
