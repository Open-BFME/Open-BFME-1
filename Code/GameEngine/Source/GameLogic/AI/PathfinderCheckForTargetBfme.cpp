// cl: /DNDEBUG /MD /EHsc
// Clean C++ reconstruction with the helper's observed BFME ABI view.
typedef int Int;
typedef bool Bool;
typedef unsigned char UByte;
enum PathfindLayerEnum { LAYER_GROUND = 1 };

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Coord3D { float x; float y; float z; };
class Object { };
class Weapon
{
public:
	Bool isGoalPosWithinAttackRange(const Object *, const Coord3D *,
		const Object *, const Coord3D *, Int) const;
};
class Pathfinder
{
public:
	UByte bfmeInnerE6E90(void *, void *, void *, void *, void *, void *,
		void **, Int);
protected:
	void adjustCoordToCell(Int, Int, Int, Coord3D &, PathfindLayerEnum);
	Bool checkForTarget(const Object *, Int, Int, const Weapon *,
		const Object *, const Coord3D *, Int, Bool, Coord3D *);
};

extern void j_000411d2(void);

class Luna39AdjustOwner
{
};

typedef void (Luna39AdjustOwner::*Luna39AdjustCall)(Int, Int, Int,
	Coord3D &, PathfindLayerEnum);

static __forceinline void luna39Adjust(Pathfinder *self, Int cellX, Int cellY,
	Int centerInCell, Coord3D &dest, PathfindLayerEnum layer)
{
	union
	{
		void (*raw)(void);
		Luna39AdjustCall member;
	} call;
	call.raw = j_000411d2;
	(reinterpret_cast<Luna39AdjustOwner *>(self)->*call.member)(
		cellX, cellY, centerInCell, dest, layer);
}

Bool Pathfinder::checkForTarget(const Object *obj, Int cellX, Int cellY,
	const Weapon *weapon, const Object *victim, const Coord3D *victimPos,
	Int iRadius, Bool center, Coord3D *dest)
{
	Coord3D adjustDest;
	Int centerInCell = *(volatile const Int *)&center;
	if (bfmeInnerE6E90((void *)obj, (void *)cellX, (void *)cellY, (void *)1,
					   (void *)iRadius, (void *)centerInCell,
					   (void **)&center, 0))
	{
		Bool centerOK = (*(const Int *)&center == 0);
		_ReadWriteBarrier();
		if (centerOK)
		{
			luna39Adjust(this, cellX, cellY, centerInCell, adjustDest, LAYER_GROUND);
			if (weapon->isGoalPosWithinAttackRange(obj, &adjustDest, victim,
										victimPos, 0x41200000))
			{
				*dest = adjustDest;
				return true;
			}
		}
	}
	return false;
}
