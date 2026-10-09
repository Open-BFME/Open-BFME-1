// cl: /Z7
extern int *g_rva01356A9C;

extern "C" unsigned char Vp6WideAccumConst86D0[8] = {
	4u, 0u, 4u, 0u, 4u, 0u, 4u, 0u
};

extern "C" unsigned char Vp6WideAccumConst86E0[8] = {
	1u, 0u, 1u, 0u, 1u, 0u, 1u, 0u
};

extern "C" unsigned char Vp6WideAccumConst86F0[8] = {
	0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u
};

struct Rva009B9700Vp6Context
{
	unsigned char m_pad00[0xc];
	int m_modeIndex;
	unsigned char m_pad10[0x28 - 0xc - 4];
	int *m_accum;
};

// Open BFME 2: Code/GameEngine/Source/Common/Rva001CA000Vp6WideAccum.cpp
// _Rva009B9700Vp6Reconstruct
extern "C" void __cdecl Rva009B9700Vp6Reconstruct(
	Rva009B9700Vp6Context *ctx,
	unsigned char *p2,
	unsigned char *p3,
	unsigned int stride,
	unsigned int count,
	int start,
	const unsigned int *table)
{
	struct __declspec(align(16)) Rva009B9700Frame
	{
		unsigned char bufEsi[0x80];
		unsigned char bufEdi[0xa0];
		unsigned char scratch5[8];
		unsigned char pad5[8];
		unsigned char scratch4[8];
		unsigned char pad4[8];
		unsigned char scratch3[8];
		unsigned char pad3[0x14];
		unsigned int endVal;
		short brdB[4];
		unsigned char padB[0x14];
		unsigned int filterValPacked;
		short brdA[4];
		unsigned char padA[0xc];
		unsigned char *ptrA;
		unsigned char *ptrB;
		unsigned char *p3minus;
		unsigned char *p3cur;
		unsigned char *p2cur;
		unsigned int frag;
		int byteIdx;
		unsigned char resultB[8];
		unsigned char padR[8];
		unsigned char resultA[8];
	} frame;
#define bufEsi frame.bufEsi
#define bufEdi frame.bufEdi
#define scratch5 frame.scratch5
#define scratch4 frame.scratch4
#define scratch3 frame.scratch3
#define endVal frame.endVal
#define brdB frame.brdB
#define filterValPacked frame.filterValPacked
#define brdA frame.brdA
#define ptrA frame.ptrA
#define ptrB frame.ptrB
#define p3minus frame.p3minus
#define p3cur frame.p3cur
#define p2cur frame.p2cur
#define frag frame.frag
#define byteIdx frame.byteIdx
#define resultB frame.resultB
#define resultA frame.resultA

	__asm {
		mov eax, ctx
		mov eax, dword ptr [eax + 0xc]
		mov ecx, table
		mov edx, start
		shl eax, 2
		mov ecx, dword ptr [eax + ecx]
		mov filterValPacked, ecx
		mov word ptr brdA[0], cx
		mov word ptr brdA[2], cx
		mov word ptr brdA[4], cx
		mov word ptr brdA[6], cx
		mov ecx, g_rva01356A9C
		mov eax, dword ptr [eax + ecx]
		mov word ptr brdB[0], ax
		mov word ptr brdB[2], ax
		mov word ptr brdB[4], ax
		mov word ptr brdB[6], ax
	}

	__asm {
		mov eax, dword ptr [ebx + 18h]
		add eax, edx
		cmp edx, eax
		mov dword ptr frag, edx
		mov dword ptr endVal, eax
		jae Rva009B9700_empty
	}

	__asm {
		mov edx, dword ptr [ebx + 0ch]
		lea ecx, [eax*4]
		mov eax, dword ptr [ebx + 10h]
		mov dword ptr byteIdx, ecx
		mov ecx, dword ptr [ebx + 14h]
		mov dword ptr p2cur, edx
		lea edx, [ecx*8]
		mov dword ptr p3cur, eax
		sub eax, edx
		mov dword ptr p3minus, eax
	}

	__asm {
	vp6_loop_body:
		mov eax, dword ptr p2cur
		mov ecx, dword ptr p3cur
		mov dword ptr ptrA, eax
		mov dword ptr ptrB, ecx
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
		mov ecx, dword ptr [ebx + 0x14]
		movd mm5, eax
		mov eax, dword ptr ptrA
		punpcklwd mm5, mm5
		lea esi, bufEsi
		punpckldq mm5, mm5
		sub edx, ecx
		movq mm6, mm5
		paddw mm6, mm5
		paddw mm6, mm5
		packuswb mm5, mm5
		movq qword ptr brdA, mm5
		psraw mm6, 2
		packuswb mm6, mm6
		lea edi, bufEdi
		pxor mm7, mm7
		psubb mm6, qword ptr Vp6WideAccumConst86F0
		lea eax, [eax + edx*4]
		movq mm0, qword ptr [eax + edx]
		movq mm1, mm0
		punpcklbw mm0, mm7
		movq mm4, mm1
		movq qword ptr scratch3, mm6
		movq mm2, qword ptr [eax]
		punpckhbw mm1, mm7
		movq qword ptr [edi], mm0
		movq mm5, mm2
		movq mm3, mm2
		movq qword ptr [edi + 8], mm1
		movq mm0, qword ptr [eax + ecx]
		psubusb mm5, mm4
		psubusb mm4, mm2
		punpcklbw mm2, mm7
		por mm4, mm5
		movq qword ptr [edi + 0x10], mm2
		movq mm6, mm3
		punpckhbw mm3, mm7
		movq qword ptr [edi + 0x18], mm3
		movq mm1, mm0
		punpcklbw mm0, mm7
		movq qword ptr [edi + 0x20], mm0
		movq mm2, qword ptr [eax + ecx*2]
		movq mm5, mm1
		psubusb mm5, mm6
		psubusb mm6, mm1
		por mm5, mm6
		movq mm6, mm1
		punpckhbw mm1, mm7
		movq mm3, mm2
		movq qword ptr [edi + 0x28], mm1
		paddusb mm4, mm5
		movq mm5, mm2
		psubusb mm5, mm6
		psubusb mm6, mm2
		por mm5, mm6
		movq mm6, mm2
		punpcklbw mm2, mm7
		lea eax, [eax + ecx*4]
		punpckhbw mm3, mm7
		movq mm0, qword ptr [eax + edx]
		movq qword ptr [edi + 0x30], mm2
		paddusb mm4, mm5
		movq mm5, mm0
		movq qword ptr [edi + 0x38], mm3
		movq mm1, mm0
		psubusb mm5, mm6
		psubusb mm6, mm1
		punpcklbw mm0, mm7
		por mm5, mm6
		movq qword ptr [edi + 0x40], mm0
		movq mm6, mm1
		punpckhbw mm1, mm7
		movq qword ptr [edi + 0x48], mm1
		movq mm0, qword ptr [eax]
		paddusb mm4, mm5
		movq qword ptr resultA, mm4
		movq mm5, qword ptr scratch3
		psubb mm4, qword ptr Vp6WideAccumConst86F0
		pcmpgtb mm5, mm4
		movq mm1, mm0
		punpcklbw mm0, mm7
		movq mm4, mm1
		movq qword ptr [edi + 0x50], mm0
		psubusb mm4, mm6
		psubusb mm6, mm1
		movq mm0, qword ptr [eax + ecx]
		movq mm3, qword ptr brdA
		por mm4, mm6
		movq mm6, mm1
		psubb mm3, qword ptr Vp6WideAccumConst86F0
		psubb mm4, qword ptr Vp6WideAccumConst86F0
		pcmpgtb mm3, mm4
		punpckhbw mm1, mm7
		movq mm4, mm0
		pand mm5, mm3
		movq qword ptr [edi + 0x58], mm1
		movq mm1, mm0
		psubusb mm4, mm6
		punpcklbw mm0, mm7
		psubusb mm6, mm1
		movq qword ptr [edi + 0x60], mm0
		por mm4, mm6
		movq mm2, qword ptr [eax + ecx*2]
		movq mm6, mm1
		lea eax, [eax + ecx*4]
		punpckhbw mm1, mm7
		movq mm0, mm2
		movq qword ptr [edi + 0x68], mm1
		movq mm3, mm0
		movq mm1, qword ptr [eax + edx]
		punpcklbw mm2, mm7
		psubusb mm3, mm6
		psubusb mm6, mm0
		por mm3, mm6
		movq qword ptr [edi + 0x70], mm2
		movq mm6, mm0
		punpckhbw mm0, mm7
		paddusb mm4, mm3
		movq mm2, mm1
		movq mm3, mm1
		movq qword ptr [edi + 0x78], mm0
		punpcklbw mm1, mm7
		movq mm0, qword ptr [eax]
		psubusb mm3, mm6
		psubusb mm6, mm2
		por mm3, mm6
		movq qword ptr [edi + 0x80], mm1
		movq mm6, mm2
		punpckhbw mm2, mm7
		paddusb mm4, mm3
		movq mm1, mm0
		movq mm3, mm0
		movq qword ptr [edi + 0x88], mm2
		punpcklbw mm0, mm7
		psubusb mm3, mm6
		movq qword ptr [edi + 0x90], mm0
		psubusb mm6, mm1
		por mm3, mm6
		punpckhbw mm1, mm7
		paddusb mm4, mm3
		movq qword ptr resultB, mm4
		movq mm6, qword ptr scratch3
		psubb mm4, qword ptr Vp6WideAccumConst86F0
		movq qword ptr [edi + 0x98], mm1
		pcmpgtb mm6, mm4
		pand mm6, mm5
		movq mm0, mm6
		movq mm7, mm6
		punpckhbw mm0, mm6
		punpcklbw mm7, mm6
		movq mm1, qword ptr brdB
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
		movq qword ptr scratch5, mm1
		punpcklbw mm2, mm6
		movq qword ptr scratch4, mm2
		movq mm3, qword ptr [edi]
		movq mm2, qword ptr [edi + 0x90]
		movq mm1, mm3
		paddw mm3, mm3
		movq mm4, qword ptr [edi + 0x10]
		paddw mm3, mm1
		paddw mm3, qword ptr [edi + 0x20]
		paddw mm4, qword ptr [edi + 0x30]
		paddw mm3, qword ptr [edi + 0x40]
		paddw mm4, qword ptr Vp6WideAccumConst86D0
		paddw mm3, mm4
		movq mm4, mm3
		movq mm5, qword ptr [edi + 0x10]
		paddw mm4, mm5
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi], mm4
		movq mm5, qword ptr [edi + 0x20]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x50]
		movq mm4, mm5
		paddw mm4, mm3
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x10], mm4
		movq mm5, qword ptr [edi + 0x30]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x60]
		movq mm4, mm5
		paddw mm4, mm3
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x20], mm4
		movq mm5, qword ptr [edi + 0x40]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x70]
		movq mm4, mm5
		paddw mm4, mm3
		movq mm5, qword ptr scratch5
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x30], mm4
		movq mm5, qword ptr [edi + 0x50]
		psubw mm3, qword ptr [edi + 0x10]
		paddw mm3, qword ptr [edi + 0x80]
		movq mm4, mm5
		paddw mm4, mm3
		movq mm5, qword ptr scratch4
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x40], mm4
		movq mm5, qword ptr [edi + 0x60]
		psubw mm3, qword ptr [edi + 0x20]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x50], mm4
		movq mm5, qword ptr [edi + 0x70]
		psubw mm3, qword ptr [edi + 0x30]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x60], mm4
		movq mm5, qword ptr [edi + 0x80]
		psubw mm3, qword ptr [edi + 0x40]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x70], mm4
		add edi, 8
		add esi, 8
		movq mm1, qword ptr brdB
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
		movq qword ptr scratch5, mm1
		punpcklbw mm2, mm6
		movq qword ptr scratch4, mm2
		movq mm3, qword ptr [edi]
		movq mm2, qword ptr [edi + 0x90]
		movq mm1, mm3
		paddw mm3, mm3
		movq mm4, qword ptr [edi + 0x10]
		paddw mm3, mm1
		paddw mm3, qword ptr [edi + 0x20]
		paddw mm4, qword ptr [edi + 0x30]
		paddw mm3, qword ptr [edi + 0x40]
		paddw mm4, qword ptr Vp6WideAccumConst86D0
		paddw mm3, mm4
		movq mm4, mm3
		movq mm5, qword ptr [edi + 0x10]
		paddw mm4, mm5
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi], mm4
		movq mm5, qword ptr [edi + 0x20]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x50]
		movq mm4, mm5
		paddw mm4, mm3
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x10], mm4
		movq mm5, qword ptr [edi + 0x30]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x60]
		movq mm4, mm5
		paddw mm4, mm3
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x20], mm4
		movq mm5, qword ptr [edi + 0x40]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x70]
		movq mm4, mm5
		paddw mm4, mm3
		movq mm5, qword ptr scratch5
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x30], mm4
		movq mm5, qword ptr [edi + 0x50]
		psubw mm3, qword ptr [edi + 0x10]
		paddw mm3, qword ptr [edi + 0x80]
		movq mm4, mm5
		paddw mm4, mm3
		movq mm5, qword ptr scratch4
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x40], mm4
		movq mm5, qword ptr [edi + 0x60]
		psubw mm3, qword ptr [edi + 0x20]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x50], mm4
		movq mm5, qword ptr [edi + 0x70]
		psubw mm3, qword ptr [edi + 0x30]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x60], mm4
		movq mm5, qword ptr [edi + 0x80]
		psubw mm3, qword ptr [edi + 0x40]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		psraw mm4, 3
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
		movzx edi, byte ptr resultA[6]
		movzx esi, byte ptr resultA[7]
		add esi, edi
		movzx edi, byte ptr resultA[5]
		add esi, edi
		movzx edi, byte ptr resultA[4]
		add esi, edi
		movzx edi, byte ptr resultA[3]
		mov edx, ctx
		mov eax, dword ptr [edx + 28h]
		mov ecx, frag
		add esi, edi
		movzx edi, byte ptr resultA[2]
		add esi, edi
		movzx edi, byte ptr resultA[1]
		add esi, edi
		movzx edi, byte ptr resultA[0]
		add esi, edi
		mov edi, dword ptr [eax + ecx*4]
		add edi, esi
		movzx esi, byte ptr resultB[6]
		lea eax, [eax + ecx*4]
		mov dword ptr [eax], edi
		mov edx, dword ptr [edx + 28h]
		mov eax, byteIdx
		add eax, edx
		movzx edx, byte ptr resultB[7]
		add edx, esi
		movzx esi, byte ptr resultB[5]
		add edx, esi
		movzx esi, byte ptr resultB[4]
		add edx, esi
		movzx esi, byte ptr resultB[3]
		add edx, esi
		movzx esi, byte ptr resultB[2]
		add edx, esi
		movzx esi, byte ptr resultB[1]
		add edx, esi
		movzx esi, byte ptr resultB[0]
		add edx, esi
		add dword ptr [eax], edx
	}

	__asm {
		cmp ecx, start
		jne vp6_second_block
		mov edi, p2cur
		mov esi, p3cur
		mov edx, p3minus
		mov eax, 8
		inc ecx
		add edi, eax
		add esi, eax
		add edx, eax
		mov frag, ecx
		mov p2cur, edi
		mov p3cur, esi
		mov p3minus, edx
		jmp vp6_loop_latch
	vp6_second_block:
	}
	__asm {
		mov eax, p3minus
		movzx cx, byte ptr [eax - 5]
		movzx dx, byte ptr [eax + 4]
		mov word ptr bufEdi[090h], dx
		mov word ptr bufEdi[0], cx
		mov ecx, stride
		movzx dx, byte ptr [eax + ecx - 5]
		mov word ptr bufEdi[2], dx
		movzx dx, byte ptr [eax + ecx + 4]
		mov word ptr bufEdi[092h], dx
		movzx dx, byte ptr [eax + ecx*2 - 5]
		mov word ptr bufEdi[4], dx
		movzx dx, byte ptr [eax + ecx*2 + 4]
		mov word ptr bufEdi[094h], dx
		lea edx, [ecx + ecx*2]
		movzx si, byte ptr [eax + edx - 5]
		movzx dx, byte ptr [eax + edx + 4]
		mov word ptr bufEdi[096h], dx
		movzx dx, byte ptr [eax + ecx*4 - 5]
		mov word ptr bufEdi[8], dx
		movzx dx, byte ptr [eax + ecx*4 + 4]
		mov word ptr bufEdi[098h], dx
		lea edx, [ecx + ecx*4]
		mov word ptr bufEdi[6], si
		movzx si, byte ptr [eax + edx - 5]
		movzx dx, byte ptr [eax + edx + 4]
		mov word ptr bufEdi[09ah], dx
		lea edx, [ecx + ecx*2]
		imul ecx, ecx, 7
		shl edx, 1
		mov word ptr bufEdi[0ah], si
		movzx si, byte ptr [eax + edx - 5]
		movzx dx, byte ptr [eax + edx + 4]
		mov word ptr bufEdi[09ch], dx
		movzx dx, byte ptr [eax + ecx - 5]
		mov ptrB, eax
		mov ptrA, eax
		movzx ax, byte ptr [eax + ecx + 4]
		mov word ptr bufEdi[0ch], si
		mov word ptr bufEdi[0eh], dx
		mov word ptr bufEdi[09eh], ax
	}
	__asm {
		push eax
		push ebp
		mov eax, dword ptr filterValPacked
		movd mm0, eax
		push ecx
		punpcklwd mm0, mm0
		punpckldq mm0, mm0
		push edx
		movq mm1, mm0
		paddw mm1, mm0
		push esi
		paddw mm1, mm0
		packuswb mm0, mm0
		push edi
		movq qword ptr brdA, mm0
		psraw mm1, 2
		packuswb mm1, mm1
		psubb mm1, qword ptr Vp6WideAccumConst86F0
		movq qword ptr scratch3, mm1
		mov eax, dword ptr ptrA
		xor edx, edx
		sub eax, 4
		lea esi, bufEsi
		lea edi, bufEdi
		mov ecx, dword ptr [ebx + 0x14]
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
		movq mm0, qword ptr [edi]
		movq mm1, qword ptr [edi + 0x10]
		movq mm2, qword ptr [edi + 0x20]
		packuswb mm0, qword ptr [edi + 8]
		packuswb mm1, qword ptr [edi + 0x18]
		packuswb mm2, qword ptr [edi + 0x28]
		movq mm3, qword ptr [edi + 0x30]
		movq mm4, qword ptr [edi + 0x40]
		packuswb mm3, qword ptr [edi + 0x38]
		packuswb mm4, qword ptr [edi + 0x48]
		movq mm5, mm1
		movq mm6, mm2
		psubusb mm5, mm0
		psubusb mm0, mm1
		por mm0, mm5
		psubusb mm6, mm1
		psubusb mm1, mm2
		movq mm5, mm3
		por mm1, mm6
		psubusb mm5, mm2
		psubusb mm2, mm3
		movq mm6, mm4
		por mm2, mm5
		psubusb mm6, mm3
		psubusb mm3, mm4
		por mm3, mm6
		paddusb mm0, mm1
		paddusb mm2, mm3
		movq mm7, qword ptr scratch3
		paddusb mm0, mm2
		movq qword ptr resultA, mm0
		movq mm6, mm4
		psubb mm0, qword ptr Vp6WideAccumConst86F0
		pcmpgtb mm7, mm0
		movq mm5, qword ptr [edi + 0x50]
		movq mm1, qword ptr [edi + 0x60]
		movq mm2, qword ptr [edi + 0x70]
		packuswb mm5, qword ptr [edi + 0x58]
		packuswb mm1, qword ptr [edi + 0x68]
		packuswb mm2, qword ptr [edi + 0x78]
		movq mm3, qword ptr [edi + 0x80]
		movq mm4, qword ptr [edi + 0x90]
		packuswb mm3, qword ptr [edi + 0x88]
		packuswb mm4, qword ptr [edi + 0x98]
		movq mm0, mm5
		psubusb mm5, mm6
		psubusb mm6, mm0
		por mm5, mm6
		movq mm6, qword ptr brdA
		psubb mm5, qword ptr Vp6WideAccumConst86F0
		psubb mm6, qword ptr Vp6WideAccumConst86F0
		pcmpgtb mm6, mm5
		movq mm5, mm1
		pand mm7, mm6
		movq mm6, mm2
		psubusb mm5, mm0
		psubusb mm0, mm1
		por mm0, mm5
		psubusb mm6, mm1
		psubusb mm1, mm2
		movq mm5, mm3
		por mm1, mm6
		psubusb mm5, mm2
		psubusb mm2, mm3
		movq mm6, mm4
		por mm2, mm5
		psubusb mm6, mm3
		psubusb mm3, mm4
		por mm3, mm6
		paddusb mm0, mm1
		paddusb mm2, mm3
		movq mm6, qword ptr scratch3
		paddusb mm0, mm2
		movq qword ptr resultB, mm0
		psubb mm0, qword ptr Vp6WideAccumConst86F0
		pcmpgtb mm6, mm0
		pand mm6, mm7
		movq mm0, mm6
		movq mm7, mm6
		punpckhbw mm0, mm6
		punpcklbw mm7, mm6
		movq mm1, qword ptr brdB
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
		movq qword ptr scratch5, mm1
		punpcklbw mm2, mm6
		movq qword ptr scratch4, mm2
		movq mm3, qword ptr [edi]
		movq mm2, qword ptr [edi + 0x90]
		movq mm1, mm3
		paddw mm3, mm3
		movq mm4, qword ptr [edi + 0x10]
		paddw mm3, mm1
		paddw mm3, qword ptr [edi + 0x20]
		paddw mm4, qword ptr [edi + 0x30]
		paddw mm3, qword ptr [edi + 0x40]
		paddw mm4, qword ptr Vp6WideAccumConst86D0
		paddw mm3, mm4
		movq mm4, mm3
		movq mm5, qword ptr [edi + 0x10]
		paddw mm4, mm5
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi], mm4
		movq mm5, qword ptr [edi + 0x20]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x50]
		movq mm4, mm5
		paddw mm4, mm3
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x10], mm4
		movq mm5, qword ptr [edi + 0x30]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x60]
		movq mm4, mm5
		paddw mm4, mm3
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x20], mm4
		movq mm5, qword ptr [edi + 0x40]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x70]
		movq mm4, mm5
		paddw mm4, mm3
		movq mm5, qword ptr scratch5
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x30], mm4
		movq mm5, qword ptr [edi + 0x50]
		psubw mm3, qword ptr [edi + 0x10]
		paddw mm3, qword ptr [edi + 0x80]
		movq mm4, mm5
		paddw mm4, mm3
		movq mm5, qword ptr scratch4
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x40], mm4
		movq mm5, qword ptr [edi + 0x60]
		psubw mm3, qword ptr [edi + 0x20]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x50], mm4
		movq mm5, qword ptr [edi + 0x70]
		psubw mm3, qword ptr [edi + 0x30]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x60], mm4
		movq mm5, qword ptr [edi + 0x80]
		psubw mm3, qword ptr [edi + 0x40]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm7
		paddw mm4, mm5
		movq qword ptr [esi + 0x70], mm4
		add edi, 8
		add esi, 8
		movq mm1, qword ptr brdB
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
		movq qword ptr scratch5, mm1
		punpcklbw mm2, mm6
		movq qword ptr scratch4, mm2
		movq mm3, qword ptr [edi]
		movq mm2, qword ptr [edi + 0x90]
		movq mm1, mm3
		paddw mm3, mm3
		movq mm4, qword ptr [edi + 0x10]
		paddw mm3, mm1
		paddw mm3, qword ptr [edi + 0x20]
		paddw mm4, qword ptr [edi + 0x30]
		paddw mm3, qword ptr [edi + 0x40]
		paddw mm4, qword ptr Vp6WideAccumConst86D0
		paddw mm3, mm4
		movq mm4, mm3
		movq mm5, qword ptr [edi + 0x10]
		paddw mm4, mm5
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi], mm4
		movq mm5, qword ptr [edi + 0x20]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x50]
		movq mm4, mm5
		paddw mm4, mm3
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x10], mm4
		movq mm5, qword ptr [edi + 0x30]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x60]
		movq mm4, mm5
		paddw mm4, mm3
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x20], mm4
		movq mm5, qword ptr [edi + 0x40]
		psubw mm3, mm1
		paddw mm3, qword ptr [edi + 0x70]
		movq mm4, mm5
		paddw mm4, mm3
		movq mm5, qword ptr scratch5
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x30], mm4
		movq mm5, qword ptr [edi + 0x50]
		psubw mm3, qword ptr [edi + 0x10]
		paddw mm3, qword ptr [edi + 0x80]
		movq mm4, mm5
		paddw mm4, mm3
		movq mm5, qword ptr scratch4
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x40], mm4
		movq mm5, qword ptr [edi + 0x60]
		psubw mm3, qword ptr [edi + 0x20]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x50], mm4
		movq mm5, qword ptr [edi + 0x70]
		psubw mm3, qword ptr [edi + 0x30]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		psraw mm4, 3
		psubw mm4, mm5
		pand mm4, mm0
		paddw mm4, mm5
		movq qword ptr [esi + 0x60], mm4
		movq mm5, qword ptr [edi + 0x80]
		psubw mm3, qword ptr [edi + 0x40]
		paddw mm3, mm2
		movq mm4, mm5
		paddw mm4, mm3
		psraw mm4, 3
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
		movzx edi, byte ptr resultA[6]
		movzx esi, byte ptr resultA[7]
		add esi, edi
		movzx edi, byte ptr resultA[5]
		add esi, edi
		movzx edi, byte ptr resultA[4]
		mov edx, ctx
		mov ecx, dword ptr [edx + 28h]
		add esi, edi
		movzx edi, byte ptr resultA[3]
		mov eax, frag
		add esi, edi
		movzx edi, byte ptr resultA[2]
		add esi, edi
		movzx edi, byte ptr resultA[1]
		add esi, edi
		movzx edi, byte ptr resultA[0]
		add esi, edi
		mov edi, dword ptr [ecx + eax*4 - 4]
		add edi, esi
		movzx esi, byte ptr resultB[6]
		lea ecx, [ecx + eax*4 - 4]
		mov dword ptr [ecx], edi
		mov edx, dword ptr [edx + 28h]
		lea ecx, [edx + eax*4]
		movzx edx, byte ptr resultB[7]
		add edx, esi
		movzx esi, byte ptr resultB[5]
		add edx, esi
		movzx esi, byte ptr resultB[4]
		add edx, esi
		movzx esi, byte ptr resultB[3]
		add edx, esi
		movzx esi, byte ptr resultB[2]
		add edx, esi
		movzx esi, byte ptr resultB[1]
		add edx, esi
		movzx esi, byte ptr resultB[0]
		add edx, esi
		mov esi, dword ptr [ecx]
		add esi, edx
		mov edx, p3cur
		mov dword ptr [ecx], esi
	}
	__asm {
		mov esi, p2cur
		mov ecx, p3minus
		inc eax
		mov frag, eax
		mov eax, 8
		add esi, eax
		add edx, eax
		add ecx, eax
		mov p3minus, ecx
		mov ecx, frag
		mov p2cur, esi
		mov p3cur, edx
	}
	__asm {
	vp6_loop_latch:
		add byteIdx, 4
		cmp ecx, endVal
		jb vp6_loop_body
	}

	__asm { Rva009B9700_empty: }
	return;

}

#undef bufEsi
#undef bufEdi
#undef scratch5
#undef scratch4
#undef scratch3
#undef endVal
#undef brdB
#undef filterValPacked
#undef brdA
#undef ptrA
#undef ptrB
#undef p3minus
#undef p3cur
#undef p2cur
#undef frag
#undef byteIdx
#undef resultB
#undef resultA
