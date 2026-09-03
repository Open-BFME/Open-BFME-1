// Byte-matched BFME single-box boundary-distance helper.
// cl: /O2 /Ob2 /G6 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWDebug

#include "../../../../Libraries/Source/WWVegas/WWMath/matrix3d.h"

typedef int Int;
typedef float Real;

extern "C" double __cdecl fabs(double value);
extern "C" double __cdecl sqrt(double value);
#pragma intrinsic(fabs)
#pragma intrinsic(sqrt)

extern const Real BfmeZeroRange;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
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
	Real boxMajorRadius() const;
	Real boxMinorRadius() const;

private:
	unsigned char m_pad000[0x10];
	Real m_boundingCircleRadius;
	unsigned char m_pad014[0x2c - 0x14];
	BfmeGeometryPiece *m_begin;
	BfmeGeometryPiece *m_end;

	friend class Object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Real bfmeSingleBoxBoundaryDistanceSquared2D(
		const Coord3D *position,
		const Object *other,
		const Coord3D *otherPosition) const;

private:
	unsigned char m_pad000[0x08];
	Matrix3D m_transform;
	Coord3D m_position;
	Real m_orientation;
	unsigned char m_pad048[0xac - 0x48];
	BfmeGeometryInfo m_geometry;
};

Real Object::bfmeSingleBoxBoundaryDistanceSquared2D(
	const Coord3D *position,
	const Object *other,
	const Coord3D *otherPosition) const
{
	const BfmeGeometryPiece *piece = m_geometry.pieceAt(0);
	Coord3D center;
	center.set(position);
	piece->transformCenter(&center, m_orientation);

	Vector3 delta(
		otherPosition->x - center.x,
		otherPosition->y - center.y,
		0.0f);
	Vector3 direction(delta);
	Real projectedX = (Real)fabs(Vector3::Dot_Product(
		m_transform.Get_X_Vector(), delta));
	Real projectedY = (Real)fabs(Vector3::Dot_Product(
		m_transform.Get_Y_Vector(), delta));

	if (projectedX < m_geometry.boxMajorRadius() &&
		projectedY < m_geometry.boxMinorRadius())
	{
		return BfmeZeroRange;
	}

	Real distanceSquared;
	Real radius;
	if (projectedX < m_geometry.boxMajorRadius())
	{
		radius = m_geometry.boxMinorRadius();
		distanceSquared = projectedY * projectedY;
	}
	else if (projectedY < m_geometry.boxMinorRadius())
	{
		radius = m_geometry.boxMajorRadius();
		distanceSquared = projectedX * projectedX;
	}
	else
	{
		Real directionLengthSquared = delta.Length2();
		if (directionLengthSquared != 0.0f)
		{
			Real inverseDistance = WWMath::Inv_Sqrt(directionLengthSquared);
			direction *= inverseDistance;
		}

		Vector3 majorAxis = m_transform.Get_X_Vector();
		Real majorRadius = m_geometry.boxMajorRadius();
		majorAxis = majorAxis * majorRadius;
		Vector3 minorAxis = m_transform.Get_Y_Vector();
		Real minorRadius = m_geometry.boxMinorRadius();
		minorAxis = minorAxis * minorRadius;
		Real majorProjection =
			(Real)fabs(Vector3::Dot_Product(majorAxis, direction));
		Real minorProjection =
			(Real)fabs(Vector3::Dot_Product(minorAxis, direction));
		radius = majorProjection + minorProjection;
		distanceSquared = delta.X * delta.X + delta.Y * delta.Y;
	}

	Real distance = (Real)sqrt(distanceSquared);
	distance -= radius + other->m_geometry.m_boundingCircleRadius;
	if (distance <= 0.0f)
		return 0.0f;
	return distance * distance;
}
