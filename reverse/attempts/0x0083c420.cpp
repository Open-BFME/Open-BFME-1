// ??$__copy_float_and_fill@GV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@YA?AV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@0@PBG0V10@HHGGG@Z
// partial score=0.8 date=2026-09-09
// cl: /O2 /Ob1 /Oy- /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 __copy_float_and_fill<wchar_t, ostreambuf_iterator<wchar_t> >
// at retail 0x0083C420 (300B).  The matched __put_float<wchar_t> body at
// 0x0083C210 calls this helper after widening and grouping the float buffer.

#define _STLP_LINK_TIME_INSTANTIATION
#include "stlport_prefix.h"
#include <stl/_num_put.h>
#include <stl/_ostreambuf_iterator.h>

_STLP_BEGIN_NAMESPACE

typedef ostreambuf_iterator<wchar_t, char_traits<wchar_t> >
	BfmeWideFloatFillIterator;

template <class CharT, class OutputIter>
OutputIter _STLP_CALL __copy_float_and_fill(
	const CharT *, const CharT *, OutputIter, ios_base::fmtflags,
	streamsize, CharT, CharT, CharT);

#pragma optimize("y", off)
template <>
BfmeWideFloatFillIterator _STLP_CALL
__copy_float_and_fill<wchar_t, BfmeWideFloatFillIterator>(
	const wchar_t *first, const wchar_t *last,
	BfmeWideFloatFillIterator out, ios_base::fmtflags flags,
	streamsize width, wchar_t fill, wchar_t plus, wchar_t minus)
{
	BfmeWideFloatFillIterator result = out;
	if (width <= last - first)
		return copy(first, last, result);

	streamsize pad = width - (last - first);
	ios_base::fmtflags direction = flags & ios_base::adjustfield;
	if (direction == ios_base::left)
	{
		result = copy(first, last, result);
		return fill_n(result, pad, fill);
	}
	else if (direction == ios_base::internal && first != last &&
		(*first == plus || *first == minus))
	{
		*result++ = *first++;
		result = fill_n(result, pad, fill);
		return copy(first, last, result);
	}
	else
	{
		result = fill_n(result, pad, fill);
		return copy(first, last, result);
	}
}
#pragma optimize("y", on)

_STLP_END_NAMESPACE
