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
	Bool iterateCircular2(ICoord2D *scanCenterCell, Int remainingCellBudget, void *adjustTargetInfoData);

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

Bool Pathfinder::iterateCircular2(ICoord2D *scanCenterCell, Int remainingCellBudget, void *adjustTargetInfoData)
{
	if (Glo012F0239 && TheCRCParameterCheck)
	{
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
			"\t\tIterateCircular2 called with center=%d,%d, maxCells=%d",
			scanCenterCell->x, scanCenterCell->y, remainingCellBudget);
	}

	AdjustTargetInfo *targetSearch = (AdjustTargetInfo *)adjustTargetInfoData;
	if (targetSearch->check(scanCenterCell->x, scanCenterCell->y))
	{
		return true;
	}

	Int bestOffsetDistanceSquared = 0;
	Int cellOffsetX = 0;
	Int cellOffsetY = 0;
	Int ringExtent = 1;

	while (remainingCellBudget > 0)
	{
		remainingCellBudget -= 4 * ringExtent + 2;
		for (Int stepsRemaining = ringExtent; stepsRemaining > 0; --stepsRemaining)
		{
			++cellOffsetX;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->check(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = ringExtent; stepsRemaining > 0; --stepsRemaining)
		{
			++cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->check(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetX;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->check(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->check(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
				}
			}
		}

		if (bestOffsetDistanceSquared == 0)
		{
			ringExtent += 2;
		}
		else
		{
			return true;
		}
	}

	return false;
}
