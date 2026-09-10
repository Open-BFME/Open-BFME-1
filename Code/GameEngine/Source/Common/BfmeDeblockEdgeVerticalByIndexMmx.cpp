// cl: /DNDEBUG /MD /O2
//
// Open-BFME5: vertical-edge sibling of bfmeDeblockEdgeByIndexMmx -- same
// table-index lookup through the shared spread table (g_rva01356A9C) and the
// same edge-limit/round/half/bias constant vectors, but the edge runs along
// columns instead of rows: it loads four rows' worth of a 4-pixel-wide strip
// straddling the edge, transposes the strip with punpck*d so the columns
// become MMX "rows", runs the identical loop-filter math, then transposes
// back and stores the four columns.  Retail 0x009C1ED0, 659 bytes.

struct Rva009C2170Ctx
{
	unsigned char m_pad[0xC];
	int m_tableIndex;
};

extern int *g_rva01356A9C;

extern const unsigned char Rva01143860Mask[8];		// retail 0x01143860 ({0xFF} x8)
extern const unsigned short Rva01143870Round[4];	// retail 0x01143870 ({4} x4)
extern const unsigned short Rva01143880Half[4];	// retail 0x01143880 ({1} x4)
extern const unsigned char Rva011438A0Limit[8];	// retail 0x011438A0 ({1} x8)
extern const unsigned char Rva011438B0Bias[8];		// retail 0x011438B0 ({0x80} x8)

