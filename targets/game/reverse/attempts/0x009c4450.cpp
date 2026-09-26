// ?d_009c4450@@YAXXZ
// partial score=0.9942 date=2026-09-22
// Rva009C4450: retail 0x009C4450..0x009C485A (1034 bytes), hand-written MMX body.
// Retail saves edx, ecx, ebx in that order with no compiler frame; the
// compiler saves ebx itself ahead of the __asm block, so this body
// differs from retail only in the order of the three entry pushes and
// the three exit pops (see build/gap_009c2cdd/GAP.md).
extern "C" short Rva01356640Table[];

void __cdecl Rva009C4450(const short *coeffs, const short *quant, short *out)
{
	__asm
	{
		push edx
		push ecx
		mov eax, dword ptr [esp + 0x10]
		mov edx, dword ptr [esp + 0x18]
		mov ecx, dword ptr [edx]
		mov ebx, dword ptr [edx + 0x1c]
		mov ecx, dword ptr [edx + 0x38]
		mov ebx, dword ptr [edx + 0x54]
		mov ecx, dword ptr [edx + 0x70]
		mov ebx, dword ptr [edx + 0x7c]
		mov ebx, dword ptr [esp + 0x14]
		lea ecx, Rva01356640Table
		movq mm0, qword ptr [eax]
		pmullw mm0, qword ptr [ebx]
		movq mm1, qword ptr [eax + 0x10]
		pmullw mm1, qword ptr [ebx + 0x10]
		movq mm2, qword ptr [eax + 0x20]
		pmullw mm2, qword ptr [ebx + 0x20]
		movq mm3, qword ptr [eax + 0x30]
		pmullw mm3, qword ptr [ebx + 0x30]
		movq qword ptr [edx], mm0
		pxor mm5, mm5
		movq qword ptr [edx + 8], mm5
		movq qword ptr [edx + 0x10], mm1
		movq qword ptr [edx + 0x18], mm5
		movq qword ptr [edx + 0x20], mm2
		movq qword ptr [edx + 0x28], mm5
		movq qword ptr [edx + 0x30], mm3
		movq qword ptr [edx + 0x38], mm5
		movq qword ptr [edx + 0x40], mm5
		movq qword ptr [edx + 0x48], mm5
		movq qword ptr [edx + 0x50], mm5
		movq qword ptr [edx + 0x58], mm5
		movq qword ptr [edx + 0x60], mm5
		movq qword ptr [edx + 0x68], mm5
		movq qword ptr [edx + 0x70], mm5
		movq qword ptr [edx + 0x78], mm5
		movq mm2, qword ptr [edx + 0x30]
		nop 
		movq mm6, qword ptr [ecx + 0x30]
		movq mm4, mm2
		movq mm1, qword ptr [ecx + 0x40]
		pmulhw mm4, mm6
		movq mm3, qword ptr [edx + 0x10]
		pmulhw mm1, mm2
		movq mm0, qword ptr [ecx + 0x20]
		paddw mm4, mm2
		pxor mm6, mm6
		paddw mm2, mm1
		movq mm5, qword ptr [edx + 0x20]
		pmulhw mm0, mm3
		movq mm1, mm5
		paddw mm0, mm3
		pmulhw mm3, qword ptr [ecx + 0x50]
		psubsw mm6, mm2
		pmulhw mm5, qword ptr [ecx + 0x28]
		psubsw mm0, mm4
		movq mm7, qword ptr [edx + 0x20]
		paddsw mm4, mm4
		paddw mm7, mm5
		paddsw mm4, mm0
		pmulhw mm1, qword ptr [ecx + 0x48]
		psubsw mm3, mm6
		movq qword ptr [edx + 0x10], mm4
		paddsw mm6, mm6
		movq mm4, qword ptr [ecx + 0x38]
		paddsw mm6, mm3
		movq mm5, mm3
		pmulhw mm3, mm4
		movq qword ptr [edx + 0x20], mm6
		movq mm2, mm0
		movq mm6, qword ptr [edx]
		pmulhw mm0, mm4
		paddw mm5, mm3
		paddw mm2, mm0
		psubsw mm5, mm1
		pmulhw mm6, mm4
		paddw mm6, qword ptr [edx]
		paddsw mm1, mm1
		movq mm4, mm6
		paddsw mm1, mm5
		psubsw mm6, mm2
		paddsw mm2, mm2
		movq mm0, qword ptr [edx + 0x10]
		paddsw mm2, mm6
		psubsw mm2, mm1
		nop 
		movq mm3, qword ptr [edx + 0x20]
		psubsw mm4, mm7
		paddsw mm1, mm1
		paddsw mm7, mm7
		paddsw mm1, mm2
		paddsw mm7, mm4
		psubsw mm4, mm3
		paddsw mm3, mm3
		psubsw mm6, mm5
		paddsw mm5, mm5
		paddsw mm3, mm4
		paddsw mm5, mm6
		psubsw mm7, mm0
		paddsw mm0, mm0
		movq qword ptr [edx + 0x10], mm1
		paddsw mm0, mm7
		movq mm1, mm4
		punpcklwd mm4, mm5
		movq qword ptr [edx], mm0
		punpckhwd mm1, mm5
		movq mm0, mm6
		punpcklwd mm6, mm7
		movq mm5, mm4
		punpckldq mm4, mm6
		punpckhdq mm5, mm6
		movq mm6, mm1
		movq qword ptr [edx + 8], mm4
		punpckhwd mm0, mm7
		movq qword ptr [edx + 0x18], mm5
		punpckhdq mm6, mm0
		movq mm4, qword ptr [edx]
		punpckldq mm1, mm0
		movq mm5, qword ptr [edx + 0x10]
		movq mm0, mm4
		movq qword ptr [edx + 0x38], mm6
		punpcklwd mm0, mm5
		movq qword ptr [edx + 0x28], mm1
		punpckhwd mm4, mm5
		movq mm5, mm2
		punpcklwd mm2, mm3
		movq mm1, mm0
		punpckldq mm0, mm2
		punpckhdq mm1, mm2
		movq mm2, mm4
		movq qword ptr [edx], mm0
		punpckhwd mm5, mm3
		movq qword ptr [edx + 0x10], mm1
		punpckhdq mm4, mm5
		punpckldq mm2, mm5
		movq qword ptr [edx + 0x30], mm4
		movq qword ptr [edx + 0x20], mm2
		movq mm2, qword ptr [edx + 0x30]
		nop 
		movq mm6, qword ptr [ecx + 0x30]
		movq mm4, mm2
		movq mm1, qword ptr [ecx + 0x40]
		pmulhw mm4, mm6
		movq mm3, qword ptr [edx + 0x10]
		pmulhw mm1, mm2
		movq mm0, qword ptr [ecx + 0x20]
		paddw mm4, mm2
		pxor mm6, mm6
		paddw mm2, mm1
		movq mm5, qword ptr [edx + 0x20]
		pmulhw mm0, mm3
		movq mm1, mm5
		paddw mm0, mm3
		pmulhw mm3, qword ptr [ecx + 0x50]
		psubsw mm6, mm2
		pmulhw mm5, qword ptr [ecx + 0x28]
		psubsw mm0, mm4
		movq mm7, qword ptr [edx + 0x20]
		paddsw mm4, mm4
		paddw mm7, mm5
		paddsw mm4, mm0
		pmulhw mm1, qword ptr [ecx + 0x48]
		psubsw mm3, mm6
		movq qword ptr [edx + 0x10], mm4
		paddsw mm6, mm6
		movq mm4, qword ptr [ecx + 0x38]
		paddsw mm6, mm3
		movq mm5, mm3
		pmulhw mm3, mm4
		movq qword ptr [edx + 0x20], mm6
		movq mm2, mm0
		movq mm6, qword ptr [edx]
		pmulhw mm0, mm4
		paddw mm5, mm3
		paddw mm2, mm0
		psubsw mm5, mm1
		pmulhw mm6, mm4
		paddw mm6, qword ptr [edx]
		paddsw mm1, mm1
		movq mm4, mm6
		paddsw mm1, mm5
		psubsw mm6, mm2
		paddsw mm2, mm2
		movq mm0, qword ptr [edx + 0x10]
		paddsw mm2, mm6
		psubsw mm2, mm1
		nop 
		paddsw mm2, qword ptr [ecx + 0x58]
		paddsw mm1, mm1
		paddsw mm1, mm2
		psraw mm2, 4
		psubsw mm4, mm7
		psraw mm1, 4
		movq mm3, qword ptr [edx + 0x20]
		paddsw mm7, mm7
		movq qword ptr [edx + 0x20], mm2
		paddsw mm7, mm4
		movq qword ptr [edx + 0x10], mm1
		psubsw mm4, mm3
		paddsw mm4, qword ptr [ecx + 0x58]
		paddsw mm3, mm3
		paddsw mm3, mm4
		psraw mm4, 4
		psubsw mm6, mm5
		psraw mm3, 4
		paddsw mm6, qword ptr [ecx + 0x58]
		paddsw mm5, mm5
		paddsw mm5, mm6
		psraw mm6, 4
		movq qword ptr [edx + 0x40], mm4
		psraw mm5, 4
		movq qword ptr [edx + 0x30], mm3
		psubsw mm7, mm0
		paddsw mm7, qword ptr [ecx + 0x58]
		paddsw mm0, mm0
		paddsw mm0, mm7
		psraw mm7, 4
		movq qword ptr [edx + 0x60], mm6
		psraw mm0, 4
		movq qword ptr [edx + 0x50], mm5
		movq qword ptr [edx + 0x70], mm7
		movq qword ptr [edx], mm0
		movq mm2, qword ptr [edx + 0x38]
		nop 
		movq mm6, qword ptr [ecx + 0x30]
		movq mm4, mm2
		movq mm1, qword ptr [ecx + 0x40]
		pmulhw mm4, mm6
		movq mm3, qword ptr [edx + 0x18]
		pmulhw mm1, mm2
		movq mm0, qword ptr [ecx + 0x20]
		paddw mm4, mm2
		pxor mm6, mm6
		paddw mm2, mm1
		movq mm5, qword ptr [edx + 0x28]
		pmulhw mm0, mm3
		movq mm1, mm5
		paddw mm0, mm3
		pmulhw mm3, qword ptr [ecx + 0x50]
		psubsw mm6, mm2
		pmulhw mm5, qword ptr [ecx + 0x28]
		psubsw mm0, mm4
		movq mm7, qword ptr [edx + 0x28]
		paddsw mm4, mm4
		paddw mm7, mm5
		paddsw mm4, mm0
		pmulhw mm1, qword ptr [ecx + 0x48]
		psubsw mm3, mm6
		movq qword ptr [edx + 0x18], mm4
		paddsw mm6, mm6
		movq mm4, qword ptr [ecx + 0x38]
		paddsw mm6, mm3
		movq mm5, mm3
		pmulhw mm3, mm4
		movq qword ptr [edx + 0x28], mm6
		movq mm2, mm0
		movq mm6, qword ptr [edx + 8]
		pmulhw mm0, mm4
		paddw mm5, mm3
		paddw mm2, mm0
		psubsw mm5, mm1
		pmulhw mm6, mm4
		paddw mm6, qword ptr [edx + 8]
		paddsw mm1, mm1
		movq mm4, mm6
		paddsw mm1, mm5
		psubsw mm6, mm2
		paddsw mm2, mm2
		movq mm0, qword ptr [edx + 0x18]
		paddsw mm2, mm6
		psubsw mm2, mm1
		nop 
		paddsw mm2, qword ptr [ecx + 0x58]
		paddsw mm1, mm1
		paddsw mm1, mm2
		psraw mm2, 4
		psubsw mm4, mm7
		psraw mm1, 4
		movq mm3, qword ptr [edx + 0x28]
		paddsw mm7, mm7
		movq qword ptr [edx + 0x28], mm2
		paddsw mm7, mm4
		movq qword ptr [edx + 0x18], mm1
		psubsw mm4, mm3
		paddsw mm4, qword ptr [ecx + 0x58]
		paddsw mm3, mm3
		paddsw mm3, mm4
		psraw mm4, 4
		psubsw mm6, mm5
		psraw mm3, 4
		paddsw mm6, qword ptr [ecx + 0x58]
		paddsw mm5, mm5
		paddsw mm5, mm6
		psraw mm6, 4
		movq qword ptr [edx + 0x48], mm4
		psraw mm5, 4
		movq qword ptr [edx + 0x38], mm3
		psubsw mm7, mm0
		paddsw mm7, qword ptr [ecx + 0x58]
		paddsw mm0, mm0
		paddsw mm0, mm7
		psraw mm7, 4
		movq qword ptr [edx + 0x68], mm6
		psraw mm0, 4
		movq qword ptr [edx + 0x58], mm5
		movq qword ptr [edx + 0x78], mm7
		movq qword ptr [edx + 8], mm0
		pop ecx
		pop edx
	}
}
