// cl: /DNDEBUG /MD /O2
//
// Fuzzy-twin (r0.937) of ?rva009C7200BinkSse@@YAXPBXPAXH00@Z in
// Code/GameEngine/Source/Common/Rva009C7200BinkSse.cpp: identical two-row
// horizontal/vertical fixed-point resampler setup, but this variant packs
// the final signed-16-bit row down to unsigned bytes (packuswb) and stores
// eight destination bytes per iteration via the MMX register (movdq2q +
// movq), instead of the twin's direct 16-byte movdqu store of the raw
// 16-bit pixels. 192B vs the twin's 188B; loop trip count differs (0x40
// vs 0x80 total run) because each iteration now advances the destination
// pointer by 8 bytes instead of 16.
// MSVC 7.1 does not form this SSE2/MMX loop from C++ or its intrinsic
// headers, so the register-level implementation is retained here (same
// anti-lift exception as the twin).

extern const unsigned short g_bfmeBinkRound[8];

// ?d_009c7140@@YAXXZ
void __cdecl rva009C7140BinkSse(const void *source, void *destination,
	int stride, const void *horizontalWeights, const void *verticalWeights)
{
	__asm
	{
		mov eax, horizontalWeights
		mov edi, destination
		mov esi, source
		lea ecx, [edi + 40h]
		mov edx, stride
		movdqa xmm1, [eax]
		movdqa xmm2, [eax + 10h]
		mov eax, verticalWeights
		pxor xmm0, xmm0
		movdqu xmm3, [esi]
		movdqa xmm4, xmm3
		punpcklbw xmm3, xmm0
		psrldq xmm4, 1
		pmullw xmm3, xmm1
		punpcklbw xmm4, xmm0
		pmullw xmm4, xmm2
		paddw xmm3, xmm4
		paddw xmm3, g_bfmeBinkRound
		psraw xmm3, 7
		movdqa xmm5, xmm3
		add esi, edx
	rvaNext:
		pmullw xmm5, xmmword ptr [eax]
		movdqu xmm3, [esi]
		movdqa xmm4, xmm3
		punpcklbw xmm3, xmm0
		psrldq xmm4, 1
		pmullw xmm3, xmm1
		punpcklbw xmm4, xmm0
		movdqa xmm6, xmm5
		pmullw xmm4, xmm2
		paddw xmm3, xmm4
		paddw xmm3, g_bfmeBinkRound
		psraw xmm3, 7
		movdqa xmm5, xmm3
		pmullw xmm3, xmmword ptr [eax + 10h]
		paddw xmm6, xmm3
		paddw xmm6, g_bfmeBinkRound
		psraw xmm6, 7
		packuswb xmm6, xmm0
		movdq2q mm0, xmm6
		movq qword ptr [edi], mm0
		add esi, edx
		add edi, 8
		cmp edi, ecx
		jne short rvaNext
	}
}
