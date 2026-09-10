// cl: /DNDEBUG /MD /O2
//
// Open-BFME5: vertical-edge sibling of bfmeFilterBlockByIndexMmx -- same
// strength-table lookup and 1/4 constant vectors, but filters across rows
// (taps at row-stride, row, row+stride, row+stride*2) instead of columns,
// writing two output rows over an 8-pixel-wide strip (two four-pixel
// groups). No scratch accumulator: retail keeps only esi live across the
// asm block.  Retail 0x009C0FC0, 352 bytes.

extern unsigned short Rva009C0D10Table[];		// retail 0x013566C0

void __cdecl bfmeFilterRowByIndex8Mmx(int index, void *row, int stride)
{
	const unsigned short *coef = Rva009C0D10Table + index * 4;
	__declspec(align(16)) unsigned short four[4] = { 4, 4, 4, 4 };
	__declspec(align(16)) unsigned short one[4] = { 1, 1, 1, 1 };

	__asm
	{
		mov eax, coef
		mov edx, stride
		xor ecx, ecx
		sub ecx, edx
		mov esi, row
		movd mm0, dword ptr [esi]
		pxor mm7, mm7
		movd mm1, dword ptr [esi + ecx]
		punpcklbw mm0, mm7
		movd mm2, dword ptr [esi + edx]
		punpcklbw mm1, mm7
		movd mm3, dword ptr [esi + ecx*2]
		movq mm5, mm0
		movq mm6, mm1
		psubw mm0, mm1
		punpcklbw mm2, mm7
		movq mm1, mm0
		punpcklbw mm3, mm7
		paddw mm0, mm1
		psubw mm3, mm2
		paddw mm1, mm0
		paddw mm3, mm1
		paddw mm3, qword ptr four
		movq mm0, qword ptr [eax]
		psraw mm3, 3
		movq mm1, mm3
		psraw mm3, 0Fh
		pxor mm1, mm3
		psubsw mm1, mm3
		por mm3, qword ptr one
		movq mm2, mm0
		psubw mm0, mm1
		movq mm4, mm0
		psraw mm0, 0Fh
		pxor mm4, mm0
		psubsw mm4, mm0
		psubusw mm2, mm4
		pmullw mm2, mm3
		psubw mm5, mm2
		paddw mm6, mm2
		packuswb mm5, mm5
		packuswb mm6, mm6
		movd dword ptr [esi], mm5
		movd dword ptr [esi + ecx], mm6
		movd mm0, dword ptr [esi + 4]
		movd mm1, dword ptr [esi + ecx + 4]
		punpcklbw mm0, mm7
		movd mm2, dword ptr [esi + edx + 4]
		punpcklbw mm1, mm7
		movd mm3, dword ptr [esi + ecx*2 + 4]
		movq mm5, mm0
		movq mm6, mm1
		psubw mm0, mm1
		punpcklbw mm2, mm7
		movq mm1, mm0
		punpcklbw mm3, mm7
		paddw mm0, mm1
		psubw mm3, mm2
		paddw mm1, mm0
		paddw mm3, mm1
		paddw mm3, qword ptr four
		movq mm0, qword ptr [eax]
		psraw mm3, 3
		movq mm1, mm3
		psraw mm3, 0Fh
		pxor mm1, mm3
		psubsw mm1, mm3
		por mm3, qword ptr one
		movq mm2, mm0
		psubw mm0, mm1
		movq mm4, mm0
		psraw mm0, 0Fh
		pxor mm4, mm0
		psubsw mm4, mm0
		psubusw mm2, mm4
		pmullw mm2, mm3
		psubw mm5, mm2
		paddw mm6, mm2
		packuswb mm5, mm5
		packuswb mm6, mm6
		movd dword ptr [esi + 4], mm5
		movd dword ptr [esi + ecx + 4], mm6
	}
}
