// ?test@BridgePointOnBridgeShim@@QAE_NPBUCoord3D@@@Z
// partial score=0.96 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

// Open-BFME: Bridge::isPointOnBridge body at 0x001A5F40, the ILT target of
// ?isPointOnBridge@Bridge@@QAE_NPBUCoord3D@@@Z.  Bounds-check then either a
// BFME extra object at +0x8C or two Point_In_Triangle_2D tests.

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Vector3
{
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

class ExtraBridgeQuery
{
public:
	bool contains(const ICoord3D *point);
};

bool Point_In_Triangle_2D(const Vector3 &tri_point0, const Vector3 &tri_point1,
	const Vector3 &tri_point2, const Vector3 &test_point, int axis_1, int axis_2,
	unsigned char &flags);

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
	ExtraBridgeQuery *m_extra;
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

	ExtraBridgeQuery *extra = m_extra;
	if (extra)
	{
		ICoord3D ic;
		ic.x = (int)point->x;
		ic.y = (int)point->y;
		ic.z = (int)point->z;
		return extra->contains(&ic);
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
		return Point_In_Triangle_2D(right1, left2, right2, testPt, 0, 1, flags) != 0;
	}
}
