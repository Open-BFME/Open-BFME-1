// cl: /DNDEBUG /MD /O2 /Oy-
//
// Open-BFME5: VP6-style MMX in-loop deblocking filter across a horizontal
// edge, writing four adjacent rows (y-2, y-1, y, y+1).  Looks its per-block
// strength value up through the shared spread table (g_rva01356A9C, already
// used by Rva009AF320CopyPlanes/Rva009ACC40SetupFilter for the same
// ctx->m_tableIndex field) and reassigns the context pointer parameter to
// that raw value -- retail never needs a fresh stack frame here, so unlike
// bfmeFilterBlockByIndexMmx's family the 1/4 and 1/2 constant vectors and
// the edge-limit/sign-bias masks stay the pre-existing globals retail reads
// them from instead of being rebuilt on the stack.  Retail 0x009C2170, 424
// bytes.

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

void __cdecl bfmeDeblockEdgeByIndexMmx(Rva009C2170Ctx *ctx, void *row, int stride)
{
	ctx = (Rva009C2170Ctx *)g_rva01356A9C[ctx->m_tableIndex];

	__asm
	{
		mov eax, ctx
		xor ecx, ecx
		mov edx, stride
		mov esi, row
		sub ecx, edx
		movq mm2, qword ptr [esi]
		movq mm7, qword ptr Rva011438A0Limit
		movq mm0, qword ptr [esi + ecx*2]
		movq mm6, mm2
		movq mm5, qword ptr [esi + ecx]
		movq mm4, mm0
		movq mm1, qword ptr Rva01143860Mask
		psubb mm0, mm5
		pcmpgtb mm1, mm0
		pcmpgtb mm0, mm7
		movq mm3, qword ptr Rva01143860Mask
		por mm0, mm1
		movq mm1, mm7
		movq mm7, qword ptr [esi + edx]
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
		paddw mm4, qword ptr Rva01143870Round
		movd mm1, eax
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
		pmullw mm2, mm1
		psubusw mm3, mm5
		psubusw mm5, mm6
		por mm5, mm3
		movq mm3, mm6
		psubusw mm3, mm5
		pmullw mm4, mm3
		movq mm5, qword ptr [esi + ecx]
		movq mm1, mm2
		movq mm7, qword ptr Rva011438B0Bias
		packsswb mm2, mm4
		movq mm6, qword ptr [esi]
		psubb mm5, mm7
		psubb mm6, mm7
		paddsb mm5, mm2
		psubsb mm6, mm2
		paddb mm5, mm7
		paddb mm6, mm7
		movq qword ptr [esi + ecx], mm5
		psraw mm1, 1
		psraw mm4, 1
		movq qword ptr [esi], mm6
		movq mm2, qword ptr [esi + ecx*2]
		packsswb mm1, mm4
		movq mm3, qword ptr [esi + edx]
		pandn mm0, mm1
		psubb mm2, mm7
		psubb mm3, mm7
		paddsb mm2, mm0
		paddb mm2, mm7
		movq qword ptr [esi + ecx*2], mm2
		psubsb mm3, mm0
		paddb mm3, mm7
		movq qword ptr [esi + edx], mm3
	}
}
