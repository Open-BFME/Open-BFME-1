// cl: /DNDEBUG /MD /O2
//
// Second MMX four-tap vertical Bink filter sharing the 0x012D88D0 round
// table with rva009C6470BinkMmx: same four rows (-stride, 0, +stride,
// +stride*2) and two four-pixel passes, but reads each tap through a
// stride-relative offset from a single base register instead of
// re-deriving the base, and combines taps with plain (non-saturating)
// paddw.  Retail 0x009C6620, 198 bytes.

extern const unsigned short Rva012D88D0Round[4];	// retail 0x012D88D0

// ?rva009C6620BinkMmx@@YAXPBXPAXHHHH0@Z
void __cdecl rva009C6620BinkMmx(const void *source, void *destination,
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
		mov edx, sourceStride
		mov edi, destination
		mov esi, source
		sub esi, sourceStride
		mov ecx, count
		mov eax, destinationStride
		pxor mm0, mm0
	rvaNext:
		movq mm3, qword ptr [esi]
		punpcklbw mm3, mm0
		pmullw mm3, mm1
		movq mm4, qword ptr [esi + edx]
		punpcklbw mm4, mm0
		pmullw mm4, mm2
		paddw mm3, mm4
		movq mm4, qword ptr [esi + edx * 2]
		punpcklbw mm4, mm0
		pmullw mm4, mm6
		paddw mm3, mm4
		add esi, edx
		movq mm4, qword ptr [esi + edx * 2]
		punpcklbw mm4, mm0
		pmullw mm4, mm7
		paddw mm3, mm4
		paddw mm3, qword ptr Rva012D88D0Round
		psraw mm3, 7
		packuswb mm3, mm0
		movd dword ptr [edi], mm3
		sub esi, edx
		movq mm3, qword ptr [esi + 4]
		punpcklbw mm3, mm0
		pmullw mm3, mm1
		movq mm4, qword ptr [esi + edx + 4]
		punpcklbw mm4, mm0
		pmullw mm4, mm2
		paddw mm3, mm4
		movq mm4, qword ptr [esi + edx * 2 + 4]
		punpcklbw mm4, mm0
		pmullw mm4, mm6
		paddw mm3, mm4
		add esi, edx
		movq mm4, qword ptr [esi + edx * 2 + 4]
		punpcklbw mm4, mm0
		pmullw mm4, mm7
		paddw mm3, mm4
		paddw mm3, qword ptr Rva012D88D0Round
		psraw mm3, 7
		packuswb mm3, mm0
		movd dword ptr [edi + 4], mm3
		add edi, eax
		dec ecx
		jne rvaNext
	}
}
