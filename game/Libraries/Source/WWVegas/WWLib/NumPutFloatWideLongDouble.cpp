// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// BFME's STLport 4.5.3 wide _M_do_put_float<long double> specialization.
// Retail owns a string and reserves 128 bytes here, unlike the stock
// specialization's char[128] stack buffer; its unwind path destroys the string.

#include "stlport_prefix.h"
#include <stl/_string.h>
#include <stl/_ios.h>
#include <stl/_numpunct.h>
#include <stl/_ostreambuf_iterator.h>

_STLP_BEGIN_NAMESPACE

void _STLP_CALL __write_float(string &, ios_base::fmtflags, int, long double);

template <class OutputIter>
OutputIter _STLP_CALL __put_float(char *, char *, OutputIter,
	ios_base &, wchar_t, wchar_t, wchar_t, const string &);

template <class CharT, class OutputIter, class Float>
OutputIter _STLP_CALL _M_do_put_float(
	OutputIter out, ios_base &stream, CharT fill, Float value)
{
	string buffer;
	buffer.reserve(128);
	__write_float(buffer, stream.flags(), (int)stream.precision(), value);
	const numpunct<CharT> &punct =
		*(const numpunct<CharT> *)stream._M_numpunct_facet();
	return __put_float(buffer.begin(), buffer.begin() + buffer.size(),
		out, stream, fill,
		punct.decimal_point(), punct.thousands_sep(), stream._M_grouping());
}

typedef ostreambuf_iterator<wchar_t, char_traits<wchar_t> >
	BfmeWideNumPutIterator;

template BfmeWideNumPutIterator _STLP_CALL
_M_do_put_float<wchar_t, BfmeWideNumPutIterator, long double>(
	BfmeWideNumPutIterator, ios_base &, wchar_t, long double);

_STLP_END_NAMESPACE
