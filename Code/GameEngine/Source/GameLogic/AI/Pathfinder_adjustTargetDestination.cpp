// ?adjustTargetDestination@Pathfinder@@QAE_NPBVObject@@0PBUCoord3D@@PBVWeapon@@PAU3@@Z
// BFME target 0x003F2DB0.  The radial target scan is the separate retail
// helper at 0x003F18E0; this body only builds its compact work record.
// cl: /DNDEBUG /MD /EHsc
// readable body of ?adjustTargetDestination@Pathfinder@@QAE_NPBVObject@@0PBUCoord3D@@PBVWeapon@@PAU3@@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp

typedef int Int;
typedef unsigned char Bool;

class Object;
class Weapon;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

struct AdjustTargetInfo;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void bfmeQuery(Object *obj, Int *radius, Bool *center);
	bool worldToCell(const Coord3D *world, ICoord2D *cell);
	bool iterateCircular2(ICoord2D *cell, Int limit, void *info);
	bool adjustTargetDestination(const Object *obj, const Object *target,
		const Coord3D *targetPos, const Weapon *weapon, Coord3D *dest);
};

struct AdjustTargetInfo
{
	Pathfinder *m_pathfinder;
	Object *m_obj;
	Bool m_center;
	Int m_radius;
	Coord3D *m_dest;
	Object *m_target;
	const Coord3D *m_targetPos;
	const Weapon *m_weapon;
};

bool Pathfinder::adjustTargetDestination(const Object *obj, const Object *target,
	const Coord3D *targetPos, const Weapon *weapon, Coord3D *dest)
{
	ICoord2D cell;
	Bool center;
	Coord3D adjustDest;

	bfmeQuery((Object *)obj, &cell.x, &center);
	adjustDest.x = dest->x;
	adjustDest.y = dest->y;
	adjustDest.z = dest->z;
	if (!center)
	{
		adjustDest.x += 5.0f;
		adjustDest.y += 5.0f;
	}
	if (worldToCell(&adjustDest, &cell))
		return false;

	AdjustTargetInfo info;
	info.m_pathfinder = this;
	info.m_obj = (Object *)obj;
	info.m_dest = dest;
	info.m_target = (Object *)target;
	info.m_targetPos = targetPos;
	info.m_weapon = weapon;
	bfmeQuery(info.m_obj, &info.m_radius, &info.m_center);
	return iterateCircular2(&cell, 0x190, &info);
}
