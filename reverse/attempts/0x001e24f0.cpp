// ?bfmeGapSqAt@Gen_001E24F0@@QBEMPBUBfmePointNC@@PBVBfmeThingNC@@@Z
// partial score=0.95 date=2026-09-02
// cl: /DNDEBUG /MD /EHs-c-
// Sibling of ?bfmeGapSq@Gen_000ED3B0@@QBEMPBV1@@Z: 2D gap between a point
// and a thing, squared, never negative.

extern "C" double sqrt(double value);
#pragma intrinsic(sqrt)

struct BfmePointNC
{
	float x;
	float y;
};

class BfmeThingNC
{
public:
	unsigned char m_unreconstructed_00[0x38];
	float m_x;
	float m_y;
	unsigned char m_unreconstructed_40[0xBC - 0x40];
	float m_radius;
};

class Gen_001E24F0
{
public:
	float bfmeGapSqAt(const BfmePointNC *point, const BfmeThingNC *thing) const;

private:
	unsigned char m_unreconstructed_00[0xBC];
	float m_radius;
};

float Gen_001E24F0::bfmeGapSqAt(const BfmePointNC *point, const BfmeThingNC *thing) const
{
	const BfmeThingNC *other = thing;
	const BfmePointNC *pt = point;
	float dx = pt->x - other->m_x;
	float dy = pt->y - other->m_y;
	float gap = (float)sqrt(dx * dx + dy * dy) - m_radius - other->m_radius;
	if (gap < 0.0f)
		return 0.0f;
	return gap * gap;
}
