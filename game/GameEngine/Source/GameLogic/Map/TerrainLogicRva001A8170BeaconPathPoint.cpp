// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWMath
// stlport
// TerrainLogic member at retail 0x001A8170 and its static helper at 0x001A6A10.
// Owner: this+0x48 is the beacon path list that TerrainLogic::buildBeacons fills.
// The helper stays static in this TU so VC7.1 gives it retail's private register ABI.

#include <list>
#include "coord3d.h"
#include <math.h>

inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &v) { x = v.x; y = v.y; z = v.z; }
inline Coord3D &Coord3D::operator=(const Coord3D &v) { struct Raw { unsigned x, y, z; }; *(Raw *)this = *(const Raw *)&v; return *this; }
inline float Coord3D::GetLength() const { float xv = x; float yv = y; float zv = z; return (float)sqrt(xv * xv + yv * yv + zv * zv); }
inline float Coord3D::GetLength2D() const { float yv = y; float xv = x; return (float)sqrt(xv * xv + yv * yv); }
inline float Coord3D::GetLengthSqrd2D() const { float xv = x; float yv = y; return xv * xv + yv * yv; }
inline float Coord3D::lengthSqr() const { return z * z + y * y + x * x; }
inline float Coord3D::operator*(const Coord3DBase &v) const { return x * v.x + y * v.y + z * v.z; }
inline Coord3D &Coord3D::operator-=(const Coord3DBase &v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
inline float Coord3D::Normalize() { float len = GetLength(); float s = 1.0f / len; x *= s; y *= s; z *= s; return len; }
inline void Coord3D::sub(const Coord3DBase *v) { x -= v->x; y -= v->y; z -= v->z; }
inline void Coord3D::add(const Coord3DBase *v) { x += v->x; y += v->y; z += v->z; }
inline void Coord3D::scale(float s) { x *= s; y *= s; z *= s; }

typedef bool Bool;
typedef float Real;

typedef _STL::list<Coord3D> Coord3DList;

// Element type of the beacon path list, named as in TerrainLogicBuildBeacons.cpp.
struct Gen_t_001acc70_p4cd : public Coord3DList
{
	Gen_t_001acc70_p4cd() {}
	Gen_t_001acc70_p4cd(const Gen_t_001acc70_p4cd &other) : Coord3DList(other) {}
};

class TerrainLogic
{
public:
	virtual void tlSlot00(void) = 0;

	Bool rva001A8170NearestBeaconPathPoint(Coord3D *result, const Coord3D *pos, const Coord3D *endpointRef, Real maxDist, Bool snapToEndpoint);

private:
	unsigned char m_unreconstructed_04[0x44];
	_STL::list<Gen_t_001acc70_p4cd> m_beaconPaths;
};

// Closest point to point on the segment start..end in the XY plane.
static Coord3D rva001A6A10NearestPointOnSegment(const Coord3D &start, const Coord3D &end, const Coord3D &point, Real *distSqr)
{
	Coord3D dir = end;
	dir -= start;
	dir.z = 0.0f;
	Real len = dir.GetLength2D();
	dir.Normalize();

	Coord3D offset = point;
	offset -= start;
	offset.z = 0.0f;
	Real t = dir * offset;
	if (t < 0.0f)
		t = 0.0f;
	else if (t > len)
		t = len;

	Coord3D closest = dir;
	closest.scale(t);
	closest.add(&start);
	if (distSqr)
	{
		offset = closest;
		offset -= point;
		*distSqr = offset.GetLengthSqrd2D();
	}
	return closest;
}

Bool TerrainLogic::rva001A8170NearestBeaconPathPoint(Coord3D *result, const Coord3D *pos, const Coord3D *endpointRef, Real maxDist, Bool snapToEndpoint)
{
	Real bestDistSqr = maxDist * maxDist;
	const Coord3DList *bestPath = 0;

	for (_STL::list<Gen_t_001acc70_p4cd>::const_iterator it = m_beaconPaths.begin(); it != m_beaconPaths.end(); ++it)
	{
		const Coord3DList &path = *it;
		Coord3DList::const_iterator pt = path.begin();
		if (pt == path.end())
			continue;
		Coord3D cur = *pt++;
		while (pt != path.end())
		{
			Coord3D prev = cur;
			cur = *pt++;
			Real distSqr;
			rva001A6A10NearestPointOnSegment(prev, cur, *pos, &distSqr);
			if (distSqr < bestDistSqr)
			{
				bestDistSqr = distSqr;
				bestPath = &path;
			}
		}
	}

	if (bestPath == 0)
		return false;

	Coord3D segment[2];
	Coord3DList::const_iterator pt = bestPath->begin();
	Coord3D cur = *pt++;
	cur.z = 0.0f;
	bestDistSqr = 1e30f;
	while (pt != bestPath->end())
	{
		Coord3D prev = cur;
		cur = *pt++;
		cur.z = 0.0f;
		Real distSqr;
		Coord3D closest = rva001A6A10NearestPointOnSegment(prev, cur, *endpointRef, &distSqr);
		if (distSqr < bestDistSqr)
		{
			bestDistSqr = distSqr;
			segment[0] = prev;
			segment[1] = cur;
			*result = closest;
		}
	}

	if (snapToEndpoint)
	{
		Coord3D delta[2];
		delta[0] = segment[0];
		delta[0].sub(endpointRef);
		delta[1] = segment[1];
		delta[1].sub(endpointRef);
		*result = delta[0].lengthSqr() < delta[1].lengthSqr() ? segment[0] : segment[1];
	}
	return true;
}
