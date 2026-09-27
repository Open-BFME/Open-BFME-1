// ?Rva009B5AF0Vp6DecodeBlock@@YAXPAEHH@Z
// partial score=0.844 date=2026-09-27
// The caller at 0x009B5DB0 invokes this body between VP6 token and motion vector helpers.
// The first predictor call writes its result into the ctx argument slot.
// The decoder passes that overwritten value as DecodeToken's third argument.
// The class and method remain unproved, so this function keeps its RVA.
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern void Rva009B5420Vp6FindPredictor(void *, int, int, int, int *);
extern int Rva009B50F0DecodeToken(unsigned char *, int, int);
extern int Rva009B5090DecodeMode(unsigned char *);
extern void Rva009B5200DecodeMotionVector(void *, short *, int);

void Rva009B5AF0Vp6DecodeBlock(unsigned char *ctx, int row, int column)
{
    unsigned char *state = ctx;
    Rva009B5420Vp6FindPredictor(state, row, column, 1, (int *)&ctx);

    int mode = Rva009B50F0DecodeToken(state, *(int *)(state + 0x39c), (int)ctx);
    volatile int *modeHome = &mode;
    *(int *)(state + 0x39c) = mode;
    *(unsigned char *)(*(int *)(state + 0x6f0) +
        *(int *)(state + 0x230) * row + column) = (unsigned char)mode;
    *(int *)(state + 8) = mode;

    if (mode == 7) {
        *(int *)(state + 0x0c) = Rva009B5090DecodeMode(state);
        *(int *)(state + 0x10) = Rva009B5090DecodeMode(state);
        *(int *)(state + 0x14) = Rva009B5090DecodeMode(state);
        *(int *)(state + 0x18) = Rva009B5090DecodeMode(state);
        *(int *)(state + 0x1c) = 7;
        *(int *)(state + 0x20) = 7;

        int sumX = 0;
        int sumY = 0;
        short *coeff = (short *)(state + 0x24);
        int *submode = (int *)(state + 0x0c);
        int count = 4;
        while (count != 0) {
            int kind = *submode;
            if (kind == 0) {
                coeff[0] = 0;
                coeff[1] = 0;
            } else if (kind == 3) {
                coeff[0] = *(short *)(state + 0x3c);
                coeff[1] = *(short *)(state + 0x3e);
                sumX += *(short *)(state + 0x3c);
                sumY += *(short *)(state + 0x3e);
            } else if (kind == 4) {
                coeff[0] = *(short *)(state + 0x40);
                coeff[1] = *(short *)(state + 0x42);
                sumX += *(short *)(state + 0x40);
                sumY += *(short *)(state + 0x42);
            } else if (kind == 2) {
                Rva009B5200DecodeMotionVector(state, (short *)&ctx, 2);
                int vectorPair = *(int *)&ctx;
                coeff[0] = (short)vectorPair;
                coeff[1] = *((short *)&ctx + 1);
                sumX += (short)vectorPair;
                sumY += *((short *)&ctx + 1);
            }
            ++submode;
            coeff += 2;
            --count;
        }

        int averageX = (sumX + (sumX >= 0 ? 1 : 0) + 1) >> 2;
        int averageY = (sumY + (sumY >= 0 ? 1 : 0) + 1) >> 2;
        int index = *(int *)(state + 0x230) * *(volatile int *)&row + *(volatile int *)&column;
        unsigned char *block = *(unsigned char **)(state + 0x6f4);
        *(short *)(block + index * 4) = *(short *)(state + 0x30);
        *(short *)(block + index * 4 + 2) = *(short *)(state + 0x32);
        *(short *)(state + 0x34) = (short)averageX;
        *(short *)(state + 0x36) = (short)averageY;
        *(short *)(state + 0x38) = (short)averageX;
        *(short *)(state + 0x3a) = (short)averageY;
        return;
    }

    int dispatchMode = mode - 2;
    int x;
    int y;
    switch (dispatchMode) {
    case 1:
        x = *(short *)(state + 0x3c);
        y = *(short *)(state + 0x3e);
        break;
    case 2:
        x = *(short *)(state + 0x40);
        y = *(short *)(state + 0x42);
        break;
    case 6:
        Rva009B5420Vp6FindPredictor(state, row, column, 2, (int *)&ctx);
        x = *(short *)(state + 0x48);
        y = *(short *)(state + 0x4a);
        break;
    case 7:
        Rva009B5420Vp6FindPredictor(state, row, column, 2, (int *)&ctx);
        x = *(short *)(state + 0x4c);
        y = *(short *)(state + 0x4e);
        break;
    case 0:
        Rva009B5200DecodeMotionVector(state, (short *)&ctx, 2);
        x = *((short *)&ctx);
        y = *((short *)&ctx + 1);
        break;
    case 4:
        Rva009B5420Vp6FindPredictor(state, row, column, 2, (int *)&ctx);
        Rva009B5200DecodeMotionVector(state, (short *)&ctx, 6);
        x = *((short *)&ctx);
        y = *((short *)&ctx + 1);
        break;
    case 3:
        x = 0;
        y = 0;
        break;
    default:
        x = 0;
        y = 0;
        break;
    }
    int index = *(int *)(state + 0x230) * row + column;
    unsigned char *block = *(unsigned char **)(state + 0x6f4);
    *(short *)(block + index * 4) = (short)x;
    *(short *)(block + index * 4 + 2) = (short)y;

    int clearMode = *modeHome;
    short *p = (short *)(state + 0x26);
    int clearCount = 6;
    while (clearCount != 0) {
        p[-1] = 0;
        p[0] = 0;
        *(int *)(p - 13) = clearMode;
        p += 2;
        --clearCount;
    }
}
