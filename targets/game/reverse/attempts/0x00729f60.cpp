// ?rva00729F60@Rva00729F60Owner@@QAEXPAMHHHHPBVVector3@@11@Z
// partial score=0.24 date=2026-09-16
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Source/WWVegas/WWSaveLoad /Ireference/shims/sweep
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include <vector3.h>
#include <lineseg.h>
#include <tri.h>
#include <colmath.h>
#include <coltest.h>

// These are the two retail memory operands used by the x87 body.  Keeping
// them as memory lvalues preserves the observed DIR32 operands.
#define RVA00729F60_ONE (*(const float *)0x01075334)
#define RVA00729F60_SCALE (*(const float *)0x01075C74)

class Rva00729F60Map
{
public:
	int width(void) const
	{
		return *(const int *)((const char *)this + 0x08);
	}

	int height(void) const
	{
		return *(const int *)((const char *)this + 0x0c);
	}

	int borderSize(void) const
	{
		return *(const int *)((const char *)this + 0x10);
	}
};

class Rva00729F60Owner
{
public:
	int originX(void) const
	{
		return *(const int *)((const char *)this + 0x40);
	}

	int originY(void) const
	{
		return *(const int *)((const char *)this + 0x44);
	}

	int gridWidth(void) const
	{
		return *(const int *)((const char *)this + 0x48);
	}

	Rva00729F60Map *map(void) const
	{
		return *(Rva00729F60Map * const *)((const char *)this + 0x4c);
	}

	int mode(void) const
	{
		return *(const int *)((const char *)this + 0xb8);
	}

	void rva00729F60(float *records, int xOrigin, int yOrigin,
		int outerEnd, int innerEnd, const Vector3 *first,
		const Vector3 *second, const Vector3 *third);
};

void Rva00729F60Owner::rva00729F60(float *records, int xOrigin, int yOrigin,
	int outerEnd, int innerEnd, const Vector3 *first,
	const Vector3 *second, const Vector3 *third)
{
	Rva00729F60Map *terrainMap = map();
	int maxMapX = terrainMap->width() - 1;
	int maxMapY = terrainMap->height() - 1;
	float minZ = WWMath::Min(first->Z, second->Z);
	minZ = WWMath::Min(third->Z, minZ);

	float maxZ = WWMath::Max(first->Z, second->Z);
	maxZ = WWMath::Max(third->Z, maxZ);

	Vector3 start;
	Vector3 end;
	int i = 0;
	while (i <= outerEnd) {
		int j = 0;
		while (j <= innerEnd) {
			int x = i + xOrigin;
			if (x >= maxMapX) {
				x = maxMapX;
			}

			int y = j + yOrigin;
			if (y >= maxMapY) {
				y = maxMapY;
			}

			int index = x + y * (gridWidth() + 1);

			CastResultStruct result;
			end.Z = maxZ + RVA00729F60_ONE;
			start.Z = minZ - RVA00729F60_ONE;

			float border = (float)map()->borderSize() * RVA00729F60_SCALE;
			int worldX = originX() + x;
			int worldY = originY() + y;
			end.X = (float)worldX * RVA00729F60_SCALE - border;
			end.Y = (float)worldY * RVA00729F60_SCALE - border;
			start.X = end.X;
			start.Y = end.Y;

			LineSegClass line(end, start);
			RayCollisionTestClass raytest(line, &result);
			raytest.Result->ComputeContactPoint = true;

			Vector3 normal;
			TriClass tri;
			tri.N = &normal;
			tri.V[0] = first;
			tri.V[1] = second;
			tri.V[2] = third;
			tri.Compute_Normal();

			if (raytest.Cast_To_Triangle(tri)) {
				float contactZ = raytest.Result->ContactPoint.Z;
				if (mode() == 2) {
					records[index * 3 + 1] = contactZ;
				} else if (mode() == 1) {
					records[index * 3] = contactZ;
				}
			}

			++j;
		}
		++i;
	}
}

