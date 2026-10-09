// _Rva009B8130Vp6Reconstruct
// partial score=0.993 date=2026-10-09
// cl: /Z7
extern int *g_rva01356A9C;
extern "C" unsigned char Vp6WideAccumConst86D0[8];
extern "C" unsigned char Vp6WideAccumConst86E0[8];
extern "C" unsigned char Rva009B8130Const86C0[8] = {3, 0, 3, 0, 3, 0, 3, 0};

struct Rva009B8130Vp6Context
{
    unsigned char m_pad00[0xc];
    unsigned int m_plane;
    unsigned char m_pad10[0x14];
    unsigned int *m_fragmentQIndex;
    unsigned int *m_accumulators;
};

// Open BFME 2: Code/GameEngine/Source/Common/Rva001CA000Vp6WideAccum.cpp
// _Rva009B8130Vp6Reconstruct
extern "C" void __cdecl Rva009B8130Vp6Reconstruct(
    Rva009B8130Vp6Context *context,
    unsigned char *sourceOffset,
    unsigned char *destinationOffset,
    unsigned int sourceStride,
    unsigned int firstBlock,
    int blockCount,
    const unsigned int *destinationStride)
{
    struct __declspec(align(16)) Rva009B8130Frame
    {
        unsigned char bufEsi[0x80];
        unsigned char bufEdi[0xa0];
        unsigned char scratchD[0x8];
        unsigned char padD[0x8];
        unsigned char scratchC[0x8];
        unsigned char padC[0x8];
        unsigned char filterBroadcast[0x8];
        unsigned char padFilter[0x14];
        unsigned int endBlock;
        unsigned char thresholdSquared[0x8];
        unsigned char padThreshold[0x8];
        short edgeBroadcast[0x4];
        unsigned char padEdge[0xc];
        unsigned char * ptrA;
        unsigned char * ptrB;
        unsigned int filterValPacked;
        unsigned short resultBLo[0x4];
        unsigned char padBL[0x8];
        unsigned short resultALo[0x4];
        unsigned char padAL[0x8];
        unsigned short resultBHi[0x4];
        unsigned char padBH[0x8];
        unsigned short resultAHi[0x4];
        unsigned char padAH[0x14];
        unsigned int block;
        unsigned char * p2cur;
        unsigned char * p3minus;
        unsigned char * p3cur;
        int byteIdx;
    } work;
#define bufEsi work.bufEsi
#define bufEdi work.bufEdi
#define scratchD work.scratchD
#define scratchC work.scratchC
#define filterBroadcast work.filterBroadcast
#define endBlock work.endBlock
#define thresholdSquared work.thresholdSquared
#define edgeBroadcast work.edgeBroadcast
#define ptrA work.ptrA
#define ptrB work.ptrB
#define filterValPacked work.filterValPacked
#define resultBLo work.resultBLo
#define resultALo work.resultALo
#define resultBHi work.resultBHi
#define resultAHi work.resultAHi
#define block work.block
#define p2cur work.p2cur
#define p3minus work.p3minus
#define p3cur work.p3cur
#define byteIdx work.byteIdx

	__asm {
		mov eax, dword ptr context
		mov edx, dword ptr [eax + 0xc]
		mov eax, dword ptr g_rva01356A9C
		mov eax, dword ptr [eax + edx*4]
		mov ecx, dword ptr blockCount
		mov edx, dword ptr firstBlock
		mov word ptr edgeBroadcast, ax
		mov word ptr edgeBroadcast[2], ax
		mov word ptr edgeBroadcast[4], ax
		mov word ptr edgeBroadcast[6], ax
	}

	__asm {
		lea eax, [edx + ecx]
		cmp ecx, eax
		mov dword ptr block, ecx
		mov dword ptr endBlock, eax
		jae label_15bb
	}

	__asm {
		mov ecx, dword ptr sourceOffset
		mov edx, dword ptr sourceStride
		shl eax, 2
		mov dword ptr byteIdx, eax
		mov eax, dword ptr destinationOffset
		mov dword ptr p2cur, ecx
		lea ecx, [edx*8]
		mov dword ptr p3cur, eax
		sub eax, ecx
		mov dword ptr p3minus, eax
	}

	__asm {
	label_0077:
		mov edx, dword ptr p2cur
		mov eax, dword ptr p3cur
		mov ecx, dword ptr context
		mov dword ptr ptrA, edx
		mov edx, dword ptr [ecx + 0x24]
		mov dword ptr ptrB, eax
		mov eax, dword ptr byteIdx
		mov ecx, dword ptr [eax + edx]
		mov edx, dword ptr destinationStride
		mov eax, dword ptr [edx + ecx*4]
		mov dword ptr filterValPacked, eax
	}

	__asm {
		push eax
		push ebp
		push ecx
		push edx
		push esi
		push edi
		mov eax, dword ptr filterValPacked
		xor edx, edx
		mov ecx, dword ptr sourceStride
		pcmpeqw mm6, mm6
		movd mm5, eax
		mov eax, dword ptr ptrA
		psrlw mm6, 0xe
		punpcklwd mm5, mm5
		lea esi, bufEsi
		punpckldq mm5, mm5
		sub edx, ecx
		pmullw mm6, mm5
		movq qword ptr filterBroadcast, mm5
		lea edi, bufEdi
		pxor mm7, mm7
		pmullw mm6, mm5
		lea eax, [eax + edx*4]
		movq mm0, qword ptr [eax + edx]
		movq mm1, mm0
		punpcklbw mm0, mm7
		psrlw mm6, 5
		movq qword ptr thresholdSquared, mm6
		movq mm2, qword ptr [eax]
		punpckhbw mm1, mm7
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq qword ptr [edi], mm0
		punpckhbw mm3, mm7
		movq qword ptr [edi + 8], mm1
		movq mm4, qword ptr [eax + ecx]
		movq qword ptr [edi + 0x10], mm2
		movq qword ptr [edi + 0x18], mm3
		movq mm5, mm4
		punpcklbw mm4, mm7
		movq mm0, qword ptr [eax + ecx*2]
		punpckhbw mm5, mm7
		movq mm1, mm0
		movq qword ptr [edi + 0x20], mm4
		punpcklbw mm0, mm7
		lea eax, [eax + ecx*4]
		movq qword ptr [edi + 0x28], mm5
		punpckhbw mm1, mm7
		movq mm2, qword ptr [eax + edx]
		movq qword ptr [edi + 0x30], mm0
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq qword ptr [edi + 0x38], mm1
		punpckhbw mm3, mm7
		movq mm4, qword ptr [eax]
		movq qword ptr [edi + 0x40], mm2
		movq mm5, mm4
		movq qword ptr [edi + 0x48], mm3
		punpcklbw mm4, mm7
		punpckhbw mm5, mm7
		movq mm0, qword ptr [eax + ecx]
		movq qword ptr [edi + 0x50], mm4
		movq mm1, mm0
		movq qword ptr [edi + 0x58], mm5
		punpcklbw mm0, mm7
		punpckhbw mm1, mm7
		movq mm2, qword ptr [eax + ecx*2]
		lea eax, [eax + ecx*4]
		movq mm3, mm2
		movq qword ptr [edi + 0x60], mm0
		punpcklbw mm2, mm7
		punpckhbw mm3, mm7
		movq mm4, qword ptr [eax + edx]
		movq qword ptr [edi + 0x68], mm1
		movq mm5, mm4
		punpcklbw mm4, mm7
		movq qword ptr [edi + 0x70], mm2
		movq qword ptr [edi + 0x78], mm3
		movq mm0, qword ptr [eax]
		punpckhbw mm5, mm7
		movq mm1, mm0
		movq qword ptr [edi + 0x80], mm4
		punpcklbw mm0, mm7
		punpckhbw mm1, mm7
		movq qword ptr [edi + 0x88], mm5
		movq qword ptr [edi + 0x90], mm0
		movq qword ptr [edi + 0x98], mm1
		pcmpeqw mm3, mm3
		psllw mm3, 0xf
		psrlw mm3, 8
		movq mm2, qword ptr [edi + 0x10]
		movq mm6, qword ptr [edi + 0x50]
		psubw mm2, mm3
		psubw mm6, mm3
		movq mm0, mm2
		movq mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		movq mm1, mm2
		movq mm5, mm6
		movq mm2, qword ptr [edi + 0x20]
		movq mm6, qword ptr [edi + 0x60]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		movq mm2, qword ptr [edi + 0x30]
		movq mm6, qword ptr [edi + 0x70]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		movq mm2, qword ptr [edi + 0x40]
		movq mm6, qword ptr [edi + 0x80]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		movq mm7, mm3
		psrlw mm7, 7
		movq mm2, mm0
		movq mm6, mm4
		paddw mm0, mm7
		paddw mm4, mm7
		psraw mm2, 1
		psraw mm6, 1
		psraw mm0, 1
		psraw mm4, 1
		pmullw mm2, mm0
		pmullw mm6, mm4
		psubw mm1, mm2
		psubw mm5, mm6
		movq mm7, qword ptr thresholdSquared
		movq mm2, mm1
		movq mm6, mm5
		movq qword ptr resultALo, mm1
		movq qword ptr resultBHi, mm5
		psubw mm1, mm7
		psubw mm5, mm7
		psraw mm2, 0xf
		psraw mm6, 0xf
		psraw mm1, 0xf
		psraw mm5, 0xf
		movq mm7, qword ptr [edi + 0x40]
		pandn mm2, mm1
		pandn mm6, mm5
		movq mm4, qword ptr [edi + 0x50]
		pand mm6, mm2
		movq mm2, mm7
		psubusw mm7, mm4
		psubusw mm4, mm2
		por mm7, mm4
		psubw mm7, qword ptr filterBroadcast
		psraw mm7, 0xf
		pand mm7, mm6
		add edi, 8
		movq mm2, qword ptr [edi + 0x10]
		movq mm6, qword ptr [edi + 0x50]
		psubw mm2, mm3
		psubw mm6, mm3
		movq mm0, mm2
		movq mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		movq mm1, mm2
		movq mm5, mm6
		movq mm2, qword ptr [edi + 0x20]
		movq mm6, qword ptr [edi + 0x60]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		movq mm2, qword ptr [edi + 0x30]
		movq mm6, qword ptr [edi + 0x70]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		movq mm2, qword ptr [edi + 0x40]
		movq mm6, qword ptr [edi + 0x80]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		psrlw mm3, 7
		movq mm2, mm0
		movq mm6, mm4
		paddw mm0, mm3
		paddw mm4, mm3
		psraw mm2, 1
		psraw mm6, 1
		psraw mm0, 1
		psraw mm4, 1
		pmullw mm2, mm0
		pmullw mm6, mm4
		psubw mm1, mm2
		psubw mm5, mm6
		movq qword ptr resultAHi, mm1
		movq qword ptr resultBLo, mm5
		movq mm3, qword ptr thresholdSquared
		movq mm2, mm1
		movq mm6, mm5
		psubw mm1, mm3
		psubw mm5, mm3
		psraw mm2, 0xf
		psraw mm6, 0xf
		psraw mm1, 0xf
		psraw mm5, 0xf
		movq mm0, qword ptr [edi + 0x40]
		pandn mm2, mm1
		pandn mm6, mm5
		movq mm4, qword ptr [edi + 0x50]
		pand mm6, mm2
		movq mm2, mm0
		psubusw mm0, mm4
		psubusw mm4, mm2
		por mm0, mm4
		psubw mm0, qword ptr filterBroadcast
		psraw mm0, 0xf
		pand mm0, mm6
		sub edi, 8
		movq mm1, qword ptr edgeBroadcast
		movq mm3, qword ptr [edi + 0x30]
		movq mm4, qword ptr [edi + 0x40]
		movq mm5, qword ptr [edi + 0x50]
		movq mm6, qword ptr [edi + 0x60]
		psubw mm5, mm4
		psubw mm3, mm6
		movq mm4, mm5
		paddw mm4, mm5
		paddw mm3, qword ptr Vp6WideAccumConst86D0
		paddw mm5, mm4
		paddw mm3, mm5
		psraw mm3, 3
		movq mm2, mm3
		psraw mm3, 0xf
		pxor mm2, mm3
		psubsw mm2, mm3
		por mm3, qword ptr Vp6WideAccumConst86E0
		movq mm4, mm1
		psubw mm1, mm2
		movq mm5, mm1
		psraw mm1, 0xf
		pxor mm5, mm1
		psubsw mm5, mm1
		psubusw mm4, mm5
		pmullw mm4, mm3
		movq mm1, qword ptr [edi + 0x40]
		movq mm2, qword ptr [edi + 0x50]
		paddw mm1, mm4
		psubw mm2, mm4
		pxor mm6, mm6
		packuswb mm1, mm1
		packuswb mm2, mm2
		punpcklbw mm1, mm6
		movq qword ptr scratchC, mm1
		punpcklbw mm2, mm6
		movq qword ptr scratchD, mm2
		movq mm5, qword ptr [edi]
		movq mm4, qword ptr [edi + 0x10]
		movq mm3, mm4
		movq mm6, mm5
		psubusw mm4, mm6
		psubusw mm5, mm3
		por mm4, mm5
		psubw mm4, qword ptr filterBroadcast
		psraw mm4, 0xf
		movq mm1, mm4
		pand mm4, mm6
		pandn mm1, mm3
		por mm1, mm4
		movq mm4, qword ptr [edi + 0x80]
		movq mm5, qword ptr [edi + 0x90]
		movq mm3, mm4
		movq mm6, mm5
		psubusw mm4, mm6
		psubusw mm5, mm3
		por mm4, mm5
		psubw mm4, qword ptr filterBroadcast
		psraw mm4, 0xf
		movq mm2, mm4
		pand mm4, mm6
		pandn mm2, mm3
		por mm2, mm4
		movq mm3, mm1
		paddw mm3, mm3
		paddw mm3, mm1
		movq mm4, qword ptr [edi + 0x10]
		paddw mm3, qword ptr [edi + 0x20]
		paddw mm4, qword ptr [edi + 0x30]
		paddw mm3, qword ptr [edi + 0x40]
		paddw mm4, qword ptr Vp6WideAccumConst86D0
		paddw mm3, mm4
		movq mm4, mm3
		movq mm5, qword ptr [edi + 0x10]
		paddw mm4, mm5
		psllw mm4, 1
		psubw mm4, qword ptr [edi + 0x40]
		paddw mm4, qword ptr [edi + 0x50]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi], mm4
		movq mm5, qword ptr [edi + 0x20]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x50]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		psubw mm4, qword ptr [edi + 0x50]
		paddw mm4, qword ptr [edi + 0x60]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x10], mm4
		movq mm5, qword ptr [edi + 0x30]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x60]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		psubw mm4, qword ptr [edi + 0x60]
		paddw mm4, qword ptr [edi + 0x70]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x20], mm4
		movq mm5, qword ptr [edi + 0x40]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x70]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, mm1
		psubw mm4, qword ptr [edi + 0x10]
		psubw mm4, qword ptr [edi + 0x70]
		paddw mm4, qword ptr [edi + 0x80]
		movq mm5, qword ptr scratchC
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x30], mm4
		movq mm5, qword ptr [edi + 0x50]
		psubw mm3, qword ptr [edi + 0x10]
		paddw mm3, qword ptr [edi + 0x80]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi + 0x10]
		psubw mm4, qword ptr [edi + 0x20]
		psubw mm4, qword ptr [edi + 0x80]
		paddw mm4, mm2
		movq mm5, qword ptr scratchD
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x40], mm4
		movq mm5, qword ptr [edi + 0x60]
		psubw mm3, qword ptr [edi + 0x20]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi + 0x20]
		psubw mm4, qword ptr [edi + 0x30]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x50], mm4
		movq mm5, qword ptr [edi + 0x70]
		psubw mm3, qword ptr [edi + 0x30]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi + 0x30]
		psubw mm4, qword ptr [edi + 0x40]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x60], mm4
		movq mm5, qword ptr [edi + 0x80]
		psubw mm3, qword ptr [edi + 0x40]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi + 0x40]
		psubw mm4, qword ptr [edi + 0x50]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x70], mm4
		add edi, 8
		add esi, 8
		movq mm1, qword ptr edgeBroadcast
		movq mm3, qword ptr [edi + 0x30]
		movq mm4, qword ptr [edi + 0x40]
		movq mm5, qword ptr [edi + 0x50]
		movq mm6, qword ptr [edi + 0x60]
		psubw mm5, mm4
		psubw mm3, mm6
		movq mm4, mm5
		paddw mm3, qword ptr Vp6WideAccumConst86D0
		paddw mm4, mm4
		paddw mm3, mm4
		paddw mm3, mm5
		psraw mm3, 3
		movq mm2, mm3
		psraw mm3, 0xf
		pxor mm2, mm3
		psubsw mm2, mm3
		por mm3, qword ptr Vp6WideAccumConst86E0
		movq mm4, mm1
		psubw mm1, mm2
		movq mm5, mm1
		psraw mm1, 0xf
		pxor mm5, mm1
		psubsw mm5, mm1
		psubusw mm4, mm5
		pmullw mm4, mm3
		movq mm1, qword ptr [edi + 0x40]
		movq mm2, qword ptr [edi + 0x50]
		paddw mm1, mm4
		psubw mm2, mm4
		pxor mm6, mm6
		packuswb mm1, mm1
		packuswb mm2, mm2
		punpcklbw mm1, mm6
		movq qword ptr scratchC, mm1
		punpcklbw mm2, mm6
		movq qword ptr scratchD, mm2
		movq mm5, qword ptr [edi]
		movq mm4, qword ptr [edi + 0x10]
		movq mm3, mm4
		movq mm6, mm5
		psubusw mm4, mm6
		psubusw mm5, mm3
		por mm4, mm5
		psubw mm4, qword ptr filterBroadcast
		psraw mm4, 0xf
		movq mm1, mm4
		pand mm4, mm6
		pandn mm1, mm3
		por mm1, mm4
		movq mm4, qword ptr [edi + 0x80]
		movq mm5, qword ptr [edi + 0x90]
		movq mm3, mm4
		movq mm6, mm5
		psubusw mm4, mm6
		psubusw mm5, mm3
		por mm4, mm5
		psubw mm4, qword ptr filterBroadcast
		psraw mm4, 0xf
		movq mm2, mm4
		pand mm4, mm6
		pandn mm2, mm3
		por mm2, mm4
		movq mm3, mm1
		paddw mm3, mm3
		paddw mm3, mm1
		movq mm4, qword ptr [edi + 0x10]
		paddw mm3, qword ptr [edi + 0x20]
		paddw mm4, qword ptr [edi + 0x30]
		paddw mm3, qword ptr [edi + 0x40]
		paddw mm4, qword ptr Vp6WideAccumConst86D0
		paddw mm3, mm4
		movq mm4, mm3
		movq mm5, qword ptr [edi + 0x10]
		paddw mm4, mm5
		psllw mm4, 1
		psubw mm4, qword ptr [edi + 0x40]
		paddw mm4, qword ptr [edi + 0x50]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi], mm4
		movq mm5, qword ptr [edi + 0x20]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x50]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		psubw mm4, qword ptr [edi + 0x50]
		paddw mm4, qword ptr [edi + 0x60]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x10], mm4
		movq mm5, qword ptr [edi + 0x30]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x60]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		psubw mm4, qword ptr [edi + 0x60]
		paddw mm4, qword ptr [edi + 0x70]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x20], mm4
		movq mm5, qword ptr [edi + 0x40]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x70]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, mm1
		psubw mm4, qword ptr [edi + 0x10]
		psubw mm4, qword ptr [edi + 0x70]
		paddw mm4, qword ptr [edi + 0x80]
		movq mm5, qword ptr scratchC
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x30], mm4
		movq mm5, qword ptr [edi + 0x50]
		psubw mm3, qword ptr [edi + 0x10]
		paddw mm3, qword ptr [edi + 0x80]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi + 0x10]
		psubw mm4, qword ptr [edi + 0x20]
		psubw mm4, qword ptr [edi + 0x80]
		paddw mm4, mm2
		movq mm5, qword ptr scratchD
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x40], mm4
		movq mm5, qword ptr [edi + 0x60]
		psubw mm3, qword ptr [edi + 0x20]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi + 0x20]
		psubw mm4, qword ptr [edi + 0x30]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x50], mm4
		movq mm5, qword ptr [edi + 0x70]
		psubw mm3, qword ptr [edi + 0x30]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi + 0x30]
		psubw mm4, qword ptr [edi + 0x40]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x60], mm4
		movq mm5, qword ptr [edi + 0x80]
		psubw mm3, qword ptr [edi + 0x40]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi + 0x40]
		psubw mm4, qword ptr [edi + 0x50]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x70], mm4
		add edi, 8
		sub esi, 8
		mov ebp, dword ptr ptrB
		lea ebp, [ebp + edx*4]
		movq mm0, qword ptr [esi]
		packuswb mm0, qword ptr [esi + 8]
		movq qword ptr [ebp], mm0
		movq mm1, qword ptr [esi + 0x10]
		packuswb mm1, qword ptr [esi + 0x18]
		movq qword ptr [ebp + ecx], mm1
		movq mm2, qword ptr [esi + 0x20]
		packuswb mm2, qword ptr [esi + 0x28]
		movq qword ptr [ebp + ecx*2], mm2
		movq mm3, qword ptr [esi + 0x30]
		packuswb mm3, qword ptr [esi + 0x38]
		lea ebp, [ebp + ecx*4]
		movq qword ptr [ebp + edx], mm3
		movq mm0, qword ptr [esi + 0x40]
		packuswb mm0, qword ptr [esi + 0x48]
		movq qword ptr [ebp], mm0
		movq mm1, qword ptr [esi + 0x50]
		packuswb mm1, qword ptr [esi + 0x58]
		movq qword ptr [ebp + ecx], mm1
		movq mm2, qword ptr [esi + 0x60]
		packuswb mm2, qword ptr [esi + 0x68]
		movq qword ptr [ebp + ecx*2], mm2
		movq mm3, qword ptr [esi + 0x70]
		packuswb mm3, qword ptr [esi + 0x78]
		lea ebp, [ebp + ecx*2]
		movq qword ptr [ebp + ecx], mm3
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebp
		pop eax
	}

	__asm {
		movzx edi, word ptr resultAHi[4]
		movzx esi, word ptr resultAHi[6]
		add esi, edi
		movzx edi, word ptr resultAHi[2]
		add esi, edi
		movzx edi, word ptr resultAHi
		add esi, edi
		movzx edi, word ptr resultALo[6]
		add esi, edi
		movzx edi, word ptr resultALo[4]
		mov edx, dword ptr context
		mov eax, dword ptr [edx + 0x28]
		mov ecx, dword ptr block
		add esi, edi
		movzx edi, word ptr resultALo[2]
		add esi, edi
		movzx edi, word ptr resultALo
		add esi, edi
		mov edi, dword ptr [eax + ecx*4]
		add edi, esi
		mov esi, dword ptr byteIdx
		mov dword ptr [eax + ecx*4], edi
		movzx edi, word ptr resultBLo[4]
		lea eax, [eax + ecx*4]
		mov eax, dword ptr [edx + 0x28]
		add eax, esi
		movzx esi, word ptr resultBLo[6]
		add esi, edi
		movzx edi, word ptr resultBLo[2]
		add esi, edi
		movzx edi, word ptr resultBLo
		add esi, edi
		movzx edi, word ptr resultBHi[6]
		add esi, edi
		movzx edi, word ptr resultBHi[4]
		add esi, edi
		movzx edi, word ptr resultBHi[2]
		add esi, edi
		movzx edi, word ptr resultBHi
		add esi, edi
		add dword ptr [eax], esi
		cmp ecx, dword ptr blockCount
		jne label_0a3c
	}

	__asm {
		mov edi, dword ptr p2cur
		mov esi, dword ptr p3cur
		mov edx, dword ptr p3minus
		mov eax, 8
		inc ecx
		add edi, eax
		add esi, eax
		add edx, eax
		mov dword ptr block, ecx
		mov dword ptr p2cur, edi
		mov dword ptr p3cur, esi
		mov dword ptr p3minus, edx
		jmp label_15ab
	}

	__asm {
	label_0a3c:
		mov edx, dword ptr [edx + 0x24]
		mov ecx, dword ptr [edx + ecx*4]
		mov eax, dword ptr p3minus
		mov edx, dword ptr destinationStride
		mov ecx, dword ptr [edx + ecx*4]
		movzx dx, byte ptr [eax - 5]
		mov word ptr bufEdi, dx
		mov dword ptr filterValPacked, ecx
		movzx cx, byte ptr [eax + 4]
		mov word ptr bufEdi[144], cx
		mov ecx, dword ptr sourceStride
		movzx dx, byte ptr [eax + ecx - 5]
		mov word ptr bufEdi[2], dx
		movzx dx, byte ptr [eax + ecx + 4]
		mov word ptr bufEdi[146], dx
		movzx dx, byte ptr [eax + ecx*2 - 5]
		mov word ptr bufEdi[4], dx
		movzx dx, byte ptr [eax + ecx*2 + 4]
		mov word ptr bufEdi[148], dx
		lea edx, [ecx + ecx*2]
		movzx si, byte ptr [eax + edx - 5]
		movzx dx, byte ptr [eax + edx + 4]
		mov word ptr bufEdi[150], dx
		movzx dx, byte ptr [eax + ecx*4 - 5]
		mov word ptr bufEdi[8], dx
		movzx dx, byte ptr [eax + ecx*4 + 4]
		mov word ptr bufEdi[152], dx
		lea edx, [ecx + ecx*4]
		mov word ptr bufEdi[6], si
		movzx si, byte ptr [eax + edx - 5]
		movzx dx, byte ptr [eax + edx + 4]
		mov word ptr bufEdi[154], dx
		lea edx, [ecx + ecx*2]
		imul ecx, ecx, 7
		shl edx, 1
		mov word ptr bufEdi[10], si
		movzx si, byte ptr [eax + edx - 5]
		movzx dx, byte ptr [eax + edx + 4]
		mov word ptr bufEdi[156], dx
		movzx dx, byte ptr [eax + ecx - 5]
		mov dword ptr ptrB, eax
		mov dword ptr ptrA, eax
		movzx ax, byte ptr [eax + ecx + 4]
		mov word ptr bufEdi[12], si
		mov word ptr bufEdi[14], dx
		mov word ptr bufEdi[158], ax
	}

	__asm {
		push eax
		push ebp
		mov eax, dword ptr filterValPacked
		movd mm0, eax
		push ecx
		punpcklwd mm0, mm0
		movq mm1, qword ptr Rva009B8130Const86C0
		push edx
		punpckldq mm0, mm0
		movq qword ptr filterBroadcast, mm0
		push esi
		pmullw mm1, mm0
		pmullw mm1, mm0
		push edi
		psrlw mm1, 5
		movq qword ptr thresholdSquared, mm1
		mov eax, dword ptr ptrA
		xor edx, edx
		sub eax, 4
		lea esi, bufEsi
		lea edi, bufEdi
		mov ecx, dword ptr sourceStride
		sub edx, ecx
		movq mm0, qword ptr [eax]
		movq mm1, qword ptr [eax + ecx]
		movq mm2, qword ptr [eax + ecx*2]
		lea eax, [eax + ecx*4]
		movq mm3, qword ptr [eax + edx]
		movq mm4, mm0
		punpcklbw mm0, mm1
		punpckhbw mm4, mm1
		movq mm5, mm2
		punpcklbw mm2, mm3
		punpckhbw mm5, mm3
		movq mm1, mm0
		punpcklwd mm0, mm2
		punpckhwd mm1, mm2
		movq mm2, mm4
		punpckhwd mm4, mm5
		punpcklwd mm2, mm5
		pxor mm7, mm7
		movq mm5, mm0
		punpcklbw mm0, mm7
		movq qword ptr [edi + 0x10], mm0
		punpckhbw mm5, mm7
		movq mm0, mm1
		movq qword ptr [edi + 0x20], mm5
		punpcklbw mm1, mm7
		punpckhbw mm0, mm7
		movq qword ptr [edi + 0x30], mm1
		movq mm3, mm2
		movq mm5, mm4
		movq qword ptr [edi + 0x40], mm0
		punpcklbw mm2, mm7
		punpckhbw mm3, mm7
		movq qword ptr [edi + 0x50], mm2
		punpcklbw mm4, mm7
		punpckhbw mm5, mm7
		movq qword ptr [edi + 0x60], mm3
		movq mm0, qword ptr [eax]
		movq mm1, qword ptr [eax + ecx]
		movq qword ptr [edi + 0x70], mm4
		movq mm2, qword ptr [eax + ecx*2]
		lea eax, [eax + ecx*4]
		movq qword ptr [edi + 0x80], mm5
		movq mm4, mm0
		movq mm3, qword ptr [eax + edx]
		punpcklbw mm0, mm1
		punpckhbw mm4, mm1
		movq mm5, mm2
		punpcklbw mm2, mm3
		punpckhbw mm5, mm3
		movq mm1, mm0
		punpcklwd mm0, mm2
		punpckhwd mm1, mm2
		movq mm2, mm4
		punpckhwd mm4, mm5
		punpcklwd mm2, mm5
		movq mm5, mm0
		punpcklbw mm0, mm7
		movq qword ptr [edi + 0x18], mm0
		punpckhbw mm5, mm7
		movq mm0, mm1
		movq qword ptr [edi + 0x28], mm5
		punpcklbw mm1, mm7
		punpckhbw mm0, mm7
		movq qword ptr [edi + 0x38], mm1
		movq mm3, mm2
		movq mm5, mm4
		movq qword ptr [edi + 0x48], mm0
		punpcklbw mm2, mm7
		punpckhbw mm3, mm7
		movq qword ptr [edi + 0x58], mm2
		punpcklbw mm4, mm7
		punpckhbw mm5, mm7
		movq qword ptr [edi + 0x68], mm3
		movq qword ptr [edi + 0x78], mm4
		movq qword ptr [edi + 0x88], mm5
		pcmpeqw mm3, mm3
		psllw mm3, 0xf
		psrlw mm3, 8
		movq mm2, qword ptr [edi + 0x10]
		movq mm6, qword ptr [edi + 0x50]
		psubw mm2, mm3
		psubw mm6, mm3
		movq mm0, mm2
		movq mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		movq mm1, mm2
		movq mm5, mm6
		movq mm2, qword ptr [edi + 0x20]
		movq mm6, qword ptr [edi + 0x60]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		movq mm2, qword ptr [edi + 0x30]
		movq mm6, qword ptr [edi + 0x70]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		movq mm2, qword ptr [edi + 0x40]
		movq mm6, qword ptr [edi + 0x80]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		movq mm7, mm3
		psrlw mm7, 7
		movq mm2, mm0
		movq mm6, mm4
		paddw mm0, mm7
		paddw mm4, mm7
		psraw mm2, 1
		psraw mm6, 1
		psraw mm0, 1
		psraw mm4, 1
		pmullw mm2, mm0
		pmullw mm6, mm4
		psubw mm1, mm2
		psubw mm5, mm6
		movq qword ptr resultALo, mm1
		movq qword ptr resultBHi, mm5
		movq mm7, qword ptr thresholdSquared
		movq mm2, mm1
		movq mm6, mm5
		psubw mm1, mm7
		psubw mm5, mm7
		psraw mm1, 0xf
		psraw mm5, 0xf
		psraw mm2, 0xf
		psraw mm6, 0xf
		movq mm7, qword ptr [edi + 0x40]
		pandn mm2, mm1
		pandn mm6, mm5
		movq mm4, qword ptr [edi + 0x50]
		pand mm6, mm2
		movq mm2, mm7
		psubusw mm7, mm4
		psubusw mm4, mm2
		por mm7, mm4
		psubw mm7, qword ptr filterBroadcast
		psraw mm7, 0xf
		pand mm7, mm6
		add edi, 8
		movq mm2, qword ptr [edi + 0x10]
		movq mm6, qword ptr [edi + 0x50]
		psubw mm2, mm3
		psubw mm6, mm3
		movq mm0, mm2
		movq mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		movq mm1, mm2
		movq mm5, mm6
		movq mm2, qword ptr [edi + 0x20]
		movq mm6, qword ptr [edi + 0x60]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		movq mm2, qword ptr [edi + 0x30]
		movq mm6, qword ptr [edi + 0x70]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		movq mm2, qword ptr [edi + 0x40]
		movq mm6, qword ptr [edi + 0x80]
		psubw mm2, mm3
		psubw mm6, mm3
		paddw mm0, mm2
		paddw mm4, mm6
		pmullw mm2, mm2
		pmullw mm6, mm6
		paddw mm1, mm2
		paddw mm5, mm6
		psrlw mm3, 7
		movq mm2, mm0
		movq mm6, mm4
		paddw mm0, mm3
		paddw mm4, mm3
		psraw mm2, 1
		psraw mm6, 1
		psraw mm0, 1
		psraw mm4, 1
		pmullw mm2, mm0
		pmullw mm6, mm4
		psubw mm1, mm2
		psubw mm5, mm6
		movq qword ptr resultAHi, mm1
		movq qword ptr resultBLo, mm5
		movq mm3, qword ptr thresholdSquared
		movq mm2, mm1
		movq mm6, mm5
		psubw mm1, mm3
		psubw mm5, mm3
		psraw mm6, 0xf
		psraw mm2, 0xf
		psraw mm1, 0xf
		psraw mm5, 0xf
		movq mm0, qword ptr [edi + 0x40]
		pandn mm2, mm1
		pandn mm6, mm5
		movq mm4, qword ptr [edi + 0x50]
		pand mm6, mm2
		movq mm2, mm0
		psubusw mm0, mm4
		psubusw mm4, mm2
		por mm0, mm4
		psubw mm0, qword ptr filterBroadcast
		psraw mm0, 0xf
		pand mm0, mm6
		sub edi, 8
		movq mm1, qword ptr edgeBroadcast
		movq mm3, qword ptr [edi + 0x30]
		movq mm4, qword ptr [edi + 0x40]
		movq mm5, qword ptr [edi + 0x50]
		movq mm6, qword ptr [edi + 0x60]
		psubw mm5, mm4
		psubw mm3, mm6
		movq mm4, mm5
		paddw mm4, mm5
		paddw mm3, qword ptr Vp6WideAccumConst86D0
		paddw mm5, mm4
		paddw mm3, mm5
		psraw mm3, 3
		movq mm2, mm3
		psraw mm3, 0xf
		pxor mm2, mm3
		psubsw mm2, mm3
		por mm3, qword ptr Vp6WideAccumConst86E0
		movq mm4, mm1
		psubw mm1, mm2
		movq mm5, mm1
		psraw mm1, 0xf
		pxor mm5, mm1
		psubsw mm5, mm1
		psubusw mm4, mm5
		pmullw mm4, mm3
		movq mm1, qword ptr [edi + 0x40]
		movq mm2, qword ptr [edi + 0x50]
		paddw mm1, mm4
		psubw mm2, mm4
		pxor mm6, mm6
		packuswb mm1, mm1
		packuswb mm2, mm2
		punpcklbw mm1, mm6
		movq qword ptr scratchC, mm1
		punpcklbw mm2, mm6
		movq qword ptr scratchD, mm2
		movq mm5, qword ptr [edi]
		movq mm4, qword ptr [edi + 0x10]
		movq mm3, mm4
		movq mm6, mm5
		psubusw mm4, mm6
		psubusw mm5, mm3
		por mm4, mm5
		psubw mm4, qword ptr filterBroadcast
		psraw mm4, 0xf
		movq mm1, mm4
		pand mm4, mm6
		pandn mm1, mm3
		por mm1, mm4
		movq mm4, qword ptr [edi + 0x80]
		movq mm5, qword ptr [edi + 0x90]
		movq mm3, mm4
		movq mm6, mm5
		psubusw mm4, mm6
		psubusw mm5, mm3
		por mm4, mm5
		psubw mm4, qword ptr filterBroadcast
		psraw mm4, 0xf
		movq mm2, mm4
		pand mm4, mm6
		pandn mm2, mm3
		por mm2, mm4
		movq mm3, mm1
		paddw mm3, mm3
		paddw mm3, mm1
		movq mm4, qword ptr [edi + 0x10]
		paddw mm3, qword ptr [edi + 0x20]
		paddw mm4, qword ptr [edi + 0x30]
		paddw mm3, qword ptr [edi + 0x40]
		paddw mm4, qword ptr Vp6WideAccumConst86D0
		paddw mm3, mm4
		movq mm4, mm3
		movq mm5, qword ptr [edi + 0x10]
		paddw mm4, mm5
		psllw mm4, 1
		psubw mm4, qword ptr [edi + 0x40]
		paddw mm4, qword ptr [edi + 0x50]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi], mm4
		movq mm5, qword ptr [edi + 0x20]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x50]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		psubw mm4, qword ptr [edi + 0x50]
		paddw mm4, qword ptr [edi + 0x60]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x10], mm4
		movq mm5, qword ptr [edi + 0x30]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x60]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		psubw mm4, qword ptr [edi + 0x60]
		paddw mm4, qword ptr [edi + 0x70]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x20], mm4
		movq mm5, qword ptr [edi + 0x40]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x70]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, mm1
		psubw mm4, qword ptr [edi + 0x10]
		psubw mm4, qword ptr [edi + 0x70]
		paddw mm4, qword ptr [edi + 0x80]
		movq mm5, qword ptr scratchC
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x30], mm4
		movq mm5, qword ptr [edi + 0x50]
		psubw mm3, qword ptr [edi + 0x10]
		paddw mm3, qword ptr [edi + 0x80]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi + 0x10]
		psubw mm4, qword ptr [edi + 0x20]
		psubw mm4, qword ptr [edi + 0x80]
		paddw mm4, mm2
		movq mm5, qword ptr scratchD
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x40], mm4
		movq mm5, qword ptr [edi + 0x60]
		psubw mm3, qword ptr [edi + 0x20]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi + 0x20]
		psubw mm4, qword ptr [edi + 0x30]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x50], mm4
		movq mm5, qword ptr [edi + 0x70]
		psubw mm3, qword ptr [edi + 0x30]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi + 0x30]
		psubw mm4, qword ptr [edi + 0x40]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x60], mm4
		movq mm5, qword ptr [edi + 0x80]
		psubw mm3, qword ptr [edi + 0x40]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi + 0x40]
		psubw mm4, qword ptr [edi + 0x50]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x70], mm4
		add edi, 8
		add esi, 8
		movq mm1, qword ptr edgeBroadcast
		movq mm3, qword ptr [edi + 0x30]
		movq mm4, qword ptr [edi + 0x40]
		movq mm5, qword ptr [edi + 0x50]
		movq mm6, qword ptr [edi + 0x60]
		psubw mm5, mm4
		psubw mm3, mm6
		movq mm4, mm5
		paddw mm4, mm5
		paddw mm3, qword ptr Vp6WideAccumConst86D0
		paddw mm5, mm4
		paddw mm3, mm5
		psraw mm3, 3
		movq mm2, mm3
		psraw mm3, 0xf
		pxor mm2, mm3
		psubsw mm2, mm3
		por mm3, qword ptr Vp6WideAccumConst86E0
		movq mm4, mm1
		psubw mm1, mm2
		movq mm5, mm1
		psraw mm1, 0xf
		pxor mm5, mm1
		psubsw mm5, mm1
		psubusw mm4, mm5
		pmullw mm4, mm3
		movq mm1, qword ptr [edi + 0x40]
		movq mm2, qword ptr [edi + 0x50]
		paddw mm1, mm4
		psubw mm2, mm4
		pxor mm6, mm6
		packuswb mm1, mm1
		packuswb mm2, mm2
		punpcklbw mm1, mm6
		movq qword ptr scratchC, mm1
		punpcklbw mm2, mm6
		movq qword ptr scratchD, mm2
		movq mm5, qword ptr [edi]
		movq mm4, qword ptr [edi + 0x10]
		movq mm3, mm4
		movq mm6, mm5
		psubusw mm4, mm6
		psubusw mm5, mm3
		por mm4, mm5
		psubw mm4, qword ptr filterBroadcast
		psraw mm4, 0xf
		movq mm1, mm4
		pand mm4, mm6
		pandn mm1, mm3
		por mm1, mm4
		movq mm4, qword ptr [edi + 0x80]
		movq mm5, qword ptr [edi + 0x90]
		movq mm3, mm4
		movq mm6, mm5
		psubusw mm4, mm6
		psubusw mm5, mm3
		por mm4, mm5
		psubw mm4, qword ptr filterBroadcast
		psraw mm4, 0xf
		movq mm2, mm4
		pand mm4, mm6
		pandn mm2, mm3
		por mm2, mm4
		movq mm3, mm1
		paddw mm3, mm3
		paddw mm3, mm1
		movq mm4, qword ptr [edi + 0x10]
		paddw mm3, qword ptr [edi + 0x20]
		paddw mm4, qword ptr [edi + 0x30]
		paddw mm3, qword ptr [edi + 0x40]
		paddw mm4, qword ptr Vp6WideAccumConst86D0
		paddw mm3, mm4
		movq mm4, mm3
		movq mm5, qword ptr [edi + 0x10]
		paddw mm4, mm5
		psllw mm4, 1
		psubw mm4, qword ptr [edi + 0x40]
		paddw mm4, qword ptr [edi + 0x50]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi], mm4
		movq mm5, qword ptr [edi + 0x20]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x50]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		psubw mm4, qword ptr [edi + 0x50]
		paddw mm4, qword ptr [edi + 0x60]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x10], mm4
		movq mm5, qword ptr [edi + 0x30]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x60]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		psubw mm4, qword ptr [edi + 0x60]
		paddw mm4, qword ptr [edi + 0x70]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x20], mm4
		movq mm5, qword ptr [edi + 0x40]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x70]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, mm1
		psubw mm4, qword ptr [edi + 0x10]
		psubw mm4, qword ptr [edi + 0x70]
		paddw mm4, qword ptr [edi + 0x80]
		movq mm5, qword ptr scratchC
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x30], mm4
		movq mm5, qword ptr [edi + 0x50]
		psubw mm3, qword ptr [edi + 0x10]
		paddw mm3, qword ptr [edi + 0x80]
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi + 0x10]
		psubw mm4, qword ptr [edi + 0x20]
		psubw mm4, qword ptr [edi + 0x80]
		paddw mm4, mm2
		movq mm5, qword ptr scratchD
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x40], mm4
		movq mm5, qword ptr [edi + 0x60]
		psubw mm3, qword ptr [edi + 0x20]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi + 0x20]
		psubw mm4, qword ptr [edi + 0x30]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x50], mm4
		movq mm5, qword ptr [edi + 0x70]
		psubw mm3, qword ptr [edi + 0x30]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi + 0x30]
		psubw mm4, qword ptr [edi + 0x40]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x60], mm4
		movq mm5, qword ptr [edi + 0x80]
		psubw mm3, qword ptr [edi + 0x40]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		paddw mm4, mm4
		paddw mm4, qword ptr [edi + 0x40]
		psubw mm4, qword ptr [edi + 0x50]
		psraw mm4, 4
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x70], mm4
		mov eax, dword ptr ptrB
		add edi, 8
		sub esi, 8
		sub eax, 4
		movq mm0, qword ptr [esi]
		movq mm1, qword ptr [esi + 0x10]
		movq mm4, mm0
		punpcklwd mm0, mm1
		punpckhwd mm4, mm1
		movq mm2, qword ptr [esi + 0x20]
		movq mm3, qword ptr [esi + 0x30]
		movq mm5, mm2
		punpcklwd mm2, mm3
		punpckhwd mm5, mm3
		movq mm1, mm0
		punpckldq mm0, mm2
		movq qword ptr [edi], mm0
		punpckhdq mm1, mm2
		movq mm0, mm4
		movq qword ptr [edi + 0x10], mm1
		punpckldq mm0, mm5
		punpckhdq mm4, mm5
		movq mm1, qword ptr [esi + 0x40]
		movq mm2, qword ptr [esi + 0x50]
		movq mm5, qword ptr [esi + 0x60]
		movq mm6, qword ptr [esi + 0x70]
		movq mm3, mm1
		movq mm7, mm5
		punpcklwd mm1, mm2
		punpckhwd mm3, mm2
		punpcklwd mm5, mm6
		punpckhwd mm7, mm6
		movq mm2, mm1
		movq mm6, mm3
		punpckldq mm1, mm5
		punpckhdq mm2, mm5
		punpckldq mm3, mm7
		punpckhdq mm6, mm7
		movq mm5, qword ptr [edi]
		packuswb mm5, mm1
		movq qword ptr [eax], mm5
		movq mm7, qword ptr [edi + 0x10]
		packuswb mm7, mm2
		movq qword ptr [eax + ecx], mm7
		packuswb mm0, mm3
		packuswb mm4, mm6
		movq qword ptr [eax + ecx*2], mm0
		lea eax, [eax + ecx*4]
		movq qword ptr [eax + edx], mm4
		add edi, 8
		add esi, 8
		movq mm0, qword ptr [esi]
		movq mm1, qword ptr [esi + 0x10]
		movq mm4, mm0
		punpcklwd mm0, mm1
		punpckhwd mm4, mm1
		movq mm2, qword ptr [esi + 0x20]
		movq mm3, qword ptr [esi + 0x30]
		movq mm5, mm2
		punpcklwd mm2, mm3
		punpckhwd mm5, mm3
		movq mm1, mm0
		punpckldq mm0, mm2
		movq qword ptr [edi], mm0
		punpckhdq mm1, mm2
		movq mm0, mm4
		movq qword ptr [edi + 0x10], mm1
		punpckldq mm0, mm5
		punpckhdq mm4, mm5
		movq mm1, qword ptr [esi + 0x40]
		movq mm2, qword ptr [esi + 0x50]
		movq mm5, qword ptr [esi + 0x60]
		movq mm6, qword ptr [esi + 0x70]
		movq mm3, mm1
		movq mm7, mm5
		punpcklwd mm1, mm2
		punpckhwd mm3, mm2
		punpcklwd mm5, mm6
		punpckhwd mm7, mm6
		movq mm2, mm1
		movq mm6, mm3
		punpckldq mm1, mm5
		punpckhdq mm2, mm5
		punpckldq mm3, mm7
		punpckhdq mm6, mm7
		movq mm5, qword ptr [edi]
		packuswb mm5, mm1
		movq qword ptr [eax], mm5
		movq mm7, qword ptr [edi + 0x10]
		packuswb mm7, mm2
		movq qword ptr [eax + ecx], mm7
		packuswb mm0, mm3
		packuswb mm4, mm6
		movq qword ptr [eax + ecx*2], mm0
		lea eax, [eax + ecx*4]
		movq qword ptr [eax + edx], mm4
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebp
		pop eax
	}

	__asm {
		movzx edi, word ptr resultAHi[4]
		movzx esi, word ptr resultAHi[6]
		add esi, edi
		movzx edi, word ptr resultAHi[2]
		add esi, edi
		movzx edi, word ptr resultAHi
		mov edx, dword ptr context
		mov ecx, dword ptr [edx + 0x28]
		mov eax, dword ptr block
		add esi, edi
		movzx edi, word ptr resultALo[6]
		add esi, edi
		movzx edi, word ptr resultALo[4]
		add esi, edi
		movzx edi, word ptr resultALo[2]
		add esi, edi
		movzx edi, word ptr resultALo
		add esi, edi
		mov edi, dword ptr [ecx + eax*4 - 4]
		lea ecx, [ecx + eax*4 - 4]
		add edi, esi
		movzx esi, word ptr resultBLo[4]
		mov dword ptr [ecx], edi
		mov edx, dword ptr [edx + 0x28]
		lea ecx, [edx + eax*4]
		movzx edx, word ptr resultBLo[6]
		add edx, esi
		movzx esi, word ptr resultBLo[2]
		add edx, esi
		movzx esi, word ptr resultBLo
		add edx, esi
		movzx esi, word ptr resultBHi[6]
		add edx, esi
		movzx esi, word ptr resultBHi[4]
		add edx, esi
		movzx esi, word ptr resultBHi[2]
		add edx, esi
		movzx esi, word ptr resultBHi
		add edx, esi
		mov esi, dword ptr [ecx]
		add esi, edx
		mov edx, dword ptr p3cur
		mov dword ptr [ecx], esi
	}

	__asm {
		mov esi, dword ptr p2cur
		mov ecx, dword ptr p3minus
		inc eax
		mov dword ptr block, eax
		mov eax, 8
		add esi, eax
		add edx, eax
		add ecx, eax
		mov dword ptr p3minus, ecx
		mov ecx, dword ptr block
		mov dword ptr p2cur, esi
		mov dword ptr p3cur, edx
	}

	__asm {
	label_15ab:
		add dword ptr byteIdx, 4
		cmp ecx, dword ptr endBlock
		jb label_0077
	}
label_15bb:;

}
#undef bufEsi
#undef bufEdi
#undef scratchD
#undef scratchC
#undef filterBroadcast
#undef endBlock
#undef thresholdSquared
#undef edgeBroadcast
#undef ptrA
#undef ptrB
#undef filterValPacked
#undef resultBLo
#undef resultALo
#undef resultBHi
#undef resultAHi
#undef block
#undef p2cur
#undef p3minus
#undef p3cur
#undef byteIdx
