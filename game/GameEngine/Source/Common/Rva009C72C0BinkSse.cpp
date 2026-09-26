// cl: /DNDEBUG /MD /O2
//
// One-row horizontal fixed-point Bink pixel filter. Retail 0x009C72C0.
// The neighboring Bink MMX and SSE2 bodies use the same coefficient table at
// 0x012D8C00. MSVC 7.1 does not form this packed-word loop from C++ or its
// intrinsic headers, so the register-level implementation stays in assembly.

extern const unsigned short g_bfmeBinkRound[8];

// ?rva009C72C0BinkSse@@YAXPBXPAXHHHH0@Z
void __cdecl rva009C72C0BinkSse(const void *source, void *destination,
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
		movdqu [edi], xmm3
		add esi, sourceStride
		add edi, eax
		dec ecx
		jne rvaNext
	}
}
