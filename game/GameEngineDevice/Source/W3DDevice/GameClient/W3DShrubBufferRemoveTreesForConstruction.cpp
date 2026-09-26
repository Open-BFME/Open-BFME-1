// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// W3DShrubBuffer construction clearing, retail 0x00721F40.

#include <vector>

typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void set(Real nx, Real ny, Real nz)
	{
		x = nx;
		y = ny;
		z = nz;
	}
};

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

template <typename T>
class StringBase
{
public:
	~StringBase();

private:
	void *m_data;
};

struct GeometryShape
{
	int m_type;
	Real m_height;
	Real m_major_radius;
	char m_unmodelled_00c[0x0C];
	Real m_offset_z;
	StringBase<char> m_name;
	Bool m_enabled;
	char m_unmodelled_21[0x03];
};

struct GeometryRecord
{
	int m_first;
	int m_second;
	int m_third;
	StringBase<char> m_name;
};

class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void unknown();
};

class GeometryInfo : public Snapshot
{
public:
	GeometryInfo(GeometryType type, Bool is_small, Real height,
		Real major_radius, Real minor_radius);

	Bool bfmeIntersects(const Coord3D &this_pos, Real this_angle,
		const GeometryInfo &that, const Coord3D &that_pos,
		Real that_angle) const;

private:
	Bool m_is_small;
	int m_scalar08;
	int m_scalar0c;
	int m_scalar10;
	int m_scalar14;
	int m_scalar18;
	int m_scalar1c;
	int m_scalar20;
	int m_scalar24;
	int m_scalar28;
	std::vector<GeometryShape> m_shapes;
	std::vector<GeometryRecord> m_records;
	int m_cached44;
	int m_cached48;
	int m_cached4c;
	int m_cached50;
	int m_cached54;
	int m_cached58;
};

struct Rva00721F40Tree
{
	Coord3D m_location;
	char m_pad0c[0x34];
	int m_treeType;
	char m_pad44[0x60];
};

class W3DShrubBuffer
{
public:
	void removeTreesForConstruction(const Coord3D *pos,
		const GeometryInfo &geom, Real angle);

private:
	char m_pad00[0x1548];
	Rva00721F40Tree m_trees[12000];
	int m_numTrees;
	Bool m_anythingChanged;
};

void W3DShrubBuffer::removeTreesForConstruction(const Coord3D *pos,
	const GeometryInfo &geom, Real angle)
{
	for (int i = 0; i < m_numTrees; ++i)
	{
		if (m_trees[i].m_treeType < 0)
			continue;

		GeometryInfo info(GEOMETRY_CYLINDER, false,
			5 * 7.0f, 2 * 7.0f, 2 * 7.0f);
		Coord3D treePos;
		treePos.set(m_trees[i].m_location.x,
			m_trees[i].m_location.y, m_trees[i].m_location.z);
		if (geom.bfmeIntersects(*pos, angle, info, treePos, 0.0f))
		{
			m_trees[i].m_treeType = -2;
			m_anythingChanged = true;
		}
	}
}
