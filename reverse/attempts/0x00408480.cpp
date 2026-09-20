// ?d_00408480@@YAXXZ
// partial score=0.45 date=2026-09-20
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Open-BFME: carved body at retail 0x00408480 (292 B), reached by the
// PathfindZoneManager::calculateZonesIncremental scheduler declared in
// PathfindZoneManagerCalculateZones.cpp. No readable Zero Hour twin exists
// for the incremental split, so this is an address-derived straight-line
// port. Walks m_zoneBlocks (this+0x23628) with 0x228-byte block records,
// dividing the column range into 16-unit cells and calling a per-cell
// worker (still a dump at retail 0x00407030) for every populated row.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

class PathfindZoneManager;

class ZoneBlock
{
public:
	void bfmeProcessCell(void *p1, IRegion2D *region, IRegion2D *bounds, PathfindZoneManager *owner);
};

#pragma pack(push, 1)
class PathfindZoneManager
{
public:
	void bfmeCalcZonesIncrementalStep00408480(void *p1, IRegion2D *bounds, Int p3, Int p4);

private:
	unsigned char m_before23628[0x23628];
	ZoneBlock **m_zoneBlocks;               // +0x23628
};
#pragma pack(pop)

void PathfindZoneManager::bfmeCalcZonesIncrementalStep00408480(void *p1, IRegion2D *bounds, Int p3, Int p4)
{
	Int loX = bounds->lo.x;
	Int width = bounds->hi.x - loX;
	Int loY = bounds->lo.y;
	Int blockCountX = (width + 16) / 16;
	Int height = bounds->hi.y - loY;
	Int blockCountY = (height + 16) / 16;

	Int gridCols = (blockCountX * p3) / 10;
	Int gridRows = (blockCountX * p4) / 10;

	for (Int col = gridCols; col < gridRows; ++col)
	{
		if (blockCountY > 0)
		{
			Int rowOffset = 0;
			Int cellY = 0;
			Int remaining = blockCountY;
			Int colBase = col << 4;
			do
			{
				IRegion2D region;
				Int cellX = bounds->lo.x + colBase;
				Int cellYStart = bounds->lo.y + cellY;
				Int endX = cellX + 0xf;
				Int endY = cellYStart + 0xf;

				region.lo.x = cellX;
				region.lo.y = cellYStart;
				if (endX > bounds->hi.x)
					endX = bounds->hi.x;
				region.hi.x = endX;
				if (endY > bounds->hi.y)
					endY = bounds->hi.y;
				region.hi.y = endY;

				ZoneBlock *block = (ZoneBlock *)((char *)m_zoneBlocks[col] + rowOffset);
				block->bfmeProcessCell(p1, &region, bounds, this);

				cellY += 0x10;
				rowOffset += 0x228;
			} while (--remaining != 0);
		}
	}
}
