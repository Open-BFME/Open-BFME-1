// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include
// readable body of ?optimize@Path@@: game/GameEngine/Source/GameLogic/AI/AIPathfind.cpp

// Path::optimize, retail 0x00401660 (669 B, ret 0xC). BFME rewrote Zero
// Hour's optimizer: each anchor scans forward, counting steps and distance,
// accepting a node when the pathfinder's cell test, a straight or diagonal
// run, an already-costed intermediate node or a line-passable check lets it
// through; layer changes past 30 units break the segment, and a crusher may
// still pass a short gap with an unobstructed world line. The crusher bit is
// the final template's KindOf bit 11.
//
// Three spellings carry the codegen: the outer loop takes the next node in
// its condition (retail's exit blocks follow that order), count is cleared
// before distance, and the step seed is computed after the layers are read.
// The ground-or-bridge test is a named Bool, which keeps retail's block
// order for the bridge-layer branch.


class PathfindCell;
class Path;

#include "../../../Include/Common/ScalarTypes.h"

#include "../../../Include/Common/ScalarTypes/Source/LocomotorSurfaceTypeMask.h"

#include <stdlib.h>
#define IABS abs

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1,
	LAYER_FIRST_BRIDGE = 16
};

#include "Lib/Coord3D.h"

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

extern AI *TheAI;						// 0x012EF214

// The six-argument line test at 0x003EE8D0, reached through ILT 0x00014EE8.
// Retail pushes optimize's Bool argument unconverted, while the ledger's
// spelling of the callee takes an Int last argument (the callee forwards the
// dword untouched); neither spelling fits the ILT window, so the call is made
// through the thunk with the Bool view the caller compiles against.
extern void j_00014ee8();

class BfmeLinePassableView
{
public:
	Int isLinePassable(Object *obj, Int acceptableSurfaces,
		PathfindLayerEnum layer, const Coord3D *start, const Coord3D *end,
		Bool blocked);
};

static __forceinline Int bfmeIsLinePassable(Pathfinder *pathfinder, Object *obj,
	Int acceptableSurfaces, PathfindLayerEnum layer, const Coord3D *start,
	const Coord3D *end, Bool blocked)
{
	typedef Int (BfmeLinePassableView::*Function)(Object *, Int,
		PathfindLayerEnum, const Coord3D *, const Coord3D *, Bool);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00014ee8;
	return (reinterpret_cast<BfmeLinePassableView *>(pathfinder)->*fn.member)(
		obj, acceptableSurfaces, layer, start, end, blocked);
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
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
	if (!thing) thing = 0;
	else if (thing->m_nextOverride)
		thing = (const ThingTemplate *)thing->m_nextOverride->getFinalOverride();
	crusher = (thing->m_kindOf >> 11) & 1;

	PathfindLayerEnum layer;
	PathfindLayerEnum curLayer;
	Int distance;
	Int count;
	Int steps;
	Bool passable;

	while (anchor && (node = anchor->getNext()) != 0)
	{
		layer = anchor->getLayer();
		curLayer = layer;
		steps = anchor->m_costSoFar != 0x7fffffff ? 0 : 3;
		count = 0;
		distance = 0;

		while (node)
		{
			++count;
			distance += 10;
			++steps;
			passable = false;

			if ((unsigned char)TheAI->pathfinder()->bfmeCellTypeTwoWithoutFlag(
				node->getPosition(), layer))
			{
				passable = true;
			}

			if (!passable)
			{
				Int dx = (Int)(node->getPosition()->x - anchor->getPosition()->x);
				Int dy = (Int)(node->getPosition()->y - anchor->getPosition()->y);


				if (dx == 0 && IABS(dy) == distance)
					passable = true;
				if (dy == 0 && IABS(dx) == distance)
					passable = true;
				if (IABS(dx) == IABS(dy) && IABS(dx) == distance)
					passable = true;
			}

			if (!passable)
			{
				if (node->m_costSoFar == 0x7fffffff && steps < 3)
					passable = true;
				if (node->m_costSoFar != 0x7fffffff)
					passable = true;
				PathNode *testNode = node->getNext();
				Int testCount = 0;
				while (testCount <= 3)
				{
					if (!testNode) break;
					if (testNode->m_costSoFar != 0x7fffffff)
						passable = true;
					testNode = testNode->getNext();
					++testCount;
				}
			}

			if (!passable)
			{
				if ((unsigned char)bfmeIsLinePassable(TheAI->pathfinder(),
					(Object *)obj, acceptableSurfaces, layer,
					anchor->getPosition(), node->getPosition(), blocked)) passable = true;
			}

			Bool onGround = curLayer == LAYER_GROUND || curLayer >= LAYER_FIRST_BRIDGE;
			if (onGround)
			{
				if (node->getLayer() != curLayer) {
					layer = node->getLayer();
					if (distance > 30) passable = false;
				}
				if (crusher && !passable) {
					if (IABS((Int)(node->getPosition()->y-m_pathTail->getPosition()->y)) +
						IABS((Int)(node->getPosition()->x-m_pathTail->getPosition()->x)) < 40)
						if (TheAI->pathfinder()->bfmeWorldLineHasNoHit(anchor->getPosition(),node->getPosition())) passable=true;
				}
			} else {
				PathNode *next=node->getNext();
				if (next && next->getLayer()!=curLayer && distance>30) passable=false;
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
			else anchor->setNextOptimized(node);
			break;
		}
		anchor = node;
	}

	m_isOptimized = true;
}

