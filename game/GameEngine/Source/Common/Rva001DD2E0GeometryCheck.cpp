// cl: /DNDEBUG /MD /EHsc

// The caller identity remains unknown, so the class keeps the retail address.
// GeometryInfo::bfmeIntersects is the pinned retail callee at 0x0087F2F0.
// This TU uses its minimal non-polymorphic declaration because geometry.h
// describes the later polymorphic GeometryInfo layout.

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

class Rva001DD2E0Item
{
public:
	unsigned char m_head[0x38];
	Coord3D m_position;
	Real m_angle;
	unsigned char m_middle[0x64];
	GeometryInfo m_geometry;
};

class Rva001DD2E0Owner
{
public:
	bool check(Rva001DD2E0Item *item);

	unsigned char m_head[8];
	Coord3D m_position;
	GeometryInfo *m_geometry;
	Real m_angle;
	bool m_kind;
};

bool Rva001DD2E0Owner::check(Rva001DD2E0Item *item)
{
	int value = *reinterpret_cast<int *>(&item->m_angle);
	volatile int keep = value;

	return m_geometry->bfmeIntersects(m_position, m_angle, item->m_geometry,
		item->m_position, item->m_angle) == m_kind;
}

// ?check@Rva001DD2E0Owner@@QAE_NPAVRva001DD2E0Item@@@Z
