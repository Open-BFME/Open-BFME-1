// Open-BFME5 conversions.

extern "C" double __cdecl tan(double a);

extern const float g_rva0107533C;
extern const float g_rva01075350;
// Retail VA 0x010F6938 .rdata bytes f9021550 = 1e10f; owned here once.
extern const float g_bfmeK1258C = 1.0e10f;


float __stdcall bfmeCot1258(float x)
{
	float t;

	t = (float)tan(*(volatile float *)&x * g_rva0107533C);
	if (t != g_rva01075350)
		return 12.0f / t;
	return g_bfmeK1258C;
}
