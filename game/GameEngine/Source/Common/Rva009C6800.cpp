// cl: /DNDEBUG /MD /O2

extern const unsigned short Rva012D88D0Round[4];

// Address-derived identity. The optimized MMX schedule does not reproduce
// from MSVC 7.1 intrinsics, so the filter core stays as typed inline assembly.
void __cdecl Rva009C6800(const unsigned char *source, unsigned char *destination,
	int stride, const void *horizontalWeights, const void *verticalWeights)
{
	__asm
	{
		mov eax, dword ptr [ebp + 14h]
		mov edi, dword ptr [ebp + 0ch]
		mov esi, dword ptr [ebp + 8]
		lea ecx, [edi + 40h]
		mov edx, dword ptr [ebp + 10h]
		movq mm1, qword ptr [eax]
		movq mm2, qword ptr [eax + 10h]
		mov eax, dword ptr [ebp + 18h]
		pxor mm0, mm0
		movq mm3, qword ptr [esi]
		movq mm4, mm3
		punpcklbw mm3, mm0
		punpckhbw mm4, mm0
		pmullw mm3, mm1
		pmullw mm4, mm1
		movq mm5, qword ptr [esi + 1]
		movq mm6, mm5
		punpcklbw mm5, mm0
		punpckhbw mm6, mm0
		pmullw mm5, mm2
		pmullw mm6, mm2
		paddw mm3, mm5
		paddw mm4, mm6
		paddw mm3, qword ptr Rva012D88D0Round
		psraw mm3, 7
		paddw mm4, qword ptr Rva012D88D0Round
		psraw mm4, 7
		movq mm7, mm3
		packuswb mm7, mm4
		add esi, edx
	rva009c6800_loop:
		movq mm3, qword ptr [esi]
		movq mm4, mm3
		punpcklbw mm3, mm0
		punpckhbw mm4, mm0
		pmullw mm3, mm1
		pmullw mm4, mm1
		movq mm5, qword ptr [esi + 1]
		movq mm6, mm5
		punpcklbw mm5, mm0
		punpckhbw mm6, mm0
		pmullw mm5, mm2
		pmullw mm6, mm2
		paddw mm3, mm5
		paddw mm4, mm6
		movq mm5, mm7
		movq mm6, mm7
		punpcklbw mm5, mm0
		punpckhbw mm6, mm0
		pmullw mm5, qword ptr [eax]
		pmullw mm6, qword ptr [eax]
		paddw mm3, qword ptr Rva012D88D0Round
		psraw mm3, 7
		paddw mm4, qword ptr Rva012D88D0Round
		psraw mm4, 7
		movq mm7, mm3
		packuswb mm7, mm4
		pmullw mm3, qword ptr [eax + 10h]
		pmullw mm4, qword ptr [eax + 10h]
		paddw mm3, mm5
		paddw mm4, mm6
		paddw mm3, qword ptr Rva012D88D0Round
		psraw mm3, 7
		paddw mm4, qword ptr Rva012D88D0Round
		psraw mm4, 7
		packuswb mm3, mm4
		movq qword ptr [edi], mm3
		add esi, edx
		add edi, 8
		cmp edi, ecx
		jne rva009c6800_loop
	}
}
