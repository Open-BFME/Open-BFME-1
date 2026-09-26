// 5-row sibling of bfmeInterpRowsMmx: the fourth output is interpolated from
// row 3 and row 5 instead of a straight copy.

namespace
{
	__declspec(align(8)) const unsigned short g_bfmeW51c[4] = { 51, 51, 51, 51 };
	__declspec(align(8)) const unsigned short g_bfmeW102c[4] = { 102, 102, 102, 102 };
	__declspec(align(8)) const unsigned short g_bfmeW154c[4] = { 154, 154, 154, 154 };
	__declspec(align(8)) const unsigned short g_bfmeW205c[4] = { 205, 205, 205, 205 };
	__declspec(align(8)) const unsigned short g_bfmeW128c[4] = { 128, 128, 128, 128 };
}

// ?bfmeInterpRows5Mmx@@YAXPAXHH@Z
void __cdecl bfmeInterpRows5Mmx(void *source, int stride, int bytes)
{
	__asm
	{
		mov esi, source
		mov ecx, stride
		lea edi, [esi+ecx*2]
		add edi, ecx
		pxor mm7, mm7
		mov edx, bytes
	bfmeNext:
		movq mm0, qword ptr [esi]
		movq mm1, qword ptr [esi+ecx]
		movq mm2, mm0
		punpcklbw mm0, mm7
		movq mm5, g_bfmeW51c
		punpckhbw mm2, mm7
		pmullw mm0, mm5
		movq mm3, mm1
		punpcklbw mm1, mm7
		pmullw mm2, mm5
		movq mm6, g_bfmeW205c
		movq mm4, mm1
		pmullw mm4, mm6
		punpckhbw mm3, mm7
		movq mm5, mm3
		pmullw mm5, mm6
		paddw mm0, mm4
		paddw mm2, mm5
		paddw mm0, g_bfmeW128c
		paddw mm2, g_bfmeW128c
		psrlw mm0, 8
		psrlw mm2, 8
		packuswb mm0, mm2
		movq qword ptr [esi+ecx], mm0
		movq mm0, qword ptr [esi+ecx*2]
		movq mm5, g_bfmeW102c
		movq mm2, mm0
		pmullw mm1, mm5
		movq mm6, g_bfmeW154c
		punpcklbw mm0, mm7
		pmullw mm3, mm5
		movq mm4, mm0
		punpckhbw mm2, mm7
		pmullw mm4, mm6
		movq mm5, mm2
		pmullw mm5, mm6
		paddw mm1, mm4
		paddw mm3, mm5
		paddw mm1, g_bfmeW128c
		paddw mm3, g_bfmeW128c
		psrlw mm1, 8
		psrlw mm3, 8
		packuswb mm1, mm3
		movq qword ptr [esi+ecx*2], mm1
		movq mm1, qword ptr [edi]
		pmullw mm0, mm6
		movq mm5, g_bfmeW102c
		movq mm3, mm1
		pmullw mm2, mm6
		punpcklbw mm1, mm7
		movq mm4, mm1
		punpckhbw mm3, mm7
		pmullw mm4, mm5
		movq mm6, mm3
		pmullw mm6, mm5
		paddw mm0, mm4
		paddw mm2, mm6
		paddw mm0, g_bfmeW128c
		paddw mm2, g_bfmeW128c
		psrlw mm0, 8
		psrlw mm2, 8
		packuswb mm0, mm2
		movq qword ptr [edi], mm0
		movq mm0, qword ptr [edi+ecx*2]
		movq mm5, g_bfmeW205c
		pmullw mm1, mm5
		movq mm6, g_bfmeW51c
		movq mm2, mm0
		pmullw mm3, mm5
		punpcklbw mm0, mm7
		pmullw mm0, mm6
		punpckhbw mm2, mm7
		paddw mm1, mm0
		pmullw mm2, mm6
		paddw mm3, mm2
		paddw mm1, g_bfmeW128c
		paddw mm3, g_bfmeW128c
		psrlw mm1, 8
		psrlw mm3, 8
		packuswb mm1, mm3
		movq qword ptr [edi+ecx], mm1
		add edi, 8
		add esi, 8
		sub edx, 8
		jg bfmeNext
	}
}
