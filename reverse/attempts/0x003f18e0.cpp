// ?iterateCircular2@Pathfinder@@QAE_NPAUICoord2D@@HPAX@Z
// partial score=0.72 date=2026-09-09
// cl: /DNDEBUG /MD
//
// Pathfinder::iterateCircular2 at retail 0x003F18E0.
//
// BFME keeps the radial search as a private helper instead of spelling the
// four-side walk inside adjustTargetDestination.  Its user record is the
// eight-field AdjustTargetInfo assembled by that caller.

typedef int Int;
typedef bool Bool;

struct ICoord2D
{
	Int x;
	Int y;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
class Weapon;

extern "C" unsigned char bfmeRetailCritterDesyncFlag;
extern "C" void *bfmeRetailCritterDesyncSink;
extern "C" void bfmeRetailCritterDesyncLog(void *, const char *, ...);

struct AdjustTargetInfo
{
	class Pathfinder *pathfinder;
	Object *obj;
	Bool center;
	Int radius;
	Coord3D *dest;
	Object *target;
	const Coord3D *targetPos;
	const Weapon *weapon;
};

class Pathfinder
{
public:
	Bool checkForTarget(const Object *obj, Int cellX, Int cellY,
		const Weapon *weapon, const Object *target,
		const Coord3D *targetPos, Int radius, Bool center, Coord3D *dest);

	Bool iterateCircular2(ICoord2D *cell, Int limit, void *userData);
};

Bool Pathfinder::iterateCircular2(ICoord2D *cell, Int limit, void *userData)
{
	if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
	{
		bfmeRetailCritterDesyncLog(bfmeRetailCritterDesyncSink,
			"\t\tIterateCircular2 called with center=%d,%d, maxCells=%d",
			cell->x, cell->y, limit);
	}

	AdjustTargetInfo *info = (AdjustTargetInfo *)userData;
	if (info->pathfinder->checkForTarget(
		info->obj, cell->x, cell->y, info->weapon, info->target,
		info->targetPos, info->radius, info->center, info->dest))
	{
		return true;
	}

	Int i = 0;
	Int j = 0;
	Int bestDistSq = 0;
	Int side = 1;
	Int delta = 4;

	while (limit > 0)
	{
		limit -= delta + 2;
		for (Int count = 0; count < side; ++count)
		{
			++i;
			if (bestDistSq == 0 || i * i + j * j < bestDistSq)
			{
				if (info->pathfinder->checkForTarget(
					info->obj, cell->x + i, cell->y + j, info->weapon,
					info->target, info->targetPos, info->radius,
					info->center, info->dest))
				{
					bestDistSq = i * i + j * j;
				}
			}
		}

		for (Int count = 0; count < side; ++count)
		{
			++j;
			if (bestDistSq == 0 || i * i + j * j < bestDistSq)
			{
				if (info->pathfinder->checkForTarget(
					info->obj, cell->x + i, cell->y + j, info->weapon,
					info->target, info->targetPos, info->radius,
					info->center, info->dest))
				{
					bestDistSq = i * i + j * j;
				}
			}
		}

		for (Int count = 0; count <= side; ++count)
		{
			--i;
			if (bestDistSq == 0 || i * i + j * j < bestDistSq)
			{
				if (info->pathfinder->checkForTarget(
					info->obj, cell->x + i, cell->y + j, info->weapon,
					info->target, info->targetPos, info->radius,
					info->center, info->dest))
				{
					bestDistSq = i * i + j * j;
				}
			}
		}

		for (Int count = 0; count <= side; ++count)
		{
			--j;
			if (bestDistSq == 0 || i * i + j * j < bestDistSq)
			{
				if (info->pathfinder->checkForTarget(
					info->obj, cell->x + i, cell->y + j, info->weapon,
					info->target, info->targetPos, info->radius,
					info->center, info->dest))
				{
					bestDistSq = i * i + j * j;
				}
			}
		}

		if (bestDistSq == 0)
		{
			side += 2;
			delta += 8;
		}
		else
		{
			return true;
		}
	}

	return false;
}
