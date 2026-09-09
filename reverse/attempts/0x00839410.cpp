// ?do_get@?$money_get@GV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@0_NAAVios_base@2@AAHAAO@Z
// partial score=0.8 date=2026-09-09
// cl: /O2 /Ob1 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 money_get<wchar_t, istreambuf_iterator<wchar_t> > long-double
// overload at retail 0x00839410 (280B).  The vendor _monetary.c body first
// dispatches the string overload, then parses its mutable wide buffer through
// __get_decimal_integer<unsigned short *, long double> at 0x00839600.
#include <locale>

#pragma inline_depth(1)

typedef _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> >
	BfmeMoneyWideIterator;

template <>
BfmeMoneyWideIterator
_STL::money_get<wchar_t, BfmeMoneyWideIterator>::do_get(
	BfmeMoneyWideIterator first, BfmeMoneyWideIterator last, bool intl,
	_STL::ios_base &stream, _STL::ios_base::iostate &error,
	long double &units) const
{
	string_type buffer;
	first = do_get(first, last, intl, stream, error, buffer);

	if (error == _STL::ios_base::goodbit ||
		error == _STL::ios_base::eofbit)
	{
		buffer.push_back(0);
		string_type::iterator begin = buffer.begin(), end = buffer.end();
		_STL::__get_decimal_integer(begin, end, units);
	}

	if (first.equal(last))
		error |= _STL::ios_base::eofbit;
	return first;
}
