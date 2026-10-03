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
		const Object *, const Coord3D *, float) const;
};
class Pathfinder
{
public:
protected:
	void adjustCoordToCell(Int, Int, Int, Coord3D &, PathfindLayerEnum);
	Bool checkForTarget(const Object *object, Int cellX, Int cellY, const Weapon *weapon,
		const Object *targetObject, const Coord3D *targetPosition, Int radius,
		Bool centerFlag, Coord3D *adjustedDestination);
};

extern void j_000411d2(void);
// ILT 0x00049F3F (?j_00049f3f@@YAXXZ, jumps to the 8-argument query at
// 0x007DF580); thiscall, so it is called through a member-pointer union.
extern void j_00049f3f(void);

class Luna39AdjustOwner
{
};

typedef void (Luna39AdjustOwner::*Luna39AdjustCall)(Int, Int, Int,
	Coord3D &, PathfindLayerEnum);

typedef UByte (Luna39AdjustOwner::*Luna39InnerCall)(void *, void *, void *,
	void *, void *, void *, void **, Int);

static __forceinline UByte luna39Inner(Pathfinder *self, void *a, void *b,
	void *c, void *d, void *e, void *f, void **g, Int h)
{
	union
	{
		void (*raw)(void);
		Luna39InnerCall member;
	} call;
	call.raw = j_00049f3f;
	return (reinterpret_cast<Luna39AdjustOwner *>(self)->*call.member)(
		a, b, c, d, e, f, g, h);
}

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

Bool Pathfinder::checkForTarget(const Object *object, Int cellX, Int cellY,
	const Weapon *weapon, const Object *targetObject, const Coord3D *targetPosition,
	Int radius, Bool centerFlag, Coord3D *adjustedDestination)
{
	Coord3D adjustDest;
	Int centerInCell = *(volatile const Int *)&centerFlag;
	if (luna39Inner(this, (void *)object, (void *)cellX, (void *)cellY, (void *)1,
					   (void *)radius, (void *)centerInCell,
					   (void **)&centerFlag, 0))
	{
		Bool centerOK = (*(const Int *)&centerFlag == 0);
		_ReadWriteBarrier();
		if (centerOK)
		{
			luna39Adjust(this, cellX, cellY, centerInCell, adjustDest, LAYER_GROUND);
			if (weapon->isGoalPosWithinAttackRange(object, &adjustDest, targetObject,
									targetPosition, 10.0f))
			{
				*adjustedDestination = adjustDest;
				return true;
			}
		}
	}
	return false;
}
