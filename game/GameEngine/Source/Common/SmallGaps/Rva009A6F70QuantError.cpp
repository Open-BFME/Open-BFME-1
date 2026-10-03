// Retail 009A6F70: squared error between a dequantized 8x8 block (quantized
// coefficient times quantizer step) and the reference block read through the
// zigzag table, scaled by four.  The plain loop is what retail compiled: the
// compiler unrolls the 64 constant iterations four at a time on its own.
int g_rva01142308[64] = {
    0, 1, 8, 16, 9, 2, 3, 10,
    17, 24, 32, 25, 18, 11, 4, 5,
    12, 19, 26, 33, 40, 48, 41, 34,
    27, 20, 13, 6, 7, 14, 21, 28,
    35, 42, 49, 56, 57, 50, 43, 36,
    29, 22, 15, 23, 30, 37, 44, 51,
    58, 59, 52, 45, 38, 31, 39, 46,
    53, 60, 61, 54, 47, 55, 62, 63,
};
void Rva009A6F70QuantError(const short *ref, const short *coef, const short *step, int *error)
{
    int sum = 0;
    int i;
    for (i = 0; i < 64; i++) {
        int d = coef[i] * step[i] - ref[g_rva01142308[i]];
        sum += d * d;
    }
    *error = sum * 4;
}
