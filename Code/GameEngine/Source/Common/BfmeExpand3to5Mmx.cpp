// 3-byte source groups expanded to 5-byte destination groups with a 4-lane
// linear interpolator. Tail shuffles the last over-read so the final store
// stays in-lane without a second loop.

namespace
{
	__declspec(align(8)) const unsigned short g_bfmeW3A[4] = { 102, 205, 51, 154 };
	__declspec(align(8)) const unsigned short g_bfmeW3B[4] = { 154, 51, 205, 102 };
	__declspec(align(8)) const unsigned short g_bfmeRound8[4] = { 128, 128, 128, 128 };
}

// ?bfmeExpand3to5Mmx@@YAXPBXHPAX@Z
void __cdecl bfmeExpand3to5Mmx(const void *source, int bytes, void *destination)
{
	__asm
	{
		push ebx
		mov esi, source
		mov edi, destination
		mov ecx, bytes
		lea edx, [esi+ecx-3]
		movq mm5, g_bfmeW3A
		movq mm6, g_bfmeW3B
		movq mm4, g_bfmeRound8
		pxor mm7, mm7
	bfmeNext:
		mov eax, dword ptr [esi]
		mov ebx, eax
		and ebx, 00ffff00h
		mov ecx, eax
		and eax, 0ffff0000h
		xor ecx, eax
		shr ebx, 8
		or eax, ebx
		shl ebx, 10h
		movd mm1, eax
		or ebx, ecx
		punpcklbw mm1, mm7
		movd mm0, ebx
		pmullw mm1, mm6
		punpcklbw mm0, mm7
		pmullw mm0, mm5
		mov dword ptr [edi], ebx
		add esi, 3
		add edi, 5
		paddw mm0, mm1
		paddw mm0, mm4
		psrlw mm0, 8
		cmp esi, edx
		packuswb mm0, mm7
		movd dword ptr [edi-4], mm0
		jl bfmeNext

		mov eax, dword ptr [esi]
		mov ebx, eax
		and ebx, 00ffff00h
		mov ecx, eax
		and eax, 0ffff0000h
		xor ecx, eax
		shr ebx, 8
		or eax, ebx
		shl eax, 8
		and eax, 0ffff0000h
		or eax, ebx
		shl ebx, 10h
		movd mm1, eax
		or ebx, ecx
		punpcklbw mm1, mm7
		movd mm0, ebx
		pmullw mm1, mm6
		punpcklbw mm0, mm7
		pmullw mm0, mm5
		mov dword ptr [edi], ebx
		paddw mm0, mm1
		paddw mm0, mm4
		psrlw mm0, 8
		packuswb mm0, mm7
		movd dword ptr [edi+1], mm0
		pop ebx
	}
}
