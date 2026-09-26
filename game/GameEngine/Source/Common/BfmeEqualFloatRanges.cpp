// cl: /DNDEBUG /MD /EHsc
//
// 0x000CD0D0: two {begin,end} float spans, reject when byte-lengths differ
// in any bit above 1:0, then bfmeEqualFloats(first1, last1, first2).
// Callee already matched at 0x000CB730.

struct BfmeFloatSpan
{
	const float *begin;
	const float *end;
};

bool __cdecl bfmeEqualFloats(const float *first, const float *last, const float *other);

// ?bfmeEqualFloatRanges@@YAHPBUBfmeFloatSpan@@0@Z
int __cdecl bfmeEqualFloatRanges(const BfmeFloatSpan *left, const BfmeFloatSpan *right)
{
	const float *last1 = left->end;
	const float *first1 = left->begin;
	const float *first2 = right->begin;
	const float *last2 = right->end;
	unsigned int lenXor = (unsigned int)((const char *)last1 - (const char *)first1)
		^ (unsigned int)((const char *)last2 - (const char *)first2);
	if ((lenXor & 0xFFFFFFFCu) == 0)
	{
		if (bfmeEqualFloats(first1, last1, first2))
			return 1;
	}
	return 0;
}
