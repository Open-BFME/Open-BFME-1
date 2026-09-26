// ?bfmeCalcZonesIncrementalStep00408480@PathfindZoneManager@@QAEXPAPAVPathfindCell@@ABUIRegion2D@@HH@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include

// Open-BFME: carved body at retail 0x00408480 (292 B), one slice of the
// BFME incremental zone rebuild. The named scheduler
// PathfindZoneManager::calculateZonesIncremental (retail 0x00408AD0, see
// PathfindZoneManagerCalculateZones.cpp) calls it for states 2..10 with
// (map, globalBounds, (state-2)*100/9, (state-1)*100/9), so each call
// rebuilds one percentage band of the zone-block columns. The block walk
// is the Zero Hour PathfindZoneManager::calculateZones loop
// (inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp)
// with the four-argument address-derived worker at retail 0x00407030 (ret
// 0x10, reached through ILT 0x00008954). Both callers pass the receiver in
// ECX and four stack arguments; no semantic method name is claimed for it.

#include "Lib/BaseType.h"

class PathfindCell;
class PathfindZoneManager;

// Opaque receiver for the unconverted retail body at this address. The
// 0x228-byte size is witnessed by the caller's zone-block stride.
class Rva00407030
{
public:
	void process(PathfindCell **map, const IRegion2D &bounds,
		const IRegion2D &globalBounds, PathfindZoneManager *owner);

private:
	unsigned char m_storage[0x228];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindZoneManager
{
public:
	enum { ZONE_BLOCK_SIZE = 16 };

	void bfmeCalcZonesIncrementalStep00408480(PathfindCell **map,
		const IRegion2D &globalBounds, Int startPercent, Int endPercent);

private:
	unsigned char m_before23628[0x23628];
	Rva00407030 **m_zoneBlocks;             // +0x23628
};

void PathfindZoneManager::bfmeCalcZonesIncrementalStep00408480(PathfindCell **map,
	const IRegion2D &globalBounds, Int startPercent, Int endPercent)
{
	Int xCount = (globalBounds.hi.x-globalBounds.lo.x+1+ZONE_BLOCK_SIZE-1)/ZONE_BLOCK_SIZE;
	Int yCount = (globalBounds.hi.y-globalBounds.lo.y+1+ZONE_BLOCK_SIZE-1)/ZONE_BLOCK_SIZE;
	Int xStart = xCount*startPercent/100;
	Int xEnd = xCount*endPercent/100;
	Int xBlock, yBlock;
	for (xBlock=xStart; xBlock<xEnd; xBlock++)
	{
		for (yBlock=0; yBlock<yCount; yBlock++)
		{
			IRegion2D bounds;
			bounds.lo.x = globalBounds.lo.x + xBlock*ZONE_BLOCK_SIZE;
			bounds.lo.y = globalBounds.lo.y + yBlock*ZONE_BLOCK_SIZE;
			bounds.hi.x = bounds.lo.x + ZONE_BLOCK_SIZE - 1; // bounds are inclusive.
			bounds.hi.y = bounds.lo.y + ZONE_BLOCK_SIZE - 1; // bounds are inclusive.
			if (bounds.hi.x > globalBounds.hi.x)
				bounds.hi.x = globalBounds.hi.x;
			if (bounds.hi.y > globalBounds.hi.y)
				bounds.hi.y = globalBounds.hi.y;
			m_zoneBlocks[xBlock][yBlock].process(map, bounds, globalBounds, this);
		}
	}
}
