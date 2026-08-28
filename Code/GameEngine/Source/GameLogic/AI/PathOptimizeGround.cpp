// BFME's ground-path optimizer takes only the path diameter. It accepts both
// ground and bridge layers in its transition scan, then shortcuts passable
// segments and removes very short optimized middle nodes.

typedef int Int;
typedef float Real;
typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1,
	LAYER_FIRST_BRIDGE = 16
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class PathNode
{
public:
	PathNode *getNext(void) const { return m_next; }
	PathNode *getPrevious(void) const { return m_previous; }
	PathNode *getNextOptimized(void) const { return m_nextOptimized; }
	void setNextOptimized(PathNode *node) { m_nextOptimized = node; }
	const Coord3D *getPosition(void) const { return &m_position; }
	PathfindLayerEnum getLayer(void) const { return m_layer; }

private:
	PathNode *m_next;
	PathNode *m_previous;
	PathNode *m_nextOptimized;
	Coord3D m_position;
	PathfindLayerEnum m_layer;
};

class Pathfinder
{
public:
	Bool isGroundPathPassable(const Coord3D &startWorld,
		PathfindLayerEnum startLayer, const Coord3D &endWorld, Int pathDiameter);
};

class AI
{
public:
	Pathfinder *pathfinder(void) const { return m_pathfinder; }

private:
	unsigned char m_unknown[0x0c];
	Pathfinder *m_pathfinder;
};

extern "C" AI *TheAIParseDefinitionAI;

class Path
{
public:
	void optimizeGroundPath(Int pathDiameter);

private:
	void *m_vtable;
	PathNode *m_path;
	PathNode *m_pathTail;
	Bool m_isOptimized;
};

// ?optimizeGroundPath@Path@@QAEXH@Z
void Path::optimizeGroundPath(Int pathDiameter)
{
	PathNode *node, *anchor;

	anchor = m_path;

	while (anchor != m_pathTail)
	{
		Bool optimizedSegment = false;
		PathfindLayerEnum layer = anchor->getLayer();
		PathfindLayerEnum curLayer = anchor->getLayer();
		Int count = 0;
		const Int ALLOWED_STEPS = 3;
		for (node = anchor->getNext(); node->getNext(); node = node->getNext())
		{
			count++;
			Bool compareNodeLayer =
				curLayer == LAYER_GROUND || curLayer >= LAYER_FIRST_BRIDGE;
			if (compareNodeLayer)
			{
				if (node->getLayer() != curLayer)
				{
					layer = node->getLayer();
					curLayer = layer;
					if (count > ALLOWED_STEPS)
						break;
				}
			}
			if (!compareNodeLayer && node->getNext()->getLayer() != curLayer)
			{
				if (count > ALLOWED_STEPS)
					break;
			}
			curLayer = node->getLayer();
		}

		for (; node != anchor; node = node->getPrevious())
		{
			Bool isPassable = false;
			if (TheAIParseDefinitionAI->pathfinder()->isGroundPathPassable(
				*anchor->getPosition(), layer, *node->getPosition(), pathDiameter))
			{
				isPassable = true;
			}

			if (!isPassable)
			{
				Int dx = node->getPosition()->x - anchor->getPosition()->x;
				Int dy = node->getPosition()->y - anchor->getPosition()->y;
				Bool mightBePassable = false;
				PathNode *tmpNode;
				if (dx == 0)
				{
					mightBePassable = true;
					for (tmpNode = node->getPrevious(); tmpNode && tmpNode != anchor;
						tmpNode = tmpNode->getPrevious())
					{
						dx = tmpNode->getNext()->getPosition()->x - tmpNode->getPosition()->x;
						if (dx != 0)
							mightBePassable = false;
					}
				}
				if (dy == 0)
				{
					mightBePassable = true;
					for (tmpNode = node->getPrevious(); tmpNode && tmpNode != anchor;
						tmpNode = tmpNode->getPrevious())
					{
						dy = tmpNode->getNext()->getPosition()->y - tmpNode->getPosition()->y;
						if (dy != 0)
							mightBePassable = false;
					}
				}
				if (dx == dy)
				{
					mightBePassable = true;
					for (tmpNode = node->getPrevious(); tmpNode && tmpNode != anchor;
						tmpNode = tmpNode->getPrevious())
					{
						dx = tmpNode->getNext()->getPosition()->x - tmpNode->getPosition()->x;
						dy = tmpNode->getNext()->getPosition()->y - tmpNode->getPosition()->y;
						if (dy != dx)
							mightBePassable = false;
					}
				}
				if (dx == -dy)
				{
					mightBePassable = true;
					for (tmpNode = node->getPrevious(); tmpNode && tmpNode != anchor;
						tmpNode = tmpNode->getPrevious())
					{
						dx = tmpNode->getNext()->getPosition()->x - tmpNode->getPosition()->x;
						dy = tmpNode->getNext()->getPosition()->y - tmpNode->getPosition()->y;
						if (dy != -dx)
							mightBePassable = false;
					}
				}
				if (mightBePassable)
					isPassable = true;
			}

			if (isPassable)
			{
				anchor->setNextOptimized(node);
				anchor = node;
				optimizedSegment = true;
				break;
			}
		}

		if (optimizedSegment == false)
		{
			anchor->setNextOptimized(anchor->getNext());
			anchor = anchor->getNext();
		}
	}

	for (anchor = m_path; anchor != 0; anchor = anchor->getNextOptimized())
	{
		node = anchor->getNextOptimized();
		if (node && node->getNextOptimized())
		{
			Real dx = node->getPosition()->x - anchor->getPosition()->x;
			Real dy = node->getPosition()->y - anchor->getPosition()->y;
			if (dx * dx + dy * dy < 390.0f)
				anchor->setNextOptimized(node->getNextOptimized());
		}
	}

	m_isOptimized = true;
}
