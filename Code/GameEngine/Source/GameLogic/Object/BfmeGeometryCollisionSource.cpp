// cl: /DNDEBUG /MD /EHsc

// Retail exposes this predicate through an unnamed collision interface.  The
// two output pointers belong to that interface but this implementation only
// reports whether the two oriented footprints intersect.

typedef float Real;

struct Coord3D
{
	Real x, y, z;
};

class GeometryInfo
{
public:
	bool bfmeIntersects(const Coord3D &thisPosition, Real thisAngle,
		const GeometryInfo &otherGeometry, const Coord3D &otherPosition,
		Real otherAngle) const;
};

class Object
{
public:
	unsigned char m_unmodelled000[0x38];
	Coord3D m_position;
	Real m_orientation;
	unsigned char m_unmodelled048[0x64];
	GeometryInfo m_geometryInfo;
};

class BfmeGeometryCollisionSource
{
public:
	unsigned char bfmeIntersectsObject(const Object *other, Coord3D *collisionLocation,
		Coord3D *collisionNormal) const;
};

unsigned char BfmeGeometryCollisionSource::bfmeIntersectsObject(const Object *other,
	Coord3D *, Coord3D *) const
{
	const char *self = reinterpret_cast<const char *>(this);
	Real otherAngle = other->m_orientation;
	Real thisAngle = *reinterpret_cast<const Real *>(self - 0x2C);
	const GeometryInfo *geometry =
		*reinterpret_cast<GeometryInfo *const *>(self + 0x98);
	const Coord3D &position =
		*reinterpret_cast<const Coord3D *>(self - 0x38);
	return geometry->bfmeIntersects(position, thisAngle,
		other->m_geometryInfo, other->m_position, otherAngle) != 0;
}
