// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: BFME W3DPropBuffer construction clearing, retail 0x007039E0.

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

struct Vector3
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

struct SphereClass
{
	Vector3 Center;
	Real Radius;
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
		const GeometryInfo &that, const Coord3D &that_pos, Real that_angle) const;

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
class BfmeRenderObj
{
public:
	virtual void Delete_This();

	void Release_Ref()
	{
		--m_refs;
		if (m_refs == 0)
			Delete_This();
	}

private:
	int m_refs;
};

struct BfmeProp
{
	BfmeRenderObj *m_robj;
	int id;
	Coord3D location;
	int prop_type;
	int shroud_status;
	int visible;
	SphereClass bounds;
};

class W3DPropBuffer
{
public:
	void removePropsForConstruction(const Coord3D *pos,
		const GeometryInfo &geom, Real angle);

private:
	void *m_snapshot_vtable;
	BfmeProp m_props[4000];
	int m_num_props;
	Bool m_anything_changed;
};

void W3DPropBuffer::removePropsForConstruction(const Coord3D *pos,
	const GeometryInfo &geom, Real angle)
{
	int i;
	for (i = 0; i < m_num_props; ++i)
	{
		if (m_props[i].m_robj == 0)
			continue;

		Real radius = m_props[i].bounds.Radius;
		GeometryInfo info(GEOMETRY_CYLINDER, false,
			5 * radius, 2 * radius, 2 * radius);

		if (geom.bfmeIntersects(*pos, angle, info,
			m_props[i].location, 0.0f))
		{
			m_props[i].location.set(0, 0, 0);
			BfmeRenderObj *robj = m_props[i].m_robj;
			m_props[i].prop_type = -1;
			if (robj != 0)
			{
				robj->Release_Ref();
				m_props[i].m_robj = 0;
			}
			m_props[i].bounds.Center.set(0, 0, 0);
			m_props[i].bounds.Radius = 1;
			m_anything_changed = true;
		}
	}
}
