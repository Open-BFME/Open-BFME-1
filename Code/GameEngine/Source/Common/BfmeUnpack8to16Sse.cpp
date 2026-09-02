// cl: /DNDEBUG /MD /O2
//
// Open-BFME5: 8-row unpack of 8 source bytes to 8 words.  Retail 0x009C7450,
// 49 bytes.  MSVC 7.1 does not emit this SSE loop from C++; the instruction
// sequence is the algorithm.

void __cdecl bfmeUnpack8to16Sse(const void *src, void *dst, int stride)
{
	__asm
	{
		mov edi, dst
		mov esi, src
		mov ecx, 8
		mov eax, 10h
		pxor xmm0, xmm0
	bfmeNext:
		movdqu xmm3, [esi]
		punpcklbw xmm3, xmm0
		movdqu [edi], xmm3
		add esi, stride
		add edi, eax
		dec ecx
		jne bfmeNext
	}
}
