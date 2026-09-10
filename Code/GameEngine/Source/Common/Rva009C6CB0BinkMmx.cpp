// cl: /DNDEBUG /MD /O2
//
// Two-row byte average with a per-column round-bias table: blends row0
// and row1 (>>1 after adding), adds the caller's 8-entry qword-pair
// rounding table, packs to bytes and stores one output row, advancing the
// table pointer by 16 and the three row pointers by stride each of eight
// iterations (0x80/0x10).  First parameter is unused.  Retail 0x009C6CB0,
// 110 bytes.

// ?rva009C6CB0BinkMmx@@YAXPAX0PBX11H@Z
void __cdecl rva009C6CB0BinkMmx(void *unusedParam, void *destination,
	const void *row0, const void *row1, const void *table, int stride)
{
	__asm
	{
		push esi
		push edi
		mov ecx, table
		mov esi, row0
		mov edi, row1
		mov ebx, destination
		mov edx, stride
		lea eax, [ecx + 80h]
		pxor mm0, mm0
	rvaNext:
		movq mm2, qword ptr [esi]
		movq mm4, qword ptr [edi]
		movq mm3, mm2
		punpcklbw mm2, mm0
		movq mm5, mm4
		movq mm6, qword ptr [ecx]
		punpckhbw mm3, mm0
		movq mm7, qword ptr [ecx + 8]
		punpcklbw mm4, mm0
		punpckhbw mm5, mm0
		paddw mm2, mm4
		paddw mm3, mm5
		psrlw mm2, 1
		psrlw mm3, 1
		paddw mm2, mm6
		paddw mm3, mm7
		lea ecx, [ecx + 10h]
		packuswb mm2, mm3
		add esi, edx
		add edi, edx
		cmp ecx, eax
		movq qword ptr [ebx], mm2
		lea ebx, [ebx + edx]
		jb rvaNext
		pop edi
		pop esi
	}
}
