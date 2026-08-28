// BFME's Path::updateLastNode checks for a tail before asking TerrainLogic for
// a layer. The later reference source performs that call first, so this small
// TU preserves the retail ordering under a collision-free selector.

typedef bool Bool;
typedef float Real;

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

class Object;

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(
		Object *object, const Coord3D *position);
};

extern TerrainLogic *TheTerrainLogic;

class PathNode
{
public:
	void setNextOptimized(PathNode *node) { m_nextOptimized = node; }

private:
	PathNode *m_next;
	PathNode *m_previous;
	PathNode *m_nextOptimized;
	Coord3D m_position;
	PathfindLayerEnum m_layer;
	Bool m_canOptimize;
	unsigned char m_padding[3];
	int m_portalObjectID;

	friend class Path;
};

class Path
{
public:
	void bfmeUpdateLastNode(const Coord3D *position);

private:
	unsigned char m_head[4];
	PathNode *m_path;
	PathNode *m_pathTail;
	Bool m_isOptimized;
};

// ?bfmeUpdateLastNode@Path@@QAEXPBUCoord3D@@@Z
void Path::bfmeUpdateLastNode(const Coord3D *position)
{
	if (m_pathTail)
	{
		m_pathTail->m_position = *position;
		m_pathTail->m_layer =
			TheTerrainLogic->getLayerForDestination(0, position);
		if (m_isOptimized)
		{
			PathNode *node = m_path;
			while (node && node->m_nextOptimized != m_pathTail)
				node = node->m_nextOptimized;
			if (node && node->m_nextOptimized == m_pathTail)
				node->setNextOptimized(m_pathTail);
		}
	}
}
