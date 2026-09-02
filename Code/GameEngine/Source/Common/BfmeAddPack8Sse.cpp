// cl: /DNDEBUG /MD /O2
//
// Open-BFME5: unpack 8 source bytes, add dest words, pack to unsigned bytes.
// Retail 0x009C7710, 69 bytes.

void __cdecl bfmeAddPack8Sse(void *, void *dst, const void *src, const void *words, int stride)
{
	__asm
	{
		push edi
		mov ebx, src
		mov ecx, words
		mov eax, dst
		mov edx, stride
		pxor xmm0, xmm0
		lea edi, [ecx + 80h]
	bfmeNext:
		movq xmm2, qword ptr [ebx]
		movdqa xmm4, xmmword ptr [ecx]
		punpcklbw xmm2, xmm0
		add ebx, edx
		paddsw xmm2, xmm4
		lea ecx, [ecx + 10h]
		packuswb xmm2, xmm0
		cmp ecx, edi
		movq qword ptr [eax], xmm2
		lea eax, [eax + edx]
		jb bfmeNext
		pop edi
	}
}
