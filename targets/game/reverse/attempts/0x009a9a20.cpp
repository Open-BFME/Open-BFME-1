// ?Rva009A9A20@@YAXPBEHIIPAEHII@Z
// partial score=0.69 date=2026-09-27
void __cdecl Rva009A9A20(
    const unsigned char *source, int sourcePitch, unsigned int step,
    unsigned int sourceCount, unsigned char *destination, int destinationPitch,
    unsigned int ratio, unsigned int outputCount)
{
    unsigned int sourceStep = (unsigned int)sourcePitch + (unsigned int)sourcePitch;
    unsigned int output = (unsigned int)destinationPitch;
    unsigned int limit = output * outputCount;
    const unsigned char *topRow = source;
    unsigned char *dest = destination;
    *dest = *topRow;
    if (output < limit) {
        const unsigned char *middleRow = topRow + sourceStep;
        do {
            unsigned int top = topRow[0];
            unsigned int center = middleRow[0];
            unsigned int bottom = middleRow[sourceStep];
            dest[output] = (unsigned char)((3 * (top + bottom) + 10 * center + 8) >> 4);
            output += (unsigned int)destinationPitch;
            topRow += sourceStep;
            middleRow += sourceStep;
        } while (output < limit);
    }
}
