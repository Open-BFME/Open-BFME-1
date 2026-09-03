// ?checkForTarget@Pathfinder@@IAE_NPBVObject@@HHPBVWeapon@@0PBUCoord3D@@H_NPAU4@@Z
// partial score=0.92 date=2026-09-03
typedef int Int;
typedef bool Bool;

static inline Bool isZero(Int value)
{
    return value == 0;
}

struct Coord3D {
    float x;
    float y;
    float z;
};

class Object {
};

class Weapon {
public:
    Bool isGoalPosWithinAttackRange(const Object *, const Coord3D *,
                                    const Object *, const Coord3D *, Int) const;
};

class Pathfinder {
public:
    Bool bfmeInnerE6E90(const Object *, Int, Int, Int, Int, Int, Int *, Int);
    void adjustCoordToCell(Int, Int, Int, Coord3D &, Int);

protected:
    Bool checkForTarget(const Object *, Int, Int, const Weapon *,
                        const Object *, const Coord3D *, Int, Bool, Coord3D *);
};

Bool Pathfinder::checkForTarget(const Object *obj, Int cellX, Int cellY,
                                const Weapon *weapon, const Object *victim,
                                const Coord3D *victimPos, Int iRadius,
                                Bool center, Coord3D *dest)
{
    Coord3D adjustDest;
    Int centerInCell = *(volatile const Int *)&center;
    Bool centerIsZero;
    if (bfmeInnerE6E90(obj, cellX, cellY, 1, iRadius, centerInCell,
                       (Int *)&center, 0) &&
        (centerIsZero = !(*(const Int *)&center))) {
        adjustCoordToCell(cellX, cellY, centerInCell, adjustDest, 1);
        if (weapon->isGoalPosWithinAttackRange(obj, &adjustDest, victim,
                                               victimPos, 0x41200000)) {
            *dest = adjustDest;
            return true;
        }
    }
    return false;
}
