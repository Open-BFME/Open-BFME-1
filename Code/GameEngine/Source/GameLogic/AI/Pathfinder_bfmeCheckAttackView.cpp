// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Coord3D;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	int bfmeCheckAttackViewAlt(Object *obj, void *targetPos);
	int bfmeCheckAttackViewAltHelper(Object *obj, Coord3D *cachedPos, void *targetPos);

	int bfmeCheckAttackView(Object *obj, void *targetPos);
	int bfmeCheckAttackViewHelper(Object *obj, Coord3D *cachedPos, void *targetPos);
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
