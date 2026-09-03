// cl: /EHs-c-
//
// 2D sibling of U4Blend006095D0::blend (0x006095D0, 30B).
// Retail 0x006096A0 (86B): evaluate the +0x18 curve twice (once per component)
// and write lo + (hi - lo) * t into a Coord2D out-parameter.

class U4Curve006095D0
{
public:
	float evaluate(int t) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord2D
{
	float x;
	float y;
};

struct U4Blend006095D0
{
	char m_pad[0x18];
	U4Curve006095D0 m_curve;
	void blend2(const Coord2D *lo, const Coord2D *hi, Coord2D *out, int t) const;
};

// ?blend2@U4Blend006095D0@@QBEXPBUCoord2D@@0PAU2@H@Z
void U4Blend006095D0::blend2(const Coord2D *lo, const Coord2D *hi, Coord2D *out, int t) const
{
	int tt = t;
	const U4Curve006095D0 *curve = &m_curve;
	float k = curve->evaluate(tt);
	const Coord2D *a = lo;
	const Coord2D *b = hi;
	Coord2D *o = out;
	float lx = a->x;
	float hx = b->x;
	o->x = lx + (hx - lx) * k;
	k = curve->evaluate(tt);
	float ly = a->y;
	float hy = b->y;
	o->y = ly + (hy - ly) * k;
}
