// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/shims/sweep
// ?Cast_Ray@BaseHeightMapRenderObjClass@@UAE_NAAVRayCollisionTestClass@@@Z
// Open-BFME: retail 0x006CDF90, 2839 bytes.
//
// Zero Hour BaseHeightMapRenderObjClass::Cast_Ray (BaseHeightMap.cpp) adapted
// to BFME 1's terrain, cross-checked against the BFME 2 donor
// Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapCastRay.cpp
// (open-bfme-2 76f0baefa6). Retail facts: m_map at this+0x2FF4; the map keeps
// x/y extents at +0x08/+0x0C, the border at +0x10 and 16-bit samples at +0x24;
// the pick box overhangs the map by 64 cells plus the border and reaches
// 65535 * (10/256) + 10 up; heights scale by 10/256. Unlike BFME 2, BFME 1
// expands the clamped sample lookup (getClipHeight) inline at all five sites.
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include <vector3.h>
#include <lineseg.h>
#include <aabox.h>
#include <tri.h>
#include <castres.h>
#include <colmath.h>
#include <coltest.h>
#include <w3d_file.h>

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef short Short;
typedef unsigned short UnsignedShort;

extern "C" __declspec(dllimport) double __cdecl floor(double value);
extern "C" __declspec(dllimport) double __cdecl ceil(double value);

#define MAP_XY_FACTOR 10.0f
#define MAP_HEIGHT_SCALE (MAP_XY_FACTOR / 256.0f)

inline long castRayFloatToLong(float f)
{
	long i;
	__asm fld [f]
	__asm fistp [i]
	return i;
}

inline Real castRayFloor(Real f)
{
	return (Real)floor(f);
}

inline Real castRayCeil(Real f)
{
	return (Real)ceil(f);
}

#define REAL_TO_INT_FLOOR(x) castRayFloatToLong(castRayFloor(x))
#define REAL_TO_INT_CEIL(x) castRayFloatToLong(castRayCeil(x))

class WorldHeightMap
{
public:
	Int getXExtent(void) const { return m_width; }
	Int getYExtent(void) const { return m_height; }
	Int getBorderSizeInline(void) const { return m_borderSize; }
	UnsignedShort *getDataPtr(void) const { return m_data; }

	char m_header[8];
	Int m_width;
	Int m_height;
	Int m_borderSize;
	char m_layout[0x10];
	UnsignedShort *m_data;
};

class BaseHeightMapRenderObjClass
{
public:
	virtual bool Cast_Ray(RayCollisionTestClass &raytest);

	__declspec(dllimport) __forceinline UnsignedShort getClipHeight(Int x, Int y) const
	{
		Int xextent = m_map->getXExtent();
		Int yextent = m_map->getYExtent();

		if (x < 0)
			x = 0;
		else if (x >= xextent)
			x = xextent - 1;

		if (y < 0)
			y = 0;
		else if (y >= yextent)
			y = yextent - 1;

		return m_map->getDataPtr()[x + y * xextent];
	}

private:
	char m_pad[0x2FF0];
	WorldHeightMap *m_map;
};

#define ADJUST_FROM_INDEX_TO_REAL(k) ((k - m_map->getBorderSizeInline()) * MAP_XY_FACTOR)

