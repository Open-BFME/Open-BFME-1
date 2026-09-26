// ?Rva009A9980@@YAXPBEHIIPAEHII@Z
// partial score=0.69 date=2026-09-27
void __cdecl Rva009A9980(
    const unsigned char *source, int sourcePitch, unsigned int step,
    unsigned int sourceCount, unsigned char *destination, int destinationPitch,
    unsigned int ratio, unsigned int outputCount)
{
    unsigned int denominator = ratio;
    unsigned int halfRatio = denominator >> 1;
    const unsigned char *sample = source;
    unsigned char left = *sample;
    sample += sourcePitch;
    unsigned char *right = (unsigned char *)&ratio;
    *right = *sample;
    unsigned int total = destinationPitch * outputCount;
    unsigned int output = 0;
    unsigned int phase = 0;
    if (total > 0) {
        do {
            destination[output] = (unsigned char)((left * (denominator - phase) + *right * phase + halfRatio) / denominator);
            phase += step;
            while (phase > denominator) {
                left = *sample;
                *right = sample[sourcePitch];
                sample += sourcePitch;
                phase -= denominator;
            }
            output += destinationPitch;
        } while (output < total);
    }
}
