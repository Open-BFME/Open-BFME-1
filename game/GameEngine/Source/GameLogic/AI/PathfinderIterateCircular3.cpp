// cl: /DNDEBUG /MD
//
// Retail 0x003E29F0, 991 bytes, ret 0x14.
// The only reference in .text to the "IterateCircular3 called with ..." string
// (VA 0x010EEAE8) is this body's push at +0x3B, so the diagnostic names this one
// function. Its caller 0x003E8E10 sets ECX to its Pathfinder receiver before the
// call (+0x60F) and the body never reads ECX, like the landed
// Pathfinder::iterateCircular2 at 0x003F18E0.
//
// The callback record is the landed Rva003DEAB0Struct
// (game/GameEngine/Source/GameLogic/AI/PathfindAdjustDeab0.cpp). Its +0x28 object
// supplies the distance origin through Thing::m_cachedPos at +0x38.
//
// Retail passes the center cell to checkCell as an 8-byte aggregate copy. Only a
// by-value ICoord2D argument produces the retail register choice for that first
// call. The landed callee declares the same two stack slots as (Int, Int), so
// the copy is passed through a member pointer of that signature.

typedef int Int;
typedef bool Bool;
typedef float Real;

struct ICoord2D
{
	Int x;
	Int y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class CRCParameterCheck;

extern bool Glo012F0239;
extern CRCParameterCheck *TheCRCParameterCheck;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(
	CRCParameterCheck *check, const char *format, ...);

class Object
{
public:
	const Coord3D *getPosition() const { return &m_cachedPos; }

private:
	char m_pad[0x38];
	Coord3D m_cachedPos;
};

class Rva003DEAB0Struct
{
public:
	Bool checkCell(Int cellX, Int cellY);

	__forceinline Bool checkCellCopy(ICoord2D cell)
	{
		typedef Bool (Rva003DEAB0Struct::*CellCopyCheck)(ICoord2D);
		return (this->*reinterpret_cast<CellCopyCheck>(&Rva003DEAB0Struct::checkCell))(cell);
	}

	char m_pad[0x28];
	Object *m_target;
};

class Pathfinder
{
public:
	Bool iterateCircular3(const ICoord2D *searchCenterCell, Int maxCells,
		ICoord2D *foundCell, void *callbackData, Int iterationsAfterHit);
};

Bool Pathfinder::iterateCircular3(const ICoord2D *searchCenterCell, Int maxCells,
	ICoord2D *foundCell, void *callbackData, Int iterationsAfterHit)
{
	Bool found = false;
	Real best = 0.0f;
	Int remaining = 10000;

	if (Glo012F0239 && TheCRCParameterCheck)
	{
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
			"\t\tIterateCircular3 called with center=%d,%d, maxCells=%d",
			searchCenterCell->x, searchCenterCell->y, maxCells);
	}

	Rva003DEAB0Struct *info = (Rva003DEAB0Struct *)callbackData;
	if (info->checkCellCopy(*searchCenterCell))
	{
		foundCell->x = searchCenterCell->x;
		foundCell->y = searchCenterCell->y;
		Real dx = (Real)(searchCenterCell->x * 10) - info->m_target->getPosition()->x;
		Real dy = (Real)(searchCenterCell->y * 10) - info->m_target->getPosition()->y;
		found = true;
		best = dx * dx + dy * dy;
		remaining = iterationsAfterHit;
	}

	Int x = 0;
	Int y = 0;
	for (Int side = 1; maxCells > 0; side += 2)
	{
		if (--remaining <= 0)
			return found;
		maxCells -= 4 * side + 2;

		for (Int i = 0; i < side; ++i)
		{
			Int cellX = searchCenterCell->x;
			++x;
			cellX += x;
			Real dx = (Real)(cellX * 10) - info->m_target->getPosition()->x;
			Real dy = (Real)((searchCenterCell->y + y) * 10) - info->m_target->getPosition()->y;
			Real distance = dx * dx + dy * dy;
			if ((!found || !(distance >= best)) && info->checkCell(cellX, searchCenterCell->y + y))
			{
				foundCell->x = searchCenterCell->x + x;
				foundCell->y = searchCenterCell->y + y;
				found = true;
				best = distance;
				remaining = iterationsAfterHit;
			}
		}

		for (Int j = 0; j < side; ++j)
		{
			++y;
			Real dx = (Real)((searchCenterCell->x + x) * 10) - info->m_target->getPosition()->x;
			Real dy = (Real)((searchCenterCell->y + y) * 10) - info->m_target->getPosition()->y;
			Real distance = dx * dx + dy * dy;
			if ((!found || !(distance >= best)) && info->checkCell(searchCenterCell->x + x, searchCenterCell->y + y))
			{
				foundCell->x = searchCenterCell->x + x;
				foundCell->y = searchCenterCell->y + y;
				found = true;
				best = distance;
				remaining = iterationsAfterHit;
			}
		}

		for (Int k = 0; k <= side; ++k)
		{
			--x;
			Real dx = (Real)((searchCenterCell->x + x) * 10) - info->m_target->getPosition()->x;
			Real dy = (Real)((searchCenterCell->y + y) * 10) - info->m_target->getPosition()->y;
			Real distance = dx * dx + dy * dy;
			if ((!found || !(distance >= best)) && info->checkCell(searchCenterCell->x + x, searchCenterCell->y + y))
			{
				foundCell->x = searchCenterCell->x + x;
				foundCell->y = searchCenterCell->y + y;
				found = true;
				best = distance;
				remaining = iterationsAfterHit;
			}
		}

		for (Int n = 0; n <= side; ++n)
		{
			--y;
			Real dx = (Real)((searchCenterCell->x + x) * 10) - info->m_target->getPosition()->x;
			Real dy = (Real)((searchCenterCell->y + y) * 10) - info->m_target->getPosition()->y;
			Real distance = dx * dx + dy * dy;
			if ((!found || !(distance >= best)) && info->checkCell(searchCenterCell->x + x, searchCenterCell->y + y))
			{
				foundCell->x = searchCenterCell->x + x;
				foundCell->y = searchCenterCell->y + y;
				found = true;
				best = distance;
				remaining = iterationsAfterHit;
			}
		}
	}

	return found;
}
