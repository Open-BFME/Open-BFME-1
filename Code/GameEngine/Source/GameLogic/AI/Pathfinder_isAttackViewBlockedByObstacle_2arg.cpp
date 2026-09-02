// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Coord3D;
class Object;

class Pathfinder
{
public:
	bool isAttackViewBlockedByObstacle(const Object *source, const Coord3D *pos);
	bool isAttackViewBlockedByObstacle(const Object *source, const Coord3D *sourcePos, const Object *victim, const Coord3D *victimPos);
};

// ?isAttackViewBlockedByObstacle@Pathfinder@@QAE_NPBVObject@@PBUCoord3D@@@Z
bool Pathfinder::isAttackViewBlockedByObstacle(const Object *source, const Coord3D *pos)
{
	const Coord3D *sourcePos = (const Coord3D *)((const char *)source + 0x38);
	return isAttackViewBlockedByObstacle(source, sourcePos, 0, pos);
}
