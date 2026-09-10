// cl: /DNDEBUG /MD /O2
//
// MMX four-tap horizontal Bink filter: pulls all four taps (source-1,
// source, source+1, source+2) out of a single unaligned qword load via
// repeated one-byte right shifts, matching rva009C6F20BinkSse's shift
// technique but four pixels at a time, so the eight-pixel strip needs two
// passes like the family's other MMX siblings; shares the 0x012D88D0
// round table with rva009C6470BinkMmx and rva009C6620BinkMmx.  Retail
// 0x009C6540, 211 bytes.

extern const unsigned short Rva012D88D0Round[4];	// retail 0x012D88D0

// ?rva009C6540BinkMmx@@YAXPBXPAXHHHH0@Z
void __cdecl rva009C6540BinkMmx(const void *source, void *destination,
	int sourceStride, int unused, int count, int destinationStride,
	const void *weights)
{
	__asm
	{
		mov edi, weights
		movq mm1, qword ptr [edi]
		movq mm2, qword ptr [edi + 10h]
		movq mm6, qword ptr [edi + 20h]
		movq mm7, qword ptr [edi + 30h]
		mov edi, destination
		mov esi, source
		dec esi
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
		psrlq mm4, 8
		movq mm5, mm4
		punpcklbw mm5, mm0
		pmullw mm5, mm6
		paddw mm3, mm5
		psrlq mm4, 8
		movq mm5, mm4
		punpcklbw mm5, mm0
		pmullw mm5, mm7
		paddw mm3, mm5
		paddw mm3, qword ptr Rva012D88D0Round
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
		psrlq mm4, 8
		movq mm5, mm4
		punpcklbw mm5, mm0
		pmullw mm5, mm6
		paddw mm3, mm5
		psrlq mm4, 8
		movq mm5, mm4
		punpcklbw mm5, mm0
		pmullw mm5, mm7
		paddw mm3, mm5
		paddw mm3, qword ptr Rva012D88D0Round
		psraw mm3, 7
		packuswb mm3, mm0
		movd dword ptr [edi + 4], mm3
		add esi, dword ptr sourceStride
		add edi, eax
		dec ecx
		jne rvaNext
	}
}
