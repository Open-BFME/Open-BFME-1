// ?d_009c4860@@YAXXZ
// partial score=0.9923 date=2026-09-22
// Rva009C4860: retail 0x009C4860..0x009C4B69 (777 bytes), hand-written MMX body.
// Retail saves edx, ecx, ebx in that order with no compiler frame; the
// compiler saves ebx itself ahead of the __asm block, so this body
// differs from retail only in the order of the three entry pushes and
// the three exit pops (see build/gap_009c2cdd/GAP.md).
extern "C" short Rva01356640Table[];

void __cdecl Rva009C4860(const short *coeffs, short *out)
{
	__asm
	{
		push edx
		push ecx
		mov eax, dword ptr [esp + 0x10]
		mov edx, dword ptr [esp + 0x14]
		mov ecx, dword ptr [edx]
		mov ebx, dword ptr [edx + 0x1c]
		mov ecx, dword ptr [edx + 0x38]
		mov ebx, dword ptr [edx + 0x54]
		mov ecx, dword ptr [edx + 0x70]
		mov ebx, dword ptr [edx + 0x7c]
		lea ecx, Rva01356640Table
		movq mm0, qword ptr [eax]
		pxor mm1, mm1
		movq mm2, qword ptr [ecx]
		movq mm3, mm0
		pxor mm4, mm4
		psrlq mm0, 0x10
		pand mm3, mm2
		movq mm5, mm0
		movq mm6, mm1
		pand mm5, mm2
		movq mm7, qword ptr [ecx + 0x18]
		pxor mm0, mm5
		pand mm7, mm6
		por mm0, mm3
		pxor mm6, mm7
		por mm0, mm7
		movq mm7, qword ptr [ecx + 0x18]
		movq mm3, mm4
		movq qword ptr [edx], mm0
		pand mm3, mm2
		psllq mm3, 0x10
		pand mm7, mm1
		por mm5, mm3
		por mm7, mm6
		por mm7, mm5
		psrlq mm4, 0x10
		movq qword ptr [edx + 0x10], mm7
		movq qword ptr [edx + 0x20], mm4
		movq qword ptr [edx + 0x30], mm4
		movq qword ptr [edx + 8], mm4
		movq qword ptr [edx + 0x18], mm4
		movq qword ptr [edx + 0x28], mm4
		movq qword ptr [edx + 0x38], mm4
		movq qword ptr [edx + 0x78], mm4
		movq qword ptr [edx + 0x68], mm4
		movq qword ptr [edx + 0x58], mm4
		movq qword ptr [edx + 0x48], mm4
		movq qword ptr [edx + 0x70], mm4
		movq qword ptr [edx + 0x60], mm4
		movq qword ptr [edx + 0x50], mm4
		movq qword ptr [edx + 0x40], mm4
		movq mm7, qword ptr [edx + 0x10]
		movq mm0, qword ptr [ecx + 0x20]
		movq mm3, qword ptr [ecx + 0x50]
		pmulhw mm0, mm7
		pmulhw mm3, mm7
		movq mm6, qword ptr [edx]
		movq mm4, qword ptr [ecx + 0x38]
		paddw mm0, mm7
		movq mm1, mm6
		pmulhw mm6, mm4
		movq mm2, mm0
		movq mm5, mm3
		pmulhw mm2, mm4
		pmulhw mm5, mm4
		paddw mm6, mm1
		movq mm4, mm6
		paddw mm2, mm0
		paddw mm5, mm3
		movq mm7, mm6
		movq mm1, mm5
		psubw mm6, mm2
		psubw mm4, mm3
		psubw mm7, mm0
		paddw mm2, mm2
		paddw mm3, mm3
		paddw mm0, mm0
		paddw mm2, mm6
		paddw mm3, mm4
		psubw mm2, mm1
		psubw mm6, mm5
		paddw mm1, mm1
		paddw mm5, mm5
		paddw mm0, mm7
		paddw mm1, mm2
		movq qword ptr [edx + 0x10], mm1
		paddw mm5, mm6
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
		movq mm7, qword ptr [edx + 0x10]
		movq mm0, qword ptr [ecx + 0x20]
		movq mm3, qword ptr [ecx + 0x50]
		pmulhw mm0, mm7
		pmulhw mm3, mm7
		movq mm6, qword ptr [edx]
		movq mm4, qword ptr [ecx + 0x38]
		paddw mm0, mm7
		movq mm1, mm6
		pmulhw mm6, mm4
		movq mm2, mm0
		movq mm5, mm3
		pmulhw mm2, mm4
		pmulhw mm5, mm4
		paddw mm6, mm1
		movq mm4, mm6
		paddw mm6, qword ptr [ecx + 0x58]
		paddw mm4, qword ptr [ecx + 0x58]
		paddw mm2, mm0
		paddw mm5, mm3
		movq mm7, mm6
		movq mm1, mm5
		psubw mm6, mm2
		psubw mm4, mm3
		psubw mm7, mm0
		paddw mm2, mm2
		paddw mm3, mm3
		paddw mm0, mm0
		paddw mm2, mm6
		paddw mm3, mm4
		psraw mm4, 4
		movq qword ptr [edx + 0x40], mm4
		psraw mm3, 4
		movq qword ptr [edx + 0x30], mm3
		psubw mm2, mm1
		psubw mm6, mm5
		paddw mm1, mm1
		paddw mm5, mm5
		paddw mm0, mm7
		paddw mm1, mm2
		psraw mm7, 4
		psraw mm2, 4
		psraw mm0, 4
		psraw mm1, 4
		movq qword ptr [edx + 0x70], mm7
		movq qword ptr [edx], mm0
		movq qword ptr [edx + 0x10], mm1
		movq qword ptr [edx + 0x20], mm2
		movq qword ptr [edx + 0x10], mm1
		paddw mm5, mm6
		psraw mm5, 4
		movq qword ptr [edx + 0x50], mm5
		psraw mm6, 4
		movq qword ptr [edx + 0x60], mm6
		movq mm7, qword ptr [edx + 0x18]
		movq mm0, qword ptr [ecx + 0x20]
		movq mm3, qword ptr [ecx + 0x50]
		pmulhw mm0, mm7
		pmulhw mm3, mm7
		movq mm6, qword ptr [edx + 8]
		movq mm4, qword ptr [ecx + 0x38]
		paddw mm0, mm7
		movq mm1, mm6
		pmulhw mm6, mm4
		movq mm2, mm0
		movq mm5, mm3
		pmulhw mm2, mm4
		pmulhw mm5, mm4
		paddw mm6, mm1
		movq mm4, mm6
		paddw mm6, qword ptr [ecx + 0x58]
		paddw mm4, qword ptr [ecx + 0x58]
		paddw mm2, mm0
		paddw mm5, mm3
		movq mm7, mm6
		movq mm1, mm5
		psubw mm6, mm2
		psubw mm4, mm3
		psubw mm7, mm0
		paddw mm2, mm2
		paddw mm3, mm3
		paddw mm0, mm0
		paddw mm2, mm6
		paddw mm3, mm4
		psraw mm4, 4
		movq qword ptr [edx + 0x48], mm4
		psraw mm3, 4
		movq qword ptr [edx + 0x38], mm3
		psubw mm2, mm1
		psubw mm6, mm5
		paddw mm1, mm1
		paddw mm5, mm5
		paddw mm0, mm7
		paddw mm1, mm2
		psraw mm7, 4
		psraw mm2, 4
		psraw mm0, 4
		psraw mm1, 4
		movq qword ptr [edx + 0x78], mm7
		movq qword ptr [edx + 8], mm0
		movq qword ptr [edx + 0x18], mm1
		movq qword ptr [edx + 0x28], mm2
		movq qword ptr [edx + 0x18], mm1
		paddw mm5, mm6
		psraw mm5, 4
		movq qword ptr [edx + 0x58], mm5
		psraw mm6, 4
		movq qword ptr [edx + 0x68], mm6
		pop ecx
		pop edx
	}
}
