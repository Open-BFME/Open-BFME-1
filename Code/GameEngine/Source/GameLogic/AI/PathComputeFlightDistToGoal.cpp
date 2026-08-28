// BFME's Path::computeFlightDistToGoal always begins at the path head. The
// later reference body consults m_cpopRecentStart, so this focused TU keeps the
// retail traversal under a collision-free selector.

#include <math.h>

typedef bool Bool;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord2D
{
	Real x;
	Real y;

	void normalize()
	{
		Real length = (Real)sqrt(x * x + y * y);
		if (length != 0.0f)
		{
			x /= length;
			y /= length;
		}
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathNode
{
public:
	PathNode *m_next;
	PathNode *m_previous;
	PathNode *m_nextOptimized;
	Coord3D m_position;
	int m_layer;
	Bool m_canOptimize;
	int m_waypointID;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Path
{
public:
	Real bfmeComputeFlightDistToGoal(const Coord3D *pos, Coord3D &goalPos);

private:
	unsigned char m_head[4];
	PathNode *m_path;
	PathNode *m_pathTail;
	Bool m_isOptimized;
	PathNode *m_cpopRecentStart;
};

// ?bfmeComputeFlightDistToGoal@Path@@QAEMPBUCoord3D@@AAU2@@Z
Real Path::bfmeComputeFlightDistToGoal(const Coord3D *pos, Coord3D &goalPos)
{
	if (m_path == 0)
	{
		goalPos.x = 0.0f;
		goalPos.y = 0.0f;
		goalPos.z = 0.0f;
		return 0.0f;
	}

	PathNode *curNode = m_path;
	PathNode *nextNode = curNode->m_nextOptimized;
	goalPos = curNode->m_position;
	Real distance = 0.0f;
	Bool useNext = true;
	while (nextNode)
	{
		if (useNext)
			goalPos = nextNode->m_position;

		Coord2D posToGoalVector;
		posToGoalVector.x = nextNode->m_position.x - pos->x;
		posToGoalVector.y = nextNode->m_position.y - pos->y;

		Coord2D pathVector;
		pathVector.x = nextNode->m_position.x - curNode->m_position.x;
		pathVector.y = nextNode->m_position.y - curNode->m_position.y;
		pathVector.normalize();

		Real dotProduct = posToGoalVector.x * pathVector.x +
			posToGoalVector.y * pathVector.y;
		if (dotProduct >= 0.0f)
		{
			distance += dotProduct;
			useNext = false;
		}
		curNode = nextNode;
		nextNode = curNode->m_nextOptimized;
	}
	return distance;
}
