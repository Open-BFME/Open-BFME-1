// cl: /DNDEBUG /MD /O2
//
// Open-BFME5: pack 8 words to signed bytes and xor 0x80.  Retail 0x009C6C20,
// 55 bytes.

__declspec(align(8)) const unsigned char g_bfmeXor80Mmx[8] =
	{ 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80 };

void __cdecl bfmePackXor80Mmx(void *, void *dst, const void *words, int stride)
{
	__asm
	{
		mov eax, words
		mov edx, dst
		movq mm0, qword ptr [g_bfmeXor80Mmx]
		mov ebx, stride
		lea ecx, [eax + 80h]
	bfmeNext:
		movq mm2, qword ptr [eax]
		packsswb mm2, qword ptr [eax + 8]
		por mm0, mm0
		pxor mm2, mm0
		lea eax, [eax + 10h]
		cmp eax, ecx
		movq qword ptr [edx], mm2
		lea edx, [edx + ebx]
		jb bfmeNext
	}
}
