// Open-BFME5 conversions.

extern "C" double __cdecl tan(double a);

extern const float g_bfmeK1258A;
extern const float g_bfmeK1258B;
extern const float g_bfmeK1258C;
extern const float g_bfmeK1258D;

float __stdcall bfmeCot1258(float x)
{
	float t;

	t = (float)tan(*(volatile float *)&x * g_bfmeK1258A);
	if (t != g_bfmeK1258B)
		return g_bfmeK1258D / t;
	return g_bfmeK1258C;
}
