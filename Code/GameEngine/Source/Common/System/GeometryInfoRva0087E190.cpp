// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME: GeometryInfo method at retail 0x0087E190, 469 bytes; the
// method's name is not proven, so it keeps its address.
//
// The owner is GeometryInfo: the body walks the 0x24-byte shape vector at
// this+0x2C/+0x30 that the landed GeometryInfo::parseGeometryMinorRadius
// (0x0087F220) and getMaxHeightAbovePosition (0x0087E000) read, and it calls
// getMaxHeightAbovePosition on this. Callers at 0x008F8800
// (PartitionData::updateCellsTouched) and 0x008FA4B0 pass a local shape that
// this body fills.
//
// A single shape is copied out whole. The loop then gathers a 2D bounds of the
// enabled box shapes and bails to the cylinder answer on any other type. As
// retail compiled it, the max step writes lo instead of hi, so hi stays at its
// zero initialiser (MSVC folds it to the 0.0f literal in the compare and
// (hi - lo) to -lo), and the box answer falls through into the cylinder
// answer, which overwrites it.

#include <vector>

typedef bool Bool;
typedef float Real;

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

struct Coord2D
{
	Real x, y;
};

struct Region2D
{
	Coord2D lo, hi;
};

struct Coord3D
{
	Real x, y, z;
};

// The shape vector's element. The ledger names its copy-assignment operator
// (0x000FC640, reached through the 0x00040F43 thunk) by address, so the class
// carries that name here. Layout as in GeometryParseActiveAndOffset.cpp.
class Rva000FC640
{
public:
	Rva000FC640 &operator=(const Rva000FC640 &other);

	GeometryType m_type;
	Real m_height;
	Real m_majorRadius;
	Real m_minorRadius;
	Coord3D m_offset;
	char m_name[0x04];
	Bool m_enabled;
	char m_unmodelled21[0x03];
};

// Reference-returning, so MSVC selects the address of the winner and reloads
// through it.
template <class T>
inline const T &bfmeMin(const T &a, const T &b)
{
	return (a < b) ? a : b;
}

template <class T>
inline const T &bfmeMax(const T &a, const T &b)
{
	return (a > b) ? a : b;
}

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition(void) const;
	void rva0087E190(Rva000FC640 &out) const;

private:
	void *m_vtbl;
	Bool m_isSmall;
	int m_scalar08;
	int m_scalar0c;
	Real m_scalar10;
	int m_scalar14;
	int m_scalar18;
	int m_scalar1c;
	int m_scalar20;
	int m_scalar24;
	int m_scalar28;
	std::vector<Rva000FC640> m_shapes;
};

void GeometryInfo::rva0087E190(Rva000FC640 &out) const
{
	if (m_shapes.size() == 1)
		out = m_shapes[0];

	Region2D bounds;
	bounds.lo.x = bounds.lo.y = bounds.hi.x = bounds.hi.y = 0.0f;
	Real maxZ = 0.0f;

	for (std::vector<Rva000FC640>::const_iterator it = m_shapes.begin(); it != m_shapes.end(); ++it)
	{
		if (!it->m_enabled)
			continue;
		if (it->m_type != GEOMETRY_BOX)
			goto cylinder;

		bounds.lo.x = bfmeMin(bounds.lo.x, it->m_offset.x - it->m_majorRadius);
		bounds.lo.y = bfmeMin(bounds.lo.y, it->m_offset.y - it->m_minorRadius);
		bounds.lo.x = bfmeMax(bounds.hi.x, it->m_offset.x - it->m_majorRadius);
		bounds.lo.y = bfmeMax(bounds.hi.y, it->m_offset.y - it->m_minorRadius);
		maxZ = bfmeMax(maxZ, it->m_height);
	}

	out.m_type = GEOMETRY_BOX;
	out.m_majorRadius = (bounds.hi.x - bounds.lo.x) * 0.5f;
	out.m_minorRadius = (bounds.hi.y - bounds.lo.y) * 0.5f;
	out.m_offset.x = bounds.lo.x + out.m_majorRadius;
	out.m_offset.y = bounds.lo.y + out.m_minorRadius;
	out.m_offset.z = 0.0f;

cylinder:
	out.m_type = GEOMETRY_CYLINDER;
	out.m_majorRadius = m_scalar10;
	out.m_minorRadius = m_scalar10;
	out.m_height = getMaxHeightAbovePosition();
	Coord3D zero;
	zero.x = 0.0f;
	zero.y = 0.0f;
	zero.z = 0.0f;
	out.m_offset = zero;
}
