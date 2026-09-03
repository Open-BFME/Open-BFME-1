// cl: /DNDEBUG /MD /EHs-c-
// Bridge::isPointOnBridge, retail 0x001A5F40.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Vector3
{
	public:
	float X;
	float Y;
	float Z;
};

struct Region2D
{
	float loX;
	float loY;
	float hiX;
	float hiY;
};

struct ICoord3D
{
	int x;
	int y;
	int z;
};

class PolygonTrigger
{
public:
	bool pointInTrigger(ICoord3D &point) const;
};

bool Point_In_Triangle_2D(const Vector3 &tri_point0, const Vector3 &tri_point1,
	const Vector3 &tri_point2, const Vector3 &test_point, int axis_1, int axis_2,
	unsigned char &flags);

static inline unsigned char Point_In_Triangle_2D_byte(const Vector3 &tri_point0,
	const Vector3 &tri_point1, const Vector3 &tri_point2, const Vector3 &test_point,
	int axis_1, int axis_2, unsigned char &flags)
{
	return Point_In_Triangle_2D(tri_point0, tri_point1, tri_point2, test_point,
		axis_1, axis_2, flags) ? 1 : 0;
}

class BridgePointOnBridgeShim
{
public:
	bool test(const Coord3D *point);

private:
	void *m_vptr;
	void *m_next;
	void *m_templateName;
	char m_infoPad[0x1C];
	Coord3D m_fromLeft;
	Coord3D m_fromRight;
	Coord3D m_toLeft;
	Coord3D m_toRight;
	char m_infoTail[0x78 - 0x58];
	Region2D m_bounds;
	int m_layer;
	PolygonTrigger *m_extra;
};

bool BridgePointOnBridgeShim::test(const Coord3D *point)
{
	if (point->x < m_bounds.loX)
		return false;
	if (point->x > m_bounds.hiX)
		return false;
	if (point->y < m_bounds.loY)
		return false;
	if (point->y > m_bounds.hiY)
		return false;

	PolygonTrigger *extra = m_extra;
	if (extra)
	{
		ICoord3D ic;
		ic.x = (int)point->x;
		ic.y = (int)point->y;
		ic.z = (int)point->z;
		return extra->pointInTrigger(ic);
	}
	else
	{
		Vector3 testPt;
		testPt.X = point->x;
		testPt.Y = point->y;
		testPt.Z = point->z;
		Vector3 left1;
		left1.X = m_fromLeft.x;
		left1.Y = m_fromLeft.y;
		left1.Z = m_fromLeft.z;
		Vector3 right1;
		right1.X = m_fromRight.x;
		right1.Y = m_fromRight.y;
		right1.Z = m_fromRight.z;
		Vector3 left2;
		left2.X = m_toLeft.x;
		left2.Y = m_toLeft.y;
		left2.Z = m_toLeft.z;
		Vector3 right2;
		right2.X = m_toRight.x;
		right2.Y = m_toRight.y;
		right2.Z = m_toRight.z;

		unsigned char flags;
		if (Point_In_Triangle_2D(left1, right1, left2, testPt, 0, 1, flags))
			return true;
		return Point_In_Triangle_2D_byte(right1, left2, right2, testPt, 0, 1, flags);
	}
}
