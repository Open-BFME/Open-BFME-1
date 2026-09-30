// cl: /DNDEBUG /MD /EHs-c-
//
// Retail 0x006FCC10 is a member helper with unused this and four 32-bit
// arguments: three Real values and a Real* fractional-result slot. Retail
// caller 0x006FCCC0 establishes the member ABI; the owner remains neutral.
// The body first rejects a non-positive upper-lower range, clamps
// the first value into that interval, scales the normalized fraction by the
// retail 50.0f at 0x0107FAA8, subtracts the 1.0f global at 0x01075334, then
// writes the fractional part after CRT floor and returns the integer
// conversion of that scaled value.

extern "C" __declspec(dllimport) double __cdecl floor(double value);
extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;

#define Rva006FCC10Scale50 (50.0f)

class Rva006FCCC0Owner
{
public:
	float rva006FCCC0(float x, float y, float unused);
	int rva006FCC10(float value, float lower, float upper, float *fraction);

private:
	char m_unreconstructed_000[0x120];
	float m_120;
	float m_124;
	float m_128;
	float m_12c;
	float m_130;
	char m_unreconstructed_134[0x24];
	float m_158[2551]; // Maximum sampled offset: 49 * 50 + 49 + 51.
};

int Rva006FCCC0Owner::rva006FCC10(float value, float lower, float upper, float *fraction)
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



float Rva006FCCC0Owner::rva006FCCC0(float x, float y, float unused)
{
	float zero = BfmeZeroRange;
	if (m_12c == zero || m_130 == zero)
		return zero;

	float fx = zero, fy = zero;
	int ix = rva006FCC10(x, m_120 - m_12c, m_120 + m_12c, &fx);
	int iy = rva006FCC10(y, m_124 - m_130, m_124 + m_130, &fy);
	int index = ix * 50 + iy;
	float base0 = m_158[index], base1 = m_158[index + 1];
	float lower = base0 + (m_158[index + 50] - base0) * fx;
	float upper = base1 + (m_158[index + 51] - base1) * fx;
	return lower + (upper - lower) * fy;
}
