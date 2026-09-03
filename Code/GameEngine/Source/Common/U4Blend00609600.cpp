// cl: /EHs-c-
//
// 3D sibling of U4Blend006095D0::blend2 (0x006096A0, 86B).
// Retail 0x00609600 (117B): evaluate the +0x18 curve three times and write
// lo + (hi - lo) * t into a Coord3D out-parameter.

class U4Curve006095D0
{
public:
	float evaluate(int t) const;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct U4Blend006095D0
{
	char m_pad[0x18];
	U4Curve006095D0 m_curve;
	void blend3(const Coord3D *lo, const Coord3D *hi, Coord3D *out, int t) const;
};

// ?blend3@U4Blend006095D0@@QBEXPBUCoord3D@@0PAU2@H@Z
void U4Blend006095D0::blend3(const Coord3D *lo, const Coord3D *hi, Coord3D *out, int t) const
{
	int tt = t;
	const U4Curve006095D0 *curve = &m_curve;
	float k = curve->evaluate(tt);
	const Coord3D *a = lo;
	const Coord3D *b = hi;
	Coord3D *o = out;
	float lx = a->x;
	float hx = b->x;
	o->x = lx + (hx - lx) * k;
	k = curve->evaluate(tt);
	float ly = a->y;
	float hy = b->y;
	o->y = ly + (hy - ly) * k;
	k = curve->evaluate(tt);
	float lz = a->z;
	float hz = b->z;
	o->z = lz + (hz - lz) * k;
}
