// cl: /O2 /Ob0 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Focused wide time_get date specialization with retail call boundaries.
#define private public
#include <locale>
#undef private

typedef _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> >
	BfmeWideDateIterator;

template <>
BfmeWideDateIterator
_STL::time_get<wchar_t, BfmeWideDateIterator>::do_get_date(
	BfmeWideDateIterator first, BfmeWideDateIterator last,
	_STL::ios_base &, _STL::ios_base::iostate &error, tm *value) const
{
	const _STL::_Time_Info &info = *reinterpret_cast<const _STL::_Time_Info *>(
		reinterpret_cast<const char *>(this) + 0x0C);
	// Retail loads string _M_start/_M_finish directly (no begin/end calls).
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
