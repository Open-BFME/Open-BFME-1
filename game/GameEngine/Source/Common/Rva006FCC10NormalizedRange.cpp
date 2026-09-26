// cl: /DNDEBUG /MD /EHs-c-
//
// Retail 0x006FCC10 is a standalone __stdcall helper with four 32-bit
// arguments: three Real values and a Real* fractional-result slot.  No named
// caller or upstream symbol is present in this image, so the identity stays
// neutral.  The body first rejects a non-positive upper-lower range, clamps
// the first value into that interval, scales the normalized fraction by the
// retail 50.0f at 0x0107FAA8, subtracts the 1.0f global at 0x01075334, then
// writes the fractional part after CRT floor and returns the integer
// conversion of that scaled value.

extern "C" __declspec(dllimport) double __cdecl floor(double value);
extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;

#define Rva006FCC10Scale50 (*(const float *)0x0107FAA8)

int __stdcall Rva006FCC10(float value, float lower, float upper, float *fraction)
{
	float range = upper - lower;
	if (range > BfmeZeroRange)
	{
		if (value < lower)
			value = lower;
		if (value > upper)
			value = upper;

		float *out = fraction;
		register float scaled = ((value - lower) / range) * Rva006FCC10Scale50 -
			g_bfmeDefaultBU;
		float floorValue = (float)floor((double)scaled);
		*out = scaled - floorValue;
		return (int)scaled;
	}
	return 0;
}
