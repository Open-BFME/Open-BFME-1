// ?bfmeFinishTurnArc@Path@@QAEXPAVPathNode@@00M@Z
// partial score=0.18 date=2026-09-25
// cl: /DNDEBUG /MD /EHsc
//
// Reconstructs Path::bfmeFinishTurnArc at retail RVA 0x003FEBB0.
// The symbol pin at ILT 0x00021BF2 and Path::bfmeBuildTurnArc at 0x003FFB50
// prove the method's identity. The carved body is 1,990 bytes.

#include <math.h>

typedef int Int;
typedef float Real;
typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Vector3
{
	Real X;
	Real Y;
	Real Z;

	Vector3(void) { }
	Vector3(Real x, Real y, Real z) : X(x), Y(y), Z(z) { }
	Vector3 &operator=(const Vector3 &that)
	{
		X = that.X;
		Y = that.Y;
		Z = that.Z;
		return *this;
	}
};

class LineSegClass
{
public:
	LineSegClass(void) { }
	LineSegClass(const Vector3 &p0, const Vector3 &p1)
	{
		P0 = p0;
		P1 = p1;
		recalculate();
	}

	void Set(const Vector3 &p0, const Vector3 &p1)
	{
		P0 = p0;
		P1 = p1;
		recalculate();
	}

	const Vector3 &Get_Dir(void) const { return Dir; }
	Real Get_Length(void) const { return Length; }
	Bool Find_Intersection(const LineSegClass &other, Vector3 *p1,
		Real *fraction1, Vector3 *p2, Real *fraction2) const;

protected:
	void recalculate(void);

	Vector3 P0;
	Vector3 P1;
	Vector3 DP;
	Vector3 Dir;
	Real Length;
};

class WWMath
{
public:
	static Real Inv_Sqrt(Real value);
};

extern Real bfmeUnitAngle(const Coord3D *a, const Coord3D *b);
extern int __stdcall bfmeScaledCount(Real angle, Real radius);

class PathNode
{
public:
	PathNode *m_next;
	PathNode *m_previous;
	PathNode *m_nextOptimized;
	Coord3D m_position;
	PathfindLayerEnum m_layer;
	Bool m_canOptimize;
	Int m_waypointID;
};

class Path
{
public:
	void bfmeFinishTurnArc(PathNode *created, PathNode *node, PathNode *next,
		Real radius);
	void appendNode(const PathNode *source);
	void appendNode(const Coord3D *position, PathfindLayerEnum layer);
};

#pragma comment(linker, "/alternatename:?recalculate@LineSegClass@@IAEXXZ=?j_00040115@@YAXXZ")
#pragma comment(linker, "/alternatename:?Inv_Sqrt@WWMath@@SIMM@Z=?j_00027a43@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeUnitAngle@@YAMPBUCoord3D@@0@Z=?j_00022c6e@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeScaledCount@@YGHMM@Z=?j_00014015@@YAXXZ")
#pragma comment(linker, "/alternatename:?appendNode@Path@@QAEXPBVPathNode@@@Z=?j_0002b48b@@YAXXZ")
#pragma comment(linker, "/alternatename:?appendNode@Path@@QAEXPBUCoord3D@@W4PathfindLayerEnum@@@Z=?j_0003833e@@YAXXZ")

#define BFME_ZERO (*(const Real *)0x01075350)
#define BFME_RADIUS_SCALE (*(const Real *)0x0109F748)
#define BFME_SHADOW_SCALE (*(const Real *)0x0109BF3C)
#define BFME_TURN_ANGLE (*(const double *)0x010F02F8)
#define BFME_SMALL_ANGLE (*(const double *)0x010F0310)
#define BFME_TURN_SCALE (*(const Real *)0x010F0308)
#define BFME_LARGE_ANGLE (*(const Real *)0x010F0304)

static void normalizeRvaVector(Vector3 &value)
{
	Real length2 = value.X * value.X + value.Y * value.Y + value.Z * value.Z;
	if (length2 != BFME_ZERO)
	{
		Real inverse = WWMath::Inv_Sqrt(length2);
		value.X *= inverse;
		value.Y *= inverse;
		value.Z *= inverse;
	}
}

