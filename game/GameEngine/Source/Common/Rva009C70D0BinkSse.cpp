// cl: /DNDEBUG /MD /O2
//
// One-row horizontal fixed-point Bink pixel filter, four-pixel variant:
// widens eight source bytes, applies the caller's coefficient pair like
// rva009C7320BinkSse, then packs the rounded result down through an MMX
// register and stores only the low four output bytes.  Retail 0x009C70D0,
// 100 bytes.

extern const unsigned short g_bfmeBinkRound[8];

// ?rva009C70D0BinkSse@@YAXPBXPAXHHHH0@Z
void __cdecl rva009C70D0BinkSse(const void *source, void *destination,
	int sourceStride, int unused, int count, int destinationStride,
	const void *weights)
{
	__asm
	{
		mov edi, weights
		movdqa xmm1, [edi]
		movdqa xmm2, [edi + 10h]
		mov edx, sourceStride
		mov edi, destination
		mov esi, source
		mov ecx, count
		mov eax, destinationStride
		pxor xmm0, xmm0
	rvaNext:
		movdqu xmm3, [esi]
		punpcklbw xmm3, xmm0
		pmullw xmm3, xmm1
		movdqu xmm4, [esi + edx]
		punpcklbw xmm4, xmm0
		pmullw xmm4, xmm2
		paddw xmm3, xmm4
		paddw xmm3, g_bfmeBinkRound
		psraw xmm3, 7
		packuswb xmm3, xmm0
		movdq2q mm0, xmm3
		movq qword ptr [edi], mm0
		add esi, edx
		add edi, eax
		dec ecx
		jne rvaNext
	}
}
