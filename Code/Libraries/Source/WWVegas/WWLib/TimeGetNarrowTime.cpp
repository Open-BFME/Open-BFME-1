// ?do_get_time@?$time_get@DV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@2@V32@0AAVios_base@2@AAHPAUtm@@@Z
// STLport 4.5.3 narrow time_get::do_get_time.
// The RTTI table at VA 0x0112EB44 names time_get<char>.
// Its slot 2 points to this 112-byte body at RVA 0x0083BC30.
// cl: /O2 /Ob0 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#define private public
#include <locale>
#undef private

typedef _STL::istreambuf_iterator<char, _STL::char_traits<char> >
	BfmeNarrowTimeIterator;

template <>
BfmeNarrowTimeIterator
_STL::time_get<char, BfmeNarrowTimeIterator>::do_get_time(
	BfmeNarrowTimeIterator first, BfmeNarrowTimeIterator last,
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
