// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 wide floating-point formatting specializations.

#include "stlport_prefix.h"
#include <stl/_string.h>
#include <stl/_ios.h>
#include <stl/_ctype.h>
#include <stl/_numpunct.h>
#include <stl/_ostreambuf_iterator.h>

_STLP_BEGIN_NAMESPACE

wchar_t *_STLP_CALL __convert_float_buffer(const char *, const char *,
	wchar_t *, const ctype<wchar_t> &, wchar_t);

ptrdiff_t _STLP_CALL __insert_grouping(wchar_t *, wchar_t *,
	const string &, wchar_t, wchar_t, wchar_t, int);

template <class CharT, class OutputIter>
OutputIter _STLP_CALL __copy_float_and_fill(const CharT *, const CharT *,
	OutputIter, ios_base::fmtflags, streamsize, CharT, CharT, CharT);

template <class OutputIter>
OutputIter _STLP_CALL __put_float(char *input, char *input_end,
	OutputIter out, ios_base &stream, wchar_t fill, wchar_t decimal_point,
	wchar_t separator, const string &grouping)
{
	const ctype<wchar_t> &ct =
		*(ctype<wchar_t> *)stream._M_ctype_facet();

	wchar_t buffer[128];
	wchar_t *end = __convert_float_buffer(input, input_end, buffer,
		ct, decimal_point);
	if (!grouping.empty())
	{
		string new_grouping = grouping;
		wchar_t *decimal_pos = find(buffer, end, decimal_point);
		if (grouping.size() == 1)
			new_grouping.push_back(grouping[0]);

		new_grouping[0] += (char)(end - decimal_pos);
		ptrdiff_t length = __insert_grouping(buffer, end, new_grouping,
			separator, ct.widen('+'), ct.widen('-'), 0);
		end = buffer + length;
	}

	return __copy_float_and_fill(buffer, end, out, stream.flags(),
		stream.width(0), fill, ct.widen('+'), ct.widen('-'));
}

typedef ostreambuf_iterator<wchar_t, char_traits<wchar_t> >
	BfmeWideNumPutIterator;

template BfmeWideNumPutIterator _STLP_CALL
__put_float<BfmeWideNumPutIterator>(char *, char *,
	BfmeWideNumPutIterator, ios_base &, wchar_t, wchar_t, wchar_t,
	const string &);

void _STLP_CALL __write_float(string &, ios_base::fmtflags, int, double);

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

template BfmeWideNumPutIterator _STLP_CALL
_M_do_put_float<wchar_t, BfmeWideNumPutIterator, double>(
	BfmeWideNumPutIterator, ios_base &, wchar_t, double);

_STLP_END_NAMESPACE
