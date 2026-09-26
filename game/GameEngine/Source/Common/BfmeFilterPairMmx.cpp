// MSVC 7.1 cannot reproduce this packed-word filter from scalar C++.
void __cdecl bfmeFilterPairMmx(void *, void *row, int stride, const void *filter)
{
	int backward = -stride;

	__asm
	{
		mov eax, filter
		mov ebx, row
		mov ecx, backward
		movd mm1, dword ptr [ebx]
		pxor mm4, mm4
		movd mm0, dword ptr [ebx + ecx]
		punpcklbw mm1, mm4
		mov edx, stride
		punpcklbw mm0, mm4
		movd mm6, dword ptr [ebx + ecx * 2]
		psubw mm1, mm0
		movq mm2, qword ptr [ebx + edx]
		movq mm3, mm1
		punpcklbw mm6, mm4
		paddw mm3, mm1
		punpcklbw mm2, mm4
		paddw mm1, mm3
		paddw mm1, qword ptr [eax + 10h]
		psubw mm6, mm2
		movq mm2, qword ptr [eax]
		paddw mm6, mm1
		movd mm5, dword ptr [ebx + 4]
		psraw mm6, 3
		movq mm1, mm6
		psraw mm6, 0fh
		movd mm7, dword ptr [ebx + ecx + 4]
		pxor mm1, mm6
		psubsw mm1, mm6
		pxor mm0, mm0
		punpcklbw mm5, mm0
		movq mm3, mm2
		por mm6, qword ptr [eax + 8]
		punpcklbw mm7, mm0
		psubw mm3, mm1
		psubw mm5, mm7
		movq mm4, mm3
		psraw mm3, 0fh
		movd mm0, dword ptr [ebx + ecx * 2 + 4]
		pxor mm4, mm3
		movd mm1, dword ptr [ebx + edx + 4]
		psubsw mm4, mm3
		pxor mm3, mm3
		psubusw mm2, mm4
		punpcklbw mm0, mm3
		movq mm7, mm5
		paddw mm7, mm5
		pmullw mm2, mm6
		punpcklbw mm1, mm3
		paddw mm5, mm7
		paddw mm5, qword ptr [eax + 10h]
		psubw mm0, mm1
		paddw mm0, mm5
		pxor mm6, mm6
		movd mm7, dword ptr [ebx]
		psraw mm0, 3
		movd mm3, dword ptr [ebx + ecx]
		punpcklbw mm7, mm6
		psubw mm7, mm2
		punpcklbw mm3, mm6
		paddw mm3, mm2
		packuswb mm7, mm7
		packuswb mm3, mm3
		movq mm1, mm0
		movd dword ptr [ebx], mm7
		psraw mm0, 0fh
		movq mm7, mm0
		pxor mm1, mm0
		movq mm2, qword ptr [eax]
		psubsw mm1, mm0
		movq mm5, mm2
		por mm7, qword ptr [eax + 8]
		psubw mm5, mm1
		movq mm4, mm5
		psraw mm5, 0fh
		movd dword ptr [ebx + ecx], mm3
		pxor mm4, mm5
		psubsw mm4, mm5
		pxor mm6, mm6
		movd mm5, dword ptr [ebx + 4]
		psubusw mm2, mm4
		movd mm3, dword ptr [ebx + ecx + 4]
		pmullw mm2, mm7
		punpcklbw mm5, mm6
		punpcklbw mm3, mm6
		paddw mm3, mm2
		psubw mm5, mm2
		packuswb mm3, mm3
		packuswb mm5, mm5
		movd dword ptr [ebx + ecx + 4], mm3
		movd dword ptr [ebx + 4], mm5
	}
}
