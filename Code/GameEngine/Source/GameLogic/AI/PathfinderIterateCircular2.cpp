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
	__forceinline Bool check(Int cellX, Int cellY) const;
};

class Pathfinder
{
public:
	Bool iterateCircular2(ICoord2D *centerCell, Int maxCells, void *adjustTargetInfoData);

protected:
	friend struct AdjustTargetInfo;
	Bool checkForTarget(const Object *object, Int cellX, Int cellY,
		const Weapon *weapon, const Object *target,
		const Coord3D *targetPosition, Int radius, Bool centerInCell, Coord3D *destination);
};

__forceinline Bool AdjustTargetInfo::check(Int cellX, Int cellY) const
{
	return m_pathfinder->checkForTarget(m_object, cellX, cellY, m_weapon, m_target,
		m_targetPosition, m_radius, m_centerInCell, m_destination);
}

Bool Pathfinder::iterateCircular2(ICoord2D *centerCell, Int maxCells, void *adjustTargetInfoData)
{
	if (Glo012F0239 && TheCRCParameterCheck)
	{
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
			"\t\tIterateCircular2 called with center=%d,%d, maxCells=%d",
			centerCell->x, centerCell->y, maxCells);
	}

	AdjustTargetInfo *info = (AdjustTargetInfo *)adjustTargetInfoData;
	if (info->check(centerCell->x, centerCell->y))
	{
		return true;
	}

	Int bestDistSq = 0;
	Int i = 0;
	Int j = 0;
	Int delta = 1;

	while (maxCells > 0)
	{
		maxCells -= 4 * delta + 2;
		for (Int count = delta; count > 0; --count)
		{
			++i;
			if (bestDistSq == 0 || i * i + j * j < bestDistSq)
			{
				if (info->check(centerCell->x + i, centerCell->y + j))
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
				if (info->check(centerCell->x + i, centerCell->y + j))
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
				if (info->check(centerCell->x + i, centerCell->y + j))
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
				if (info->check(centerCell->x + i, centerCell->y + j))
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
