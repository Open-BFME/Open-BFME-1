// cl: /DNDEBUG /MD /EHs-c-
// Bridge::getBridgeHeight, retail 0x001A7520 (664 B: ret 8 at +0x295, int3 from +0x298).
//
// Callers reach it through the Bridge member thunk at ILT 0x0000B802
// (BridgeMemberThunks.cpp). ilt_oracle CONFIRMS the class-keyed decoration
// ?getBridgeHeight@Bridge@@QAEMPBVCoord3D@@PAV2@@Z for that slot (8601).
//
// BFME 2 donor: open-bfme-2 45afcff3a6 Code/GameEngine/Source/GameLogic/Map/BridgeGetBridgeHeight.cpp
// (BFME 2 retail 0x0027FD2A). Its body compiles byte-exact here with BFME 1's flags once the
// polygon-area pointer sits at BFME 1's +0x8C (the m_extra offset of BridgeIsPointOnBridge.cpp).
// Plane branch: Zero Hour TerrainLogic.cpp Bridge::getBridgeHeight. Retail calls
// Coord3D::normalize (0x000FB930) twice, PlaneClass::Set (0x001A5DC0) and
// PlaneClass::Compute_Intersection (0x001A1CF0) out of line.

typedef float Real;

// class-gate: allow Coord3D BFME's user default and copy constructors and header-inline sub/scale, absent from the canonical header, give the polygon-area branch retail's member-wise copies and stack slots
class Coord3D
{
public:
	Real x;
	Real y;
	Real z;
	Coord3D() {}
	Coord3D(const Coord3D &o) : x(o.x), y(o.y), z(o.z) {}
	Coord3D(Real ax, Real ay, Real az) : x(ax), y(ay), z(az) {}
	void normalize();
	void sub(const Coord3D *p) { x -= p->x; y -= p->y; z -= p->z; }
	void scaleInlined(Real s) { x *= s; y *= s; z *= s; }
};

class Vector3
{
public:
	Vector3() {}
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }

	Real X;
	Real Y;
	Real Z;
};

class PlaneClass
{
public:
	__declspec(dllimport) __forceinline PlaneClass() {}
	void Set(const Vector3 &point1, const Vector3 &point2, const Vector3 &point3);
	bool Compute_Intersection(const Vector3 &p0, const Vector3 &p1, Real *set_t) const;

	Vector3 N;
	Real D;
};

struct BridgeInfo
{
	Coord3D from;
	Coord3D to;
	Real bridgeWidth;
	Coord3D fromLeft;
	Coord3D fromRight;
	Coord3D toLeft;
	Coord3D toRight;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Bridge
{
public:
	Real getBridgeHeight(const Coord3D *pLoc, Coord3D *normal);

private:
	void *m_vptr;
	void *m_next;
	void *m_templateName;
	BridgeInfo m_bridgeInfo; // +0x0C
	char m_infoTail[0x8C - 0x58];
	void *m_area; // +0x8C
};

// ?getBridgeHeight@Bridge@@QAEMPBVCoord3D@@PAV2@@Z
Real Bridge::getBridgeHeight(const Coord3D *pLoc, Coord3D *normal)
{
	if (m_area)
	{
		Coord3D along;
		along = m_bridgeInfo.to;
		along.sub(&m_bridgeInfo.from);
		Coord3D fromEdge = m_bridgeInfo.fromRight;
		fromEdge.sub(&m_bridgeInfo.fromLeft);
		Coord3D toEdge = m_bridgeInfo.toRight;
		toEdge.sub(&m_bridgeInfo.toLeft);
		Coord3D fromNormal(-fromEdge.y, fromEdge.x, 0);
		Coord3D toNormal(toEdge.y, -toEdge.x, 0);
		Real fromDot = along.x * fromNormal.x + along.y * fromNormal.y;
		if (fromDot < 0)
			fromNormal.scaleInlined(-1.0f);
		Real toDot = along.x * toNormal.x + along.y * toNormal.y;
		if (toDot > 0)
			toNormal.scaleInlined(-1.0f);
		fromNormal.normalize();
		toNormal.normalize();
		Coord3D fromDelta = *pLoc;
		fromDelta.sub(&m_bridgeInfo.from);
		Real fromDist = fromDelta.x * fromNormal.x + fromDelta.y * fromNormal.y;
		Coord3D toDelta = *pLoc;
		toDelta.sub(&m_bridgeInfo.to);
		Real toDist = toDelta.x * toNormal.x + toDelta.y * toNormal.y;
		Real total = fromDist + toDist;
		fromDist /= total;
		toDist /= total;
		Real fromHeight = (m_bridgeInfo.to.z - m_bridgeInfo.from.z) * fromDist + m_bridgeInfo.from.z;
		Real toHeight = (m_bridgeInfo.from.z - m_bridgeInfo.to.z) * toDist + m_bridgeInfo.to.z;
		Real height = (1.0f - fromDist) * fromHeight + (1.0f - toDist) * toHeight;
		if (normal)
		{
			normal->x = normal->y = 0;
			normal->z = 1.0f;
		}
		return height;
	}
	else
	{
		PlaneClass plane;
		{
		Vector3 left1(m_bridgeInfo.fromLeft.x, m_bridgeInfo.fromLeft.y, m_bridgeInfo.fromLeft.z);
		Vector3 right1(m_bridgeInfo.fromRight.x, m_bridgeInfo.fromRight.y, m_bridgeInfo.fromRight.z);
		Vector3 left2(m_bridgeInfo.toLeft.x, m_bridgeInfo.toLeft.y, m_bridgeInfo.toLeft.z);
		plane.Set(left1, right1, left2);
		}
		{
		const Real factor = 1000.0f;
		Vector3 bottom(pLoc->x, pLoc->y, 0);
		Vector3 top(pLoc->x, pLoc->y, factor);
		Real t;
		plane.Compute_Intersection(bottom, top, &t);
		if (normal)
			*(Vector3 *)normal = plane.N;
		return t * factor;
		}
	}
}
