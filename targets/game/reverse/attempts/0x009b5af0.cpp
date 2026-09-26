// ?Rva009B5AF0Vp6DecodeBlock@@YAXPAEHH@Z
// partial score=0.25 date=2026-09-10
// ?Rva009B5AF0Vp6DecodeBlock@@YAXPAEHH@Z
// Address-derived VP6 block-mode decoder.  The direct caller at 0x009B5DB0
// supplies ctx/row/column and leaves the caller's saved-register words in the
// remaining stack slots; the retail helper consumes the sixth word as the
// token-tree plane.  The fields below are the established decoder layout used
// by the adjacent 0x009B50F0/0x009B5200 helpers.
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern void Rva009B5420Vp6FindPredictor(void *, int, int, int, int *);
extern int Rva009B50F0DecodeToken(unsigned char *, int, int);
extern int Rva009B5090DecodeMode(unsigned char *);
extern void Rva009B5200DecodeMotionVector(void *, short *, int);

void Rva009B5AF0Vp6DecodeBlock(unsigned char *ctx, int row, int column)
{
    Rva009B5420Vp6FindPredictor(ctx, row, column, 1, (int *)&ctx);

    int mode = Rva009B50F0DecodeToken(ctx, *(int *)(ctx + 0x39c),
        *((int *)&ctx + 5));
    *(int *)(ctx + 0x39c) = mode;
    *(unsigned char *)(*(int *)(ctx + 0x6f0) +
        *(int *)(ctx + 0x230) * row + column) = (unsigned char)mode;
    *(int *)(ctx + 8) = mode;

    if (mode == 7) {
        *(int *)(ctx + 0x0c) = Rva009B5090DecodeMode(ctx);
        *(int *)(ctx + 0x10) = Rva009B5090DecodeMode(ctx);
        *(int *)(ctx + 0x14) = Rva009B5090DecodeMode(ctx);
        *(int *)(ctx + 0x18) = Rva009B5090DecodeMode(ctx);
        *(int *)(ctx + 0x1c) = 7;
        *(int *)(ctx + 0x20) = 7;

        int sumX = 0;
        int sumY = 0;
        short *coeff = (short *)(ctx + 0x24);
        int *submode = (int *)(ctx + 0x0c);
        int count = 4;
        while (count != 0) {
            int kind = *submode;
            if (kind == 0) {
                coeff[0] = 0;
                coeff[1] = 0;
            } else if (kind == 3) {
                coeff[0] = *(short *)(ctx + 0x3c);
                coeff[1] = *(short *)(ctx + 0x3e);
                sumX += *(short *)(ctx + 0x3c);
                sumY += *(short *)(ctx + 0x3e);
            } else if (kind == 4) {
                coeff[0] = *(short *)(ctx + 0x40);
                coeff[1] = *(short *)(ctx + 0x42);
                sumX += *(short *)(ctx + 0x40);
                sumY += *(short *)(ctx + 0x42);
            } else if (kind == 2) {
                short mv[2];
                Rva009B5200DecodeMotionVector(ctx, mv, 2);
                coeff[0] = mv[0];
                coeff[1] = mv[1];
                sumX += mv[0];
                sumY += mv[1];
            }
            ++submode;
            coeff += 2;
            --count;
        }

        int averageX = (sumX + (sumX >= 0 ? 1 : 0)) >> 2;
        int averageY = (sumY + (sumY >= 0 ? 1 : 0)) >> 2;
        int index = *(int *)(ctx + 0x230) * row + column;
        unsigned char *block = *(unsigned char **)(ctx + 0x6f4);
        *(short *)(block + index * 4) = *(short *)(ctx + 0x30);
        *(short *)(block + index * 4 + 2) = *(short *)(ctx + 0x32);
        *(short *)(ctx + 0x34) = (short)averageX;
        *(short *)(ctx + 0x36) = (short)averageY;
        *(short *)(ctx + 0x38) = (short)averageX;
        *(short *)(ctx + 0x3a) = (short)averageY;
        return;
    }

    mode -= 2;
    int x;
    int y;
    if (mode == 0) {
        short mv[2];
        Rva009B5200DecodeMotionVector(ctx, mv, 2);
        x = mv[0];
        y = mv[1];
    } else if (mode == 1) {
        x = *(short *)(ctx + 0x3c);
        y = *(short *)(ctx + 0x3e);
    } else if (mode == 2) {
        x = *(short *)(ctx + 0x40);
        y = *(short *)(ctx + 0x42);
    } else if (mode == 3) {
        x = 0;
        y = 0;
    } else if (mode == 4) {
        Rva009B5420Vp6FindPredictor(ctx, row, column, 2, (int *)&ctx);
        short mv[2];
        Rva009B5200DecodeMotionVector(ctx, mv, 6);
        x = mv[0];
        y = mv[1];
    } else if (mode == 6) {
        Rva009B5420Vp6FindPredictor(ctx, row, column, 2, (int *)&ctx);
        x = *(short *)(ctx + 0x48);
        y = *(short *)(ctx + 0x4a);
    } else if (mode == 7) {
        Rva009B5420Vp6FindPredictor(ctx, row, column, 2, (int *)&ctx);
        x = *(short *)(ctx + 0x4c);
        y = *(short *)(ctx + 0x4e);
    } else {
        x = 0;
        y = 0;
    }

    int index = *(int *)(ctx + 0x230) * row + column;
    unsigned char *block = *(unsigned char **)(ctx + 0x6f4);
    *(short *)(block + index * 4) = (short)x;
    *(short *)(block + index * 4 + 2) = (short)y;

    short *p = (short *)(ctx + 0x26);
    int clearCount = 6;
    while (clearCount != 0) {
        p[-1] = 0;
        p[0] = 0;
        *(int *)(p - 13) = 0;
        p += 2;
        --clearCount;
    }
}
