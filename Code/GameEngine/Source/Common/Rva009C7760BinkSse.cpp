// cl: /DNDEBUG /MD /O2
//
// SSE2 sibling of rva009C6CB0BinkMmx: same two-row byte average with a
// per-column round-bias table, but the whole 8-word lane fits in one xmm
// register so there is no high/low split.  First parameter is unused.
// Retail 0x009C7760, 95 bytes.

// ?rva009C7760BinkSse@@YAXPAX0PBX11H@Z
void __cdecl rva009C7760BinkSse(void *unusedParam, void *destination,
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
		pxor xmm0, xmm0
	rvaNext:
		movq xmm2, qword ptr [esi]
		movq xmm4, qword ptr [edi]
		punpcklbw xmm2, xmm0
		punpcklbw xmm4, xmm0
		movdqa xmm6, xmmword ptr [ecx]
		paddw xmm2, xmm4
		psrlw xmm2, 1
		paddw xmm2, xmm6
		lea ecx, [ecx + 10h]
		packuswb xmm2, xmm0
		add esi, edx
		add edi, edx
		cmp ecx, eax
		movq qword ptr [ebx], xmm2
		lea ebx, [ebx + edx]
		jb rvaNext
		pop edi
		pop esi
	}
}
