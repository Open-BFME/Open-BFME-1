// ?d_009ae6a0@@YAXXZ
// partial score=0.69 date=2026-09-27
// Retail 0x009AE6A0: interleaved horizontal and vertical edge filtering.
// Raw context offsets are witnessed; no codec structure identity is asserted.
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
void filterBand009AE6A0(Rva009AE6A0State *context, byte *source, byte *destination,
    int stride, unsigned width, unsigned first, const int *scale)
{
    unsigned current;
    int x0, x1, x2, x3, x4, x5, x6, x7, x8, x9;
    int d1, d2, d3, d4, sum1, sum2, running;
    int q = scale[context->field0c];
    int limit;
    byte *src, *dst;
    for (current = first; current < first + width; ++current) {
        src = source + 8 * (current - first) - 5*stride;
        limit = (q * 3) >> 2;
        dst = destination + 8 * (current - first) - 4*stride;
        for (unsigned j = 0; j < 8; ++j) {
            x0 = src[0 * stride];
            x1 = src[1 * stride];
            x3 = src[3 * stride];
            x2 = src[2 * stride];
            x4 = src[4 * stride];
            x5 = src[5 * stride];
            x7 = src[7 * stride];
            x6 = src[6 * stride];
            x8 = src[8 * stride];
            x9 = src[9 * stride];
            d1 = x1 - x0;
            if (d1 <= 0) d1 = x0 - x1;
            d2 = x2 - x1;
            if (d2 <= 0) d2 = x1 - x2;
            d3 = x3 - x2;
            if (d3 <= 0) d3 = x2 - x3;
            d4 = x4 - x3;
            if (d4 <= 0) d4 = x3 - x4;
            sum1 = d1 + d2 + d3 + d4;
            d1 = x5 - x6;
            if (d1 <= 0) d1 = x6 - x5;
            d2 = x6 - x7;
            if (d2 <= 0) d2 = x7 - x6;
            d3 = x7 - x8;
            if (d3 <= 0) d3 = x8 - x7;
            d4 = x8 - x9;
            if (d4 <= 0) d4 = x9 - x8;
            sum2 = d1 + d2 + d3 + d4;
            context->field28[current] += sum1 > 255 ? 255 : sum1;
            context->field28[current + width] += sum2 > 255 ? 255 : sum2;
            if (sum1 < limit && sum2 < limit && x5 - x4 < q && x4 - x5 < q) {
                running = x4 + 3*x0 + x3 + x2 + 4 + x1;
                dst[0 * stride] = (byte)((running + x1) >> 3);
                running += x5 - x0;
                dst[1 * stride] = (byte)((running + x2) >> 3);
                running += x6 - x0;
                dst[2 * stride] = (byte)((running + x3) >> 3);
                running += x7 - x0;
                dst[3 * stride] = (byte)((running + x4) >> 3);
                running += x8 - x1;
                dst[4 * stride] = (byte)((running + x5) >> 3);
                running += x9 - x2;
                dst[5 * stride] = (byte)((running + x6) >> 3);
                running += x9 - x3;
                dst[6 * stride] = (byte)((running + x7) >> 3);
                running += x9 - x4;
                dst[7 * stride] = (byte)((running + x8) >> 3);
            } else {
                int delta = context->field38[(3*(x5-x4) - x6 + 4 + x3) >> 3];
                dst[3 * stride] = g_bfmeClampTable[x4 + delta];
                dst[4 * stride] = g_bfmeClampTable[x5 - delta];
                dst[0 * stride] = src[1 * stride];
                dst[1 * stride] = src[2 * stride];
                dst[2 * stride] = src[3 * stride];
                dst[5 * stride] = src[6 * stride];
                dst[6 * stride] = src[7 * stride];
                dst[7 * stride] = src[8 * stride];
            }
            ++src; ++dst;
        }
        if (current != first) {
            dst = destination - 8*stride + 8*(current-first);
            src = dst - 5;
            dst -= 4;
            for (unsigned j = 0; j < 8; ++j) {
            x0 = src[0];
            x1 = src[1];
            x2 = src[2];
            x3 = src[3];
            x4 = src[4];
            x5 = src[5];
            x6 = src[6];
            x7 = src[7];
            x8 = src[8];
            x9 = src[9];
            d1 = x1 - x0;
            if (d1 <= 0) d1 = x0 - x1;
            d2 = x2 - x1;
            if (d2 <= 0) d2 = x1 - x2;
            d3 = x3 - x2;
            if (d3 <= 0) d3 = x2 - x3;
            d4 = x4 - x3;
            if (d4 <= 0) d4 = x3 - x4;
            sum1 = d1 + d2 + d3 + d4;
            d1 = x5 - x6;
            if (d1 <= 0) d1 = x6 - x5;
            d2 = x6 - x7;
            if (d2 <= 0) d2 = x7 - x6;
            d3 = x7 - x8;
            if (d3 <= 0) d3 = x8 - x7;
            d4 = x8 - x9;
            if (d4 <= 0) d4 = x9 - x8;
            sum2 = d1 + d2 + d3 + d4;
            context->field28[current - 1] += sum1 > 255 ? 255 : sum1;
            context->field28[current] += sum2 > 255 ? 255 : sum2;
            if (sum1 < limit && sum2 < limit && x5 - x4 < q && x4 - x5 < q) {
                running = x4 + 3*x0 + x3 + x2 + 4 + x1;
                dst[0] = (byte)((running + x1) >> 3);
                running += x5 - x0;
                dst[1] = (byte)((running + x2) >> 3);
                running += x6 - x0;
                dst[2] = (byte)((running + x3) >> 3);
                running += x7 - x0;
                dst[3] = (byte)((running + x4) >> 3);
                running += x8 - x1;
                dst[4] = (byte)((running + x5) >> 3);
                running += x9 - x2;
                dst[5] = (byte)((running + x6) >> 3);
                running += x9 - x3;
                dst[6] = (byte)((running + x7) >> 3);
                running += x9 - x4;
                dst[7] = (byte)((running + x8) >> 3);
            } else {
                int delta = context->field38[(3*(x5-x4) - x6 + 4 + x3) >> 3];
                dst[3] = g_bfmeClampTable[x4 + delta];
                dst[4] = g_bfmeClampTable[x5 - delta];
            }
                src += stride; dst += stride;
            }
        }
    }
}
