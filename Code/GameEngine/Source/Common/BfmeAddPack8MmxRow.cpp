// cl: /DNDEBUG /MD /O2
//
// Open-BFME5: unpack 8 source bytes, add dest words, pack to unsigned bytes.
// Retail 0x009C6C60, 75 bytes.

void __cdecl bfmeAddPack8MmxRow(void *, void *dst, const void *src, const void *words, int stride)
{
	__asm
	{
		push edi
		mov ebx, src
		mov ecx, words
		mov eax, dst
		mov edx, stride
		pxor mm0, mm0
		lea edi, [ecx + 80h]
	bfmeNext:
		movq mm2, qword ptr [ebx]
		movq mm4, qword ptr [ecx]
		movq mm3, mm2
		movq mm5, qword ptr [ecx + 8]
		punpcklbw mm2, mm0
		paddsw mm2, mm4
		punpckhbw mm3, mm0
		paddsw mm3, mm5
		add ebx, edx
		packuswb mm2, mm3
		lea ecx, [ecx + 10h]
		cmp ecx, edi
		movq qword ptr [eax], mm2
		lea eax, [eax + edx]
		jb bfmeNext
		pop edi
	}
}
