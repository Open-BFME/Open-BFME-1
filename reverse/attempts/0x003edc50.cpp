// ?getAircraftPath@Pathfinder@@QAEPAVPath@@PBVObject@@PBUCoord3D@@@Z
// partial score=0.86 date=2026-09-10
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME Pathfinder::getAircraftPath, retail RVA 0x003EDC50.
//
// This method's retail object views are narrower than the shared Zero Hour
// declarations: Object caches its position at +0x38 and AI at +0x204, Path
// and PathNode are both 0x24-byte allocations, and the current locomotor's
// template is an OVERRIDE walk.  Keep those views local to this TU.

typedef bool Bool;
typedef int Int;
typedef float Real;

struct Coord3D
{
	Coord3D &operator=(const Coord3D &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	Real x;
	Real y;
	Real z;
};

enum ObjectID
{
	INVALID_ID = 0
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

enum LocomotorAppearance
{
	LOCO_WINGS = 3
};

// The BFME locomotor template uses the existing typed override-chain helper
// at ILT 0x000022BB; its one-level view is distinct from the Zero Hour
// Overridable spelling used by the shared headers.
class LocomotorOverridable
{
public:
	LocomotorOverridable *friend_getFinalOverride(void);

	// The inline OVERRIDE access below advances one link before calling the
	// typed retail walker at 0x000022BB.
	void *m_head;
	LocomotorOverridable *m_nextOverride;
};

template <class T>
class OVERRIDE
{
public:
	const T *operator->(void) const
	{
		if (!m_overridable)
			return 0;
		LocomotorOverridable *next = m_overridable->m_nextOverride;
		if (next)
			return (const T *)next->friend_getFinalOverride();
		return (const T *)m_overridable;
	}

private:
	LocomotorOverridable *m_overridable;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h
class LocomotorTemplate : public LocomotorOverridable
{
private:
	unsigned char m_unreconstructed[0x68];

public:
	Int m_appearance;
};

class Locomotor
{
public:
	Int getAppearance(void) const
	{
		return m_template->m_appearance;
	}

private:
	void *m_head;
	OVERRIDE<LocomotorTemplate> m_template;
};

template <Int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

// getBuildingToNotPathAround is the 95th virtual slot (vtable +0x17c).
class AIUpdateInterface : public BfmeVirtualSlots<95>
{
public:
	virtual ObjectID getBuildingToNotPathAround(void) const = 0;

	Locomotor *getCurLocomotor(void) const
	{
		return m_curLocomotor;
	}

private:
	unsigned char m_unreconstructed[0x1c8];
	Locomotor *m_curLocomotor;
};

// Object's Thing prefix ends with the cached position at +0x38; the cached
// AI pointer used by this body is at +0x204.
class Object
{
public:
	const AIUpdateInterface *getAI(void) const
	{
		return m_ai;
	}

	const Coord3D *getPosition(void) const
	{
		return &m_position;
	}

private:
	void *m_head;
	void *m_template;
	unsigned char m_transform[0x30];
	Coord3D m_position;
	unsigned char m_unreconstructed[0x1c0];
	AIUpdateInterface *m_ai;
};

class PathNode
{
public:
	PathNode(const Coord3D *position, PathfindLayerEnum layer)
	{
		m_next = 0;
		m_previous = 0;
		m_nextOptimized = 0;
		m_position = *position;
		m_layer = layer;
		m_canOptimize = false;
		m_costSoFar = 0x7fffffff;
	}

	PathNode *getNext(void) const
	{
		return m_next;
	}

	void append(PathNode *newNode)
	{
		newNode->m_next = m_next;
		newNode->m_previous = this;
		if (newNode->m_next)
			newNode->m_next->m_previous = newNode;
		m_next = newNode;
	}

	void setNextOptimized(PathNode *node);

	PathNode *m_next;
	PathNode *m_previous;
	PathNode *m_nextOptimized;
	Coord3D m_position;
	PathfindLayerEnum m_layer;
	Bool m_canOptimize;
	Int m_costSoFar;
};

class __declspec(novtable) Path
{
public:
	Path();

	PathNode *getFirstNode(void) const
	{
		return m_path;
	}

	void prependNode(const Coord3D *position, PathfindLayerEnum layer);

	void markOptimized(void)
	{
		m_isOptimized = true;
	}

protected:
	virtual ~Path();

private:
	PathNode *m_path;
	PathNode *m_pathTail;
	Bool m_isOptimized;
	char m_tail[0x24 - 0x10];
};

class Pathfinder
{
public:
	Path *getAircraftPath(const Object *obj, const Coord3D *to);
	void setDebugPath(Path *debugpath);

protected:
	Bool segmentIntersectsTallBuilding(const PathNode *curNode, PathNode *nextNode,
		ObjectID ignoreBuilding, Coord3D *insertPos1, Coord3D *insertPos2,
		Coord3D *insertPos3);
	Bool circleClipsTallBuilding(const Coord3D *from, const Coord3D *to,
		Real circleRadius, ObjectID ignoreBuilding, Coord3D *adjustTo);
};

class AI
{
public:
	Pathfinder *pathfinder(void) const
	{
		return m_pathfinder;
	}

private:
	unsigned char m_unreconstructed[0x0c];
	Pathfinder *m_pathfinder;
};

struct GlobalData
{
	unsigned char m_unreconstructed[0xa88];
	Int m_debugAI;
};

extern AI *TheAI;
extern GlobalData *TheWritableGlobalData;

// ?getAircraftPath@Pathfinder@@QAEPAVPath@@PBVObject@@PBUCoord3D@@@Z
Path *Pathfinder::getAircraftPath(const Object *obj, const Coord3D *to)
{
	Pathfinder *self = this;
	Path *thePath = new Path;
	const AIUpdateInterface *ai = obj->getAI();
	ObjectID avoidObject = INVALID_ID;
	if (ai)
		avoidObject = ai->getBuildingToNotPathAround();

	Bool checkClips = false;
	if (ai && ai->getCurLocomotor())
	{
		if (ai->getCurLocomotor()->getAppearance() == LOCO_WINGS)
			checkClips = true;
	}

	Real radius = 100;
	Coord3D adjDest = *to;
	if (checkClips)
		self->circleClipsTallBuilding(obj->getPosition(), to, radius, avoidObject, &adjDest);

	PathfindLayerEnum layer = LAYER_GROUND;
	thePath->prependNode(&adjDest, layer);
	Coord3D pos = *obj->getPosition();
	pos.z = to->z;
	thePath->prependNode(&pos, layer);

	Int limit = 20;
	PathNode *curNode = thePath->getFirstNode();
	while (curNode && curNode->getNext())
	{
		Coord3D newPos1, newPos2, newPos3;
		if (self->segmentIntersectsTallBuilding(curNode, curNode->getNext(), avoidObject,
			&newPos1, &newPos2, &newPos3))
		{
			PathNode *newNode3 = new PathNode(&newPos3, layer);
			curNode->append(newNode3);
			PathNode *newNode2 = new PathNode(&newPos2, layer);
			curNode->append(newNode2);
			PathNode *newNode1 = new PathNode(&newPos1, layer);
			curNode->append(newNode1);
			curNode = newNode2;
		}
		curNode = curNode->getNext();
		limit--;
		if (limit < 0)
			break;
	}

	curNode = thePath->getFirstNode();
	while (curNode && curNode->getNext())
	{
		curNode->setNextOptimized(curNode->getNext());
		curNode = curNode->getNext();
	}
	thePath->markOptimized();
	if (TheWritableGlobalData->m_debugAI == 1)
		TheAI->pathfinder()->setDebugPath(thePath);

	return thePath;
}
