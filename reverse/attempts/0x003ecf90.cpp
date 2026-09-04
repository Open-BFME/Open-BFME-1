// ?checkForTarget@Pathfinder@@IAE_NPBVObject@@HHPBVWeapon@@0PBUCoord3D@@H_NPAU4@@Z
// partial score=0.96 date=2026-09-04
// ?checkForTarget@Pathfinder@@IAE_NPBVObject@@HHPBVWeapon@@0PBUCoord3D@@H_NPAU4@@Z present-unmatched
// Retail 0x003ECF90: Pathfinder::checkForTarget BFME body.

typedef int Int;
typedef bool Bool;
static inline Bool isZero(Int value)
{
	return value == 0;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	Bool isGoalPosWithinAttackRange(const Object *, const Coord3D *,
		const Object *, const Coord3D *, Int) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Bool bfmeInnerE6E90(const Object *, Int, Int, Int, Int, Int, Int *, Int);
	Bool shapeProbe(Int value);

protected:
	void adjustCoordToCell(Int, Int, Int, Coord3D &, Int);
	Bool checkForTarget(const Object *, Int, Int, const Weapon *,
		const Object *, const Coord3D *, Int, Bool, Coord3D *);
};

Bool Pathfinder::checkForTarget(const Object *obj, Int cellX, Int cellY,
	const Weapon *weapon, const Object *victim, const Coord3D *victimPos,
	Int iRadius, Bool center, Coord3D *dest)
{
	Coord3D adjustDest;
	Int centerInCell = *(volatile const Int *)&center;
	if (bfmeInnerE6E90(obj, cellX, cellY, 1, iRadius, centerInCell,
					   (Int *)&center, 0)) {
		center = (*(const Int *)&center == 0);
		if (center) {
			adjustCoordToCell(cellX, cellY, centerInCell, adjustDest, 1);
			if (weapon->isGoalPosWithinAttackRange(obj, &adjustDest, victim,
										victimPos, 0x41200000)) {
				*dest = adjustDest;
				return true;
			}
		}
	}
	return false;
}

Bool Pathfinder::shapeProbe(Int value)
{
	Bool result;
	result = (*(const Int *)&value == 0);
	if (result)
		return (Bool)(value + 1);
	return false;
}
