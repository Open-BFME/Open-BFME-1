// cl: /DNDEBUG /MD /EHsc

typedef float Real;

struct Coord3D
{
	Real x, y, z;
	void set(Real xIn, Real yIn, Real zIn)
	{
		x = xIn;
		y = yIn;
		z = zIn;
	}
};

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
	inline Real getMajorRadius() const { return m_majorRadius; }

private:
	unsigned char m_unmodelled_000[0x10];
	Real m_majorRadius;
};

class ObjectGeometryBoundsData
{
public:
	unsigned char m_unmodelled_000[0x38];
	Coord3D m_position;
	unsigned char m_unmodelled_044[0xac - 0x44];
	GeometryInfo m_geometryInfo;
};

class ObjectGeometryBoundsShim
{
public:
	void getMax(Coord3D &out) const;
	__forceinline const ObjectGeometryBoundsData *getObject() const
	{
		return reinterpret_cast<const ObjectGeometryBoundsData *>(
			reinterpret_cast<const char *>(this) - 0x70);
	}
};

void ObjectGeometryBoundsShim::getMax(Coord3D &out) const
{
	const ObjectGeometryBoundsData *object = getObject();
	const GeometryInfo &geometry = object->m_geometryInfo;
	Coord3D result;
	result.x = object->m_position.x;
	result.y = object->m_position.y;
	result.z = object->m_position.z;
	result.z += geometry.getMaxHeightAbovePosition();
	result.x += geometry.getMajorRadius();
	result.y += geometry.getMajorRadius();
	out.set(result.x, result.y, result.z);
}
