// ?rva003ecc70@Pathfinder@@QAE_NPBVPathNode@@PAV2@W4ObjectID@@PAUCoord3D@@33@Z
// partial score=0.3172 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc
#include <math.h>

typedef int Int;
typedef bool Bool;
typedef float Real;

enum ObjectID { INVALID_ID = 0 };
enum PathfindLayerEnum { LAYER_GROUND = 1 };

struct Coord3D
{
	Real x, y, z;
	Coord3D() {}
	Coord3D(const Coord3D &o) : x(o.x), y(o.y), z(o.z) {}
};
struct ICoord2D { Int x, y; };
struct Coord2D
{
	Real x, y;
	Real length() const { return (Real)sqrt(x * x + y * y); }
	void normalize()
	{
		Real len = length();
		if (len != 0.0f)
		{
			Real inv = 1.0f / len;
			x *= inv;
			y *= inv;
		}
	}
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	Real getBoundingCircleRadius() const { return m_boundingCircleRadius; }
private:
	char m_beforePosition[0x38];
	Coord3D m_pos;
	char m_beforeGeometryInfo[0xbc - 0x44];
	Real m_boundingCircleRadius;
};

class PathNode
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	void setPosition(const Coord3D *pos) { m_pos = *pos; }
private:
	char m_pad00[0x0c];
	Coord3D m_pos;
};

struct Rva003E3650Struct
{
	Object *theTallBuilding;
	ObjectID ignoreBuilding;
};

class Pathfinder
{
public:
	Bool worldToCell(const Coord3D *pos, ICoord2D *cell);
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end, PathfindLayerEnum layer, Rva003E3650Struct *info);
	Bool rva003ecc70(const PathNode *curNode, PathNode *nextNode, ObjectID ignoreBuilding,
		Coord3D *insertPos1, Coord3D *insertPos2, Coord3D *insertPos3);
};

static void computeNormalRadialOffset(const Coord3D &from, Coord3D &insert, const Coord3D &to, Object *obj, Real radius)
{
	Real dx = to.x - from.x;
	Real dy = to.y - from.y;
	Coord3D objPos = *obj->getPosition();
	Real objDx = objPos.x - from.x;
	Real objDy = objPos.y - from.y;
	Real cross = dx * objDy - dy * objDx;
	Coord2D normal;
	if (cross > 0.0f)
	{
		normal.x = dy;
		normal.y = -dx;
	}
	else
	{
		normal.x = -dy;
		normal.y = dx;
	}
	normal.normalize();
	insert = *obj->getPosition();
	insert.x += normal.x * radius;
	insert.y += normal.y * radius;
}

Bool Pathfinder::rva003ecc70(const PathNode *curNode, PathNode *nextNode, ObjectID ignoreBuilding,
	Coord3D *insertPos1, Coord3D *insertPos2, Coord3D *insertPos3)
{
	Rva003E3650Struct info;
	info.theTallBuilding = 0;
	info.ignoreBuilding = ignoreBuilding;
	Coord3D fromPos = *curNode->getPosition();
	Coord3D toPos = *nextNode->getPosition();

	for (Int i = 0; i < 2; ++i)
	{
		ICoord2D fromCell, toCell;
		worldToCell(&fromPos, &fromCell);
		worldToCell(&toPos, &toCell);
		if (iterateCellsAlongLine(fromCell, toCell, LAYER_GROUND, &info) && info.theTallBuilding)
		{
			Object *bldg = info.theTallBuilding;
			Coord3D bldgPos = *bldg->getPosition();
			Real radius = bldg->getBoundingCircleRadius() + 20.0f;
			Coord2D delta;
			delta.x = toPos.x - bldgPos.x;
			delta.y = toPos.y - bldgPos.y;
			if (delta.length() <= radius * 0.98)
			{
				if (delta.length() < 0.1)
					delta.x = 1.0f;
				delta.normalize();
				delta.x *= radius;
				delta.y *= radius;
				toPos.x = bldgPos.x + delta.x;
				toPos.y = bldgPos.y + delta.y;
				nextNode->setPosition(&toPos);
				continue;
			}
			delta.x = fromPos.x - bldgPos.x;
			delta.y = fromPos.y - bldgPos.y;
			if (delta.length() <= radius * 0.98)
			{
				if (delta.length() < 0.1)
					delta.x = 1.0f;
				delta.normalize();
				delta.x *= radius;
				delta.y *= radius;
				fromPos.x = bldgPos.x + delta.x;
				fromPos.y = bldgPos.y + delta.y;
			}
			computeNormalRadialOffset(fromPos, *insertPos2, toPos, bldg, radius);
			computeNormalRadialOffset(fromPos, *insertPos1, *insertPos2, bldg, radius);
			computeNormalRadialOffset(*insertPos2, *insertPos3, toPos, bldg, radius);
			return true;
		}
	}
	return false;
}
