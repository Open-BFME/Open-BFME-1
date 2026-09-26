// ?optimize@Path@@QAEXPBVObject@@H_N@Z
// partial score=0.65 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x003E10F0: Pathfinder::buildActualPath.
//
class Object;
class PathfindCell;
class Path;

typedef int Int;
typedef bool Bool;
typedef int LocomotorSurfaceTypeMask;

inline Int IABS(Int value) { return value >= 0 ? value : -value; }

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1,
	LAYER_FIRST_BRIDGE = 16
};

struct Coord3D { float x, y, z; };

// BFME's object template keeps the override chain at +0x04 and kind-of flags
// at +0xC8.  This is the same view used by the matched Player build-list
// conversion; it is needed here only for the crusher bit read in optimize().
class Overridable
{
public:
	Overridable *getFinalOverride();

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad08[0xC0];
	unsigned int m_kindOf;
};

class Object
{
public:
	void *m_vtable;
	ThingTemplate *m_thingTemplate;
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
	Bool getCanOptimize(void) const { return m_canOptimize; }

	PathNode *m_next;
	PathNode *m_previous;
	PathNode *m_nextOptimized;
	Coord3D m_position;
	PathfindLayerEnum m_layer;
	Bool m_canOptimize;
	Int m_costSoFar;
};

class Pathfinder
{
public:
	Int isLinePassable(Object *obj, Int acceptableSurfaces,
		PathfindLayerEnum layer, const Coord3D *start, const Coord3D *end,
		Int blocked);
	Int bfmeCellTypeTwoWithoutFlag(const Coord3D *pos, PathfindLayerEnum layer);
	Bool bfmeWorldLineHasNoHit(const Coord3D *start, const Coord3D *end);
	Path *buildActualPath( const Object *obj, LocomotorSurfaceTypeMask acceptableSurfaces,
		const Coord3D *fromPos, PathfindCell *goalCell, Bool center, Bool blocked );
	void prependCells( Path *path, const Coord3D *fromPos, PathfindCell *goalCell, Bool center );
};

class AI
{
public:
	Pathfinder *pathfinder(void) const { return m_pathfinder; }

private:
	unsigned char m_pad00[0x0C];
	Pathfinder *m_pathfinder;
};

extern "C" AI *TheAIParseDefinitionAI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Path
{
public:
	Path();
	PathNode *getFirstNode(void) const { return m_path; }
	PathNode *getLastNode(void) const { return m_pathTail; }
	void optimize( const Object *obj, LocomotorSurfaceTypeMask acceptableSurfaces, Bool blocked );
	void bfmeOptimizeDir( const Object *obj, const Coord3D *dir,
		LocomotorSurfaceTypeMask acceptableSurfaces, Bool blocked );

private:
	void *m_vtable;
	PathNode *m_path;
	PathNode *m_pathTail;
	Bool m_isOptimized;
	unsigned char m_pad10[0x14];
};

// ?optimize@Path@@QAEXPBVObject@@H_N@Z
void Path::optimize(const Object *obj, LocomotorSurfaceTypeMask acceptableSurfaces,
	Bool blocked)
{
	PathNode *anchor, *node;
	const ThingTemplate *thing = obj->m_thingTemplate;
	anchor = m_path;
	Bool crusher;
	if (thing->m_nextOverride)
		thing = (const ThingTemplate *)thing->m_nextOverride->getFinalOverride();
	crusher = (thing->m_kindOf >> 11) & 1;

	if (anchor == 0)
	{
		m_isOptimized = true;
		return;
	}

	PathfindLayerEnum layer;
	PathfindLayerEnum curLayer;
	Int distance;
	Int count;
	Int steps;
	Bool passable;

	while (anchor->getNext())
	{
		node = anchor->getNext();
		layer = anchor->getLayer();
		curLayer = layer;
		distance = 0;
		count = 0;
		steps = anchor->m_costSoFar != 0x7fffffff ? 0 : 3;

		while (node)
		{
			++count;
			distance += 10;
			++steps;
			passable = false;

			if (TheAIParseDefinitionAI->pathfinder()->bfmeCellTypeTwoWithoutFlag(
				node->getPosition(), layer))
			{
				passable = true;
			}

			if (!passable)
			{
				Int dx = (Int)(node->getPosition()->x - anchor->getPosition()->x);
				Int dy = (Int)(node->getPosition()->y - anchor->getPosition()->y);
				Bool mightBePassable = false;

				if (dx == 0 && IABS(dy) == distance)
					mightBePassable = true;
				if (dy == 0 && IABS(dx) == distance)
					mightBePassable = true;
				if (IABS(dx) == IABS(dy) && IABS(dx) == distance)
					mightBePassable = true;
				if (mightBePassable)
					passable = true;
			}

			if (!passable)
			{
				if (node->m_costSoFar != 0x7fffffff && steps < 3)
					passable = true;
				if (node->m_costSoFar == 0x7fffffff)
					passable = true;
			}

			if (!passable)
			{
				PathNode *testNode = node;
				Int testCount = 0;
				while (testNode && testCount <= 3)
				{
					if (testNode->m_costSoFar != 0x7fffffff)
						passable = true;
					testNode = testNode->getNext();
					++testCount;
				}
			}

			if (!passable)
			{
				passable = TheAIParseDefinitionAI->pathfinder()->isLinePassable(
					(Object *)obj, acceptableSurfaces, layer,
					anchor->getPosition(), node->getPosition(), blocked);
			}

			if (curLayer != LAYER_GROUND)
			{
				if (curLayer >= LAYER_FIRST_BRIDGE)
				{
					if (node->getLayer() != curLayer)
					{
						layer = node->getLayer();
						if (distance > 30)
							passable = false;
					}
				}
				else
				{
					PathNode *next = node->getNext();
					if (next && next->getLayer() != curLayer && distance > 30)
						passable = false;
				}
			}

			if (crusher && !passable)
			{
				Int dx = (Int)(node->getPosition()->y - m_pathTail->getPosition()->y);
				Int dy = (Int)(node->getPosition()->x - m_pathTail->getPosition()->x);
				if (IABS(dx) + IABS(dy) < 40)
					passable = TheAIParseDefinitionAI->pathfinder()->bfmeWorldLineHasNoHit(
						anchor->getPosition(), node->getPosition());
			}

			curLayer = node->getLayer();
			if (passable && node->getCanOptimize())
			{
				anchor->setNextOptimized(node);
				node = node->getNext();
				continue;
			}

			if (count > 1)
				node = node->getPrevious();
			anchor->setNextOptimized(node);
			anchor = node;
			break;
		}
	}

	m_isOptimized = true;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D( void ) const;
};

Path *Pathfinder::buildActualPath( const Object *obj, LocomotorSurfaceTypeMask acceptableSurfaces,
	const Coord3D *fromPos, PathfindCell *goalCell, Bool center, Bool blocked )
{
	Path *path = new Path;

	prependCells( path, fromPos, goalCell, center );

	path->optimize( obj, acceptableSurfaces, blocked );

	Coord3D dir = *((const Thing *)obj)->getUnitDirectionVector2D();

	path->bfmeOptimizeDir( obj, &dir, acceptableSurfaces, blocked );

	return path;
}