bool BaseHeightMapRenderObjClass::Cast_Ray(RayCollisionTestClass &raytest)
{
	TriClass tri;
	Bool hit = false;
	Int X, Y;
	Vector3 normal, P0, P1, P2, P3;

	if (!m_map)
		return false;	//need valid pointer to heightmap samples
	//Clip ray to extents of heightfield
	AABoxClass hbox;
	LineSegClass lineseg, lineseg2;
	CastResultStruct result;
	Int StartCellX = 0;
	Int EndCellX = 0;
	Int StartCellY = 0;
	Int EndCellY = 0;
	const Int overhang = 2 * 32 + m_map->getBorderSizeInline(); // Allow picking past the edge for scrolling & objects.
	Vector3 minPt(MAP_XY_FACTOR * (-overhang), MAP_XY_FACTOR * (-overhang), -MAP_XY_FACTOR);
	Vector3 maxPt(MAP_XY_FACTOR * (m_map->getXExtent() + overhang),
		MAP_XY_FACTOR * (m_map->getYExtent() + overhang), MAP_HEIGHT_SCALE * 65535 + MAP_XY_FACTOR);
	MinMaxAABoxClass mmbox(minPt, maxPt);
	hbox.Init(mmbox);

	lineseg = raytest.Ray;

	//Set initial ray endpoints
	P0 = raytest.Ray.Get_P0();
	P1 = raytest.Ray.Get_P1();
	result.ComputeContactPoint = true;

	Int p;
	for (p = 0; p < 3; p++) {
		//find intersection point of ray and terrain bounding box
		result.Reset();
		result.ComputeContactPoint = true;
		if (CollisionMath::Collide(lineseg, hbox, &result))
		{	//ray intersects terrain or starts inside the terrain.
			if (!result.StartBad)	//check if start point inside terrain
				P0 = result.ContactPoint;			//make intersection point the new start of the ray.

			//reverse direction of original ray and clip again to extent of
			//heightmap
			result.Fraction = 1.0f;	//reset the result
			result.StartBad = false;
			lineseg2.Set(lineseg.Get_P1(), lineseg.Get_P0());	//reverse line segment
			if (CollisionMath::Collide(lineseg2, hbox, &result))
			{	if (!result.StartBad)	//check if end point inside terrain
					P1 = result.ContactPoint;	//make intersection point the new end pont of ray
			}
		} else {
			if (p == 0) return(false);
			break;
		}

		// Take the 2D bounding box of ray and check heights
		// inside this box for intersection.
		if (P0.X > P1.X) {	//flip start/end points
			StartCellX = REAL_TO_INT_FLOOR(P1.X * (1.0f / MAP_XY_FACTOR));
			EndCellX = REAL_TO_INT_CEIL(P0.X * (1.0f / MAP_XY_FACTOR));
		}	else {
			StartCellX = REAL_TO_INT_FLOOR(P0.X * (1.0f / MAP_XY_FACTOR));
			EndCellX = REAL_TO_INT_CEIL(P1.X * (1.0f / MAP_XY_FACTOR));
		}
		if (P0.Y > P1.Y) {	//flip start/end points
			StartCellY = REAL_TO_INT_FLOOR(P1.Y * (1.0f / MAP_XY_FACTOR));
			EndCellY = REAL_TO_INT_CEIL(P0.Y * (1.0f / MAP_XY_FACTOR));
		}	else {
			StartCellY = REAL_TO_INT_FLOOR(P0.Y * (1.0f / MAP_XY_FACTOR));
			EndCellY = REAL_TO_INT_CEIL(P1.Y * (1.0f / MAP_XY_FACTOR));
		}

		Int i, j, minHt, maxHt;

		minHt = 65535;
		maxHt = 0;

		for (j = StartCellY; j <= EndCellY; j++) {
			for (i = StartCellX; i <= EndCellX; i++) {
				Short cur = getClipHeight(i + m_map->getBorderSizeInline(), j + m_map->getBorderSizeInline());
				if (cur < minHt) minHt = cur;
				if (maxHt < cur) maxHt = cur;
			}
		}
		Vector3 minPt(MAP_XY_FACTOR * (StartCellX - 1), MAP_XY_FACTOR * (StartCellY - 1), MAP_HEIGHT_SCALE * (minHt - 1));
		Vector3 maxPt(MAP_XY_FACTOR * (EndCellX + 1), MAP_XY_FACTOR * (EndCellY + 1), MAP_HEIGHT_SCALE * (maxHt + 1));
		MinMaxAABoxClass mmbox(minPt, maxPt);
		hbox.Init(mmbox);
	}

	raytest.Result->ComputeContactPoint = true;	//tell CollisionMath that we need point.

	// Adjust indexes into the bordered height map.

	StartCellX += m_map->getBorderSizeInline();
	EndCellX += m_map->getBorderSizeInline();
	StartCellY += m_map->getBorderSizeInline();
	EndCellY += m_map->getBorderSizeInline();

	Int offset;
	for (offset = 1; offset < 5; offset *= 3) {
		for (Y = StartCellY - offset; Y <= EndCellY + offset; Y++) {

			for (X = StartCellX - offset; X <= EndCellX + offset; X++) {
				//test the 2 triangles in this cell
				//	3-----2
				//  |    /|
				//  |  /  |
				//	|/    |
				//  0-----1

				//bottom triangle first
				P0.X = ADJUST_FROM_INDEX_TO_REAL(X);
				P0.Y = ADJUST_FROM_INDEX_TO_REAL(Y);
				P0.Z = MAP_HEIGHT_SCALE * (float)getClipHeight(X, Y);

				P1.X = ADJUST_FROM_INDEX_TO_REAL(X + 1);
				P1.Y = ADJUST_FROM_INDEX_TO_REAL(Y);
				P1.Z = MAP_HEIGHT_SCALE * (float)getClipHeight(X + 1, Y);

				P2.X = ADJUST_FROM_INDEX_TO_REAL(X + 1);
				P2.Y = ADJUST_FROM_INDEX_TO_REAL(Y + 1);
				P2.Z = MAP_HEIGHT_SCALE * (float)getClipHeight(X + 1, Y + 1);

				P3.X = ADJUST_FROM_INDEX_TO_REAL(X);
				P3.Y = ADJUST_FROM_INDEX_TO_REAL(Y + 1);
				P3.Z = MAP_HEIGHT_SCALE * (float)getClipHeight(X, Y + 1);

				tri.V[0] = &P0;
				tri.V[1] = &P1;
				tri.V[2] = &P2;

				tri.N = &normal;

				tri.Compute_Normal();

				hit = hit || (Bool)CollisionMath::Collide(raytest.Ray, tri, raytest.Result);

				if (raytest.Result->StartBad)
					return true;

				//top triangle
				tri.V[0] = &P2;
				tri.V[1] = &P3;
				tri.V[2] = &P0;

				tri.N = &normal;

				tri.Compute_Normal();

				hit = hit || (Bool)CollisionMath::Collide(raytest.Ray, tri, raytest.Result);

				if (hit)
					raytest.Result->SurfaceType = SURFACE_TYPE_DEFAULT;
			}
		}
	}
	return hit;
}
