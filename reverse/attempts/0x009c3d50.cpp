// ?d_009c3d50@@YAXXZ
// partial score=0.9966 date=2026-09-22
// Rva009C3D50: retail 0x009C3D50..0x009C4441 (1777 bytes), hand-written MMX body.
// Retail saves edx, ecx, ebx in that order with no compiler frame; the
// compiler saves ebx itself ahead of the __asm block, so this body
// differs from retail only in the order of the three entry pushes and
// the three exit pops (see build/gap_009c2cdd/GAP.md).
extern "C" short Rva01356640Table[];

void __cdecl Rva009C3D50(const short *coeffs, const short *quant, short *out)
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
		movq mm1, qword ptr [eax + 8]
		pmullw mm1, qword ptr [ebx + 8]
		movq mm2, qword ptr [eax + 0x10]
		pmullw mm2, qword ptr [ebx + 0x10]
		movq mm3, qword ptr [eax + 0x18]
		pmullw mm3, qword ptr [ebx + 0x18]
		movq mm4, qword ptr [eax + 0x20]
		pmullw mm4, qword ptr [ebx + 0x20]
		movq mm5, qword ptr [eax + 0x28]
		pmullw mm5, qword ptr [ebx + 0x28]
		movq mm6, qword ptr [eax + 0x30]
		pmullw mm6, qword ptr [ebx + 0x30]
		movq mm7, qword ptr [eax + 0x38]
		pmullw mm7, qword ptr [ebx + 0x38]
		movq qword ptr [edx], mm0
		movq qword ptr [edx + 8], mm1
		movq qword ptr [edx + 0x10], mm2
		movq qword ptr [edx + 0x18], mm3
		movq qword ptr [edx + 0x20], mm4
		movq qword ptr [edx + 0x28], mm5
		movq qword ptr [edx + 0x30], mm6
		movq qword ptr [edx + 0x38], mm7
		movq mm0, qword ptr [eax + 0x40]
		pmullw mm0, qword ptr [ebx + 0x40]
		movq mm1, qword ptr [eax + 0x48]
		pmullw mm1, qword ptr [ebx + 0x48]
		movq mm2, qword ptr [eax + 0x50]
		pmullw mm2, qword ptr [ebx + 0x50]
		movq mm3, qword ptr [eax + 0x58]
		pmullw mm3, qword ptr [ebx + 0x58]
		movq mm4, qword ptr [eax + 0x60]
		pmullw mm4, qword ptr [ebx + 0x60]
		movq mm5, qword ptr [eax + 0x68]
		pmullw mm5, qword ptr [ebx + 0x68]
		movq mm6, qword ptr [eax + 0x70]
		pmullw mm6, qword ptr [ebx + 0x70]
		movq mm7, qword ptr [eax + 0x78]
		pmullw mm7, qword ptr [ebx + 0x78]
		movq qword ptr [edx + 0x40], mm0
		movq qword ptr [edx + 0x48], mm1
		movq qword ptr [edx + 0x50], mm2
		movq qword ptr [edx + 0x58], mm3
		movq qword ptr [edx + 0x60], mm4
		movq qword ptr [edx + 0x68], mm5
		movq qword ptr [edx + 0x70], mm6
		movq qword ptr [edx + 0x78], mm7
		movq mm2, qword ptr [edx + 0x30]
		movq mm6, qword ptr [ecx + 0x30]
		movq mm4, mm2
		movq mm7, qword ptr [edx + 0x18]
		pmulhw mm4, mm6
		movq mm1, qword ptr [ecx + 0x40]
		pmulhw mm6, mm7
		movq mm5, mm1
		pmulhw mm1, mm2
		movq mm3, qword ptr [edx + 0x10]
		pmulhw mm5, mm7
		movq mm0, qword ptr [ecx + 0x20]
		paddw mm4, mm2
		paddw mm6, mm7
		paddw mm2, mm1
		movq mm1, qword ptr [edx + 0x38]
		paddw mm7, mm5
		movq mm5, mm0
		pmulhw mm0, mm3
		paddsw mm4, mm7
		pmulhw mm5, mm1
		movq mm7, qword ptr [ecx + 0x50]
		psubsw mm6, mm2
		paddw mm0, mm3
		pmulhw mm3, mm7
		movq mm2, qword ptr [edx + 0x20]
		pmulhw mm7, mm1
		paddw mm5, mm1
		movq mm1, mm2
		pmulhw mm2, qword ptr [ecx + 0x28]
		psubsw mm3, mm5
		movq mm5, qword ptr [edx + 0x28]
		paddsw mm0, mm7
		movq mm7, mm5
		psubsw mm0, mm4
		pmulhw mm5, qword ptr [ecx + 0x28]
		paddw mm2, mm1
		pmulhw mm1, qword ptr [ecx + 0x48]
		paddsw mm4, mm4
		paddsw mm4, mm0
		psubsw mm3, mm6
		paddw mm5, mm7
		paddsw mm6, mm6
		pmulhw mm7, qword ptr [ecx + 0x48]
		paddsw mm6, mm3
		movq qword ptr [edx + 0x10], mm4
		psubsw mm1, mm5
		movq mm4, qword ptr [ecx + 0x38]
		movq mm5, mm3
		pmulhw mm3, mm4
		paddsw mm7, mm2
		movq qword ptr [edx + 0x20], mm6
		movq mm2, mm0
		movq mm6, qword ptr [edx]
		pmulhw mm0, mm4
		paddw mm5, mm3
		movq mm3, qword ptr [edx + 8]
		psubsw mm5, mm1
		paddw mm2, mm0
		psubsw mm6, mm3
		movq mm0, mm6
		pmulhw mm6, mm4
		paddsw mm3, mm3
		paddsw mm1, mm1
		paddsw mm3, mm0
		paddsw mm1, mm5
		pmulhw mm4, mm3
		paddsw mm6, mm0
		psubsw mm6, mm2
		paddsw mm2, mm2
		movq mm0, qword ptr [edx + 0x10]
		paddsw mm2, mm6
		paddw mm4, mm3
		psubsw mm2, mm1
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
		movq mm2, qword ptr [edx + 0x70]
		movq mm6, qword ptr [ecx + 0x30]
		movq mm4, mm2
		movq mm7, qword ptr [edx + 0x58]
		pmulhw mm4, mm6
		movq mm1, qword ptr [ecx + 0x40]
		pmulhw mm6, mm7
		movq mm5, mm1
		pmulhw mm1, mm2
		movq mm3, qword ptr [edx + 0x50]
		pmulhw mm5, mm7
		movq mm0, qword ptr [ecx + 0x20]
		paddw mm4, mm2
		paddw mm6, mm7
		paddw mm2, mm1
		movq mm1, qword ptr [edx + 0x78]
		paddw mm7, mm5
		movq mm5, mm0
		pmulhw mm0, mm3
		paddsw mm4, mm7
		pmulhw mm5, mm1
		movq mm7, qword ptr [ecx + 0x50]
		psubsw mm6, mm2
		paddw mm0, mm3
		pmulhw mm3, mm7
		movq mm2, qword ptr [edx + 0x60]
		pmulhw mm7, mm1
		paddw mm5, mm1
		movq mm1, mm2
		pmulhw mm2, qword ptr [ecx + 0x28]
		psubsw mm3, mm5
		movq mm5, qword ptr [edx + 0x68]
		paddsw mm0, mm7
		movq mm7, mm5
		psubsw mm0, mm4
		pmulhw mm5, qword ptr [ecx + 0x28]
		paddw mm2, mm1
		pmulhw mm1, qword ptr [ecx + 0x48]
		paddsw mm4, mm4
		paddsw mm4, mm0
		psubsw mm3, mm6
		paddw mm5, mm7
		paddsw mm6, mm6
		pmulhw mm7, qword ptr [ecx + 0x48]
		paddsw mm6, mm3
		movq qword ptr [edx + 0x50], mm4
		psubsw mm1, mm5
		movq mm4, qword ptr [ecx + 0x38]
		movq mm5, mm3
		pmulhw mm3, mm4
		paddsw mm7, mm2
		movq qword ptr [edx + 0x60], mm6
		movq mm2, mm0
		movq mm6, qword ptr [edx + 0x40]
		pmulhw mm0, mm4
		paddw mm5, mm3
		movq mm3, qword ptr [edx + 0x48]
		psubsw mm5, mm1
		paddw mm2, mm0
		psubsw mm6, mm3
		movq mm0, mm6
		pmulhw mm6, mm4
		paddsw mm3, mm3
		paddsw mm1, mm1
		paddsw mm3, mm0
		paddsw mm1, mm5
		pmulhw mm4, mm3
		paddsw mm6, mm0
		psubsw mm6, mm2
		paddsw mm2, mm2
		movq mm0, qword ptr [edx + 0x50]
		paddsw mm2, mm6
		paddw mm4, mm3
		psubsw mm2, mm1
		movq mm3, qword ptr [edx + 0x60]
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
		movq qword ptr [edx + 0x50], mm1
		paddsw mm0, mm7
		movq mm1, mm4
		punpcklwd mm4, mm5
		movq qword ptr [edx + 0x40], mm0
		punpckhwd mm1, mm5
		movq mm0, mm6
		punpcklwd mm6, mm7
		movq mm5, mm4
		punpckldq mm4, mm6
		punpckhdq mm5, mm6
		movq mm6, mm1
		movq qword ptr [edx + 0x48], mm4
		punpckhwd mm0, mm7
		movq qword ptr [edx + 0x58], mm5
		punpckhdq mm6, mm0
		movq mm4, qword ptr [edx + 0x40]
		punpckldq mm1, mm0
		movq mm5, qword ptr [edx + 0x50]
		movq mm0, mm4
		movq qword ptr [edx + 0x78], mm6
		punpcklwd mm0, mm5
		movq qword ptr [edx + 0x68], mm1
		punpckhwd mm4, mm5
		movq mm5, mm2
		punpcklwd mm2, mm3
		movq mm1, mm0
		punpckldq mm0, mm2
		punpckhdq mm1, mm2
		movq mm2, mm4
		movq qword ptr [edx + 0x40], mm0
		punpckhwd mm5, mm3
		movq qword ptr [edx + 0x50], mm1
		punpckhdq mm4, mm5
		punpckldq mm2, mm5
		movq qword ptr [edx + 0x70], mm4
		movq qword ptr [edx + 0x60], mm2
		movq mm2, qword ptr [edx + 0x30]
		movq mm6, qword ptr [ecx + 0x30]
		movq mm4, mm2
		movq mm7, qword ptr [edx + 0x50]
		pmulhw mm4, mm6
		movq mm1, qword ptr [ecx + 0x40]
		pmulhw mm6, mm7
		movq mm5, mm1
		pmulhw mm1, mm2
		movq mm3, qword ptr [edx + 0x10]
		pmulhw mm5, mm7
		movq mm0, qword ptr [ecx + 0x20]
		paddw mm4, mm2
		paddw mm6, mm7
		paddw mm2, mm1
		movq mm1, qword ptr [edx + 0x70]
		paddw mm7, mm5
		movq mm5, mm0
		pmulhw mm0, mm3
		paddsw mm4, mm7
		pmulhw mm5, mm1
		movq mm7, qword ptr [ecx + 0x50]
		psubsw mm6, mm2
		paddw mm0, mm3
		pmulhw mm3, mm7
		movq mm2, qword ptr [edx + 0x20]
		pmulhw mm7, mm1
		paddw mm5, mm1
		movq mm1, mm2
		pmulhw mm2, qword ptr [ecx + 0x28]
		psubsw mm3, mm5
		movq mm5, qword ptr [edx + 0x60]
		paddsw mm0, mm7
		movq mm7, mm5
		psubsw mm0, mm4
		pmulhw mm5, qword ptr [ecx + 0x28]
		paddw mm2, mm1
		pmulhw mm1, qword ptr [ecx + 0x48]
		paddsw mm4, mm4
		paddsw mm4, mm0
		psubsw mm3, mm6
		paddw mm5, mm7
		paddsw mm6, mm6
		pmulhw mm7, qword ptr [ecx + 0x48]
		paddsw mm6, mm3
		movq qword ptr [edx + 0x10], mm4
		psubsw mm1, mm5
		movq mm4, qword ptr [ecx + 0x38]
		movq mm5, mm3
		pmulhw mm3, mm4
		paddsw mm7, mm2
		movq qword ptr [edx + 0x20], mm6
		movq mm2, mm0
		movq mm6, qword ptr [edx]
		pmulhw mm0, mm4
		paddw mm5, mm3
		movq mm3, qword ptr [edx + 0x40]
		psubsw mm5, mm1
		paddw mm2, mm0
		psubsw mm6, mm3
		movq mm0, mm6
		pmulhw mm6, mm4
		paddsw mm3, mm3
		paddsw mm1, mm1
		paddsw mm3, mm0
		paddsw mm1, mm5
		pmulhw mm4, mm3
		paddsw mm6, mm0
		psubsw mm6, mm2
		paddsw mm2, mm2
		movq mm0, qword ptr [edx + 0x10]
		paddsw mm2, mm6
		paddw mm4, mm3
		psubsw mm2, mm1
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
		movq mm6, qword ptr [ecx + 0x30]
		movq mm4, mm2
		movq mm7, qword ptr [edx + 0x58]
		pmulhw mm4, mm6
		movq mm1, qword ptr [ecx + 0x40]
		pmulhw mm6, mm7
		movq mm5, mm1
		pmulhw mm1, mm2
		movq mm3, qword ptr [edx + 0x18]
		pmulhw mm5, mm7
		movq mm0, qword ptr [ecx + 0x20]
		paddw mm4, mm2
		paddw mm6, mm7
		paddw mm2, mm1
		movq mm1, qword ptr [edx + 0x78]
		paddw mm7, mm5
		movq mm5, mm0
		pmulhw mm0, mm3
		paddsw mm4, mm7
		pmulhw mm5, mm1
		movq mm7, qword ptr [ecx + 0x50]
		psubsw mm6, mm2
		paddw mm0, mm3
		pmulhw mm3, mm7
		movq mm2, qword ptr [edx + 0x28]
		pmulhw mm7, mm1
		paddw mm5, mm1
		movq mm1, mm2
		pmulhw mm2, qword ptr [ecx + 0x28]
		psubsw mm3, mm5
		movq mm5, qword ptr [edx + 0x68]
		paddsw mm0, mm7
		movq mm7, mm5
		psubsw mm0, mm4
		pmulhw mm5, qword ptr [ecx + 0x28]
		paddw mm2, mm1
		pmulhw mm1, qword ptr [ecx + 0x48]
		paddsw mm4, mm4
		paddsw mm4, mm0
		psubsw mm3, mm6
		paddw mm5, mm7
		paddsw mm6, mm6
		pmulhw mm7, qword ptr [ecx + 0x48]
		paddsw mm6, mm3
		movq qword ptr [edx + 0x18], mm4
		psubsw mm1, mm5
		movq mm4, qword ptr [ecx + 0x38]
		movq mm5, mm3
		pmulhw mm3, mm4
		paddsw mm7, mm2
		movq qword ptr [edx + 0x28], mm6
		movq mm2, mm0
		movq mm6, qword ptr [edx + 8]
		pmulhw mm0, mm4
		paddw mm5, mm3
		movq mm3, qword ptr [edx + 0x48]
		psubsw mm5, mm1
		paddw mm2, mm0
		psubsw mm6, mm3
		movq mm0, mm6
		pmulhw mm6, mm4
		paddsw mm3, mm3
		paddsw mm1, mm1
		paddsw mm3, mm0
		paddsw mm1, mm5
		pmulhw mm4, mm3
		paddsw mm6, mm0
		psubsw mm6, mm2
		paddsw mm2, mm2
		movq mm0, qword ptr [edx + 0x18]
		paddsw mm2, mm6
		paddw mm4, mm3
		psubsw mm2, mm1
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
