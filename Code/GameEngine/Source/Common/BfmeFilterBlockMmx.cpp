// cl: /DNDEBUG /MD /O2
//
// Open-BFME5: two-pass MMX interpolation filter over a 2x4 pixel block --
// vertical differences for four source rows are staged into a scratch
// buffer, then combined per-column and written back as words.  Sibling of
// bfmeFilterPairMmx (same clamp/limit shape, applied across a block rather
// than a single row pair).  Retail 0x009C2970, 551 bytes.

void __cdecl bfmeFilterBlockMmx(void *, void *row, int stride, void *work)
{
	__asm
	{
		mov eax, work
		mov edx, stride
		mov ebx, row
		mov ecx, stride
		movd mm0, dword ptr [ebx - 2]
		movd mm4, dword ptr [ebx + 2]
		psrld mm0, 10h
		movd mm1, dword ptr [ebx + ecx - 2]
		punpcklwd mm0, mm4
		movd mm4, dword ptr [ebx + ecx + 2]
		psrld mm1, 10h
		punpcklwd mm1, mm4
		lea edx, [edx + edx * 2]
		movd mm2, dword ptr [ebx + ecx * 2 - 2]
		punpcklbw mm0, mm1
		movd mm4, dword ptr [ebx + ecx * 2 + 2]
		psrld mm2, 10h
		movd mm1, dword ptr [ebx + edx - 2]
		punpcklwd mm2, mm4
		movd mm4, dword ptr [ebx + edx + 2]
		psrld mm1, 10h
		punpcklwd mm1, mm4
		pxor mm4, mm4
		punpcklbw mm2, mm1
		movq mm1, mm0
		punpcklwd mm0, mm2
		lea ebx, [ebx + ecx * 4]
		punpckhwd mm1, mm2
		movq mm6, mm0
		movq qword ptr [eax + 18h], mm0
		movq mm2, mm1
		movq qword ptr [eax + 20h], mm1
		psrlq mm0, 20h
		movd mm7, dword ptr [ebx - 2]
		punpcklbw mm1, mm4
		movd mm4, dword ptr [ebx + 2]
		psrld mm7, 10h
		movd mm5, dword ptr [ebx + ecx - 2]
		punpcklwd mm7, mm4
		movd mm4, dword ptr [ebx + ecx + 2]
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
		paddw mm1, qword ptr [eax + 10h]
		psubw mm6, mm2
		movd mm2, dword ptr [ebx + ecx * 2 - 2]
		paddw mm6, mm1
		movd mm4, dword ptr [ebx + ecx * 2 + 2]
		psrld mm2, 10h
		movd mm5, dword ptr [ebx + edx - 2]
		punpcklwd mm2, mm4
		movd mm4, dword ptr [ebx + edx + 2]
		psrld mm5, 10h
		mov ebx, row
		punpcklwd mm5, mm4
		psraw mm6, 3
		pxor mm4, mm4
		punpcklbw mm2, mm5
		movq mm5, mm7
		movq mm1, mm6
		punpckhwd mm5, mm2
		movq qword ptr [eax + 30h], mm5
		punpcklwd mm7, mm2
		movq qword ptr [eax + 28h], mm7
		psraw mm6, 0fh
		movq mm2, qword ptr [eax]
		movq mm0, mm7
		psrlq mm7, 20h
		pxor mm1, mm6
		psubsw mm1, mm6
		punpcklbw mm5, mm4
		por mm6, qword ptr [eax + 8]
		movq mm3, mm2
		punpcklbw mm7, mm4
		psubw mm3, mm1
		movq mm4, mm3
		psraw mm3, 0fh
		push ebp
		psubw mm5, mm7
		pxor mm4, mm3
		psubsw mm4, mm3
		pxor mm3, mm3
		movq mm1, qword ptr [eax + 34h]
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
		movd mm7, dword ptr [eax + 20h]
		psraw mm0, 3
		movd mm3, dword ptr [eax + 1ch]
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
		movd ebp, mm3
		pxor mm1, mm0
		mov word ptr [ebx + 1], bp
		psubsw mm1, mm0
		shr ebp, 10h
		movq mm5, mm2
		mov word ptr [ebx + ecx + 1], bp
		psrlq mm3, 20h
		por mm7, qword ptr [eax + 8]
		psubw mm5, mm1
		movd ebp, mm3
		movq mm4, mm5
		mov word ptr [ebx + ecx * 2 + 1], bp
		psraw mm5, 0fh
		shr ebp, 10h
		pxor mm4, mm5
		mov word ptr [ebx + edx + 1], bp
		psubsw mm4, mm5
		movd mm5, dword ptr [eax + 30h]
		psubusw mm2, mm4
		pmullw mm2, mm7
		pxor mm6, mm6
		movd mm3, dword ptr [eax + 2ch]
		punpcklbw mm5, mm6
		lea ebx, [ebx + ecx * 4]
		punpcklbw mm3, mm6
		paddw mm3, mm2
		psubw mm5, mm2
		packuswb mm3, mm3
		pop ebp
		packuswb mm5, mm5
		punpcklbw mm3, mm5
		movd eax, mm3
		psrlq mm3, 20h
		mov word ptr [ebx + 1], ax
		shr eax, 10h
		mov word ptr [ebx + ecx + 1], ax
		movd eax, mm3
		mov word ptr [ebx + ecx * 2 + 1], ax
		shr eax, 10h
		mov word ptr [ebx + edx + 1], ax
	}
}
