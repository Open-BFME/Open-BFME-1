// ?Rva009ADAA0@@YAXPAURva009AF200Context@@PAE1IIHPBI@Z
// partial score=0.7538 date=2026-09-28
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?Rva009ADAA0@@YAXPAURva009AF200Context@@PAE1IIHPBI@Z  retail 0x009ADAA0, 730 B (RET at +0x2D9; ledger 727 is truncated)
// Shape: On2 VP3 postproc DeblockVerticalEdgesInLoopFilteredBand (tail band called last by
// matched copyPlane009AF0D0), VP6 variant: QStep = QuantScale[ctx+0xC] outside the loop, FLimit =
// QStep*QStep*3>>5 inside the band loop, Src/Des from 8*(CurrentFrag-StartFrag+1) (the
// compiler forms Src[-3] as Des-3+distance), Sum1/Sum2 as two separate k loops, old-loopfilter
// else arm through the ctx+0x38 bounding table and the 0x01356FE0 clamp table. Identity unproven: opaque name.
// Probe --size 730: 726 B, 177 differing bytes, frame 0x40 exact; residue = register choice in
// the last Sum2 ABS (+0x16D) and the running-sum tail from +0x217.
extern const unsigned char g_bfmeClampTable[];

struct Rva009AF200Context
{
	int m_mode;
	unsigned char m_pad04[8];
	int m_tableIndex;
	unsigned char m_pad10[0x28 - 0x10];
	void *m_scratch;
	unsigned char m_pad2C[0x38 - 0x2C];
	int *m_bounding;
};

#define ABS(x) ((x) > 0 ? (x) : -(x))

void Rva009ADAA0(Rva009AF200Context *pbi, unsigned char *SrcPtr,
	unsigned char *DesPtr, unsigned int PlaneLineStep,
	unsigned int FragsAcross, int StartFrag, const unsigned int *QuantScale)
{
	unsigned int j, k;
	unsigned int CurrentFrag = StartFrag;
	int QStep;
	int FLimit;
	unsigned char *Src, *Des;
	int x[10];
	int Sum1, Sum2;
	int FiltVal;

	QStep = QuantScale[pbi->m_tableIndex];

	while (CurrentFrag < StartFrag + FragsAcross - 1) {
		FLimit = (QStep * QStep * 3) >> 5;
		Src = SrcPtr + 8 * (CurrentFrag - StartFrag + 1);
		Des = DesPtr + 8 * (CurrentFrag - StartFrag + 1);

		for (j = 0; j < 8; j++) {
			x[0] = Src[-5];
			x[1] = Src[-4];
			x[2] = Src[-3];
			x[3] = Src[-2];
			x[4] = Src[-1];
			x[5] = Src[0];
			x[6] = Src[1];
			x[7] = Src[2];
			x[8] = Src[3];
			x[9] = Src[4];

			Sum1 = Sum2 = 0;

			for (k = 1; k <= 4; k++)
				Sum1 += ABS(x[k] - x[k - 1]);
			for (k = 1; k <= 4; k++)
				Sum2 += ABS(x[k + 4] - x[k + 5]);

			if (Sum1 < FLimit && Sum2 < FLimit && (x[5] - x[4]) < QStep && (x[4] - x[5]) < QStep) {
				Sum1 = x[0] + x[0] + x[0] + x[1] + x[2] + x[3] + x[4] + 4;
				Des[-4] = (unsigned char)((Sum1 + x[1]) >> 3);
				Sum1 += x[5] - x[0];
				Des[-3] = (unsigned char)((Sum1 + x[2]) >> 3);
				Sum1 += x[6] - x[0];
				Des[-2] = (unsigned char)((Sum1 + x[3]) >> 3);
				Sum1 += x[7] - x[0];
				Des[-1] = (unsigned char)((Sum1 + x[4]) >> 3);
				Sum1 += x[8] - x[1];
				Des[0] = (unsigned char)((Sum1 + x[5]) >> 3);
				Sum1 += x[9] - x[2];
				Des[1] = (unsigned char)((Sum1 + x[6]) >> 3);
				Sum1 += x[9] - x[3];
				Des[2] = (unsigned char)((Sum1 + x[7]) >> 3);
				Sum1 += x[9] - x[4];
				Des[3] = (unsigned char)((Sum1 + x[8]) >> 3);
			} else {
				FiltVal = pbi->m_bounding[(x[3] - x[4] * 3 + x[5] * 3 - x[6] + 4) >> 3];
				Des[-1] = g_bfmeClampTable[x[4] + FiltVal];
				Des[0] = g_bfmeClampTable[x[5] - FiltVal];
			}

			Src += PlaneLineStep;
			Des += PlaneLineStep;
		}
		CurrentFrag++;
	}
}
