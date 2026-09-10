// cl: /DNDEBUG /MD /O2
//
// One-row horizontal fixed-point Bink pixel filter, two-tap adjacent-byte
// variant: both taps come from the SAME source read (byte i and byte i+1
// via a one-byte shift) instead of two separate rows, matching
// rva009C7200BinkSse's horizontal half but self-contained with its own
// loop and an MMX-packed four-byte store like rva009C70D0BinkSse.  Retail
// 0x009C7060, 102 bytes.

extern const unsigned short g_bfmeBinkRound[8];

// ?rva009C7060BinkSse@@YAXPBXPAXHHHH0@Z
void __cdecl rva009C7060BinkSse(const void *source, void *destination,
	int sourceStride, int unused, int count, int destinationStride,
	const void *weights)
{
	__asm
	{
		mov edi, weights
		movdqa xmm1, [edi]
		movdqa xmm2, [edi + 10h]
		mov edi, destination
		mov esi, source
		mov ecx, count
		mov eax, destinationStride
		pxor xmm0, xmm0
	rvaNext:
		movdqu xmm3, [esi]
		movdqu xmm5, xmm3
		punpcklbw xmm3, xmm0
		pmullw xmm3, xmm1
		psrldq xmm5, 1
		punpcklbw xmm5, xmm0
		pmullw xmm5, xmm2
		paddw xmm3, xmm5
		paddw xmm3, g_bfmeBinkRound
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
