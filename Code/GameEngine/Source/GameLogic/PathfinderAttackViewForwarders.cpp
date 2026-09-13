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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	bool isSignificantlyAboveTerrain(void) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	int bfmeCheckAttackViewAlt(Object *obj, void *targetPos);
	int bfmeCheckAttackViewAltHelper(Object *obj, Coord3D *cachedPos, void *targetPos);

	int bfmeCheckAttackView(Object *obj, void *targetPos);
	int bfmeCheckAttackViewHelper(Object *obj, Coord3D *cachedPos, void *targetPos);

	bool isAttackViewBlockedByObstacle(const Object *source, const Coord3D *pos);
	bool isAttackViewBlockedByObstacle(const Object *source, const Object *target);
	bool isAttackViewBlockedByObstacle(const Object *source, const Coord3D *sourcePos, const Object *target, const Coord3D *targetPos);
};

// ?bfmeCheckAttackViewAlt@Pathfinder@@QAEHPAVObject@@PAX@Z
int Pathfinder::bfmeCheckAttackViewAlt(Object *obj, void *targetPos)
{
	Coord3D *cachedPos = (Coord3D *)((char *)obj + 0x38);
	return bfmeCheckAttackViewAltHelper(obj, cachedPos, targetPos);
}

// ?bfmeCheckAttackView@Pathfinder@@QAEHPAVObject@@PAX@Z
int Pathfinder::bfmeCheckAttackView(Object *obj, void *targetPos)
{
	Coord3D *cachedPos = (Coord3D *)((char *)obj + 0x38);
	return bfmeCheckAttackViewHelper(obj, cachedPos, targetPos);
}

// ?isAttackViewBlockedByObstacle@Pathfinder@@QAE_NPBVObject@@PBUCoord3D@@@Z
bool Pathfinder::isAttackViewBlockedByObstacle(const Object *source, const Coord3D *pos)
{
	const Coord3D *sourcePos = (const Coord3D *)((const char *)source + 0x38);
	return isAttackViewBlockedByObstacle(source, sourcePos, 0, pos);
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
