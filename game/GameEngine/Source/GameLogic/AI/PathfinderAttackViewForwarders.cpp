// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Open-BFME: the four Pathfinder attack-view forwarders -- the only bodies in
// this class retail compiled with optimisation on.
//
//   ?bfmeCheckAttackViewAlt@         0x003EA940, 22 bytes
//   ?bfmeCheckAttackView@            0x003EA960, 22 bytes
//   ?isAttackViewBlockedByObstacle@  0x003EE730, 52 bytes  (source, target)
//   ?isAttackViewBlockedByObstacle@  0x003EE780, 24 bytes  (source, position)
//
// Every one of the four does the same one thing before it calls the real
// worker: it reads the object's cached position out of the object itself at
// +0x38 and passes it along. Four files each spelled that cast privately, so
// the offset appeared four times and read as four coincidences. It is one fact
// about Object, and it is the whole reason these forwarders exist -- the
// workers want positions, the callers have objects.
//
// The Alt pair and the named pair are the same shape twice over: two entry
// points, two helpers, one cast each, 22 bytes each. The 52-byte member is the
// only one that does more, refusing outright when the target is significantly
// above the terrain, which is why it is more than twice the size of its
// position-taking sibling at 24.

struct Coord3D;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	bool isSignificantlyAboveTerrain(void) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	int bfmeCheckAttackViewAlt(Object *object, void *targetPosition);
	int bfmeCheckAttackViewAltHelper(Object *object, Coord3D *cachedPosition, void *targetPosition);

	int bfmeCheckAttackView(Object *object, void *targetPosition);
	int bfmeCheckAttackViewHelper(Object *object, Coord3D *cachedPosition, void *targetPosition);

	bool isAttackViewBlockedByObstacle(const Object *source, const Coord3D *targetPosition);
	bool isAttackViewBlockedByObstacle(const Object *source, const Object *target);
	bool isAttackViewBlockedByObstacle(const Object *source, const Coord3D *sourcePosition, const Object *target, const Coord3D *targetPosition);
};

// ?bfmeCheckAttackViewAlt@Pathfinder@@QAEHPAVObject@@PAX@Z
int Pathfinder::bfmeCheckAttackViewAlt(Object *object, void *targetPosition)
{
	Coord3D *cachedPos = (Coord3D *)((char *)object + 0x38);
	return bfmeCheckAttackViewAltHelper(object, cachedPos, targetPosition);
}

// ?bfmeCheckAttackView@Pathfinder@@QAEHPAVObject@@PAX@Z
int Pathfinder::bfmeCheckAttackView(Object *object, void *targetPosition)
{
	Coord3D *cachedPos = (Coord3D *)((char *)object + 0x38);
	return bfmeCheckAttackViewHelper(object, cachedPos, targetPosition);
}

// ?isAttackViewBlockedByObstacle@Pathfinder@@QAE_NPBVObject@@PBUCoord3D@@@Z
bool Pathfinder::isAttackViewBlockedByObstacle(const Object *source, const Coord3D *targetPosition)
{
	const Coord3D *sourcePos = (const Coord3D *)((const char *)source + 0x38);
	return isAttackViewBlockedByObstacle(source, sourcePos, 0, targetPosition);
}

// ?isAttackViewBlockedByObstacle@Pathfinder@@QAE_NPBVObject@@0@Z
bool Pathfinder::isAttackViewBlockedByObstacle(const Object *source, const Object *target)
{
	if (target->isSignificantlyAboveTerrain()) {
		return false;
	}
	const Coord3D *sourcePos = (const Coord3D *)((const char *)source + 0x38);
	const Coord3D *targetPos = (const Coord3D *)((const char *)target + 0x38);
	return isAttackViewBlockedByObstacle(source, sourcePos, target, targetPos);
}
