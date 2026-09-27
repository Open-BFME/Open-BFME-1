// ?d_009add80@@YAXXZ
// partial score=0.809 date=2026-09-27
// Retail 0x009ADD80: interleaved variance-based eight-pixel edge filters.
// Retail advances current twice after the first horizontal fragment; retain it.
// The context offsets below are witnessed loads, not a claimed codec class.
// Whole-body reconstruction: no calls or EH in retail.
typedef unsigned char byte;
extern const unsigned char g_bfmeClampTable[];
void filterBand009ADD80(int context, byte *source, byte *destination,
    int stride, unsigned width, unsigned first, const int *scale)
{
    unsigned current;
    int step2 = stride * 2;
    int step3 = stride * 3;
    int step4 = stride * 4;
    int step5 = stride * 5;

    int x[10];
    int sum1, sum2, variance1, variance2, running;
    int q, limit;
    byte *src, *dst;
    for (current = first; current < first + width; ++current) {
        src = source + 8 * (current - first);
        dst = destination + 8 * (current - first);
        q = scale[(*(int **)(context + 0x24))[current + width]];
        limit = (q * q * 3) >> 5;
        for (unsigned j = 0; j < 8; ++j) {
            x[1] = src[-step4];
            x[2] = src[-step3];
            x[4] = src[-1 * stride];
            x[3] = src[-step2];
            x[6] = src[1 * stride];
            x[5] = src[0 * stride];
            x[8] = src[step3];
            x[7] = src[step2];
            sum1 = x[3] + x[4] + x[2] + x[1];
            sum2 = x[7] + x[8] + x[6] + x[5];
            variance1 = x[4]*x[4] + x[3]*x[3] + x[2]*x[2] + x[1]*x[1]
                - ((sum1 + 1) >> 1) * (sum1 >> 1);
            variance2 = x[8]*x[8] + x[7]*x[7] + x[6]*x[6] + x[5]*x[5]
                - ((sum2 + 1) >> 1) * (sum2 >> 1);
            (*(int **)(context + 0x28))[current] += variance1;
            (*(int **)(context + 0x28))[current + width] += variance2;
            if (variance1 < limit && variance2 < limit &&
                x[5] - x[4] < q && x[4] - x[5] < q) {
                int a = src[-step4], b = src[-step5];
                int difference = a - b;
                if (difference <= 0) difference = b - a;
                x[0] = difference < q ? b : a;
                a = src[step3]; b = src[step4];
                difference = a - b;
                if (difference <= 0) difference = b - a;
                x[9] = difference < q ? b : a;
                running = x[4] + 3*x[0] + x[3] + x[2] + 4 + x[1];
                dst[-step4] = (byte)(((running + x[1])*2 - x[4] + x[5]) >> 4);
                running += x[5] - x[0];
                dst[-step3] = (byte)(((running + x[2])*2 - x[5] + x[6]) >> 4);
                running += x[6] - x[0];
                dst[-step2] = (byte)(((running + x[3])*2 - x[6] + x[7]) >> 4);
                running += x[7] - x[0];
                dst[-1 * stride] = (byte)(((running + x[4])*2 - x[7] - x[1] + x[0] + x[8]) >> 4);
                running += x[8] - x[1];
                dst[0] = (byte)(((running + x[5])*2 - x[8] - x[2] + x[9] + x[1]) >> 4);
                running += x[9] - x[2];
                dst[1 * stride] = (byte)(((running + x[6])*2 - x[3] + x[2]) >> 4);
                running += x[9] - x[3];
                dst[step2] = (byte)(((running + x[7])*2 - x[4] + x[3]) >> 4);
                dst[step3] = (byte)(((running + x[9] + x[8])*2 - x[5] - x[4]) >> 4);
            } else {
                int delta = (*(int **)(context + 0x38))[(3*(x[5]-x[4]) - x[6] + 4 + x[3]) >> 3];
                dst[-stride] = g_bfmeClampTable[x[4] + delta];
                dst[0] = g_bfmeClampTable[x[5] - delta];
                dst[-step4] = src[-step4];
                dst[-step3] = src[-step3];
                dst[-step2] = src[-step2];
                dst[1 * stride] = src[1 * stride];
                dst[step2] = src[step2];
                dst[step3] = src[step3];
            }
            ++src; ++dst;
        }
        if (current == first) {
            ++current;
        } else {

        dst = destination - 8 * stride + 8 * (current - first);
        src = dst;
        q = scale[(*(int **)(context + 0x24))[current]];
        limit = (q * q * 3) >> 5;
        for (unsigned j = 0; j < 8; ++j) {
            x[1] = src[-4];
            x[2] = src[-3];
            x[3] = src[-2];
            x[4] = src[-1];
            x[5] = src[0];
            x[6] = src[1];
            x[7] = src[2];
            x[8] = src[3];
            sum1 = x[3] + x[4] + x[2] + x[1];
            sum2 = x[7] + x[8] + x[6] + x[5];
            variance1 = x[4]*x[4] + x[3]*x[3] + x[2]*x[2] + x[1]*x[1]
                - ((sum1 + 1) >> 1) * (sum1 >> 1);
            variance2 = x[8]*x[8] + x[7]*x[7] + x[6]*x[6] + x[5]*x[5]
                - ((sum2 + 1) >> 1) * (sum2 >> 1);
            (*(int **)(context + 0x28))[current - 1] += variance1;
            (*(int **)(context + 0x28))[current] += variance2;
            if (variance1 < limit && variance2 < limit &&
                x[5] - x[4] < q && x[4] - x[5] < q) {
                int a = src[-4], b = src[-5];
                int difference = a - b;
                if (difference <= 0) difference = b - a;
                x[0] = difference < q ? b : a;
                a = src[3]; b = src[4];
                difference = a - b;
                if (difference <= 0) difference = b - a;
                x[9] = difference < q ? b : a;
                running = x[4] + 3*x[0] + x[3] + x[2] + 4 + x[1];
                dst[-4] = (byte)(((running + x[1])*2 - x[4] + x[5]) >> 4);
                running += x[5] - x[0];
                dst[-3] = (byte)(((running + x[2])*2 - x[5] + x[6]) >> 4);
                running += x[6] - x[0];
                dst[-2] = (byte)(((running + x[3])*2 - x[6] + x[7]) >> 4);
                running += x[7] - x[0];
                dst[-1] = (byte)(((running + x[4])*2 - x[7] - x[1] + x[0] + x[8]) >> 4);
                running += x[8] - x[1];
                dst[0] = (byte)(((running + x[5])*2 - x[8] - x[2] + x[9] + x[1]) >> 4);
                running += x[9] - x[2];
                dst[1] = (byte)(((running + x[6])*2 - x[3] + x[2]) >> 4);
                running += x[9] - x[3];
                dst[2] = (byte)(((running + x[7])*2 - x[4] + x[3]) >> 4);
                dst[3] = (byte)(((running + x[9] + x[8])*2 - x[5] - x[4]) >> 4);
            } else {
                int delta = (*(int **)(context + 0x38))[(3*(x[5]-x[4]) - x[6] + 4 + x[3]) >> 3];
                dst[-1] = g_bfmeClampTable[x[4] + delta];
                dst[0] = g_bfmeClampTable[x[5] - delta];
            }
            src += stride; dst += stride;
        }
    }
    }
}
