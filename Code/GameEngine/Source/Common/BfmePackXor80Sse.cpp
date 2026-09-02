// cl: /DNDEBUG /MD /O2
//
// Open-BFME5: pack 8 words to signed bytes and xor 0x80.  Retail 0x009C76D0,
// 62 bytes.

__declspec(align(8)) const unsigned char g_bfmeXor80Sse[8] =
	{ 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80 };

void __cdecl bfmePackXor80Sse(void *, void *dst, const void *words, int stride)
{
	__asm
	{
		push ebx
		mov eax, words
		mov edx, dst
		movq xmm0, qword ptr [g_bfmeXor80Sse]
		pxor xmm3, xmm3
		mov ebx, stride
		lea ecx, [eax + 80h]
	bfmeNext:
		movdqa xmm2, xmmword ptr [eax]
		packsswb xmm2, xmm3
		pxor xmm2, xmm0
		lea eax, [eax + 10h]
		cmp eax, ecx
		movq qword ptr [edx], xmm2
		lea edx, [edx + ebx]
		jb bfmeNext
		pop ebx
	}
}
