// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 narrow floating-point output helper.

#include "stlport_prefix.h"
#include <stl/_string.h>
#include <stl/_ios.h>
#include <stl/_numpunct.h>
#include <stl/_ostreambuf_iterator.h>

_STLP_BEGIN_NAMESPACE

// The retail instantiation was compiled without exposing this specialization's
// body to __put_float.  Keeping the already-emitted helper opaque preserves the
// caller's distinct decimal-position stack slot.
template <>
char *_STLP_CALL __find<char *, char>(char *, char *, const char &,
	const random_access_iterator_tag &);

void _STLP_CALL __adjust_float_buffer(char *, char *, char);

ptrdiff_t _STLP_CALL __insert_grouping(char *, char *,
	const string &, char, char, char, int);

template <class CharT, class OutputIter>
OutputIter _STLP_CALL __copy_float_and_fill(const CharT *, const CharT *,
	OutputIter, ios_base::fmtflags, streamsize, CharT, CharT, CharT);

template <class OutputIter>
OutputIter _STLP_CALL __put_float(char *input, char *input_end,
	OutputIter out, ios_base &stream, char fill, char decimal_point,
	char separator, const string &grouping)
{
	__adjust_float_buffer(input, input_end, decimal_point);
	if (!grouping.empty())
	{
		string new_grouping = grouping;
		const char *decimal_pos = find(input, input_end, decimal_point);
		if (grouping.size() == 1)
			new_grouping.push_back(grouping[0]);

		new_grouping[0] += (char)(input_end - decimal_pos);
		ptrdiff_t length = __insert_grouping(input, input_end, new_grouping,
			separator, '+', '-', 0);
		input_end = input + length;
	}

	return __copy_float_and_fill(input, input_end, out, stream.flags(),
		stream.width(0), fill, '+', '-');
}

typedef ostreambuf_iterator<char, char_traits<char> >
	BfmeNarrowNumPutIterator;

template BfmeNarrowNumPutIterator _STLP_CALL
__put_float<BfmeNarrowNumPutIterator>(char *, char *,
	BfmeNarrowNumPutIterator, ios_base &, char, char, char,
	const string &);

_STLP_END_NAMESPACE
