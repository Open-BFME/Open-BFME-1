// ?do_put@?$time_put@DV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@MBE?AV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@2@V32@AAVios_base@2@DPBUtm@@DD@Z
// partial score=0.51 date=2026-09-02
// cl: /O2 /Ob0 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Narrow time_put virtual formatter with the retail iterator call boundary.
#define private public
#include <locale>
#undef private

typedef _STL::ostreambuf_iterator<char, _STL::char_traits<char> >
	BfmeNarrowTimeOutputIterator;

template <>
BfmeNarrowTimeOutputIterator
_STL::time_put<char, BfmeNarrowTimeOutputIterator>::do_put(
	BfmeNarrowTimeOutputIterator out, _STL::ios_base &stream, char,
	const tm *value, char format, char modifier) const
{
	char buffer[64];
	BfmeNarrowTimeOutputIterator result = out;
	int count = (int)(_STL::__write_formatted_time(buffer, format, modifier,
		*reinterpret_cast<const _STL::_Time_Info *>(
			reinterpret_cast<const char *>(this) + 0x0C), value) - buffer);
	if (count > 0)
	{
		char *p = buffer;
		do
		{
			*result++ = *p++;
		} while (--count != 0);
	}
	return result;
}
