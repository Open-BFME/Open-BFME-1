// ?Rva009BEBB0Vp6DeblockBand@@YAXPAURva009BEBB0Vp6PostProc@@PAE1IIIPAI@Z
// partial score=0.85 date=2026-09-10
// ?Rva009BEBB0Vp6DeblockBand@@YAXPAURva009BEBB0Vp6PostProc@@PAE1IIIPAI@Z
// cl: /O2
//
// Open-BFME5: VP6 postprocessor band deblock -- horizontal pass (loop 1)
// then vertical pass (loop 2) over one 8-pixel-wide fragment column strip.
// Retail 0x009BEBB0, 3721 bytes. Hand-vectorized SSE2/MMX kernel; each pass
// is real C control flow (the fragment/qIndex loop, kept live in ebx) around
// one literal __asm island transcribing retail's SIMD core byte-for-byte.
// The islands reference the surrounding C locals BY NAME so MSVC treats the
// slots as genuinely live -- with literal [esp+NNh] operands the optimizer
// cannot see the locals are used and drops/reorders stores around them.
// See reverse/re_attempts.log (0x009bebb0) for prior session analysis.

struct Rva009BEBB0Vp6PostProc
{
	unsigned char m_pad[0x24];
	unsigned int *m_fragmentQIndex;    // +0x24
	unsigned int *m_fragmentVariances; // +0x28
};

extern const unsigned short kRva012D87C0Three[8]; // retail 0x012D87C0 ({3} x8)
extern const unsigned short kRva012D87D0Four[8];  // retail 0x012D87D0 ({4} x8)