void __cdecl bfmeDeblockEdgeVerticalByIndexMmx(Rva009C2170Ctx *ctx, void *row, int stride)
{
	Rva009C2170Ctx *base = (Rva009C2170Ctx *)g_rva01356A9C[ctx->m_tableIndex];
	__declspec(align(16)) unsigned short work[16];

	__asm
	{
		mov eax, base
		xor ecx, ecx
		mov edx, stride
		mov esi, row
		sub ecx, edx
		lea esi, [esi + edx]
		movd mm0, dword ptr [esi + ecx - 2]
		movd mm4, dword ptr [esi - 2]
		movd mm2, dword ptr [esi + ecx + 2]
		punpcklbw mm0, mm4
		movd mm3, dword ptr [esi + 2]
		punpcklbw mm2, mm3
		movd mm1, dword ptr [esi + edx - 2]
		movd mm5, dword ptr [esi + edx*2 - 2]
		movd mm6, dword ptr [esi + edx + 2]
		punpcklbw mm1, mm5
		movd mm7, dword ptr [esi + edx*2 + 2]
		punpckhwd mm0, mm1
		punpcklbw mm6, mm7
		lea edi, work
		punpcklwd mm2, mm6
		lea esi, [esi + edx*4]
		movd mm4, dword ptr [esi + ecx - 2]
		movd mm1, dword ptr [esi - 2]
		movd mm3, dword ptr [esi + ecx + 2]
		punpcklbw mm4, mm1
		movd mm6, dword ptr [esi + 2]
		movd mm1, dword ptr [esi + edx - 2]
		punpcklbw mm3, mm6
		movq mm5, qword ptr [esi + edx*2 - 2]
		movq mm6, qword ptr [esi + edx + 2]
		punpcklbw mm1, mm5
		movq mm7, qword ptr [esi + edx*2 + 2]
		punpckhwd mm4, mm1
		punpcklbw mm6, mm7
		movq mm1, mm0
		punpcklwd mm3, mm6
		movq mm7, mm2
		punpckldq mm0, mm4
		movq qword ptr [edi], mm0
		punpckhdq mm1, mm4
		movq mm4, mm0
		movq qword ptr [edi + 8], mm1
		punpckldq mm2, mm3
		movq mm5, mm1
		movq qword ptr [edi + 10h], mm2
		punpckhdq mm7, mm3
		movq mm6, mm2
		movq qword ptr [edi + 18h], mm7
		movq mm1, qword ptr Rva01143860Mask
		psubb mm0, mm5
		movq mm7, qword ptr Rva011438A0Limit
		pcmpgtb mm1, mm0
		pcmpgtb mm0, mm7
		movq mm3, qword ptr Rva01143860Mask
		por mm0, mm1
		movq mm1, mm7
		movq mm7, qword ptr [edi + 18h]
		psubb mm2, mm7
		pcmpgtb mm3, mm2
		pcmpgtb mm2, mm1
		por mm2, mm3
		movq mm3, qword ptr Rva011438B0Bias
		por mm0, mm2
		pxor mm1, mm1
		movq mm2, mm5
		movq mm3, mm6
		punpcklbw mm2, mm1
		punpcklbw mm3, mm1
		psubw mm3, mm2
		punpckhbw mm5, mm1
		movq mm2, mm3
		punpckhbw mm6, mm1
		paddw mm3, mm3
		psubw mm6, mm5
		paddw mm2, mm3
		movq mm5, mm6
		movq mm3, mm4
		paddw mm6, mm6
		punpcklbw mm3, mm1
		paddw mm5, mm6
		punpckhbw mm4, mm1
		movq mm6, mm7
		punpcklbw mm7, mm1
		punpckhbw mm6, mm1
		psubw mm3, mm7
		punpcklbw mm1, mm0
		pxor mm7, mm7
		psraw mm1, 8
		punpckhbw mm7, mm0
		psubw mm4, mm6
		psraw mm7, 8
		pand mm3, mm1
		pand mm4, mm7
		paddw mm2, mm3
		paddw mm4, mm5
		paddw mm2, qword ptr Rva01143870Round
		movd mm1, eax
		paddw mm4, qword ptr Rva01143870Round
		psraw mm2, 3
		psraw mm4, 3
		movq mm3, mm2
		punpcklwd mm1, mm1
		movq mm5, mm4
		punpckldq mm1, mm1
		psraw mm2, 0Fh
		movq mm6, mm1
		psraw mm4, 0Fh
		pxor mm3, mm2
		psubsw mm3, mm2
		pxor mm5, mm4
		psubsw mm5, mm4
		por mm2, qword ptr Rva01143880Half
		por mm4, qword ptr Rva01143880Half
		movq mm6, mm1
		psubusw mm1, mm3
		psubusw mm3, mm6
		por mm3, mm1
		movq mm1, mm6
		psubusw mm1, mm3
		movq mm3, mm6
		pmullw mm1, mm2
		psubusw mm3, mm5
		psubusw mm5, mm6
		por mm5, mm3
		movq mm3, mm6
		psubusw mm3, mm5
		pmullw mm4, mm3
		movq mm2, mm4
		movq mm5, qword ptr [edi + 8]
		movq mm3, mm1
		movq mm4, qword ptr Rva011438B0Bias
		packsswb mm1, mm2
		movq mm6, qword ptr [edi + 10h]
		psubb mm5, mm4
		psubb mm6, mm4
		paddsb mm5, mm1
		psubsb mm6, mm1
		paddb mm5, mm4
		paddb mm6, mm4
		movq mm1, qword ptr [edi]
		psraw mm3, 1
		psraw mm2, 1
		movq mm7, qword ptr [edi + 18h]
		packsswb mm3, mm2
		psubb mm1, mm4
		pandn mm0, mm3
		psubb mm7, mm4
		psubsb mm7, mm0
		paddsb mm0, mm1
		paddb mm7, mm4
		paddb mm0, mm4
		lea esi, [esi + ecx*4]
		movq mm4, mm0
		punpcklbw mm0, mm5
		punpckhbw mm4, mm5
		movq mm2, mm6
		punpcklbw mm2, mm7
		punpckhbw mm6, mm7
		movq mm1, mm0
		punpcklwd mm0, mm2
		movd dword ptr [esi + ecx], mm0
		punpckhwd mm1, mm2
		psrlq mm0, 20h
		movd dword ptr [esi], mm0
		movq mm5, mm4
		punpcklwd mm4, mm6
		movd dword ptr [esi + edx], mm1
		psrlq mm1, 20h
		punpckhwd mm5, mm6
		movd dword ptr [esi + edx*2], mm1
		lea esi, [esi + edx*4]
		movd dword ptr [esi + ecx], mm4
		psrlq mm4, 20h
		movd dword ptr [esi], mm4
		movd dword ptr [esi + edx], mm5
		psrlq mm5, 20h
		movd dword ptr [esi + edx*2], mm5
	}
}
