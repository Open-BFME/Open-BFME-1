// Clone a PathNode onto the tail of a Path. BFME carries the waypoint ID into
// the clone and maintains both the ordinary and optimized links.

typedef int Int;
typedef float Real;
typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
#include "../../../../Libraries/Include/Lib/Coord3D.h"

// Absent-from-retail source-shaping helper: preserves both complete PathNode
// copy bodies without defining a shared Coord3D assignment COMDAT. MSVC 7.1
// also emits an unreferenced local copy; it has no claimed retail identity/RVA.
static __forceinline Coord3D &copyCoordinates(Coord3D &destination, const Coord3D &source)
{
	destination.x = source.x;
	destination.y = source.y;
	destination.z = source.z;
	return destination;
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathNode
{
public:
	PathNode(const Coord3D *position, PathfindLayerEnum layer)
	{
		m_next = 0;
		m_previous = 0;
		m_nextOptimized = 0;
		copyCoordinates(m_position, *position);
		m_layer = layer;
		m_canOptimize = false;
		m_waypointID = 0x7fffffff;
	}

	PathNode *m_next;
	PathNode *m_previous;
	PathNode *m_nextOptimized;
	Coord3D m_position;
	PathfindLayerEnum m_layer;
	Bool m_canOptimize;
	Int m_waypointID;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Path
{
public:
	void appendNode(const PathNode *source);

private:
	char m_bfmeHead[4];
	PathNode *m_path;
	PathNode *m_pathTail;
	Bool m_isOptimized;
};

// ?appendNode@Path@@QAEXPBVPathNode@@@Z
void Path::appendNode(const PathNode *source)
{
	if (m_isOptimized && m_pathTail)
	{
		if (source->m_position.x == m_pathTail->m_position.x &&
			source->m_position.y == m_pathTail->m_position.y)
		{
			return;
		}
	}

	PathNode *node = new PathNode(&source->m_position, source->m_layer);
	node->m_waypointID = source->m_waypointID;

	PathNode *tail = m_pathTail;
	if (tail)
	{
		tail->m_next = node;
		node->m_previous = tail;
	}

	if (m_isOptimized && m_pathTail)
		m_pathTail->m_nextOptimized = node;

	m_pathTail = node;
	if (m_path == 0)
		m_path = node;
}
