// Retail 009A6F70: squared error between a dequantized 8x8 block (quantized
// coefficient times quantizer step) and the reference block read through the
// zigzag table, scaled by four.  The plain loop is what retail compiled: the
// compiler unrolls the 64 constant iterations four at a time on its own.
extern int g_rva01142308[];
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
