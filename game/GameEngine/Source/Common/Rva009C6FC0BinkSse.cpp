// cl: /DNDEBUG /MD /O2
//
// Four-tap vertical fixed-point Bink pixel filter: blends source rows at
// -stride, 0, +stride and +stride*2 through the caller's four-entry
// coefficient table, rounds through the shared g_bfmeBinkRound table and
// packs the result through an MMX register like rva009C70D0BinkSse.
// Retail 0x009C6FC0, 146 bytes.

extern const unsigned short g_bfmeBinkRound[8];

// ?rva009C6FC0BinkSse@@YAXPBXPAXHHHH0@Z
void __cdecl rva009C6FC0BinkSse(const void *source, void *destination,
	int sourceStride, int unused, int count, int destinationStride,
	const void *weights)
{
	__asm
	{
		mov edi, weights
		movdqa xmm1, [edi]
		movdqa xmm2, [edi + 10h]
		movdqa xmm6, [edi + 20h]
		movdqa xmm7, [edi + 30h]
		mov edx, sourceStride
		mov edi, destination
		mov esi, source
		sub esi, sourceStride
		mov ecx, count
		mov eax, destinationStride
		pxor xmm0, xmm0
	rvaNext:
		movdqu xmm3, [esi]
		punpcklbw xmm3, xmm0
		pmullw xmm3, xmm1
		add esi, edx
		movdqu xmm4, [esi + edx * 2]
		punpcklbw xmm4, xmm0
		pmullw xmm4, xmm7
		paddsw xmm3, xmm4
		movdqu xmm4, [esi]
		punpcklbw xmm4, xmm0
		pmullw xmm4, xmm2
		paddsw xmm3, xmm4
		movdqu xmm4, [esi + edx]
		punpcklbw xmm4, xmm0
		pmullw xmm4, xmm6
		paddsw xmm3, xmm4
		paddsw xmm3, g_bfmeBinkRound
		psraw xmm3, 7
		packuswb xmm3, xmm0
		movdq2q mm0, xmm3
		movq qword ptr [edi], mm0
		add edi, eax
		dec ecx
		jne rvaNext
	}
}