void __cdecl Rva009BEBB0Vp6DeblockBand(
	Rva009BEBB0Vp6PostProc *ctx,
	unsigned char *src,
	unsigned char *dst,
	unsigned int stride,
	unsigned int count,
	unsigned int start,
	unsigned int *qTable)
{
	volatile unsigned char *srcHome;
	unsigned char *dstPtr;
	unsigned int qIndex;
	unsigned char *srcPtr;
	__declspec(align(16)) unsigned short qv[8];
	__declspec(align(16)) unsigned short out[16];
	unsigned int end;
	__declspec(align(16)) unsigned short qsq[8];
	__declspec(align(16)) unsigned short work[80];
	unsigned int frag;

#define CTX (*(Rva009BEBB0Vp6PostProc * volatile *)&ctx)
#define PV(x) (*(volatile unsigned int *)&x)

	srcHome = src;
	srcPtr = src;
	frag = start;
	dstPtr = dst;
	end = start + count;
	qIndex = end;

	while (frag < end)
	{
		unsigned int q = qTable[ CTX->m_fragmentQIndex[ qIndex ] ];
		if (q > 3)
		{
			unsigned short qw = (unsigned short)q;
			qv[0] = qw;
			qv[1] = qw;
			qv[2] = qw;
			qv[3] = qw;
			qv[4] = qw;
			qv[5] = qw;
			qv[6] = qw;
			qv[7] = qw;

			__asm
			{
				push eax
				push ecx
				push edx
				push esi
				push edi
				movdqa xmm0, xmmword ptr qv
				movdqa xmm1, xmmword ptr kRva012D87C0Three
				pmullw xmm1, xmm0
				pmullw xmm1, xmm0
				psrlw xmm1, 5
				movdqa xmmword ptr qsq, xmm1
				mov eax, dword ptr srcPtr
				xor edx, edx
				mov esi, dword ptr dstPtr
				lea edi, work
				mov ecx, dword ptr [ebp + 14h]
				pxor xmm7, xmm7
				sub edx, ecx
				lea eax, [eax + edx*4]
				lea esi, [esi + edx*2]
				movq xmm0, qword ptr [eax + edx]
				movq xmm1, qword ptr [eax]
				punpcklbw xmm0, xmm7
				punpcklbw xmm1, xmm7
				movdqa xmmword ptr [edi], xmm0
				movdqa xmmword ptr [edi + 10h], xmm1
				movq xmm2, qword ptr [eax + ecx]
				movq xmm3, qword ptr [eax + ecx*2]
				punpcklbw xmm2, xmm7
				punpcklbw xmm3, xmm7
				movdqa xmmword ptr [edi + 20h], xmm2
				movdqa xmmword ptr [edi + 30h], xmm3
				lea eax, [eax + ecx*4]
				movq xmm0, qword ptr [eax + edx]
				movq xmm1, qword ptr [eax]
				punpcklbw xmm0, xmm7
				punpcklbw xmm1, xmm7
				movdqa xmmword ptr [edi + 40h], xmm0
				movdqa xmmword ptr [edi + 50h], xmm1
				movq xmm2, qword ptr [eax + ecx]
				movq xmm3, qword ptr [eax + ecx*2]
				punpcklbw xmm2, xmm7
				punpcklbw xmm3, xmm7
				movdqa xmmword ptr [edi + 60h], xmm2
				movdqa xmmword ptr [edi + 70h], xmm3
				lea eax, [eax + ecx*4]
				movq xmm0, qword ptr [eax + edx]
				movq xmm1, qword ptr [eax]
				punpcklbw xmm0, xmm7
				punpcklbw xmm1, xmm7
				movdqa xmmword ptr [edi + 80h], xmm0
				movdqa xmmword ptr [edi + 90h], xmm1
				pcmpeqw xmm3, xmm3
				psllw xmm3, 0Fh
				psrlw xmm3, 8
				movdqa xmm2, xmmword ptr [edi + 10h]
				movdqa xmm6, xmmword ptr [edi + 50h]
				psubw xmm2, xmm3
				psubw xmm6, xmm3
				movdqa xmm0, xmm2
				movdqa xmm4, xmm6
				pmullw xmm2, xmm2
				pmullw xmm6, xmm6
				movdqa xmm1, xmm2
				movdqa xmm5, xmm6
				movdqa xmm2, xmmword ptr [edi + 20h]
				movdqa xmm6, xmmword ptr [edi + 60h]
				psubw xmm2, xmm3
				psubw xmm6, xmm3
				paddw xmm0, xmm2
				paddw xmm4, xmm6
				pmullw xmm2, xmm2
				pmullw xmm6, xmm6
				paddw xmm1, xmm2
				paddw xmm5, xmm6
				movdqa xmm2, xmmword ptr [edi + 30h]
				movdqa xmm6, xmmword ptr [edi + 70h]
				psubw xmm2, xmm3
				psubw xmm6, xmm3
				paddw xmm0, xmm2
				paddw xmm4, xmm6
				pmullw xmm2, xmm2
				pmullw xmm6, xmm6
				paddw xmm1, xmm2
				paddw xmm5, xmm6
				movdqa xmm2, xmmword ptr [edi + 40h]
				movdqa xmm6, xmmword ptr [edi + 80h]
				psubw xmm2, xmm3
				psubw xmm6, xmm3
				paddw xmm0, xmm2
				paddw xmm4, xmm6
				pmullw xmm2, xmm2
				pmullw xmm6, xmm6
				paddw xmm1, xmm2
				paddw xmm5, xmm6
				movdqa xmm7, xmm3
				psrlw xmm7, 7
				movdqa xmm2, xmm0
				movdqa xmm6, xmm4
				paddw xmm0, xmm7
				paddw xmm4, xmm7
				psraw xmm2, 1
				psraw xmm6, 1
				psraw xmm0, 1
				psraw xmm4, 1
				pmullw xmm2, xmm0
				pmullw xmm6, xmm4
				psubw xmm1, xmm2
				psubw xmm5, xmm6
				movdqa xmm7, xmmword ptr qsq
				movdqa xmm2, xmm1
				movdqa xmmword ptr [out+10h], xmm1
				movdqa xmmword ptr [out], xmm5
				movdqa xmm6, xmm5
				psubw xmm1, xmm7
				psubw xmm5, xmm7
				psraw xmm2, 0Fh
				psraw xmm6, 0Fh
				psraw xmm1, 0Fh
				psraw xmm5, 0Fh
				movdqa xmm7, xmmword ptr [edi + 40h]
				pandn xmm2, xmm1
				pandn xmm6, xmm5
				movdqa xmm4, xmmword ptr [edi + 50h]
				pand xmm6, xmm2
				movdqa xmm2, xmm7
				psubusw xmm7, xmm4
				psubusw xmm4, xmm2
				por xmm7, xmm4
				psubw xmm7, xmmword ptr qv
				psraw xmm7, 0Fh
				pand xmm7, xmm6
				movdqa xmm5, xmmword ptr [edi]
				movdqa xmm4, xmmword ptr [edi + 10h]
				movdqa xmm3, xmm4
				movdqa xmm6, xmm5
				psubusw xmm4, xmm6
				psubusw xmm5, xmm3
				por xmm4, xmm5
				psubw xmm4, xmmword ptr qv
				psraw xmm4, 0Fh
				movdqa xmm1, xmm4
				pand xmm4, xmm6
				pandn xmm1, xmm3
				por xmm1, xmm4
				movdqa xmm4, xmmword ptr [edi + 80h]
				movdqa xmm5, xmmword ptr [edi + 90h]
				movdqa xmm3, xmm4
				movdqa xmm6, xmm5
				psubusw xmm4, xmm6
				psubusw xmm5, xmm3
				por xmm4, xmm5
				psubw xmm4, xmmword ptr qv
				psraw xmm4, 0Fh
				movdqa xmm2, xmm4
				pand xmm4, xmm6
				pandn xmm2, xmm3
				por xmm2, xmm4
				pxor xmm0, xmm0
				movdqa xmm3, xmm1
				paddw xmm3, xmm3
				paddw xmm3, xmm1
				movdqa xmm4, xmmword ptr [edi + 10h]
				paddw xmm3, xmmword ptr [edi + 20h]
				paddw xmm4, xmmword ptr [edi + 30h]
				paddw xmm3, xmmword ptr [edi + 40h]
				paddw xmm4, xmmword ptr kRva012D87D0Four
				paddw xmm3, xmm4
				movdqa xmm4, xmm3
				movdqa xmm5, xmmword ptr [edi + 10h]
				paddw xmm4, xmm5
				psllw xmm4, 1
				psubw xmm4, xmmword ptr [edi + 40h]
				paddw xmm4, xmmword ptr [edi + 50h]
				psraw xmm4, 4
				psubw xmm4, xmm5
				pand xmm4, xmm7
				paddw xmm4, xmm5
				packuswb xmm4, xmm0
				movq qword ptr [esi + edx*2], xmm4
				movdqa xmm5, xmmword ptr [edi + 20h]
				psubw xmm3, xmm1
				paddw xmm3, xmmword ptr [edi + 50h]
				movdqa xmm4, xmm5
				paddw xmm4, xmm3
				paddw xmm4, xmm4
				psubw xmm4, xmmword ptr [edi + 50h]
				paddw xmm4, xmmword ptr [edi + 60h]
				psraw xmm4, 4
				psubw xmm4, xmm5
				pand xmm4, xmm7
				paddw xmm4, xmm5
				packuswb xmm4, xmm0
				movq qword ptr [esi + edx], xmm4
				movdqa xmm5, xmmword ptr [edi + 30h]
				psubw xmm3, xmm1
				paddw xmm3, xmmword ptr [edi + 60h]
				movdqa xmm4, xmm5
				paddw xmm4, xmm3
				paddw xmm4, xmm4
				psubw xmm4, xmmword ptr [edi + 60h]
				paddw xmm4, xmmword ptr [edi + 70h]
				psraw xmm4, 4
				psubw xmm4, xmm5
				pand xmm4, xmm7
				paddw xmm4, xmm5
				packuswb xmm4, xmm0
				movq qword ptr [esi], xmm4
				movdqa xmm5, xmmword ptr [edi + 40h]
				psubw xmm3, xmm1
				paddw xmm3, xmmword ptr [edi + 70h]
				movdqa xmm4, xmm5
				paddw xmm4, xmm3
				paddw xmm4, xmm4
				paddw xmm4, xmm1
				psubw xmm4, xmmword ptr [edi + 10h]
				psubw xmm4, xmmword ptr [edi + 70h]
				paddw xmm4, xmmword ptr [edi + 80h]
				psraw xmm4, 4
				psubw xmm4, xmm5
				pand xmm4, xmm7
				paddw xmm4, xmm5
				packuswb xmm4, xmm0
				movq qword ptr [esi + ecx], xmm4
				movdqa xmm5, xmmword ptr [edi + 50h]
				psubw xmm3, xmmword ptr [edi + 10h]
				paddw xmm3, xmmword ptr [edi + 80h]
				movdqa xmm4, xmm5
				paddw xmm4, xmm3
				paddw xmm4, xmm4
				paddw xmm4, xmmword ptr [edi + 10h]
				psubw xmm4, xmmword ptr [edi + 20h]
				psubw xmm4, xmmword ptr [edi + 80h]
				paddw xmm4, xmm2
				psraw xmm4, 4
				psubw xmm4, xmm5
				pand xmm4, xmm7
				paddw xmm4, xmm5
				lea esi, [esi + ecx*4]
				packuswb xmm4, xmm0
				movq qword ptr [esi + edx*2], xmm4
				movdqa xmm5, xmmword ptr [edi + 60h]
				psubw xmm3, xmmword ptr [edi + 20h]
				paddw xmm3, xmm2
				movdqa xmm4, xmm5
				paddw xmm4, xmm3
				paddw xmm4, xmm4
				paddw xmm4, xmmword ptr [edi + 20h]
				psubw xmm4, xmmword ptr [edi + 30h]
				psraw xmm4, 4
				psubw xmm4, xmm5
				pand xmm4, xmm7
				paddw xmm4, xmm5
				packuswb xmm4, xmm0
				movq qword ptr [esi + edx], xmm4
				movdqa xmm5, xmmword ptr [edi + 70h]
				psubw xmm3, xmmword ptr [edi + 30h]
				paddw xmm3, xmm2
				movdqa xmm4, xmm5
				paddw xmm4, xmm3
				paddw xmm4, xmm4
				paddw xmm4, xmmword ptr [edi + 30h]
				psubw xmm4, xmmword ptr [edi + 40h]
				psraw xmm4, 4
				psubw xmm4, xmm5
				pand xmm4, xmm7
				paddw xmm4, xmm5
				packuswb xmm4, xmm0
				movq qword ptr [esi], xmm4
				movdqa xmm5, xmmword ptr [edi + 80h]
				psubw xmm3, xmmword ptr [edi + 40h]
				paddw xmm3, xmm2
				movdqa xmm4, xmm5
				paddw xmm4, xmm3
				paddw xmm4, xmm4
				paddw xmm4, xmmword ptr [edi + 40h]
				psubw xmm4, xmmword ptr [edi + 50h]
				psraw xmm4, 4
				psubw xmm4, xmm5
				pand xmm4, xmm7
				paddw xmm4, xmm5
				packuswb xmm4, xmm0
				movq qword ptr [esi + ecx], xmm4
				pop edi
				pop esi
				pop edx
				pop ecx
				pop eax
			}

			CTX->m_fragmentVariances[frag] += out[14] + out[15] + out[13] + out[12] + out[11] + out[10] + out[9] + out[8];
			CTX->m_fragmentVariances[qIndex] += out[7] + out[6] + out[5] + out[4] + out[3] + out[2] + out[1] + out[0];
		}
		else
		{
			__asm
			{
				push esi
				push edi
				push ecx
				mov esi, dword ptr srcPtr
				mov edi, dword ptr dstPtr
				push edx
				mov ecx, dword ptr [ebp + 14h]
				xor edx, edx
				sub edx, ecx
				lea esi, [esi + edx*4]
				movq mm0, qword ptr [esi]
				movq qword ptr [edi + edx*4], mm0
				lea edi, [edi + edx*4]
				movq mm1, qword ptr [esi + ecx]
				movq qword ptr [edi + ecx], mm1
				movq mm2, qword ptr [esi + ecx*2]
				lea esi, [esi + ecx*4]
				movq qword ptr [edi + ecx*2], mm2
				lea edi, [edi + ecx*4]
				movq mm3, qword ptr [esi + edx]
				movq qword ptr [edi + edx], mm3
				movq mm4, qword ptr [esi]
				movq mm5, qword ptr [esi + ecx]
				movq qword ptr [edi], mm4
				movq mm6, qword ptr [esi + ecx*2]
				lea esi, [esi + ecx*4]
				movq qword ptr [edi + ecx], mm5
				movq qword ptr [edi + ecx*2], mm6
				movq mm7, qword ptr [esi + edx]
				lea edi, [edi + ecx*4]
				movq qword ptr [edi + edx], mm7
				pop edx
				pop ecx
				pop edi
				pop esi
			}
		}

		srcPtr += 8;
		dstPtr += 8;
		++frag;
		++qIndex;
	}

	// --- loop 2: vertical edge pass over the already-filtered destination ---
	{
		unsigned int rewind = 8 - PV(stride) * 8 - PV(count) * 8;
		dstPtr = dstPtr + rewind;
		srcPtr = dstPtr;
		qIndex = PV(start);
		end = end - 1;

		while (qIndex < end)
		{
			unsigned int q = qTable[ CTX->m_fragmentQIndex[ qIndex + 1 ] ];
			if (q > 3)
			{
				work[0] = srcPtr[0 * (int)stride - 5];
				work[72] = srcPtr[0 * (int)stride + 4];
				work[1] = srcPtr[1 * (int)stride - 5];
				work[73] = srcPtr[1 * (int)stride + 4];
				work[2] = srcPtr[2 * (int)stride - 5];
				work[74] = srcPtr[2 * (int)stride + 4];
				work[3] = srcPtr[3 * (int)stride - 5];
				work[75] = srcPtr[3 * (int)stride + 4];
				work[4] = srcPtr[4 * (int)stride - 5];
				work[76] = srcPtr[4 * (int)stride + 4];
				work[5] = srcPtr[5 * (int)stride - 5];
				work[77] = srcPtr[5 * (int)stride + 4];
				work[6] = srcPtr[6 * (int)stride - 5];
				work[78] = srcPtr[6 * (int)stride + 4];
				work[7] = srcPtr[7 * (int)stride - 5];
				work[79] = srcPtr[7 * (int)stride + 4];

				{
					unsigned short qw = (unsigned short)q;
					qv[0] = qw;
					qv[1] = qw;
					qv[2] = qw;
					qv[3] = qw;
					qv[4] = qw;
					qv[5] = qw;
					qv[6] = qw;
					qv[7] = qw;
				}

				__asm
				{
		push eax
		push ecx
		push edx
		push esi
		push edi
		movdqa xmm0, xmmword ptr qv
		movdqa xmm1, xmmword ptr kRva012D87C0Three
		pmullw xmm1, xmm0
		pmullw xmm1, xmm0
		psrlw xmm1, 5
		movdqa xmmword ptr qsq, xmm1
		mov eax, dword ptr srcPtr
		xor edx, edx
		mov esi, dword ptr dstPtr
		sub eax, 4
		sub esi, 4
		lea edi, work
		mov ecx, dword ptr [ebp + 14h]
		sub edx, ecx
		lea esi, [esi + ecx*2]
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
		movq qword ptr [edi + 10h], mm0
		punpckhbw mm5, mm7
		movq mm0, mm1
		movq qword ptr [edi + 20h], mm5
		punpcklbw mm1, mm7
		punpckhbw mm0, mm7
		movq qword ptr [edi + 30h], mm1
		movq mm3, mm2
		movq mm5, mm4
		movq qword ptr [edi + 40h], mm0
		punpcklbw mm2, mm7
		punpckhbw mm3, mm7
		movq qword ptr [edi + 50h], mm2
		punpcklbw mm4, mm7
		punpckhbw mm5, mm7
		movq qword ptr [edi + 60h], mm3
		movq mm0, qword ptr [eax]
		movq mm1, qword ptr [eax + ecx]
		movq qword ptr [edi + 70h], mm4
		movq mm2, qword ptr [eax + ecx*2]
		lea eax, [eax + ecx*4]
		movq qword ptr [edi + 80h], mm5
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
		movq qword ptr [edi + 18h], mm0
		punpckhbw mm5, mm7
		movq mm0, mm1
		movq qword ptr [edi + 28h], mm5
		punpcklbw mm1, mm7
		punpckhbw mm0, mm7
		movq qword ptr [edi + 38h], mm1
		movq mm3, mm2
		movq mm5, mm4
		movq qword ptr [edi + 48h], mm0
		punpcklbw mm2, mm7
		punpckhbw mm3, mm7
		movq qword ptr [edi + 58h], mm2
		punpcklbw mm4, mm7
		punpckhbw mm5, mm7
		movq qword ptr [edi + 68h], mm3
		movq qword ptr [edi + 78h], mm4
		movq qword ptr [edi + 88h], mm5
		pcmpeqw xmm3, xmm3
		psllw xmm3, 0Fh
		psrlw xmm3, 8
		movdqa xmm2, xmmword ptr [edi + 10h]
		movdqa xmm6, xmmword ptr [edi + 50h]
		psubw xmm2, xmm3
		psubw xmm6, xmm3
		movdqa xmm0, xmm2
		movdqa xmm4, xmm6
		pmullw xmm2, xmm2
		pmullw xmm6, xmm6
		movdqa xmm1, xmm2
		movdqa xmm5, xmm6
		movdqa xmm2, xmmword ptr [edi + 20h]
		movdqa xmm6, xmmword ptr [edi + 60h]
		psubw xmm2, xmm3
		psubw xmm6, xmm3
		paddw xmm0, xmm2
		paddw xmm4, xmm6
		pmullw xmm2, xmm2
		pmullw xmm6, xmm6
		paddw xmm1, xmm2
		paddw xmm5, xmm6
		movdqa xmm2, xmmword ptr [edi + 30h]
		movdqa xmm6, xmmword ptr [edi + 70h]
		psubw xmm2, xmm3
		psubw xmm6, xmm3
		paddw xmm0, xmm2
		paddw xmm4, xmm6
		pmullw xmm2, xmm2
		pmullw xmm6, xmm6
		paddw xmm1, xmm2
		paddw xmm5, xmm6
		movdqa xmm2, xmmword ptr [edi + 40h]
		movdqa xmm6, xmmword ptr [edi + 80h]
		psubw xmm2, xmm3
		psubw xmm6, xmm3
		paddw xmm0, xmm2
		paddw xmm4, xmm6
		pmullw xmm2, xmm2
		pmullw xmm6, xmm6
		paddw xmm1, xmm2
		paddw xmm5, xmm6
		movdqa xmm7, xmm3
		psrlw xmm7, 7
		movdqa xmm2, xmm0
		movdqa xmm6, xmm4
		paddw xmm0, xmm7
		paddw xmm4, xmm7
		psraw xmm2, 1
		psraw xmm6, 1
		psraw xmm0, 1
		psraw xmm4, 1
		pmullw xmm2, xmm0
		pmullw xmm6, xmm4
		psubw xmm1, xmm2
		psubw xmm5, xmm6
		movdqa xmm7, xmmword ptr qsq
		movdqa xmm2, xmm1
		movdqa xmmword ptr [out+10h], xmm1
		movdqa xmmword ptr [out], xmm5
		movdqa xmm6, xmm5
		psubw xmm1, xmm7
		psubw xmm5, xmm7
		psraw xmm2, 0Fh
		psraw xmm6, 0Fh
		psraw xmm1, 0Fh
		psraw xmm5, 0Fh
		movdqa xmm7, xmmword ptr [edi + 40h]
		pandn xmm2, xmm1
		pandn xmm6, xmm5
		movdqa xmm4, xmmword ptr [edi + 50h]
		pand xmm6, xmm2
		movdqa xmm2, xmm7
		psubusw xmm7, xmm4
		psubusw xmm4, xmm2
		por xmm7, xmm4
		psubw xmm7, xmmword ptr qv
		psraw xmm7, 0Fh
		pand xmm7, xmm6
		movdqa xmm5, xmmword ptr [edi]
		movdqa xmm4, xmmword ptr [edi + 10h]
		movdqa xmm3, xmm4
		movdqa xmm6, xmm5
		psubusw xmm4, xmm6
		psubusw xmm5, xmm3
		por xmm4, xmm5
		psubw xmm4, xmmword ptr qv
		psraw xmm4, 0Fh
		movdqa xmm1, xmm4
		pand xmm4, xmm6
		pandn xmm1, xmm3
		por xmm1, xmm4
		movdqa xmm4, xmmword ptr [edi + 80h]
		movdqa xmm5, xmmword ptr [edi + 90h]
		movdqa xmm3, xmm4
		movdqa xmm6, xmm5
		psubusw xmm4, xmm6
		psubusw xmm5, xmm3
		por xmm4, xmm5
		psubw xmm4, xmmword ptr qv
		psraw xmm4, 0Fh
		movdqa xmm2, xmm4
		pand xmm4, xmm6
		pandn xmm2, xmm3
		por xmm2, xmm4
		pxor xmm0, xmm0
		movdqa xmm3, xmm1
		paddw xmm3, xmm3
		paddw xmm3, xmm1
		movdqa xmm4, xmmword ptr [edi + 10h]
		paddw xmm3, xmmword ptr [edi + 20h]
		paddw xmm4, xmmword ptr [edi + 30h]
		paddw xmm3, xmmword ptr [edi + 40h]
		paddw xmm4, xmmword ptr kRva012D87D0Four
		paddw xmm3, xmm4
		movdqa xmm4, xmm3
		movdqa xmm5, xmmword ptr [edi + 10h]
		paddw xmm4, xmm5
		psllw xmm4, 1
		psubw xmm4, xmmword ptr [edi + 40h]
		paddw xmm4, xmmword ptr [edi + 50h]
		psraw xmm4, 4
		psubw xmm4, xmm5
		pand xmm4, xmm7
		paddw xmm4, xmm5
		packuswb xmm4, xmm0
		movdq2q mm0, xmm4
		movdqa xmm5, xmmword ptr [edi + 20h]
		psubw xmm3, xmm1
		paddw xmm3, xmmword ptr [edi + 50h]
		movdqa xmm4, xmm5
		paddw xmm4, xmm3
		paddw xmm4, xmm4
		psubw xmm4, xmmword ptr [edi + 50h]
		paddw xmm4, xmmword ptr [edi + 60h]
		psraw xmm4, 4
		psubw xmm4, xmm5
		pand xmm4, xmm7
		paddw xmm4, xmm5
		packuswb xmm4, xmm0
		movdq2q mm1, xmm4
		movdqa xmm5, xmmword ptr [edi + 30h]
		psubw xmm3, xmm1
		paddw xmm3, xmmword ptr [edi + 60h]
		movdqa xmm4, xmm5
		paddw xmm4, xmm3
		paddw xmm4, xmm4
		psubw xmm4, xmmword ptr [edi + 60h]
		paddw xmm4, xmmword ptr [edi + 70h]
		psraw xmm4, 4
		psubw xmm4, xmm5
		pand xmm4, xmm7
		paddw xmm4, xmm5
		packuswb xmm4, xmm0
		movdq2q mm2, xmm4
		movdqa xmm5, xmmword ptr [edi + 40h]
		psubw xmm3, xmm1
		paddw xmm3, xmmword ptr [edi + 70h]
		movdqa xmm4, xmm5
		paddw xmm4, xmm3
		paddw xmm4, xmm4
		paddw xmm4, xmm1
		psubw xmm4, xmmword ptr [edi + 10h]
		psubw xmm4, xmmword ptr [edi + 70h]
		paddw xmm4, xmmword ptr [edi + 80h]
		psraw xmm4, 4
		psubw xmm4, xmm5
		pand xmm4, xmm7
		paddw xmm4, xmm5
		packuswb xmm4, xmm0
		movdq2q mm3, xmm4
		movdqa xmm5, xmmword ptr [edi + 50h]
		psubw xmm3, xmmword ptr [edi + 10h]
		paddw xmm3, xmmword ptr [edi + 80h]
		movdqa xmm4, xmm5
		paddw xmm4, xmm3
		paddw xmm4, xmm4
		paddw xmm4, xmmword ptr [edi + 10h]
		psubw xmm4, xmmword ptr [edi + 20h]
		psubw xmm4, xmmword ptr [edi + 80h]
		paddw xmm4, xmm2
		psraw xmm4, 4
		psubw xmm4, xmm5
		pand xmm4, xmm7
		paddw xmm4, xmm5
		packuswb xmm4, xmm0
		movdq2q mm4, xmm4
		movdqa xmm5, xmmword ptr [edi + 60h]
		psubw xmm3, xmmword ptr [edi + 20h]
		paddw xmm3, xmm2
		movdqa xmm4, xmm5
		paddw xmm4, xmm3
		paddw xmm4, xmm4
		paddw xmm4, xmmword ptr [edi + 20h]
		psubw xmm4, xmmword ptr [edi + 30h]
		psraw xmm4, 4
		psubw xmm4, xmm5
		pand xmm4, xmm7
		paddw xmm4, xmm5
		packuswb xmm4, xmm0
		movdq2q mm5, xmm4
		movdqa xmm5, xmmword ptr [edi + 70h]
		psubw xmm3, xmmword ptr [edi + 30h]
		paddw xmm3, xmm2
		movdqa xmm4, xmm5
		paddw xmm4, xmm3
		paddw xmm4, xmm4
		paddw xmm4, xmmword ptr [edi + 30h]
		psubw xmm4, xmmword ptr [edi + 40h]
		psraw xmm4, 4
		psubw xmm4, xmm5
		pand xmm4, xmm7
		paddw xmm4, xmm5
		packuswb xmm4, xmm0
		movdq2q mm6, xmm4
		movdqa xmm5, xmmword ptr [edi + 80h]
		psubw xmm3, xmmword ptr [edi + 40h]
		paddw xmm3, xmm2
		movdqa xmm4, xmm5
		paddw xmm4, xmm3
		paddw xmm4, xmm4
		paddw xmm4, xmmword ptr [edi + 40h]
		psubw xmm4, xmmword ptr [edi + 50h]
		psraw xmm4, 4
		psubw xmm4, xmm5
		pand xmm4, xmm7
		paddw xmm4, xmm5
		packuswb xmm4, xmm0
		movdq2q mm7, xmm4
		movq2dq xmm0, mm0
		movq2dq xmm1, mm1
		movq2dq xmm2, mm2
		movq2dq xmm3, mm3
		punpcklbw xmm0, xmm1
		punpcklbw xmm2, xmm3
		movdqa xmm1, xmm0
		punpcklwd xmm0, xmm2
		punpckhwd xmm1, xmm2
		movq2dq xmm4, mm4
		movq2dq xmm5, mm5
		movq2dq xmm6, mm6
		movq2dq xmm7, mm7
		punpcklbw xmm4, xmm5
		punpcklbw xmm6, xmm7
		movdqa xmm5, xmm4
		punpcklwd xmm4, xmm6
		punpckhwd xmm5, xmm6
		movdqa xmm2, xmm0
		punpckldq xmm0, xmm4
		movq qword ptr [esi + edx*2], xmm0
		psrldq xmm0, 8
		punpckhdq xmm2, xmm4
		movq qword ptr [esi + edx], xmm0
		movdqa xmm3, xmm1
		punpckldq xmm1, xmm5
		movq qword ptr [esi], xmm2
		psrldq xmm2, 8
		punpckhdq xmm3, xmm5
		movq qword ptr [esi + ecx], xmm2
		lea esi, [esi + ecx*4]
		movq qword ptr [esi + edx*2], xmm1
		movq qword ptr [esi], xmm3
		psrldq xmm1, 8
		psrldq xmm3, 8
		movq qword ptr [esi + edx], xmm1
		movq qword ptr [esi + ecx], xmm3
		pop edi
		pop esi
		pop edx
		pop ecx
		pop eax
				}

				CTX->m_fragmentVariances[qIndex] += out[14] + out[15] + out[13] + out[12] + out[11] + out[10] + out[9] + out[8];
				CTX->m_fragmentVariances[qIndex + 1] += out[6] + out[7] + out[5] + out[4] + out[3] + out[2] + out[1] + out[0];
			}

			++qIndex;
			dstPtr += 8;
			srcPtr += 8;
		}
	}
}
