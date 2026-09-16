// ?do_get_time@?$time_get@GV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@2@V32@0AAVios_base@2@AAHPAUtm@@@Z
// STLport 4.5.3 wide time_get::do_get_time.
// The RTTI table at VA 0x0112EB70 names time_get<wchar_t>.
// Its slot 2 points to this 112-byte body at RVA 0x0083C6A0.
// cl: /O2 /Ob0 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#define private public
#include <locale>
#undef private

typedef _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> >
	BfmeWideTimeIterator;

template <>
BfmeWideTimeIterator
_STL::time_get<wchar_t, BfmeWideTimeIterator>::do_get_time(
	BfmeWideTimeIterator first, BfmeWideTimeIterator last,
	_STL::ios_base &, _STL::ios_base::iostate &error, tm *value) const
{
	const _STL::_Time_Info &info = *reinterpret_cast<const _STL::_Time_Info *>(
		reinterpret_cast<const char *>(this) + 0x0C);
	const char *const *time_ptrs = reinterpret_cast<const char *const *>(
		reinterpret_cast<const char *>(this) + 0x1EC);
	const char *format = time_ptrs[0];
	const char *format_end = time_ptrs[1];
	const char *result = _STL::__get_formatted_time(
		first, last, format, format_end, info, error, value);
	error = result == format_end ? _STL::ios_base::goodbit
		: _STL::ios_base::failbit;
	if (first.equal(last))
		error |= _STL::ios_base::eofbit;
	return first;
}
