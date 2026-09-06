// cl: /DNDEBUG /MD /O2
//
// MMX two-row Bink pixel filter.  Retail 0x009C6390, 211 bytes.
// MSVC 7.1 does not form this packed-word loop from scalar C++, so the
// register-level implementation stays in inline assembly.

extern const unsigned short g_bfmeBinkRound[8];

// ?rva009C6390BinkMmx@@YAXPBXPAXHHHH0@Z
void __cdecl rva009C6390BinkMmx(const void *source, void *destination,
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
		psrlq mm4, 18h
		movq mm5, mm4
		punpcklbw mm5, mm0
		pmullw mm5, mm7
		paddsw mm3, mm5
		movq mm4, qword ptr [esi + 1]
		movq mm5, mm4
		punpcklbw mm5, mm0
		pmullw mm5, mm2
		paddsw mm3, mm5
		psrlq mm4, 8
		movq mm5, mm4
		punpcklbw mm5, mm0
		pmullw mm5, mm6
		paddsw mm3, mm5
		paddsw mm3, g_bfmeBinkRound
		psraw mm3, 7
		packuswb mm3, mm0
		movd dword ptr [edi], mm3

		movq mm3, qword ptr [esi + 4]
		movq mm4, mm3
		punpcklbw mm3, mm0
		pmullw mm3, mm1
		psrlq mm4, 18h
		movq mm5, mm4
		punpcklbw mm5, mm0
		pmullw mm5, mm7
		paddsw mm3, mm5
		movq mm4, qword ptr [esi + 5]
		movq mm5, mm4
		punpcklbw mm5, mm0
		pmullw mm5, mm2
		paddsw mm3, mm5
		psrlq mm4, 8
		movq mm5, mm4
		punpcklbw mm5, mm0
		pmullw mm5, mm6
		paddsw mm3, mm5
		paddsw mm3, g_bfmeBinkRound
		psraw mm3, 7
		packuswb mm3, mm0
		movd dword ptr [edi + 4], mm3

		add esi, sourceStride
		add edi, eax
		dec ecx
		jne rvaNext
	}
}
