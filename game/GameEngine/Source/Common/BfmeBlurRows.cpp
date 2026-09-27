// Scalar 3-tap vertical box blur over one column of an image: the first and
// last rows are copied verbatim, every row between them becomes
// (prev + 2*cur + next + 2) >> 2. Installed into dispatch slot 3 by the
// matched bfmeInstallCpuDispatchTable (0x009B0D60) in the generic tier, where
// the SSE and MMX tiers install bfmeBlurRowsSse and bfmeBlurRowsMmx instead;
// bfmeBlurRowsMmx and bfmeBlurRowsSse are the same blur in the other two
// instruction sets.
//
// The locals are ordered and spelled to reproduce retail's register
// assignment: the four pointers are materialised src, width, dst before the
// first memcpy, the walking `next` is derived inside the loop body so retail's
// strength reduction builds it in the loop preheader (after the row-count
// guard), and the inner trip count is a signed compare so retail's guard is
// `test`/`jle` while its latch is an unsigned `dec`/`jne`.

extern "C" void * __cdecl memcpy(void *destination, const void *source, unsigned int bytes);
#pragma intrinsic(memcpy)

void __cdecl bfmeBlurRows(void *src, void *dst, unsigned int width, int count, int stride)
{
	unsigned char *out;
	const unsigned char *cur;
	const unsigned char *next;
	const unsigned char *prev;
	int x;
	int i;
	unsigned int w;

	cur = (const unsigned char *)src;
	prev = cur;
	w = width;
	out = (unsigned char *)dst;
	memcpy(out, cur, w);
	for (i = 1; i < count - 1; i++) {
		prev = cur;
		cur += stride;
		next = cur + stride;
		out += stride;
		for (x = 0; x < (int)w; x++)
			out[x] = (unsigned char)((prev[x] + 2u * cur[x] + 2u + next[x]) >> 2);
	}
	memcpy(out + stride, cur + stride, w);
}
