// ?Rva009C5D60@@YAXPAF00@Z
// partial score=0.82 date=2026-09-27
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern void __cdecl Rva009C5CA0(short *, short *, int *);

#define VP6_MUL(a, b) ((int)((unsigned int)(a) * (b)) >> 16)

#define VP6_IDCT4(input, output) \
    if ((input)[3] | (input)[2] | (input)[1] | (input)[0]) { \
        A = VP6_MUL(0xfb15, (input)[1]); \
        B = VP6_MUL(0x31f1, (input)[1]); \
        C = VP6_MUL(0xd4db, (input)[3]); \
        D = -VP6_MUL(0x8e3a, (input)[3]); \
        Ad = VP6_MUL(0xb505, A - C); \
        Bd = VP6_MUL(0xb505, B - D); \
        Cd = A + C; \
        Dd = B + D; \
        E = VP6_MUL(0xb505, (input)[0]); \
        F = E; \
        G = VP6_MUL(0xec83, (input)[2]); \
        H = VP6_MUL(0x61f8, (input)[2]); \
        Ed = E - G; \
        Gd = E + G; \
        Add = F + Ad; \
        Bdd = Bd - H; \
        Fd = F - Ad; \
        Hd = Bd + H; \
        (output)[0] = (short)(Cd + Gd); \
        (output)[7] = (short)(Gd - Cd); \
        (output)[1] = (short)(Add + Hd); \
        (output)[2] = (short)(Add - Hd); \
        (output)[3] = (short)(Ed + Dd); \
        (output)[4] = (short)(Ed - Dd); \
        (output)[5] = (short)(Fd + Bdd); \
        (output)[6] = (short)(Fd - Bdd); \
    }

// ?Rva009C5D60@@YAXPAF00@Z
void __cdecl Rva009C5D60(short *first, short *second, short *destination)
{
    int block[64];
    int *input;
    short *output;
    int count;
    int zero;
    int A, B, C, D, Ad, Bd, Cd, Dd, E, F, G, H;
    int Ed, Gd, Add, Bdd, Fd, Hd;
    int p0, p1, p2, p3;
    Rva009C5CA0(second, first, block);

    VP6_IDCT4(block, block);
    VP6_IDCT4(block + 8, block + 8);
    VP6_IDCT4(block + 16, block + 16);
    VP6_IDCT4(block + 24, block + 24);

    count = 8;
    input = block + 24;
    output = destination + 8;
    zero = 0;
    do {
        p3 = input[0];
        p0 = input[-24];
        p1 = input[-16];
        p2 = input[-8];
        if (p0 | p1 | p2 | p3) {
            E = VP6_MUL(0xb505, p0);
            F = E;
            A = VP6_MUL(0xfb15, p1);
            B = VP6_MUL(0x31f1, p1);
            C = VP6_MUL(0xd4db, p3);
            D = -VP6_MUL(0x8e3a, p3);
            Ad = VP6_MUL(0xb505, A - C);
            Bd = VP6_MUL(0xb505, B - D);
            Cd = A + C;
            Dd = B + D;
            G = VP6_MUL(0xec83, p2);
            H = VP6_MUL(0x61f8, p2);
            Ed = E - G;
            Gd = E + G;
            Add = F + Ad;
            Bdd = Bd - H;
            Fd = F - Ad;
            Hd = Bd + H;
            output[-8] = (short)((Gd + Cd + 8) >> 4);
            output[0] = (short)((Add + Hd + 8) >> 4);
            output[24] = (short)((Ed + Dd + 8) >> 4);
            output[48] = (short)((Gd - Cd + 8) >> 4);
            output[8] = (short)((Add - Hd + 8) >> 4);
            output[16] = (short)((Ed - Dd + 8) >> 4);
            output[32] = (short)((Fd + Bdd + 8) >> 4);
            output[40] = (short)((Fd - Bdd + 8) >> 4);
        } else {
            output[-8] = zero;
            output[48] = zero;
            output[8] = zero;
            output[16] = zero;
            output[0] = zero;
            output[24] = zero;
            output[32] = zero;
            output[40] = zero;
        }
        ++input;
        ++output;
    } while (--count);
}

#undef VP6_IDCT4
#undef VP6_MUL
