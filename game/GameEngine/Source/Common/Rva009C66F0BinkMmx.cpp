// cl: /DNDEBUG /MD /O2
//
// MMX two-row Bink pixel filter.  Retail 0x009C66F0 uses the same ABI and
// weight table as Rva009C6780BinkMmx, but filters the low and high four-pixel
// groups from each source row separately.

extern const unsigned short g_bfmeBinkRound[8];

// ?rva009C66F0BinkMmx@@YAXPBXPAXHHHH0@Z
void __cdecl rva009C66F0BinkMmx(const void *source, void *destination,
	int sourceStride, int unused, int count, int destinationStride,
	const void *weights)
{
	__asm
	{
		mov edi, weights
		movq mm1, qword ptr [edi]
		movq mm2, qword ptr [edi + 10h]
		mov edi, destination
		mov esi, source
		mov ecx, count
		mov eax, destinationStride
		pxor mm0, mm0
	rvaNext:
		movq mm3, qword ptr [esi]
		movq mm4, mm3
		punpcklbw mm3, mm0
		pmullw mm3, mm1
		psrlq mm4, 8
		movq mm5, mm4
		punpcklbw mm5, mm0
		pmullw mm5, mm2
		paddw mm3, mm5
		paddw mm3, g_bfmeBinkRound
		psraw mm3, 7
		packuswb mm3, mm0
		movd dword ptr [edi], mm3
		movq mm3, qword ptr [esi + 4]
		movq mm4, mm3
		punpcklbw mm3, mm0
		pmullw mm3, mm1
		psrlq mm4, 8
		movq mm5, mm4
		punpcklbw mm5, mm0
		pmullw mm5, mm2
		paddw mm3, mm5
		paddw mm3, g_bfmeBinkRound
		psraw mm3, 7
		packuswb mm3, mm0
		movd dword ptr [edi + 4], mm3
		add esi, sourceStride
		add edi, eax
		dec ecx
		jne rvaNext
	}
}
