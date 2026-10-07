// Open-BFME5 conversions.

float bfmeSpline1266(float p0, float p1, float p2, float p3, float t)
{
	return ((((*(volatile float *)&p1 * 3.0f - p0 - *(volatile float *)&p2 * 3.0f + p3) * t
		+ (p0 + p0 - *(volatile float *)&p1 * 5.0f + *(volatile float *)&p2 * 4.0f - p3)) * t
		+ (p2 - p0)) * t
		+ (p1 + p1)) * 0.5f;
}

// Retail 0x00064410. Evaluates each coordinate of a four-point Catmull-Rom
// curve through bfmeSpline1266 (retail calls 0x63F10 via its ILT thunk).
struct Rva00064410Point
{
	float x;
	float y;
	float z;
};

void calc(
	Rva00064410Point *out,
	const Rva00064410Point *p0,
	const Rva00064410Point *p1,
	const Rva00064410Point *p2,
	const Rva00064410Point *p3,
	float t)
{
	volatile float z = bfmeSpline1266(p0->z, p1->z, p2->z, p3->z, t);
	volatile float y = bfmeSpline1266(p0->y, p1->y, p2->y, p3->y, t);
	float x = bfmeSpline1266(p0->x, p1->x, p2->x, p3->x, t);
	out->x = x;
	out->y = y;
	out->z = z;
}
