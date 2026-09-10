// _Rva009B9700Vp6Reconstruct
// partial score=0.15 date=2026-09-10
// cl: /O2 /Z7
//
// VP6 wide-region reconstruct/accumulate: per-fragment loop-filter strength
// pass over an 8x8 block strip, feeding a per-plane accumulator array. Genuine
// hand-vectorized MMX retail body, same /Z7 aligned-frame prologue and
// push-eax/ebp/ecx/edx/esi/edi island idiom as BfmeConv9BD750.cpp and the
// stashed reverse/attempts/0x009bebb0.cpp band-deblock sibling (same ctx
// field offsets: +0xc mode index, +0x28 int* accumulator array). Structure
// derived fresh via build/scaffold.py this session -- see reverse/re_attempts.log
// (0x009B9700) for the full derivation and the branch-direction correction.
//
// One outer for(frag=start;frag<end;frag++) loop. Every iteration runs
// island1 (always) plus its scalar byte-sum reduction into accum[frag].
// Every iteration EXCEPT the first (frag==start) additionally builds an
// 8-tap near/far reference table from the row three positions back
// (p3minus = p3 - stride*8) and runs island2 plus a second reduction that
// corrects accum[frag-1] and a second accumulator slot at byte offset
// byteIdx (which starts at end*4 and advances by 4/iteration in lockstep
// with frag, landing outside the [start,end) index range -- a distinct
// per-plane totals region of the same array, not accum[frag]).

extern int *g_rva01356A9C;

extern "C" unsigned char Vp6WideAccumConst86D0[8]; // retail VA 0x012D86D0
extern "C" unsigned char Vp6WideAccumConst86E0[8]; // retail VA 0x012D86E0
extern "C" unsigned char Vp6WideAccumConst86F0[8]; // retail VA 0x012D86F0

struct Rva009B9700Vp6Context
{
	unsigned char m_pad00[0xc];
	int m_modeIndex;         // +0xc
	unsigned char m_pad10[0x28 - 0xc - 4];
	int *m_accum;             // +0x28
};

extern "C" void __cdecl Rva009B9700Vp6Reconstruct(
	Rva009B9700Vp6Context *ctx,
	unsigned char *p2,
	unsigned char *p3,
	int stride,
	int count,
	int start,
	int *table)
{
	__declspec(align(16)) unsigned char bufEsi[0x80];
	__declspec(align(8)) unsigned char bufEdi[0xa0];
	unsigned char scratch5[8];
	unsigned char scratch4[8];
	unsigned char scratch3[8];
	unsigned char resultA[8];
	unsigned char resultB[8];
	short brdA[4];
	short brdB[4];
	unsigned int filterValPacked;
	int endVal;
	unsigned char *ptrA;
	unsigned char *ptrB;
	unsigned char *p3minus;
	unsigned char *p3cur;
	unsigned char *p2cur;
	int frag;
	int byteIdx;

	int modeIndex4 = ctx->m_modeIndex << 2;
	int filterValRaw = *(int *)((char *)table + modeIndex4);
	int edgeValRaw = *(int *)((char *)g_rva01356A9C + modeIndex4);

	filterValPacked = (unsigned int)filterValRaw;
	brdA[0] = brdA[1] = brdA[2] = brdA[3] = (short)filterValRaw;
	brdB[0] = brdB[1] = brdB[2] = brdB[3] = (short)edgeValRaw;

	endVal = start + count;

	if (start < endVal) {
		p2cur = p2;
		byteIdx = endVal * 4;
		p3cur = p3;
		p3minus = p3 - stride * 8;

		frag = start;
		while (frag < endVal) {
			ptrA = p2cur;
			ptrB = p3cur;

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

			{
				unsigned int sum1 = resultA[0] + resultA[1] + resultA[2] + resultA[3]
					+ resultA[4] + resultA[5] + resultA[6] + resultA[7];
				int *arr = ctx->m_accum;
				arr[frag] += sum1;
				{
					unsigned int sum2 = resultB[0] + resultB[1] + resultB[2] + resultB[3]
						+ resultB[4] + resultB[5] + resultB[6] + resultB[7];
					int *arr2 = ctx->m_accum;
					*(int *)((char *)arr2 + byteIdx) += sum2;
				}
			}

			if (frag == start) {
				p2cur += 8;
				p3cur += 8;
				p3minus += 8;
				frag++;
			} else {
				unsigned char *col = p3minus;
				int s = stride;
				((unsigned short *)bufEdi)[0] = *(unsigned char *)(col - 5);
				((unsigned short *)bufEdi)[0x90 / 2] = *(unsigned char *)(col + 4);
				((unsigned short *)bufEdi)[1] = *(unsigned char *)(col + s - 5);
				((unsigned short *)bufEdi)[0x92 / 2] = *(unsigned char *)(col + s + 4);
				((unsigned short *)bufEdi)[2] = *(unsigned char *)(col + s * 2 - 5);
				((unsigned short *)bufEdi)[0x94 / 2] = *(unsigned char *)(col + s * 2 + 4);
				((unsigned short *)bufEdi)[3] = *(unsigned char *)(col + s * 3 - 5);
				((unsigned short *)bufEdi)[0x96 / 2] = *(unsigned char *)(col + s * 3 + 4);
				((unsigned short *)bufEdi)[4] = *(unsigned char *)(col + s * 4 - 5);
				((unsigned short *)bufEdi)[0x98 / 2] = *(unsigned char *)(col + s * 4 + 4);
				((unsigned short *)bufEdi)[5] = *(unsigned char *)(col + s * 5 - 5);
				((unsigned short *)bufEdi)[0x9a / 2] = *(unsigned char *)(col + s * 5 + 4);
				((unsigned short *)bufEdi)[6] = *(unsigned char *)(col + s * 6 - 5);
				((unsigned short *)bufEdi)[0x9c / 2] = *(unsigned char *)(col + s * 6 + 4);
				ptrB = ptrA = p3minus;
				((unsigned short *)bufEdi)[7] = *(unsigned char *)(col + s * 7 - 5);
				((unsigned short *)bufEdi)[0x9e / 2] = *(unsigned char *)(col + s * 7 + 4);

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

				{
					unsigned int sum1 = resultA[0] + resultA[1] + resultA[2] + resultA[3]
						+ resultA[4] + resultA[5] + resultA[6] + resultA[7];
					int *arr = ctx->m_accum;
					arr[frag - 1] += sum1;
					{
						unsigned int sum2 = resultB[0] + resultB[1] + resultB[2] + resultB[3]
							+ resultB[4] + resultB[5] + resultB[6] + resultB[7];
						int *arr2 = ctx->m_accum;
						*(int *)((char *)arr2 + byteIdx) += sum2;
					}
				}

				p2cur += 8;
				p3cur += 8;
				p3minus += 8;
				frag++;
			}
			byteIdx += 4;
		}
	}
}
