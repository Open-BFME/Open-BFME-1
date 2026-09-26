// ?bfmeIntersects@GeometryInfo@@QBE_NABUCoord3D@@MABV1@0M@Z
// partial score=0.99 date=2026-09-08
// cl: /O2 /Ob2 /G6 /DNDEBUG /MD /EHs-c-
// Open-BFME: GeometryInfo oriented-shape intersection, retail 0x0087F2F0.

typedef float Real;
typedef bool Bool;

template <typename T>
class StringBase
{
public:
	~StringBase()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer();
	void *m_data;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct BfmePosF0
{
	Real x;
	Real y;
	Real z;
};

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

struct BfmeShapeF0
{
	GeometryType m_type;
	Real m_height;
	Real m_majorRadius;
	unsigned char m_unmodelled00c[0x0c];
	Real m_offsetZ;
	StringBase<char> m_name;
	Bool m_enabled;
	unsigned char m_unmodelled021[0x03];
};

struct BfmeCollisionShape
{
	GeometryType m_type;
	int m_height;
	int m_majorRadius;
	unsigned char m_unmodelled00c[0x0c];
	int m_offsetZ;
	StringBase<char> m_name;
	Bool m_enabled;
	unsigned char m_unmodelled021[0x03];
	Coord3D m_position;
	int m_angle;
};

class BfmeObjF0
{
public:
	~BfmeObjF0()
	{
	}

	BfmeObjF0 *set(const BfmePosF0 *position, const BfmeShapeF0 *shape,
		Real angle);
	static Bool bfmeIntersectsBoxes(const BfmeObjF0 *first,
		const BfmeObjF0 *second);
	static Bool bfmeIntersectsBox(const BfmeObjF0 *first,
		const BfmeObjF0 *second);

	GeometryType m_type;
	int m_height;
	int m_majorRadius;
	unsigned char m_unmodelled00c[0x0c];
	int m_offsetZ;
	StringBase<char> m_name;
	Bool m_enabled;
	unsigned char m_unmodelled021[0x03];
	Coord3D m_position;
	int m_angle;

};

void bfmeTransformShape(BfmePosF0 *out, const Coord3D *position,
	const BfmeShapeF0 *shape, Real angle);
Bool bfmeSphereOverlap(const BfmeCollisionShape *first,
	const BfmeCollisionShape *second);

class GeometryInfo
{
public:
	Bool bfmeIntersects(const Coord3D &thisPosition, Real thisAngle,
		const GeometryInfo &otherGeometry, const Coord3D &otherPosition,
		Real otherAngle) const;

private:
	unsigned char m_unmodelled000[0x2c];
	BfmeShapeF0 *m_shapes;
	BfmeShapeF0 *m_shapesEnd;
};

Bool GeometryInfo::bfmeIntersects(const Coord3D &thisPosition,
	Real thisAngle, const GeometryInfo &otherGeometry,
	const Coord3D &otherPosition, Real otherAngle) const
{
	Bool result = false;
	for (const BfmeShapeF0 *thisShape = m_shapes;
		thisShape != m_shapesEnd; ++thisShape)
	{
		if (!thisShape->m_enabled)
			continue;
		if (result)
			break;

		BfmePosF0 thisCenter;
		bfmeTransformShape(&thisCenter, &thisPosition, thisShape, thisAngle);

		for (const BfmeShapeF0 *thatShape = otherGeometry.m_shapes;
			thatShape != otherGeometry.m_shapesEnd; ++thatShape)
		{
			if (!thatShape->m_enabled)
				continue;
			if (result)
				break;

			BfmePosF0 thatCenter;
			bfmeTransformShape(&thatCenter, &otherPosition, thatShape,
				otherAngle);

			Real thisHeight = 0.0f;
			switch (thisShape->m_type)
			{
				case GEOMETRY_SPHERE:
					thisHeight = thisShape->m_majorRadius;
					break;
				case GEOMETRY_CYLINDER:
				case GEOMETRY_BOX:
					thisHeight = thisShape->m_height;
					break;
			}
			thisHeight += thisShape->m_offsetZ;
			thisHeight += thisCenter.z;
			if (otherPosition.z > thisHeight)
				continue;

			Real thatHeight = 0.0f;
			switch (thatShape->m_type)
			{
				case GEOMETRY_SPHERE:
					thatHeight = thatShape->m_majorRadius;
					break;
				case GEOMETRY_CYLINDER:
				case GEOMETRY_BOX:
					thatHeight = thatShape->m_height;
					break;
			}
			thatHeight += thatShape->m_offsetZ;
			thatHeight += thatCenter.z;
			if (thisCenter.z > thatHeight)
				continue;

			BfmeObjF0 thisObject;
			BfmeObjF0 thatObject;
			thisObject.set(&thisCenter, thisShape, thisAngle);
			thatObject.set(&thatCenter, thatShape, otherAngle);

			switch (thisObject.m_type)
			{
				case GEOMETRY_BOX:
					if (thatObject.m_type == GEOMETRY_BOX)
						result = BfmeObjF0::bfmeIntersectsBoxes(
							&thisObject, &thatObject);
					else
						result = BfmeObjF0::bfmeIntersectsBox(
							&thatObject, &thisObject);
					break;
				case GEOMETRY_SPHERE:
				case GEOMETRY_CYLINDER:
					if (thatObject.m_type == GEOMETRY_BOX)
					{
						result = BfmeObjF0::bfmeIntersectsBox(
							&thisObject, &thatObject);
					}
					else
					{
						result = bfmeSphereOverlap(
							reinterpret_cast<const BfmeCollisionShape *>(
								&thisObject),
							reinterpret_cast<const BfmeCollisionShape *>(
								&thatObject));
					}
					break;
			}
		}
	}
	return result;
}
