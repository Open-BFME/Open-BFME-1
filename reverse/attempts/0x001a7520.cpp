// ?getBridgeHeight@Bridge@@QAEMPBUCoord3D@@PAU2@@Z
// partial score=0.62 date=2026-09-04
// cl: /DNDEBUG /MD /EHs-c-
// Bridge::getBridgeHeight, retail 0x001A7520 size 664.
// Identity: reloc-named real body behind ILT 0xB802; dump ?d_001a7520@@YAXXZ.

struct Coord3D
{
	float x;
	float y;
	float z;
	void normalize();
};

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class PlaneClass
{
public:
	Vector3 N;
	float D;

	void Set(const Vector3 &point1, const Vector3 &point2, const Vector3 &point3);
	bool Compute_Intersection(const Vector3 &p0, const Vector3 &p1, float *set_t) const;
};

class Bridge
{
public:
	float getBridgeHeight(const Coord3D *pLoc, Coord3D *normal);

private:
	void *m_vptr;
	void *m_next;
	void *m_templateName;
	Coord3D m_from;
	Coord3D m_to;
	float m_bridgeWidth;
	Coord3D m_fromLeft;
	Coord3D m_fromRight;
	Coord3D m_toLeft;
	Coord3D m_toRight;
	char m_infoTail[0x78 - 0x58];
	char m_bounds[0x10];
	int m_layer;
	void *m_extra;
};

struct Align34
{
	Coord3D nFrom;
	float gap;
	Coord3D nTo;
	Vector3 scratch;
	float tmp;
	float pad[2];
};

float Bridge::getBridgeHeight(const Coord3D *pLoc, Coord3D *normal)
{
	Align34 f;
	if (m_extra)
	{
		Coord3D *toPtr = &m_to;
		f.scratch = *reinterpret_cast<Vector3 *>(toPtr);
		float alongX = f.scratch.X - m_from.x;
		float alongY = f.scratch.Y - m_from.y;
		f.nFrom.x = m_fromRight.y;
		f.nFrom.z = 0.0f;
		f.tmp = m_fromRight.x - m_fromLeft.x;
		f.nTo.z = 0.0f;
		f.nFrom.y = f.tmp;
		f.nFrom.x = f.nFrom.x - m_fromLeft.y;
		f.nTo.y = m_toRight.y;
		f.scratch.X = m_toRight.x - m_toLeft.x;
		f.scratch.Y = f.nTo.y - m_toLeft.y;
		f.nTo.x = f.scratch.Y;
		f.nFrom.x = -f.nFrom.x;
		f.nTo.y = -f.scratch.X;
		if (f.nFrom.x * alongX + f.nFrom.y * alongY < 0.0f)
		{
			f.nFrom.z = -0.0f;
			f.nFrom.x = f.nFrom.x * -1.0f;
			f.nFrom.y = f.tmp * -1.0f;
		}
		if (f.nTo.x * alongX + f.nTo.y * alongY > 0.0f)
		{
			f.nTo.z = -0.0f;
			f.nTo.x = f.scratch.Y * -1.0f;
			f.nTo.y = f.nTo.y * -1.0f;
		}
		f.nFrom.normalize();
		f.nTo.normalize();
		f.tmp = f.nFrom.x * (pLoc->x - m_from.x) + f.nFrom.y * (pLoc->y - m_from.y);
		f.gap = f.nTo.x * (pLoc->x - toPtr->x) + f.nTo.y * (pLoc->y - toPtr->y);
		f.scratch.X = 1.0f / (f.tmp + f.gap);
		f.scratch.Y = f.scratch.X * f.tmp;
		f.scratch.Z = f.scratch.X * f.gap;
		f.tmp = (m_to.z + (m_from.z - m_to.z) * f.scratch.Z) * (1.0f - f.scratch.Z)
			+ (m_from.z + (m_to.z - m_from.z) * f.scratch.Y) * (1.0f - f.scratch.Y);
		if (normal)
		{
			normal->x = 0.0f;
			normal->y = 0.0f;
			normal->z = 1.0f;
		}
		return f.tmp;
	}

	{
		char *base = reinterpret_cast<char *>(&f);
		Vector3 &left1 = *reinterpret_cast<Vector3 *>(base + 0x10);
		Vector3 &right1 = *reinterpret_cast<Vector3 *>(base + 0x1c);
		Vector3 &left2 = *reinterpret_cast<Vector3 *>(base + 0x28);
		PlaneClass &plane = *reinterpret_cast<PlaneClass *>(base + 0x0c);
		left1 = *reinterpret_cast<Vector3 *>(&m_fromLeft);
		right1 = *reinterpret_cast<Vector3 *>(&m_fromRight);
		left2 = *reinterpret_cast<Vector3 *>(&m_toLeft);
		plane.Set(left1, right1, left2);
		right1.X = pLoc->x;
		left2.X = pLoc->x;
		right1.Y = pLoc->y;
		left2.Y = pLoc->y;
		right1.Z = 0.0f;
		left2.Z = 1000.0f;
		plane.Compute_Intersection(right1, left2, &f.tmp);
		if (normal)
		{
			normal->x = plane.N.X;
			normal->y = plane.N.Y;
			normal->z = plane.N.Z;
		}
		return f.tmp * 1000.0f;
	}
}
