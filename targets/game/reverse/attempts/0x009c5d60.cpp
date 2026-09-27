// ?Rva009C5D60@@YAXPAF00@Z
// partial score=0.99 date=2026-09-27
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// On2 VP3/VP6-style IDct10: dequantise the first ten coefficients, row pass over
// four rows, column pass over eight columns. Stored by the codec init at 0x009B3D76
// in the function table slots for 2..10 coefficients (0x009C6360 below, 0x009C5890 above).

extern void __cdecl Rva009C5CA0(short *, short *, int *);

#define VP6_MUL(a, b) (((a) * (b)) >> 16)

// ?Rva009C5D60@@YAXPAF00@Z
void __cdecl Rva009C5D60(short *first, short *second, short *destination)
{
    int block[64];
    int *input = block;
    short *output = destination;
    int A, B, C, D, Ad, Bd, Cd, Dd, E, F, G, H;
    int Ed, Gd, Add, Bdd, Fd, Hd;
    int loop;

    Rva009C5CA0(second, first, block);

    for (loop = 0; loop < 4; loop++) {
        if (input[0] | input[1] | input[2] | input[3]) {
            A = VP6_MUL(64277, input[1]);
            B = VP6_MUL(12785, input[1]);
            C = VP6_MUL(54491, input[3]);
            D = -VP6_MUL(36410, input[3]);
            Ad = VP6_MUL(46341, (A - C));
            Bd = VP6_MUL(46341, (B - D));
            Cd = A + C;
            Dd = B + D;
            E = VP6_MUL(46341, input[0]);
            F = E;
            G = VP6_MUL(60547, input[2]);
            H = VP6_MUL(25080, input[2]);
            Ed = E - G;
            Gd = E + G;
            Add = F + Ad;
            Bdd = Bd - H;
            Fd = F - Ad;
            Hd = Bd + H;
            input[0] = (short)((Gd + Cd) >> 0);
            input[7] = (short)((Gd - Cd) >> 0);
            input[1] = (short)((Add + Hd) >> 0);
            input[2] = (short)((Add - Hd) >> 0);
            input[3] = (short)((Ed + Dd) >> 0);
            input[4] = (short)((Ed - Dd) >> 0);
            input[5] = (short)((Fd + Bdd) >> 0);
            input[6] = (short)((Fd - Bdd) >> 0);
        }
        input += 8;
    }

    input = block;

    for (loop = 0; loop < 8; loop++) {
        if (input[0 * 8] | input[1 * 8] | input[2 * 8] | input[3 * 8]) {
            A = VP6_MUL(64277, input[1 * 8]);
            B = VP6_MUL(12785, input[1 * 8]);
            C = VP6_MUL(54491, input[3 * 8]);
            D = -VP6_MUL(36410, input[3 * 8]);
            Ad = VP6_MUL(46341, (A - C));
            Bd = VP6_MUL(46341, (B - D));
            Cd = A + C;
            Dd = B + D;
            E = VP6_MUL(46341, input[0 * 8]);
            F = E;
            G = VP6_MUL(60547, input[2 * 8]);
            H = VP6_MUL(25080, input[2 * 8]);
            Ed = E - G;
            Gd = E + G;
            Add = F + Ad;
            Bdd = Bd - H;
            Fd = F - Ad;
            Hd = Bd + H;
            Gd += 8;
            Add += 8;
            Ed += 8;
            Fd += 8;
            output[0 * 8] = (short)((Gd + Cd) >> 4);
            output[7 * 8] = (short)((Gd - Cd) >> 4);
            output[1 * 8] = (short)((Add + Hd) >> 4);
            output[2 * 8] = (short)((Add - Hd) >> 4);
            output[3 * 8] = (short)((Ed + Dd) >> 4);
            output[4 * 8] = (short)((Ed - Dd) >> 4);
            output[5 * 8] = (short)((Fd + Bdd) >> 4);
            output[6 * 8] = (short)((Fd - Bdd) >> 4);
        } else {
            output[0 * 8] = 0;
            output[7 * 8] = 0;
            output[1 * 8] = 0;
            output[2 * 8] = 0;
            output[3 * 8] = 0;
            output[4 * 8] = 0;
            output[5 * 8] = 0;
            output[6 * 8] = 0;
        }
        input++;
        output++;
    }
}

#undef VP6_MUL
