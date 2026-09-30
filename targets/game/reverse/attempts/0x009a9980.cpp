// ?Rva009A9980@@YAXPBEHIIPAEHII@Z
// partial score=0.5871 date=2026-09-30
void __cdecl Rva009A9980(const unsigned char *source, int sourcePitch, unsigned int step, unsigned int sourceCount, unsigned char *destination, int destinationPitch, unsigned int ratio, unsigned int outputCount)
{
 unsigned int denominator = ratio;
 unsigned int half = denominator >> 1;
 unsigned char left = *source;
 source += sourcePitch;
 unsigned char *right = (unsigned char *)&ratio;
 *right = *source;
 unsigned int total = destinationPitch * outputCount;
 unsigned int output = 0;
 unsigned int phase = 0;
 unsigned int leftWeight = denominator;
 if (total > 0) {
  do {
   destination[output] = (unsigned char)((*right * phase + half + left * leftWeight) / denominator);
   phase += step;
   while (phase > denominator) {
    left = *source;
    *right = source[sourcePitch];
    source += sourcePitch;
    phase -= denominator;
   }
   output += destinationPitch;
   leftWeight = denominator - phase;
  } while (output < total);
 }
}
