// ?iterateCircular2@Pathfinder@@QAE_NPAUICoord2D@@HPAX@Z
// cl: /DNDEBUG /MD
//
// The matched adjustTargetDestination caller at 0x003F2DB0 fills the eight-field
// AdjustTargetInfo record and calls this scan. Five pinned checkForTarget calls
// confirm the target.

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
class Pathfinder;
class CRCParameterCheck;

extern bool Glo012F0239;
extern CRCParameterCheck *TheCRCParameterCheck;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(
	CRCParameterCheck *check, const char *format, ...);

struct AdjustTargetInfo
{
	Pathfinder *m_pathfinder;
	Object *m_object;
	Bool m_centerInCell;
	Int m_radius;
	Coord3D *m_destination;
	Object *m_target;
	const Coord3D *m_targetPosition;
	const Weapon *m_weapon;
	__forceinline Bool check(Int x, Int y) const;
};

class Pathfinder
{
public:
	Bool iterateCircular2(ICoord2D *cell, Int limit, void *userData);

protected:
	friend struct AdjustTargetInfo;
	Bool checkForTarget(const Object *obj, Int cellX, Int cellY,
		const Weapon *weapon, const Object *target,
		const Coord3D *targetPos, Int radius, Bool center, Coord3D *dest);
};

__forceinline Bool AdjustTargetInfo::check(Int x, Int y) const
{
	return m_pathfinder->checkForTarget(m_object, x, y, m_weapon, m_target,
		m_targetPosition, m_radius, m_centerInCell, m_destination);
}

Bool Pathfinder::iterateCircular2(ICoord2D *cell, Int limit, void *userData)
{
	if (Glo012F0239 && TheCRCParameterCheck)
	{
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
			"\t\tIterateCircular2 called with center=%d,%d, maxCells=%d",
			cell->x, cell->y, limit);
	}

	AdjustTargetInfo *info = (AdjustTargetInfo *)userData;
	if (info->check(cell->x, cell->y))
	{
		return true;
	}

	Int bestDistSq = 0;
	Int i = 0;
	Int j = 0;
	Int delta = 1;

	while (limit > 0)
	{
		limit -= 4 * delta + 2;
		for (Int count = delta; count > 0; --count)
		{
			++i;
			if (bestDistSq == 0 || i * i + j * j < bestDistSq)
			{
				if (info->check(cell->x + i, cell->y + j))
				{
					bestDistSq = i * i + j * j;
				}
			}
		}

		for (Int count = delta; count > 0; --count)
		{
			++j;
			if (bestDistSq == 0 || i * i + j * j < bestDistSq)
			{
				if (info->check(cell->x + i, cell->y + j))
				{
					bestDistSq = i * i + j * j;
				}
			}
		}

		for (Int count = 0; count <= delta; ++count)
		{
			--i;
			if (bestDistSq == 0 || i * i + j * j < bestDistSq)
			{
				if (info->check(cell->x + i, cell->y + j))
				{
					bestDistSq = i * i + j * j;
				}
			}
		}

		for (Int count = 0; count <= delta; ++count)
		{
			--j;
			if (bestDistSq == 0 || i * i + j * j < bestDistSq)
			{
				if (info->check(cell->x + i, cell->y + j))
				{
					bestDistSq = i * i + j * j;
				}
			}
		}

		if (bestDistSq == 0)
		{
			delta += 2;
		}
		else
		{
			return true;
		}
	}

	return false;
}
