// ?rva009C6D30BinkCopy@@YAXPBXPAXH@Z
// partial score=0.55 date=2026-09-10
// cl: /DNDEBUG /MD /O2
//
// 8x8 pixel block copy by stride, used by the Bink filter dispatch to
// relay an unmodified block.  Retail 0x009C6D30, 110 bytes.  Retail has NO
// stack frame (esp-relative addressing throughout) and loads all four rows
// of each unrolled group into mm0-mm3 before storing any of them; every
// C++ shape tried here either collapses to a single reused mm0 (shorter,
// interleaved load/store) or -- once named __m64 locals force four live
// registers -- gains an 8-byte stack-realignment prologue (push ebp / mov
// ebp,esp / and esp,0xfffffff8) that retail does not have.  Closest here:
// named locals, matches retail's load-4-then-store-4 shape but 92B with
// the alignment prologue vs retail's 110B with none.

#include <mmintrin.h>

// ?rva009C6D30BinkCopy@@YAXPBXPAXH@Z
void __cdecl rva009C6D30BinkCopy(const void *source, void *destination, int stride)
{
	const char *src = (const char *)source;
	char *dst = (char *)destination;

	__m64 a = *(const __m64 *)(src);
	__m64 b = *(const __m64 *)(src + stride);
	__m64 c = *(const __m64 *)(src + stride * 2);
	__m64 d = *(const __m64 *)(src + stride * 3);
	src += stride * 4;
	*(__m64 *)(dst) = a;
	*(__m64 *)(dst + stride) = b;
	*(__m64 *)(dst + stride * 2) = c;
	*(__m64 *)(dst + stride * 3) = d;
	dst += stride * 4;

	a = *(const __m64 *)(src);
	b = *(const __m64 *)(src + stride);
	c = *(const __m64 *)(src + stride * 2);
	d = *(const __m64 *)(src + stride * 3);
	*(__m64 *)(dst) = a;
	*(__m64 *)(dst + stride) = b;
	*(__m64 *)(dst + stride * 2) = c;
	*(__m64 *)(dst + stride * 3) = d;
}
