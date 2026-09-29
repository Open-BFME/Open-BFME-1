// MMX tier of the 3-tap vertical box blur over one column of an image: the
// first and last rows are copied verbatim, every row between them becomes
// (prev + 2*cur + next + 2) >> 2, eight bytes at a time. Installed into
// dispatch slot 3 by the matched bfmeInstallCpuDispatchTable (0x009B0D60) in
// the MMX tier, where the SSE and generic tiers install bfmeBlurRowsSse and
// bfmeBlurRows; the scalar bfmeBlurRows in BfmeBlurRows.cpp is this same blur.
//
// The blur itself is inline asm: MSVC 7.1 has no way to reach this packed-word
// shape from C++ (its intrinsic form also forces a stack-alignment prologue
// retail does not have), exactly as in the sibling bfmeFilterPairMmx. The loop
// scaffolding around it IS C++ and is what fixes retail's register choice:
// `cur`/`out` are pointer locals seeded from the parameters, so the allocator
// keeps `out` in eax across the leading memcpy and reloads the three row
// pointers at the top of each iteration, while `i` coalesces onto the
// `count` argument slot and yields retail's memory-decrement latch. The
// spelling of the tail (`cur += stride; out += stride; memcpy(out, cur, ...)`)
// is what leaves the destination in a register for the final copy.

extern "C" void * __cdecl memcpy(void *destination, const void *source, unsigned int bytes);
#pragma intrinsic(memcpy)

namespace
{
	__declspec(align(8)) const unsigned short g_bfmeBlurBiasMmx[4] = { 2, 2, 2, 2 };
}

// ?bfmeBlurRowsMmx@@YAXPAX0IHH@Z
void __cdecl bfmeBlurRowsMmx(void *src, void *dst, unsigned int width, int count, int stride)
{
	const unsigned char *cur = (const unsigned char *)src;
	unsigned char *out = (unsigned char *)dst;
	int i;

	memcpy(out, cur, width);
	for (i = 1; i < count - 1; i++) {
		out += stride;
		__asm
		{
			mov esi, cur
			mov edi, out
			xor ecx, ecx
			mov edx, stride
			lea eax, [esi + edx]
			lea edx, [eax + edx]
			mov ebx, width
			pxor mm7, mm7
		bfmeInner:
			movq mm0, qword ptr [esi + ecx]
			movq mm1, qword ptr [eax + ecx]
			movq mm3, mm0
			punpcklbw mm0, mm7
			movq mm2, qword ptr [edx + ecx]
			punpckhbw mm3, mm7
			movq mm4, mm1
			punpcklbw mm1, mm7
			paddw mm0, g_bfmeBlurBiasMmx
			paddw mm3, g_bfmeBlurBiasMmx
			punpckhbw mm4, mm7
			psllw mm1, 1
			psllw mm4, 1
			movq mm5, mm2
			punpcklbw mm2, mm7
			paddw mm0, mm1
			paddw mm3, mm4
			punpckhbw mm5, mm7
			paddw mm0, mm2
			paddw mm3, mm5
			psraw mm0, 2
			psraw mm3, 2
			packuswb mm0, mm3
			movq qword ptr [edi + ecx], mm0
			add ecx, 8
			cmp ecx, ebx
			jl bfmeInner
		}
		cur += stride;
	}
	cur += stride;
	out += stride;
	memcpy(out, cur, width);
}
