// cl: /DNDEBUG /MD /EHsc
// Open-BFME: anonymous GeometryInfo sphere overlap helper, retail 0x00880D90,
// 61 bytes.
//
// GeometryInfo::bfmeIntersects calls this cdecl helper for the branch that
// compares two transformed circular footprints. The caller stores each
// footprint's radius at +0x08 and its x and y coordinates at +0x24 and +0x28.

typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct BfmeCollisionShape
{
	struct Geometry
	{
		unsigned char m_unmodelled_000[0x08];
		Real m_radius;
		unsigned char m_unmodelled_00c[0x24 - 0x0c];
		Real getMajorRadius() const
		{
			return m_radius;
		}
	};

	Geometry m_geometry;
	Coord3D m_position;
};

inline void vecDiff2D(const Coord3D *first, const Coord3D *second,
	Coord3D *result)
{
	result->x = first->x - second->x;
	result->y = first->y - second->y;
	result->z = 0.0f;
}

inline Real calcSqrDist2D(const Coord3D *value)
{
	return value->x * value->x + value->y * value->y;
}

inline Real sqr(Real operand)
{
	return operand * operand;
}

bool bfmeSphereOverlap(const BfmeCollisionShape *first,
	const BfmeCollisionShape *second)
{
	Coord3D diff;
	vecDiff2D(&second->m_position, &first->m_position, &diff);
	Real distSqr = calcSqrDist2D(&diff);
	Real touchingDistSqr = sqr(first->m_geometry.getMajorRadius()
		+ second->m_geometry.getMajorRadius());
	if (touchingDistSqr < distSqr)
		return false;
	return true;
}
