// cl: /DNDEBUG /MD /O2
//
// MMX two-row Bink pixel filter.  Retail 0x009C6780, 125 bytes.
// MSVC 7.1 does not form this packed-word loop from scalar C++, so the
// register-level implementation stays in inline assembly.

extern const unsigned short g_bfmeBinkRound[8];

// ?rva009C6780BinkMmx@@YAXPBXPAXHHHH0@Z
void __cdecl rva009C6780BinkMmx(const void *source, void *destination,
	int sourceStride, int unused, int count, int destinationStride,
	const void *weights)
{
	__asm
	{
		mov edi, weights
		movq mm1, qword ptr [edi]
		movq mm2, qword ptr [edi + 10h]
		mov edx, sourceStride
		mov edi, destination
		mov esi, source
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
		paddw mm3, g_bfmeBinkRound
		psraw mm3, 7
		packuswb mm3, mm0
		movd dword ptr [edi], mm3
		movq mm3, qword ptr [esi + 4]
		punpcklbw mm3, mm0
		pmullw mm3, mm1
		movq mm4, qword ptr [esi + edx + 4]
		punpcklbw mm4, mm0
		pmullw mm4, mm2
		paddw mm3, mm4
		paddw mm3, g_bfmeBinkRound
		psraw mm3, 7
		packuswb mm3, mm0
		movd dword ptr [edi + 4], mm3
		add esi, edx
		add edi, eax
		dec ecx
		jne rvaNext
	}
}
