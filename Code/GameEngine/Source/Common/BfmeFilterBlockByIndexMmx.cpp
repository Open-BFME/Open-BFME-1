// cl: /DNDEBUG /MD /O2
//
// Open-BFME5: same MMX block filter as bfmeFilterBlockMmx, but self
// contained -- looks the coefficient qword up from the retail strength
// table (Rva009C0D10Table, 8 bytes/entry) by index instead of taking a
// caller-supplied work buffer, and keeps the 1/4 constant vectors plus the
// scratch accumulator on the stack.  Retail 0x009C0D50, 622 bytes.

extern unsigned short Rva009C0D10Table[];		// retail 0x013566C0

void __cdecl bfmeFilterBlockByIndexMmx(int index, void *row, int stride)
{
	const unsigned short *coef = Rva009C0D10Table + index * 4;
	__declspec(align(16)) unsigned short four[4] = { 4, 4, 4, 4 };
	__declspec(align(16)) unsigned short one[4] = { 1, 1, 1, 1 };
	__declspec(align(16)) unsigned short work[16];

	__asm
	{
		mov eax, coef
		mov edx, stride
		mov esi, row
		lea edi, work
		mov ecx, edx
		movd mm0, dword ptr [esi - 4]
		movd mm4, dword ptr [esi]
		psrld mm0, 10h
		movd mm1, dword ptr [esi + ecx - 4]
		punpcklwd mm0, mm4
		movd mm4, dword ptr [esi + ecx]
		psrld mm1, 10h
		punpcklwd mm1, mm4
		lea edx, [edx + edx * 2]
		movd mm2, dword ptr [esi + ecx * 2 - 4]
		punpcklbw mm0, mm1
		movd mm4, dword ptr [esi + ecx * 2]
		psrld mm2, 10h
		movd mm1, dword ptr [esi + edx - 4]
		punpcklwd mm2, mm4
		movd mm4, dword ptr [esi + edx]
		psrld mm1, 10h
		punpcklwd mm1, mm4
		pxor mm4, mm4
		punpcklbw mm2, mm1
		movq mm1, mm0
		punpcklwd mm0, mm2
		lea esi, [esi + ecx * 4]
		punpckhwd mm1, mm2
		movq mm6, mm0
		movq qword ptr [edi], mm0
		movq mm2, mm1
		movq qword ptr [edi + 8], mm1
		psrlq mm0, 20h
		movd mm7, dword ptr [esi - 4]
		punpcklbw mm1, mm4
		movd mm4, dword ptr [esi]
		psrld mm7, 10h
		movd mm5, dword ptr [esi + ecx - 4]
		punpcklwd mm7, mm4
		movd mm4, dword ptr [esi + ecx]
		psrld mm5, 10h
		punpcklwd mm5, mm4
		pxor mm4, mm4
		punpcklbw mm0, mm4
		psrlq mm2, 20h
		psubw mm1, mm0
		punpcklbw mm7, mm5
		movq mm3, mm1
		punpcklbw mm6, mm4
		paddw mm3, mm1
		punpcklbw mm2, mm4
		paddw mm1, mm3
		paddw mm1, qword ptr four
		psubw mm6, mm2
		movd mm2, dword ptr [esi + ecx * 2 - 4]
		paddw mm6, mm1
		movd mm4, dword ptr [esi + ecx * 2]
		psrld mm2, 10h
		movd mm5, dword ptr [esi + edx - 4]
		punpcklwd mm2, mm4
		movd mm4, dword ptr [esi + edx]
		psrld mm5, 10h
		mov esi, row
		punpcklwd mm5, mm4
		psraw mm6, 3
		pxor mm4, mm4
		punpcklbw mm2, mm5
		movq mm5, mm7
		movq mm1, mm6
		punpckhwd mm5, mm2
		movq qword ptr [edi + 18h], mm5
		punpcklwd mm7, mm2
		movq qword ptr [edi + 10h], mm7
		psraw mm6, 0fh
		movq mm2, qword ptr [eax]
		movq mm0, mm7
		psrlq mm7, 20h
		pxor mm1, mm6
		psubsw mm1, mm6
		punpcklbw mm5, mm4
		por mm6, qword ptr one
		movq mm3, mm2
		punpcklbw mm7, mm4
		psubw mm3, mm1
		movq mm4, mm3
		psraw mm3, 0fh
		psubw mm5, mm7
		pxor mm4, mm3
		psubsw mm4, mm3
		pxor mm3, mm3
		movd mm1, dword ptr [edi + 1ch]
		psubusw mm2, mm4
		punpcklbw mm0, mm3
		movq mm7, mm5
		paddw mm7, mm5
		pmullw mm2, mm6
		punpcklbw mm1, mm3
		paddw mm5, mm7
		paddw mm5, qword ptr four
		psubw mm0, mm1
		paddw mm0, mm5
		pxor mm6, mm6
		movd mm7, dword ptr [edi + 8]
		psraw mm0, 3
		movd mm3, dword ptr [edi + 4]
		punpcklbw mm7, mm6
		psubw mm7, mm2
		punpcklbw mm3, mm6
		paddw mm3, mm2
		packuswb mm7, mm7
		packuswb mm3, mm3
		movq mm1, mm0
		movq mm2, qword ptr [eax]
		psraw mm0, 0fh
		punpcklbw mm3, mm7
		movq mm7, mm0
		movd eax, mm3
		pxor mm1, mm0
		mov word ptr [esi - 1], ax
		psubsw mm1, mm0
		shr eax, 10h
		movq mm5, mm2
		mov word ptr [esi + ecx - 1], ax
		psrlq mm3, 20h
		por mm7, qword ptr one
		psubw mm5, mm1
		movd eax, mm3
		movq mm4, mm5
		mov word ptr [esi + ecx * 2 - 1], ax
		psraw mm5, 0fh
		shr eax, 10h
		pxor mm4, mm5
		mov word ptr [esi + edx - 1], ax
		psubsw mm4, mm5
		movd mm5, dword ptr [edi + 18h]
		psubusw mm2, mm4
		pmullw mm2, mm7
		pxor mm6, mm6
		movd mm3, dword ptr [edi + 14h]
		punpcklbw mm5, mm6
		lea esi, [esi + ecx * 4]
		punpcklbw mm3, mm6
		paddw mm3, mm2
		psubw mm5, mm2
		packuswb mm3, mm3
		packuswb mm5, mm5
		punpcklbw mm3, mm5
		movd eax, mm3
		psrlq mm3, 20h
		mov word ptr [esi - 1], ax
		shr eax, 10h
		mov word ptr [esi + ecx - 1], ax
		movd eax, mm3
		mov word ptr [esi + ecx * 2 - 1], ax
		shr eax, 10h
		mov word ptr [esi + edx - 1], ax
	}
}
