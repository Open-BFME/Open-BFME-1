// ?filterBand009AE6A0@@YAXPAURva009AE6A0State@@PAE1HIIPBH@Z
// partial score=0.925 date=2026-09-28
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x009AE6A0: On2 VP3/VP6 postprocessor DeblockNonFilteredBand, generic tier of dispatch slot 21
// (g_rva01356EB4, the band callback of copyPlane009AF0D0). field0c=FrameQIndex, field28=FragmentVariances, field38=FiltBoundingValue.
typedef unsigned char byte;
extern const unsigned char g_bfmeClampTable[];
struct Rva009AE6A0State {
    byte pad00[0x0c];
    int field0c;
    byte pad10[0x18];
    int *field28;
    byte pad2c[0x0c];
    int *field38;
};
#define ABS(a) ((a) > 0 ? (a) : -(a))
void filterBand009AE6A0(Rva009AE6A0State *pbi, byte *SrcPtr, byte *DesPtr,
    int PlaneLineStep, unsigned FragAcross, unsigned StartFrag, const int *QuantScale)
{
    unsigned j;
    unsigned CurrentFrag = StartFrag;
    int QStep;
    int FLimit;
    byte *Src, *Des;
    int x[10];
    int Sum1, Sum2;
    int FiltVal;

    int Step2 = 2 * PlaneLineStep;
    int Step3 = 3 * PlaneLineStep;
    int Step4 = 4 * PlaneLineStep;
    int Step5 = 5 * PlaneLineStep;
    QStep = QuantScale[pbi->field0c];

    while (CurrentFrag < StartFrag + FragAcross) {
        Src = SrcPtr + 8 * (CurrentFrag - StartFrag);
        Des = DesPtr + 8 * (CurrentFrag - StartFrag);
        FLimit = (QStep * 3) >> 2;

        for (j = 0; j < 8; j++) {
            x[0] = Src[-Step5];
            x[1] = Src[-Step4];
            x[2] = Src[-Step3];
            x[3] = Src[-Step2];
            x[4] = Src[-1 * PlaneLineStep];
            x[5] = Src[0];
            x[6] = Src[PlaneLineStep];
            x[7] = Src[Step2];
            x[8] = Src[Step3];
            x[9] = Src[Step4];

            Sum1 = Sum2 = 0;
            Sum1 += ABS(x[1] - x[0]);
            Sum1 += ABS(x[2] - x[1]);
            Sum1 += ABS(x[3] - x[2]);
            Sum1 += ABS(x[4] - x[3]);
            Sum2 += ABS(x[5] - x[6]);
            Sum2 += ABS(x[6] - x[7]);
            Sum2 += ABS(x[7] - x[8]);
            Sum2 += ABS(x[8] - x[9]);

            pbi->field28[CurrentFrag] += (Sum1 > 255) ? 255 : Sum1;
            pbi->field28[CurrentFrag + FragAcross] += (Sum2 > 255) ? 255 : Sum2;

            if (Sum1 < FLimit && Sum2 < FLimit &&
                (x[5] - x[4]) < QStep && (x[4] - x[5]) < QStep) {
                Sum1 = x[0] * 3 + x[1] + x[2] + x[3] + x[4] + 4;
                Des[-Step4] = (byte)((Sum1 + x[1]) >> 3);
                Sum1 += x[5] - x[0];
                Des[-Step3] = (byte)((Sum1 + x[2]) >> 3);
                Sum1 += x[6] - x[0];
                Des[-Step2] = (byte)((Sum1 + x[3]) >> 3);
                Sum1 += x[7] - x[0];
                Des[-1 * PlaneLineStep] = (byte)((Sum1 + x[4]) >> 3);
                Sum1 += x[8] - x[1];
                Des[0] = (byte)((Sum1 + x[5]) >> 3);
                Sum1 += x[9] - x[2];
                Des[PlaneLineStep] = (byte)((Sum1 + x[6]) >> 3);
                Sum1 += x[9] - x[3];
                Des[Step2] = (byte)((Sum1 + x[7]) >> 3);
                Sum1 += x[9] - x[4];
                Des[Step3] = (byte)((Sum1 + x[8]) >> 3);
            } else {
                FiltVal = pbi->field38[((x[3] - x[6]) + 3 * (x[5] - x[4]) + 4) >> 3];
                Des[-1 * PlaneLineStep] = g_bfmeClampTable[x[4] + FiltVal];
                Des[0] = g_bfmeClampTable[x[5] - FiltVal];
                Des[-Step4] = Src[-Step4];
                Des[-Step3] = Src[-Step3];
                Des[-Step2] = Src[-Step2];
                Des[PlaneLineStep] = Src[PlaneLineStep];
                Des[Step2] = Src[Step2];
                Des[Step3] = Src[Step3];
            }
            Src++;
            Des++;
        }

        if (CurrentFrag == StartFrag)
            CurrentFrag++;
        else {
            Des = DesPtr - 8 * PlaneLineStep + 8 * (CurrentFrag - StartFrag);
            Src = Des;
            FLimit = (QStep * 3) >> 2;

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
                Sum1 += ABS(x[1] - x[0]);
                Sum1 += ABS(x[2] - x[1]);
                Sum1 += ABS(x[3] - x[2]);
                Sum1 += ABS(x[4] - x[3]);
                Sum2 += ABS(x[5] - x[6]);
                Sum2 += ABS(x[6] - x[7]);
                Sum2 += ABS(x[7] - x[8]);
                Sum2 += ABS(x[8] - x[9]);

                pbi->field28[CurrentFrag - 1] += (Sum1 > 255) ? 255 : Sum1;
                pbi->field28[CurrentFrag] += (Sum2 > 255) ? 255 : Sum2;

                if (Sum1 < FLimit && Sum2 < FLimit &&
                    (x[5] - x[4]) < QStep && (x[4] - x[5]) < QStep) {
                    Sum1 = x[0] * 3 + x[1] + x[2] + x[3] + x[4] + 4;
                    Des[-4] = (byte)((Sum1 + x[1]) >> 3);
                    Sum1 += x[5] - x[0];
                    Des[-3] = (byte)((Sum1 + x[2]) >> 3);
                    Sum1 += x[6] - x[0];
                    Des[-2] = (byte)((Sum1 + x[3]) >> 3);
                    Sum1 += x[7] - x[0];
                    Des[-1] = (byte)((Sum1 + x[4]) >> 3);
                    Sum1 += x[8] - x[1];
                    Des[0] = (byte)((Sum1 + x[5]) >> 3);
                    Sum1 += x[9] - x[2];
                    Des[1] = (byte)((Sum1 + x[6]) >> 3);
                    Sum1 += x[9] - x[3];
                    Des[2] = (byte)((Sum1 + x[7]) >> 3);
                    Sum1 += x[9] - x[4];
                    Des[3] = (byte)((Sum1 + x[8]) >> 3);
                } else {
                    FiltVal = pbi->field38[((x[3] - x[6]) + 3 * (x[5] - x[4]) + 4) >> 3];
                    Des[-1] = g_bfmeClampTable[x[4] + FiltVal];
                    Des[0] = g_bfmeClampTable[x[5] - FiltVal];
                }
                Src += PlaneLineStep;
                Des += PlaneLineStep;
            }
            CurrentFrag++;
        }
    }
}
