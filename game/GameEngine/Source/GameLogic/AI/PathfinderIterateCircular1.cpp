// cl: /DNDEBUG /MD /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// Retail 0x003D9F00 (969 bytes) and 0x003DA3C0 (1017 bytes).
// The diagnostic at VA 0x010EE570 names IterateCircular1; address tokens
// distinguish its two callback specializations without inventing their names.
// Parent wrappers 0x003DAC80/0x003DAD60 supply the Pathfinder callback context.
// Traversal follows the already matched iterateCircular2; all five diagnostic
// strings are copied from the retail image and verified by the scoped gate.
#include "Lib/BaseType.h"
class CRCParameterCheck;
extern bool Glo012F0239;
extern CRCParameterCheck *TheCRCParameterCheck;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(CRCParameterCheck *,const char *,...);
// Both predicates witness 16-byte cells and the packed word at +0x0c.
struct PathfindCell
{
 char m_pad00[0xc];
 unsigned int m_packed;
 __forceinline bool bit21() const { return ((m_packed >> 21) & 1) != 0; }
 __forceinline unsigned int low3() const { return m_packed & 7; }
};
class Pathfinder {
public:
 Bool iterateCircular1Ground003D9F00(const ICoord2D *,Int,ICoord2D *,void *);
 Bool iterateCircular1Predicate003DA3C0(const ICoord2D *,Int,ICoord2D *,void *);
 char m_pad00[0x10]; PathfindCell **m_map;
 struct { ICoord2D lo,hi; } m_extent;
 __forceinline PathfindCell *groundCell(int x,int y) {
  if(x>=m_extent.lo.x && x<=m_extent.hi.x && y>=m_extent.lo.y && y<=m_extent.hi.y)
   return &m_map[x][y];
  return 0;
 }
};
struct GroundSearch003D9F00 {
 Pathfinder *pathfinder;
 __forceinline bool check(int x,int y) const {
  PathfindCell *cell=pathfinder->groundCell(x,y);
  return cell && ((cell->m_packed>>6)&63)==1;
 }
};
Bool Pathfinder::iterateCircular1Ground003D9F00(const ICoord2D *scanCenterCell, Int remainingCellBudget, ICoord2D *foundCell, void *adjustTargetInfoData)
{
	if (Glo012F0239 && TheCRCParameterCheck)
	{
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
			"\t\tIterateCircular1 called with center=%d,%d, maxCells=%d",
			scanCenterCell->x, scanCenterCell->y, remainingCellBudget);
	}

	GroundSearch003D9F00 *targetSearch = (GroundSearch003D9F00 *)adjustTargetInfoData;
	if (targetSearch->check(scanCenterCell->x, scanCenterCell->y))
	{
		if (Glo012F0239 && TheCRCParameterCheck)
			bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\tfunc succeeded found=%d,%d", scanCenterCell->x, scanCenterCell->y);
		foundCell->x=scanCenterCell->x;
		foundCell->y=scanCenterCell->y;
		return true;
	}
	if (Glo012F0239 && TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\tfunc failed");

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
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
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
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
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
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
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
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		if (bestOffsetDistanceSquared == 0)
		{
			ringExtent += 2;
		}
		else
		{
			if (Glo012F0239 && TheCRCParameterCheck)
				bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\tbest return true. found=%d,%d", foundCell->x, foundCell->y);
			return true;
		}
	}

	if (Glo012F0239 && TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\ttotal failure. found=%d,%d", foundCell->x, foundCell->y);
	return false;
}

// RVA 0x003DA3C0 uses the same traversal with the landed Rva003D5B70 predicate.
// The initial probe calls the external predicate; the four ring probes inline it.
struct Rva003D5B70 {
 Pathfinder *pathfinder;
 bool check(int x,int y);
 __forceinline bool inlineCheck(int x,int y) {
  PathfindCell *cell=pathfinder->groundCell(x,y);
  if(cell) {
   if(cell->bit21()) return false;
   if(cell->low3()==2 || cell->low3()==5 || cell->low3()==4 || cell->low3()==1) return false;
  }
  return true;
 }
};
Bool Pathfinder::iterateCircular1Predicate003DA3C0(const ICoord2D *scanCenterCell, Int remainingCellBudget, ICoord2D *foundCell, void *adjustTargetInfoData)
{
	if (Glo012F0239 && TheCRCParameterCheck)
	{
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
			"\t\tIterateCircular1 called with center=%d,%d, maxCells=%d",
			scanCenterCell->x, scanCenterCell->y, remainingCellBudget);
	}

	Rva003D5B70 *targetSearch = (Rva003D5B70 *)adjustTargetInfoData;
	if (targetSearch->check(scanCenterCell->x, scanCenterCell->y))
	{
		if (Glo012F0239 && TheCRCParameterCheck)
			bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\tfunc succeeded found=%d,%d", scanCenterCell->x, scanCenterCell->y);
		foundCell->x=scanCenterCell->x;
		foundCell->y=scanCenterCell->y;
		return true;
	}
	if (Glo012F0239 && TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\tfunc failed");

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
				if (targetSearch->inlineCheck(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = ringExtent; stepsRemaining > 0; --stepsRemaining)
		{
			++cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->inlineCheck(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetX;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->inlineCheck(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->inlineCheck(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		if (bestOffsetDistanceSquared == 0)
		{
			ringExtent += 2;
		}
		else
		{
			if (Glo012F0239 && TheCRCParameterCheck)
				bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\tbest return true. found=%d,%d", foundCell->x, foundCell->y);
			return true;
		}
	}

	if (Glo012F0239 && TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\ttotal failure. found=%d,%d", foundCell->x, foundCell->y);
	return false;
}

