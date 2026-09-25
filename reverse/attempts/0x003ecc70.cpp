// ?d_003ecc70@@YAXXZ
// partial score=0.1674 date=2026-09-25
// cl: /DNDEBUG /MD /EHsc

#include <math.h>

typedef int Int;
typedef bool Bool;
typedef float Real;

enum ObjectID
{
	OBJECT_ID_INVALID = 0
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Real length() const
	{
		return (Real)sqrt(x * x + y * y + z * z);
	}

	void normalize()
	{
		Real lengthValue = length();
		if (lengthValue != 0)
		{
			x /= lengthValue;
			y /= lengthValue;
			z /= lengthValue;
		}
	}
};

struct Coord2D
{
	Real x;
	Real y;

	Real length() const
	{
		return (Real)sqrt(x * x + y * y);
	}

	void normalize()
	{
		Real lengthValue = length();
		if (lengthValue != 0)
		{
			x /= lengthValue;
			y /= lengthValue;
		}
	}
};

struct ICoord2D
{
	Int x;
	Int y;
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

struct Rva003E3650Struct
{
	class Object *theTallBuilding;
	ObjectID ignoreBuilding;
};

class PathNode
{
public:
	Coord3D *getPosition()
	{
		return &m_position;
	}

	const Coord3D *getPosition() const
	{
		return &m_position;
	}

	void setPosition(const Coord3D *position)
	{
		m_position = *position;
	}

	PathNode *m_next;
	PathNode *m_previous;
	PathNode *m_nextOptimized;
	Coord3D m_position;
	PathfindLayerEnum m_layer;
	Bool m_canOptimize;
	Int m_costSoFar;
};

class GeometryInfo
{
public:
	Real getBoundingCircleRadius() const
	{
		return m_boundingCircleRadius;
	}

private:
	char m_beforeRadius[0xc];
	Real m_boundingCircleRadius;
};

class Object
{
public:
	const Coord3D *getPosition() const
	{
		return &m_position;
	}

	const GeometryInfo &getGeometryInfo() const
	{
		return m_geometryInfo;
	}

private:
	char m_beforePosition[0x38];
	Coord3D m_position;
	char m_beforeGeometryInfo[0x6c];
	GeometryInfo m_geometryInfo;
};

class Pathfinder
{
public:
	Bool worldToCell(const Coord3D *world, ICoord2D *cell);
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, Rva003E3650Struct *userData);
	Int iterateCellsAlongLine(const Coord3D &startWorld,
		const Coord3D &endWorld, PathfindLayerEnum layer,
		Rva003E3650Struct *userData);

protected:
	Bool rva003ecc70(const PathNode *curNode, PathNode *nextNode,
		ObjectID ignoreBuilding, Coord3D *insertPos1,
		Coord3D *insertPos2, Coord3D *insertPos3);

private:
	char m_witnessedPathfinderLayout[0x8c0];
};

__forceinline Int Pathfinder::iterateCellsAlongLine(
	const Coord3D &startWorld, const Coord3D &endWorld,
	PathfindLayerEnum layer, Rva003E3650Struct *userData)
{
	ICoord2D start;
	ICoord2D end;
	worldToCell(&startWorld, &start);
	worldToCell(&endWorld, &end);
	return iterateCellsAlongLine(start, end, layer, userData);
}

extern const Real BfmeZeroRange;
extern const Real g_bfmeDefaultBU;
#define PATHFIND_CELL_SIZE_F (*(const Real *)0x010977E0)

static void computeNormalRadialOffset(const Coord3D &from,
	Coord3D &insert, const Coord3D &to, Object *obj, Real radius)
{
	Real crossProduct;
	Real dx = to.x - from.x;
	Real dy = to.y - from.y;
	Coord3D objPos = *obj->getPosition();
	Real objDx = objPos.x - from.x;
	Real objDy = objPos.y - from.y;

	crossProduct = dx * objDy - dy * objDx;

	Coord3D fromToNormal;
	fromToNormal.z = 0;
	if (crossProduct > 0)
	{
		fromToNormal.x = dy;
		fromToNormal.y = -dx;
	}
	else
	{
		fromToNormal.x = -dy;
		fromToNormal.y = dx;
	}
	fromToNormal.normalize();
	Real length = radius;
	insert = *obj->getPosition();
	insert.x += fromToNormal.x * length;
	insert.y += fromToNormal.y * length;
}

Bool Pathfinder::rva003ecc70(const PathNode *curNode,
	PathNode *nextNode, ObjectID ignoreBuilding, Coord3D *insertPos1,
	Coord3D *insertPos2, Coord3D *insertPos3)
{
	Rva003E3650Struct info;
	info.ignoreBuilding = ignoreBuilding;

	Coord3D fromPos;
	fromPos = *curNode->getPosition();
	Coord3D toPos;
	toPos = *nextNode->getPosition();
	info.theTallBuilding = 0;

	Int i;
	for (i = 0; i < 2; i++)
	{
		Int ret = iterateCellsAlongLine(fromPos, toPos, LAYER_GROUND,
			&info);
		if (ret != 0 && info.theTallBuilding)
		{
			Coord3D bldgPos = *info.theTallBuilding->getPosition();
			Coord2D delta;
			Real radius = info.theTallBuilding->getGeometryInfo().getBoundingCircleRadius();
			radius += PATHFIND_CELL_SIZE_F;
			delta.x = toPos.x - bldgPos.x;
			delta.y = toPos.y - bldgPos.y;
			if (delta.length() <= radius * 0.98)
			{
				if (delta.length() < 0.1)
					delta.x = 1;
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
					delta.x = 1;
				delta.normalize();
				delta.x *= radius;
				delta.y *= radius;
				fromPos.y = bldgPos.y + delta.y;
				fromPos.x = bldgPos.x + delta.x;
			}

			computeNormalRadialOffset(fromPos, *insertPos2, toPos,
				info.theTallBuilding, radius);
			computeNormalRadialOffset(fromPos, *insertPos1, *insertPos2,
				info.theTallBuilding, radius);
			computeNormalRadialOffset(*insertPos2, *insertPos3, toPos,
				info.theTallBuilding, radius);
			return true;
		}
	}

	return false;
}
