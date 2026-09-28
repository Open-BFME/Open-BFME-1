// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/shims/sweep
// ?rva00729F60@Rva00729F60Owner@@QAEXPAMHHHHPBVVector3@@11@Z
// Open-BFME: retail 0x00729F60, 897 bytes, ret 0x20 (eight stack arguments).
//
// For every cell of an (outerEnd+1) x (innerEnd+1) block, clamped to the
// height map, cast a vertical segment from just above the triangle's highest
// corner to just below its lowest one and, on a hit, write the contact height
// into the X or Y slot of the cell's 12-byte record (mode +0xb8 == 1 or 2).
// The owner reads origin +0x40/+0x44, grid width +0x48 and the height map
// +0x4c, the BFME W3DTerrainBackground offsets that the matched setFlip
// (0x00729F00) witnesses, but no caller is matched yet (d_0072a3d0 and
// d_0072b580 reach it through ILT 0x000453F9), so the class and method keep
// address-derived names.
//
// Codegen notes: 1.0f and MAP_XY_FACTOR (10.0f) are literals, which lets
// VC7.1 hoist the two segment-end Z stores out of the inner loop as retail
// does; the min/max are nested WWMath calls; ComputeContactPoint is set
// before the ray test is built and the triangle normal pointer last.
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include <vector3.h>
#include <lineseg.h>
#include <tri.h>
#include <colmath.h>
#include <coltest.h>

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
	float minZ = WWMath::Min(third->Z, WWMath::Min(first->Z, second->Z));

	float maxZ = WWMath::Max(third->Z, WWMath::Max(first->Z, second->Z));

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
			end.Z = maxZ + 1.0f;
			start.Z = minZ - 1.0f;

			float border = (float)map()->borderSize() * 10.0f;
			int worldX = originX() + x;
			int worldY = originY() + y;
			end.X = (float)worldX * 10.0f - border;
			end.Y = (float)worldY * 10.0f - border;
			start.X = end.X;
			start.Y = end.Y;

			LineSegClass line(end, start);
			result.ComputeContactPoint = true;
			RayCollisionTestClass raytest(line, &result);

			Vector3 normal;
			TriClass tri;
			tri.V[0] = first;
			tri.V[1] = second;
			tri.V[2] = third;
			tri.N = &normal;
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

