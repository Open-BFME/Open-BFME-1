// Open-BFME5 conversions.

extern const float g_bfmeK1266A;
extern const float g_bfmeK1266B;
extern const float g_bfmeK1266C;
extern const float g_bfmeK1266D;

float bfmeSpline1266(float p0, float p1, float p2, float p3, float t)
{
	return ((((*(volatile float *)&p1 * g_bfmeK1266A - p0 - *(volatile float *)&p2 * g_bfmeK1266A + p3) * t
		+ (p0 + p0 - *(volatile float *)&p1 * g_bfmeK1266C + *(volatile float *)&p2 * g_bfmeK1266B - p3)) * t
		+ (p2 - p0)) * t
		+ (p1 + p1)) * g_bfmeK1266D;
}
