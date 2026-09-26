// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME: STLport random-access __copy over a 48-byte POD, retail
// 0x001A5BA0.  Ghidra truncated the body at the first ret (72 bytes); the
// empty-range epilogue `mov eax,[esp+0x10]; pop ebx; ret` sits at +72 and
// brings the true size to 78.  Magic 0x2AAAAAAB / sar 3 plus `rep movsd`
// of 12 dwords is a 0x30-byte element.  The payload type is not recovered.

struct BfmeTerrainP48
{
	int m_words[12];
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result,
	const random_access_iterator_tag &, Distance *)
{
	for (Distance count = last - first; count > 0; --count, ++first, ++result)
		*result = *first;
	return result;
}

template BfmeTerrainP48 *__copy<BfmeTerrainP48 *, BfmeTerrainP48 *, int>(
	BfmeTerrainP48 *, BfmeTerrainP48 *, BfmeTerrainP48 *,
	const random_access_iterator_tag &, int *);
}
