// Two more: a cubic curve in Horner form, and a gap that never goes negative
// before it is squared.

float bfmeBezier(float a, float b, float c, float d, float t)
{
	float rest = 1.0f - t;
	return ((a * rest + b * t * 3.0f) * rest + c * t * t * 3.0f) * rest + d * t * t * t;
}

extern "C" double sqrt(double value);
#pragma intrinsic(sqrt)

class Gen_000ED3B0
{
public:
	float bfmeGapSq(const Gen_000ED3B0 *other) const;
private:
	int m_bfmeGap[14];							// +0x00
	float m_bfmeX;								// +0x38
	float m_bfmeY;								// +0x3c
	int m_bfmeGap2[31];							// +0x40
	float m_bfmeRadius;							// +0xbc
};

float Gen_000ED3B0::bfmeGapSq(const Gen_000ED3B0 *other) const
{
	float dx = m_bfmeX - other->m_bfmeX;
	float dy = m_bfmeY - other->m_bfmeY;

	float gap = (float)sqrt(dx * dx + dy * dy) - m_bfmeRadius - other->m_bfmeRadius;
	if (gap < 0.0f)
		return 0.0f;
	return gap * gap;
}
