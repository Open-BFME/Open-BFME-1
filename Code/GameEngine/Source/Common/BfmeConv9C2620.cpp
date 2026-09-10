// cl: /O2 /Z7
//
// VP6 adaptive four-neighbour diagonal block filter. Genuine hand-vectorized
// MMX/SSE2 retail body (movd/punpcklbw/pcmpgtb/movq2dq/psraw), not compiler
// auto-vectorization -- see reverse/attempts/0x009c2320.cpp for the full
// structural derivation. Two fused loops over 8 rows: the first computes
// three signed-byte edge-weight planes per row (vertical-vs-row-above, left,
// right) into two __declspec(align(16)) frame buffers referenced by name
// from inside the __asm islands (the aligned-frame prologue this requires
// -- push ebx/mov ebx,esp/sub esp,8/and esp,-16/add esp,4/push ebp/
// mov ebp,[ebx+4]/mov [esp+4],ebp/mov ebp,esp -- is produced by /Z7 plus
// these align(16) locals plus an __asm island that uses ebp as its own
// scratch register, confirmed empirically). The second loop folds the two
// planes into the eight-row reconstruction and writes the output rows.

extern "C" int Vp6FilterEdgeTagTable[];
extern "C" unsigned char Vp6FilterConst8840[];
extern "C" unsigned char Vp6FilterConst8850[];
extern "C" unsigned char Vp6FilterConst8860[];
extern "C" unsigned char Vp6FilterConst8870[];
extern "C" unsigned char Vp6FilterConst8880[];
extern "C" unsigned char Vp6FilterConst8890[];
extern "C" unsigned char Vp6FilterConst88B0[];

