// cl: /DNDEBUG /MD /O2
//
// One-row horizontal fixed-point Bink pixel filter, two-tap variant: each
// output pixel blends the corresponding source byte and its next-row
// neighbor through the caller's coefficient pair before rounding.  Sibling
// of rva009C72C0BinkSse; differs only in explicitly loading the source
// stride into edx instead of referencing the stack slot inline.  Retail
// 0x009C7320, 93 bytes.

extern const unsigned short g_bfmeBinkRound[8];

// ?rva009C7320BinkSse@@YAXPBXPAXHHHH0@Z
void __cdecl rva009C7320BinkSse(const void *source, void *destination,
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
		movdqu [edi], xmm3
		add esi, edx
		add edi, eax
		dec ecx
		jne rvaNext
	}
}
