// cl: /DNDEBUG /MD /O2
//
// Open-BFME5: average two 8-byte rows into words.  Retail 0x009C6DE0, 84 bytes.

void __cdecl bfmeAvg8to16Mmx(const void *srcA, const void *srcB, void *dst, int stride)
{
	__asm
	{
		mov esi, srcA
		mov eax, srcB
		mov edi, dst
		mov ecx, 8
		mov edx, stride
		pxor mm7, mm7
	bfmeNext:
		movq mm0, qword ptr [esi]
		movq mm1, qword ptr [eax]
		movq mm2, mm0
		punpcklbw mm0, mm7
		movq mm3, mm1
		punpcklbw mm1, mm7
		paddw mm0, mm1
		punpckhbw mm2, mm7
		psraw mm0, 1
		punpckhbw mm3, mm7
		paddw mm2, mm3
		movq qword ptr [edi], mm0
		psraw mm2, 1
		add esi, edx
		add eax, edx
		add edi, 10h
		movq qword ptr [edi - 8], mm2
		dec ecx
		jne bfmeNext
	}
}
