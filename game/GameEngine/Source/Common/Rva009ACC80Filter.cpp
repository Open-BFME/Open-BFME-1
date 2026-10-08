// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Sample and variance fields are witnessed at context offsets 0x24 and 0x28.

struct Rva009ACC80Context
{
    unsigned char m_pad00[0x24];
    unsigned int *m_tableIndex;
    int *m_variance;
};

// ?Rva009ACC80Filter@@YAXPAURva009ACC80Context@@PAE1IIHPBI@Z
void __cdecl Rva009ACC80Filter(Rva009ACC80Context *ctx, unsigned char *source, unsigned char *destination, unsigned int stride, unsigned int count, int first, const unsigned int *limits)
{
    unsigned int index;
    int samples[10];
    int sumLeft, sumRight, varianceLeft, varianceRight, rolling;
    int limit, varianceLimit;
    unsigned char *rowInput, *rowOutput;
    for (index = first; index < first + count - 1; ++index) {
        limit = limits[ctx->m_tableIndex[index + 1]];
        varianceLimit = (limit * limit * 3) >> 5;
        rowInput = source + 8 * (index - first + 1);
        rowOutput = destination + 8 * (index - first + 1);
        for (unsigned int row = 0; row < 8; ++row) {
            samples[1] = rowInput[-4];
            samples[2] = rowInput[-3];
            samples[3] = rowInput[-2];
            samples[4] = rowInput[-1];
            samples[5] = rowInput[0];
            samples[6] = rowInput[1];
            samples[7] = rowInput[2];
            samples[8] = rowInput[3];
            sumLeft = sumRight = varianceLeft = varianceRight = 0;
            for (unsigned int k = 1; k <= 4; ++k) {
                sumLeft += samples[k];
                varianceLeft += samples[k] * samples[k];
                sumRight += samples[k + 4];
                varianceRight += samples[k + 4] * samples[k + 4];
            }
            varianceLeft -= ((sumLeft + 1) >> 1) * (sumLeft >> 1);
            varianceRight -= ((sumRight + 1) >> 1) * (sumRight >> 1);
            ctx->m_variance[index] += varianceLeft;
            ctx->m_variance[index + 1] += varianceRight;
            if (varianceLeft < varianceLimit && varianceRight < varianceLimit && samples[5] - samples[4] < limit && samples[4] - samples[5] < limit) {
                int a = rowInput[-4], b = rowInput[-5];
                int difference = a - b;
                if (difference <= 0) difference = b - a;
                int left = b;
                if (difference >= limit) left = a;
                int right;
                if (((rowInput[3] - rowInput[4]) > 0 ? (rowInput[3] - rowInput[4]) : (rowInput[4] - rowInput[3])) < limit) right = rowInput[4];
                else right = rowInput[3];
                rolling = samples[4] + 3*left + samples[3] + samples[2] + 4 + samples[1];
                rowOutput[-4] = (unsigned char)(((rolling+samples[1])*2-samples[4]+samples[5])>>4);
                rolling += samples[5]-left;
                rowOutput[-3] = (unsigned char)(((rolling+samples[2])*2-samples[5]+samples[6])>>4);
                rolling += samples[6]-left;
                rowOutput[-2] = (unsigned char)(((rolling+samples[3])*2-samples[6]+samples[7])>>4);
                rolling += samples[7]-left;
                rowOutput[-1] = (unsigned char)(((rolling+samples[4])*2-samples[7]-samples[1]+left+samples[8])>>4);
                rolling += samples[8]-samples[1];
                rowOutput[0] = (unsigned char)(((rolling+samples[5])*2-samples[8]-samples[2]+right+samples[1])>>4);
                rolling += right-samples[2];
                rowOutput[1] = (unsigned char)(((rolling+samples[6])*2-samples[3]+samples[2])>>4);
                rolling += right-samples[3];
                rowOutput[2] = (unsigned char)(((rolling+samples[7])*2-samples[4]+samples[3])>>4);
                rowOutput[3] = (unsigned char)(((rolling+right+samples[8])*2-samples[5] - samples[4])>>4);
            }
            rowInput += stride;
            rowOutput += stride;
        }
    }
}
