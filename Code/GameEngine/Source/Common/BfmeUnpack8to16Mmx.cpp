// cl: /DNDEBUG /MD /O2
//
// Open-BFME5: 8-row unpack of 8 source bytes to 8 words via MMX.  Retail
// 0x009C6E40, 53 bytes.  MSVC 7.1 does not emit this MMX loop from C++.

void __cdecl bfmeUnpack8to16Mmx(const void *src, void *dst, int stride)
{
	__asm
	{
		mov esi, src
		mov edi, dst
		mov ecx, 8
		mov edx, stride
		pxor mm7, mm7
	bfmeNext:
		movq mm0, qword ptr [esi]
		movq mm2, mm0
		punpcklbw mm0, mm7
		movq qword ptr [edi], mm0
		punpckhbw mm2, mm7
		add esi, edx
		movq qword ptr [edi + 8], mm2
		add edi, 10h
		dec ecx
		jne bfmeNext
	}
}
