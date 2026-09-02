// cl: /DNDEBUG /MD /O2
//
// Open-BFME5: unpack 8 source bytes to words and subtract the destination
// words in place.  Retail 0x009C6E80, 66 bytes.

void __cdecl bfmeSub8to16Mmx(const void *src, void *dst, int stride)
{
	__asm
	{
		mov esi, src
		mov edi, dst
		mov edx, stride
		mov ecx, 8
		pxor mm7, mm7
	bfmeNext:
		movq mm0, qword ptr [esi]
		movq mm1, qword ptr [edi]
		movq mm2, mm0
		punpcklbw mm0, mm7
		movq mm3, qword ptr [edi + 8]
		psubw mm0, mm1
		punpckhbw mm2, mm7
		movq qword ptr [edi], mm0
		psubw mm2, mm3
		add esi, edx
		movq qword ptr [edi + 8], mm2
		add edi, 10h
		dec ecx
		jne bfmeNext
	}
}
