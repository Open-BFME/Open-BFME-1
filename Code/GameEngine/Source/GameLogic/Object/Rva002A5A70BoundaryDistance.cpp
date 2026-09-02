// cl: /O2 /Ob2 /G6
// Open-BFME5: clean C++ conversion of the retail single-box distance wrapper.

typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object
{
public:
	Real bfmeSingleBoxBoundaryDistanceSquared2D(
		const Coord3D *position,
		const Object *other,
		const Coord3D *otherPosition) const;

	Real bfmeBoundaryDistanceSquared2D(const Object *other) const;

private:
	unsigned char m_pad000[0x38];
	Coord3D m_position;
};

Real Object::bfmeBoundaryDistanceSquared2D(const Object *other) const
{
	return bfmeSingleBoxBoundaryDistanceSquared2D(
		&m_position, other, &other->m_position);
}
