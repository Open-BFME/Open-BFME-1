// ?getBoundingSphereRadius@GeometryShape@@QBEMXZ
// partial score=0.92 date=2026-09-17
// cl: /DNDEBUG /MD /EHsc

#include <math.h>

typedef float Real;

inline Real geometrySqr(Real value)
{
	return value * value;
}

enum GeometryType
{
	GEOMETRY_SPHERE,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class GeometryShape
{
public:
	Real getBoundingSphereRadius() const;

private:
	GeometryType m_type;
	Real m_height;
	Real m_majorRadius;
	Real m_minorRadius;
	Coord3D m_centerOffset;
};

Real GeometryShape::getBoundingSphereRadius() const
{
	Real result = 0.0f;
	switch (m_type)
	{
		case GEOMETRY_SPHERE:
			result = sqrt(geometrySqr(m_centerOffset.x) +
				geometrySqr(m_centerOffset.y) +
				geometrySqr(m_centerOffset.z)) + m_majorRadius;
			break;

		case GEOMETRY_CYLINDER:
			result = sqrt(
				geometrySqr(sqrt(geometrySqr(m_centerOffset.x) +
					geometrySqr(m_centerOffset.y)) + m_majorRadius) +
				geometrySqr(fabs(m_centerOffset.z) + m_height * 0.5)) +
				sqrt(geometrySqr(m_centerOffset.x) +
					geometrySqr(m_centerOffset.y) +
					geometrySqr(m_centerOffset.z));
			break;

		case GEOMETRY_BOX:
			result = sqrt(
				geometrySqr(fabs(m_centerOffset.x) + m_majorRadius) +
				geometrySqr(fabs(m_centerOffset.y) + m_minorRadius) +
				geometrySqr(fabs(m_centerOffset.z) + m_height * 0.5));
			break;
	}
	return result;
}
