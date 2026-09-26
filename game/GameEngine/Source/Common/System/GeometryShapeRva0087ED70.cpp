// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /G6 /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME: GeometryShape::rva0087ED70, retail 0x0087ED70, 228 bytes.
//
// The per-shape bounding-sphere reach that GeometryInfo::calcBoundingStuff
// (0x0087EE60, direct call at +0x4E) folds into its sphere radius with ecx on
// a 0x24-byte GeometryShape element; the adjacent 0x0087ED00 is the planar
// (circle) counterpart.  The field names follow the Geometry* FieldParse
// entries; the method name is unproven, so it keeps its address (pin in
// targets/game/reverse/symbols.csv).
//
// Shape notes: the box case keeps its three extents in named locals and
// groups the first two squares explicitly (MSVC 7.1 honours the parentheses
// when ordering the x87 multiplies); the cylinder squares and accumulates
// into its planar-reach local before the sqrt.  Both place retail's x87
// stack slots.

#include "coord.h"

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

inline Real sqr(Real x)
{
	return x * x;
}

struct GeometryShape
{
	GeometryType m_type;
	Real m_height;
	Real m_majorRadius;
	Real m_minorRadius;
	Coord3D m_offset;

	Real rva0087ED70() const;
};

// ?rva0087ED70@GeometryShape@@QBEMXZ
Real GeometryShape::rva0087ED70() const
{
	Real result = 0.0f;
	switch (m_type)
	{
		case GEOMETRY_SPHERE:
			result = sqrt(sqr(m_offset.x) + sqr(m_offset.y) + sqr(m_offset.z)) + m_majorRadius;
			break;

		case GEOMETRY_CYLINDER:
		{
			Real planar = sqrt(sqr(m_offset.x) + sqr(m_offset.y)) + m_majorRadius;
			Real vertical = fabs(m_offset.z) + m_height * 0.5;
			Real offsetLength = sqrt(sqr(m_offset.x) + sqr(m_offset.y) + sqr(m_offset.z));
			planar = sqr(planar);
			planar += sqr(vertical);
			result = sqrt(planar) + offsetLength;
			break;
		}

		case GEOMETRY_BOX:
		{
			Real x = fabs(m_offset.x) + m_majorRadius;
			Real y = fabs(m_offset.y) + m_minorRadius;
			Real z = fabs(m_offset.z) + m_height * 0.5;
			result = sqrt((sqr(x) + sqr(y)) + sqr(z));
			break;
		}
	}
	return result;
}
