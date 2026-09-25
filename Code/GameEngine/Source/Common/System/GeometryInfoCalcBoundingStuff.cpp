// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /G6 /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: GeometryInfo::calcBoundingStuff, retail 0x0087EE60, 301 bytes.
//
// Identity: the matched GeometryInfo::parseGeometryIsSmall (0x0087F160)
// tail-calls this body (jmp at +0x1B) on the INI store, and the matched
// parseGeometryHeight (0x0087F180) calls it and then calls 0x0087EBB0.
// It rebuilds the bounding circle (+0x10) and sphere (+0x14) radii as the
// maximum over the enabled 0x24-byte GeometryShape entries at +0x2C, then
// derives the centre and two extents from the bounds helper at 0x0087E650.
//
// The two per-shape radius helpers (0x0087ED00, 0x0087ED70) precede this body
// in the same retail TU and are given their bodies here under noinline: retail
// keeps the shape pointer in EDX across both calls, which MSVC 7.1 only does
// when it can see the callee does not clobber EDX.  Their method names are not
// proven, so they keep their addresses.

#include <vector>
#include "coord.h"
#include "ascii_string.h"

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

template <class T>
inline const T &bfmeMax(const T &a, const T &b)
{
	return (a > b) ? a : b;
}

struct GeometryShape
{
	GeometryType m_type;
	Real m_height;
	Real m_majorRadius;
	Real m_minorRadius;
	Coord3D m_offset;
	AsciiString m_name;
	Bool m_enabled;
	char m_unmodelled21[3];

	Real rva0087ED00() const;
	Real rva0087ED70() const;
};

typedef char GeometryShape_size_check[sizeof(GeometryShape) == 0x24 ? 1 : -1];

// Six-float bounds the 0x0087E650 helper fills: minimum x/y/z then maximum x/y/z.
struct Rva0087E650Bounds
{
	Real m_minX;
	Real m_minY;
	Real m_minZ;
	Real m_maxX;
	Real m_maxY;
	Real m_maxZ;
};

extern const Real g_bfmeK1257;	// 0.5f at retail 0x0107533C

class Snapshot
{
public:
	virtual ~Snapshot();
};

class GeometryInfo : public Snapshot
{
public:
	void rva0087E650(Rva0087E650Bounds *bounds);

private:
	void calcBoundingStuff();

	Bool m_isSmall;
	int m_scalar08;
	int m_scalar0c;
	Real m_boundingCircleRadius;
	Real m_boundingSphereRadius;
	Coord3D m_boundsCenter18;
	Real m_extent24;
	Real m_extent28;
	std::vector<GeometryShape> m_shapes;
};

// ?rva0087ED00@GeometryShape@@QBEMXZ: a semantically faithful but not
// byte-exact model of retail 0x0087ED00 (101 bytes; this compiles to 89),
// kept visible only so calcBoundingStuff's register allocation matches.
__declspec(noinline) Real GeometryShape::rva0087ED00() const
{
	Real y = m_offset.y;
	Real result = 0.0f;
	switch (m_type)
	{
		case GEOMETRY_SPHERE:
		case GEOMETRY_CYLINDER:
			result = sqrt(sqr(m_offset.x) + sqr(y)) + m_majorRadius;
			break;
		case GEOMETRY_BOX:
			result = sqrt(sqr(fabs(m_offset.x) + m_majorRadius) + sqr(fabs(y) + m_minorRadius));
			break;
	}
	return result;
}

// ?rva0087ED70@GeometryShape@@QBEMXZ: a semantically faithful but not
// byte-exact model of retail 0x0087ED70 (228 bytes; this compiles to 224),
// kept visible only so calcBoundingStuff's register allocation matches.
// The cylinder case adds the offset length, as retail does at +0x80..+0xB3.
__declspec(noinline) Real GeometryShape::rva0087ED70() const
{
	Real result = 0.0f;
	switch (m_type)
	{
		case GEOMETRY_SPHERE:
			result = sqrt(sqr(m_offset.x) + sqr(m_offset.y) + sqr(m_offset.z)) + m_majorRadius;
			break;
		case GEOMETRY_CYLINDER:
			result = sqrt(sqr(sqrt(sqr(m_offset.x) + sqr(m_offset.y)) + m_majorRadius) +
				sqr(fabs(m_offset.z) + m_height * 0.5)) +
				sqrt(sqr(m_offset.x) + sqr(m_offset.y) + sqr(m_offset.z));
			break;
		case GEOMETRY_BOX:
			result = sqrt(sqr(fabs(m_offset.x) + m_majorRadius) +
				sqr(fabs(m_offset.y) + m_minorRadius) +
				sqr(fabs(m_offset.z) + m_height * 0.5));
			break;
	}
	return result;
}

// ?calcBoundingStuff@GeometryInfo@@AAEXXZ
void GeometryInfo::calcBoundingStuff()
{
	m_boundingCircleRadius = 0.0f;
	m_boundingSphereRadius = 0.0f;

	for (std::vector<GeometryShape>::const_iterator it = m_shapes.begin(); it != m_shapes.end(); ++it)
	{
		if (!it->m_enabled)
			continue;
		m_boundingCircleRadius = bfmeMax(m_boundingCircleRadius, it->rva0087ED00());
		m_boundingSphereRadius = bfmeMax(m_boundingSphereRadius, it->rva0087ED70());
	}

	Rva0087E650Bounds bounds;
	rva0087E650(&bounds);
	m_boundsCenter18.zero();
	m_boundsCenter18.x = (bounds.m_maxX + bounds.m_minX) * g_bfmeK1257;
	m_boundsCenter18.y = (bounds.m_maxY + bounds.m_minY) * g_bfmeK1257;
	m_boundsCenter18.z = (bounds.m_maxZ + bounds.m_minZ) * g_bfmeK1257;
	m_extent24 = bfmeMax(bounds.m_maxX, -bounds.m_minX);
	m_extent28 = bfmeMax(bounds.m_maxY, -bounds.m_maxY);
}
