// ?rva009C7CC0@@YAXPBX0PAX@Z
// cl: /DNDEBUG /MD /O2

// Straight-line SSE2 leaf, no calls, no branches.  Elementwise-multiplies
// two 4-row (8-word) coefficient planes, runs an 8-point butterfly against
// a 7-entry constant table to produce an 8x8 output block, transposes the
// block in place, then runs the identical butterfly a second time over the
// transposed rows (a separable two-pass transform).  Retail 0x009C7CC0,
// 1024 bytes.

extern const unsigned short kRva012D8F40[56];	// retail 0x012D8F40, 7 rows x 8 words
extern const unsigned short kRva012D8F20[8];	// retail 0x012D8F20, round constant

// ?rva009C7CC0@@YAXPBX00@Z
void __cdecl rva009C7CC0(const void *p1, const void *p2, void *p3)
{
	__asm
	{
		push ebx
		mov eax, dword ptr [esp + 0Ch]
		mov ebx, dword ptr [esp + 10h]
		mov edx, dword ptr [esp + 14h]
		lea ecx, kRva012D8F40
		movdqa xmm0, xmmword ptr [eax]
		movdqa xmm1, xmmword ptr [eax + 10h]
		pmullw xmm0, xmmword ptr [ebx]
		pmullw xmm1, xmmword ptr [ebx + 10h]
		movdqa xmm2, xmmword ptr [eax + 20h]
		movdqa xmm3, xmmword ptr [eax + 30h]
		pmullw xmm2, xmmword ptr [ebx + 20h]
		pmullw xmm3, xmmword ptr [ebx + 30h]
		movdqa xmmword ptr [edx], xmm0
		movdqa xmmword ptr [edx + 10h], xmm1
		movdqa xmmword ptr [edx + 20h], xmm2
		movdqa xmmword ptr [edx + 30h], xmm3
		movdqa xmm2, xmmword ptr [edx + 30h]
		movdqa xmm6, xmmword ptr [ecx + 20h]
		movdqa xmm4, xmm2
		pmulhw xmm4, xmm6
		movdqa xmm1, xmmword ptr [ecx + 40h]
		movdqa xmm5, xmm1
		pmulhw xmm1, xmm2
		movdqa xmm3, xmmword ptr [edx + 10h]
		movdqa xmm0, xmmword ptr [ecx]
		paddw xmm4, xmm2
		movdqa xmm7, xmmword ptr [ecx + 60h]
		paddw xmm2, xmm1
		movdqa xmm5, xmm0
		pmulhw xmm0, xmm3
		pxor xmm6, xmm6
		psubsw xmm6, xmm2
		paddw xmm0, xmm3
		pmulhw xmm3, xmm7
		movdqa xmm2, xmmword ptr [edx + 20h]
		movdqa xmm1, xmm2
		pmulhw xmm2, xmmword ptr [ecx + 10h]
		psubsw xmm0, xmm4
		paddw xmm2, xmm1
		pmulhw xmm1, xmmword ptr [ecx + 50h]
		paddsw xmm4, xmm4
		paddsw xmm4, xmm0
		psubsw xmm3, xmm6
		paddsw xmm6, xmm6
		paddsw xmm6, xmm3
		movdqa xmmword ptr [edx + 10h], xmm4
		movdqa xmm4, xmmword ptr [ecx + 30h]
		movdqa xmm5, xmm3
		pmulhw xmm3, xmm4
		movdqa xmm7, xmm2
		movdqa xmmword ptr [edx + 20h], xmm6
		movdqa xmm2, xmm0
		movdqa xmm6, xmmword ptr [edx]
		pmulhw xmm0, xmm4
		paddw xmm5, xmm3
		psubsw xmm5, xmm1
		paddw xmm2, xmm0
		movdqa xmm0, xmm6
		pmulhw xmm6, xmm4
		paddsw xmm1, xmm1
		paddsw xmm1, xmm5
		paddw xmm6, xmm0
		movdqa xmm4, xmm6
		psubsw xmm6, xmm2
		paddsw xmm2, xmm2
		movdqa xmm0, xmmword ptr [edx + 10h]
		paddsw xmm2, xmm6
		psubsw xmm2, xmm1
		paddsw xmm1, xmm1
		paddsw xmm1, xmm2
		psubsw xmm4, xmm7
		movdqa xmm3, xmmword ptr [edx + 20h]
		paddsw xmm7, xmm7
		movdqa xmmword ptr [edx + 20h], xmm2
		paddsw xmm7, xmm4
		movdqa xmmword ptr [edx + 10h], xmm1
		psubsw xmm4, xmm3
		paddsw xmm3, xmm3
		paddsw xmm3, xmm4
		psubsw xmm6, xmm5
		paddsw xmm5, xmm5
		paddsw xmm5, xmm6
		movdqa xmmword ptr [edx + 40h], xmm4
		movdqa xmmword ptr [edx + 30h], xmm3
		psubsw xmm7, xmm0
		paddsw xmm0, xmm0
		paddsw xmm0, xmm7
		movdqa xmmword ptr [edx + 60h], xmm6
		movdqa xmmword ptr [edx + 50h], xmm5
		movdqa xmmword ptr [edx + 70h], xmm7
		movdqa xmmword ptr [edx], xmm0
		movdqa xmm4, xmmword ptr [edx + 40h]
		movdqa xmm0, xmmword ptr [edx + 50h]
		movdqa xmm5, xmm4
		punpcklwd xmm4, xmm0
		punpckhwd xmm5, xmm0
		movdqa xmm6, xmmword ptr [edx + 60h]
		movdqa xmm0, xmmword ptr [edx + 70h]
		movdqa xmm7, xmm6
		punpcklwd xmm6, xmm0
		punpckhwd xmm7, xmm0
		movdqa xmm3, xmm4
		punpckldq xmm4, xmm6
		punpckhdq xmm3, xmm6
		movdqa xmmword ptr [edx + 60h], xmm3
		movdqa xmm6, xmm5
		punpckldq xmm5, xmm7
		punpckhdq xmm6, xmm7
		movdqa xmm0, xmmword ptr [edx]
		movdqa xmm1, xmmword ptr [edx + 10h]
		movdqa xmm7, xmm0
		punpcklwd xmm0, xmm1
		punpckhwd xmm7, xmm1
		movdqa xmm2, xmmword ptr [edx + 20h]
		movdqa xmm3, xmmword ptr [edx + 30h]
		movdqa xmm1, xmm2
		punpcklwd xmm2, xmm3
		punpckhwd xmm1, xmm3
		movdqa xmm3, xmm0
		punpckldq xmm0, xmm2
		punpckhdq xmm3, xmm2
		movdqa xmm2, xmm7
		punpckldq xmm2, xmm1
		punpckhdq xmm7, xmm1
		movdqa xmm1, xmm0
		punpcklqdq xmm0, xmm4
		punpckhqdq xmm1, xmm4
		movdqa xmmword ptr [edx], xmm0
		movdqa xmmword ptr [edx + 10h], xmm1
		movdqa xmm0, xmmword ptr [edx + 60h]
		movdqa xmm1, xmm3
		punpcklqdq xmm1, xmm0
		punpckhqdq xmm3, xmm0
		movdqa xmm4, xmm2
		punpcklqdq xmm4, xmm5
		punpckhqdq xmm2, xmm5
		movdqa xmmword ptr [edx + 20h], xmm1
		movdqa xmmword ptr [edx + 30h], xmm3
		movdqa xmmword ptr [edx + 40h], xmm4
		movdqa xmmword ptr [edx + 50h], xmm2
		movdqa xmm5, xmm7
		punpcklqdq xmm5, xmm6
		punpckhqdq xmm7, xmm6
		movdqa xmmword ptr [edx + 60h], xmm5
		movdqa xmmword ptr [edx + 70h], xmm7
		movdqa xmm2, xmmword ptr [edx + 30h]
		movdqa xmm6, xmmword ptr [ecx + 20h]
		movdqa xmm4, xmm2
		pmulhw xmm4, xmm6
		movdqa xmm1, xmmword ptr [ecx + 40h]
		movdqa xmm5, xmm1
		pmulhw xmm1, xmm2
		movdqa xmm3, xmmword ptr [edx + 10h]
		movdqa xmm0, xmmword ptr [ecx]
		paddw xmm4, xmm2
		movdqa xmm7, xmmword ptr [ecx + 60h]
		paddw xmm2, xmm1
		movdqa xmm5, xmm0
		pmulhw xmm0, xmm3
		pxor xmm6, xmm6
		psubsw xmm6, xmm2
		paddw xmm0, xmm3
		pmulhw xmm3, xmm7
		movdqa xmm2, xmmword ptr [edx + 20h]
		movdqa xmm1, xmm2
		pmulhw xmm2, xmmword ptr [ecx + 10h]
		psubsw xmm0, xmm4
		paddw xmm2, xmm1
		pmulhw xmm1, xmmword ptr [ecx + 50h]
		paddsw xmm4, xmm4
		paddsw xmm4, xmm0
		psubsw xmm3, xmm6
		paddsw xmm6, xmm6
		paddsw xmm6, xmm3
		movdqa xmmword ptr [edx + 10h], xmm4
		movdqa xmm4, xmmword ptr [ecx + 30h]
		movdqa xmm5, xmm3
		pmulhw xmm3, xmm4
		movdqa xmm7, xmm2
		movdqa xmmword ptr [edx + 20h], xmm6
		movdqa xmm2, xmm0
		movdqa xmm6, xmmword ptr [edx]
		pmulhw xmm0, xmm4
		paddw xmm5, xmm3
		psubsw xmm5, xmm1
		paddw xmm2, xmm0
		movdqa xmm0, xmm6
		pmulhw xmm6, xmm4
		paddsw xmm1, xmm1
		paddsw xmm1, xmm5
		paddw xmm6, xmm0
		movdqa xmm4, xmm6
		psubsw xmm6, xmm2
		paddsw xmm2, xmm2
		movdqa xmm0, xmmword ptr [edx + 10h]
		paddsw xmm2, xmm6
		psubsw xmm2, xmm1
		paddsw xmm2, xmmword ptr [kRva012D8F20]
		paddsw xmm1, xmm1
		paddsw xmm1, xmm2
		psraw xmm2, 4
		psubsw xmm4, xmm7
		psraw xmm1, 4
		movdqa xmm3, xmmword ptr [edx + 20h]
		paddsw xmm7, xmm7
		movdqa xmmword ptr [edx + 20h], xmm2
		paddsw xmm7, xmm4
		movdqa xmmword ptr [edx + 10h], xmm1
		psubsw xmm4, xmm3
		paddsw xmm4, xmmword ptr [kRva012D8F20]
		paddsw xmm3, xmm3
		paddsw xmm3, xmm4
		psraw xmm4, 4
		psubsw xmm6, xmm5
		psraw xmm3, 4
		paddsw xmm6, xmmword ptr [kRva012D8F20]
		paddsw xmm5, xmm5
		paddsw xmm5, xmm6
		psraw xmm6, 4
		movdqa xmmword ptr [edx + 40h], xmm4
		psraw xmm5, 4
		movdqa xmmword ptr [edx + 30h], xmm3
		psubsw xmm7, xmm0
		paddsw xmm7, xmmword ptr [kRva012D8F20]
		paddsw xmm0, xmm0
		paddsw xmm0, xmm7
		psraw xmm7, 4
		movdqa xmmword ptr [edx + 60h], xmm6
		psraw xmm0, 4
		movdqa xmmword ptr [edx + 50h], xmm5
		movdqa xmmword ptr [edx + 70h], xmm7
		movdqa xmmword ptr [edx], xmm0
		pop ebx
	}
}
