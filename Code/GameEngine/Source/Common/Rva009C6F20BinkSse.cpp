// cl: /DNDEBUG /MD /O2
//
// Four-tap horizontal fixed-point Bink pixel filter: reads one unaligned
// 16-byte window starting at source-1 plus a second at source, and pulls
// all four taps (source-1, source, source+1, source+2) out of those two
// registers with byte shifts instead of four separate loads, matching
// rva009C6FC0BinkSse's four-tap vertical sibling.  Retail 0x009C6F20,
// 159 bytes.

extern const unsigned short g_bfmeBinkRound[8];

// ?rva009C6F20BinkSse@@YAXPBXPAXHHHH0@Z
void __cdecl rva009C6F20BinkSse(const void *source, void *destination,
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
		mov edi, destination
		mov esi, source
		dec esi
		mov ecx, count
		mov eax, destinationStride
		pxor xmm0, xmm0
	rvaNext:
		movdqu xmm3, [esi]
		movdqu xmm4, xmm3
		punpcklbw xmm3, xmm0
		pmullw xmm3, xmm1
		psrldq xmm4, 3
		movdqa xmm5, xmm4
		punpcklbw xmm5, xmm0
		pmullw xmm5, xmm7
		paddsw xmm3, xmm5
		movdqu xmm4, [esi + 1]
		movdqa xmm5, xmm4
		punpcklbw xmm5, xmm0
		pmullw xmm5, xmm2
		paddsw xmm3, xmm5
		psrldq xmm4, 1
		movdqa xmm5, xmm4
		punpcklbw xmm5, xmm0
		pmullw xmm5, xmm6
		paddsw xmm3, xmm5
		paddsw xmm3, g_bfmeBinkRound
		psraw xmm3, 7
		packuswb xmm3, xmm0
		movdq2q mm0, xmm3
		movq qword ptr [edi], mm0
		add esi, dword ptr sourceStride
		add edi, eax
		dec ecx
		jne rvaNext
	}
}
