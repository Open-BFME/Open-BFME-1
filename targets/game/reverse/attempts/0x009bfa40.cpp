// _DeblockLoopFilteredBand_WMT
// partial score=0.18 date=2026-09-10
// _DeblockLoopFilteredBand_WMT
// cl: /O2
//
// Open-BFME5: VP6 postprocessor "loop filtered band" deblock, retail
// 0x009BFA40, 4068 bytes. Same ctx shape as the sibling Rva009BEBB0Vp6
// DeblockBand (0x009BEBB0): m_fragmentQIndex pointer at +0x24,
// m_fragmentVariances pointer at +0x28, PLUS one extra field m_tableIndex
// (int) at +0xc feeding g_rva01356A9C[ctx->m_tableIndex] whose low word is
// broadcast unconditionally into an 8-word buffer before the loop even tests
// fragment<end -- confirmed from the entry bytes: eax=[ebp+8](ctx);
// edx=[eax+0xc](m_tableIndex); eax=[0x1356a9c][edx] (g_rva01356A9C lookup);
// then eight `mov word ptr [esp+N],ax` stores. See reverse/re_attempts.log
// (0x009bfa40) for the byte-level recon this session builds on.
//
// STATUS this session: corrects the ctx field model (the 0.12 predecessor's
// POSTPROC_INSTANCE_9BFA40 had m_tableIndex mis-typed as UINT8* and no
// m_fragmentQIndex/m_fragmentVariances distinction) and confirms the entry
// broadcast idiom compiles with the right instruction shape when qv is a
// real align(16) array with volatile-cast stores (forces the aligned frame
// AND keeps the dead broadcast live). Still a scalar reconstruction of the
// filter body, NOT the masmified SIMD islands -- tools/probe.py against
// retail: 2673/4068 non-reloc bytes differ, first real divergence at +0x6
// (sub esp,0x144 vs our smaller frame; register roles differ, structurally
// the retail loop is confirmed to carry TWO loop indices -- frag from
// `start` and qIndex from `end` -- both incrementing together, matching the
// sibling 0x009BEBB0's loop1 exactly, including the variance-target order
// ctx->m_fragmentVariances[frag] / [qIndex]). Recon for the next session:
// the q>3 SIMD island (+0xac..+0x704 relative to the function, ~1624 bytes)
// is byte-for-byte parallel to 0x009BEBB0's loop1 kernel (same q-broadcast,
// 8-row unpack into a work[80]-shaped buffer, same variance-threshold mask)
// PLUS an extra correction step not present in the sibling: outputs 4 and 5
// (the two samples straddling the actual block edge) get an additional
// clip/blend pass using a {1}x8-word constant at retail 0x012D8820 (and the
// existing kRva012D87D0Four {4}x8 at 0x012D87D0) before the shared 8-tap
// filter runs -- reverse/attempts/history for this rva has the masmified
// dump of that island via build/masmify.py (rewritten this session, still
// present at build/masmify.py, gitignored). A second real-control-flow gate
// `if (frag != start) { <~2202-byte vertical/edge island> }` follows the
// horizontal pass every iteration (confirmed by two DISTINCT copies of the
// pointer-bump tail in the retail bytes, one inside the skip branch, one
// after the gated island -- rules out a shared-tail early-continue reading
// as the same code, source likely uses an early `continue` after bumping
// pointers when frag==start). That island reads already-filtered dst bytes
// through a pointer initialised to `dst - stride*8` (kept in ebx across the
// whole loop) at offsets ebx-5/ebx+4 -- not yet transcribed.

typedef unsigned char UINT8;
typedef unsigned int UINT32;

struct Rva009BFA40Ctx
{
	unsigned char m_pad0[0xC];
	int m_tableIndex;                  // +0x0c
	unsigned char m_pad1[0x24 - 0x10];
	unsigned int *m_fragmentQIndex;    // +0x24
	unsigned int *m_fragmentVariances; // +0x28
};

extern int *g_rva01356A9C;

static __forceinline int bfmeAbs9BFA40(int value)
{
	return value < 0 ? -value : value;
}

static __forceinline UINT8 bfmeClamp9BFA40(int value)
{
	if (value < 0)
		return 0;
	if (value > 255)
		return 255;
	return (UINT8)value;
}

