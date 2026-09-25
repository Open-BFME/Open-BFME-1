// cl: /DNDEBUG /MD /EHsc-
// ?rva001E2560@Object@@QBE?AUCoord3D@@PBU2@@Z
// BFME Object helper at retail RVA 0x001E2560 (170 bytes).
//
// Owner: Weapon::computeApproachTarget (0x001E43D0) calls this through ILT
// 0x00023420 with ECX = its `source` Object and pushes its `const Coord3D *pos`
// argument; it then reads the three result dwords through EAX, so the body
// returns a Coord3D by value (hidden result slot, ret 8). This is the slot where
// Zero Hour called ThePartitionManager->getVectorTo(source, pos, ...) before
// flipping the vector. The sibling 0x001E3E40 does the same for an Object and
// subtracts both objects' +0xBC values. The method name is not recovered, so it
// keeps the address.
//
// Body: the planar delta from 0x00148960 (reached through ILT 0x0000B00F; it
// reads this+0x38/+0x3C and stores z = 0), its length, then either the zero
// vector (three loads of the 0.0f constant at 0x01075350) or the delta scaled
// by (length - radius) / length.
//
// Shape: the result is `delta` changed in place with Zero Hour's inline
// Coord3D::set and Coord3D::scale, then returned. BFME's Coord3D has a
// field-wise copy constructor (coord3d.h declares one, and the matched
// 0x00148960 return type in Bfme5ThirtyEight.cpp needs one). That is why the
// return copy computes all three values before the fxch st(2) and the three
// ordered stores through the reloaded result pointer.

extern "C" double sqrt(double x);
#pragma intrinsic(sqrt)

typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &o)
	{
		x = o.x;
		y = o.y;
		z = o.z;
	}

	Real length(void) const { return (Real)sqrt(x * x + y * y + z * z); }

	void scale(Real scale)
	{
		x *= scale;
		y *= scale;
		z *= scale;
	}

	void set(Real ax, Real ay, Real az)
	{
		x = ax;
		y = ay;
		z = az;
	}

	Real x;
	Real y;
	Real z;
};

extern const Real BfmeZeroRange;			///< retail 0x01075350, 0.0f

class Object
{
public:
	Coord3D rva00148960(const Coord3D *pos) const;	///< retail ILT 0x0000B00F -> 0x00148960
	Coord3D rva001E2560(const Coord3D *pos) const;

	unsigned char m_bfmeHeadDH[0xbc];
	Real m_float0BC;				///< retail this+0xbc
};

Coord3D Object::rva001E2560(const Coord3D *pos) const
{
	Coord3D delta = rva00148960(pos);
	Real dist = delta.length();
	Real radius = m_float0BC;
	if (dist <= radius)
		delta.set(BfmeZeroRange, BfmeZeroRange, BfmeZeroRange);
	else
		delta.scale((dist - radius) / dist);
	return delta;
}