extern "C" void __cdecl Rva009C2620Vp6FilterDiag4(
	void *unused, void *sourceArgument, void *destinationArgument,
	int stride, int selector, int *filterTable)
{
	__declspec(align(16)) short vertical[9][8];
	__declspec(align(16)) short horiz[16][8];
	int localStride = stride;
	unsigned char *source = (unsigned char *)sourceArgument;
	unsigned char *dest = (unsigned char *)destinationArgument;
	short *bufV = &vertical[0][0];
	short *bufH = &horiz[0][0];
	int selectorWeight = filterTable[selector];
	int edgeTag = Vp6FilterEdgeTagTable[selector];

	__asm {
		push esi
		push edi
		mov esi, source
		mov edi, bufV
		push ecx
		push edx
		mov ecx, localStride
		xor edx, edx
		push eax
		push ebx
		mov eax, selectorWeight
		mov ebx, edgeTag
		movd mm0, eax
		movd mm2, ebx
		push ebp
		punpcklbw mm0, mm0
		sub edx, ecx
		punpcklbw mm2, mm2
		pxor mm7, mm7
		punpcklbw mm0, mm0
		mov eax, bufH
		punpcklbw mm2, mm2
		lea ebx, [esi + ecx*8]
		punpcklbw mm0, mm0
		movq mm1, mm0
		punpcklbw mm2, mm2
		paddb mm1, mm0
		paddb mm1, mm0
		paddusb mm1, qword ptr [Vp6FilterConst88B0]
		paddb mm0, qword ptr [Vp6FilterConst8870]
		psubusb mm1, qword ptr [Vp6FilterConst88B0]
		movq mm3, qword ptr [Vp6FilterConst8880]
		pandn mm1, mm3
	vloop1:
		movq mm3, qword ptr [esi]
		pxor xmm7, xmm7
		movq mm4, qword ptr [esi + edx]
		movq mm5, mm3
		psubusb mm3, mm4
		psubusb mm4, mm5
		por mm3, mm4
		movq mm6, mm0
		paddusb mm3, mm3
		movq mm4, mm0
		psubusb mm6, mm3
		movq mm5, qword ptr [Vp6FilterConst8890]
		paddb mm4, qword ptr [Vp6FilterConst8860]
		pxor mm4, mm5
		pxor mm3, mm5
		pcmpgtb mm3, mm4
		pand mm3, mm2
		paddsb mm6, mm1
		psubsb mm6, mm1
		por mm6, mm3
		movq mm3, qword ptr [esi]
		movq2dq xmm0, mm6
		movq mm4, qword ptr [esi - 1]
		punpcklbw xmm7, xmm0
		movq mm5, mm3
		psraw xmm7, 8
		psubusb mm3, mm4
		movdqa xmmword ptr [edi], xmm7
		psubusb mm4, mm5
		por mm3, mm4
		movq mm6, mm0
		paddusb mm3, mm3
		movq mm4, mm0
		psubusb mm6, mm3
		movq mm5, qword ptr [Vp6FilterConst8890]
		paddb mm4, qword ptr [Vp6FilterConst8860]
		pxor mm4, mm5
		pxor mm3, mm5
		pcmpgtb mm3, mm4
		pand mm3, mm2
		paddsb mm6, mm1
		psubsb mm6, mm1
		por mm6, mm3
		movq mm3, qword ptr [esi]
		pxor xmm7, xmm7
		movq mm4, qword ptr [esi + 1]
		movq2dq xmm0, mm6
		movq mm5, mm3
		punpcklbw xmm7, xmm0
		psubusb mm3, mm4
		psraw xmm7, 8
		psubusb mm4, mm5
		movdqa xmmword ptr [eax], xmm7
		por mm3, mm4
		movq mm6, mm0
		paddusb mm3, mm3
		pxor xmm7, xmm7
		movq mm4, mm0
		psubusb mm6, mm3
		movq mm5, qword ptr [Vp6FilterConst8890]
		paddb mm4, qword ptr [Vp6FilterConst8860]
		pxor mm4, mm5
		pxor mm3, mm5
		pcmpgtb mm3, mm4
		pand mm3, mm2
		paddsb mm6, mm1
		psubsb mm6, mm1
		por mm6, mm3
		add esi, ecx
		movq2dq xmm0, mm6
		add edi, 16
		punpcklbw xmm7, xmm0
		add eax, 16
		psraw xmm7, 8
		cmp esi, ebx
		movdqa xmmword ptr [eax + 70h], xmm7
		jne vloop1

		movq mm3, qword ptr [esi]
		pxor xmm7, xmm7
		movq mm4, qword ptr [esi + edx]
		movq mm5, mm3
		psubusb mm3, mm4
		psubusb mm4, mm5
		por mm3, mm4
		movq mm6, mm0
		paddusb mm3, mm3
		movq mm4, mm0
		psubusb mm6, mm3
		movq mm5, qword ptr [Vp6FilterConst8890]
		paddb mm4, qword ptr [Vp6FilterConst8860]
		pxor mm4, mm5
		pxor mm3, mm5
		pcmpgtb mm3, mm4
		pand mm3, mm2
		paddsb mm6, mm1
		psubsb mm6, mm1
		por mm6, mm3
		movq2dq xmm6, mm6
		punpcklbw xmm7, xmm6
		psraw xmm7, 8
		movdqa xmmword ptr [edi], xmm7

		mov esi, source
		mov edi, dest
		mov eax, bufV
		mov ebx, bufH
		mov ebp, 8
	rloop2:
		movq xmm0, qword ptr [esi + edx]
		pxor xmm7, xmm7
		movdqa xmm4, xmmword ptr [eax]
		punpcklbw xmm0, xmm7
		movq xmm2, qword ptr [esi + ecx]
		pmullw xmm0, xmm4
		movdqa xmm6, xmmword ptr [eax + 16]
		punpcklbw xmm2, xmm7
		movq xmm1, qword ptr [esi - 1]
		pmullw xmm2, xmm6
		movdqa xmm3, xmmword ptr [ebx]
		punpcklbw xmm1, xmm7
		movq xmm5, qword ptr [esi + 1]
		pmullw xmm1, xmm3
		paddw xmm4, xmm6
		punpcklbw xmm5, xmm7
		movdqa xmm6, xmmword ptr [ebx + 80h]
		pmullw xmm5, xmm6
		paddw xmm0, xmm2
		paddw xmm4, xmm3
		paddw xmm0, xmm1
		paddw xmm4, xmm6
		movq xmm2, qword ptr [esi]
		paddw xmm0, xmm5
		movdqa xmm1, xmmword ptr [Vp6FilterConst8840]
		punpcklbw xmm2, xmm7
		psubw xmm1, xmm4
		pmullw xmm2, xmm1
		add esi, ecx
		movdqa xmm6, xmmword ptr [Vp6FilterConst8850]
		movdqa xmm7, xmm6
		add eax, 16
		psllw xmm7, 8
		paddw xmm0, xmm2
		add edi, ecx
		paddw xmm0, xmm6
		add ebx, 16
		paddw xmm0, xmm7
		psubusw xmm0, xmm7
		dec ebp
		psrlw xmm0, 7
		packuswb xmm0, xmm7
		movq qword ptr [edi + edx], xmm0
		jne rloop2

		pop ebp
		pop ebx
		pop eax
		pop edx
		pop ecx
		pop edi
		pop esi
	}
}
