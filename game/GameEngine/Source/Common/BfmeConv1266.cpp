// Open-BFME5 conversions.

float bfmeSpline1266(float p0, float p1, float p2, float p3, float t)
{
	return ((((*(volatile float *)&p1 * 3.0f - p0 - *(volatile float *)&p2 * 3.0f + p3) * t
		+ (p0 + p0 - *(volatile float *)&p1 * 5.0f + *(volatile float *)&p2 * 4.0f - p3)) * t
		+ (p2 - p0)) * t
		+ (p1 + p1)) * 0.5f;
}
