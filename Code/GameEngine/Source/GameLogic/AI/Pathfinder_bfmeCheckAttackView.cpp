// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Coord3D;
class Object;

class Pathfinder
{
public:
	int bfmeCheckAttackView(Object *obj, void *targetPos);
	int bfmeCheckAttackViewHelper(Object *obj, Coord3D *cachedPos, void *targetPos);
};

// ?bfmeCheckAttackView@Pathfinder@@QAEHPAVObject@@PAX@Z
int Pathfinder::bfmeCheckAttackView(Object *obj, void *targetPos)
{
	Coord3D *cachedPos = (Coord3D *)((char *)obj + 0x38);
	return bfmeCheckAttackViewHelper(obj, cachedPos, targetPos);
}
