// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

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
	bool isAttackViewBlockedByObstacle(const Object *source, const Coord3D *pos);
	bool isAttackViewBlockedByObstacle(const Object *source, const Object *target);
	bool isAttackViewBlockedByObstacle(const Object *source, const Coord3D *sourcePos, const Object *target, const Coord3D *targetPos);
};

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
