// One more: the three-argument gap.

extern "C" double sqrt(double value);
#pragma intrinsic(sqrt)

class BfmePointNC
{
public:
	float m_bfmeX;								// +0x00
	float m_bfmeY;								// +0x04
};

class BfmeThingNC
{
public:
	int m_bfmeGap[47];							// +0x00
	float m_bfmeRadius;							// +0xbc
};

class Gen_000ED340
{
public:
	float bfmeGapSqBetween(const BfmePointNC *a, const BfmeThingNC *thing, const BfmePointNC *b) const;
private:
	int m_bfmeGap[47];							// +0x00
	float m_bfmeRadius;							// +0xbc
};

float Gen_000ED340::bfmeGapSqBetween(const BfmePointNC *a, const BfmeThingNC *thing, const BfmePointNC *b) const
{
	float dx = a->m_bfmeX - b->m_bfmeX;
	float dy = a->m_bfmeY - b->m_bfmeY;

	float gap = (float)sqrt(dx * dx + dy * dy) - m_bfmeRadius - thing->m_bfmeRadius;
	if (gap < 0.0f)
		return 0.0f;
	return gap * gap;
}
