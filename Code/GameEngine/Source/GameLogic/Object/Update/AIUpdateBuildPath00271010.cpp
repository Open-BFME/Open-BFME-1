// cl: /DNDEBUG /MD /EHsc
// Opaque path-builder body at retail RVA 0x00271010.

typedef int Int;
typedef bool Bool;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

struct Coord3D
{
	float x, y, z;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

class Object
{
public:
	char m_unmodelled_00[0x38];
	Coord3D m_position;
};

class PathNode
{
public:
	PathNode *getNext(void) const { return m_next; }
	void setNextOptimized(PathNode *node);

	PathNode *m_next;
	PathNode *m_prev;
	PathNode *m_nextOptimized;
	Coord3D m_position;
	PathfindLayerEnum m_layer;
	Bool m_canOptimize;
	Int m_costSoFar;
};

class AIUpdateInterface;

class Path
{
	friend class AIUpdateInterface;

public:
	Path();
	PathNode *getFirstNode(void) const { return m_path; }
	void prependNode(const Coord3D *position, PathfindLayerEnum layer);
	void markOptimized(void) { m_isOptimized = true; }

protected:
	virtual ~Path();

private:
	PathNode *m_path;
	PathNode *m_pathTail;
	Bool m_isOptimized;
	char m_unmodelled_0d[0x24 - 0x0d];
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *object, const Coord3D *position);
};

class Pathfinder
{
public:
	void setDebugPath(Path *path);
};

class AI
{
public:
	char m_unmodelled_00[0x0c];
	Pathfinder *m_pathfinder;
};

class GlobalData
{
public:
	char m_unmodelled_00[0xa88];
	Int m_debugAI;
};

extern TerrainLogic *TheTerrainLogic;
extern AI *TheAI;
extern GlobalData *TheWritableGlobalData;

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class UpdateModule : public BfmeVirtualSlots<122>
{
public:
	Object *getObject(void) const { return m_object; }

protected:
	char m_unmodelled_04[4];
	Object *m_object;
	char m_unmodelled_0c[0x14];
};

class AICommandInterface
{
private:
	char m_unmodelled_00[4];
};

class AIUpdateInterface : public UpdateModule, public AICommandInterface
{
public:
	virtual void setLocomotorGoalNone(void) = 0;
	void buildPath_00271010(const Coord3D *, const Coord3D *, Int,
		PathfindLayerEnum, const Coord3D *, const Coord3D *);

private:
	void destroyPath(void)
	{
		if (m_path) {
			Path *oldPath = m_path;
			oldPath->Path::~Path();
			::operator delete(oldPath);
		}
		m_path = 0;
		m_waitingForPath = false;
		m_isBlockedAndStuck = false;
		m_isAttackPath = false;
		setLocomotorGoalNone();
	}

	char m_unmodelled_24[0x140 - 0x24];
	Path *m_path;
	char m_unmodelled_144[0x1d8 - 0x144];
	Int m_locomotorGoalType;
	Coord3D m_locomotorGoalData;
	char m_unmodelled_1e8[0x31e - 0x1e8];
	Bool m_waitingForPath;
	Bool m_isAttackPath;
	char m_unmodelled_320[0x326 - 0x320];
	Bool m_isBlockedAndStuck;
};

void AIUpdateInterface::buildPath_00271010(
	const Coord3D *firstPosition,
	const Coord3D *thirdPosition,
	Int cost,
	PathfindLayerEnum layer,
	const Coord3D *middlePosition,
	const Coord3D *destination)
{
	destroyPath();
	Path *newPath = new Path;
	m_path = newPath;
	m_path->prependNode(destination,
		TheTerrainLogic->getLayerForDestination(getObject(), destination));
	m_path->getFirstNode()->m_costSoFar = cost;
	if (middlePosition->x != destination->x
		|| middlePosition->y != destination->y
		|| middlePosition->z != destination->z) {
		m_path->prependNode(middlePosition,
			TheTerrainLogic->getLayerForDestination(getObject(), middlePosition));
		m_path->getFirstNode()->m_costSoFar = cost;
	}
	m_path->prependNode(thirdPosition, layer);
	m_path->getFirstNode()->setNextOptimized(
		m_path->getFirstNode()->getNext());
	m_path->getFirstNode()->m_costSoFar = cost;
	m_path->prependNode(firstPosition,
		TheTerrainLogic->getLayerForDestination(getObject(), firstPosition));
	m_path->getFirstNode()->setNextOptimized(
		m_path->getFirstNode()->getNext());
	Coord3D objectPosition;
	objectPosition.x = getObject()->m_position.x;
	objectPosition.y = getObject()->m_position.y;
	objectPosition.z = getObject()->m_position.z;
	m_path->prependNode(&objectPosition,
		TheTerrainLogic->getLayerForDestination(getObject(), &objectPosition));
	m_path->getFirstNode()->setNextOptimized(
		m_path->getFirstNode()->getNext());
	m_path->markOptimized();
	if (TheWritableGlobalData->m_debugAI == 1)
		TheAI->m_pathfinder->setDebugPath(m_path);
	m_locomotorGoalType = 4;
	m_locomotorGoalData = *destination;
}
