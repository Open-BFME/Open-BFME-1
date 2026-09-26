// cl: /DNDEBUG /MD /O2
//
// Open-BFME5: add two 8-word rows and pack to unsigned bytes.  Retail
// 0x009C6ED0, 66 bytes.

void __cdecl bfmeAddPack8Mmx(const void *srcA, const void *srcB, void *dst, int stride)
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
		movq mm2, qword ptr [esi + 8]
		movq mm3, qword ptr [eax + 8]
		paddw mm0, mm1
		paddw mm2, mm3
		packuswb mm0, mm2
		movq qword ptr [edi], mm0
		add esi, 10h
		add eax, 10h
		add edi, edx
		dec ecx
		jne bfmeNext
	}
}
