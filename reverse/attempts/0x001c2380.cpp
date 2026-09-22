// ?d_001c2380@@YAXXZ
// partial score=0.37 date=2026-09-22
// Candidate for the multi-piece Object boundary distance body at 0x001C2380.
// The owner and ABI are established from the caller and the adjacent Object helper.
// cl: /O2 /Ob2 /G6 /FAsc /Fabuild/target-001c2380/Rva001C2380Distance.cod /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWDebug

#include "../../Code/Libraries/Source/WWVegas/WWMath/matrix3d.h"

typedef int Int;
typedef float Real;

extern "C" double __cdecl sqrt(double value);
extern "C" double __cdecl fabs(double value);
#pragma intrinsic(sqrt)
#pragma intrinsic(fabs)

extern const Real BfmeZeroRange;

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	__forceinline void set(const Coord3D *other)
	{
		x = other->x;
		y = other->y;
		z = other->z;
	}
};

struct Direction2
{
	Real x;
	Real y;
};

struct BfmeGeometryPiece
{
	Int m_type;
	Real m_height;
	Real m_majorRadius;
	Real m_minorRadius;
	Coord3D m_localCenter;
	unsigned char m_pad01c[4];
	bool m_active;
	unsigned char m_pad021[3];

	void transformCenter(Coord3D *position, Real angle) const;
};

class BfmeGeometryInfo
{
public:
	const BfmeGeometryPiece *pieceAt(Int index) const;

private:
	unsigned char m_pad000[0x10];
	Real m_boundingCircleRadius;
	unsigned char m_pad014[0x2c - 0x14];
	BfmeGeometryPiece *m_begin;
	BfmeGeometryPiece *m_end;

	friend class Object;
};

class Object
{
public:
	Real rva001c2380Distance(const Coord3D *position,
		const Object *other, const Coord3D *otherPosition) const;

private:
	unsigned char m_pad000[0x08];
	Matrix3D m_transform;
	Coord3D m_position;
	Real m_orientation;
	unsigned char m_pad048[0xac - 0x48];
	BfmeGeometryInfo m_geometry;
};

Real Object::rva001c2380Distance(const Coord3D *position,
	const Object *other, const Coord3D *otherPosition) const
{
	const BfmeGeometryInfo *geometry = &m_geometry;
	Real closestDistance = 9999999.0f;
	bool found = false;

	for (Int i = 0; i < geometry->m_end - geometry->m_begin; ++i)
	{
		const BfmeGeometryPiece *piece = geometry->pieceAt(i);
		if (!piece->m_active)
			continue;

		Real distanceSquared;
		Real radius;
		Coord3D center;
		center.set(position);
		piece->transformCenter(&center, m_orientation);

		Real deltaX = otherPosition->x - center.x;
		Real deltaY = otherPosition->y - center.y;
		Direction2 direction = {deltaX, deltaY};
		Real projectedX = (Real)fabs(Vector3::Dot_Product(
			m_transform.Get_X_Vector(),
			Vector3(deltaX, deltaY, BfmeZeroRange)));
		Real projectedY = (Real)fabs(Vector3::Dot_Product(
			m_transform.Get_Y_Vector(),
			Vector3(deltaX, deltaY, BfmeZeroRange)));

		if (projectedX < piece->m_majorRadius &&
			projectedY < piece->m_minorRadius)
		{
			return BfmeZeroRange;
		}
		else if (projectedX < piece->m_majorRadius)
		{
			radius = piece->m_minorRadius;
			distanceSquared = projectedY * projectedY;
		}
		else if (projectedY < piece->m_minorRadius)
		{
			distanceSquared = projectedX * projectedX;
			radius = piece->m_majorRadius;
		}
		else
		{
			Real directionLengthSquared = deltaX * deltaX + deltaY * deltaY;
			if (directionLengthSquared != BfmeZeroRange)
			{
				Real inverseDistance = WWMath::Inv_Sqrt(directionLengthSquared);
				direction.x *= inverseDistance;
				direction.y *= inverseDistance;
			}

			Vector3 majorAxis = m_transform.Get_X_Vector();
			Real majorRadius = piece->m_majorRadius;
			majorAxis = majorAxis * majorRadius;
			Vector3 minorAxis = m_transform.Get_Y_Vector();
			Real minorRadius = piece->m_minorRadius;
			minorAxis = minorAxis * minorRadius;
			Real majorProjection =
				(Real)fabs(Vector3::Dot_Product(majorAxis,
					Vector3(direction.x, direction.y, BfmeZeroRange)));
			Real minorProjection =
				(Real)fabs(Vector3::Dot_Product(minorAxis,
					Vector3(direction.x, direction.y, BfmeZeroRange)));
			radius = majorProjection + minorProjection;
			distanceSquared = deltaX * deltaX + deltaY * deltaY;
		}

		Real distance = (Real)sqrt(distanceSquared);
		distance -= radius + other->m_geometry.m_boundingCircleRadius;
		if (!found || distance < closestDistance)
		{
			closestDistance = distance;
			found = true;
		}
	}

	if (closestDistance <= BfmeZeroRange)
		return BfmeZeroRange;
	return closestDistance * closestDistance;
}