void Path::bfmeFinishTurnArc(PathNode *created, PathNode *node,
	PathNode *next, Real radius)
{
	LineSegClass first;
	LineSegClass second;
	Real pointAX;
	Real pointAY;
	Real pointBX;
	Real pointBY;
	Bool positiveTurn;
	Real length;

	{
		Real createdX = created->m_position.x;
		Real createdY = created->m_position.y;
		Real nextX;
		Real nextY;

		first.Set(Vector3(createdX, createdY, 0.0f),
			Vector3(node->m_position.x, node->m_position.y, 0.0f));
		nextX = next->m_position.x;
		nextY = next->m_position.y;
		second.Set(Vector3(node->m_position.x, node->m_position.y, 0.0f),
			Vector3(nextX, nextY, 0.0f));

		length = first.Get_Length();
	if (second.Get_Length() < length)
		length = second.Get_Length();
	length *= BFME_RADIUS_SCALE;
	if (radius > length)
		radius = length;

		Real cross = first.Get_Dir().X * second.Get_Dir().Y -
			second.Get_Dir().X * first.Get_Dir().Y;
		if (cross >= BFME_ZERO)
		{
			pointAX = createdX;
			pointAY = createdY;
			pointBX = nextX;
			pointBY = nextY;
			positiveTurn = true;
		}
		else
		{
			pointAX = nextX;
			pointAY = nextY;
			pointBX = createdX;
			pointBY = createdY;
			positiveTurn = false;

			first.Set(Vector3(nextX, nextY, 0.0f),
				Vector3(node->m_position.x, node->m_position.y, 0.0f));
			second.Set(Vector3(node->m_position.x, node->m_position.y, 0.0f),
				Vector3(createdX, createdY, 0.0f));
		}
	}

	Real angle = bfmeUnitAngle(
		(const Coord3D *)&first.Get_Dir(),
		(const Coord3D *)&second.Get_Dir());
	if (angle < BFME_SMALL_ANGLE)
		radius *= BFME_TURN_SCALE;

	if (node->m_waypointID != 0x7fffffff || angle > BFME_LARGE_ANGLE)
	{
		this->appendNode(node);
		return;
	}

	Vector3 offsetA(
		first.Get_Dir().X * radius,
		first.Get_Dir().Y * radius,
		first.Get_Dir().Z * radius);
	Vector3 offsetB(
		second.Get_Dir().X * radius,
		second.Get_Dir().Y * radius,
		second.Get_Dir().Z * radius);

	Real sine = (Real)sin(BFME_TURN_ANGLE);
	Real cosine = (Real)cos(BFME_TURN_ANGLE);
	Vector3 rotatedA;
	rotatedA.X = offsetA.X * cosine - offsetA.Y * sine;
	rotatedA.Y = offsetA.X * sine + offsetA.Y * cosine;
	rotatedA.Z = offsetA.Z;
	Vector3 rotatedB;
	rotatedB.X = offsetB.X * cosine - offsetB.Y * sine;
	rotatedB.Y = offsetB.X * sine + offsetB.Y * cosine;
	rotatedB.Z = offsetB.Z;

	LineSegClass offsetLineA(
		Vector3(rotatedA.X + pointAX, rotatedA.Y + pointAY, rotatedA.Z),
		Vector3(rotatedA.X + node->m_position.x,
			rotatedA.Y + node->m_position.y, rotatedA.Z));
	LineSegClass offsetLineB(
		Vector3(rotatedB.X + node->m_position.x,
			rotatedB.Y + node->m_position.y, rotatedB.Z),
		Vector3(rotatedB.X + pointBX, rotatedB.Y + pointBY, rotatedB.Z));

	normalizeRvaVector(rotatedA);
	normalizeRvaVector(rotatedB);

	angle = bfmeUnitAngle((const Coord3D *)&rotatedB,
		(const Coord3D *)&rotatedA);
	Int count = bfmeScaledCount(angle, radius);
	if (count < 2)
	{
		this->appendNode(node);
		return;
	}
	Real step = sine / (Real)count;

	Real fraction;
	Vector3 intersectionA;
	Vector3 intersectionB;
	if (!offsetLineA.Find_Intersection(offsetLineB, &intersectionA,
		&fraction, &intersectionB, &fraction))
		return;

	Coord3D point;
	if (positiveTurn)
	{
		point.x = intersectionA.X - rotatedA.X;
		point.y = intersectionA.Y - rotatedA.Y;
		point.z = node->m_position.z;
		this->appendNode(&point, node->m_layer);

		rotatedA.X *= BFME_SHADOW_SCALE;
		rotatedA.Y *= BFME_SHADOW_SCALE;
		if (count > 1)
		{
			Real sineStep = (Real)sin(-step);
			Real cosineStep = (Real)cos(-step);
			do
			{
				--count;
				Real oldX = rotatedA.X;
				rotatedA.X = oldX * cosineStep - rotatedA.Y * sineStep;
				rotatedA.Y = rotatedA.Y * cosineStep + oldX * sineStep;
				point.x = intersectionA.X + rotatedA.X;
				point.y = intersectionA.Y + rotatedA.Y;
				point.z = node->m_position.z;
				this->appendNode(&point, node->m_layer);
			} while (count != 0);
		}

		point.x = intersectionA.X - rotatedB.X;
		point.y = intersectionA.Y - rotatedB.Y;
		point.z = node->m_position.z;
		this->appendNode(&point, node->m_layer);
	}
	else
	{
		point.x = intersectionA.X - rotatedB.X;
		point.y = intersectionA.Y - rotatedB.Y;
		point.z = node->m_position.z;
		this->appendNode(&point, node->m_layer);

		rotatedB.X *= BFME_SHADOW_SCALE;
		rotatedB.Y *= BFME_SHADOW_SCALE;
		if (count > 1)
		{
			Real sineStep = (Real)sin(-step);
			Real cosineStep = (Real)cos(-step);
			do
			{
				--count;
				Real oldX = rotatedB.X;
				rotatedB.X = oldX * cosineStep - rotatedB.Y * sineStep;
				rotatedB.Y = rotatedB.Y * cosineStep + oldX * sineStep;
				point.x = intersectionA.X + rotatedB.X;
				point.y = intersectionA.Y + rotatedB.Y;
				point.z = node->m_position.z;
				this->appendNode(&point, node->m_layer);
			} while (count != 0);
		}

		point.x = intersectionA.X - rotatedA.X;
		point.y = intersectionA.Y - rotatedA.Y;
		point.z = node->m_position.z;
		this->appendNode(&point, node->m_layer);
	}

	node->m_position.x = point.x;
	node->m_position.y = point.y;
	node->m_position.z = point.z;
}