// Filter one eight-sample line straddling a block boundary.  The two four
// sample variances and the centre discontinuity jointly gate the update.
static __forceinline UINT32 bfmeFilterLine9BFA40(const UINT8 *source, int step,
	UINT8 *destination, int destinationStep, UINT32 qStep)
{
	int sample[10];
	int i;
	int sum1 = 0;
	int sum2 = 0;
	int square1 = 0;
	int square2 = 0;

	for (i = 0; i < 10; ++i)
		sample[i] = source[(i - 5) * step];

	for (i = 1; i <= 4; ++i) {
		int value = sample[i] - 128;
		sum1 += value;
		square1 += value * value;
	}
	for (i = 5; i <= 8; ++i) {
		int value = sample[i] - 128;
		sum2 += value;
		square2 += value * value;
	}

	UINT32 variance1 = (UINT32)(square1 - (sum1 >> 1) * ((sum1 + 1) >> 1));
	UINT32 variance2 = (UINT32)(square2 - (sum2 >> 1) * ((sum2 + 1) >> 1));
	UINT32 limit = (3 * qStep * qStep) >> 5;
	bool filter = variance1 < limit && variance2 < limit
		&& bfmeAbs9BFA40(sample[4] - sample[5]) < (int)qStep;

	if (!filter) {
		for (i = 1; i <= 8; ++i)
			destination[(i - 5) * destinationStep] = (UINT8)sample[i];
		return variance1 + variance2;
	}

	int left = bfmeAbs9BFA40(sample[0] - sample[1]) < (int)qStep ? sample[0] : sample[1];
	int right = bfmeAbs9BFA40(sample[8] - sample[9]) < (int)qStep ? sample[9] : sample[8];
	int window = left * 3 + sample[1] + sample[2] + sample[3] + sample[4] + 4;

	for (i = 1; i <= 8; ++i) {
		int previous = i == 1 ? left : sample[i - 1];
		int next = i == 8 ? right : sample[i + 1];
		int value = ((window + sample[i]) * 2 + previous - next) >> 4;
		destination[(i - 5) * destinationStep] = bfmeClamp9BFA40(value);
		window -= i < 4 ? left : sample[i - 3];
		window += i < 4 ? sample[i + 4] : right;
	}

	return variance1 + variance2;
}

extern "C" void __cdecl DeblockLoopFilteredBand_WMT(
	Rva009BFA40Ctx *ctx, UINT8 *src, UINT8 *dst,
	UINT32 stride, UINT32 count, UINT32 start,
	UINT32 *qTable)
{
	// Unconditional shared-table lookup + broadcast, independent of the
	// per-fragment qStep test below -- matches the entry bytes exactly.
	// A real align(16) array (not a volatile scalar) is what makes MSVC emit
	// retail's "and esp,-16" aligned-frame prologue at all.
	__declspec(align(16)) unsigned short qv[8];
	unsigned short tableQ = (unsigned short)g_rva01356A9C[ctx->m_tableIndex];
	*(volatile unsigned short *)&qv[0] = tableQ;
	*(volatile unsigned short *)&qv[1] = tableQ;
	*(volatile unsigned short *)&qv[2] = tableQ;
	*(volatile unsigned short *)&qv[3] = tableQ;
	*(volatile unsigned short *)&qv[4] = tableQ;
	*(volatile unsigned short *)&qv[5] = tableQ;
	*(volatile unsigned short *)&qv[6] = tableQ;
	*(volatile unsigned short *)&qv[7] = tableQ;

	UINT32 frag = start;
	UINT32 end = count + start;

	if (frag < end)
	{
		UINT32 qIndex = end;
		do
		{
			UINT32 qStep = qTable[ctx->m_fragmentQIndex[qIndex]];
			if (qStep > 3) {
				UINT32 horizontalVariance = 0;
				UINT32 verticalVariance = 0;
				int i;

				for (i = 0; i < 8; ++i)
					horizontalVariance += bfmeFilterLine9BFA40(
						src + i, (int)stride, dst + i, (int)stride, qStep);

				for (i = -4; i < 4; ++i)
					verticalVariance += bfmeFilterLine9BFA40(
						src + i * (int)stride, 1,
						dst + i * (int)stride, 1, qStep);

				ctx->m_fragmentVariances[frag] += horizontalVariance;
				ctx->m_fragmentVariances[qIndex] += horizontalVariance;
				ctx->m_fragmentVariances[frag] += verticalVariance;
				ctx->m_fragmentVariances[qIndex] += verticalVariance;
			} else {
				int row;
				for (row = -4; row < 4; ++row) {
					int column;
					for (column = 0; column < 8; ++column)
						dst[row * (int)stride + column] = src[row * (int)stride + column];
				}
			}

			src += 8;
			dst += 8;
			++frag;
			++qIndex;
		} while (frag < end);
	}
}
