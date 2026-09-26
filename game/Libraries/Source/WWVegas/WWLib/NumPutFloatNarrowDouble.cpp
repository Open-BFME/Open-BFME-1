// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// BFME's STLport 4.5.3 narrow _M_do_put_float<double> specialization.

#include "stlport_prefix.h"
#include <stl/_string.h>
#include <stl/_ios.h>
#include <stl/_numpunct.h>
#include <stl/_ostreambuf_iterator.h>

_STLP_BEGIN_NAMESPACE

void _STLP_CALL __write_float(string &, ios_base::fmtflags, int, double);

template <class OutputIter>
OutputIter _STLP_CALL __put_float(char *, char *, OutputIter,
	ios_base &, char, char, char, const string &);

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

typedef ostreambuf_iterator<char, char_traits<char> >
	BfmeNarrowNumPutIterator;

template BfmeNarrowNumPutIterator _STLP_CALL
_M_do_put_float<char, BfmeNarrowNumPutIterator, double>(
	BfmeNarrowNumPutIterator, ios_base &, char, double);

_STLP_END_NAMESPACE
