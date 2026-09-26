// 8 source bytes to 10 destination bytes (4:5) with complementary 1/5..4/5
// weights. Tail replicates the last source byte via a psrlq/pand/psllq rotate,
// same trick as bfmeExpandMmx.

namespace
{
	__declspec(align(8)) const unsigned short g_bfmeW4A[4] = { 51, 102, 154, 205 };
	__declspec(align(8)) const unsigned short g_bfmeW4B[4] = { 205, 154, 102, 51 };
	__declspec(align(8)) const unsigned short g_bfmeRound8b[4] = { 128, 128, 128, 128 };
	__declspec(align(8)) const unsigned char g_bfmeTailMask[8] = { 0, 0, 0, 0, 0, 0, 255, 0 };
}

// ?bfmeExpand4to5Mmx@@YAXPBXHPAX@Z
void __cdecl bfmeExpand4to5Mmx(const void *source, int bytes, void *destination)
{
	__asm
	{
		mov esi, source
		mov edi, destination
		mov ecx, bytes
		lea edx, [esi+ecx-8]
		movq mm5, g_bfmeW4A
		movq mm6, g_bfmeW4B
		movq mm4, g_bfmeRound8b
		pxor mm7, mm7
	bfmeNext:
		movq mm0, qword ptr [esi]
		movq mm1, qword ptr [esi+1]
		movq mm2, mm0
		movq mm3, mm1
		movd dword ptr [edi], mm0
		punpcklbw mm0, mm7
		punpcklbw mm1, mm7
		pmullw mm0, mm5
		pmullw mm1, mm6
		punpckhbw mm2, mm7
		movd dword ptr [edi+5], mm2
		pmullw mm2, mm5
		punpckhbw mm3, mm7
		pmullw mm3, mm6
		paddw mm0, mm1
		paddw mm0, mm4
		psrlw mm0, 8
		packuswb mm0, mm7
		movd dword ptr [edi+1], mm0
		add edi, 0Ah
		add esi, 8
		paddw mm2, mm3
		paddw mm2, mm4
		cmp esi, edx
		psrlw mm2, 8
		packuswb mm2, mm7
		movd dword ptr [edi-4], mm2
		jl bfmeNext

		movq mm0, qword ptr [esi]
		movq mm1, mm0
		movq mm2, mm0
		psrlq mm1, 8
		movq mm3, g_bfmeTailMask
		pand mm3, mm1
		psllq mm3, 8
		por mm1, mm3
		movq mm3, mm1
		movd dword ptr [edi], mm0
		punpcklbw mm0, mm7
		punpcklbw mm1, mm7
		pmullw mm0, mm5
		pmullw mm1, mm6
		punpckhbw mm2, mm7
		movd dword ptr [edi+5], mm2
		pmullw mm2, mm5
		punpckhbw mm3, mm7
		pmullw mm3, mm6
		paddw mm0, mm1
		paddw mm0, mm4
		psrlw mm0, 8
		packuswb mm0, mm7
		movd dword ptr [edi+1], mm0
		paddw mm2, mm3
		paddw mm2, mm4
		psrlw mm2, 8
		packuswb mm2, mm7
		movd dword ptr [edi+6], mm2
	}
}
