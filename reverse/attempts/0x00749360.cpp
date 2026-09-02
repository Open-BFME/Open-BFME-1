// ??$__copy@PAUBfmeNineWordRecord@@PAU1@H@_STL@@YAPAUBfmeNineWordRecord@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z
// partial score=0.92 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#pragma warning(disable: 4716)

// Open-BFME5: STLport random-access copy helper for a trivially-copyable
// nine-dword record.  Retail divides the byte span by 0x24 and copies nine
// dwords per iteration.

struct BfmeNineWordRecord
{
	int m_words[9];
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy(InputIterator first, InputIterator last,
	OutputIterator result, const random_access_iterator_tag &, Distance *)
{
	for (Distance count = last - first; count > 0;
		--count, ++first, ++result)
	{
		*result = *first;
	}
	return result;
}

template BfmeNineWordRecord *__copy<BfmeNineWordRecord *,
	BfmeNineWordRecord *, int>(BfmeNineWordRecord *, BfmeNineWordRecord *,
	BfmeNineWordRecord *, const random_access_iterator_tag &, int *);
}
