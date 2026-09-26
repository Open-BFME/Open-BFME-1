// cl: /DNDEBUG /MD /O2
//
// Two-row horizontal/vertical fixed-point resampler used by the Bink pixel
// filter.  Each iteration consumes eight source bytes from two adjacent rows,
// applies the caller's eight-tap horizontal coefficients, then combines the
// rows with the two vertical coefficients into eight signed 16-bit pixels.
// MSVC 7.1 does not form this SSE2 loop from C++ or its intrinsic headers, so
// the register-level implementation is retained here.

extern const unsigned short g_bfmeBinkRound[8];

// ?rva009C7200BinkSse@@YAXPBXPAXH00@Z
void __cdecl rva009C7200BinkSse(const void *source, void *destination,
	int stride, const void *horizontalWeights, const void *verticalWeights)
{
	__asm
	{
		mov eax, horizontalWeights
		mov edi, destination
		mov esi, source
		lea ecx, [edi + 80h]
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
		movdqu [edi], xmm6
		add esi, edx
		add edi, 10h
		cmp edi, ecx
		jne short rvaNext
	}
}
